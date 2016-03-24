#ifndef CAPPEDCONEMESH_HPP
#define CAPPEDCONEMESH_HPP

#include <QObject>

#include "model/mesh/BaseCylindricalMesh.hpp"

namespace balls {

class CappedConeMesh : public BaseCylindricalMesh
{
  Q_OBJECT

  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)

public:
  CappedConeMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  unsigned int m_rings;

private /* setters */:
  void setRings(unsigned int);
};
}

Q_DECLARE_METATYPE(balls::CappedConeMesh*)
#endif // CAPPEDCONEMESH_HPP
