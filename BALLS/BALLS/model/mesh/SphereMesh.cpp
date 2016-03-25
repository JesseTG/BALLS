#include "precompiled.hpp"

#include "model/mesh/SphereMesh.hpp"
#include "Constants.hpp"

#include <generator/SphereMesh.hpp>

namespace balls {
SphereMesh::SphereMesh(QObject *parent) : BaseSphereMesh(parent, Type::Sphere) {
  m_radius = 1.0;
  m_slices = 32u;
  m_segments = 16u;
  m_sliceStart = 0.0;
  m_sliceSweep = 360.0;
  m_segmentStart = 0.0;
  m_segmentSweep = 180.0;

  updateMesh();
}

void SphereMesh::setSlices(unsigned int slices) {
  if (slices != m_slices) {
    // If the user actually adjusted the number of slices...
    m_slices = slices;
    updateMesh();
  }
}

void SphereMesh::setSliceStart(double sliceStart) {
  if (glm::epsilonNotEqual(sliceStart, m_sliceStart, constants::EPSILON)) {
    // If the user actually adjusted the start of the slice arc...
    m_sliceStart = sliceStart;
    updateMesh();
  }
}

void SphereMesh::setSliceSweep(double sliceSweep) {
  if (glm::epsilonNotEqual(sliceSweep, m_sliceSweep, constants::EPSILON)) {
    // If the user actually adjusted the sweep of the slice arc...
    m_sliceSweep = sliceSweep;
    updateMesh();
  }
}

void SphereMesh::setSegmentStart(double segmentStart) {
  if (glm::epsilonNotEqual(segmentStart, m_segmentStart, constants::EPSILON)) {
    // If the user actually adjusted the start of the segment arc...
    m_segmentStart = segmentStart;
    updateMesh();
  }
}

void SphereMesh::setSegmentSweep(double segmentSweep) {
  if (glm::epsilonNotEqual(segmentSweep, m_segmentSweep, constants::EPSILON)) {
    // If the user actually adjusted the sweep of the segment arc...
    m_segmentSweep = segmentSweep;
    updateMesh();
  }
}

void SphereMesh::assignMesh() {
  m_mesh = generator::SphereMesh(
      m_radius, m_slices, m_segments, glm::radians(m_sliceStart),
      glm::radians(m_sliceSweep), glm::radians(m_segmentStart),
      glm::radians(m_segmentSweep));
}
}
