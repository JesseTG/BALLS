#include "precompiled.hpp"

#include "ui/docks/TextureManager.hpp"

TextureManager::TextureManager(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);

  ui.createTextureButton->addActions(
      {ui.actionFrom_Image, ui.actionFrom_Gradient});
}
