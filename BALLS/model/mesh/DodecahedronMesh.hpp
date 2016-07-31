#ifndef DODECAHEDRONMESH_HPP
#define DODECAHEDRONMESH_HPP

#include <QObject>
#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class DodecahedronMesh : public BaseSphereMesh
{
  Q_OBJECT

  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)

public:
  explicit DodecahedronMesh(QObject* parent = nullptr);
protected /* constructors */:
  using BaseSphereMesh::BaseSphereMesh;

protected /* members */:
  unsigned int m_rings;

protected /* methods */:
  void assignMesh() override final;

private /* setters */:
  void setRings(unsigned int);
};
}

Q_DECLARE_METATYPE(balls::DodecahedronMesh*)

#endif // DODECAHEDRONMESH_HPP
