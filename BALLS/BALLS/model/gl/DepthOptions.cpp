#include "precompiled.hpp"
#include "model/gl/DepthOptions.hpp"

#include <QOpenGLFunctions_3_0>

namespace balls {

DepthOptions::DepthOptions(OpenGLPointers& gl, QObject* parent)
  : QObject(parent),
    m_gl(gl),
    m_testEnabled(false),
    m_clampEnabled(false),
    m_clearDepth(1.0f),
    m_depthFunction(DepthFunction::Less),
    m_depthNear(0.0f),
    m_depthFar(1.0f),
    m_depthMask(true) {
  // Defaults as defined by OpenGL
  Q_ASSUME(m_gl.gl30 != nullptr);
}

void DepthOptions::setTestEnabled(bool enabled) noexcept {
  m_testEnabled = enabled;

  if (m_testEnabled) {
    m_gl.gl30->glEnable(GL_DEPTH_TEST);
  } else {
    m_gl.gl30->glDisable(GL_DEPTH_TEST);
  }
}

void DepthOptions::setClampEnabled(bool enabled) noexcept {
  m_clampEnabled = enabled;

  if (m_clampEnabled) {
    m_gl.gl30->glEnable(GL_DEPTH_CLAMP);
  } else {
    m_gl.gl30->glDisable(GL_DEPTH_CLAMP);
  }
}

void DepthOptions::setClearDepth(float clear) noexcept {
  m_clearDepth = clear;

  m_gl.gl30->glClearDepth(m_clearDepth);
}

void DepthOptions::setDepthFunction(DepthFunction function) noexcept {
  m_depthFunction = function;

  m_gl.gl30->glDepthFunc(m_depthFunction);
}

void DepthOptions::setDepthMask(bool mask) noexcept {
  m_depthMask = mask;

  m_gl.gl30->glDepthMask(m_depthMask);
}

void DepthOptions::setDepthNear(float near) noexcept {
  m_depthNear = near;

  updateDepthRange();
}

void DepthOptions::setDepthFar(float far) noexcept {
  m_depthFar = far;

  updateDepthRange();
}

void DepthOptions::updateDepthRange() noexcept {

  m_gl.gl30->glDepthRange(m_depthNear, m_depthFar);
}
}