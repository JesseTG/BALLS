#include "precompiled.hpp"

#include "model/mesh/Mesh.hpp"

namespace balls {
Mesh::Mesh(QObject *parent, Type type, Topology topology)
  : QObject(parent), m_type(type), m_topology(topology) {}

const std::vector<GLfloat> &Mesh::positions() const noexcept {
  return m_positions;
}

const std::vector<GLfloat> &Mesh::normals() const noexcept {
  return m_normals;
}

const std::vector<GLfloat> &Mesh::texCoords() const noexcept {
  return m_texCoords;
}

const std::vector<GLushort> &Mesh::indices() const noexcept {
  return m_indices;
}
}
