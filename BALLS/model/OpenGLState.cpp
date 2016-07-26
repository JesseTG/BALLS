#include "precompiled.hpp"
#include "model/OpenGLState.hpp"

#include <QOpenGLFunctions_3_0>

namespace balls {

OpenGLState::OpenGLState(OpenGLPointers& pointers, QObject* parent)
  : QObject(parent), m_gl(pointers) {
  Q_ASSUME(m_gl.gl30 != nullptr);
}

bool OpenGLState::hasGl31() const noexcept {
  return m_gl.gl31 != nullptr;
}

bool OpenGLState::hasGl32() const noexcept {
  return m_gl.gl32 != nullptr;
}

bool OpenGLState::hasGl33() const noexcept {
  return m_gl.gl33 != nullptr;
}

bool OpenGLState::hasGl40() const noexcept {
  return m_gl.gl40 != nullptr;
}

bool OpenGLState::hasGl41() const noexcept {
  return m_gl.gl41 != nullptr;
}

bool OpenGLState::hasGl42() const noexcept {
  return m_gl.gl42 != nullptr;
}

bool OpenGLState::hasGl43() const noexcept {
  return m_gl.gl43 != nullptr;
}

bool OpenGLState::hasGl44() const noexcept {
  return m_gl.gl44 != nullptr;
}

bool OpenGLState::hasGl45() const noexcept {
  return m_gl.gl45 != nullptr;
}

void OpenGLState::setGlFeature(bool enabled, GLenum feature) {
  if (enabled) {
    m_gl.gl30Current()->glEnable(feature);
  } else {
    m_gl.gl30Current()->glDisable(feature);
  }
}
}
