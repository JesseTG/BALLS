#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <QWidget>
#include "ui_TextureManager.h"

namespace Ui {
class TextureManager;
}

class TextureManager : public QWidget
{
  Q_OBJECT

public:
  explicit TextureManager(QWidget *parent = 0);

private:
  Ui::TextureManager ui;
};

#endif // TEXTUREMANAGER_HPP
