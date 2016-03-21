#include "precompiled.hpp"

#include "model/mesh/MeshMesh.hpp"

#include <generator/Triangle.hpp>
#include <generator/MeshVertex.hpp>
#include <generator/EmptyMesh.hpp>

namespace balls {

MeshMesh::MeshMesh(QObject* parent, Type type)
    : Mesh(parent, type, Topology::Volume), m_mesh(generator::EmptyMesh()) {}


void MeshMesh::updateMesh() {
  this->assignMesh();

  m_vertices.clear();
  m_indices.clear();

  for (const generator::Triangle &t : m_mesh.triangles()) {
    m_indices.push_back(t.vertices.x);
    m_indices.push_back(t.vertices.y);
    m_indices.push_back(t.vertices.z);
  }

  for (const generator::MeshVertex &v : m_mesh.vertices()) {
    m_vertices.push_back(v.position.x);
    m_vertices.push_back(v.position.y);
    m_vertices.push_back(v.position.z);
    m_vertices.push_back(v.normal.x);
    m_vertices.push_back(v.normal.y);
    m_vertices.push_back(v.normal.z);
    m_vertices.push_back(v.texCoord.x);
    m_vertices.push_back(v.texCoord.y);
  }
}
}
