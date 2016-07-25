#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/TriangleMesh.hpp"

#include <generator/TriangleMesh.hpp>

namespace balls {

TriangleMesh::TriangleMesh(QObject *parent)
  : MeshMesh(parent, Type::Triangle),
    m_a(glm::normalize(dvec3(-1.0, -1.0, 0.0))),
    m_b(glm::normalize(dvec3(1.0, -1.0, 0.0))),
    m_c(0.0, 1.0, 0.0),
    m_segments(4u) {
  updateMesh();
}

void TriangleMesh::setA(const dvec3 &a) {
  if (glm::any(glm::epsilonNotEqual(a, m_a, constants::EPSILON))) {
    // If the user actually adjusted the first vertex...
    m_a = a;
    updateMesh();
  }
}

void TriangleMesh::setB(const dvec3 &b) {
  if (glm::any(glm::epsilonNotEqual(b, m_b, constants::EPSILON))) {
    // If the user actually adjusted the second vertex...
    m_b = b;
    updateMesh();
  }
}

void TriangleMesh::setC(const dvec3 &c) {
  if (glm::any(glm::epsilonNotEqual(c, m_c, constants::EPSILON))) {
    // If the user actually adjusted the third vertex...
    m_c = c;
    updateMesh();
  }
}

void TriangleMesh::setSegments(unsigned int segments) {
  if (m_segments != segments) {
    // If the user actually adjusted the segment resolution...
    m_segments = segments;
    updateMesh();
  }
}

void TriangleMesh::assignMesh() {
  m_mesh = generator::TriangleMesh(m_a, m_b, m_c, m_segments);
}
}
