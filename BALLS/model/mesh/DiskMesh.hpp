#ifndef DISKMESH_HPP
#define DISKMESH_HPP

#include <QObject>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

class DiskMesh : public MeshMesh {
  Q_OBJECT

  Q_PROPERTY(double radius MEMBER m_radius WRITE setRadius FINAL)
  Q_PROPERTY(double innerRadius MEMBER m_innerRadius WRITE setInnerRadius FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)
  Q_PROPERTY(double start MEMBER m_start WRITE setStart FINAL)
  Q_PROPERTY(double sweep MEMBER m_sweep WRITE setSweep FINAL)

public:
  explicit DiskMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  double m_radius;
  double m_innerRadius;
  unsigned int m_slices;
  unsigned int m_rings;

  // Stored in degrees, but passed to mesh generator in radians
  double m_start;
  double m_sweep;

private /* setters */:
  void setRadius(double);
  void setInnerRadius(double);
  void setSlices(unsigned int);
  void setRings(unsigned int);
  void setStart(double);
  void setSweep(double);
};
}

Q_DECLARE_METATYPE(balls::DiskMesh*)

#endif // DISKMESH_HPP
