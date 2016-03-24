#ifndef BASECYLINDRICALMESH_HPP
#define BASECYLINDRICALMESH_HPP

#include <QObject>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

class BaseCylindricalMesh : public MeshMesh
{
  Q_OBJECT

  Q_PROPERTY(double radius MEMBER m_radius WRITE setRadius FINAL)
  Q_PROPERTY(double size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(uint segments MEMBER m_segments WRITE setSegments FINAL)
  Q_PROPERTY(double start MEMBER m_start WRITE setStart FINAL)
  Q_PROPERTY(double sweep MEMBER m_sweep WRITE setSweep FINAL)

public:
  virtual ~BaseCylindricalMesh() {}
protected /* constructors */:
  using MeshMesh::MeshMesh;
protected /* members */:
  double m_radius;
  double m_size;
  unsigned int m_slices;
  unsigned int m_segments;
  double m_start;

  // Stored in degrees, but passed to mesh generator in radians
  double m_sweep;

private /* setters */:
  void setRadius(double);
  void setSize(double);
  void setSlices(unsigned int);
  void setSegments(unsigned int);
  void setStart(double);
  void setSweep(double);
};
}

#endif // BASECYLINDRICALMESH_HPP
