#ifndef MODEL_MESH_HPP
#define MODEL_MESH_HPP

#include <vector>

#include <qopengl.h>
#include <QObject>

namespace balls {

class Mesh : public QObject {
  Q_OBJECT

  Q_ENUMS(Type)
  Q_ENUMS(Attribute)
  Q_ENUMS(Topology)

public /* enums */:
  enum Attribute {
    Position = 0b00000001,
    Normal = 0b00000010,
    TextureCoord = 0b00000100,
    Tangent = 0b00001000,
    Binormal = 0b00010000,
  };

  enum Type {
    Box,
    Capsule,
    Circle,
    Cone,
    Cylinder,
    Disk,
    Dodecahedron,
    Helix,
    Icosahedron,
    IcoSphere,
    Knot,
    Line2D,
    Line3D,
    Plane,
    Rectangle,
    RoundedBox,
    RoundedRectangle,
    Sphere,
    SphericalCone,
    SphericalTriangle,
    Spring,
    Torus,
    TorusKnot,
    Triangle,
    Tube,
    // TODO: Parameterization
  };

  enum Topology {
    Volume,
    Shape,
    Path,
  };

  // TODO: Mesh modifiers (maybe another class)

  using CoordType = GLfloat;
  using IndexType = GLushort;

public /* methods */:
  const std::vector<GLfloat> &getVertices() const noexcept;
  const std::vector<GLushort> &getIndices() const noexcept;
  Type type() const noexcept {
    return m_type;
  }

protected /* methods */:
  Mesh(QObject *, Type, Topology);
  virtual void updateMesh() = 0;
  virtual void assignMesh() = 0;

protected /* fields */:
  std::vector<GLushort> m_indices;
  std::vector<GLfloat> m_vertices;

private /* fields */:
  Type m_type;
  Topology m_topology;
};
}

Q_DECLARE_METATYPE(balls::Mesh::Type)
Q_DECLARE_METATYPE(balls::Mesh *)

#endif // MODEL_MESH_HPP
