#include "precompiled.hpp"
#include "ui/BallsCanvas.hpp"

#include <stdexcept>

#include <QtGui/QCursor>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions_3_1>
#include <QtGui/QOpenGLFunctions_3_2_Core>
#include <QtGui/QOpenGLFunctions_3_3_Core>
#include <QtGui/QOpenGLFunctions_4_0_Core>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtGui/QOpenGLFunctions_4_2_Core>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QOpenGLWidget>

#include "Constants.hpp"
#include "model/mesh/Mesh.hpp"
#include "ui/BallsWindow.hpp"
#include "util/Logging.hpp"
#include "util/Util.hpp"

namespace balls {

using std::pair;
using std::runtime_error;
using std::vector;
using namespace balls::config;
using namespace balls::shader;
using UsagePattern = QOpenGLBuffer::UsagePattern;

constexpr UsagePattern USAGE_PATTERN = UsagePattern::StaticDraw;

constexpr float DEFAULT_ZOOM = -8;
constexpr float TRACKBALL_RADIUS = 1;

BallsCanvas::BallsCanvas(QWidget *parent)
  : QOpenGLWidget(parent),
    _uniforms(nullptr),
    _uniformsMeta(nullptr),
    _uniformsPropertyOffset(0),
    _uniformsPropertyCount(0),
    _log(nullptr),
    _positionBuffer(QOpenGLBuffer::VertexBuffer),
    _normalBuffer(QOpenGLBuffer::VertexBuffer),
    _texCoordBuffer(QOpenGLBuffer::VertexBuffer),
    _ibo(QOpenGLBuffer::IndexBuffer),
    m_indexCount(0) {
  qDebug() << "Format:" << this->format();
}

BallsCanvas::~BallsCanvas() {
  qDebug() << "Cleaning up the BallsCanvas";
  _ibo.release();
  _positionBuffer.release();
  _normalBuffer.release();
  _texCoordBuffer.release();
  _vao.release();
  _ibo.destroy();
  _positionBuffer.destroy();
  _normalBuffer.destroy();
  _texCoordBuffer.destroy();
  _vao.destroy();
  _shader.disableAttributeArray(_attributes[attribute::POSITION]);
  _shader.disableAttributeArray(_attributes[attribute::NORMAL]);
  _shader.disableAttributeArray(_attributes[attribute::TEXCOORDS]);
  _shader.removeAllShaders();
}

void BallsCanvas::initializeGL() {
  qDebug() << "Initializing the BallsCanvas";
  this->initializeOpenGLFunctions();

  connect(
    this,
    &BallsCanvas::uniformsDiscovered,
    _uniforms,
    &Uniforms::receiveUniforms);
  _initGLPointers();
  _initGLMemory();
  _initLogger();
  _initShaders();
  _initAttributes();
  //_updateUniformList();

  this->finishedInitializing(this->gl);
  this->startTimer(1000.f / 60, Qt::PreciseTimer);
}

inline void BallsCanvas::_initGLPointers() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  gl = OpenGLPointers(context());
  qCDebug(logs::gl::Feature) << "OpenGL 3.1:" << (gl.gl31 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 3.2:" << (gl.gl32 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 3.3:" << (gl.gl33 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 4.0:" << (gl.gl40 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 4.1:" << (gl.gl41 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 4.2:" << (gl.gl42 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 4.3:" << (gl.gl43 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 4.4:" << (gl.gl44 ? "OK" : "No");
  qCDebug(logs::gl::Feature) << "OpenGL 4.5:" << (gl.gl45 ? "OK" : "No");

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
      tr(
        "Shaders are not available on this graphics "
        "hardware, but BALLS needs"
        " them to run."),
      constants::errors::SHADER_PROGRAMS_UNAVAILABLE);
  }

  if (
    !(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex)
      && QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment))) {
    fatalGraphicsError(
      tr("OpenGL Error: Required features not available"),
      tr(
        "Vertex and fragment shaders must both be available, "
        "but they're not."),
      constants::errors::SHADER_TYPES_UNAVAILABLE);
  }

  if (!hasOpenGLFeature(OpenGLFeature::Buffers)) {
    fatalGraphicsError(
      tr("OpenGL Error: Required features not available"),
      tr(
        "Vertex and index buffer objects must be available, "
        "but they're not"),
      constants::errors::BUFFERS_UNAVAILABLE);
  }

