#include "precompiled.hpp"
#include "ui/docks/MeshManagerWidget.hpp"

#include "Constants.hpp"
#include "shader/ShaderUniform.hpp"

namespace balls {

MeshManagerWidget::MeshManagerWidget(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  ui.meshProperties->setNameFilter(constants::regex::NAME_FILTER);
  ui.meshProperties->registerCustomPropertyCB(shader::createShaderProperty);

  ui.createMeshButton->addActions(
    {
      ui.actionBox,
      ui.actionCapsule,
      ui.actionCone,
      ui.actionCylinder,
      ui.actionDisk,
      ui.actionDodecahedron,
      ui.actionIcosahedron,
      ui.actionIcosphere,
      ui.actionPlane,
      ui.actionRounded_Box,
      ui.actionSphere,
      ui.actionSpherical_Cone,
      ui.actionSpherical_Triangle,
      ui.actionSpring,
      ui.actionTorus,
      ui.actionTorus_Knot,
      ui.actionTriangle,
      ui.actionTube,
    });

  ui.actionBox->setData(QVariant::fromValue(Mesh::Type::Box));
  ui.actionCapsule->setData(QVariant::fromValue(Mesh::Type::Capsule));
  ui.actionCone->setData(QVariant::fromValue(Mesh::Type::Cone));
  ui.actionCylinder->setData(QVariant::fromValue(Mesh::Type::Cylinder));
  ui.actionDisk->setData(QVariant::fromValue(Mesh::Type::Disk));
  ui.actionDodecahedron->setData(QVariant::fromValue(Mesh::Type::Dodecahedron));
  ui.actionIcosahedron->setData(QVariant::fromValue(Mesh::Type::Icosahedron));
  ui.actionIcosphere->setData(QVariant::fromValue(Mesh::Type::IcoSphere));
  ui.actionPlane->setData(QVariant::fromValue(Mesh::Type::Plane));
  ui.actionRounded_Box->setData(QVariant::fromValue(Mesh::Type::RoundedBox));
  ui.actionSphere->setData(QVariant::fromValue(Mesh::Type::Sphere));
  ui.actionSpherical_Cone->setData(
    QVariant::fromValue(Mesh::Type::SphericalCone));
  ui.actionSpherical_Triangle->setData(
    QVariant::fromValue(Mesh::Type::SphericalTriangle));
  ui.actionSpring->setData(QVariant::fromValue(Mesh::Type::Spring));
  ui.actionTorus->setData(QVariant::fromValue(Mesh::Type::Torus));
  ui.actionTorus_Knot->setData(QVariant::fromValue(Mesh::Type::TorusKnot));
  ui.actionTriangle->setData(QVariant::fromValue(Mesh::Type::Triangle));
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

  item->setFlags(constants::RESOURCE_FLAGS);

  item->setData(Qt::DisplayRole, mesh.objectName());
  item->setData(Qt::UserRole, QVariant::fromValue(static_cast<Mesh *>(&mesh)));

  ui.meshList->addItem(item);
  this->meshCreated(mesh);
}

/// Renames a Mesh object when a user changes its name in the editor
void balls::MeshManagerWidget::on_meshList_itemChanged(QListWidgetItem *item) {
  QVariant mesh = item->data(Qt::UserRole);
  if (mesh.isValid()) {
    Mesh *meshPtr = mesh.value<Mesh *>();

    QVariant name = item->data(Qt::DisplayRole);
    meshPtr->setObjectName(name.toString());
  }
}
