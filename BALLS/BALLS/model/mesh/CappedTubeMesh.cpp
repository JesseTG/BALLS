#include "precompiled.hpp"

#include "model/mesh/CappedTubeMesh.hpp"
#include "Constants.hpp"

#include <generator/CappedTubeMesh.hpp>

namespace balls {
CappedTubeMesh::CappedTubeMesh(QObject *parent)
    : BaseCylindricalMesh(parent, Type::CappedTube) {
  m_radius = 1.0; // Can't initialize these in member initializer list,
  m_size = 1.0;   // don't feel like figuring out why
  m_innerRadius = 0.75;
  m_slices = 32u;
  m_segments = 8u;
  m_rings = 4u;
  m_start = 0.0;
  m_sweep = 360.0;

  updateMesh();
}

void CappedTubeMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void CappedTubeMesh::setInnerRadius(double innerRadius) {
  if (glm::epsilonNotEqual(innerRadius, m_innerRadius, constants::EPSILON)) {
    // If the user actually adjusted the number of rings...
    m_innerRadius = innerRadius;
    updateMesh();
  }
}

void CappedTubeMesh::assignMesh() {
  m_mesh =
      generator::CappedTubeMesh(m_radius, m_innerRadius, m_size, m_slices, m_segments, m_rings,
                                glm::radians(m_start), glm::radians(m_sweep));
}
}
