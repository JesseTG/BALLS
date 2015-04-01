#include "ui/BallsCanvas.hpp"

#include <exception>
#include <sstream>
#include <vector>

#include <QColor>
#include <QCursor>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_3_1>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLWidget>
#include <QPointF>
#include <QSurfaceFormat>
#include <QString>
#include <QWheelEvent>
#include <QVector>

#include "mesh/Mesh.hpp"
#include "mesh/MeshGenerator.hpp"
#include "config/Settings.hpp"

namespace balls {

using std::string;
using std::vector;
using namespace balls::config;
using namespace balls::shader;

constexpr QSurfaceFormat::FormatOption FORMAT_OPTION =
#ifdef DEBUG
 QSurfaceFormat::DebugContext;
#else
 QSurfaceFormat::StereoBuffers;
#endif
constexpr QSurfaceFormat::OpenGLContextProfile PROFILE = QSurfaceFormat::CoreProfile;
constexpr QSurfaceFormat::RenderableType RENDER_TYPE = QSurfaceFormat::OpenGL;
constexpr QSurfaceFormat::SwapBehavior SWAP_TYPE = QSurfaceFormat::DefaultSwapBehavior;
constexpr int SAMPLES = 4;
constexpr int DEPTH_BUFFER_BITS = 8;

constexpr QSurfaceFormat::FormatOptions
 FLAGS(FORMAT_OPTION | RENDER_TYPE | PROFILE | SWAP_TYPE);

constexpr QOpenGLBuffer::UsagePattern USAGE_PATTERN = QOpenGLBuffer::StaticDraw;

constexpr float ORTHO_SCALE = 10;
constexpr float DEFAULT_ZOOM = -8;
constexpr float ZOOM_INTERVAL = 1;

const QColor DEFAULT_COLOR = QColor(255, 0, 0);
const QColor DEFAULT_NORMAL_COLOR = QColor(0, 255, 0);

const char* FRAGMENT = "fragment";

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
  this->_initGLPointers();
  this->_initGLMemory();
  this->_initLogger();
  this->_initShaders();
  this->_queryInputLocations();
  this->_initAttributes();

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

  this->geometryShadersSupported(this->_gl32);
  if (!this->_gl32) {
    qWarning() << "Warning: Geometry shaders not supported!";
  } else if (!this->_gl30) {
    qFatal("FATAL: OpenGL 3.0 or higher is required to use BALLS!");
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

  if (!_vbo.create()) {
    ostringstream e;
    e << "Could not create VBO (ID: " << _vbo.bufferId() << ')';
    throw runtime_error(e.str());
  }

  if (!_vbo.bind()) {
    ostringstream e;
    e << "Could not bind VBO (ID: " << _vbo.bufferId() << ')';
    throw runtime_error(e.str());
  }

  _vbo.setUsagePattern(USAGE_PATTERN);

  if (!_ibo.create()) {
    ostringstream e;
    e << "Could not create IBO (ID: " << _ibo.bufferId() << ')';
    throw runtime_error(e.str());
  }

  if (!_ibo.bind()) {
    ostringstream e;
    e << "Could not bind IBO (ID: " << _ibo.bufferId() << ')';
    throw runtime_error(e.str());
  }

  _ibo.setUsagePattern(USAGE_PATTERN);
}

void BallsCanvas::_initLogger() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

  if (!_log.initialize()) {
    qWarning() << "GL_KHR_debug extension not supported, debug logging will "
                  "not be available\n";
  } else {
    _log.enableMessages();
    _log.startLogging();
  }
}

void BallsCanvas::_initShaders() {
  using std::runtime_error;
  using std::ostringstream;

  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());
  Q_ASSERT(this->_gl30 != nullptr);

  _shader.addShaderFromSourceFile(
   QOpenGLShader::Vertex, ":/shader/default.vert");
  _shader.addShaderFromSourceFile(
   QOpenGLShader::Fragment, ":/shader/default.frag");

  if (!_shader.link()) {
    ostringstream e;
    e << "Could not link shader program (ID: " << _shader.programId() << ')';
    throw runtime_error(e.str());
  }
  if (!_shader.bind()) {
    ostringstream e;
    e << "Could not bind shader program (ID: " << _shader.programId() << ')';
    throw runtime_error(e.str());
  }
}

