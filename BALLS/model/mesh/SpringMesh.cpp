#include "precompiled.hpp"

#include "Constants.hpp"
#include "model/mesh/SpringMesh.hpp"

#include <generator/SpringMesh.hpp>

namespace balls {

SpringMesh::SpringMesh(QObject *parent)
  : MeshMesh(parent, Type::Spring),
    m_minor(0.25),
    m_major(1.0),
    m_size(1.0),
    m_slices(8u),
    m_segments(32u),
    m_minorStart(0.0),
    m_minorSweep(360.0),
    m_majorStart(0.0),
    m_majorSweep(720.0) {
  updateMesh();
}

void SpringMesh::setMinor(double minor) {
  if (glm::epsilonNotEqual(minor, m_minor, constants::EPSILON)) {
    // If the user actually adjusted the minor...
    m_minor = minor;
    updateMesh();
  }
}

void SpringMesh::setMajor(double major) {
  if (glm::epsilonNotEqual(major, m_major, constants::EPSILON)) {
    // If the user actually adjusted the major...
    m_major = major;
    updateMesh();
  }
}

void SpringMesh::setSize(double size) {
  if (glm::epsilonNotEqual(size, m_size, constants::EPSILON)) {
    // If the user actually adjusted the size...
    m_size = size;
    updateMesh();
  }
}

void SpringMesh::setSlices(unsigned int slices) {
  if (slices != m_slices) {
    // If the user actually adjusted the number of slices...
    m_slices = slices;
    updateMesh();
  }
}

void SpringMesh::setSegments(unsigned int segments) {
  if (segments != m_segments) {
    // If the user actually adjusted the number of segments...
    m_segments = segments;
    updateMesh();
  }
}

void SpringMesh::setMinorStart(double minorStart) {
  if (glm::epsilonNotEqual(minorStart, m_minorStart, constants::EPSILON)) {
    // If the user actually adjusted the minor start...
    m_minorStart = minorStart;
    updateMesh();
  }
}

void SpringMesh::setMinorSweep(double minorSweep) {
  if (glm::epsilonNotEqual(minorSweep, m_minorSweep, constants::EPSILON)) {
    // If the user actually adjusted the minor sweep...
    m_minorSweep = minorSweep;
    updateMesh();
  }
}

void SpringMesh::setMajorStart(double majorStart) {
  if (glm::epsilonNotEqual(majorStart, m_majorStart, constants::EPSILON)) {
    // If the user actually adjusted the major start...
    m_majorStart = majorStart;
    updateMesh();
  }
}

void SpringMesh::setMajorSweep(double majorSweep) {
  if (glm::epsilonNotEqual(majorSweep, m_majorSweep, constants::EPSILON)) {
    // If the user actually adjusted the major sweep...
    m_majorSweep = majorSweep;
    updateMesh();
  }
}

void SpringMesh::assignMesh() {
  m_mesh = generator::SpringMesh(
    m_minor,
    m_major,
    m_size,
    m_slices,
    m_segments,
    glm::radians(m_minorStart),
    glm::radians(m_minorSweep),
    glm::radians(m_majorStart),
    glm::radians(m_majorSweep));
}
}
