#include "precompiled.hpp"
#include "ui/docks/SceneSettings.hpp"

namespace balls {

SceneSettings::SceneSettings(QWidget* parent) :
  QDockWidget(parent)
{
  ui.setupUi(this);
}
}
