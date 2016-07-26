#include "precompiled.hpp"
#include "model/Uniforms.hpp"
#include "util/Logging.hpp"

#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QWheelEvent>

#include "util/ArcBall.hpp"
#include "util/TypeInfo.hpp"
#include "util/Util.hpp"

// TODO Should implement  Qtilities::Core::Interfaces::IModificationNotifier
namespace balls {

constexpr float ZOOM_INTERVAL = 1.0f;

using balls::util::types::info;
using balls::util::resolveGLType;
using balls::util::types::UniformInfo;
using balls::util::types::UniformCollection;

Uniforms::Uniforms(QObject* parent) noexcept
  : QObject(parent),
    _meta(metaObject()),
    _view(glm::translate(vec3(0, 0, -8))),
    _trackball(vec3(0, 0, 0), .8),
    _canvasSize(1, 1),
    _lastCanvasSize(1, 1),
    _farPlane(100),
    _nearPlane(.01f) {
  setFov(glm::radians(45.0f));
  _elapsedTime.start();
}

void Uniforms::receiveUniforms(const UniformCollection& uniforms) noexcept {
  // We must consider three cases:
  // 1: Uniforms that were removed (old - new)
  // 2: Uniforms that were added (new - old)
  // 3: Uniforms we still have (new & old)

  using balls::util::types::info;
  using balls::util::resolveGLType;
  using balls::util::types::UniformInfo;
  using balls::util::types::UniformCollection;
  using std::set_difference;
  using std::set_intersection;

  UniformCollection temp;

  auto cb = _uniformList.cbegin();
  auto ce = _uniformList.cend();
  // It's okay to cache these iterators, as we're not modifying _uniformList

  // First handle discarded uniforms (old - new)
  set_difference(
    cb,
    ce,
    uniforms.cbegin(),
    uniforms.cend(),
    std::inserter(temp, temp.begin()));

  _handleDiscardedUniforms(temp);
  temp.clear();

  // Now handle new uniforms; we have to add these (new - old)
  set_difference(
    uniforms.cbegin(),
    uniforms.cend(),
    cb,
    ce,
    std::inserter(temp, temp.begin()));
  _handleNewUniforms(temp);

  temp.clear();

  // Finally, handle uniforms that still exist, but may have changed type (new &
  // old)
  set_intersection(
    uniforms.cbegin(),
    uniforms.cend(),
    cb,
    ce,
    std::inserter(temp, temp.begin()));

  _handleKeptUniforms(temp);

  this->_uniformList = uniforms;
}

void Uniforms::_handleDiscardedUniforms(
  const UniformCollection& temp) noexcept {
#ifdef DEBUG
  QStringList removed;
#endif

  for (const UniformInfo& i : temp) {
    // For each uniform we're throwing away...
    QByteArray name = i.name.toLocal8Bit();
    const char* name_cstr = name.data();

    if (_meta->indexOfProperty(name_cstr) == -1) {
      // If this is a custom uniform...

      Q_ASSERT(property(name_cstr).isValid());
      this->setProperty(name_cstr, QVariant());
      // Then clear it
      Q_ASSERT(!property(name_cstr).isValid());

#ifdef DEBUG
      removed << i.name;
#endif
    }
  }

#ifdef DEBUG
  qCDebug(logs::uniform::Removed).noquote()
    << (removed.empty() ? "None" : removed.join(", "));
#endif
}

void Uniforms::_handleNewUniforms(const UniformCollection& temp) noexcept {
#ifdef DEBUG
  QStringList added;
#endif

  for (const UniformInfo& i : temp) {
    // For each uniform we're adding...

    QByteArray name = i.name.toLocal8Bit();
    const char* name_cstr = name.data();
    auto qtype = info[i.type].qMetaType;

    if (_meta->indexOfProperty(name_cstr) == -1) {
// If this is a custom uniform...

#ifdef DEBUG
      added << QString("%1(%2)").arg(i.name, QMetaType::typeName(qtype));
#endif

      // Q_ASSERT(!property(name_cstr).isValid());
      this->setProperty(name_cstr, QVariant(qtype, nullptr));
      // Q_ASSERT(property(name_cstr).isValid());
      // Add a default-constructed uniform
    } else {
#if DEBUG
      added
        << QString("%1(built-in %2)").arg(i.name, QMetaType::typeName(qtype));
#endif
    }
  }

#ifdef DEBUG
  qCDebug(logs::uniform::New).noquote()
    << (added.empty() ? "None" : added.join(", "));
#endif
}

void Uniforms::_handleKeptUniforms(const UniformCollection& temp) noexcept {
  qCDebug(logs::uniform::Name) << temp.size() << "uniforms carried over";

  for (const UniformInfo& i : temp) {
    // For each uniform we still have...

    QByteArray name = i.name.toLocal8Bit();
    const char* name_cstr = name.data();

    const util::types::TypeInfo& inf = info[i.type];

    QVariant prop = this->property(name_cstr);

    if (_meta->indexOfProperty(name_cstr) == -1) {
      // If this is a custom uniform...

      if (prop.userType() == inf.qMetaType) {
        // If this uniform still has the same type as before...
        qCDebug(logs::uniform::Name) << "Left" << prop.typeName() << i.name
                                     << "unchanged";
      } else {
        // This uniform is defined with a different type this time...

        if (prop.canConvert(inf.qMetaType)) {
          // If a conversion exists to this new type...
          prop.convert(inf.qMetaType);
        } else {
          prop = QVariant(inf.qMetaType, nullptr);
          // Otherwise, just default-construct a value
        }

        this->setProperty(name_cstr, prop);
        qCDebug(logs::uniform::Name)
          << "Have" << prop.typeName() << i.name << "but it's now a"
          << QMetaType::typeName(info[i.type].qMetaType) << i.name;
      }
    }
  }
}

void Uniforms::resetModelView() noexcept {
  _model = mat4();
  _view = mat4();
}

void Uniforms::setFov(const float fov) noexcept {
  _fov = fov;

  _updateProjection();
}

void Uniforms::_updateProjection() noexcept {
  _projection = glm::perspectiveFov(
    _fov,
    static_cast<float>(_canvasSize.x),
    static_cast<float>(_canvasSize.y + 1),
    _nearPlane,
    _farPlane);

  _trackball.setScreenToTCS(glm::inverse(_projection * _view));
}

bool Uniforms::event(QEvent* e) {
  return QObject::event(e);
}

bool Uniforms::eventFilter(QObject* obj, QEvent* event) {
  switch (event->type()) {
  case QEvent::MouseMove:
    mouseMoveEvent(static_cast<QMouseEvent*>(event));
    return false;

  case QEvent::MouseButtonPress:
    mousePressEvent(static_cast<QMouseEvent*>(event));
    return false;

  case QEvent::Wheel:
    wheelEvent(static_cast<QWheelEvent*>(event));
    return false;

  case QEvent::Resize:
    resizeEvent(static_cast<QResizeEvent*>(event));
    return false;

  default:
    return QObject::eventFilter(obj, event);
  }
}


void Uniforms::mouseMoveEvent(QMouseEvent* e) noexcept {
  this->_lastMousePos = this->_mousePos;

  this->_mousePos.x = e->x();
  this->_mousePos.y = e->y();

  if (e->buttons() & Qt::LeftButton) {
    // If the left mouse button is being held down...
    _trackball.drag(
      vec2(
        (2 * float(_mousePos.x) / _canvasSize.x) - 1.0,
        (2 * float(_canvasSize.y - _mousePos.y) / _canvasSize.y) - 1.0));
    // Map from -1 to 1

    _model = _trackball.getTransformation();
  }
}

void Uniforms::mousePressEvent(QMouseEvent* e) noexcept {

  if (e->buttons() & Qt::LeftButton) {
    // If the left mouse button was just clicked...

    const QPointF& position = e->localPos();
    _trackball.beginDrag(
      vec2(
        (2 * position.x() / _canvasSize.x) - 1.0,
        (2 * (_canvasSize.y - position.y()) / _canvasSize.y) - 1.0));
  }
}

void Uniforms::wheelEvent(QWheelEvent* e) noexcept {
  int delta = e->angleDelta().y();

  _view = glm::translate(
    _view, {0.0f, 0.0f, (delta > 0 ? ZOOM_INTERVAL : -ZOOM_INTERVAL)});
}

void Uniforms::resizeEvent(QResizeEvent* e) noexcept {
  const QSize& size = e->size();
  int w = std::max(1, size.width());
  int h = std::max(1, size.height());

  _canvasSize.x = w;
  _canvasSize.y = h;

  const QSize& lastSize = e->oldSize();
  _lastCanvasSize.x = lastSize.width();
  _lastCanvasSize.y = lastSize.height();

  _updateProjection();
  //_trackball.setBounds(w, h);
}
}
