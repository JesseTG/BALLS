#ifndef DEPTHOPTIONS_HPP
#define DEPTHOPTIONS_HPP

#include <QObject>

#include "gl/OpenGLConstants.hpp"
#include "gl/OpenGLPointers.hpp"
#include "model/OpenGLState.hpp"

namespace balls {

class DepthOptions : public OpenGLState {
  Q_OBJECT

  Q_ENUMS(DepthFunction)

  // clang-format off
  Q_PROPERTY(bool testEnabled MEMBER m_testEnabled WRITE setTestEnabled FINAL)
  Q_PROPERTY(bool clampEnabled MEMBER m_clampEnabled WRITE setClampEnabled FINAL)
  Q_PROPERTY(float clearDepth MEMBER m_clearDepth WRITE setClearDepth FINAL)
  Q_PROPERTY(DepthFunction depthFunction MEMBER m_depthFunction WRITE setDepthFunction FINAL)
  Q_PROPERTY(bool depthMask MEMBER m_depthMask WRITE setDepthMask FINAL)
  Q_PROPERTY(float depthNear MEMBER m_depthNear WRITE setDepthNear FINAL)
  Q_PROPERTY(float depthFar MEMBER m_depthFar WRITE setDepthFar FINAL)
  // clang-format on

public /* enums */:
  enum DepthFunction : GLenum {
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
  explicit DepthOptions(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  void setTestEnabled(bool) noexcept;
  void setClampEnabled(bool) noexcept;
  void setClearDepth(float) noexcept;
  void setDepthFunction(DepthFunction) noexcept;
  void setDepthMask(bool) noexcept;
  void setDepthNear(float) noexcept;
  void setDepthFar(float) noexcept;

private /* update functions */:
  void updateDepthRange() noexcept;

private /* members */:
  bool m_testEnabled;
  bool m_clampEnabled;
  float m_clearDepth;
  DepthFunction m_depthFunction;
  bool m_depthMask;
  float m_depthNear;
  float m_depthFar;
};
}


Q_DECLARE_METATYPE(balls::DepthOptions*)

#endif // DEPTHOPTIONS_HPP
