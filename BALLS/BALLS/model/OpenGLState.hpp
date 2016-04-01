#ifndef OPENGLSTATE_HPP
#define OPENGLSTATE_HPP

#include <QColor>
#include <QObject>
#include <QOpenGLContext>

#include "gl/OpenGLPointers.hpp"

namespace balls {

class OpenGLState : public QObject {
  Q_OBJECT

public:
  explicit OpenGLState(OpenGLPointers&, QObject* = nullptr);
  virtual ~OpenGLState() {}

protected /* methods */:
  void ensureContext();

  bool hasGl31() const noexcept;
  bool hasGl32() const noexcept;
  bool hasGl33() const noexcept;
  bool hasGl40() const noexcept;
  bool hasGl41() const noexcept;
  bool hasGl42() const noexcept;
  bool hasGl43() const noexcept;
  bool hasGl44() const noexcept;
  bool hasGl45() const noexcept;

protected /* members */:
  OpenGLPointers m_gl;
};
}

#endif // OPENGLSTATE_HPP
