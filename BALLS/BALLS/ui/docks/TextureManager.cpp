#include "precompiled.hpp"

#include "ui/docks/TextureManager.hpp"
#include "model/ImageTexture.hpp"

#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>

#include "util/Logging.hpp"

namespace balls {

TextureManager::TextureManager(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  ui.createTextureButton->addActions(
      {ui.actionFrom_Image, ui.actionFrom_Gradient});
}

void TextureManager::loadImage() {
  qDebug() << "Loading an image texture";

  QString imagePath = QFileDialog::getOpenFileName(
      this, tr("Load Texture"),
      QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0],
      tr("Images (*.png *.xpm *.jpg)"));

  if (!imagePath.isNull()) {
    // If the user picked an image...
    QImage image(imagePath);
    QPixmap pixmap = QPixmap::fromImage(image);

    ImageTexture* texture = new ImageTexture(image);
    QListWidgetItem* item = new QListWidgetItem();

    item->setData(Qt::DisplayRole, imagePath);
    item->setData(Qt::UserRole, QVariant::fromValue(static_cast<QObject*>(texture)));

    ui.textureList->addItem(item);

    this->ui.imageLabel->setPixmap(pixmap);
    qDebug() << "Loaded image" << imagePath;
  }
}
}

void balls::TextureManager::on_textureList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
  QObject* subject = current->data(Qt::UserRole).value<QObject*>();
  if (subject) {
    qDebug() << "Displaying image" << current->data(Qt::DisplayRole).toString();
    ui.textureProperties->setObject(subject);
  }
}
