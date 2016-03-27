#ifndef BASECYLINDRICALMESH_HPP
#define BASECYLINDRICALMESH_HPP

#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class BaseCylindricalMesh : public BaseSphereMesh {
  Q_OBJECT

  Q_PROPERTY(double size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(double start MEMBER m_start WRITE setStart FINAL)
  Q_PROPERTY(double sweep MEMBER m_sweep WRITE setSweep FINAL)

public:
  virtual ~BaseCylindricalMesh() {}
protected /* constructors */:
  using BaseSphereMesh::BaseSphereMesh;
protected /* members */:
  double m_size;
  unsigned int m_slices;

  // Stored in degrees, but passed to mesh generator in radians
  double m_start;
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
