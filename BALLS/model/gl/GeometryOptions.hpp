#ifndef GEOMETRYOPTIONS_HPP
#define GEOMETRYOPTIONS_HPP

#include <QObject>

#include "gl/OpenGLConstants.hpp"
#include "gl/OpenGLPointers.hpp"
#include "model/OpenGLState.hpp"

namespace balls {

class GeometryOptions : public OpenGLState {
  Q_OBJECT

  Q_ENUMS(CullFace)
  Q_ENUMS(FrontFace)
  Q_ENUMS(PolygonMode)
  Q_ENUMS(ProvokeMode)
  Q_ENUMS(SpriteCoordOrigin)

  // clang-format off
  Q_PROPERTY(CullFace cullFace MEMBER m_cullFace WRITE setCullFace FINAL)
  Q_PROPERTY(FrontFace frontFace MEMBER m_frontFace WRITE setFrontFace FINAL)
  Q_PROPERTY(float lineWidth MEMBER m_lineWidth WRITE setLineWidth FINAL)
  Q_PROPERTY(float pointFadeThresholdSize MEMBER m_pointFadeThresholdSize WRITE setPointFadeThresholdSize FINAL)
  Q_PROPERTY(float pointSize MEMBER m_pointSize WRITE setPointSize FINAL)
  Q_PROPERTY(PolygonMode polygonMode MEMBER m_polygonMode WRITE setPolygonMode FINAL)
  Q_PROPERTY(float polygonOffsetFactor MEMBER m_polygonOffsetFactor WRITE setPolygonOffsetFactor FINAL)
  Q_PROPERTY(float polygonOffsetUnits MEMBER m_polygonOffsetUnits WRITE setPolygonOffsetUnits FINAL)
  Q_PROPERTY(bool polygonOffsetFill MEMBER m_polygonOffsetFill WRITE setPolygonOffsetFill FINAL)
  Q_PROPERTY(bool polygonOffsetPoint MEMBER m_polygonOffsetPoint WRITE setPolygonOffsetPoint FINAL)
  Q_PROPERTY(bool polygonOffsetLine MEMBER m_polygonOffsetLine WRITE setPolygonOffsetLine FINAL)
  Q_PROPERTY(bool primitiveRestartEnabled MEMBER m_primitiveRestartEnabled WRITE setPrimitiveRestartEnabled FINAL)
  Q_PROPERTY(uint primitiveRestartIndex MEMBER m_primitiveRestartIndex WRITE setPrimitiveRestartIndex FINAL)
  Q_PROPERTY(ProvokeMode provokingVertex MEMBER m_provokingVertex WRITE setProvokingVertex FINAL)
  Q_PROPERTY(bool programPointSize MEMBER m_programPointSize WRITE setProgramPointSize FINAL)
  Q_PROPERTY(bool polygonSmooth MEMBER m_polygonSmooth WRITE setPolygonSmooth FINAL)
  Q_PROPERTY(SpriteCoordOrigin spriteCoordOrigin MEMBER m_spriteCoordOrigin WRITE setSpriteCoordOrigin FINAL)

  // clang-format on

public /* enums */:
  enum CullFace : GLenum {
    None,
    Front = GL_FRONT,
    Back = GL_BACK,
    FrontAndBack = GL_FRONT_AND_BACK,
  };

  enum FrontFace : GLenum {
    Clockwise = GL_CW,
    CounterClockwise = GL_CCW,
  };


  enum PolygonMode : GLenum {
    Point = GL_POINT,
    Line = GL_LINE,
    Fill = GL_FILL,
  };

  enum ProvokeMode : GLenum {
    FirstVertexConvention = GL_FIRST_VERTEX_CONVENTION,
    LastVertexConvention = GL_LAST_VERTEX_CONVENTION,
  };

  enum SpriteCoordOrigin {
    UpperLeft = GL_UPPER_LEFT,
    LowerLeft = GL_LOWER_LEFT,
  };

public:
  explicit GeometryOptions(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  void setCullFace(CullFace) noexcept;
  void setFrontFace(FrontFace) noexcept;
  void setLineWidth(float) noexcept;
  void setPointFadeThresholdSize(float) noexcept;
  void setPointSize(float) noexcept;
  void setPolygonMode(PolygonMode) noexcept;
  void setPolygonOffsetFactor(float) noexcept;
  void setPolygonOffsetUnits(float) noexcept;
  void setPolygonOffsetFill(bool) noexcept;
  void setPolygonOffsetPoint(bool) noexcept;
  void setPolygonOffsetLine(bool) noexcept;
  void setPrimitiveRestartEnabled(bool) noexcept;
  void setPrimitiveRestartIndex(unsigned int) noexcept;
  void setProvokingVertex(ProvokeMode) noexcept;
  void setProgramPointSize(bool) noexcept;
  void setPolygonSmooth(bool) noexcept;
  void setSpriteCoordOrigin(SpriteCoordOrigin) noexcept;

private /* members */:
  CullFace m_cullFace;
  FrontFace m_frontFace;
  PolygonMode m_polygonMode;
  ProvokeMode m_provokingVertex;
  bool m_primitiveRestartEnabled;
  unsigned int m_primitiveRestartIndex;
  bool m_programPointSize;
  float m_pointFadeThresholdSize;
  float m_pointSize;
  float m_lineWidth;
  float m_polygonOffsetFactor;
  float m_polygonOffsetUnits;
  bool m_polygonOffsetFill;
  bool m_polygonOffsetPoint;
  bool m_polygonOffsetLine;
  bool m_polygonSmooth;
  SpriteCoordOrigin m_spriteCoordOrigin;
};
}

Q_DECLARE_METATYPE(balls::GeometryOptions*)

#endif // GEOMETRYOPTIONS_HPP
