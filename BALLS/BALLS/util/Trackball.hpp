#ifndef TRACKBALL_HPP
#define TRACKBALL_HPP

#include <glm/glm.hpp>
#include <QPoint>
#include <QPointF>

namespace balls {
namespace util {

using namespace glm;

/**
 * Code is a heavily modified form of
 * http://nehe.gamedev.net/tutorial/arcball_rotation/19003/
 */
class Trackball {
public:
  //Create/Destroy
  Trackball(const float, const float) noexcept;
Trackball() noexcept :
  Trackball(2.0f, 2.0f) {}

  //Set new bounds
  void setBounds(float w, float h) noexcept {
    Q_ASSERT((w > 1.0f)&&  (h > 1.0f));

    //Set adjustment factor for width/height
    this->AdjustWidth  = 1.0f / ((w  - 1.0f) * 0.5f);
    this->AdjustHeight = 1.0f / ((h - 1.0f) * 0.5f);
  }

  //Mouse down
  void click(const vec2&) noexcept;
  void click(const QPointF& p) noexcept { click(vec2(p.x(), p.y())); }
  void click(const QPoint& p) noexcept { click(vec2(p.x(), p.y())); }
  void click(const float x, const float y) noexcept { click(vec2(x, y)); }

  //Mouse drag, calculate rotation
  void drag(const vec2&) noexcept;
  void drag(const QPointF& p) noexcept { drag(vec2(p.x(), p.y())); }
  void drag(const QPoint& p) noexcept { drag(vec2(p.x(), p.y())); }
  void drag(const float x, const float y) noexcept { drag(vec2(x, y)); }

  const quat& getQuaternion() const noexcept { return _rotation; }
  const mat4& getMatrix() const noexcept { return _matrix; }
private:
  //Saved click vector
  vec3 _start;
  //Saved drag vector
  vec3 _end;
  //Mouse bounds width
  float AdjustWidth;
  //Mouse bounds height
  float AdjustHeight;

  quat _rotation;
  mat4 _matrix;
private:
  vec3 _mapToSphere(vec2) const noexcept;
};
}
}

#endif // TRACKBALL_HPP
