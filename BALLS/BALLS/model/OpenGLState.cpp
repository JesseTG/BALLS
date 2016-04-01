#include "precompiled.hpp"
#include "model/OpenGLState.hpp"

namespace balls {

OpenGLState::OpenGLState(OpenGLPointers& context, QObject* parent)
  : QObject(parent), m_gl(context) {}

void OpenGLState::ensureContext() {
  bool success = m_gl.context->makeCurrent(m_gl.context->surface());

  if (!success) {
    throw std::runtime_error("Cannot make the window context current");
  }
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
  return false;
  // TODO: Upgrade Qt version
}

bool OpenGLState::hasGl45() const noexcept {
  return false;
  // TODO: Upgrade Qt version
}
}
