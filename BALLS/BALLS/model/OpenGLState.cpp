#include "precompiled.hpp"
#include "model/OpenGLState.hpp"

namespace balls {

OpenGLState::OpenGLState(OpenGLPointers& context, QObject* parent)
  : QObject(parent), m_gl(context) {}
}
