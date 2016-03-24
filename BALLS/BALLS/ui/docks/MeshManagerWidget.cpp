#include "precompiled.hpp"

#include "ui/docks/MeshManagerWidget.hpp"
#include "shader/ShaderUniform.hpp"

namespace balls {

MeshManagerWidget::MeshManagerWidget(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  ui.meshProperties->registerCustomPropertyCB(shader::createShaderProperty);

  ui.createMeshButton->addActions({
      ui.actionBox, ui.actionCapsule, ui.actionCone, ui.actionCylinder,
      ui.actionDisk, ui.actionTube,
  });

  ui.actionBox->setData(QVariant::fromValue(Mesh::Type::Box));
  ui.actionCapsule->setData(QVariant::fromValue(Mesh::Type::Capsule));
  ui.actionCone->setData(QVariant::fromValue(Mesh::Type::Cone));
  ui.actionCylinder->setData(QVariant::fromValue(Mesh::Type::Cylinder));
  ui.actionDisk->setData(QVariant::fromValue(Mesh::Type::Disk));
  ui.actionTube->setData(QVariant::fromValue(Mesh::Type::Tube));
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
