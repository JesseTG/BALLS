#include "precompiled.hpp"

#include "model/mesh/SphericalConeMesh.hpp"
#include "Constants.hpp"

#include <generator/SphericalConeMesh.hpp>

namespace balls {
SphericalConeMesh::SphericalConeMesh(QObject *parent)
    : BaseCylindricalMesh(parent, Type::SphericalCone) {
  m_radius = 1.0;
  m_size = 1.0;
  m_slices = 32u;
  m_segments = 8u;
  m_rings = 4u;
  m_start = 0.0;
  m_sweep = 360.0;

  updateMesh();
}

void SphericalConeMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void SphericalConeMesh::assignMesh() {
  m_mesh = generator::SphericalConeMesh(m_radius, m_size, m_slices, m_segments,
                                        m_rings, glm::radians(m_start),
                                        glm::radians(m_sweep));
}
}
