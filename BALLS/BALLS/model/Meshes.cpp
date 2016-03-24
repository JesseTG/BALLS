#include "precompiled.hpp"

#include "model/Meshes.hpp"

#include "model/mesh/BoxMesh.hpp"
#include "model/mesh/CapsuleMesh.hpp"
#include "model/mesh/ConeMesh.hpp"
#include "model/mesh/CylinderMesh.hpp"
#include "model/mesh/DiskMesh.hpp"
#include "model/mesh/TubeMesh.hpp"

namespace balls {

Meshes::Meshes(QObject *parent) : QObject(parent) {}

Mesh &Meshes::createMesh(Mesh::Type type) noexcept {
  switch (type) {
  case Mesh::Box:
    m_meshes.push_back(new BoxMesh(this));
    break;
  case Mesh::Capsule:
    m_meshes.push_back(new CapsuleMesh(this));
    break;
  case Mesh::Cone:
    m_meshes.push_back(new ConeMesh(this));
    break;
  case Mesh::Cylinder:
    m_meshes.push_back(new CylinderMesh(this));
    break;
  case Mesh::Disk:
    m_meshes.push_back(new DiskMesh(this));
    break;
  case Mesh::Tube:
    m_meshes.push_back(new TubeMesh(this));
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
