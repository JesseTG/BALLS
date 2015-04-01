#include "mesh/MeshFunction.hpp"

#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>

#include <QDebug>
#include <QtMath>
#include <QVector>

#include "mesh/Mesh.hpp"
#include "mesh/MeshParameter.hpp"
#include "mesh/MeshGenerator.hpp"
#include "util/Util.hpp"


namespace balls {
namespace mesh {
namespace functions {

using std::cos;
using std::max;
using std::min;
using std::sin;
using std::string;
using std::sqrt;
using std::uint64_t;
using std::unordered_map;

const float PHI = (1 + sqrt(5)) / 2.0f;
const float INV_SQRT_2 = 1.0f / sqrt(2);

MeshFunction empty = [](const MeshParameters&) { return Mesh(); };
// NOTE: Anonymous functions like this one ARE IN THE C++ STANDARD

MeshFunction plane = [](const MeshParameters& params) {
  float length = params.at(LENGTH).getFloat();
  float width = params.at(WIDTH).getFloat();

  Mesh mesh;

  mesh.add_vertex(width / 2.0f, -length / 2.0f, 0.0f);
  mesh.add_vertex(width / 2.0f, length / 2.0f, 0.0f);
  mesh.add_vertex(-width / 2.0f, length / 2.0f, 0.0f);
  mesh.add_vertex(-width / 2.0f, -length / 2.0f, 0.0f);

  mesh.add_faces({{1, 2, 0}, {2, 3, 0}});
  return mesh;
};

MeshFunction box = [](const MeshParameters& params) {
  float length = params.at(LENGTH).getFloat();
  float width = params.at(WIDTH).getFloat();
  float height = params.at(HEIGHT).getFloat();

  float hl = length / 2;
  float hw = width / 2;
  float hh = height / 2;

  Mesh mesh;

  mesh.add_vertex(hw, -hl, -hh);
  mesh.add_vertex(hw, -hl, hh);
  mesh.add_vertex(-hw, -hl, hh);
  mesh.add_vertex(-hw, -hl, -hh);
  mesh.add_vertex(hw, hl, -hh);
  mesh.add_vertex(hw, hl, hh);
  mesh.add_vertex(-hw, hl, hh);
  mesh.add_vertex(-hw, hl, -hh);

  mesh.add_faces({{0, 2, 3},
                  {0, 1, 2},
                  {4, 1, 0},
                  {4, 5, 1},
                  {7, 5, 4},
                  {7, 6, 5},
                  {3, 6, 7},
                  {3, 2, 6},
                  {1, 6, 2},
                  {1, 5, 6},
                  {3, 7, 4},
                  {3, 4, 0}});
  // Indices derived from a sketch I made on paper
  return mesh;
};

MeshFunction tetrahedron = [](const MeshParameters& params) {
  float length = params.at(LENGTH).getFloat();

  float hl = length / 2;
  Mesh mesh;

  mesh.add_vertex(hl, hl, hl);
  mesh.add_vertex(hl, -hl, -hl);
  mesh.add_vertex(-hl, hl, -hl);
  mesh.add_vertex(-hl, -hl, hl);

  mesh.add_faces({{0, 1, 2}, {0, 3, 1}, {0, 2, 3}, {2, 1, 3}});

  return mesh;
};


MeshFunction icosahedron = [](const MeshParameters& params) {
  float radius = params.at(RADIUS).getFloat();
  int subdivisions = params.at(SUBDIVISIONS).getInteger();

  Q_ASSERT(subdivisions >= 0);

  Mesh mesh;

  unordered_map<uint64_t, Mesh::IndexType> indices;
  auto makeMidpoint = [&](const Mesh::IndexType p1, const Mesh::IndexType p2) {
    const QVector3D& v1 = mesh[p1];
    const QVector3D& v2 = mesh[p2];
    QVector3D mid = (v1 + v2) / 2.0f;
    mid.normalize();
    return mesh.add_vertex(mid * radius);
  };

  mesh.add_vertex(QVector3D(-1, PHI, 0).normalized() * radius);
  mesh.add_vertex(QVector3D(1, PHI, 0).normalized() * radius);
  mesh.add_vertex(QVector3D(-1, -PHI, 0).normalized() * radius);
  mesh.add_vertex(QVector3D(1, -PHI, 0).normalized() * radius);
  mesh.add_vertex(QVector3D(0, -1, PHI).normalized() * radius);
  mesh.add_vertex(QVector3D(0, 1, PHI).normalized() * radius);
  mesh.add_vertex(QVector3D(0, -1, -PHI).normalized() * radius);
  mesh.add_vertex(QVector3D(0, 1, -PHI).normalized() * radius);
  mesh.add_vertex(QVector3D(PHI, 0, -1).normalized() * radius);
  mesh.add_vertex(QVector3D(PHI, 0, 1).normalized() * radius);
  mesh.add_vertex(QVector3D(-PHI, 0, -1).normalized() * radius);
  mesh.add_vertex(QVector3D(-PHI, 0, 1).normalized() * radius);

  vector<array<Mesh::IndexType, 3>> faces({{0, 11, 5},
                                           {0, 5, 1},
                                           {0, 1, 7},
                                           {0, 7, 10},
                                           {0, 10, 11},
                                           {1, 5, 9},
                                           {5, 11, 4},
                                           {11, 10, 2},
                                           {10, 7, 6},
                                           {7, 1, 8},
                                           {3, 9, 4},
                                           {3, 4, 2},
                                           {3, 2, 6},
                                           {3, 6, 8},
                                           {3, 8, 9},
                                           {4, 9, 5},
                                           {2, 4, 11},
                                           {6, 2, 10},
                                           {8, 6, 7},
                                           {9, 8, 1}});


  for (int i = 0; i < subdivisions; ++i) {
    decltype(faces) faces1;
    for (const array<Mesh::IndexType, 3>& face : faces) {

      Mesh::IndexType a = makeMidpoint(face[0], face[1]);
      Mesh::IndexType b = makeMidpoint(face[1], face[2]);
      Mesh::IndexType c = makeMidpoint(face[2], face[0]);

      faces1.push_back({face[0], a, c});
      faces1.push_back({face[1], b, a});
      faces1.push_back({face[2], c, b});
      faces1.push_back({a, b, c});
    }

    faces.swap(faces1);
  }

  for (const array<Mesh::IndexType, 3>& face : faces) {
    mesh.add_face(face[0], face[1], face[2]);
  }

  Q_ASSERT(mesh.indices().size() % 3 == 0);
  return mesh;
};



MeshFunction cylinder = [](const MeshParameters& params) {
  int resolution = params.at(RESOLUTION).getInteger();
  float height = params.at(HEIGHT).getFloat();
  float radius = params.at(RADIUS).getFloat();

  Q_ASSERT(resolution >= 3);

  float hh = height / 2;

  Mesh mesh;

  if (resolution >= 3) {
    Mesh::IndexType topCenter = mesh.add_vertex(0, hh, 0);
    Mesh::IndexType bottomCenter = mesh.add_vertex(0, -hh, 0);
    for (int i = 0; i < resolution; ++i) {
      float angle = (static_cast<float>(i) / resolution) * (2 * M_PI);
      float opp = sin(angle) * radius;
      float adj = cos(angle) * radius;

      mesh.add_vertex(adj, hh, opp);
      mesh.add_vertex(adj, -hh, opp);

      Mesh::IndexType top = ((i + 1) * 2) % ((resolution * 2) + 2);
      Mesh::IndexType topNext = max(2, (top + 2) % ((resolution * 2) + 2));
      Mesh::IndexType bottom = top + 1;
      Mesh::IndexType bottomNext = topNext + 1;

      mesh.add_face(topCenter, topNext, top);
      mesh.add_face(top, bottomNext, bottom);
      mesh.add_face(top, topNext, bottomNext);
      mesh.add_face(bottomCenter, bottom, bottomNext);
    }
  }

  return mesh;
};

MeshFunction cone = [](const MeshParameters& params) {
  int resolution = params.at(RESOLUTION).getInteger();
  float height = params.at(HEIGHT).getFloat();
  float radius = params.at(RADIUS).getFloat();

  Q_ASSERT(resolution >= 3);

  float hh = height / 2;

  Mesh mesh;

  if (resolution >= 3) {
    Mesh::IndexType topCenter = mesh.add_vertex(0, hh, 0);
    Mesh::IndexType bottomCenter = mesh.add_vertex(0, -hh, 0);
    for (int i = 0; i < resolution; ++i) {
      float angle = (static_cast<float>(i) / resolution) * (2 * M_PI);
      float opp = sin(angle) * radius;
      float adj = cos(angle) * radius;

      Mesh::IndexType index = mesh.add_vertex(adj, -hh, opp);

      Mesh::IndexType v = i + 2;
      Mesh::IndexType vNext = max(2, (v + 1) % (resolution + 2));

      mesh.add_face(topCenter, vNext, v);
      mesh.add_face(bottomCenter, v, vNext);
    }
  }

  return mesh;
};

MeshFunction uvsphere = [](const MeshParameters& params) {
  int u_samples = params.at(U_SAMPLES).getInteger();
  int v_samples = params.at(V_SAMPLES).getInteger();
  float x_scl = params.at(X_SCALE).getFloat();
  float y_scl = params.at(Y_SCALE).getFloat();
  float z_scl = params.at(Z_SCALE).getFloat();

  Mesh mesh;

  for (int t = 0; t < u_samples; t++) {
    float theta1 = (static_cast<float>(t) / u_samples) * M_PI;
    float theta2 = (static_cast<float>(t + 1) / u_samples) * M_PI;

    float st1 = sin(theta1), st2 = sin(theta2);
    float ct1 = cos(theta1), ct2 = cos(theta2);
    for (int p = 0; p < v_samples; p++) {
      float phi1 = (static_cast<float>(p) / v_samples) * 2 * M_PI;
      float phi2 = (static_cast<float>(p + 1) / v_samples) * 2 * M_PI;

      float sp1 = sin(phi1), sp2 = sin(phi2);
      float cp1 = cos(phi1), cp2 = cos(phi2);

      auto v1 = mesh.add_vertex(x_scl * st1 * cp1, y_scl * st1 * sp1, z_scl * ct1);
      auto v2 = mesh.add_vertex(x_scl * st1 * cp2, y_scl * st1 * sp2, z_scl * ct1);
      auto v3 = mesh.add_vertex(x_scl * st2 * cp2, y_scl * st2 * sp2, z_scl * ct2);
      auto v4 = mesh.add_vertex(x_scl * st2 * cp1, y_scl * st2 * sp1, z_scl * ct2);

      if (t == 0) {
        mesh.add_face(v1, v4, v3);
      } else if (t + 1 == u_samples) {
        mesh.add_face(v3, v2, v1);
      } else {
        mesh.add_face(v1, v4, v2);
        mesh.add_face(v2, v4, v3);
      }
    }
  }

  return mesh;
};

MeshFunction torus = [](const MeshParameters& params) {

  float major_radius = params.at(OUTER_RADIUS).getFloat();
  float minor_radius = params.at(INNER_RADIUS).getFloat();
  int u_samples = params.at(U_SAMPLES).getInteger();
  int v_samples = params.at(V_SAMPLES).getInteger();

  Mesh mesh;
  auto f = [](float R, float r, float su, float cu, float sv, float cv) {
    return QVector3D((R + r * cv) * cu, (R + r * cv) * su, r * sv);
  };

  for (int u = 0; u < u_samples; u++) {
    float u1 = 2 * M_PI * u / u_samples;
    float u2 = 2 * M_PI * (u + 1) / u_samples;

    float cu1 = cos(u1), cu2 = cos(u2);
    float su1 = sin(u1), su2 = sin(u2);
    for (int v = 0; v < v_samples; v++) {
      float v1 = 2 * M_PI * v / v_samples;
      float v2 = 2 * M_PI * (v + 1) / v_samples;

      float cv1 = cos(v1), cv2 = cos(v2);
      float sv1 = sin(v1), sv2 = sin(v2);
      auto i1 = mesh.add_vertex(f(major_radius, minor_radius, su1, cu1, sv1, cv1));
      auto i2 = mesh.add_vertex(f(major_radius, minor_radius, su2, cu2, sv1, cv1));
      auto i3 = mesh.add_vertex(f(major_radius, minor_radius, su2, cu2, sv2, cv2));
      auto i4 = mesh.add_vertex(f(major_radius, minor_radius, su1, cu1, sv2, cv2));

      mesh.add_face(i1, i2, i3);
      mesh.add_face(i3, i4, i1);
    }
  }

  return mesh;
};
}
}
}
