#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP

#include <vector>
#include <memory>

#include <QObject>
#include <generator/AnyMesh.hpp>

#include "model/mesh/Mesh.hpp"

namespace balls {

class Meshes : public QObject {
  Q_OBJECT
public /* enums */:

public:
  explicit Meshes(QObject *parent = 0);
  virtual ~Meshes() {}

signals:

  void meshRemoved(const Mesh&);

public slots:
  Mesh& createMesh(Mesh::Type) noexcept;
  void removeMesh(int);
  void clear();

private /* fields */:
  std::vector<Mesh*> m_meshes;
};
}

#endif // MESHMANAGER_HPP
