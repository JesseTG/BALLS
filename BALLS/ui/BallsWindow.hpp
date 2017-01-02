#ifndef BALLSWINDOW_HPP
#define BALLSWINDOW_HPP

#include "ui_BallsWindow.h"

#include <QtGlobal>
#include <random>

#include "config/ProjectConfig.hpp"
#include "model/Meshes.hpp"
#include "model/Uniforms.hpp"
#include "shader/ShaderUniform.hpp"

class QsciLexerGLSL;
class QErrorMessage;
class QFileDialog;
class QSettings;
class QCloseEvent;

namespace balls {

using std::random_device;
using std::default_random_engine;
using std::uniform_real_distribution;

class BallsWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit BallsWindow(QWidget* parent = 0) noexcept;
  ~BallsWindow();

  Q_DECL_DEPRECATED config::ProjectConfig getProjectConfig() const noexcept;
public slots:
  //  void setMesh(const int) noexcept;
  void saveProject() noexcept;
  void loadProject();
protected /* events */:
  void closeEvent(QCloseEvent*) override;

private /* members */:
  Ui::BallsWindow ui;
  bool _generatorsInitialized;

  QSettings* _settings;
private /* UI components/dialogs/etc. */:
  QsciLexerGLSL* _vertLexer;
  QsciLexerGLSL* _fragLexer;
  QsciLexerGLSL* _geomLexer;
  QFileDialog* _save;
  QFileDialog* _load;
  QErrorMessage* _error;

private /* data models */:
  Uniforms m_uniforms;
  Meshes m_meshes;
private slots:
  void _saveProject(const QString&) noexcept;
  void _loadProject(const QString&) noexcept;
  void loadExample() noexcept;

  //  void initializeMeshGenerators() noexcept;
  void forceShaderUpdate() noexcept;
  void reportFatalError(const QString&, const QString&, const int) noexcept;
  void reportWarning(const QString&, const QString&) noexcept;
  void showAboutQt() noexcept;

  // HACK: Must figure out why Qt Designer doesn't see meshManager
  void on_meshManager_meshSelected(const Mesh&);
};
}

#endif // BALLSWINDOW_HPP
