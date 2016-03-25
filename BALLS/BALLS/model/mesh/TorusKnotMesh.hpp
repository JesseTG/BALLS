#ifndef TORUSKNOTMESH_HPP
#define TORUSKNOTMESH_HPP

#include <QObject>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

class TorusKnotMesh : public MeshMesh
{
  Q_OBJECT

  Q_PROPERTY(int p MEMBER m_p WRITE setP FINAL)
  Q_PROPERTY(int q MEMBER m_q WRITE setQ FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(uint segments MEMBER m_segments WRITE setSegments FINAL)

public:
  TorusKnotMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  int m_p;
  int m_q;
  unsigned int m_slices;
  unsigned int m_segments;

private /* setters */:
  void setP(int);
  void setQ(int);
  void setSlices(unsigned int);
  void setSegments(unsigned int);
};
}

Q_DECLARE_METATYPE(balls::TorusKnotMesh*)

#endif // TORUSKNOTMESH_HPP
