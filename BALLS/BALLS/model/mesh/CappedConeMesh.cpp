#include "precompiled.hpp"

#include "model/mesh/CappedConeMesh.hpp"
#include "Constants.hpp"

#include <generator/CappedConeMesh.hpp>

namespace balls {
/*
 * 		double radius = 1.0,
        double size = 1.0,
        unsigned slices = 32u,
        unsigned segments = 8u,
        unsigned rings = 4u,
        double start = 0.0,
        double sweep = gml::radians(360.0)
        */
CappedConeMesh::CappedConeMesh(QObject *parent)
    : MeshMesh(parent, Type::CappedCone), m_radius(1.0), m_size(1.0),
      m_slices(32u), m_segments(8u), m_rings(4u), m_start(0.0),
      m_sweep(360.0) {
  updateMesh();
}

void CappedConeMesh::setRadius(double radius) {
  if (glm::epsilonNotEqual(radius, m_radius, constants::EPSILON)) {
    // If the user actually adjusted the radius...
    m_radius = radius;
    updateMesh();
  }
}

void CappedConeMesh::setSize(double size) {
  if (glm::epsilonNotEqual(size, m_size, constants::EPSILON)) {
    // If the user actually adjusted the size...
    m_size = size;
    updateMesh();
  }
}

void CappedConeMesh::setSlices(unsigned int slices) {
  if (slices != m_slices) {
    // If the user actually adjusted the number of slices...
    m_slices = slices;
    updateMesh();
  }
}

void CappedConeMesh::setSegments(unsigned int segments) {
  if (segments != m_segments) {
    // If the user actually adjusted the number of segments...
    m_segments = segments;
    updateMesh();
  }
}

void CappedConeMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void CappedConeMesh::setStart(double start) {
  if (glm::epsilonNotEqual(start, m_start, constants::EPSILON)) {
    // If the user actually adjusted the start of the arc...
    m_start = start;
    updateMesh();
  }
}

void CappedConeMesh::setSweep(double sweep) {
  if (glm::epsilonNotEqual(sweep, m_sweep, constants::EPSILON)) {
    // If the user actually adjusted the sweep interval...
    m_sweep = sweep;
    updateMesh();
  }
}

void CappedConeMesh::assignMesh() {
  m_mesh = generator::CappedConeMesh(m_radius, m_size, m_slices, m_segments,
                                     m_rings, glm::radians(m_start), glm::radians(m_sweep));
}
}
