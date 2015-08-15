#include "precompiled.hpp"
#include "ui/BallsCanvas.hpp"

#include <stdexcept>

#include <QtGui/QCursor>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions_3_0>
#include <QtGui/QOpenGLFunctions_3_1>
#include <QtGui/QOpenGLFunctions_3_2_Core>
#include <QtGui/QOpenGLFunctions_3_3_Core>
#include <QtGui/QOpenGLFunctions_4_0_Core>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtGui/QOpenGLFunctions_4_2_Core>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QOpenGLWidget>

#include "util/Logging.hpp"
#include "util/Util.hpp"
#include "Constants.hpp"
#include "mesh/Mesh.hpp"
#include "mesh/MeshGenerator.hpp"
#include "config/Settings.hpp"
#include "ui/BallsWindow.hpp"

namespace balls {

using std::pair;
using std::runtime_error;
using std::vector;
using namespace balls::config;
using namespace balls::shader;
using FormatOption = QSurfaceFormat::FormatOption;
using FormatOptions = QSurfaceFormat::FormatOptions;
using OpenGLContextProfile = QSurfaceFormat::OpenGLContextProfile;
using RenderableType = QSurfaceFormat::RenderableType;
using SwapBehavior = QSurfaceFormat::SwapBehavior;
using UsagePattern = QOpenGLBuffer::UsagePattern;

constexpr FormatOption FORMAT_OPTION =
  #ifdef DEBUG
  FormatOption::DebugContext;
  #else
  FormatOption::StereoBuffers;
  #endif
constexpr OpenGLContextProfile PROFILE = OpenGLContextProfile::CoreProfile;
constexpr RenderableType RENDER_TYPE = RenderableType::OpenGL;
constexpr SwapBehavior SWAP_TYPE = SwapBehavior::DefaultSwapBehavior;
constexpr int SAMPLES = 4;
constexpr int DEPTH_BUFFER_BITS = 8;

constexpr FormatOptions FLAGS(FORMAT_OPTION | RENDER_TYPE | PROFILE |
                              SWAP_TYPE);

constexpr UsagePattern USAGE_PATTERN = UsagePattern::StaticDraw;

constexpr float DEFAULT_ZOOM = -8;
constexpr float TRACKBALL_RADIUS = 1;

BallsCanvas::BallsCanvas(QWidget* parent)
  : QOpenGLWidget(parent),
    _uniforms(nullptr),
    _uniformsMeta(_uniforms.metaObject()),
    _uniformsPropertyOffset(_uniformsMeta->propertyOffset()),
    _uniformsPropertyCount(_uniformsMeta->propertyCount()),
    _log(nullptr),
    _vbo(QOpenGLBuffer::VertexBuffer),
    _ibo(QOpenGLBuffer::IndexBuffer),
    _gl30(nullptr),
    _gl31(nullptr),
    _gl32(nullptr),
    _gl33(nullptr),
    _gl40(nullptr),
    _gl41(nullptr),
    _gl42(nullptr),
    _gl43(nullptr)
{
  QSurfaceFormat format(FLAGS);
  format.setSamples(SAMPLES);
  format.setDepthBufferSize(DEPTH_BUFFER_BITS);
  this->setFormat(format);
  _uniforms.setObjectName("Uniforms");
  this->installEventFilter(&_uniforms);
  // ^ So it will show up
  // TODO: Handle uniforms whose names start with "_" or "_q_" or even "__"

}

BallsCanvas::~BallsCanvas() {
  _ibo.release();
  _vbo.release();
  _vao.release();
  _ibo.destroy();
  _vbo.destroy();
  _vao.destroy();
  _shader.disableAttributeArray(_attributes[attribute::POSITION]);
  _shader.disableAttributeArray(_attributes[attribute::NORMAL]);
  _shader.removeAllShaders();
}

void BallsCanvas::initializeGL() {
  this->initializeOpenGLFunctions();

  connect(this, &BallsCanvas::uniformsDiscovered, &_uniforms, &Uniforms::receiveUniforms);
  _initSettings();
  _initGLPointers();
  _initGLMemory();
  _initLogger();
  _initShaders();
  _initAttributeLocations();
  _initAttributes();
  //_updateUniformList();

  this->finishedInitializing();
  this->startTimer(1000.f / 60, Qt::PreciseTimer);
}

void BallsCanvas::_initSettings() noexcept {
  this->_settings[SettingKey::WireFrame] = {false};
  this->_settings[SettingKey::DepthTestEnabled] = {true, true};
  this->_settings[SettingKey::FaceCullingEnabled] = {true, true};
  this->_settings[SettingKey::Dithering] = {true, true};
}

template <int Major, int Minor, class QOpenGLF>
void _initGLFunction(QOpenGLF** gl) noexcept {
  using namespace logs;

  * (gl) = QOpenGLContext::currentContext()->versionFunctions<QOpenGLF>();

  if (*gl) {
    (*gl)->initializeOpenGLFunctions();
    // If we have this version of OpenGL available...
  }

  qCDebug(logs::gl::Feature).nospace() << "OpenGL " << Major << '.' << Minor
  << ((*gl) ? " available" : " NOT available");
}

inline void BallsCanvas::_initGLPointers() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  _initGLFunction<3, 0, QOpenGLFunctions_3_0>(&(_gl30));
  _initGLFunction<3, 1, QOpenGLFunctions_3_1>(&(_gl31));
  _initGLFunction<3, 2, QOpenGLFunctions_3_2_Core>(&(_gl32));
  _initGLFunction<3, 3, QOpenGLFunctions_3_3_Core>(&(_gl33));
  _initGLFunction<4, 0, QOpenGLFunctions_4_0_Core>(&(_gl40));
  _initGLFunction<4, 1, QOpenGLFunctions_4_1_Core>(&(_gl41));
  _initGLFunction<4, 2, QOpenGLFunctions_4_2_Core>(&(_gl42));
  _initGLFunction<4, 3, QOpenGLFunctions_4_3_Core>(&(_gl43));
  QSurfaceFormat format = context()->format();
  this->_glmajor = format.majorVersion();
  this->_glminor = format.minorVersion();

