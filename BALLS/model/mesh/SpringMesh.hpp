#ifndef SPRINGMESH_HPP
#define SPRINGMESH_HPP

#include <QObject>

#include "model/mesh/MeshMesh.hpp"

namespace balls {

class SpringMesh : public MeshMesh {
  Q_OBJECT

  Q_PROPERTY(double minor MEMBER m_minor WRITE setMinor FINAL)
  Q_PROPERTY(double major MEMBER m_major WRITE setMajor FINAL)
  Q_PROPERTY(double size MEMBER m_size WRITE setSize FINAL)
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(uint segments MEMBER m_segments WRITE setSegments FINAL)
  Q_PROPERTY(double minorStart MEMBER m_minorStart WRITE setMinorStart FINAL)
  Q_PROPERTY(double minorSweep MEMBER m_minorSweep WRITE setMinorSweep FINAL)
  Q_PROPERTY(double majorStart MEMBER m_majorStart WRITE setMajorStart FINAL)
  Q_PROPERTY(double majorSweep MEMBER m_majorSweep WRITE setMajorSweep FINAL)

public:
  SpringMesh(QObject* parent = nullptr);

protected /* methods */:
  void assignMesh() override;

private /* members */:
  double m_minor;
  double m_major;
  double m_size;
  unsigned int m_slices;
  unsigned int m_segments;
  double m_minorStart;
  double m_minorSweep;
  double m_majorStart;
  double m_majorSweep;

private /* setters */:
  void setMinor(double);
  void setMajor(double);
  void setSize(double);
  void setSlices(unsigned int);
  void setSegments(unsigned int);
  void setMinorStart(double);
  void setMinorSweep(double);
  void setMajorStart(double);
  void setMajorSweep(double);
};
}

Q_DECLARE_METATYPE(balls::SpringMesh*)

#endif // SPRINGMESH_HPP
