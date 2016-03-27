#include "precompiled.hpp"
#include "util/Trackball.hpp"
#include "util/Util.hpp"

namespace balls {
namespace util {

constexpr float RADIUS = 1.0f;
constexpr float DIAMETER = RADIUS * 2;
constexpr float RADIUS_SQUARED = RADIUS * RADIUS;

Trackball::Trackball(const float w, const float h) noexcept {
  // Set initial bounds
  this->setBounds(w, h);
}

vec3 Trackball::_mapToSphere(vec2 coords) const noexcept {

  // Adjust point coords and scale down to range of [-1 ... 1]
  coords.x = ((coords.x * this->AdjustWidth) - 1.0f);
  coords.y = (1.0f - (coords.y * this->AdjustHeight));

  // Compute the square of the length of the vector to the point from the center
  float length = glm::length2(coords);

  if (length > RADIUS_SQUARED) {
    // If the point is mapped outside of the sphere... (length > radius squared)

    // Compute a normalizing factor (radius / sqrt(length))
    float norm = RADIUS * glm::fastInverseSqrt(length);

    // Return the "normalized" vector, a point on the sphere
    return vec3(coords * norm, 0.0f);
  } else {
    // Else it's on the inside
    // Return a vector to a point mapped inside the sphere sqrt(radius squared -
    // length)
    return vec3(coords, glm::fastSqrt(RADIUS_SQUARED - length));
  }
}

// Mouse down
void Trackball::click(const vec2& coords) noexcept {
  // Map the point to the sphere
  _start = this->_mapToSphere(coords);
}

// Mouse drag, calculate rotation
void Trackball::drag(const vec2& coords) noexcept {
  // Map the point to the sphere
  _end = _mapToSphere(coords);

  // Return the quaternion equivalent to the rotation
  // Compute the vector perpendicular to the begin and end vectors
  vec3 cross = glm::cross(_start, _end);

  if (glm::length2(cross) > std::numeric_limits<float>::epsilon()) {
    // Compute the length of the perpendicular vector, and if it's non-zero...
    // We're ok, so return the perpendicular vector as the transform after all
    // In the quaternion values, w is cosine (theta / 2), where theta is
    // rotation angle
    _rotation = glm::normalize(quat(glm::dot(_start, _end), cross));
  } else {
    // The begin and end vectors coincide, so return an identity transform
    _rotation = {};
  }

  _matrix = static_cast<mat4>(_rotation);
}
}
}
