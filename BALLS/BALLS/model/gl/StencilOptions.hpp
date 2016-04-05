#ifndef STENCILOPTIONS_HPP
#define STENCILOPTIONS_HPP

#include <QObject>

#include <qopengl.h>

#include "gl/OpenGLPointers.hpp"
#include "model/OpenGLState.hpp"

namespace balls {

class StencilOptions : public OpenGLState {
  Q_OBJECT

  Q_ENUMS(StencilAction)
  Q_ENUMS(StencilFunction)

  // clang-format off
  Q_PROPERTY(bool stencilEnabled MEMBER m_stencilEnabled WRITE setStencilEnabled FINAL)
  Q_PROPERTY(int clearStencil MEMBER m_clearStencil WRITE setClearStencil FINAL)
  Q_PROPERTY(uint frontStencilMask MEMBER m_frontStencilMask WRITE setFrontStencilMask FINAL)
  Q_PROPERTY(uint backStencilMask MEMBER m_backStencilMask WRITE setBackStencilMask FINAL)

  Q_PROPERTY(StencilAction frontStencilFail MEMBER m_frontStencilFail WRITE setFrontStencilFail FINAL)
  Q_PROPERTY(StencilAction frontStencilPassDepthFail MEMBER m_frontStencilPassDepthFail WRITE setFrontStencilPassDepthFail FINAL)
  Q_PROPERTY(StencilAction frontStencilPassDepthPass MEMBER m_frontStencilPassDepthPass WRITE setFrontStencilPassDepthPass FINAL)

  Q_PROPERTY(StencilAction backStencilFail MEMBER m_backStencilFail WRITE setBackStencilFail FINAL)
  Q_PROPERTY(StencilAction backStencilPassDepthFail MEMBER m_backStencilPassDepthFail WRITE setBackStencilPassDepthFail FINAL)
  Q_PROPERTY(StencilAction backStencilPassDepthPass MEMBER m_backStencilPassDepthPass WRITE setBackStencilPassDepthPass FINAL)

  Q_PROPERTY(StencilFunction frontStencilFunction MEMBER m_frontStencilFunction WRITE setFrontStencilFunction FINAL)
  Q_PROPERTY(int frontStencilRef MEMBER m_frontStencilRef WRITE setFrontStencilRef FINAL)
  Q_PROPERTY(uint frontStencilValueMask MEMBER m_frontStencilValueMask WRITE setFrontStencilValueMask FINAL)

  Q_PROPERTY(StencilFunction backStencilFunction MEMBER m_backStencilFunction WRITE setBackStencilFunction FINAL)
  Q_PROPERTY(int backStencilRef MEMBER m_backStencilRef WRITE setBackStencilRef FINAL)
  Q_PROPERTY(uint backStencilValueMask MEMBER m_backStencilValueMask WRITE setBackStencilValueMask FINAL)
  // clang-format on

public /* enums */:
  enum StencilAction : GLenum {
    Keep = GL_KEEP,
    Zero = GL_ZERO,
    Replace = GL_REPLACE,
    Increment = GL_INCR,
    IncrementWrap = GL_INCR_WRAP,
    Decrement = GL_DECR,
    DecrementWrap = GL_DECR_WRAP,
    Invert = GL_INVERT,
  };

  enum StencilFunction : GLenum {
    Never = GL_NEVER,
    Less = GL_LESS,
    Equal = GL_EQUAL,
    LessEqual = GL_LEQUAL,
    Greater = GL_GREATER,
    NotEqual = GL_NOTEQUAL,
    GreaterEqual = GL_GEQUAL,
    Always = GL_ALWAYS,
  };

public:
  explicit StencilOptions(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  void setStencilEnabled(bool) noexcept;
  void setClearStencil(int) noexcept;
  void setFrontStencilMask(unsigned int) noexcept;
  void setBackStencilMask(unsigned int) noexcept;

  void setFrontStencilFail(StencilAction) noexcept;
  void setFrontStencilPassDepthFail(StencilAction) noexcept;
  void setFrontStencilPassDepthPass(StencilAction) noexcept;

  void setBackStencilFail(StencilAction) noexcept;
  void setBackStencilPassDepthFail(StencilAction) noexcept;
  void setBackStencilPassDepthPass(StencilAction) noexcept;

  void setFrontStencilFunction(StencilFunction) noexcept;
  void setFrontStencilRef(int) noexcept;
  void setFrontStencilValueMask(unsigned int) noexcept;

  void setBackStencilFunction(StencilFunction) noexcept;
  void setBackStencilRef(int) noexcept;
  void setBackStencilValueMask(unsigned int) noexcept;

  void updateStencilOpFront() noexcept;
  void updateStencilOpBack() noexcept;
  void updateStencilFuncFront() noexcept;
  void updateStencilFuncBack() noexcept;
private /* members */:
  bool m_stencilEnabled;
  int m_clearStencil;
  unsigned int m_frontStencilMask;
  unsigned int m_backStencilMask;

  StencilAction m_frontStencilFail;
  StencilAction m_frontStencilPassDepthFail;
  StencilAction m_frontStencilPassDepthPass;

  StencilAction m_backStencilFail;
  StencilAction m_backStencilPassDepthFail;
  StencilAction m_backStencilPassDepthPass;

  StencilFunction m_frontStencilFunction;
  int m_frontStencilRef;
  unsigned int m_frontStencilValueMask;

  StencilFunction m_backStencilFunction;
  int m_backStencilRef;
  unsigned int m_backStencilValueMask;
};
}

Q_DECLARE_METATYPE(balls::StencilOptions*)

#endif // STENCILOPTIONS_HPP