  bool hasGeom = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Geometry);
  this->geometryShadersSupported(hasGeom);

  if (!hasGeom) {
    qCWarning(logs::gl::Feature) << "Geometry shaders not supported!";
  }

  if (!QOpenGLShaderProgram::hasOpenGLShaderPrograms()) {
    fatalGraphicsError(
      tr("OpenGL Error: Hardware too old"),
      tr("Shaders are not available on this graphics hardware, but BALLS needs"
         " them to run."),
      constants::errors::SHADER_PROGRAMS_UNAVAILABLE);
  }

  if (!(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex) &&
        QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment))) {
    fatalGraphicsError(
      tr("OpenGL Error: Required features not available"),
      tr("Vertex and fragment shaders must both be available, but they're not."),
      constants::errors::SHADER_TYPES_UNAVAILABLE);
  }

  if (!hasOpenGLFeature(OpenGLFeature::Buffers)) {
    fatalGraphicsError(
      tr("OpenGL Error: Required features not available"),
      tr("Vertex and index buffer objects must be available, but they're not"),
      constants::errors::BUFFERS_UNAVAILABLE);
  }

  if (!hasOpenGLFeature(OpenGLFeature::Framebuffers)) {
    throw std::runtime_error("Need framebuffers");
  }


  if (!_gl30) {
    QString e = QString(
                  tr("OpenGL 3.0 or higher is required to use BALLS, but only "
                     "%1.%2 is available"))
                .arg(_glmajor)
                .arg(_glminor);

    qCCritical(logs::gl::Feature) << e;
    this->fatalGraphicsError(
      tr("OpenGL version is too old"), e,
      constants::errors::NEED_BETTER_OPENGL);
  }
}

