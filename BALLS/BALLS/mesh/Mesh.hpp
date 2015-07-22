#ifndef MESH_HPP
#define MESH_HPP

#include <array>
#include <cstdint>
#include <initializer_list>
#include <vector>

#include <QOpenGLContext>

#include <glm/vec3.hpp>

namespace balls {
namespace mesh {

using std::array;
using std::initializer_list;
using std::size_t;
using std::uint16_t;
using std::vector;
using glm::vec3;

class Mesh {
public:
  typedef float CoordType;
  typedef uint16_t IndexType;

  Mesh() noexcept {}

  inline IndexType add_vertex(const CoordType, const CoordType,
                              const CoordType) noexcept;
  inline IndexType add_vertex(const vec3&) noexcept;
  inline void add_faces(const initializer_list<array<IndexType, 3>>&)
  noexcept;
  inline void add_face(const IndexType, const IndexType,
                       const IndexType) noexcept;

  vector<CoordType> combined() noexcept;

public /* getters */:
  const vector<vec3>& vertices() const noexcept { return this->_vertices; }
  const vector<IndexType>& indices() const noexcept { return this->_indices; }
  const vector<vec3>& normals() const noexcept { return this->_normals; }

  inline vec3& operator[](const IndexType pos);
  inline const vec3& operator[](const IndexType pos) const;

private /* members */:
  vector<vec3> _vertices;
  vector<vec3> _normals;
  vector<IndexType> _indices;

private /* methods */:
  void _computeNormals() noexcept;
};

inline vec3& Mesh::operator[](const Mesh::IndexType pos) {
  #ifdef DEBUG
  return this->_vertices.at(pos);
  // at() has bounds-checking, operator[] doesn't
  #else
  return this->_vertices[pos];
  #endif
}

inline const vec3& Mesh::operator[](const Mesh::IndexType pos) const {
  #ifdef DEBUG
  return this->_vertices.at(pos);
  #else
  return this->_vertices[pos];
  #endif
}

inline Mesh::IndexType Mesh::add_vertex(const CoordType x, const CoordType y,
                                        const CoordType z) noexcept {
  return add_vertex(vec3(x, y, z));
}

inline Mesh::IndexType Mesh::add_vertex(const vec3& v) noexcept {
  _vertices.push_back(v);

  return _vertices.size() - 1;
}

inline void Mesh::add_faces(const initializer_list<array<IndexType, 3>>& faces)
noexcept {
  for (const array<IndexType, 3>& face : faces) {
    add_face(face[0], face[1], face[2]);
  }
}

inline void Mesh::add_face(const IndexType a, const IndexType b,
                           const IndexType c) noexcept {
  _indices.push_back(a);
  _indices.push_back(b);
  _indices.push_back(c);
}
}
}

#endif // MESH_HPP
