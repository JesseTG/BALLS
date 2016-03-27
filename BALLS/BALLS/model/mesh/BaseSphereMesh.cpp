#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

void BaseSphereMesh::setRadius(double radius) {
  if (glm::epsilonNotEqual(radius, m_radius, constants::EPSILON)) {
    // If the user actually adjusted the radius...
    m_radius = radius;
    updateMesh();
  }
}

void BaseSphereMesh::setSegments(unsigned int segments) {
  if (segments != m_segments) {
    // If the user actually adjusted the number of segments...
    m_segments = segments;
    updateMesh();
  }
}
}
