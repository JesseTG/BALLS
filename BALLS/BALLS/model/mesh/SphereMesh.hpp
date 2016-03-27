#ifndef SPHEREMESH_HPP
#define SPHEREMESH_HPP
#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class SphereMesh : public BaseSphereMesh {
  Q_OBJECT

  // clang-format off
  Q_PROPERTY(uint slices MEMBER m_slices WRITE setSlices FINAL)
  Q_PROPERTY(double sliceStart MEMBER m_sliceStart WRITE setSliceStart FINAL)
  Q_PROPERTY(double sliceSweep MEMBER m_sliceSweep WRITE setSliceSweep FINAL)
  Q_PROPERTY(double segmentStart MEMBER m_segmentStart WRITE setSegmentStart FINAL)
  Q_PROPERTY(double segmentSweep MEMBER m_segmentSweep WRITE setSegmentSweep FINAL)
  // clang-format on

public:
  SphereMesh(QObject* parent = nullptr);

protected /* methods */:
  void assignMesh() override;

private /* members */:
  unsigned int m_slices;
  double m_sliceStart;
  double m_sliceSweep;
  double m_segmentStart;
  double m_segmentSweep;

private /* setters */:
  void setSlices(unsigned int);
  void setSliceStart(double);
  void setSliceSweep(double);
  void setSegmentStart(double);
  void setSegmentSweep(double);
};
}

Q_DECLARE_METATYPE(balls::SphereMesh*)

#endif // SPHEREMESH_HPP
