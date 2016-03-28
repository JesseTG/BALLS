#ifndef HINTS_HPP
#define HINTS_HPP

#include <QObject>

#include <qopengl.h>

#include "gl/OpenGLPointers.hpp"

namespace balls {

class Hints : public QObject {
  Q_OBJECT

  Q_ENUMS(HintMode)

  // clang-format off
  Q_PROPERTY(HintMode fragmentDerivative MEMBER m_fragmentDerivative WRITE setFragmentDerivative FINAL)
  Q_PROPERTY(HintMode lineSmooth MEMBER m_lineSmooth WRITE setLineSmooth FINAL)
  Q_PROPERTY(HintMode polygonSmooth MEMBER m_polygonSmooth WRITE setPolygonSmooth FINAL)
  Q_PROPERTY(HintMode textureCompression MEMBER m_textureCompression WRITE setTextureCompression FINAL)
  // clang-format on

public /* enums */:
  enum HintMode : GLenum {
    Fastest = GL_FASTEST,
    Nicest = GL_NICEST,
    DontCare = GL_DONT_CARE,
  };

public:
  explicit Hints(OpenGLPointers&, QObject* = nullptr);

private /* setters */:
  void setFragmentDerivative(HintMode) noexcept;
  void setLineSmooth(HintMode) noexcept;
  void setPolygonSmooth(HintMode) noexcept;
  void setTextureCompression(HintMode) noexcept;

private /* members */:
  OpenGLPointers m_gl;

  HintMode m_fragmentDerivative;
  HintMode m_lineSmooth;
  HintMode m_polygonSmooth;
  HintMode m_textureCompression;
};
}

Q_DECLARE_METATYPE(balls::Hints*)

#endif // HINTS_HPP
