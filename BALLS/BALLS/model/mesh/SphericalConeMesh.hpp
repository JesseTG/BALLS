#ifndef SPHERICALCONEMESH_HPP
#define SPHERICALCONEMESH_HPP

#include <QObject>

#include "model/mesh/BaseCylindricalMesh.hpp"

namespace balls {

class SphericalConeMesh : public BaseCylindricalMesh {
  Q_OBJECT

  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)

public:
  SphericalConeMesh(QObject* parent = nullptr);

protected /* methods */:
  void assignMesh() override;

private /* members */:
  unsigned int m_rings;

private /* setters */:
  void setRings(unsigned int);
};
}

Q_DECLARE_METATYPE(balls::SphericalConeMesh*)

#endif // SPHERICALCONEMESH_HPP