  if (!hasOpenGLFeature(OpenGLFeature::Framebuffers)) {
    throw std::runtime_error("Need framebuffers");
  }

  if (!gl.gl31) {
    QString e = QString(
                  tr(
                    "OpenGL 3.1 or higher is required to use BALLS, but only "
                    "%1.%2 is available"))
                  .arg(_glmajor)
                  .arg(_glminor);

    qCCritical(logs::gl::Feature) << e;
    this->fatalGraphicsError(
      tr("OpenGL version is too old"),
      e,
      constants::errors::NEED_BETTER_OPENGL);
  }
}

static void _initBuffer(QOpenGLFunctions* gl, QOpenGLBuffer& buffer, const QString& name) {
  if (!buffer.create()) {
    QString e = QString("Could not create %1 buffer").arg(name);
    throw std::runtime_error(qPrintable(e));
  }
  buffer.setUsagePattern(USAGE_PATTERN);

  if (GLenum error = gl->glGetError()) {
    qDebug() << "Error" << error << "setting usage pattern for" << name << "buffer";
  }

  qDebug() << name << "buffer" << buffer.bufferId() << "created";
}

void BallsCanvas::_initGLMemory() {
  using std::runtime_error;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_vao.create()) {
    QString e = QString("Could not create VAO (ID: %1)").arg(_vao.objectId());
    throw runtime_error(qPrintable(e));
  }

  QOpenGLVertexArrayObject::Binder binder(&_vao);

  _initBuffer(this, _positionBuffer, "position");
  _initBuffer(this, _normalBuffer, "normal");
  _initBuffer(this, _texCoordBuffer, "texCoord");
  _initBuffer(this, _ibo, "index");

  if (!_ibo.bind()) {
    qDebug() << "Couldn't bind index buffer";
  }
}

void BallsCanvas::_initLogger() noexcept {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_log.initialize()) {
    qCWarning(logs::gl::Feature)
      << "OpenGL debug logging unsupported on this driver";
  } else {
    _log.enableMessages();
    _log.startLogging();
  }
}

void BallsCanvas::_initShaders() noexcept {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  Q_ASSUME(
    _shader.addShaderFromSourceFile(
      QOpenGLShader::Vertex, constants::paths::DEFAULT_VERTEX));
  Q_ASSUME(
    _shader.addShaderFromSourceFile(
      QOpenGLShader::Fragment, constants::paths::DEFAULT_FRAGMENT));
  // These shaders are built into the binary via the resource system
  Q_ASSUME(_shader.link() && _shader.bind());
  // If we've gotten this far, then the code that checked for the availability
  // of shaders has already given us the green light
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
    glGetActiveUniform(
      program, i, name.size() - 1, &length, &size, &type, name.data());
    QString sname(name.data());
    Q_ASSERT(sname.size() == length);

    uniformInfo.push_back({sname, type, size});
  }

  this->uniformsDiscovered(uniformInfo);

  qCDebug(logs::uniform::Name) << "Updated uniform list";
}

void BallsCanvas::_updateUniformValues() noexcept {
  using util::types::UniformInfo;

  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  for (const UniformInfo &i : this->_uniforms->uniformInfo()) {
    QVariant u = _uniforms->property(qPrintable(i.name));
    setUniform(i, u);
  }
}

static void _initAttribute(QOpenGLFunctions* gl, QOpenGLShaderProgram& shader, QOpenGLBuffer& buffer, int index, int size, const QString& name) {
  if (!buffer.bind()) {
    qDebug() << "Failed to bind" << name << "buffer";
  }

  shader.enableAttributeArray(index);
  gl->glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, (void *)0);
  if (GLenum error = gl->glGetError()) {
    qDebug() << "glVertexAttribPointer(" << name << ") failed with" << error;
  }

  if (GLenum error = gl->glGetError()) {
    qDebug() << "_shader.enableAttributeArray(" << name << ") failed with" << error;
  }
}

