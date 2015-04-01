#ifndef MESH_HPP
#define MESH_HPP

#include <array>
#include <cstdint>
#include <initializer_list>
#include <vector>

#include <QOpenGLContext>
#include <QVector3D>

class QVector3D;

namespace balls {
namespace mesh {

using std::array;
using std::initializer_list;
using std::size_t;
using std::uint16_t;
using std::vector;

class Mesh {
public:
  typedef float CoordType;
  typedef uint16_t IndexType;

  Mesh() noexcept {}

  IndexType add_vertex(const CoordType, const CoordType, const CoordType) noexcept;
  IndexType add_vertex(const QVector3D&) noexcept;
  void add_faces(const initializer_list<array<IndexType, 3>>&) noexcept;
  void add_face(const IndexType, const IndexType, const IndexType) noexcept;

  vector<CoordType> combined() noexcept;

public /* getters */:
  const vector<QVector3D>& vertices() const noexcept { return this->_vertices; }
  const vector<IndexType>& indices() const noexcept { return this->_indices; }
  const vector<QVector3D>& normals() const noexcept { return this->_normals; }

  QVector3D& operator[](const IndexType pos);
  const QVector3D& operator[](const IndexType pos) const;

private /* members */:
  vector<QVector3D> _vertices;
  vector<QVector3D> _normals;
  vector<IndexType> _indices;

private /* methods */:
  void _computeNormals() noexcept;
};
}
}

#endif // MESH_HPP
