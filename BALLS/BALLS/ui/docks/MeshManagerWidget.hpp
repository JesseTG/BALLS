#ifndef MESHMANAGERWIDGET_HPP
#define MESHMANAGERWIDGET_HPP

#include <QWidget>
#include "ui_MeshManager.h"
#include "model/Meshes.hpp"

namespace balls {

class MeshManagerWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MeshManagerWidget(QWidget *parent = 0);

  void setMeshModel(Meshes* meshes) {
    m_meshes = meshes;
  }

signals:
  void meshCreated(const Mesh&);
  void meshSelected(const Mesh&);

private slots:
  void on_meshList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *);

  void on_createMeshButton_triggered(QAction *arg1);

  void on_meshList_itemChanged(QListWidgetItem *item);

private /* fields */:
  Ui::MeshManager ui;
  QPointer<Meshes> m_meshes;
};
}

#endif // MESHMANAGERWIDGET_HPP