void BallsCanvas::_initAttributes() noexcept {
  using namespace attribute;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  Q_ASSERT(this->gl.gl31 != nullptr);

  _attributes[POSITION] = _shader.attributeLocation(POSITION);
  _attributes[NORMAL] = _shader.attributeLocation(NORMAL);
  _attributes[TEXCOORDS] = _shader.attributeLocation(TEXCOORDS);

  gl.gl31->glBindFragDataLocation(_shader.programId(), 0, qPrintable(out::FRAGMENT));
  if (GLenum error = glGetError()) {
    qDebug() << "glBindFragDataLocation failed with" << error;
  }

#ifdef DEBUG
  int currentShader = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
  Q_ASSERT(static_cast<GLuint>(currentShader) == _shader.programId());
#endif

  QOpenGLVertexArrayObject::Binder binder(&_vao);

  int position = _attributes[attribute::POSITION];
  int normal = _attributes[attribute::NORMAL];
  int texCoords = _attributes[attribute::TEXCOORDS];

  _initAttribute(this, _shader, _positionBuffer, position, 3, "position");
  _initAttribute(this, _shader, _normalBuffer, normal, 3, "normal");
  _initAttribute(this, _shader, _texCoordBuffer, texCoords, 2, "texCoords");
}

void BallsCanvas::resizeGL(const int width, const int height) {}

void BallsCanvas::paintGL() {
  Q_ASSERT(this->_vao.isCreated());
  Q_ASSERT(this->_positionBuffer.isCreated());
  Q_ASSERT(this->_normalBuffer.isCreated());
  Q_ASSERT(this->_texCoordBuffer.isCreated());
  Q_ASSERT(this->_ibo.isCreated());

  // TODO: Isn't the context always current at this point?
  if (!context()->makeCurrent(context()->surface())) {
    qDebug() << "Failed to make context" << context() << "current";
  }

  QOpenGLVertexArrayObject::Binder binder(&_vao);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (GLenum error = glGetError()) {
    qDebug() << "Error" << error << "when clearing the frame";
  }

  _updateUniformValues();
  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, nullptr);
  if (GLenum error = glGetError()) {
    qDebug() << "Error" << error << "when rendering the mesh";
  }

  this->context()->swapBuffers(this->context()->surface());
}

template<class T>
static void fillBuffer(QOpenGLFunctions* gl, QOpenGLBuffer& buffer, const QString& name, const vector<T>& data) {
  if (!buffer.bind()) {
    qDebug() << "Could not bind" << name << "buffer" << buffer.bufferId();
  }

  buffer.allocate(data.data(), data.size() * sizeof(T));
  if (GLenum error = gl->glGetError()) {
    qDebug() << "Cannot allocate" << (data.size() * sizeof(T)) << "bytes for" << name << "buffer, error" << error;
  }
}


void BallsCanvas::setMesh(const Mesh &mesh) noexcept {
  const vector<Mesh::IndexType> &indices = mesh.indices();
  const auto& positions = mesh.positions();
  const auto& normals = mesh.normals();
  const auto& texCoords = mesh.texCoords();


  QOpenGLContext* ctx = context();
  if (!ctx->makeCurrent(ctx->surface())) {
    qDebug() << "Could not make the context" << context() << "current";
  }

  QOpenGLVertexArrayObject::Binder binder(&_vao);

  m_indexCount = indices.size();
  fillBuffer(this, _positionBuffer, "position", positions);
  _shader.setAttributeBuffer(_attributes[attribute::POSITION], GL_FLOAT, 0, 3, 0);

  fillBuffer(this, _normalBuffer, "normal", normals);
  _shader.setAttributeBuffer(_attributes[attribute::NORMAL], GL_FLOAT, 0, 3, 0);

  fillBuffer(this, _texCoordBuffer, "texCoord", texCoords);
  _shader.setAttributeArray(_attributes[attribute::TEXCOORDS], GL_FLOAT, 0, 2, 0);

  fillBuffer(this, _ibo, "index", mesh.indices());
}

void BallsCanvas::mouseMoveEvent(QMouseEvent *e) {}

void BallsCanvas::wheelEvent(QWheelEvent *) {}

void BallsCanvas::timerEvent(QTimerEvent *e) {
  update();
}

