#ifndef SPHERICALTRIANGLEMESH_HPP
#define SPHERICALTRIANGLEMESH_HPP

#include <QObject>

#include "model/mesh/BaseSphereMesh.hpp"

namespace balls {

// TODO: Provide a variant that allows arbitrary vertices
class SphericalTriangleMesh : public BaseSphereMesh {
  Q_OBJECT

public:
  explicit SphericalTriangleMesh(QObject* parent = nullptr);

protected /* methods */:
  void assignMesh() override;
};
}

Q_DECLARE_METATYPE(balls::SphericalTriangleMesh*)

#endif // SPHERICALTRIANGLEMESH_HPP
