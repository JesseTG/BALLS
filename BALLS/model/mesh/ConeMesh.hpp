#ifndef CONEMESH_HPP
#define CONEMESH_HPP

#include <QObject>

#include "model/mesh/BaseCylindricalMesh.hpp"

namespace balls {

class ConeMesh : public BaseCylindricalMesh {
  Q_OBJECT

  Q_PROPERTY(uint rings MEMBER m_rings WRITE setRings FINAL)
  Q_PROPERTY(bool capped MEMBER m_capped WRITE setCapped FINAL)

public:
  explicit ConeMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
private /* members */:
  unsigned int m_rings;
  bool m_capped;

private /* setters */:
  void setRings(unsigned int);
  void setCapped(bool);
};
}

Q_DECLARE_METATYPE(balls::ConeMesh*)
#endif // CONEMESH_HPP
