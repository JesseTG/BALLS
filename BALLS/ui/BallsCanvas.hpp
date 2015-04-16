#ifndef BALLSCANVAS_HPP
#define BALLSCANVAS_HPP

#include <unordered_map>

#include <QtCore/QtGlobal>
#include <QtGui/QColor>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLDebugLogger>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QVector3D>
#include <QtWidgets/QOpenGLWidget>

#include "mesh/Mesh.hpp"
#include "shader/ShaderInputs.hpp"
#include "shader/ShaderUniform.hpp"
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

using std::unordered_map;
using std::uint8_t;
using namespace balls::config;
using namespace balls::shader;

static Q_CONSTEXPR GLuint DEFAULT_INDEX = -1;
static Q_CONSTEXPR GLenum DEFAULT_TYPE = -1;
static Q_CONSTEXPR GLint DEFAULT_SIZE = 0;
static Q_CONSTEXPR GLsizei DEFAULT_LENGTH = 0;

enum class UpdateFrequency {
  EveryFrame,
  OnRecompile,
  OnChange,
  OnlyOnce,
};

struct UniformInfo {
  UniformFunction function;
  UpdateFrequency whenToUpdate;
  GLuint index;
  GLenum type;
  GLsizei length;
  GLint size;

  UniformInfo(const UniformFunction& f, const UpdateFrequency freq)
    : function(f),
      whenToUpdate(freq),
      index(DEFAULT_INDEX),
      type(DEFAULT_TYPE),
      length(DEFAULT_LENGTH),
      size(DEFAULT_SIZE) {}
  UniformInfo() : UniformInfo(nullptr, UpdateFrequency::EveryFrame) {}
};

class BallsCanvas : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit BallsCanvas(QWidget* parent = nullptr);
  ~BallsCanvas();
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(const int, const int) override;
  void setMesh(mesh::MeshGenerator*) Q_DECL_NOEXCEPT;
  bool updateShaders(const QString&, const QString&,
                     const QString&) Q_DECL_NOEXCEPT;
  void updateUniformInfo();
  void changeUniform(const UniformInfo&, const QVariant&);

public /* getters/setters */:
  QOpenGLShaderProgram& getShader() Q_DECL_NOEXCEPT { return this->_shader; }
  const QOpenGLShaderProgram& getShader() const Q_DECL_NOEXCEPT {
    return this->_shader;
  }

  QOpenGLDebugLogger& getLogger() Q_DECL_NOEXCEPT { return this->_log; }
  const QOpenGLDebugLogger& getLogger() const Q_DECL_NOEXCEPT {
    return this->_log;
  }

  uint8_t getOpenGLMajor() const Q_DECL_NOEXCEPT { return _glmajor; }
  uint8_t getOpenGLMinor() const Q_DECL_NOEXCEPT { return _glminor; }
signals:
  void geometryShadersSupported(const bool);
  void gl3NotSupported();
  void finishedInitializing();
  void fatalGraphicsError(const QString&, const QString&, const int);
  void graphicsWarning(const QString&, const QString&);
  void reportNewUniforms(const balls::shader::UniformMap&);
  void reportRemovedUniforms(const QStringList&);
  void reportChangedUniforms(const balls::shader::UniformMap);
public slots:
  void setOption(const bool) Q_DECL_NOEXCEPT;
  void setOption(const int) Q_DECL_NOEXCEPT;
  void resetCamera() Q_DECL_NOEXCEPT;
  void changeCustomUniform(const QString&, const QVariant&);

protected /* events */:
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
  unordered_map<AttributeName, int> _attributes;
  unordered_map<UniformName, UniformInfo> _builtInUniforms;
  unordered_map<UniformName, UniformInfo> _customUniforms;
  unordered_map<QString, Setting> _settings;

  QPointF _lastMousePos;

private /* matrices */:
  QMatrix4x4 _model;
  QMatrix4x4 _view;
  QMatrix4x4 _projection;
  QMatrix4x4 _combined;

private /* OpenGL structures */:
  QOpenGLDebugLogger _log;
  QOpenGLBuffer _vbo;
  QOpenGLBuffer _ibo;
  QOpenGLVertexArrayObject _vao;
  QOpenGLShaderProgram _shader;
  uint8_t _glmajor : 3;
  uint8_t _glminor : 3;

private /* OpenGL function pointers */:
  QOpenGLFunctions_3_0* _gl30;
  QOpenGLFunctions_3_1* _gl31;
  QOpenGLFunctions_3_2_Core* _gl32;
  QOpenGLFunctions_3_3_Core* _gl33;
  QOpenGLFunctions_4_0_Core* _gl40;
  QOpenGLFunctions_4_1_Core* _gl41;
  QOpenGLFunctions_4_2_Core* _gl42;
  QOpenGLFunctions_4_3_Core* _gl43;

private /* update methods */:
  void _updateUniformList() Q_DECL_NOEXCEPT;
  void _updateRegularUniformValues();
private /* initializers */:
  void _initAttributeLocations();
  void _initSettings();
  void _initGLPointers();
  void _initGLMemory();
  void _initLogger();
  void _initShaders();
  void _initAttributes();
  void _initUniforms();

private /* templated utility methods */:
  template <int Major, int Minor, class QOpenGLF>
  void _initGLFunction(QOpenGLF** gl) Q_DECL_NOEXCEPT {
    *(gl) = QOpenGLContext::currentContext()->versionFunctions<QOpenGLF>();

    if (*gl) {
      (*gl)->initializeOpenGLFunctions();
      // If we have this version of OpenGL available...

      qDebug().nospace() << "OpenGL version " << Major << '.' << Minor
      << " available";
    }
    else {
      qDebug().nospace() << "Could not load OpenGL version " << Major << '.' << Minor;
    }
  }

  template <GLenum E>
  void _glToggle(const bool enabled) Q_DECL_NOEXCEPT {
    if (enabled) {
      this->glEnable(E);
    }
    else {
      this->glDisable(E);
    }
  }

  template <GLenum GL>
  void _updateGLSetting(const QString& key) Q_DECL_NOEXCEPT {
    Setting& setting = _settings[key];

    if (setting.changed) {
      this->_glToggle<GL>(setting.value.toBool());
      setting.changed = false;
    }
  }
};
}

#endif // BALLSCANVAS_HPP
