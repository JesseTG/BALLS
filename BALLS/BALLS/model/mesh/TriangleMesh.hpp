#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include <QObject>
#include <glm/vec3.hpp>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

using glm::dvec3;

class TriangleMesh : public MeshMesh
{
  Q_OBJECT

  Q_PROPERTY(dvec3 a MEMBER m_a WRITE setA FINAL)
  Q_PROPERTY(dvec3 b MEMBER m_b WRITE setB FINAL)
  Q_PROPERTY(dvec3 c MEMBER m_c WRITE setC FINAL)
  Q_PROPERTY(uint segments MEMBER m_segments WRITE setSegments FINAL)

public:
  TriangleMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  dvec3 m_a;
  dvec3 m_b;
  dvec3 m_c;
  unsigned int m_segments;

private /* setters */:
  void setSegments(unsigned int);
  void setA(const dvec3&);
  void setB(const dvec3&);
  void setC(const dvec3&);
};
}

Q_DECLARE_METATYPE(balls::TriangleMesh*)

#endif // TRIANGLEMESH_HPP