void BallsCanvas::_queryInputLocations() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

#ifdef DEBUG
  int currentShader = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
  Q_ASSERT(currentShader == _shader.programId());
#endif

  _attributes[attribute::POSITION] = _shader.attributeLocation(attribute::POSITION);
  _attributes[attribute::NORMAL] = _shader.attributeLocation(attribute::NORMAL);

  _uniforms[uniform::MATRIX] = _shader.uniformLocation(uniform::MATRIX);
  _uniforms[uniform::COLOR] = _shader.uniformLocation(uniform::COLOR);

  this->_gl30->glBindFragDataLocation(_shader.programId(), 0, out::FRAGMENT);
}

void BallsCanvas::_initAttributes() {
  Q_ASSERT(this->isValid());
  Q_ASSERT(this->context() == QOpenGLContext::currentContext());

#ifdef DEBUG
  int currentShader = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);
  Q_ASSERT(currentShader == _shader.programId());
#endif

  int position = _attributes[attribute::POSITION];
  int normal = _attributes[attribute::NORMAL];

  glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
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

  this->_updateGLSetting<SettingKey::DepthTestEnabled, GL_DEPTH_TEST>();
  this->_updateGLSetting<SettingKey::FaceCullingEnabled, GL_CULL_FACE>();
  this->_updateGLSetting<SettingKey::Dithering, GL_DITHER>();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _combined = this->_projection * this->_view * this->_model;
  _shader.setUniformValue(_uniforms[uniform::MATRIX], _combined);
  _shader.setUniformValue(_uniforms[uniform::COLOR], DEFAULT_COLOR);
  glDrawElements(
   _settings[SettingKey::WireFrame].value.toBool() ? GL_LINE_LOOP : GL_TRIANGLES,
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

void BallsCanvas::setMesh(mesh::MeshGenerator* generator) noexcept {
  using mesh::Mesh;
  Q_ASSERT(generator);

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

void BallsCanvas::setBackfaceCulling(const bool enabled) noexcept {
  this->_settings[SettingKey::FaceCullingEnabled] = {enabled, true};

#ifdef DEBUG
  qDebug() << (enabled ? "Enabled" : "Disabled") << "backface culling";
#endif

  this->update();
}

void BallsCanvas::setDepthTesting(const bool enabled) noexcept {
  this->_settings[SettingKey::DepthTestEnabled] = {enabled, true};

#ifdef DEBUG
  qDebug() << (enabled ? "Enabled" : "Disabled") << "depth-testing";
#endif

  this->update();
}

void BallsCanvas::setWireframe(const bool enabled) noexcept {
  this->_settings[SettingKey::WireFrame] = {enabled, true};

#ifdef DEBUG
  qDebug() << (enabled ? "Enabled" : "Disabled") << "wireframe rendering";
#endif

  this->update();
}

void BallsCanvas::setDithering(const bool enabled) noexcept {
  this->_settings[SettingKey::Dithering] = {enabled, true};

#ifdef DEBUG
  qDebug() << (enabled ? "Enabled" : "Disabled") << "dithering";
#endif

  this->update();
}

void BallsCanvas::resetCamera() noexcept {
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
                                const QString& fragment) noexcept {

  using namespace balls::shader;
#ifdef DEBUG
  qDebug() << "Updating shaders...";
#endif

  this->makeCurrent();
  this->_shader.release();
  this->_shader.removeAllShaders();

  bool added = true;
  added &= _shader.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
  added &= _shader.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment);

  if (!added) {
#ifdef DEBUG
    qDebug() << "Could not compile user-given shaders:" << _shader.log();
#endif
    return false;
  }

  if (!_shader.link()) {
#ifdef DEBUG
    qDebug() << "Could not link user-given shaders:" << _shader.log();
#endif
    return false;
  }

  if (!_shader.bind()) {
#ifdef DEBUG
    qDebug() << "Could not bind user-given shader program:" << _shader.log();
#endif

    return false;
  }

  this->_queryInputLocations();

  return true;
}
}
