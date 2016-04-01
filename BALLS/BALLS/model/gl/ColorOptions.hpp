#ifndef COLOROPTIONS_HPP
#define COLOROPTIONS_HPP

#include <QObject>

#include <qopengl.h>
#include <glm/vec4.hpp>

#include "gl/OpenGLPointers.hpp"

namespace balls {

using glm::bvec4;

class ColorOptions : public QObject {
  Q_OBJECT

  Q_ENUMS(LogicOperation)

  // clang-format off
  Q_PROPERTY(bool logicOpEnabled MEMBER m_logicOpEnabled WRITE setLogicOpEnabled FINAL)
  Q_PROPERTY(bool clampColor MEMBER m_clampColor WRITE setClampColor FINAL)
  Q_PROPERTY(bool dithering MEMBER m_dithering WRITE setDithering FINAL)
  Q_PROPERTY(QColor clearColor MEMBER m_clearColor WRITE setClearColor FINAL)
  Q_PROPERTY(bvec4 colorMask MEMBER m_colorMask WRITE setColorMask FINAL)
  Q_PROPERTY(LogicOperation logicOperation MEMBER m_logicOp WRITE setLogicOperation FINAL)
  // clang-format on

public /* enums */:
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

public:
  explicit ColorOptions(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  void setLogicOpEnabled(bool) noexcept;
  void setClampColor(bool) noexcept;
  void setClearColor(const QColor&) noexcept;
  void setColorMask(const bvec4&) noexcept;
  void setLogicOperation(LogicOperation) noexcept;
  void setDithering(bool) noexcept;

private /* members */:
  OpenGLPointers m_gl;

  bool m_logicOpEnabled;
  bool m_clampColor;
  bool m_dithering;
  QColor m_clearColor;
  bvec4 m_colorMask;
  LogicOperation m_logicOp;
};
}


Q_DECLARE_METATYPE(balls::ColorOptions*)

#endif // COLOROPTIONS_HPP
