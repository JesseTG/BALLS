#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/PlaneMesh.hpp"

#include <generator/PlaneMesh.hpp>

namespace balls {

PlaneMesh::PlaneMesh(QObject *parent)
  : MeshMesh(parent, Type::Plane), m_size(1.0, 1.0), m_segments(8u, 8u) {
  updateMesh();
}

void PlaneMesh::setSize(const dvec2 &size) {
  if (glm::any(glm::epsilonNotEqual(size, m_size, constants::EPSILON))) {
    // If the user actually adjusted the size...
    m_size = size;
    updateMesh();
  }
}

void PlaneMesh::setSegments(const uvec2 &segments) {
  if (m_segments != segments) {
    // If the user actually adjusted the segment resolution...
    m_segments = segments;
    updateMesh();
  }
}

void PlaneMesh::assignMesh() {
  m_mesh = generator::PlaneMesh(m_size, m_segments);
}
}
