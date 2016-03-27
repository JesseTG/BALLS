#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/BoxMesh.hpp"

#include <generator/BoxMesh.hpp>

namespace balls {

BoxMesh::BoxMesh(QObject *parent)
  : MeshMesh(parent, Type::Box), m_size(1.0, 1.0, 1.0), m_segments(8u, 8u, 8u) {
  updateMesh();
}

void BoxMesh::setSize(const dvec3 &size) {
  if (glm::any(glm::epsilonNotEqual(size, m_size, constants::EPSILON))) {
    // If the user actually adjusted the size...
    m_size = size;
    updateMesh();
  }
}

void BoxMesh::setSegments(const uvec3 &segments) {
  if (m_segments != segments) {
    // If the user actually adjusted the segment resolution...
    m_segments = segments;
    updateMesh();
  }
}

void BoxMesh::assignMesh() {
  m_mesh = generator::BoxMesh(m_size, m_segments);
}
}
