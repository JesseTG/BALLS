#include "precompiled.hpp"

#include "model/Meshes.hpp"

#include "model/mesh/BoxMesh.hpp"
#include "model/mesh/CappedConeMesh.hpp"

namespace balls {

Meshes::Meshes(QObject *parent) : QObject(parent) {}

Mesh &Meshes::createMesh(Mesh::Type type) noexcept {
  switch (type) {
  case Mesh::Box:
    m_meshes.push_back(new BoxMesh(this));
    break;
  case Mesh::CappedCone:
    m_meshes.push_back(new CappedConeMesh(this));
    break;
  default:
    break; // TODO: Support other mesh types
  }

  qDebug() << "Created mesh of type" << type;
  m_meshes.back()->setObjectName("Mesh");

  return *m_meshes.back();
}

void Meshes::removeMesh(int index) {}

void Meshes::clear() { m_meshes.clear(); }
}
