#include "precompiled.hpp"
#include "ui/BallsWindow.hpp"

#include <QMetaEnum>
#include <QtCore/QXmlStreamWriter>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMessageBox>

#include "Constants.hpp"
#include "mesh/MeshFunction.hpp"
#include "mesh/MeshGenerator.hpp"
#include "mesh/Generators.hpp"
#include "util/Util.hpp"
#include "config/ProjectConfig.hpp"

Q_DECLARE_METATYPE(balls::mesh::MeshGenerator*)

namespace balls {

Q_CONSTEXPR QSettings::Scope SCOPE = QSettings::UserScope;
Q_CONSTEXPR QSettings::Format FORMAT = QSettings::NativeFormat;

BallsWindow::BallsWindow(QWidget* parent) Q_DECL_NOEXCEPT
:
QMainWindow(parent),
            _vertHighlighter(this, QOpenGLShader::Vertex),
            _fragHighlighter(this, QOpenGLShader::Fragment),
            _geomHighlighter(this, QOpenGLShader::Geometry),
            _generatorsInitialized(false),
_settings(FORMAT, SCOPE, Constants::AUTHOR_NAME, Constants::APP_NAME, this) {
  ui.setupUi(this);
  _vertHighlighter.setDocument(ui.vertexEditor->document());
  _fragHighlighter.setDocument(ui.fragmentEditor->document());
  _geomHighlighter.setDocument(ui.geometryEditor->document());
  QFile vert(Constants::DEFAULT_VERTEX_PATH);
  QFile frag(Constants::DEFAULT_FRAGMENT_PATH);
  Q_ASSUME(vert.open(QFile::ReadOnly | QFile::Text));
  Q_ASSUME(frag.open(QFile::ReadOnly | QFile::Text));
  // These should refer to internal resources
  QTextStream vv(&vert);
  QTextStream ff(&frag);
  ui.vertexEditor->setPlainText(vv.readAll());
  ui.fragmentEditor->setPlainText(ff.readAll());
}

BallsWindow::~BallsWindow() { _settings.sync(); }

ProjectConfig BallsWindow::getProjectConfig() const Q_DECL_NOEXCEPT {
  ProjectConfig project;
  project.vertexShader = ui.vertexEditor->toPlainText();
  project.fragmentShader = ui.fragmentEditor->toPlainText();
  project.glMajor = ui.canvas->getOpenGLMajor();
  project.glMinor = ui.canvas->getOpenGLMinor();
  return project;
}

void BallsWindow::setMesh(const int index) Q_DECL_NOEXCEPT {
  QVariant var = this->ui.meshComboBox->currentData();
  mesh::MeshGenerator* generator = var.value<mesh::MeshGenerator*>();

  Q_ASSERT(generator != nullptr);
  Q_ASSERT(0 <= index&&  index < ui.meshComboBox->count());
  Q_ASSERT(var.isValid());

  this->ui.canvas->setMesh(generator);

  #ifdef DEBUG
  qDebug() << "Switched to mesh" << generator->getName();
  #endif
}

void BallsWindow::initializeMeshGenerators() Q_DECL_NOEXCEPT {
  using namespace balls::mesh;

  if (!this->_generatorsInitialized) {
    auto _addGenerator = [this](MeshGenerator * gen) Q_DECL_NOEXCEPT {
      QVariant var = QVariant::fromValue(static_cast<MeshGenerator*>(gen));
      ui.meshComboBox->addItem(gen->getName(), var);

      #ifdef DEBUG
      qDebug() << "Added mesh generator" << gen->getName() << "to selector";
      #endif
    };
    _addGenerator(&generators::quad);
    _addGenerator(&generators::box);
    _addGenerator(&generators::tetrahedron);
    _addGenerator(&generators::icosahedron);
    _addGenerator(&generators::sphere80);
    _addGenerator(&generators::sphere320);
    _addGenerator(&generators::icosphere);
    _addGenerator(&generators::cylinder);
    _addGenerator(&generators::cone);
    _addGenerator(&generators::uvsphere);
    _addGenerator(&generators::torus);
    _addGenerator(&generators::ellipsoid);
    this->ui.canvas->updateUniformInfo();
  }

  this->_generatorsInitialized = true;
}

void BallsWindow::forceShaderUpdate() Q_DECL_NOEXCEPT {
  QString vertex = this->ui.vertexEditor->toPlainText();
  QString geometry = this->ui.geometryEditor->toPlainText();
  QString fragment = this->ui.fragmentEditor->toPlainText();
  this->ui.log->clear();

  #ifdef DEBUG
  qDebug() << "Compiling shaders";
  #endif
  this->ui.canvas->makeCurrent();
  this->ui.canvas->updateUniformInfo();

  if (this->ui.canvas->updateShaders(vertex, geometry, fragment)) {
    this->ui.log->appendPlainText("Success");
  }

  else {
    // const QOpenGLShaderProgram& shader = this->ui.canvas->getShader();
    const QOpenGLDebugLogger& log = this->ui.canvas->getLogger();

    // this->ui.log->appendPlainText(shader.log());
    if (log.isLogging()) {
      for (const QOpenGLDebugMessage& message : log.loggedMessages()) {
        qDebug() << message;
        this->ui.log->appendPlainText(message.message());
      }
    }
  }
}

void BallsWindow::saveProject(const QString& path) Q_DECL_NOEXCEPT {
  ProjectConfig project = this->getProjectConfig();
  balls::config::saveToFile(project, path);
}

void BallsWindow::loadProject(const QString& path) {}

void BallsWindow::requestShaderUpdate() Q_DECL_NOEXCEPT {}

void BallsWindow::loadExampleShaders() Q_DECL_NOEXCEPT {
  using namespace Constants;

  QObject* s = sender();
  Q_ASSERT(s != nullptr);
  // This should only be called from a signal
  // TODO: Geometry shaders
  QVariant vert = s->property(VERT_PROPERTY);
  QVariant frag = s->property(FRAG_PROPERTY);

  Q_ASSERT(vert.type() == QVariant::String);
  Q_ASSERT(frag.type() == QVariant::String);

  QString v = SHADER_PREFIX + vert.toString() + '.' + VERT_EXT;
  QString f = SHADER_PREFIX + frag.toString() + '.' + FRAG_EXT;

  #ifdef DEBUG
  qDebug() << "Loading example shaders" << v << "and" << f;
  #endif

  loadShaders(v, "", f);
  forceShaderUpdate();
}

bool BallsWindow::loadShaders(const QString& vert, const QString& geom,
                              const QString& frag) {
  auto load =
    [](const QString & path, const QOpenGLShader::ShaderType type,
  QPlainTextEdit * editor) {
    if (path.isEmpty()) {
      qDebug() << "No need to reload" << type << "shader, empty path given";
      return true;
    }

    QFile file(path);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
      qDebug() << "Failed to load" << type << "shader" << path;
      return false;
    }

    QTextStream stream(&file);
    editor->setPlainText(stream.readAll());
    qDebug() << "Loaded" << type << "shader" << path;
    return true;
  };
  bool success = true;
  success &= load(vert, QOpenGLShader::Vertex, ui.vertexEditor);
  success &= load(frag, QOpenGLShader::Fragment, ui.fragmentEditor);
  return success;
}

void BallsWindow::reportFatalError(const QString& title,
                                   const QString& text,
                                   const int error) Q_DECL_NOEXCEPT {
  QMessageBox::critical(this, title, text);
  qDebug().nospace() << "Exiting with fatal error " << error << ": " << text;
  std::exit(error);
}
void BallsWindow::reportWarning(const QString& title,
                                const QString& text) Q_DECL_NOEXCEPT {
  QMessageBox::warning(this, title, text);
  qWarning() << text;
}

void BallsWindow::showAboutQt() Q_DECL_NOEXCEPT {
  QMessageBox::aboutQt(this, "About Qt");
}
}
