#ifndef BOXMESH_HPP
#define BOXMESH_HPP

#include <QObject>
#include <glm/vec3.hpp>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

using glm::dvec3;
using glm::uvec3;

class BoxMesh : public MeshMesh {
  Q_OBJECT

  Q_CLASSINFO("segments", "minimum=1;")

  Q_PROPERTY(dvec3 size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uvec3 segments MEMBER m_segments WRITE setSegments FINAL)

public:
  explicit BoxMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  dvec3 m_size;
  uvec3 m_segments;

private /* setters */:
  void setSize(const dvec3& size);
  void setSegments(const uvec3& segments);
};
}

Q_DECLARE_METATYPE(balls::BoxMesh*)
#endif // BOXMESH_HPP
