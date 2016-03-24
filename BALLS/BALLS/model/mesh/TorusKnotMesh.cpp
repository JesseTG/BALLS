#include "precompiled.hpp"

#include "model/mesh/TorusKnotMesh.hpp"
#include "Constants.hpp"

#include <generator/TorusKnotMesh.hpp>

namespace balls {

TorusKnotMesh::TorusKnotMesh(QObject *parent)
    : MeshMesh(parent, Type::TorusKnot), m_p(2), m_q(3), m_slices(8u),
      m_segments(96u) {
  updateMesh();
}

void TorusKnotMesh::setP(int p) {
  if (m_p != p) {
    // If the user actually adjusted p...
    m_p = p;
    updateMesh();
  }
}

void TorusKnotMesh::setQ(int q) {
  if (m_q != q) {
    // If the user actually adjusted q...
    m_q = q;
    updateMesh();
  }
}

void TorusKnotMesh::setSlices(unsigned int slices) {
  if (m_slices != slices) {
    // If the user actually adjusted the slice resolution...
    m_slices = slices;
    updateMesh();
  }
}

void TorusKnotMesh::setSegments(unsigned int segments) {
  if (m_segments != segments) {
    // If the user actually adjusted the segment resolution...
    m_segments = segments;
    updateMesh();
  }
}

void TorusKnotMesh::assignMesh() {
  m_mesh = generator::TorusKnotMesh(m_p, m_q, m_slices, m_segments);
}
}
