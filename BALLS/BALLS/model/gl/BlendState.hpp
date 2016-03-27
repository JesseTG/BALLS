#ifndef BLENDFUNCTIONSTATE_HPP
#define BLENDFUNCTIONSTATE_HPP

#include <qopengl.h>
#include <QObject>

#include "gl/OpenGLPointers.hpp"

namespace balls {

class BlendState : public QObject {
  Q_OBJECT

  Q_ENUMS(BlendEquation)
  Q_ENUMS(BlendFunction)

  // clang-format off
  Q_PROPERTY(QColor blendColor READ blendColor WRITE setBlendColor STORED false FINAL)
  Q_PROPERTY(BlendEquation blendEquationRgb READ eq(GL_BLEND_EQUATION_RGB) WRITE setBlendRgb STORED false FINAL)
  Q_PROPERTY(BlendEquation blendEquationAlpha READ eq(GL_BLEND_EQUATION_ALPHA) WRITE setBlendAlpha STORED false FINAL)
  Q_PROPERTY(BlendFunction sourceRgb READ func(GL_BLEND_SRC_RGB) WRITE setSrcRgb STORED false FINAL)
  Q_PROPERTY(BlendFunction destinationRgb READ func(GL_BLEND_DST_RGB) WRITE setDstRgb STORED false FINAL)
  Q_PROPERTY(BlendFunction sourceAlpha READ func(GL_BLEND_SRC_ALPHA) WRITE setSrcAlpha STORED false FINAL)
  Q_PROPERTY(BlendFunction destinationAlpha READ func(GL_BLEND_DST_ALPHA) WRITE setDstAlpha STORED false FINAL)
  // clang-format on

public /* enums */:
  enum BlendEquation {
    Add = GL_FUNC_ADD,
    Subtract = GL_FUNC_SUBTRACT,
    ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
    Min = GL_MIN,
    Max = GL_MAX,
  };

  enum BlendFunction {
    Zero = GL_ZERO,
    One = GL_ONE,
    SourceColor = GL_SRC_COLOR,
    OneMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,
    DestinationColor = GL_DST_COLOR,
    OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,
    SourceAlpha = GL_SRC_ALPHA,
    OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
    DestinationAlpha = GL_DST_ALPHA,
    OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
    ConstantColor = GL_CONSTANT_COLOR,
    OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
    ConstantAlpha = GL_CONSTANT_ALPHA,
    OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
    SourceAlphaSaturate = GL_SRC_ALPHA_SATURATE,
    Source1Color = GL_SRC1_COLOR,
    OneMinusSource1Color = GL_ONE_MINUS_SRC1_COLOR,
    Source1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
    OneMinusSource1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
  };

public:
  explicit BlendState(QOpenGLContext*, QObject* = nullptr);

private /* getters */:
  BlendFunction func(GLenum);
  BlendEquation eq(GLenum);

private /* setters */:
  void setBlendRgb(BlendEquation);
  void setBlendAlpha(BlendEquation);
  void setSrcRgb(BlendFunction);
  void setDstRgb(BlendFunction);
  void setSrcAlpha(BlendFunction);
  void setDstAlpha(BlendFunction);
private /* members */:
  OpenGLPointers m_gl;
};
}

Q_DECLARE_METATYPE(balls::BlendFunctionState*)

#endif // BLENDFUNCTIONSTATE_HPP
