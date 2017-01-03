#include "precompiled.hpp"
#include "model/gl/Hints.hpp"

#include <QOpenGLFunctions_3_1>

namespace balls {

Hints::Hints(OpenGLPointers& gl, QObject* parent)
  : OpenGLState(gl, parent),
    m_fragmentDerivative(HintMode::DontCare),
    m_lineSmooth(HintMode::DontCare),
    m_polygonSmooth(HintMode::DontCare),
    m_textureCompression(HintMode::DontCare) {
  Q_ASSUME(m_gl.gl31 != nullptr);
}

void Hints::setFragmentDerivative(HintMode hint) noexcept {
  m_fragmentDerivative = hint;
  m_gl.gl31Current()->glHint(
    GL_FRAGMENT_SHADER_DERIVATIVE_HINT, m_fragmentDerivative);
}

void Hints::setLineSmooth(HintMode hint) noexcept {
  m_lineSmooth = hint;
  m_gl.gl31Current()->glHint(GL_LINE_SMOOTH_HINT, m_lineSmooth);
}

void Hints::setPolygonSmooth(HintMode hint) noexcept {
  m_polygonSmooth = hint;
  m_gl.gl31Current()->glHint(GL_POLYGON_SMOOTH_HINT, m_polygonSmooth);
}

void Hints::setTextureCompression(HintMode hint) noexcept {
  m_textureCompression = hint;
  m_gl.gl31Current()->glHint(GL_TEXTURE_COMPRESSION_HINT, m_textureCompression);
}
}
