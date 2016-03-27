#include "precompiled.hpp"
#include "model/Meshes.hpp"

#include "model/mesh/BoxMesh.hpp"
#include "model/mesh/CapsuleMesh.hpp"
#include "model/mesh/ConeMesh.hpp"
#include "model/mesh/CylinderMesh.hpp"
#include "model/mesh/DiskMesh.hpp"
#include "model/mesh/IcoSphereMesh.hpp"
#include "model/mesh/IcosahedronMesh.hpp"
#include "model/mesh/PlaneMesh.hpp"
#include "model/mesh/RoundedBoxMesh.hpp"
#include "model/mesh/SphereMesh.hpp"
#include "model/mesh/SphericalConeMesh.hpp"
#include "model/mesh/SphericalTriangleMesh.hpp"
#include "model/mesh/SpringMesh.hpp"
#include "model/mesh/TorusKnotMesh.hpp"
#include "model/mesh/TorusMesh.hpp"
#include "model/mesh/TriangleMesh.hpp"
#include "model/mesh/TubeMesh.hpp"

namespace balls {

Meshes::Meshes(QObject *parent) : QObject(parent) {
  int index = Mesh::staticMetaObject.indexOfEnumerator("Type");

  Q_ASSUME(index >= 0);

  m_metaEnum = Mesh::staticMetaObject.enumerator(index);
}

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
  case Mesh::Icosahedron:
    m_meshes.push_back(new IcosahedronMesh(this));
    break;
  case Mesh::IcoSphere:
    m_meshes.push_back(new IcoSphereMesh(this));
    break;
  case Mesh::Plane:
    m_meshes.push_back(new PlaneMesh(this));
    break;
  case Mesh::RoundedBox:
    m_meshes.push_back(new RoundedBoxMesh(this));
    break;
  case Mesh::Sphere:
    m_meshes.push_back(new SphereMesh(this));
    break;
  case Mesh::SphericalCone:
    m_meshes.push_back(new SphericalConeMesh(this));
    break;
  case Mesh::SphericalTriangle:
    m_meshes.push_back(new SphericalTriangleMesh(this));
    break;
  case Mesh::Spring:
    m_meshes.push_back(new SpringMesh(this));
    break;
  case Mesh::Torus:
    m_meshes.push_back(new TorusMesh(this));
    break;
  case Mesh::TorusKnot:
    m_meshes.push_back(new TorusKnotMesh(this));
    break;
  case Mesh::Triangle:
    m_meshes.push_back(new TriangleMesh(this));
    break;
  case Mesh::Tube:
    m_meshes.push_back(new TubeMesh(this));
    break;
  default:
    break; // TODO: Support other mesh types
  }

  const char *name = m_metaEnum.valueToKey(type);

  Q_ASSUME(name != nullptr);
  qDebug() << "Created mesh of type" << name;
  m_meshes.back()->setObjectName(name);

  return *m_meshes.back();
}

void Meshes::removeMesh(int index) {}

void Meshes::clear() {
  m_meshes.clear();
}
}
