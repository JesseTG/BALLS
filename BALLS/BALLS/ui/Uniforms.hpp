#ifndef UNIFORMMEDIATOR_HPP
#define UNIFORMMEDIATOR_HPP

#include <QtCore/QElapsedTimer>
#include <QtCore/QObject>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "util/Trackball.hpp"
#include "util/TypeInfo.hpp"

class QEvent;
class QMouseEvent;
class QResizeEvent;
class QWheelEvent;

namespace balls {

using balls::util::types::UniformCollection;
using balls::util::types::UniformInfo;
using namespace glm;

class BallsCanvas;

class Uniforms final : public QObject {
  Q_OBJECT

  // Note: We can't have one uniform be read as multiple types.  So pick a
  // canonical type, and let BallsCanvas work out the conversions
  Q_PROPERTY(uint elapsedTime READ elapsedTime STORED false DESIGNABLE active("elapsedTime") FINAL)
  Q_PROPERTY(ivec2 mousePos READ mousePos DESIGNABLE active("mousePos") FINAL)
  Q_PROPERTY(ivec2 lastMousePos READ lastMousePos DESIGNABLE
             active("lastMousePos") FINAL)
  Q_PROPERTY(uvec2 canvasSize READ canvasSize DESIGNABLE active("canvasSize")
             FINAL)
  Q_PROPERTY(uint canvasWidth READ canvasWidth DESIGNABLE active("canvasWidth")
             STORED false FINAL)
  Q_PROPERTY(uint canvasHeight READ canvasHeight DESIGNABLE active("canvasHeight")
             STORED false FINAL)
  Q_PROPERTY(uvec2 lastCanvasSize READ lastCanvasSize DESIGNABLE
             active("lastCanvasSize") FINAL)
  Q_PROPERTY(mat4 trackball READ trackball DESIGNABLE active("trackball") STORED false FINAL)
  Q_PROPERTY(mat4 matrix READ matrix DESIGNABLE active("matrix") STORED false FINAL)
  Q_PROPERTY(mat4 model MEMBER _model DESIGNABLE active("model") FINAL)
  Q_PROPERTY(mat4 view MEMBER _view DESIGNABLE active("view") FINAL)
  Q_PROPERTY(mat4 modelView READ modelView DESIGNABLE active("modelView") STORED false FINAL)
  Q_PROPERTY(mat4 projection MEMBER _projection DESIGNABLE active("projection") FINAL)

  // How about I *ignore* the GLSL type here and let BallsCanvas decide what conversion to make?
  // But maybe use tags for deciding how often to update a static property?
public:
  explicit Uniforms(QObject* = nullptr) noexcept;
  // TODO: Figure out how to minimize calls to READs (because that means we're
  // probably also transferring stuff to the GPU).
public /* getters */:
  const UniformCollection& uniformInfo() const noexcept;

private /* uniform property accessors */:
  uint elapsedTime() const noexcept;
  ivec2 mousePos() const noexcept;
  ivec2 lastMousePos() const noexcept;
  uvec2 canvasSize() const noexcept;
  uint canvasWidth() const noexcept;
  uint canvasHeight() const noexcept;
  uvec2 lastCanvasSize() const noexcept;
  const mat4& trackball() const noexcept;
  const mat4 matrix() const noexcept;
  const mat4 modelView() const noexcept;

public /* uniform list queries */:
  bool active(const QString& name) const noexcept;
public /* setters */:
  void setFov(const float) noexcept;
public slots:
  void receiveUniforms(const UniformCollection&) noexcept;
protected:
  bool eventFilter(QObject* obj, QEvent* event) override;
  bool event(QEvent* e) override;
  void mouseMoveEvent(QMouseEvent*) noexcept;
  void mousePressEvent(QMouseEvent*) noexcept;
  void wheelEvent(QWheelEvent*) noexcept;
  void resizeEvent(QResizeEvent*) noexcept;

public /* types */:

public /* resetters */:
  void resetModelView() noexcept;
private /* helpers */:
  void _updateProjection() noexcept;
  void _handleNewUniforms(const UniformCollection&) noexcept;
  void _handleDiscardedUniforms(const UniformCollection&) noexcept;
  void _handleKeptUniforms(const UniformCollection&) noexcept;

private /* meta info */:
  const QMetaObject* _meta;
  UniformCollection _uniformList;

private /* uniform source values */:
  mat4 _model;
  mat4 _view;
  mat4 _projection;
  util::Trackball _trackball;
  ivec2 _mousePos;
  ivec2 _lastMousePos;
  uvec2 _canvasSize;
  uvec2 _lastCanvasSize;
  float _fov;
  float _farPlane;
  float _nearPlane;
  QElapsedTimer _elapsedTime;
};

inline bool Uniforms::active(const QString& name) const noexcept {
  return std::any_of(
           _uniformList.cbegin(),
           _uniformList.cend(),
  [&name](const UniformInfo & u) {
    return u.name == name;
  });
}

inline const UniformCollection& Uniforms::uniformInfo() const noexcept {
  return this->_uniformList;
}

inline uint Uniforms::elapsedTime() const noexcept {
  return _elapsedTime.elapsed();
}

inline const mat4 Uniforms::matrix() const noexcept {
  return _projection * _view * _model;
}

inline const mat4 Uniforms::modelView() const noexcept {
  return _view * _model;
}

inline ivec2 Uniforms::mousePos() const noexcept {
  return _mousePos;
}

inline ivec2 Uniforms::lastMousePos() const noexcept {
  return _lastMousePos;
}

inline uvec2 Uniforms::canvasSize() const noexcept {
  return _canvasSize;
}

inline uint Uniforms::canvasWidth() const noexcept {
  return _canvasSize.x;
}

inline uint Uniforms::canvasHeight() const noexcept {
  return _canvasSize.y;
}

inline uvec2 Uniforms::lastCanvasSize() const noexcept {
  return _lastCanvasSize;
}

inline const mat4& Uniforms::trackball() const noexcept {
  return _trackball.getMatrix();
}

}

#endif // UNIFORMMEDIATOR_HPP
