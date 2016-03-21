#ifndef MESHMESH_HPP
#define MESHMESH_HPP

#include "model/mesh/Mesh.hpp"

#include <generator/AnyMesh.hpp>

namespace balls {

class MeshMesh : public Mesh
{
  Q_OBJECT

public:
  MeshMesh(QObject* parent, Type);
  virtual ~MeshMesh() {}

protected /* methods */:
  void updateMesh() override final;

protected /* fields */:
  generator::AnyMesh m_mesh;
};
}


Q_DECLARE_METATYPE(balls::MeshMesh*)

#endif // MESHMESH_HPP
