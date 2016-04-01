#include "precompiled.hpp"
#include "model/gl/StencilOptions.hpp"

#include <QOpenGLFunctions_3_0>

namespace balls {

StencilOptions::StencilOptions(OpenGLPointers& gl, QObject* parent)
  : OpenGLState(gl, parent),
    m_stencilEnabled(false),
    m_clearStencil(0),
    m_frontStencilMask(0xFFFFFFFF),
    m_backStencilMask(0xFFFFFFFF),
    m_frontStencilFail(StencilAction::Keep),
    m_frontStencilPassDepthFail(StencilAction::Keep),
    m_frontStencilPassDepthPass(StencilAction::Keep),
    m_backStencilFail(StencilAction::Keep),
    m_backStencilPassDepthFail(StencilAction::Keep),
    m_backStencilPassDepthPass(StencilAction::Keep),
    m_frontStencilFunction(StencilFunction::Always),
    m_frontStencilRef(0),
    m_frontStencilValueMask(0xFFFFFFFF),
    m_backStencilFunction(StencilFunction::Always),
    m_backStencilRef(0),
    m_backStencilValueMask(0xFFFFFFFF) {}


void StencilOptions::setStencilEnabled(bool enabled) noexcept {
  m_stencilEnabled = enabled;

  if (m_stencilEnabled) {
    m_gl.gl30->glEnable(GL_STENCIL_TEST);
  } else {
    m_gl.gl30->glDisable(GL_STENCIL_TEST);
  }
}

void StencilOptions::setClearStencil(int clearStencil) noexcept {
  m_clearStencil = clearStencil;

  m_gl.gl30->glClearStencil(m_clearStencil);
}

void StencilOptions::setFrontStencilMask(unsigned int frontMask) noexcept {
  m_frontStencilMask = frontMask;

  m_gl.gl30->glStencilMaskSeparate(GL_FRONT, m_frontStencilMask);
}

void StencilOptions::setBackStencilMask(unsigned int backMask) noexcept {
  m_backStencilMask = backMask;

  m_gl.gl30->glStencilMaskSeparate(GL_BACK, m_backStencilMask);
}

void StencilOptions::setFrontStencilFail(StencilAction act) noexcept {
  m_frontStencilFail = act;

  m_gl.gl30->glStencilOpSeparate(
    GL_FRONT,
    m_frontStencilFail,
    m_frontStencilPassDepthFail,
    m_frontStencilPassDepthPass);
}

void StencilOptions::setFrontStencilPassDepthFail(StencilAction act) noexcept {
  m_frontStencilPassDepthFail = act;

  m_gl.gl30->glStencilOpSeparate(
    GL_FRONT,
    m_frontStencilFail,
    m_frontStencilPassDepthFail,
    m_frontStencilPassDepthPass);
}

void StencilOptions::setFrontStencilPassDepthPass(StencilAction act) noexcept {
  m_frontStencilPassDepthPass = act;

  m_gl.gl30->glStencilOpSeparate(
    GL_FRONT,
    m_frontStencilFail,
    m_frontStencilPassDepthFail,
    m_frontStencilPassDepthPass);
}

void StencilOptions::setBackStencilFail(StencilAction act) noexcept {
  m_backStencilFail = act;

  m_gl.gl30->glStencilOpSeparate(
    GL_BACK,
    m_backStencilFail,
    m_backStencilPassDepthFail,
    m_backStencilPassDepthPass);
}

void StencilOptions::setBackStencilPassDepthFail(StencilAction act) noexcept {
  m_backStencilPassDepthFail = act;

  m_gl.gl30->glStencilOpSeparate(
    GL_BACK,
    m_backStencilFail,
    m_backStencilPassDepthFail,
    m_backStencilPassDepthPass);
}

void StencilOptions::setBackStencilPassDepthPass(StencilAction act) noexcept {
  m_backStencilPassDepthPass = act;

  m_gl.gl30->glStencilOpSeparate(
    GL_BACK,
    m_backStencilFail,
    m_backStencilPassDepthFail,
    m_backStencilPassDepthPass);
}

void StencilOptions::setFrontStencilFunction(StencilFunction func) noexcept {
  m_frontStencilFunction = func;

  m_gl.gl30->glStencilFuncSeparate(
    GL_FRONT,
    m_frontStencilFunction,
    m_frontStencilRef,
    m_frontStencilValueMask);
}

void StencilOptions::setFrontStencilRef(int ref) noexcept {
  m_frontStencilRef = ref;

  m_gl.gl30->glStencilFuncSeparate(
    GL_FRONT,
    m_frontStencilFunction,
    m_frontStencilRef,
    m_frontStencilValueMask);
}

void StencilOptions::setFrontStencilValueMask(unsigned int mask) noexcept {
  m_frontStencilValueMask = mask;

  m_gl.gl30->glStencilFuncSeparate(
    GL_FRONT,
    m_frontStencilFunction,
    m_frontStencilRef,
    m_frontStencilValueMask);
}

void StencilOptions::setBackStencilFunction(StencilFunction func) noexcept {
  m_backStencilFunction = func;

  m_gl.gl30->glStencilFuncSeparate(
    GL_BACK, m_backStencilFunction, m_backStencilRef, m_backStencilValueMask);
}

void StencilOptions::setBackStencilRef(int ref) noexcept {
  m_backStencilRef = ref;

  m_gl.gl30->glStencilFuncSeparate(
    GL_BACK, m_backStencilFunction, m_backStencilRef, m_backStencilValueMask);
}

void StencilOptions::setBackStencilValueMask(unsigned int mask) noexcept {
  m_backStencilValueMask = mask;

  m_gl.gl30->glStencilFuncSeparate(
    GL_BACK, m_backStencilFunction, m_backStencilRef, m_backStencilValueMask);
}
}
