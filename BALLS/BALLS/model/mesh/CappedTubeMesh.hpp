#ifndef CAPPEDTUBEMESH_HPP
#define CAPPEDTUBEMESH_HPP

#include <QObject>

#include "model/mesh/BaseCylindricalMesh.hpp"

namespace balls {

class CappedTubeMesh : public BaseCylindricalMesh
{
  Q_OBJECT

  Q_PROPERTY(double innerRadius MEMBER m_innerRadius WRITE setInnerRadius FINAL)
  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)

public:
  CappedTubeMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  unsigned int m_rings;
  double m_innerRadius;

private /* setters */:
  void setRings(unsigned int);
  void setInnerRadius(double);
};
}

Q_DECLARE_METATYPE(balls::CappedTubeMesh*)

#endif // CAPPEDTUBEMESH_HPP