void BallsCanvas::_initGLMemory() {
  using std::runtime_error;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_vao.create()) {
    QString e = QString("Could not create VAO (ID: %1)").arg(_vao.objectId());
    throw runtime_error(qPrintable(e));
  }

  _vao.bind();

  if (Q_UNLIKELY(!(_vbo.create() && _vbo.bind()))) {
    throw std::runtime_error("");
    // TODO: Exception text
  }

  _vbo.setUsagePattern(USAGE_PATTERN);
  qCDebug(logs::gl::Feature) << "VBO" << _vbo.bufferId() <<
                             "created and bound";

  if (Q_UNLIKELY(!(_ibo.create() && _ibo.bind()))) {
    throw std::runtime_error("");
    // TODO: Exception text
  }

  _ibo.setUsagePattern(USAGE_PATTERN);
  qCDebug(logs::gl::Feature) << "IBO" << _ibo.bufferId() <<
                             "created and bound";
}

void BallsCanvas::_initLogger() noexcept {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_log.initialize()) {
    qCWarning(logs::gl::Feature) <<
    "OpenGL debug logging unsupported on this driver";
  }
  else {
    _log.enableMessages();
    _log.startLogging();
  }
}

void BallsCanvas::_initShaders() noexcept {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  Q_ASSUME(_shader.addShaderFromSourceFile(
    QOpenGLShader::Vertex, constants::paths::DEFAULT_VERTEX));
  Q_ASSUME(_shader.addShaderFromSourceFile(
    QOpenGLShader::Fragment, constants::paths::DEFAULT_FRAGMENT));
  // These shaders are built into the binary via the resource system
  Q_ASSUME(_shader.link() && _shader.bind());
  // If we've gotten this far, then the code that checked for the availability
  // of shaders has already given us the green light
}

void BallsCanvas::_initAttributeLocations() noexcept {
  using namespace attribute;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  Q_ASSERT(this->_gl30 != nullptr);
  #ifdef DEBUG
  int currentShader = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
  Q_ASSERT(static_cast<GLuint>(currentShader) == _shader.programId());
  #endif
  _attributes[POSITION] = _shader.attributeLocation(qPrintable(POSITION));
  _attributes[NORMAL] = _shader.attributeLocation(qPrintable(NORMAL));
  _gl30->glBindFragDataLocation(_shader.programId(), 0, qPrintable(out::FRAGMENT));
}

// Called on recompile
void BallsCanvas::_updateUniformList() noexcept {
  using std::array;
  using util::resolveGLType;
  using util::types::UniformInfo;

  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  array<GLchar, 128> name;
  GLuint program = _shader.programId();

  GLsizei length = 0;
  GLint size = 0;
  GLenum type = 0;
  int activeUniforms = 0;
  glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);

  balls::util::types::UniformCollection uniformInfo;
  uniformInfo.reserve(activeUniforms);

  for (int i = 0; i < activeUniforms; ++i) {
    glGetActiveUniform(program, i, name.size() - 1, &length, &size, &type,
    name.data());
    QString sname(name.data());
    Q_ASSERT(sname.size() == length);

    uniformInfo.push_back({sname, i, type, size});
  }

  this->uniformsDiscovered(uniformInfo);

  qCDebug(logs::uniform::Name) << "Updated uniform list";
}

void BallsCanvas::_updateUniformValues() noexcept {
  using util::types::UniformInfo;

  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  for (const UniformInfo& i : this->_uniforms.uniformInfo()) {
    QVariant u = _uniforms.property(qPrintable(i.name));
    setUniform(i, u);
  }
}

void BallsCanvas::_initAttributes() noexcept {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  #ifdef DEBUG
  int currentShader = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
  Q_ASSERT(static_cast<GLuint>(currentShader) == _shader.programId());
  #endif

  int position = _attributes[attribute::POSITION];
  int normal = _attributes[attribute::NORMAL];
  glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  (void*)0);
  glVertexAttribPointer(
    normal, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  _shader.enableAttributeArray(position);
  _shader.enableAttributeArray(normal);
}

