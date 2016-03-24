#ifndef ICOSPHEREMESH_HPP
#define ICOSPHEREMESH_HPP

#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class IcoSphereMesh : public BaseSphereMesh
{
  Q_OBJECT

public:
  IcoSphereMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
};
}

Q_DECLARE_METATYPE(balls::IcoSphereMesh*)

#endif // ICOSPHEREMESH_HPP
