#include "precompiled.hpp"

#include "model/mesh/IcoSphereMesh.hpp"
#include "Constants.hpp"

#include <generator/IcoSphereMesh.hpp>

namespace balls {
IcoSphereMesh::IcoSphereMesh(QObject *parent)
    : BaseSphereMesh(parent, Type::IcoSphere) {
  m_radius = 1.0;
  m_segments = 1u;

  updateMesh();
}

void IcoSphereMesh::assignMesh() {
  m_mesh = generator::IcoSphereMesh(m_radius, m_segments);
}
}
