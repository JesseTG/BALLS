#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/DodecahedronMesh.hpp"

#include <generator/DodecahedronMesh.hpp>

namespace balls {

DodecahedronMesh::DodecahedronMesh(QObject* parent)
  : BaseSphereMesh(parent, Type::Dodecahedron) {
  m_radius = 1.0;
  m_segments = 1u;
  m_rings = 1u;
  updateMesh();
}

void DodecahedronMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void DodecahedronMesh::assignMesh() {
  m_mesh = generator::DodecahedronMesh(m_radius, m_segments, m_rings);
}
}
