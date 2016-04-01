#include "precompiled.hpp"
#include "model/gl/SampleOptions.hpp"

#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_4_0_Core>

namespace balls {

SampleOptions::SampleOptions(OpenGLPointers& gl, QObject* parent)
  : QObject(parent),
    m_gl(gl),
    m_sampleCoverage(1.0f),
    m_invertSampleCoverage(false),
    m_sampleAlphaToCoverage(false),
    m_sampleAlphaToOne(false),
    m_sampleCoverageEnabled(false),
    m_sampleShadingEnabled(false),
    m_sampleMaskEnabled(false),
    m_multisample(true),
    m_minSampleShading(1.0f) {}

void SampleOptions::setSampleCoverage(float sampleCoverage) noexcept {
  m_sampleCoverage = sampleCoverage;

  m_gl.gl30->glSampleCoverage(m_sampleCoverage, m_invertSampleCoverage);
}

void SampleOptions::setInvertSampleCoverage(
  bool invertSampleCoverage) noexcept {
  m_invertSampleCoverage = invertSampleCoverage;

  m_gl.gl30->glSampleCoverage(m_sampleCoverage, m_invertSampleCoverage);
}

void SampleOptions::setSampleAlphaToCoverage(bool coverage) noexcept {
  m_sampleAlphaToCoverage = coverage;

  if (m_sampleAlphaToCoverage) {
    m_gl.gl30->glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
  } else {
    m_gl.gl30->glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
  }
}

void SampleOptions::setSampleAlphaToOne(bool sampleAlphaToOne) noexcept {
  m_sampleAlphaToOne = sampleAlphaToOne;

  if (m_sampleAlphaToOne) {
    m_gl.gl30->glEnable(GL_SAMPLE_ALPHA_TO_ONE);
  } else {
    m_gl.gl30->glDisable(GL_SAMPLE_ALPHA_TO_ONE);
  }
}
void SampleOptions::setSampleCoverageEnabled(bool sampleCoverage) noexcept {
  m_sampleCoverage = sampleCoverage;

  if (m_sampleCoverage) {
    m_gl.gl30->glEnable(GL_SAMPLE_COVERAGE);
  } else {
    m_gl.gl30->glDisable(GL_SAMPLE_COVERAGE);
  }
}

void SampleOptions::setSampleShadingEnabled(bool enabled) noexcept {
  m_sampleShadingEnabled = enabled;

  if (m_sampleShadingEnabled) {
    m_gl.gl30->glEnable(GL_SAMPLE_SHADING);
  } else {
    m_gl.gl30->glDisable(GL_SAMPLE_SHADING);
  }
}

void SampleOptions::setSampleMaskEnabled(bool sampleMask) noexcept {
  m_sampleMaskEnabled = sampleMask;

  if (m_sampleMaskEnabled) {
    m_gl.gl30->glEnable(GL_SAMPLE_MASK);
  } else {
    m_gl.gl30->glDisable(GL_SAMPLE_MASK);
  }
}

void SampleOptions::setMultisample(bool multisample) noexcept {
  m_multisample = multisample;

  if (m_multisample) {
    m_gl.gl30->glEnable(GL_MULTISAMPLE);
  } else {
    m_gl.gl30->glDisable(GL_MULTISAMPLE);
  }
}
void SampleOptions::setMinSampleShading(float minSampleShading) noexcept {
  m_minSampleShading = minSampleShading;

  if (m_gl.gl40) {
    // If OpenGL 4.0 is available...
    m_gl.gl40->glMinSampleShading(m_minSampleShading);
  }
}
}
