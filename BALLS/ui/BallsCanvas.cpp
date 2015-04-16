#include "precompiled.hpp"
#include "ui/BallsCanvas.hpp"

#include <exception>
#include <sstream>

#include <QtGui/QCursor>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
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
#include <QtGui/QWheelEvent>
#include <QtWidgets/QOpenGLWidget>

#include "Constants.hpp"
#include "mesh/Mesh.hpp"
#include "mesh/MeshGenerator.hpp"
#include "config/Settings.hpp"
#include "ui/BallsWindow.hpp"

namespace balls {

using std::ostringstream;
using std::pair;
using std::runtime_error;
using std::string;
using std::vector;
using namespace balls::config;
using namespace balls::shader;

Q_CONSTEXPR QSurfaceFormat::FormatOption FORMAT_OPTION =
  #ifdef DEBUG
  QSurfaceFormat::DebugContext;
  #else
  QSurfaceFormat::StereoBuffers;
  #endif
Q_CONSTEXPR QSurfaceFormat::OpenGLContextProfile PROFILE =
  QSurfaceFormat::CoreProfile;
Q_CONSTEXPR QSurfaceFormat::RenderableType RENDER_TYPE = QSurfaceFormat::OpenGL;
Q_CONSTEXPR QSurfaceFormat::SwapBehavior SWAP_TYPE =
  QSurfaceFormat::DefaultSwapBehavior;
Q_CONSTEXPR int SAMPLES = 4;
Q_CONSTEXPR int DEPTH_BUFFER_BITS = 8;

Q_CONSTEXPR QSurfaceFormat::FormatOptions
FLAGS(FORMAT_OPTION | RENDER_TYPE | PROFILE | SWAP_TYPE);

Q_CONSTEXPR QOpenGLBuffer::UsagePattern USAGE_PATTERN =
  QOpenGLBuffer::StaticDraw;

Q_CONSTEXPR float DEFAULT_ZOOM = -8;
Q_CONSTEXPR float ZOOM_INTERVAL = 1;

const QColor DEFAULT_COLOR = QColor(255, 0, 0);

BallsCanvas::BallsCanvas(QWidget* parent)
  : QOpenGLWidget(parent),
    _log(parent),
    _vbo(QOpenGLBuffer::VertexBuffer),
    _ibo(QOpenGLBuffer::IndexBuffer),
    _gl30(nullptr),
    _gl31(nullptr),
    _gl32(nullptr),
    _gl33(nullptr),
    _gl40(nullptr),
    _gl41(nullptr),
    _gl42(nullptr),
    _gl43(nullptr) {
  QSurfaceFormat format(FLAGS);
  format.setSamples(SAMPLES);
  format.setDepthBufferSize(DEPTH_BUFFER_BITS);
  this->setFormat(format);
  this->_view.translate(0, 0, DEFAULT_ZOOM);
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
  this->_shader.removeAllShaders();
}

void BallsCanvas::initializeGL() {
  this->initializeOpenGLFunctions();
  this->_initSettings();
  this->_initUniforms();
  this->_initGLPointers();
  this->_initGLMemory();
  this->_initLogger();
  this->_initShaders();
  this->_initAttributeLocations();
  this->_initAttributes();
  this->updateUniformInfo();
  this->finishedInitializing();
}

void BallsCanvas::_initSettings() {
  this->_settings[SettingKey::WireFrame] = {false};
  this->_settings[SettingKey::DepthTestEnabled] = {true, true};
  this->_settings[SettingKey::FaceCullingEnabled] = {true, true};
  this->_settings[SettingKey::Dithering] = {true, true};
}

void BallsCanvas::_initGLPointers() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  this->_initGLFunction<3, 0, QOpenGLFunctions_3_0>(&(this->_gl30));
  this->_initGLFunction<3, 1, QOpenGLFunctions_3_1>(&(this->_gl31));
  this->_initGLFunction<3, 2, QOpenGLFunctions_3_2_Core>(&(this->_gl32));
  this->_initGLFunction<3, 3, QOpenGLFunctions_3_3_Core>(&(this->_gl33));
  this->_initGLFunction<4, 0, QOpenGLFunctions_4_0_Core>(&(this->_gl40));
  this->_initGLFunction<4, 1, QOpenGLFunctions_4_1_Core>(&(this->_gl41));
  this->_initGLFunction<4, 2, QOpenGLFunctions_4_2_Core>(&(this->_gl42));
  this->_initGLFunction<4, 3, QOpenGLFunctions_4_3_Core>(&(this->_gl43));
  QSurfaceFormat format = context()->format();
  this->_glmajor = format.majorVersion();
  this->_glminor = format.minorVersion();
  this->geometryShadersSupported(this->_gl32);

