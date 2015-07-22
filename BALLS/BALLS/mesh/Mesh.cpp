#include "precompiled.hpp"
#include "mesh/Mesh.hpp"

namespace balls {
namespace mesh {

using std::vector;

vector<Mesh::CoordType> Mesh::combined() noexcept {
  _computeNormals();

  Q_ASSERT(_vertices.size() == _normals.size());

  vector<CoordType> buffer;
  buffer.reserve(_vertices.size() * 6);
  // ^ *2 because vertices and normals, *3 because x, y, z

  for (auto i = 0u; i < _vertices.size(); ++i) {
    #ifdef DEBUG
    const vec3& v = _vertices.at(i);
    const vec3& n = _normals.at(i);
    #else
    const vec3& v = _vertices[i];
    const vec3& n = _normals[i];
    #endif
    buffer.push_back(v.x);
    buffer.push_back(v.y);
    buffer.push_back(v.z);
    buffer.push_back(n.x);
    buffer.push_back(n.y);
    buffer.push_back(n.z);
  }

  return buffer;
}

void Mesh::_computeNormals() noexcept {
  Q_ASSERT(_indices.size() % 3 == 0);

  _normals = vector<vec3>(_vertices.size(), vec3());

  // To silence sign-compare warnings
  for (auto i = 0u; i < _indices.size(); i += 3) {
    #ifdef DEBUG
    IndexType i1 = _indices.at(i);
    IndexType i2 = _indices.at(i + 1);
    IndexType i3 = _indices.at(i + 2);
    const vec3& v1 = _vertices.at(i1);
    const vec3& v2 = _vertices.at(i2);
    const vec3& v3 = _vertices.at(i3);

    vec3 normal = glm::triangleNormal(v1, v2, v3);
    _normals.at(i1) += normal;
    _normals.at(i2) += normal;
    _normals.at(i3) += normal;
    #else
    IndexType i1 = _indices[i];
    IndexType i2 = _indices[i + 1];
    IndexType i3 = _indices[i + 2];
    const vec3& v1 = _vertices[i1];
    const vec3& v2 = _vertices[i2];
    const vec3& v3 = _vertices[i3];

    vec3 normal = glm::triangleNormal(v1, v2, v3);
    _normals[i1] += normal;
    _normals[i2] += normal;
    _normals[i3] += normal;
    #endif
  }

  for (vec3& n : _normals) {
    n = glm::normalize(n);
  }
}
}
}
