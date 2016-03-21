#include "precompiled.hpp"

#include "model/mesh/Mesh.hpp"

namespace balls {
Mesh::Mesh(QObject *parent, Type type, Topology topology)
    : QObject(parent), m_type(type), m_topology(topology) {}

const std::vector<GLfloat> &Mesh::getVertices() const noexcept {
  return m_vertices;
}
const std::vector<GLushort> &Mesh::getIndices() const noexcept {
  return m_indices;
}
}