  if (!this->_gl32) {
    qWarning() << "Warning: Geometry shaders not supported!";
  }

  if (!QOpenGLShaderProgram::hasOpenGLShaderPrograms()) {
    this->fatalGraphicsError(
      "OpenGL Error: Hardware too old",
      "Shaders are not available on this graphics hardware, but BALLS needs"
      " them to run.",
      Constants::SHADER_PROGRAMS_UNAVAILABLE);
  }
  else if (!(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex) &&
             QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment))) {
    this->fatalGraphicsError(
      "OpenGL Error: Required features not available",
      "Vertex and fragment shaders must both be available, but they're not.",
      Constants::SHADER_TYPES_UNAVAILABLE);
  }
  else if (!this->hasOpenGLFeature(OpenGLFeature::Buffers)) {
    this->fatalGraphicsError(
      "OpenGL Error: Required features not available",
      "Vertex and index buffer objects must be available, but they're not",
      Constants::BUFFERS_UNAVAILABLE);
  }

  if (!this->_gl30) {
    ostringstream e;
    e << "OpenGL 3.0 or higher is required to use BALLS, but only " << _glmajor
      << '.' << _glminor << " is available.";
    qFatal(e.str().c_str());
    this->fatalGraphicsError(
      "OpenGL version is too old", e.str().c_str(), Constants::NEED_BETTER_OPENGL);
  }
}

void BallsCanvas::_initGLMemory() {
  using std::runtime_error;
  using std::ostringstream;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_vao.create()) {
    ostringstream e;
    e << "Could not create VAO (ID: " << _vao.objectId() << ')';
    throw runtime_error(e.str());
  }

  _vao.bind();
  // If buffers aren't available, we wouldn't even get this far
  Q_ASSUME(_vbo.create() && _vbo.bind());
  _vbo.setUsagePattern(USAGE_PATTERN);
  #ifdef DEBUG
  qDebug() << "VBO" << _vbo.bufferId() << "created and bound";
  #endif
  Q_ASSUME(_ibo.create() && _ibo.bind());
  _ibo.setUsagePattern(USAGE_PATTERN);
  #ifdef DEBUG
  qDebug() << "IBO" << _ibo.bufferId() << "created and bound";
  #endif
}

void BallsCanvas::_initLogger() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_log.initialize()) {
    qWarning() << "GL_KHR_debug extension not supported, debug logging will "
               "not be available";
  }
  else {
    _log.enableMessages();
    _log.startLogging();
  }
}

void BallsCanvas::_initShaders() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  Q_ASSERT(this->hasOpenGLFeature(OpenGLFeature::Shaders));
  Q_ASSERT(this->hasOpenGLFeature(OpenGLFeature::Buffers));
  Q_ASSERT(QOpenGLShaderProgram::hasOpenGLShaderPrograms(context()));
  Q_ASSERT(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex, context()));
  Q_ASSERT(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment, context()));
  Q_ASSUME(_shader.addShaderFromSourceFile(
             QOpenGLShader::Vertex, Constants::DEFAULT_VERTEX_PATH));
  Q_ASSUME(_shader.addShaderFromSourceFile(
             QOpenGLShader::Fragment, Constants::DEFAULT_FRAGMENT_PATH));
  // These shaders are built into the binary via the resource system
  Q_ASSUME(_shader.link() && _shader.bind());
  // If we've gotten this far, then the code that checked for the availability
  // of shaders has already given us the green light
}

void BallsCanvas::_initAttributeLocations() {
  using namespace attribute;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  Q_ASSERT(this->_gl30 != nullptr);
  Q_ASSERT(this->hasOpenGLFeature(OpenGLFeature::Shaders));
  Q_ASSERT(this->hasOpenGLFeature(OpenGLFeature::Buffers));
  Q_ASSERT(QOpenGLShaderProgram::hasOpenGLShaderPrograms(context()));
  Q_ASSERT(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex, context()));
  Q_ASSERT(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment, context()));
  #ifdef DEBUG
  int currentShader = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
  Q_ASSERT(static_cast<GLuint>(currentShader) == _shader.programId());
  #endif
  _attributes[POSITION] = _shader.attributeLocation(POSITION.toUtf8().data());
  _attributes[NORMAL] = _shader.attributeLocation(NORMAL.toUtf8().data());
  this->_gl30->glBindFragDataLocation(
    _shader.programId(), 0, out::FRAGMENT.toUtf8().data());
}

