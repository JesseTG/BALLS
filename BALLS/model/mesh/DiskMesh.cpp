#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/DiskMesh.hpp"

#include <generator/DiskMesh.hpp>

namespace balls {
DiskMesh::DiskMesh(QObject *parent) : MeshMesh(parent, Type::Disk) {
  m_radius = 1.0;
  m_innerRadius = 0.0;
  m_slices = 32u;
  m_rings = 4u;
  m_start = 0.0;
  m_sweep = 360.0;
  updateMesh();
}

void DiskMesh::setRadius(double radius) {
  if (glm::epsilonNotEqual(radius, m_radius, constants::EPSILON)) {
    // If the user actually adjusted the radius...
    m_radius = radius;
    updateMesh();
  }
}

void DiskMesh::setInnerRadius(double innerRadius) {
  if (glm::epsilonNotEqual(innerRadius, m_innerRadius, constants::EPSILON)) {
    // If the user actually adjusted the inner radius...
    m_innerRadius = innerRadius;
    updateMesh();
  }
}

void DiskMesh::setSlices(unsigned int slices) {
  if (slices != m_slices) {
    // If the user actually adjusted the number of slices...
    m_slices = slices;
    updateMesh();
  }
}

void DiskMesh::setRings(unsigned int rings) {
  if (rings != m_rings) {
    // If the user actually adjusted the number of rings...
    m_rings = rings;
    updateMesh();
  }
}

void DiskMesh::setStart(double start) {
  if (glm::epsilonNotEqual(start, m_start, constants::EPSILON)) {
    // If the user actually adjusted the start of the arc...
    m_start = start;
    updateMesh();
  }
}

void DiskMesh::setSweep(double sweep) {
  if (glm::epsilonNotEqual(sweep, m_sweep, constants::EPSILON)) {
    // If the user actually adjusted the sweep interval...
    m_sweep = sweep;
    updateMesh();
  }
}

void DiskMesh::assignMesh() {
  m_mesh = generator::DiskMesh(
    m_radius,
    m_innerRadius,
    m_slices,
    m_rings,
    glm::radians(m_start),
    glm::radians(m_sweep));
}
}
