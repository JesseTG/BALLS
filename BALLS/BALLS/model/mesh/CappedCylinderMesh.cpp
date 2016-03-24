#include "precompiled.hpp"

#include "model/mesh/CappedCylinderMesh.hpp"
#include "Constants.hpp"

#include <generator/CappedCylinderMesh.hpp>

namespace balls {
CappedCylinderMesh::CappedCylinderMesh(QObject *parent)
    : BaseCylindricalMesh(parent, Type::CappedCylinder) {
  m_radius = 1.0; // Can't initialize these in member initializer list,
  m_size = 1.0;   // don't feel like figuring out why
  m_slices = 32u;
  m_segments = 8u;
  m_rings = 4u;
  m_start = 0.0;
  m_sweep = 360.0;

  updateMesh();
}

void CappedCylinderMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void CappedCylinderMesh::assignMesh() {
  m_mesh = generator::CappedCylinderMesh(m_radius, m_size, m_slices, m_segments,
                                         m_rings, glm::radians(m_start),
                                         glm::radians(m_sweep));
}
}
