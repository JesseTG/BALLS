#ifndef CAPSULEMESH_HPP
#define CAPSULEMESH_HPP

#include <QObject>

#include "model/mesh/BaseCylindricalMesh.hpp"

namespace balls {

class CapsuleMesh : public BaseCylindricalMesh {
  Q_OBJECT

  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)

public:
  explicit CapsuleMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  unsigned int m_rings;

private /* setters */:
  void setRings(unsigned int);
};
}

Q_DECLARE_METATYPE(balls::CapsuleMesh*)

#endif // CAPSULEMESH_HPP
