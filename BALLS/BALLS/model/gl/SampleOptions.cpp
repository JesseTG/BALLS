#include "precompiled.hpp"
#include "model/gl/SampleOptions.hpp"

#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_4_0_Core>

namespace balls {

SampleOptions::SampleOptions(OpenGLPointers& gl, QObject* parent)
  : OpenGLState(gl, parent),
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

  setGlFeature(m_sampleAlphaToCoverage, GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void SampleOptions::setSampleAlphaToOne(bool sampleAlphaToOne) noexcept {
  m_sampleAlphaToOne = sampleAlphaToOne;

  setGlFeature(m_sampleAlphaToOne, GL_SAMPLE_ALPHA_TO_ONE);
}
void SampleOptions::setSampleCoverageEnabled(bool sampleCoverage) noexcept {
  m_sampleCoverage = sampleCoverage;

  setGlFeature(m_sampleCoverage, GL_SAMPLE_COVERAGE);
}

void SampleOptions::setSampleShadingEnabled(bool enabled) noexcept {
  m_sampleShadingEnabled = enabled;

  setGlFeature(m_sampleShadingEnabled, GL_SAMPLE_SHADING);
}

void SampleOptions::setSampleMaskEnabled(bool sampleMask) noexcept {
  m_sampleMaskEnabled = sampleMask;

  setGlFeature(m_sampleMaskEnabled, GL_SAMPLE_MASK);
}

void SampleOptions::setMultisample(bool multisample) noexcept {
  m_multisample = multisample;

  setGlFeature(m_multisample, GL_MULTISAMPLE);
}
void SampleOptions::setMinSampleShading(float minSampleShading) noexcept {
  m_minSampleShading = minSampleShading;

  if (m_gl.gl40) {
    // If OpenGL 4.0 is available...
    m_gl.gl40->glMinSampleShading(m_minSampleShading);
  }
}
}
