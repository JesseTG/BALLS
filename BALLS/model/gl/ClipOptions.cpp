#include "precompiled.hpp"
#include "model/gl/ClipOptions.hpp"

#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLFunctions_4_5_Core>

namespace balls {

using std::array;

ClipOptions::ClipOptions(OpenGLPointers& gl, QObject* parent)
  : OpenGLState(gl, parent),
    m_scissorEnabled(false),
    m_viewportPosition(0, 0),
    m_scissorPosition(0, 0),
    m_origin(ClipControlOrigin::LowerLeft),
    m_depth(ClipControlDepth::NegativeOneToOne) {
  Q_ASSUME(m_gl.gl30 != nullptr);
}

uvec2 ClipOptions::viewportSize() noexcept {
  array<GLsizei, 4> viewport;
  m_gl.gl30Current()->glGetIntegerv(GL_VIEWPORT, viewport.data());

  return {viewport[2], viewport[3]};
}

uvec2 ClipOptions::scissorSize() noexcept {
  array<GLsizei, 4> scissor;
  m_gl.gl30Current()->glGetIntegerv(GL_SCISSOR_BOX, scissor.data());

  return {scissor[2], scissor[3]};
}

void ClipOptions::setViewportPosition(const ivec2& position) noexcept {
  m_viewportPosition = position;

  uvec2 size = viewportSize();

  m_gl.gl30Current()->glViewport(position.x, position.y, size.x, size.y);
}

void ClipOptions::setScissorPosition(const ivec2& position) noexcept {
  m_scissorPosition = position;

  uvec2 size = scissorSize();

  m_gl.gl30Current()->glScissor(position.x, position.y, size.x, size.y);
}

void ClipOptions::setScissorSize(const uvec2& size) noexcept {
  m_gl.gl30Current()->glScissor(
    m_scissorPosition.x, m_scissorPosition.y, size.x, size.y);
}

void ClipOptions::setScissorEnabled(bool enabled) noexcept {
  m_scissorEnabled = enabled;

  setGlFeature(m_scissorEnabled, GL_SCISSOR_TEST);
}

void ClipOptions::setOrigin(ClipControlOrigin origin) noexcept {
  m_origin = origin;

  if (hasGl45()) {
    m_gl.gl45Current()->glClipControl(m_origin, m_depth);
  }
}

void ClipOptions::setDepth(ClipControlDepth depth) noexcept {
  m_depth = depth;

  if (hasGl45()) {
    m_gl.gl45Current()->glClipControl(m_origin, m_depth);
  }
}
}
