#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <QWidget>
#include "ui_TextureManager.h"

namespace balls {

class TextureManager : public QWidget {
  Q_OBJECT

public:
  explicit TextureManager(QWidget *parent = nullptr);

private slots:
  void loadImage();
  void on_textureList_currentItemChanged(
    QListWidgetItem *current, QListWidgetItem *previous);

private:
  Ui::TextureManager ui;
};
}
#endif // TEXTUREMANAGER_HPP
