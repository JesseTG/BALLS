#include "precompiled.hpp"

#include "SceneSettings.hpp"

#include <QOpenGLContext>
#include "ui/BallsCanvas.hpp"

namespace balls {

SceneSettings::SceneSettings(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
}

void SceneSettings::initCanvas(BallsCanvas *canvas) {
  connect(
    ui.wireframeCheck, SIGNAL(toggled(bool)), canvas, SLOT(setOption(bool)));
  connect(
    ui.depthTestCheck, SIGNAL(toggled(bool)), canvas, SLOT(setOption(bool)));
  connect(ui.ditherCheck, SIGNAL(toggled(bool)), canvas, SLOT(setOption(bool)));
  connect(
    ui.backfaceCheck, SIGNAL(toggled(bool)), canvas, SLOT(setOption(bool)));
  // ^ HACK: Replace this with a PROPER ui (with a panel for OpenGL state)
}
}
