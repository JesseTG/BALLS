#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/RoundedBoxMesh.hpp"

#include <generator/RoundedBoxMesh.hpp>

namespace balls {

RoundedBoxMesh::RoundedBoxMesh(QObject *parent)
  : MeshMesh(parent, Type::RoundedBox),
    m_radius(0.25),
    m_size(1.0, 1.0, 1.0),
    m_slices(4u),
    m_segments(8u, 8u, 8u) {
  updateMesh();
}

void RoundedBoxMesh::setRadius(double radius) {
  if (glm::epsilonNotEqual(radius, m_radius, constants::EPSILON)) {
    // If the user actually adjusted the radius...
    m_radius = radius;
    updateMesh();
  }
}

void RoundedBoxMesh::setSize(const dvec3 &size) {
  if (glm::any(glm::epsilonNotEqual(size, m_size, constants::EPSILON))) {
    // If the user actually adjusted the size...
    m_size = size;
    updateMesh();
  }
}

void RoundedBoxMesh::setSlices(unsigned int slices) {
  if (m_slices != slices) {
    // If the user actually adjusted the slice resolution...
    m_slices = slices;
    updateMesh();
  }
}

void RoundedBoxMesh::setSegments(const uvec3 &segments) {
  if (m_segments != segments) {
    // If the user actually adjusted the segment resolution...
    m_segments = segments;
    updateMesh();
  }
}

void RoundedBoxMesh::assignMesh() {
  m_mesh = generator::RoundedBoxMesh(m_radius, m_size, m_slices, m_segments);
}
}