void BallsCanvas::updateUniformInfo() {
  using std::array;
  using std::pair;
  using shader::UniformFunction;
  using shader::UniformName;

  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  array<GLchar, 128> name;
  GLuint program = _shader.programId();

  for (const pair<UniformName, UniformInfo>& u : this->_builtInUniforms) {
    // For each built-in uniform...
    int index = _shader.uniformLocation(u.first.toUtf8().data());
    UniformInfo& info = _builtInUniforms[u.first];

    if (index != -1) {
      // If this uniform is defined...
      info.index = static_cast<GLuint>(index);
      glGetActiveUniform(
        program,
        index,
        name.size(),
        &(info.length),
        &(info.size),
        &(info.type),
        name.data()
      );
    }
    else {
      info.index = DEFAULT_INDEX;
      info.length = DEFAULT_LENGTH;
      info.size = DEFAULT_SIZE;
      info.type = DEFAULT_TYPE;
    }
  }
}

void BallsCanvas::_updateUniformList() Q_DECL_NOEXCEPT {
  using std::array;
  using std::pair;
  using shader::UniformFunction;
  using shader::UniformName;

  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  array<GLchar, 128> name;
  GLuint program = _shader.programId();

  GLsizei length = 0;
  GLint size = 0;
  GLenum type = 0;
  int activeUniforms = 0;
  glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);

  UniformMap custom;
  UniformMap changed;
  QStringList removed;

  for (const auto& u : this->_customUniforms) {
    removed.push_back(u.first);
  }

  for (int i = 0; i < activeUniforms; ++i) {
    glGetActiveUniform(program, i, name.size(), &length, &size, &type, name.data());
    QString sname(name.data());

    Q_ASSERT(sname.size() == length);
    int has = _builtInUniforms.count(sname);

    if (has) {
      // If this is one of our built-in uniforms...
    }
    else {
      // This is a custom uniform, then
      if (_customUniforms.count(sname) == 0 || _customUniforms[sname].type != type) {
        // If we didn't have this uniform before...
        custom[sname] = type;
        // Get it ready to report it later (and unmark it for deletion)
        UniformInfo& info = (this->_customUniforms[sname] = UniformInfo());
        info.index = i;
        info.length = length;
        info.size = size;
        info.type = type;
        info.whenToUpdate = UpdateFrequency::OnChange;
      }
      else {
        removed.removeAll(sname);
      }
    }
  }

  if (removed.size() > 0) {
    // If any of our uniforms were removed...
    for (const QString& s : removed) {
      this->_customUniforms.erase(s);
    }

    this->reportRemovedUniforms(removed);
  }

  if (changed.size() > 0) {
    // If any of our uniforms changed types...
    this->reportChangedUniforms(changed);
  }

  if (custom.size() > 0) {
    // If we have any new uniforms...
    this->reportNewUniforms(custom);
  }


}

void BallsCanvas::_updateRegularUniformValues() {
  using std::array;
  using std::pair;
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  for (const pair<UniformName, UniformInfo>& u : _builtInUniforms) {
    if (u.second.type != DEFAULT_TYPE
        && u.second.whenToUpdate == UpdateFrequency::EveryFrame) {
      QVariant var = u.second.function(u.second.type);
      changeUniform(u.second, var);
    }
  }
}

void BallsCanvas::_initAttributes() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  Q_ASSERT(this->_gl30 != nullptr);
  Q_ASSERT(this->hasOpenGLFeature(OpenGLFeature::Shaders));
  Q_ASSERT(this->hasOpenGLFeature(OpenGLFeature::Buffers));
  Q_ASSERT(QOpenGLShaderProgram::hasOpenGLShaderPrograms(context()));
  Q_ASSERT(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex, context()));
  Q_ASSERT(QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment, context()));
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

