#ifndef BALLSWINDOW_HPP
#define BALLSWINDOW_HPP

#include "ui_BallsWindow.h"

#include <random>
#include <unordered_map>

#include <QtGlobal>
#include <QSettings>
#include <QTimer>

#include "config/ProjectConfig.hpp"
#include "shader/ShaderUniform.hpp"
#include "ui/glslhighlighter.hpp"

namespace balls {

using std::random_device;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::unordered_map;

class BallsWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit BallsWindow(QWidget* parent = 0) Q_DECL_NOEXCEPT;
  ~BallsWindow();

  ProjectConfig getProjectConfig() const Q_DECL_NOEXCEPT;
public slots:
  void setMesh(const int) Q_DECL_NOEXCEPT;
  void saveProject(const QString&) Q_DECL_NOEXCEPT;
  void loadProject(const QString&);
private /* members */:
  Ui::BallsWindow ui;
  GlslHighlighter _vertHighlighter;
  GlslHighlighter _fragHighlighter;
  GlslHighlighter _geomHighlighter;

  QTimer _shaderUpdate;
  bool _generatorsInitialized;

  QSettings _settings;
private /* methods */:
  bool loadShaders(const QString&, const QString&, const QString&);
private slots:
  void loadExampleShaders() Q_DECL_NOEXCEPT;

  void initializeMeshGenerators() Q_DECL_NOEXCEPT;
  void requestShaderUpdate() Q_DECL_NOEXCEPT;
  void forceShaderUpdate() Q_DECL_NOEXCEPT;
  void reportFatalError(const QString&, const QString&,
                        const int) Q_DECL_NOEXCEPT;
  void reportWarning(const QString&, const QString&) Q_DECL_NOEXCEPT;
  void showAboutQt() Q_DECL_NOEXCEPT;
};
}

#endif // BALLSWINDOW_HPP
