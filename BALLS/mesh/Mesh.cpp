#include "mesh/Mesh.hpp"

#include <vector>
#include <QVector3D>

namespace balls {
namespace mesh {

using std::vector;

Mesh::IndexType
 Mesh::add_vertex(const CoordType x, const CoordType y, const CoordType z) noexcept {
  return this->add_vertex(QVector3D(x, y, z));
}

QVector3D& Mesh::operator[](const Mesh::IndexType pos) {
#ifdef DEBUG
  return this->_vertices.at(pos);
// at() has bounds-checking, operator[] doesn't
#else
  return this->_vertices[pos];
#endif
}

const QVector3D& Mesh::operator[](const Mesh::IndexType pos) const {
#ifdef DEBUG
  return this->_vertices.at(pos);
#else
  return this->_vertices[pos];
#endif
}

Mesh::IndexType Mesh::add_vertex(const QVector3D& v) noexcept {
  this->_vertices.push_back(v);

  return this->_vertices.size() - 1;
}

void Mesh::add_faces(const initializer_list<array<IndexType, 3>>& faces) noexcept {
  for (const array<IndexType, 3>& face : faces) {
    this->add_face(face[0], face[1], face[2]);
  }
}

void Mesh::add_face(const IndexType a, const IndexType b, const IndexType c) noexcept {
  this->_indices.push_back(a);
  this->_indices.push_back(b);
  this->_indices.push_back(c);
}

vector<Mesh::CoordType> Mesh::combined() noexcept {
  this->_computeNormals();

  Q_ASSERT(this->_vertices.size() == this->_normals.size());

  vector<CoordType> buffer;
  buffer.reserve(this->_vertices.size() * 6);
  // ^ *2 because vertices and normals, *3 because x, y, z

  for (auto i = 0; i < this->_vertices.size(); ++i) {
#ifdef DEBUG
    const QVector3D& v = this->_vertices.at(i);
    const QVector3D& n = this->_normals.at(i);
#else
    const QVector3D& v = this->_vertices[i];
    const QVector3D& n = this->_normals[i];
#endif
    buffer.push_back(v.x());
    buffer.push_back(v.y());
    buffer.push_back(v.z());
    buffer.push_back(n.x());
    buffer.push_back(n.y());
    buffer.push_back(n.z());
  }

  return buffer;
}

void Mesh::_computeNormals() noexcept {
  this->_normals = vector<QVector3D>(this->_vertices.size(), QVector3D());

  Q_ASSERT(this->_indices.size() % 3 == 0);

  for (int i = 0; i < this->_indices.size(); i += 3) {
    IndexType i1 = this->_indices.at(i);
    IndexType i2 = this->_indices.at(i + 1);
    IndexType i3 = this->_indices.at(i + 2);

    const QVector3D& v1 = this->_vertices.at(i1);
    const QVector3D& v2 = this->_vertices.at(i2);
    const QVector3D& v3 = this->_vertices.at(i3);

    QVector3D normal = QVector3D::normal(v1, v2, v3);
    this->_normals.at(i1) += normal;
    this->_normals.at(i2) += normal;
    this->_normals.at(i3) += normal;
  }

  for (QVector3D& n : this->_normals) {
    n.normalize();
  }
}
}
}
