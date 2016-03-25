#ifndef ICOSAHEDRONMESH_HPP
#define ICOSAHEDRONMESH_HPP

#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class IcosahedronMesh : public BaseSphereMesh
{
  Q_OBJECT

public:
  IcosahedronMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
};
}

Q_DECLARE_METATYPE(balls::IcosahedronMesh*)
#endif // ICOSAHEDRONMESH_HPP
