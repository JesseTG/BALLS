#include "precompiled.hpp"

#include "ui/docks/MeshManagerWidget.hpp"
#include "shader/ShaderUniform.hpp"

namespace balls {

MeshManagerWidget::MeshManagerWidget(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  ui.meshProperties->registerCustomPropertyCB(shader::createShaderProperty);

  ui.createMeshButton->addActions({ui.actionBox, ui.actionCapped_Cone,
                                   ui.actionCapped_Cylinder,
                                   ui.actionCapped_Tube, ui.actionCapsule});

  ui.actionBox->setData(QVariant::fromValue(Mesh::Type::Box));
  ui.actionCapped_Cone->setData(QVariant::fromValue(Mesh::Type::CappedCone));
  ui.actionCapped_Cylinder->setData(
      QVariant::fromValue(Mesh::Type::CappedCylinder));
  ui.actionCapped_Tube->setData(QVariant::fromValue(Mesh::Type::CappedTube));
  ui.actionCapsule->setData(QVariant::fromValue(Mesh::Type::Capsule));
}
}

void balls::MeshManagerWidget::on_meshList_currentItemChanged(
    QListWidgetItem *current, QListWidgetItem *) {
  Mesh *subject = current->data(Qt::UserRole).value<Mesh *>();
  if (subject) {
    qDebug() << "Displaying mesh" << current->data(Qt::DisplayRole).toString();
    ui.meshProperties->setObject(subject);
    ui.meshProperties->update();
    this->meshSelected(*subject);
  }
}

void balls::MeshManagerWidget::on_createMeshButton_triggered(QAction *arg1) {
  qDebug() << arg1;
  Mesh::Type type = arg1->data().value<Mesh::Type>();

  Mesh &mesh = m_meshes->createMesh(type);

  QListWidgetItem *item = new QListWidgetItem();

  item->setData(Qt::DisplayRole, arg1->objectName());
  item->setData(Qt::UserRole, QVariant::fromValue(static_cast<Mesh *>(&mesh)));

  ui.meshList->addItem(item);
  this->meshCreated(mesh);
}