void BallsCanvas::resizeGL(const int w, const int h) {
  this->_projection.setToIdentity();
  this->_projection.perspective(45, float(w) / float(h ? h : 1), .01, 100);
  this->update();
  // this->projection.ortho(-width / ORTHO_SCALE, width / ORTHO_SCALE,
  //-height / ORTHO_SCALE, height / ORTHO_SCALE, 0, 1);
}

void BallsCanvas::paintGL() {
  Q_ASSERT(this->_vao.isCreated());
  Q_ASSERT(this->_vbo.isCreated());
  Q_ASSERT(this->_ibo.isCreated());

  this->_updateGLSetting<GL_DEPTH_TEST>(SettingKey::DepthTestEnabled);
  this->_updateGLSetting<GL_CULL_FACE>(SettingKey::FaceCullingEnabled);
  this->_updateGLSetting<GL_DITHER>(SettingKey::Dithering);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _combined = this->_projection * this->_view * this->_model;
  this->_updateRegularUniformValues();
  glDrawElements(_settings[SettingKey::WireFrame].value.toBool() ? GL_LINE_STRIP
                 : GL_TRIANGLES,
                 _mesh.indices().size(),
                 GL_UNSIGNED_SHORT,
                 nullptr);
}

void BallsCanvas::wheelEvent(QWheelEvent* e) {
  int delta = e->angleDelta().y();
  this->_view.translate(0, 0, (delta > 0) ? ZOOM_INTERVAL : -ZOOM_INTERVAL);
  this->update();
}

void BallsCanvas::mouseMoveEvent(QMouseEvent* e) {
  if (e->buttons() & Qt::LeftButton) {
    QPointF delta = e->localPos() - this->_lastMousePos;
    this->_model.rotate(delta.x(), 0, 1, 0);
    this->_model.rotate(delta.y(), 1, 0, 0);
  }

  this->_lastMousePos = e->localPos();
  this->update();
}

void BallsCanvas::mousePressEvent(QMouseEvent*) {}

void BallsCanvas::mouseReleaseEvent(QMouseEvent*) {}

void BallsCanvas::keyPressEvent(QKeyEvent*) {}

void BallsCanvas::keyReleaseEvent(QKeyEvent*) {}

void BallsCanvas::setMesh(mesh::MeshGenerator* generator) Q_DECL_NOEXCEPT {
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

  this->update();
}

void BallsCanvas::setOption(const bool value) Q_DECL_NOEXCEPT {
  QObject* send = sender();
  QVariant name = send->property(Constants::OPTION_PROPERTY);

  Q_ASSERT(send != nullptr); // Must be called as a slot!
  Q_ASSERT(name.isValid()&&  name.type() == QVariant::String);

  this->_settings[name.toString()] = Setting(value, true);

  #ifdef DEBUG
  qDebug() << "Set" << name.toString() << "to" << value;
  #endif

  this->update();
}

void BallsCanvas::setOption(const int value) Q_DECL_NOEXCEPT {
  QObject* send = sender();
  QVariant name = send->property(Constants::OPTION_PROPERTY);

  Q_ASSERT(send != nullptr && "Must be called as a slot!");
  Q_ASSERT(name.isValid() && name.type() == QVariant::String);

  this->_settings[name.toString()] = Setting(value, true);

  #ifdef DEBUG
  qDebug() << "Set" << name.toString() << "to" << value;
  #endif

  this->update();
}

