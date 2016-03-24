#include "precompiled.hpp"

#include "model/mesh/BaseCylindricalMesh.hpp"
#include "Constants.hpp"

namespace balls {

void BaseCylindricalMesh::setRadius(double radius) {
  if (glm::epsilonNotEqual(radius, m_radius, constants::EPSILON)) {
    // If the user actually adjusted the radius...
    m_radius = radius;
    updateMesh();
  }
}

void BaseCylindricalMesh::setSize(double size) {
  if (glm::epsilonNotEqual(size, m_size, constants::EPSILON)) {
    // If the user actually adjusted the size...
    m_size = size;
    updateMesh();
  }
}

void BaseCylindricalMesh::setSlices(unsigned int slices) {
  if (slices != m_slices) {
    // If the user actually adjusted the number of slices...
    m_slices = slices;
    updateMesh();
  }
}

void BaseCylindricalMesh::setSegments(unsigned int segments) {
  if (segments != m_segments) {
    // If the user actually adjusted the number of segments...
    m_segments = segments;
    updateMesh();
  }
}

void BaseCylindricalMesh::setStart(double start) {
  if (glm::epsilonNotEqual(start, m_start, constants::EPSILON)) {
    // If the user actually adjusted the start of the arc...
    m_start = start;
    updateMesh();
  }
}

void BaseCylindricalMesh::setSweep(double sweep) {
  if (glm::epsilonNotEqual(sweep, m_sweep, constants::EPSILON)) {
    // If the user actually adjusted the sweep interval...
    m_sweep = sweep;
    updateMesh();
  }
}
}
