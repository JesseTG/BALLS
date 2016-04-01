#ifndef CLIPOPTIONS_HPP
#define CLIPOPTIONS_HPP

#include <qopengl.h>
#include <QObject>

#include <glm/fwd.hpp>

#include "model/OpenGLState.hpp"
#include "gl/OpenGLPointers.hpp"

namespace balls {

using glm::ivec2;
using glm::vec2;
using glm::uvec2;

class ClipOptions : public OpenGLState {
  Q_OBJECT

  Q_ENUMS(ClipControlOrigin)
  Q_ENUMS(ClipControlDepth)

  // clang-format off
  Q_PROPERTY(ivec2 viewportPosition MEMBER m_viewportPosition WRITE setViewportPosition FINAL)
  Q_PROPERTY(uvec2 viewportSize READ viewportSize WRITE setViewportSize STORED false FINAL)
  Q_PROPERTY(bool scissorEnabled MEMBER m_scissorEnabled WRITE setScissorEnabled FINAL)
  Q_PROPERTY(ivec2 scissorPosition MEMBER m_scissorPosition WRITE setScissorPosition FINAL)
  Q_PROPERTY(uvec2 scissorSize READ scissorSize WRITE setScissorSize STORED false FINAL)
  Q_PROPERTY(ClipControlOrigin origin MEMBER m_origin WRITE setOrigin FINAL)
  Q_PROPERTY(ClipControlDepth depth MEMBER m_depth WRITE setDepth FINAL)
  // clang-format on

public /* enums */:
  enum ClipControlOrigin : GLenum {
    LowerLeft = GL_LOWER_LEFT,
    UpperLeft = GL_UPPER_LEFT,
  };

  enum ClipControlDepth : GLenum {
    NegativeOneToOne = GL_NEGATIVE_ONE_TO_ONE,
    ZeroToOne = GL_ZERO_TO_ONE,
  };

public:
  explicit ClipOptions(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  uvec2 viewportSize() noexcept;
  uvec2 scissorSize() noexcept;

private /* setters */:
  void setViewportPosition(const ivec2&) noexcept;
  void setViewportSize(const uvec2&) noexcept;
  void setScissorPosition(const ivec2&) noexcept;
  void setScissorSize(const uvec2&) noexcept;
  void setScissorEnabled(bool) noexcept;
  void setOrigin(ClipControlOrigin) noexcept;
  void setDepth(ClipControlDepth) noexcept;

private /* members */:
  bool m_scissorEnabled;
  ivec2 m_viewportPosition;
  ivec2 m_scissorPosition;
  ClipControlOrigin m_origin;
  ClipControlDepth m_depth;
};
}


Q_DECLARE_METATYPE(balls::ClipOptions*)

#endif // CLIPOPTIONS_HPP
