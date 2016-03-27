#include "precompiled.hpp"
#include "model/OpenGLState.hpp"

namespace balls {

OpenGLState::OpenGLState(QOpenGLContext* context, QObject* parent)
  : QObject(parent), m_gl(context) {}
}