void BallsCanvas::resizeGL(const int width, const int height) {
}

void BallsCanvas::paintGL() {
  Q_ASSERT(this->_vao.isCreated());
  Q_ASSERT(this->_vbo.isCreated());
  Q_ASSERT(this->_ibo.isCreated());

  _updateGLSetting<GL_DEPTH_TEST>(SettingKey::DepthTestEnabled);
  _updateGLSetting<GL_CULL_FACE>(SettingKey::FaceCullingEnabled);
  _updateGLSetting<GL_DITHER>(SettingKey::Dithering);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _updateUniformValues();
  glDrawElements(
    _settings[SettingKey::WireFrame].value.toBool() ? GL_LINE_STRIP
    : GL_TRIANGLES,
    _mesh.indices().size(),
    GL_UNSIGNED_SHORT,
    nullptr
  );
}

void BallsCanvas::setMesh(mesh::MeshGenerator* generator) noexcept {
  using mesh::Mesh;
  Q_ASSERT(generator != nullptr);

  this->_meshgen = generator;
  this->_mesh = this->_meshgen->getMesh();

  vector<Mesh::CoordType> data = this->_mesh.combined();
  const vector<Mesh::IndexType>& indices = this->_mesh.indices();

  this->_vbo.bind();
  this->_vbo.allocate(data.data(), data.size() * sizeof(Mesh::CoordType));
  this->_ibo.bind();
  this->_ibo.allocate(indices.data(), indices.size() * sizeof(Mesh::IndexType));
}

void BallsCanvas::setOption(const bool value) noexcept {
  QObject* send = sender();
  QVariant name = send->property(constants::properties::OPTION);

  Q_ASSERT(send != nullptr); // Must be called as a slot!
  Q_ASSERT(name.isValid()&&  name.type() == QVariant::String);

  this->_settings[name.toString()] = Setting(value, true);

  qCDebug(logs::gl::State) << "Set" << name.toString() << "to" << value;
}

void BallsCanvas::setOption(const int value) noexcept {
  QObject* send = sender();
  QVariant name = send->property(constants::properties::OPTION);

  Q_ASSERT(send != nullptr); // Must be called as a slot!");
  Q_ASSERT(name.isValid() && name.type() == QVariant::String);

  this->_settings[name.toString()] = Setting(value, true);

  qCDebug(logs::gl::State) << "Set" << name.toString() << "to" << value;
}

void BallsCanvas::mouseMoveEvent(QMouseEvent *e) {
}

void BallsCanvas::wheelEvent(QWheelEvent *) {
}

void BallsCanvas::timerEvent(QTimerEvent * e) {
  update();
}

