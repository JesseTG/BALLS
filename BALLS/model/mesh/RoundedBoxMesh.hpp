#ifndef ROUNDEDBOXMESH_HPP
#define ROUNDEDBOXMESH_HPP

#include <QObject>
#include <glm/vec3.hpp>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

using glm::dvec3;
using glm::uvec3;

class RoundedBoxMesh : public MeshMesh {
  Q_OBJECT

  Q_PROPERTY(double radius MEMBER m_radius WRITE setRadius FINAL)
  Q_PROPERTY(dvec3 size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(uvec3 segments MEMBER m_segments WRITE setSegments FINAL)

public:
  explicit RoundedBoxMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  double m_radius;
  dvec3 m_size;
  unsigned int m_slices;
  uvec3 m_segments;

private /* setters */:
  void setRadius(double);
  void setSize(const dvec3& size);
  void setSlices(unsigned int);
  void setSegments(const uvec3& segments);
};
}

Q_DECLARE_METATYPE(balls::RoundedBoxMesh*)

#endif // ROUNDEDBOXMESH_HPP
