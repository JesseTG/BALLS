#include "ui/BallsWindow.hpp"
#include "mesh/MeshFunction.hpp"
#include "mesh/MeshGenerator.hpp"
#include "mesh/Generators.hpp"

#include <QComboBox>
#include <QPointer>
#include <QString>
#include <QVariant>

Q_DECLARE_METATYPE(balls::mesh::MeshGenerator*)

namespace balls {

void _addGenerator(Ui::BallsWindow&, mesh::MeshGenerator*) noexcept;

BallsWindow::BallsWindow(QWidget* parent) noexcept : QMainWindow(parent),
                                                     _vertHighlighter(this),
                                                     _fragHighlighter(this),
                                                     _geomHighlighter(this),
                                                     _generatorsInitialized(false) {
  ui.setupUi(this);

  _vertHighlighter.setDocument(ui.vertexEditor->document());
  _fragHighlighter.setDocument(ui.fragmentEditor->document());
  _geomHighlighter.setDocument(ui.geometryEditor->document());

  QFile vert(":/shader/default.vert"), frag(":/shader/default.frag");
  Q_ASSUME(vert.open(QFile::ReadOnly | QFile::Text));
  Q_ASSUME(frag.open(QFile::ReadOnly | QFile::Text));

  QTextStream vv(&vert);
  QTextStream ff(&frag);

  ui.vertexEditor->setPlainText(vv.readAll());
  ui.fragmentEditor->setPlainText(ff.readAll());
}

void BallsWindow::setMesh(const int index) noexcept {
  QVariant var = this->ui.meshComboBox->currentData();
  mesh::MeshGenerator* generator = var.value<mesh::MeshGenerator*>();

  Q_ASSERT(generator);
  Q_ASSERT(0 <= index && index < ui.meshComboBox->count());

  this->ui.canvas->setMesh(generator);

#ifdef DEBUG
  qDebug().nospace() << "Switched to mesh \"" << generator->getName().c_str() << '"';
#endif
}

void BallsWindow::initializeMeshGenerators() noexcept {
  using namespace balls::mesh;
  if (!this->_generatorsInitialized) {
    _addGenerator(this->ui, &generators::plane);
    _addGenerator(this->ui, &generators::box);
    _addGenerator(this->ui, &generators::tetrahedron);
    _addGenerator(this->ui, &generators::icosahedron);
    _addGenerator(this->ui, &generators::sphere80);
    _addGenerator(this->ui, &generators::sphere320);
    _addGenerator(this->ui, &generators::icosphere);
    _addGenerator(this->ui, &generators::cylinder);
    _addGenerator(this->ui, &generators::cone);
    _addGenerator(this->ui, &generators::uvsphere);
    _addGenerator(this->ui, &generators::torus);
    _addGenerator(this->ui, &generators::ellipsoid);
  }

  this->_generatorsInitialized = true;
}

void BallsWindow::forceShaderUpdate() noexcept {
  QString vertex = this->ui.vertexEditor->toPlainText();
  QString geometry = this->ui.geometryEditor->toPlainText();
  QString fragment = this->ui.fragmentEditor->toPlainText();
  this->ui.log->clear();

#ifdef DEBUG
  qDebug() << "User requested compile";
#endif
  this->ui.canvas->makeCurrent();
  if (this->ui.canvas->updateShaders(vertex, geometry, fragment)) {
    this->ui.log->appendPlainText("Success");
  } else {
    QOpenGLShaderProgram& shader = this->ui.canvas->getShader();
    QOpenGLDebugLogger& log = this->ui.canvas->getLogger();

    // this->ui.log->appendPlainText(shader.log());
    if (log.isLogging()) {
      for (const QOpenGLDebugMessage& message : log.loggedMessages()) {
        qDebug() << message;

        if (message.source() == QOpenGLDebugMessage::ShaderCompilerSource) {
          this->ui.log->appendPlainText(message.message());
        }
      }
    }
  }
}

void BallsWindow::requestShaderUpdate() noexcept {}

void _addGenerator(Ui::BallsWindow& window, mesh::MeshGenerator* gen) noexcept {
  QVariant var = QVariant::fromValue(static_cast<mesh::MeshGenerator*>(gen));
  window.meshComboBox->addItem(gen->getName().c_str(), var);

#ifdef DEBUG
  qDebug().nospace() << "Added mesh generator \"" << gen->getName().c_str()
                     << "\" to selector";
#endif
}
}
