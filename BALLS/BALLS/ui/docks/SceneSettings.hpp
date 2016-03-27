#ifndef SCENESETTINGS_HPP
#define SCENESETTINGS_HPP

#include <QWidget>
#include "ui_SceneSettings.h"

class QOpenGLContext;

namespace balls {

class BallsCanvas;

class Q_DECL_DEPRECATED SceneSettings : public QWidget {
  Q_OBJECT

public:
  explicit SceneSettings(QWidget* parent = 0);

private:
  friend class BallsWindow; // HACK: restructure properly later
  Ui::SceneSettings ui;

  void initCanvas(BallsCanvas* canvas);
};
}

#endif // SCENESETTINGS_HPP
