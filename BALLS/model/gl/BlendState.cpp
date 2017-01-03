#include "precompiled.hpp"
#include "model/gl/BlendState.hpp"

#include <QOpenGLFunctions_3_1>

namespace balls {

BlendState::BlendState(OpenGLPointers& gl, QObject* parent)
  : OpenGLState(gl, parent),
    m_enabled(false),
    m_blendRgb(BlendEquation::Add),
    m_blendAlpha(BlendEquation::Add),
    m_srcRgb(BlendFunction::One),
    m_dstRgb(BlendFunction::Zero),
    m_srcAlpha(BlendFunction::One),
    m_dstAlpha(BlendFunction::Zero) {
  Q_ASSUME(m_gl.gl31 != nullptr);
}
//  ^ Defaults specified in OpenGL

void BlendState::setEnabled(bool enabled) noexcept {
  m_enabled = enabled;

  setGlFeature(m_enabled, GL_BLEND);
}

void BlendState::setBlendColor(const QColor& color) noexcept {
  m_blendColor = color;

  m_gl.gl31Current()->glBlendColor(
    color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void BlendState::setBlendRgb(BlendEquation equation) noexcept {
  m_blendRgb = equation;

  updateEquation();
}

void BlendState::setBlendAlpha(BlendEquation equation) noexcept {
  m_blendAlpha = equation;

  updateEquation();
}

void BlendState::setSrcRgb(BlendFunction function) noexcept {
  m_srcRgb = function;

  updateFunction();
}

void BlendState::setDstRgb(BlendFunction function) noexcept {
  m_dstRgb = function;

  updateFunction();
}

void BlendState::setSrcAlpha(BlendFunction function) noexcept {
  m_srcAlpha = function;

  updateFunction();
}

void BlendState::setDstAlpha(BlendFunction function) noexcept {
  m_dstAlpha = function;

  updateFunction();
}

void BlendState::updateEquation() noexcept {
  m_gl.gl31Current()->glBlendEquationSeparate(m_blendRgb, m_blendAlpha);
}

void BlendState::updateFunction() noexcept {
  m_gl.gl31Current()->glBlendFuncSeparate(
    m_srcRgb, m_dstRgb, m_srcAlpha, m_dstAlpha);
}
}
