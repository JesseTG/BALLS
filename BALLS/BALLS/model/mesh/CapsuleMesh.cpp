#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/CapsuleMesh.hpp"

#include <generator/CapsuleMesh.hpp>

namespace balls {
CapsuleMesh::CapsuleMesh(QObject *parent)
  : BaseCylindricalMesh(parent, Type::Capsule) {
  m_radius = 1.0; // Can't initialize these in member initializer list,
  m_size = 0.5; // don't feel like figuring out why
  m_slices = 32u;
  m_segments = 4u;
  m_rings = 8u;
  m_start = 0.0;
  m_sweep = 360.0;

  updateMesh();
}

void CapsuleMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void CapsuleMesh::assignMesh() {
  m_mesh = generator::CapsuleMesh(
    m_radius,
    m_size,
    m_slices,
    m_segments,
    m_rings,
    glm::radians(m_start),
    glm::radians(m_sweep));
}
}
