#include "precompiled.hpp"

#include "model/mesh/MeshMesh.hpp"

#include <generator/EmptyMesh.hpp>
#include <generator/MeshVertex.hpp>
#include <generator/Triangle.hpp>

namespace balls {

MeshMesh::MeshMesh(QObject *parent, Type type)
  : Mesh(parent, type, Topology::Volume), m_mesh(generator::EmptyMesh()) {}

void MeshMesh::updateMesh() {
  this->assignMesh();

  m_positions.clear();
  m_normals.clear();
  m_texCoords.clear();
  m_indices.clear();

  for (const generator::Triangle &t : m_mesh.triangles()) {
    m_indices.push_back(t.vertices.x);
    m_indices.push_back(t.vertices.y);
    m_indices.push_back(t.vertices.z);
  }

  for (const generator::MeshVertex &v : m_mesh.vertices()) {
    m_positions.push_back(v.position.x);
    m_positions.push_back(v.position.y);
    m_positions.push_back(v.position.z);
    m_normals.push_back(v.normal.x);
    m_normals.push_back(v.normal.y);
    m_normals.push_back(v.normal.z);
    m_texCoords.push_back(v.texCoord.x);
    m_texCoords.push_back(v.texCoord.y);
  }
}
}
