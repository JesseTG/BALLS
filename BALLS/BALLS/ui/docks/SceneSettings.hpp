#ifndef SCENESETTINGS_HPP
#define SCENESETTINGS_HPP

#include "ui_SceneSettings.h"

namespace balls {

class SceneSettings : public QDockWidget {
  Q_OBJECT

public:
  explicit SceneSettings(QWidget* parent = 0);

private:
  Ui::SceneSettings ui;
};
}

#endif // SCENESETTINGS_HPP
