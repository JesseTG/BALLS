#ifndef PLANEMESH_HPP
#define PLANEMESH_HPP

#include <QObject>
#include <glm/vec2.hpp>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

using glm::dvec2;
using glm::uvec2;

class PlaneMesh : public MeshMesh {
  Q_OBJECT

  Q_PROPERTY(dvec2 size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uvec2 segments MEMBER m_segments WRITE setSegments FINAL)

public:
  explicit PlaneMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  dvec2 m_size;
  uvec2 m_segments;

private /* setters */:
  void setSize(const dvec2& size);
  void setSegments(const uvec2& segments);
};
}

Q_DECLARE_METATYPE(balls::PlaneMesh*)

#endif // PLANEMESH_HPP
