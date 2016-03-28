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
  Q_PROPERTY(bool enabled MEMBER m_enabled WRITE setEnabled FINAL)
  Q_PROPERTY(QColor blendColor MEMBER m_blendColor WRITE setBlendColor FINAL)
  Q_PROPERTY(BlendEquation blendEquationRgb MEMBER m_blendRgb WRITE setBlendRgb FINAL)
  Q_PROPERTY(BlendEquation blendEquationAlpha MEMBER m_blendAlpha WRITE setBlendAlpha FINAL)
  Q_PROPERTY(BlendFunction sourceRgb MEMBER m_srcRgb WRITE setSrcRgb FINAL)
  Q_PROPERTY(BlendFunction destinationRgb MEMBER m_dstRgb WRITE setDstRgb FINAL)
  Q_PROPERTY(BlendFunction sourceAlpha MEMBER m_srcAlpha WRITE setSrcAlpha FINAL)
  Q_PROPERTY(BlendFunction destinationAlpha MEMBER m_dstAlpha WRITE setDstAlpha FINAL)
  // clang-format on

public /* enums */:
  enum BlendEquation : GLenum {
    Add = GL_FUNC_ADD,
    Subtract = GL_FUNC_SUBTRACT,
    ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
    Min = GL_MIN,
    Max = GL_MAX,
  };

  enum BlendFunction : GLenum {
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
  explicit BlendState(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  void setEnabled(bool) noexcept;
  void setBlendColor(const QColor&) noexcept;
  void setBlendRgb(BlendEquation) noexcept;
  void setBlendAlpha(BlendEquation) noexcept;
  void setSrcRgb(BlendFunction) noexcept;
  void setDstRgb(BlendFunction) noexcept;
  void setSrcAlpha(BlendFunction) noexcept;
  void setDstAlpha(BlendFunction) noexcept;

private /* update methods */:
  void updateEquation() noexcept;
  void updateFunction() noexcept;

private /* members */:
  OpenGLPointers m_gl;

  bool m_enabled;
  QColor m_blendColor;
  BlendEquation m_blendRgb;
  BlendEquation m_blendAlpha;
  BlendFunction m_srcRgb;
  BlendFunction m_dstRgb;
  BlendFunction m_srcAlpha;
  BlendFunction m_dstAlpha;
};
}

Q_DECLARE_METATYPE(balls::BlendState*)

#endif // BLENDFUNCTIONSTATE_HPP
