#ifndef OPENGLSTATE_HPP
#define OPENGLSTATE_HPP

#include <QColor>
#include <QObject>
#include <QOpenGLContext>

#include <glm/fwd.hpp>

#include "gl/OpenGLPointers.hpp"

namespace balls {

using glm::bvec4;

class OpenGLState : public QObject {
  Q_OBJECT

  /* Categories of OpenGL state:
   * - Blend State (DONE)
   * - Implementation info (vendors, etc.)
   * - Limits (GL_MAX_VARYING_COMPONENTS, etc.)
   * - Hints
   * - Stencil
   * - Depth (DONE)
   * - Color
   * - View (scissor, viewport)
   *
   */


  Q_ENUMS(CullFace)
  Q_ENUMS(FrontFace)
  Q_ENUMS(LogicOperation)
  Q_ENUMS(PolygonMode)
  Q_ENUMS(ProvokeMode)
  Q_ENUMS(SpriteCoordOrigin)

  // clang-format off

  Q_PROPERTY(bool clampColor READ clampColor WRITE setClampColor STORED false FINAL)
  Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor STORED false FINAL)
  Q_PROPERTY(int clearStencil READ clearSTencil WRITE setClearStencil STORED false FINAL)
  Q_PROPERTY(bvec4 colorMask READ colorMask WRITE setColorMask STORED false FINAL)
  Q_PROPERTY(CullFace cullFace READ cullFace WRITE setCullFace STORED false FINAL)
  Q_PROPERTY(FrontFace frontFace READ frontFace WRITE setFrontFace STORED false FINAL)
  Q_PROPERTY(bool invertSampleCoverage READ invertSampleCoverage WRITE setInvertSampleCoverage STORED false FINAL)
  Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth STORED false FINAL)
  Q_PROPERTY(float pointFadeThresholdSize READ pointFadeThresholdSize WRITE setPointFadeThresholdSize STORED false FINAL)
  Q_PROPERTY(float pointSize READ pointSize WRITE setPointSize STORED false FINAL)
  Q_PROPERTY(PolygonMode polygonMode READ polygonMode WRITE setPolygonMode STORED false FINAL)
  Q_PROPERTY(float polygonOffsetFactor READ polygonOffsetFactor WRITE setPolygonOffsetFactor STORED false FINAL)
  Q_PROPERTY(float polygonOffsetUnits READ polygonOffsetUnits WRITE setPolygonOffsetUnits STORED false FINAL)
  Q_PROPERTY(uint primitiveRestartIndex READ primitiveRestartIndex WRITE setPrimitiveRestartIndex STORED false FINAL)
  Q_PROPERTY(ProvokeMode provokingVertex READ provokingVertex WRITE setProvokingIndex STORED false FINAL)
  Q_PROPERTY(float sampleCoverage READ sampleCoverage WRITE setSampleCoverage STORED false FINAL)
  Q_PROPERTY(SpriteCoordOrigin spriteCoordOrigin READ spriteCoordOrigin WRITE setSpriteCoordOrigin STORED false FINAL)

  // clang-format on

public /* enums */:


  enum CullFace {
    None,
    Front = GL_FRONT,
    Back = GL_BACK,
    FrontAndBack = GL_FRONT_AND_BACK,
  };

  enum FrontFace {
    Clockwise = GL_CW,
    CounterClockwise = GL_CCW,
  };


  enum LogicOperation {
    Clear = GL_CLEAR,
    Set = GL_SET,
    Copy = GL_COPY,
    CopyInverted = GL_COPY_INVERTED,
    Noop = GL_NOOP,
    Invert = GL_INVERT,
    And = GL_AND,
    Nand = GL_NAND,
    Or = GL_OR,
    Xor = GL_XOR,
    Equivalent = GL_EQUIV,
    AndReverse = GL_AND_REVERSE,
    AndInverted = GL_AND_INVERTED,
    OrReverse = GL_OR_REVERSE,
    OrInverted = GL_OR_INVERTED,
  };

  enum PolygonMode {
    Point = GL_POINT,
    Line = GL_LINE,
    Fill = GL_FILL,
  };

  enum ProvokeMode {
    FirstVertexConvention = GL_FIRST_VERTEX_CONVENTION,
    LastVertexConvention = GL_LAST_VERTEX_CONVENTION,
  };

  enum SpriteCoordOrigin {
    UpperLeft = GL_UPPER_LEFT,
    LowerLeft = GL_LOWER_LEFT,
  };

public:
  explicit OpenGLState(QOpenGLContext*, QObject* = nullptr);

private /* members */:
  OpenGLPointers m_gl;
};
}

#endif // OPENGLSTATE_HPP
