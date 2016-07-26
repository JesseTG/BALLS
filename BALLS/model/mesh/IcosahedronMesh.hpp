#ifndef ICOSAHEDRONMESH_HPP
#define ICOSAHEDRONMESH_HPP

#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class IcosahedronMesh : public BaseSphereMesh {
  Q_OBJECT

  Q_CLASSINFO("segments", "minimum=1;")

public:
  explicit IcosahedronMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
};
}

Q_DECLARE_METATYPE(balls::IcosahedronMesh*)
#endif // ICOSAHEDRONMESH_HPP
