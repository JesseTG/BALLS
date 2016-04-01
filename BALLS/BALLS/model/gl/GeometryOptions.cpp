#include "precompiled.hpp"
#include "model/gl/GeometryOptions.hpp"

#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_3_2_Core>

namespace balls {

GeometryOptions::GeometryOptions(OpenGLPointers& gl, QObject* parent)
  : QObject(parent),
    m_gl(gl),
    m_cullFace(CullFace::None),
    m_frontFace(FrontFace::CounterClockwise),
    m_polygonMode(PolygonMode::Fill),
    m_provokingVertex(ProvokeMode::LastVertexConvention),
    m_primitiveRestartEnabled(false),
    m_primitiveRestartIndex(0),
    m_programPointSize(false),
    m_pointFadeThresholdSize(1.0f),
    m_pointSize(1.0f),
    m_lineWidth(1.0f),
    m_polygonOffsetFactor(0.0f),
    m_polygonOffsetUnits(0.0f),
    m_polygonOffsetFill(false),
    m_polygonOffsetPoint(false),
    m_polygonOffsetLine(false),
    m_polygonSmooth(false),
    m_spriteCoordOrigin(SpriteCoordOrigin::UpperLeft) {}
// Initialized with the defualt values as specified by OpenGL

void GeometryOptions::setCullFace(CullFace cullFace) noexcept {
  m_cullFace = cullFace;

  if (m_cullFace == CullFace::None) {
    // If we're turning off backface culling...

    m_gl.gl30->glDisable(GL_CULL_FACE);
  } else {
    m_gl.gl30->glEnable(GL_CULL_FACE);
    m_gl.gl30->glCullFace(m_cullFace);
  }
}

void GeometryOptions::setFrontFace(FrontFace frontFace) noexcept {
  m_frontFace = frontFace;

  m_gl.gl30->glFrontFace(m_frontFace);
}

void GeometryOptions::setLineWidth(float lineWidth) noexcept {
  m_lineWidth = lineWidth;

  m_gl.gl30->glLineWidth(m_lineWidth);
}

void GeometryOptions::setPointFadeThresholdSize(float threshold) noexcept {
  m_pointFadeThresholdSize = threshold;

  m_gl.gl30->glPointParameterf(
    GL_POINT_FADE_THRESHOLD_SIZE, m_pointFadeThresholdSize);
}

void GeometryOptions::setPointSize(float pointSize) noexcept {
  m_pointSize = pointSize;

  m_gl.gl30->glPointSize(pointSize);
}

void GeometryOptions::setPolygonMode(PolygonMode polygonMode) noexcept {
  m_polygonMode = polygonMode;

  m_gl.gl30->glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void GeometryOptions::setPolygonOffsetFactor(float factor) noexcept {
  m_polygonOffsetFactor = factor;

  m_gl.gl30->glPolygonOffset(m_polygonOffsetFactor, m_polygonOffsetUnits);
}

void GeometryOptions::setPolygonOffsetUnits(float units) noexcept {
  m_polygonOffsetUnits = units;

  m_gl.gl30->glPolygonOffset(m_polygonOffsetFactor, m_polygonOffsetUnits);
}
void GeometryOptions::setPolygonOffsetFill(bool fill) noexcept {
  m_polygonOffsetFill = fill;

  if (m_polygonOffsetFill) {
    m_gl.gl30->glEnable(GL_POLYGON_OFFSET_FILL);
  } else {
    m_gl.gl30->glDisable(GL_POLYGON_OFFSET_FILL);
  }
}
void GeometryOptions::setPolygonOffsetPoint(bool point) noexcept {
  m_polygonOffsetPoint = point;

  if (m_polygonOffsetPoint) {
    m_gl.gl30->glEnable(GL_POLYGON_OFFSET_POINT);
  } else {
    m_gl.gl30->glDisable(GL_POLYGON_OFFSET_POINT);
  }
}
void GeometryOptions::setPolygonOffsetLine(bool line) noexcept {
  m_polygonOffsetLine = line;

  if (m_polygonOffsetLine) {
    m_gl.gl30->glEnable(GL_POLYGON_OFFSET_LINE);
  } else {
    m_gl.gl30->glDisable(GL_POLYGON_OFFSET_LINE);
  }
}

void GeometryOptions::setPrimitiveRestartEnabled(bool enabled) noexcept {
  m_primitiveRestartEnabled = enabled;

  if (m_primitiveRestartEnabled) {
    m_gl.gl30->glEnable(GL_PRIMITIVE_RESTART);
  } else {
    m_gl.gl30->glDisable(GL_PRIMITIVE_RESTART);
  }
}

void GeometryOptions::setPrimitiveRestartIndex(unsigned int index) noexcept {
  m_primitiveRestartIndex = index;

  if (m_gl.gl32) {
    // If OpenGL 3.2 is available...
    m_gl.gl32->glPrimitiveRestartIndex(m_primitiveRestartIndex);
  }
}

void GeometryOptions::setProvokingVertex(ProvokeMode provokeMode) noexcept {
  m_provokingVertex = provokeMode;

  if (m_gl.gl32) {
    // If OpenGL 3.2 is available...
    m_gl.gl32->glProvokingVertex(m_provokingVertex);
  }
}
void GeometryOptions::setProgramPointSize(bool enabled) noexcept {
  m_programPointSize = enabled;

  if (m_programPointSize) {
    m_gl.gl30->glEnable(GL_PROGRAM_POINT_SIZE);
  } else {
    m_gl.gl30->glDisable(GL_PROGRAM_POINT_SIZE);
  }
}
void GeometryOptions::setPolygonSmooth(bool enabled) noexcept {
  m_polygonSmooth = enabled;

  if (m_polygonSmooth) {
    m_gl.gl30->glEnable(GL_POLYGON_SMOOTH);
  } else {
    m_gl.gl30->glDisable(GL_POLYGON_SMOOTH);
  }
}

void GeometryOptions::setSpriteCoordOrigin(SpriteCoordOrigin origin) noexcept {
  m_spriteCoordOrigin = origin;

  m_gl.gl30->glPointParameteri(
    GL_POINT_SPRITE_COORD_ORIGIN, m_spriteCoordOrigin);
}
}