void BallsCanvas::setUniform(
  const UniformInfo &info, const QVariant &var) noexcept {
  if (!_shader.isLinked()) {
    qDebug() << "Shader is not linked";
    return;
  }

  if (_shader.programId() == 0) {
    qDebug() << "No shader loaded";
    return;
  }
  // If the shader wasn't compiled properly, the object's ID will be 0 (no
  // shader)

  Q_ASSERT(var.isValid());

  int index = _shader.uniformLocation(info.name);

  // In the switch/case below, all of the double conversions fall back to float
  // versions if the hardware doesn't support doubles.  This is done through
  // case passthrough; double -> float passthroughs are intentional!
  if (index != -1) {
    this->makeCurrent();
    if (GLenum error = glGetError()) {
      qDebug() << "Error" << error << "when trying to make context current";
    }

    switch (info.type) {
    case GL_INT: {
      Q_ASSERT(var.canConvert<int>());
      gl.gl31->glUniform1i(index, var.value<int>());
      break;
    }

    case GL_DOUBLE: {
      if (gl.gl40) {
        // If the GPU supports double types...
        Q_ASSERT(var.canConvert<double>());
        gl.gl40->glUniform1d(index, var.value<double>());
        break;
      }
    }

    // Otherwise, just treat it like a float
    case GL_FLOAT: {
      Q_ASSERT(var.canConvert<float>());
      gl.gl31->glUniform1f(index, var.value<float>());
      break;
    }

    case GL_UNSIGNED_INT: {
      Q_ASSERT(var.canConvert<unsigned int>());
      gl.gl31->glUniform1ui(index, var.value<unsigned int>());
      break;
    }

    case GL_BOOL: {
      Q_ASSERT(var.canConvert<bool>());
      gl.gl31->glUniform1i(index, var.value<bool>());
      break;
    }

    case GL_DOUBLE_VEC2: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dvec2>());
        glm::dvec2 dvec2 = var.value<glm::dvec2>();
        gl.gl40->glUniform2d(index, dvec2.x, dvec2.y);
        break;
      }
    }

    case GL_FLOAT_VEC2: {
      Q_ASSERT(var.canConvert<glm::vec2>());
      glm::vec2 vec2 = var.value<glm::vec2>();
      gl.gl31->glUniform2f(index, vec2.x, vec2.y);
      break;
    }

    case GL_INT_VEC2: {
      Q_ASSERT(var.canConvert<glm::ivec2>());
      glm::ivec2 ivec2 = var.value<glm::ivec2>();
      gl.gl31->glUniform2i(index, ivec2.x, ivec2.y);
      break;
    }

    case GL_UNSIGNED_INT_VEC2: {
      Q_ASSERT(var.canConvert<glm::uvec2>());
      glm::uvec2 uvec2 = var.value<glm::uvec2>();
      gl.gl31->glUniform2ui(index, uvec2.x, uvec2.y);
      break;
    }

    case GL_BOOL_VEC2: {
      Q_ASSERT(var.canConvert<glm::bvec2>());
      glm::bvec2 bvec2 = var.value<glm::bvec2>();
      gl.gl31->glUniform2i(index, bvec2.x, bvec2.y);
      break;
    }

    case GL_DOUBLE_VEC3: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dvec3>());
        glm::dvec3 dvec3 = var.value<glm::dvec3>();
        gl.gl40->glUniform3d(index, dvec3.x, dvec3.y, dvec3.z);
        break;
      }
      // Otherwise, case to GL_FLOAT_VEC3
    }

    case GL_FLOAT_VEC3: {
      Q_ASSERT(var.canConvert<glm::vec3>());
      glm::vec3 vec3 = var.value<glm::vec3>();
      gl.gl31->glUniform3f(index, vec3.x, vec3.y, vec3.z);
      break;
    }

    case GL_INT_VEC3: {
      Q_ASSERT(var.canConvert<glm::ivec3>());
      glm::ivec3 ivec3 = var.value<glm::ivec3>();
      gl.gl31->glUniform3i(index, ivec3.x, ivec3.y, ivec3.z);
      break;
    }

    case GL_UNSIGNED_INT_VEC3: {
      Q_ASSERT(var.canConvert<glm::uvec3>());
      glm::uvec3 uvec3 = var.value<glm::uvec3>();
      gl.gl31->glUniform3ui(index, uvec3.x, uvec3.y, uvec3.z);
      break;
    }

    case GL_BOOL_VEC3: {
      Q_ASSERT(var.canConvert<glm::bvec3>());
      glm::bvec3 bvec3 = var.value<glm::bvec3>();
      gl.gl31->glUniform3i(index, bvec3.x, bvec3.y, bvec3.z);
      break;
    }

    case GL_DOUBLE_VEC4: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dvec4>());
        glm::dvec4 dvec4 = var.value<glm::dvec4>();
        gl.gl40->glUniform4d(index, dvec4.x, dvec4.y, dvec4.z, dvec4.w);
        break;
      }
    }

    case GL_FLOAT_VEC4: {
      Q_ASSERT(var.canConvert<glm::vec4>());
      glm::vec4 vec4 = var.value<glm::vec4>();
      gl.gl31->glUniform4f(index, vec4.x, vec4.y, vec4.z, vec4.w);
      break;
    }

    case GL_INT_VEC4: {
      Q_ASSERT(var.canConvert<glm::ivec4>());
      glm::ivec4 ivec4 = var.value<glm::ivec4>();
      gl.gl31->glUniform4i(index, ivec4.x, ivec4.y, ivec4.z, ivec4.w);
      break;
    }

    case GL_UNSIGNED_INT_VEC4: {
      Q_ASSERT(var.canConvert<glm::uvec4>());
      glm::uvec4 uvec4 = var.value<glm::uvec4>();
      gl.gl31->glUniform4ui(index, uvec4.x, uvec4.y, uvec4.z, uvec4.w);
      break;
    }

    case GL_BOOL_VEC4: {
      Q_ASSERT(var.canConvert<glm::bvec4>());
      glm::bvec4 bvec4 = var.value<glm::bvec4>();
      gl.gl31->glUniform4i(index, bvec4.x, bvec4.y, bvec4.z, bvec4.w);
      break;
    }

    case GL_DOUBLE_MAT2: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat2>());
        glm::dmat2 dmat2 = var.value<glm::dmat2>();
        gl.gl40->glUniformMatrix2dv(index, 1, false, glm::value_ptr(dmat2));
        break;
      }
    }

    case GL_FLOAT_MAT2: {
      Q_ASSERT(var.canConvert<glm::mat2>());
      glm::mat2 mat2 = var.value<glm::mat2>();
      gl.gl31->glUniformMatrix2fv(index, 1, false, glm::value_ptr(mat2));
      break;
    }

    case GL_DOUBLE_MAT2x3: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat2x3>());
        glm::dmat2x3 dmat2x3 = var.value<glm::dmat2x3>();
        gl.gl40->glUniformMatrix2x3dv(index, 1, false, glm::value_ptr(dmat2x3));
        break;
      }
    }

    case GL_FLOAT_MAT2x3: {
      Q_ASSERT(var.canConvert<glm::mat2x3>());
      glm::mat2x3 mat2x3 = var.value<glm::mat2x3>();
      gl.gl31->glUniformMatrix2x3fv(index, 1, false, glm::value_ptr(mat2x3));
      break;
    }

    case GL_DOUBLE_MAT2x4: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat2x4>());
        glm::dmat2x4 dmat2x4 = var.value<glm::dmat2x4>();
        gl.gl40->glUniformMatrix2x4dv(index, 1, false, glm::value_ptr(dmat2x4));
        break;
      }
    }

    case GL_FLOAT_MAT2x4: {
      Q_ASSERT(var.canConvert<glm::mat2x4>());
      glm::mat2x4 mat2x4 = var.value<glm::mat2x4>();
      gl.gl31->glUniformMatrix2x4fv(index, 1, false, glm::value_ptr(mat2x4));
      break;
    }

    case GL_DOUBLE_MAT3x2: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat3x2>());
        glm::dmat3x2 dmat3x2 = var.value<glm::dmat3x2>();
        gl.gl40->glUniformMatrix3x2dv(index, 1, false, glm::value_ptr(dmat3x2));
        break;
      }
    }

    case GL_FLOAT_MAT3x2: {
      Q_ASSERT(var.canConvert<glm::mat3x2>());
      glm::mat3x2 mat3x2 = var.value<glm::mat3x2>();
      gl.gl31->glUniformMatrix3x2fv(index, 1, false, glm::value_ptr(mat3x2));
      break;
    }

    case GL_DOUBLE_MAT3: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat3>());
        glm::dmat3 dmat3 = var.value<glm::dmat3>();
        gl.gl40->glUniformMatrix3dv(index, 1, false, glm::value_ptr(dmat3));
        break;
      }
    }

    case GL_FLOAT_MAT3: {
      Q_ASSERT(var.canConvert<glm::mat3>());
      glm::mat3 mat3 = var.value<glm::mat3>();
      gl.gl31->glUniformMatrix3fv(index, 1, false, glm::value_ptr(mat3));
      break;
    }

    case GL_DOUBLE_MAT3x4: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat3x4>());
        glm::dmat3x4 dmat3x4 = var.value<glm::dmat3x4>();
        gl.gl40->glUniformMatrix3x4dv(index, 1, false, glm::value_ptr(dmat3x4));
        break;
      }
    }

    case GL_FLOAT_MAT3x4: {
      Q_ASSERT(var.canConvert<glm::mat3x4>());
      glm::mat3x4 mat3x4 = var.value<glm::mat3x4>();
      gl.gl31->glUniformMatrix3x4fv(index, 1, false, glm::value_ptr(mat3x4));
      break;
    }

    case GL_DOUBLE_MAT4x2: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat4x2>());
        glm::dmat4x2 dmat4x2 = var.value<glm::dmat4x2>();
        gl.gl40->glUniformMatrix4x2dv(index, 1, false, glm::value_ptr(dmat4x2));
        break;
      }
    }

    case GL_FLOAT_MAT4x2: {
      Q_ASSERT(var.canConvert<glm::mat4x2>());
      glm::mat4x2 mat4x2 = var.value<glm::mat4x2>();
      gl.gl31->glUniformMatrix4x2fv(index, 1, false, glm::value_ptr(mat4x2));
      break;
    }

    case GL_DOUBLE_MAT4x3: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat4x3>());
        glm::dmat4x3 dmat4x3 = var.value<glm::dmat4x3>();
        gl.gl40->glUniformMatrix4x3dv(index, 1, false, glm::value_ptr(dmat4x3));
        break;
      }
    }

    case GL_FLOAT_MAT4x3: {
      Q_ASSERT(var.canConvert<glm::mat4x3>());
      glm::mat4x3 mat4x3 = var.value<glm::mat4x3>();
      gl.gl31->glUniformMatrix4x3fv(index, 1, false, glm::value_ptr(mat4x3));
      break;
    }

    case GL_DOUBLE_MAT4: {
      if (gl.gl40) {
        Q_ASSERT(var.canConvert<glm::dmat4>());
        glm::dmat4 dmat4 = var.value<glm::dmat4>();
        gl.gl40->glUniformMatrix4dv(index, 1, false, glm::value_ptr(dmat4));
        break;
      }
    }

    case GL_FLOAT_MAT4: {
      Q_ASSERT(var.canConvert<glm::mat4>());
      glm::mat4 mat4 = var.value<glm::mat4>();
      gl.gl31->glUniformMatrix4fv(index, 1, false, glm::value_ptr(mat4));
      break;
    }

    case GL_SAMPLER_2D: {
      break;
      // TODO: Support
    }

    default:
      qCWarning(logs::uniform::Type) << "Unsupported GLSL type"
                                     << util::resolveGLType(info.type);
    }

    if (GLenum error = glGetError()) {
      qDebug() << "Error" << error << "when trying to set uniform" << info.name;
    }
  } else {
    qCWarning(logs::uniform::Name) << "Attempted to set non-existing uniform"
                                   << info.name << "to" << var;
  }
}

void BallsCanvas::resetCamera() noexcept {
  _uniforms->resetModelView();

  qCDebug(logs::uniform::Env) << "Reset camera and model rotation to default";
}

bool BallsCanvas::updateShaders(
  const QString &vertex,
  const QString &geometry,
  const QString &fragment) noexcept {

  Q_UNUSED(geometry);
  using namespace balls::shader;

  qDebug() << "In BallsCanvas::updateShaders";

  this->makeCurrent();
  if (GLenum error = glGetError()) {
    qDebug() << "Could not make context current";
  }

  this->_shader.release();
  if (GLenum error = glGetError()) {
    qDebug() << "_shader.release() failed";
  }

  this->_shader.removeAllShaders();
  if (GLenum error = glGetError()) {
    qDebug() << "_shader.removeAllShaders() failed";
  }


  bool vert = _shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
  bool frag =
    _shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment);
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
