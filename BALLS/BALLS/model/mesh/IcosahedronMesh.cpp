#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/IcosahedronMesh.hpp"

#include <generator/IcosahedronMesh.hpp>

namespace balls {
IcosahedronMesh::IcosahedronMesh(QObject *parent)
  : BaseSphereMesh(parent, Type::Icosahedron) {
  m_radius = 1.0;
  m_segments = 1u;

  updateMesh();
}

void IcosahedronMesh::assignMesh() {
  m_mesh = generator::IcosahedronMesh(m_radius, m_segments);
}
}
