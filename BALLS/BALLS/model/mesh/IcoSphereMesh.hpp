#ifndef ICOSPHEREMESH_HPP
#define ICOSPHEREMESH_HPP

#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

class IcoSphereMesh : public BaseSphereMesh
{
  Q_OBJECT

  Q_CLASSINFO("segments", "minimum=1;")

public:
  IcoSphereMesh(QObject* parent = nullptr);
protected /* methods */:
  void assignMesh() override;
};
}

Q_DECLARE_METATYPE(balls::IcoSphereMesh*)

#endif // ICOSPHEREMESH_HPP
