#ifndef BASESPHEREMESH_HPP
#define BASESPHEREMESH_HPP
#include <QObject>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

class BaseSphereMesh : public MeshMesh
{
  Q_OBJECT

  Q_PROPERTY(double radius MEMBER m_radius WRITE setRadius FINAL)
  Q_PROPERTY(uint segments MEMBER m_segments WRITE setSegments FINAL)

public:
  virtual ~BaseSphereMesh() {}
protected /* constructors */:
  using MeshMesh::MeshMesh;
protected /* members */:
  double m_radius;
  unsigned int m_segments;

private /* setters */:
  void setRadius(double);
  void setSegments(unsigned int);
};
}

#endif // BASESPHEREMESH_HPP
