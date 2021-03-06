#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP

#include <memory>
#include <vector>

#include <QObject>
#include <QMetaEnum>

#include <generator/AnyMesh.hpp>

#include "model/mesh/Mesh.hpp"

namespace balls {

class Meshes : public QObject {
  Q_OBJECT

public:
  explicit Meshes(QObject* parent = 0);
  virtual ~Meshes() {}

signals:
  void meshRemoved(const Mesh&);

public slots:
  Mesh& createMesh(Mesh::Type) noexcept;
  void removeMesh(int);
  void clear();

private /* fields */:
  std::vector<Mesh*> m_meshes;
  QMetaEnum m_metaEnum;
};
}

#endif // MESHMANAGER_HPP