void BallsCanvas::changeUniform(const UniformInfo& info, const QVariant& var) {
  Q_ASSERT(info.index != -1);
  Q_ASSERT(info.length > 0);
  Q_ASSERT(var.isValid() && !var.isNull());

  bool converted = true;

  switch (info.type) {
  case GL_INT:
    _shader.setUniformValue(info.index, var.toInt(&converted));
    break;

  case GL_DOUBLE:
    if (this->_gl40) {
      this->_gl40->glUniform1d(info.index, var.toDouble(&converted));
      break;
    }

  case GL_FLOAT:
    _shader.setUniformValue(info.index, var.toFloat(&converted));
    break;

  case GL_UNSIGNED_INT:
    _shader.setUniformValue(info.index, var.toUInt(&converted));
    break;

  case GL_INT_VEC2:
  case GL_UNSIGNED_INT_VEC2:
  case GL_BOOL_VEC2:
  case GL_DOUBLE_VEC2:
  case GL_FLOAT_VEC2: {
    converted = var.canConvert(QVariant::Vector2D);
    _shader.setUniformValue(info.index, var.value<QVector2D>());
    break;
  }

  case GL_INT_VEC3:
  case GL_UNSIGNED_INT_VEC3:
  case GL_BOOL_VEC3:
  case GL_DOUBLE_VEC3:
  case GL_FLOAT_VEC3: {
    converted = var.canConvert(QVariant::Vector3D);
    _shader.setUniformValue(info.index, var.value<QVector3D>());
    break;
  }

  case GL_INT_VEC4:
  case GL_UNSIGNED_INT_VEC4:
  case GL_BOOL_VEC4:
  case GL_DOUBLE_VEC4:
  case GL_FLOAT_VEC4: {
    converted = var.canConvert(QVariant::Vector4D);
    _shader.setUniformValue(info.index, var.value<QVector4D>());
    break;
  }

  case GL_DOUBLE_MAT2:
  case GL_FLOAT_MAT2: {
    QMatrix2x2 m = var.value<QMatrix4x4>().toGenericMatrix<2, 2>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT2x3:
  case GL_FLOAT_MAT2x3: {
    QMatrix2x3 m = var.value<QMatrix4x4>().toGenericMatrix<2, 3>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT2x4:
  case GL_FLOAT_MAT2x4: {
    QMatrix2x4 m = var.value<QMatrix4x4>().toGenericMatrix<2, 4>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT3x2:
  case GL_FLOAT_MAT3x2: {
    QMatrix3x2 m = var.value<QMatrix4x4>().toGenericMatrix<3, 2>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT3:
  case GL_FLOAT_MAT3: {
    QMatrix3x3 m = var.value<QMatrix4x4>().toGenericMatrix<3, 3>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT3x4:
  case GL_FLOAT_MAT3x4: {
    QMatrix3x4 m = var.value<QMatrix4x4>().toGenericMatrix<3, 4>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT4x2:
  case GL_FLOAT_MAT4x2: {
    QMatrix4x2 m = var.value<QMatrix4x4>().toGenericMatrix<4, 2>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT4x3:
  case GL_FLOAT_MAT4x3: {
    QMatrix4x3 m = var.value<QMatrix4x4>().toGenericMatrix<4, 3>();
    _shader.setUniformValue(info.index, m);
  }

  case GL_DOUBLE_MAT4:
  case GL_FLOAT_MAT4:
    _shader.setUniformValue(info.index, var.value<QMatrix4x4>());
    break;

  default:
    #ifdef DEBUG
    qDebug() << "Unsupported GLSL type" << info.type;
    #endif
  }

  Q_ASSERT(converted);
}

void BallsCanvas::changeCustomUniform(const QString& name,
                                      const QVariant& var) {
  Q_ASSERT(_customUniforms.count(name) == 1);
  UniformInfo& info = this->_customUniforms[name];

  this->changeUniform(info, var);
  #ifdef DEBUG
  qDebug() << "Changed uniform" << name << "to" << var;
  #endif
}

void BallsCanvas::resetCamera() Q_DECL_NOEXCEPT {
  // TODO: Make use of the w in homogenous vector coords for zoom
  this->_model.setToIdentity();
  this->_view.setToIdentity();
  this->_view.translate(0, 0, DEFAULT_ZOOM);

  #ifdef DEBUG
  qDebug() << "Reset camera and model rotation to default";
  #endif
  this->update();
}

bool BallsCanvas::updateShaders(const QString& vertex,
                                const QString& geometry,
                                const QString& fragment) Q_DECL_NOEXCEPT {

  Q_UNUSED(geometry);
  using namespace balls::shader;
  #ifdef DEBUG
  qDebug() << "Updating shaders...";
  #endif

  this->makeCurrent();
  this->_shader.release();
  this->_shader.removeAllShaders();

  bool vert = _shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
  bool frag = _shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment);
  bool link = _shader.link();
  bool bind = _shader.bind();
  bool result = vert && frag && link;

  #ifdef DEBUG

  if (!vert) {
    qDebug() << "Couldn't compile vertex shader";
  }

  if (!frag) {
    qDebug() << "Couldn't compile fragment shader";
  }

  if (!link) {
    qDebug() << "Couldn't link shaders together";
  }

  if (!bind) {
    qDebug() << "Couldn't bind shader program to context";
  }

  if (!result) {
    qDebug() << _shader.log();
  }

  #endif

  if (result) {
    this->_updateUniformList();
  }

  return result;
}
}
