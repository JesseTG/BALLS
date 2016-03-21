#ifndef CAPPEDCONEMESH_HPP
#define CAPPEDCONEMESH_HPP

#include <QObject>
#include <generator/CappedConeMesh.hpp>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

class CappedConeMesh : public MeshMesh
{
  Q_OBJECT

  Q_PROPERTY(double radius MEMBER m_radius WRITE setRadius FINAL)
  Q_PROPERTY(double size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(uint segments MEMBER m_segments WRITE setSegments FINAL)
  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)
  Q_PROPERTY(double start MEMBER m_start WRITE setStart FINAL)
  Q_PROPERTY(double sweep MEMBER m_sweep WRITE setSweep FINAL)

public:
  CappedConeMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  double m_radius;
  double m_size;
  unsigned int m_slices;
  unsigned int m_segments;
  unsigned int m_rings;
  double m_start;

  // Stored in degrees, but passed to mesh generator in radians
  double m_sweep;

private /* setters */:
  void setRadius(double);
  void setSize(double);
  void setSlices(unsigned int);
  void setSegments(unsigned int);
  void setRings(unsigned int);
  void setStart(double);
  void setSweep(double);
};
}

#endif // CAPPEDCONEMESH_HPP
