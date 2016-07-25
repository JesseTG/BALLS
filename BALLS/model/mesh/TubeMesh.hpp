#ifndef TUBEMESH_HPP
#define TUBEMESH_HPP

#include <QObject>

#include "model/mesh/BaseCylindricalMesh.hpp"

namespace balls {

class TubeMesh : public BaseCylindricalMesh {
  Q_OBJECT

  Q_PROPERTY(double innerRadius MEMBER m_innerRadius WRITE setInnerRadius FINAL)
  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)
  Q_PROPERTY(bool capped MEMBER m_capped WRITE setCapped FINAL)

public:
  TubeMesh(QObject* parent = nullptr);

protected /* methods */:
  void assignMesh() override;

private /* members */:
  unsigned int m_rings;
  double m_innerRadius;
  bool m_capped;

private /* setters */:
  void setRings(unsigned int);
  void setInnerRadius(double);
  void setCapped(bool);
};
}

Q_DECLARE_METATYPE(balls::TubeMesh*)

#endif // TUBEMESH_HPP
