#ifndef BALLSWINDOW_HPP
#define BALLSWINDOW_HPP

#include "ui_BallsWindow.h"

#include "ui/GLSLHighlighter.hpp"

#include <QTimer>

namespace balls {

using ui::GLSLHighlighter;

class BallsWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit BallsWindow(QWidget* parent = 0) noexcept;

public slots:
  void setMesh(const int) noexcept;

private /* members */:
  Ui::BallsWindow ui;
  bool _generatorsInitialized;
  GLSLHighlighter _vertHighlighter;
  GLSLHighlighter _fragHighlighter;
  GLSLHighlighter _geomHighlighter;
  QTimer _shaderUpdate;

private slots:
  void initializeMeshGenerators() noexcept;
  void requestShaderUpdate() noexcept;
  void forceShaderUpdate() noexcept;
};
}

#endif // BALLSWINDOW_HPP
