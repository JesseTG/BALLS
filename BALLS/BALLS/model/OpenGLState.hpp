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

protected /* members */:
  OpenGLPointers m_gl;
};
}

#endif // OPENGLSTATE_HPP