void BallsCanvas::setUniform(const UniformInfo& info, const QVariant& var) noexcept {
  if (!_shader.isLinked()) return;
  if (_shader.programId() == 0) return;
  // If the shader wasn't compiled properly, the object's ID will be 0 (no shader)

  Q_ASSERT(var.isValid());
  Q_ASSERT(_shader.uniformLocation(info.name) == info.index);

  int index = info.index;

  if (index != -1) {
    this->makeCurrent();

    switch (info.type) {
    case GL_INT: {
      Q_ASSERT(var.canConvert<int>());
      _gl30->glUniform1i(index, var.value<int>());
      break;
    }

    case GL_DOUBLE: {
      if (_gl40) {
        // If the GPU supports double types...
        Q_ASSERT(var.canConvert<double>());
        _gl40->glUniform1d(index, var.value<double>());
        break;
      }
    }

    // Otherwise, just treat it like a float
    case GL_FLOAT: {
      Q_ASSERT(var.canConvert<float>());
      _gl30->glUniform1f(index, var.value<float>());
      break;
    }

    case GL_UNSIGNED_INT: {
      Q_ASSERT(var.canConvert<unsigned int>());
      _gl30->glUniform1ui(index, var.value<unsigned int>());
      break;
    }

    case GL_BOOL: {
      Q_ASSERT(var.canConvert<bool>());
      _gl30->glUniform1i(index, var.value<bool>());
      break;
    }

    case GL_DOUBLE_VEC2: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dvec2>());
        glm::dvec2 dvec2 = var.value<glm::dvec2>();
        _gl40->glUniform2d(index, dvec2.x, dvec2.y);
        break;
      }
    }

    case GL_FLOAT_VEC2: {
      Q_ASSERT(var.canConvert<glm::vec2>());
      glm::vec2 vec2 = var.value<glm::vec2>();
      _gl30->glUniform2f(index, vec2.x, vec2.y);
      break;
    }

    case GL_INT_VEC2: {
      Q_ASSERT(var.canConvert<glm::ivec2>());
      glm::ivec2 ivec2 = var.value<glm::ivec2>();
      _gl30->glUniform2i(index, ivec2.x, ivec2.y);
      break;
    }

    case GL_UNSIGNED_INT_VEC2: {
      Q_ASSERT(var.canConvert<glm::uvec2>());
      glm::uvec2 uvec2 = var.value<glm::uvec2>();
      _gl30->glUniform2ui(index, uvec2.x, uvec2.y);
      break;
    }

    case GL_BOOL_VEC2: {
      Q_ASSERT(var.canConvert<glm::bvec2>());
      glm::bvec2 bvec2 = var.value<glm::bvec2>();
      _gl30->glUniform2i(index, bvec2.x, bvec2.y);
      break;
    }

    case GL_DOUBLE_VEC3: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dvec3>());
        glm::dvec3 dvec3 = var.value<glm::dvec3>();
        _gl40->glUniform3d(index, dvec3.x, dvec3.y, dvec3.z);
        break;
      }
      // Otherwise, case to GL_FLOAT_VEC3
    }

    case GL_FLOAT_VEC3: {
      Q_ASSERT(var.canConvert<glm::vec3>());
      glm::vec3 vec3 = var.value<glm::vec3>();
      _gl30->glUniform3f(index, vec3.x, vec3.y, vec3.z);
      break;
    }

    case GL_INT_VEC3: {
      Q_ASSERT(var.canConvert<glm::ivec3>());
      glm::ivec3 ivec3 = var.value<glm::ivec3>();
      _gl30->glUniform3i(index, ivec3.x, ivec3.y, ivec3.z);
      break;
    }

    case GL_UNSIGNED_INT_VEC3: {
      Q_ASSERT(var.canConvert<glm::uvec3>());
      glm::uvec3 uvec3 = var.value<glm::uvec3>();
      _gl30->glUniform3ui(index, uvec3.x, uvec3.y, uvec3.z);
      break;
    }

    case GL_BOOL_VEC3: {
      Q_ASSERT(var.canConvert<glm::bvec3>());
      glm::bvec3 bvec3 = var.value<glm::bvec3>();
      _gl30->glUniform3i(index, bvec3.x, bvec3.y, bvec3.z);
      break;
    }

    case GL_DOUBLE_VEC4: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dvec4>());
        glm::dvec4 dvec4 = var.value<glm::dvec4>();
        _gl40->glUniform4d(index, dvec4.x, dvec4.y, dvec4.z, dvec4.w);
        break;
      }
    }

    case GL_FLOAT_VEC4: {
      Q_ASSERT(var.canConvert<glm::vec4>());
      glm::vec4 vec4 = var.value<glm::vec4>();
      _gl30->glUniform4f(index, vec4.x, vec4.y, vec4.z, vec4.w);
      break;
    }

    case GL_INT_VEC4: {
      Q_ASSERT(var.canConvert<glm::ivec4>());
      glm::ivec4 ivec4 = var.value<glm::ivec4>();
      _gl30->glUniform4i(index, ivec4.x, ivec4.y, ivec4.z, ivec4.w);
      break;
    }

    case GL_UNSIGNED_INT_VEC4: {
      Q_ASSERT(var.canConvert<glm::uvec4>());
      glm::uvec4 uvec4 = var.value<glm::uvec4>();
      _gl30->glUniform4ui(index, uvec4.x, uvec4.y, uvec4.z, uvec4.w);
      break;
    }

    case GL_BOOL_VEC4: {
      Q_ASSERT(var.canConvert<glm::bvec4>());
      glm::bvec4 bvec4 = var.value<glm::bvec4>();
      _gl30->glUniform4i(index, bvec4.x, bvec4.y, bvec4.z, bvec4.w);
      break;
    }

    case GL_DOUBLE_MAT2: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat2>());
        glm::dmat2 dmat2 = var.value<glm::dmat2>();
        _gl40->glUniformMatrix2dv(index, 1, false, glm::value_ptr(dmat2));
        break;
      }
    }

    case GL_FLOAT_MAT2: {
      Q_ASSERT(var.canConvert<glm::mat2>());
      glm::mat2 mat2 = var.value<glm::mat2>();
      _gl30->glUniformMatrix2fv(index, 1, false, glm::value_ptr(mat2));
      break;
    }

    case GL_DOUBLE_MAT2x3: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat2x3>());
        glm::dmat2x3 dmat2x3 = var.value<glm::dmat2x3>();
        _gl40->glUniformMatrix2x3dv(index, 1, false, glm::value_ptr(dmat2x3));
        break;
      }
    }

    case GL_FLOAT_MAT2x3: {
      Q_ASSERT(var.canConvert<glm::mat2x3>());
      glm::mat2x3 mat2x3 = var.value<glm::mat2x3>();
      _gl30->glUniformMatrix2x3fv(index, 1, false, glm::value_ptr(mat2x3));
      break;
    }

    case GL_DOUBLE_MAT2x4: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat2x4>());
        glm::dmat2x4 dmat2x4 = var.value<glm::dmat2x4>();
        _gl40->glUniformMatrix2x4dv(index, 1, false, glm::value_ptr(dmat2x4));
        break;
      }
    }

    case GL_FLOAT_MAT2x4: {
      Q_ASSERT(var.canConvert<glm::mat2x4>());
      glm::mat2x4 mat2x4 = var.value<glm::mat2x4>();
      _gl30->glUniformMatrix2x4fv(index, 1, false, glm::value_ptr(mat2x4));
      break;
    }

    case GL_DOUBLE_MAT3x2: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat3x2>());
        glm::dmat3x2 dmat3x2 = var.value<glm::dmat3x2>();
        _gl40->glUniformMatrix3x2dv(index, 1, false, glm::value_ptr(dmat3x2));
        break;
      }
    }

    case GL_FLOAT_MAT3x2: {
      Q_ASSERT(var.canConvert<glm::mat3x2>());
      glm::mat3x2 mat3x2 = var.value<glm::mat3x2>();
      _gl30->glUniformMatrix3x2fv(index, 1, false, glm::value_ptr(mat3x2));
      break;
    }

    case GL_DOUBLE_MAT3: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat3>());
        glm::dmat3 dmat3 = var.value<glm::dmat3>();
        _gl40->glUniformMatrix3dv(index, 1, false, glm::value_ptr(dmat3));
        break;
      }
    }

    case GL_FLOAT_MAT3: {
      Q_ASSERT(var.canConvert<glm::mat3>());
      glm::mat3 mat3 = var.value<glm::mat3>();
      _gl30->glUniformMatrix3fv(index, 1, false, glm::value_ptr(mat3));
      break;
    }

    case GL_DOUBLE_MAT3x4: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat3x4>());
        glm::dmat3x4 dmat3x4 = var.value<glm::dmat3x4>();
        _gl40->glUniformMatrix3x4dv(index, 1, false, glm::value_ptr(dmat3x4));
        break;
      }
    }

    case GL_FLOAT_MAT3x4: {
      Q_ASSERT(var.canConvert<glm::mat3x4>());
      glm::mat3x4 mat3x4 = var.value<glm::mat3x4>();
      _gl30->glUniformMatrix3x4fv(index, 1, false, glm::value_ptr(mat3x4));
      break;
    }

    case GL_DOUBLE_MAT4x2: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat4x2>());
        glm::dmat4x2 dmat4x2 = var.value<glm::dmat4x2>();
        _gl40->glUniformMatrix4x2dv(index, 1, false, glm::value_ptr(dmat4x2));
        break;
      }
    }

    case GL_FLOAT_MAT4x2: {
      Q_ASSERT(var.canConvert<glm::mat4x2>());
      glm::mat4x2 mat4x2 = var.value<glm::mat4x2>();
      _gl30->glUniformMatrix4x2fv(index, 1, false, glm::value_ptr(mat4x2));
      break;
    }

    case GL_DOUBLE_MAT4x3: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat4x3>());
        glm::dmat4x3 dmat4x3 = var.value<glm::dmat4x3>();
        _gl40->glUniformMatrix4x3dv(index, 1, false, glm::value_ptr(dmat4x3));
        break;
      }
    }

    case GL_FLOAT_MAT4x3: {
      Q_ASSERT(var.canConvert<glm::mat4x3>());
      glm::mat4x3 mat4x3 = var.value<glm::mat4x3>();
      _gl30->glUniformMatrix4x3fv(index, 1, false, glm::value_ptr(mat4x3));
      break;
    }

    case GL_DOUBLE_MAT4: {
      if (_gl40) {
        Q_ASSERT(var.canConvert<glm::dmat4>());
        glm::dmat4 dmat4 = var.value<glm::dmat4>();
        _gl40->glUniformMatrix4dv(index, 1, false, glm::value_ptr(dmat4));
        break;
      }
    }

    case GL_FLOAT_MAT4: {
      Q_ASSERT(var.canConvert<glm::mat4>());
      glm::mat4 mat4 = var.value<glm::mat4>();
      _gl30->glUniformMatrix4fv(index, 1, false, glm::value_ptr(mat4));
      break;
    }

    default:
      qCWarning(logs::uniform::Type)
          << "Unsupported GLSL type" << util::resolveGLType(info.type);
    }
  }
  else {
    qCWarning(logs::uniform::Name)
        << "Attempted to set non-existing uniform" << info.name << "to" << var;
  }
}

