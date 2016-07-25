#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/ConeMesh.hpp"

#include <generator/CappedConeMesh.hpp>
#include <generator/ConeMesh.hpp>

namespace balls {
ConeMesh::ConeMesh(QObject *parent) : BaseCylindricalMesh(parent, Type::Cone) {
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

void ConeMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void ConeMesh::setCapped(bool capped) {
  if (capped != m_capped) {
    // If the user toggled the existence of the cap...
    m_capped = capped;
    updateMesh();
  }
}

void ConeMesh::assignMesh() {
  if (m_capped) {
    m_mesh = generator::CappedConeMesh(
      m_radius,
      m_size,
      m_slices,
      m_segments,
      m_rings,
      glm::radians(m_start),
      glm::radians(m_sweep));
  } else {
    m_mesh = generator::ConeMesh(
      m_radius,
      m_size,
      m_slices,
      m_segments,
      glm::radians(m_start),
      glm::radians(m_sweep));
  }
}
}
