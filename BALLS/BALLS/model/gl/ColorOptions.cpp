#include "precompiled.hpp"
#include "model/gl/ColorOptions.hpp"

#include <QOpenGLFunctions_3_0>

namespace balls {

ColorOptions::ColorOptions(OpenGLPointers& gl, QObject* parent)
  : OpenGLState(gl, parent),
    m_logicOpEnabled(false),
    m_clampColor(false),
    m_dithering(true),
    m_clearColor(0, 0, 0, 0),
    m_colorMask(true, true, true, true),
    m_logicOp(LogicOperation::Copy) {
  // ^ As defined in the OpenGL specs (GL_DITHER is true by default, all other
  // glGet()s are false by default)
  Q_ASSUME(m_gl.gl30 != nullptr);
}

void ColorOptions::setLogicOpEnabled(bool enabled) noexcept {
  m_logicOpEnabled = enabled;

  setGlFeature(m_logicOpEnabled, GL_COLOR_LOGIC_OP);
}

void ColorOptions::setClampColor(bool clamp) noexcept {
  m_clampColor = clamp;

  m_gl.gl30Current()->glClampColor(GL_CLAMP_READ_COLOR, m_clampColor);
}

void ColorOptions::setClearColor(const QColor& color) noexcept {
  m_clearColor = color;

  m_gl.gl30Current()->glClearColor(
    color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void ColorOptions::setColorMask(const bvec4& mask) noexcept {
  m_colorMask = mask;

  m_gl.gl30Current()->glColorMask(mask.r, mask.g, mask.b, mask.a);
}

void ColorOptions::setLogicOperation(LogicOperation operation) noexcept {
  m_logicOp = operation;

  m_gl.gl30Current()->glLogicOp(m_logicOp);
}

void ColorOptions::setDithering(bool dithering) noexcept {
  m_dithering = dithering;

  setGlFeature(m_dithering, GL_DITHER);
}
}
