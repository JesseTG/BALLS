#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/CylinderMesh.hpp"

#include <generator/CappedCylinderMesh.hpp>
#include <generator/CylinderMesh.hpp>

namespace balls {
CylinderMesh::CylinderMesh(QObject *parent)
  : BaseCylindricalMesh(parent, Type::Cylinder) {
  m_radius = 1.0; // Can't initialize these in member initializer list,
  m_size = 1.0; // don't feel like figuring out why
  m_slices = 32u;
  m_segments = 8u;
  m_rings = 4u;
  m_start = 0.0;
  m_sweep = 360.0;
  m_capped = true;
  updateMesh();
}

void CylinderMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}


void CylinderMesh::setCapped(bool capped) {
  if (capped != m_capped) {
    // If the user toggled the existence of the cap...
    m_capped = capped;
    updateMesh();
  }
}

void CylinderMesh::assignMesh() {
  if (m_capped) {
    m_mesh = generator::CappedCylinderMesh(
      m_radius,
      m_size,
      m_slices,
      m_segments,
      m_rings,
      glm::radians(m_start),
      glm::radians(m_sweep));
  } else {
    m_mesh = generator::CylinderMesh(
      m_radius,
      m_size,
      m_slices,
      m_segments,
      glm::radians(m_start),
      glm::radians(m_sweep));
  }
}
}
