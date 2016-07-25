#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/SphericalTriangleMesh.hpp"

#include <generator/SphericalTriangleMesh.hpp>

namespace balls {
SphericalTriangleMesh::SphericalTriangleMesh(QObject *parent)
  : BaseSphereMesh(parent, Type::SphericalTriangle) {
  m_radius = 1.0;
  m_segments = 4u;

  updateMesh();
}

void SphericalTriangleMesh::assignMesh() {
  m_mesh = generator::SphericalTriangleMesh(m_radius, m_segments);
}
}
