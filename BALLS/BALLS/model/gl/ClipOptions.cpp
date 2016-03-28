#include "precompiled.hpp"
#include "model/gl/ClipOptions.hpp"

#include <QOpenGLFunctions_3_0>

namespace balls {

using std::array;

ClipOptions::ClipOptions(OpenGLPointers& gl, QObject* parent)
  : QObject(parent),
    m_gl(gl),
    m_scissorEnabled(false),
    m_viewportPosition(0, 0),
    m_scissorPosition(0, 0),
    m_origin(ClipControlOrigin::LowerLeft),
    m_depth(ClipControlDepth::NegativeOneToOne) {
  Q_ASSUME(m_gl.gl30 != nullptr);
}

uvec2 ClipOptions::viewportSize() noexcept {
  array<GLsizei, 4> viewport;
  m_gl.gl30->glGetIntegerv(GL_VIEWPORT, viewport.data());

  return {viewport[2], viewport[3]};
}

uvec2 ClipOptions::scissorSize() noexcept {
  array<GLsizei, 4> scissor;
  m_gl.gl30->glGetIntegerv(GL_SCISSOR_BOX, scissor.data());

  return {scissor[2], scissor[3]};
}

void ClipOptions::setViewportPosition(const ivec2& position) noexcept {
  m_viewportPosition = position;

  uvec2 size = viewportSize();

  m_gl.gl30->glViewport(position.x, position.y, size.x, size.y);
}

void ClipOptions::setViewportSize(const uvec2& size) noexcept {
  m_gl.gl30->glViewport(
    m_viewportPosition.x, m_viewportPosition.y, size.x, size.y);
}

void ClipOptions::setScissorPosition(const ivec2& position) noexcept {
  m_scissorPosition = position;

  uvec2 size = scissorSize();

  m_gl.gl30->glScissor(position.x, position.y, size.x, size.y);
}

void ClipOptions::setScissorSize(const uvec2& size) noexcept {
  m_gl.gl30->glScissor(
    m_scissorPosition.x, m_scissorPosition.y, size.x, size.y);
}

void ClipOptions::setScissorEnabled(bool enabled) noexcept {
  m_scissorEnabled = enabled;

  if (m_scissorEnabled) {
    m_gl.gl30->glEnable(GL_SCISSOR_TEST);
  } else {
    m_gl.gl30->glDisable(GL_SCISSOR_TEST);
  }
}

void ClipOptions::setOrigin(ClipControlOrigin origin) noexcept {
  m_origin = origin;

  glClipControl(m_origin, m_depth);
}

void ClipOptions::setDepth(ClipControlDepth depth) noexcept {
  m_depth = depth;

  glClipControl(m_origin, m_depth);
}
}
