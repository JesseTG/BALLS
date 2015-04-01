#ifndef BALLSCANVAS_HPP
#define BALLSCANVAS_HPP

#include <array>
#include <unordered_map>

#include <QColor>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtGlobal>
#include <QVector3D>

#include "mesh/Mesh.hpp"
#include "mesh/ShaderInputs.hpp"
#include "config/Settings.hpp"

class QKeyEvent;
class QMouseEvent;
class QOpenGLFunctions_3_0;
class QOpenGLFunctions_3_1;
class QOpenGLFunctions_3_2_Core;
class QOpenGLFunctions_3_3_Core;
class QOpenGLFunctions_4_0_Core;
class QOpenGLFunctions_4_1_Core;
class QOpenGLFunctions_4_2_Core;
class QOpenGLFunctions_4_3_Core;
class QOpenGLShader;
class QWheelEvent;

namespace balls {
namespace mesh {
class MeshGenerator;
}

using std::array;
using std::unordered_map;
using namespace balls::config;

class BallsCanvas : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit BallsCanvas(QWidget* parent = nullptr);
  ~BallsCanvas();
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(const int, const int) override;
  void setMesh(mesh::MeshGenerator*) noexcept;
  bool updateShaders(const QString&, const QString&, const QString&) noexcept;

public /* getters */:
  QOpenGLShaderProgram& getShader() { return this->_shader; }
  const QOpenGLShaderProgram& getShader() const { return this->_shader; }

  QOpenGLDebugLogger& getLogger() { return this->_log; }
  const QOpenGLDebugLogger& getLogger() const { return this->_log; }

signals:
  void geometryShadersSupported(const bool);
  void gl3NotSupported();
  void finishedInitializing();

public slots:
  void setBackfaceCulling(const bool) noexcept;
  void setDepthTesting(const bool) noexcept;
  void setWireframe(const bool) noexcept;
  void setDithering(const bool) noexcept;
  void resetCamera() noexcept;

protected:
  void mousePressEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void wheelEvent(QWheelEvent*) override;

private /* mesh information */:
  mesh::MeshGenerator* _meshgen;
  mesh::Mesh _mesh;

private /* shader attributes/uniforms */:
  unordered_map<shader::AttributeName, int> _attributes;
  unordered_map<shader::UniformName, int> _uniforms;
  array<Setting, static_cast<std::size_t>(SettingKey::Count)> _settings;

  QPointF _lastMousePos;

  QMatrix4x4 _model;
  QMatrix4x4 _view;
  QMatrix4x4 _projection;
  QMatrix4x4 _combined;

  QOpenGLDebugLogger _log;
  QOpenGLBuffer _vbo;
  QOpenGLBuffer _ibo;
  QOpenGLVertexArrayObject _vao;

  QOpenGLShaderProgram _shader;

  QOpenGLFunctions_3_0* _gl30;
  QOpenGLFunctions_3_1* _gl31;
  QOpenGLFunctions_3_2_Core* _gl32;
  QOpenGLFunctions_3_3_Core* _gl33;
  QOpenGLFunctions_4_0_Core* _gl40;
  QOpenGLFunctions_4_1_Core* _gl41;
  QOpenGLFunctions_4_2_Core* _gl42;
  QOpenGLFunctions_4_3_Core* _gl43;

private /* methods */:
  void _initSettings();
  void _initGLPointers();
  void _initGLMemory();
  void _initLogger();
  void _initShaders();
  void _queryInputLocations();
  void _initAttributes();
  void _drawNormals() noexcept;
private /* template methods */:
  template <int Major, int Minor, class QOpenGLF>
  void _initGLFunction(QOpenGLF** gl) {
    *(gl) = QOpenGLContext::currentContext()->versionFunctions<QOpenGLF>();
    if (*gl) {
      (*gl)->initializeOpenGLFunctions();
      // If we have this version of OpenGL available...

      qDebug().nospace() << "OpenGL version " << Major << '.' << Minor
                         << " available";
    } else {
      qDebug().nospace() << "Could not load OpenGL version " << Major << '.' << Minor;
    }
  }

  template <GLenum E>
  void _glToggle(const bool enabled) noexcept {
    if (enabled) {
      this->glEnable(E);
    } else {
      this->glDisable(E);
    }
  }

  template <SettingKey Key, GLenum GL>
  void _updateGLSetting() {
    Setting& setting = _settings[Key];
    if (setting.changed) {
      this->_glToggle<GL>(setting.value.toBool());
      setting.changed = false;
    }
  }
};
}

#endif // BALLSCANVAS_HPP