void BallsCanvas::resetCamera() noexcept {
  _uniforms.resetModelView();

  qCDebug(logs::uniform::Env) << "Reset camera and model rotation to default";
}

bool BallsCanvas::updateShaders(const QString& vertex,
                                const QString& geometry,
                                const QString& fragment) noexcept {

  Q_UNUSED(geometry);
  using namespace balls::shader;

  this->makeCurrent();
  this->_shader.release();
  this->_shader.removeAllShaders();

  bool vert = _shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
  bool frag = _shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment);
  bool link = _shader.link();
  bool bind = _shader.bind();
  bool result = vert && frag && link && bind;

  if (Q_UNLIKELY(!vert)) {
    qCWarning(logs::shader::Name) << "Couldn't compile vertex shader";
  }

  if (Q_UNLIKELY(!frag)) {
    qCWarning(logs::shader::Name) << "Couldn't compile fragment shader";
  }

  if (Q_UNLIKELY(!link)) {
    qCWarning(logs::shader::Name) << "Couldn't link shaders together";
  }

  if (Q_UNLIKELY(!bind)) {
    qCWarning(logs::shader::Name) << "Couldn't bind shader program to context";
  }

  if (Q_UNLIKELY(!result)) {
    qCWarning(logs::shader::Name) << _shader.log();
    _shader.removeAllShaders();
  }

  if (Q_LIKELY(result)) {
    this->_updateUniformList();
    qCDebug(logs::shader::Name) << "Updated shaders";
  }

  return result;
}
}
