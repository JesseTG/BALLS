#include "precompiled.hpp"
#include "model/gl/ImplementationInfo.hpp"

#include <QOpenGLFunctions_3_0>

#include "gl/OpenGLPointers.hpp"

namespace balls {

ImplementationInfo::ImplementationInfo(OpenGLPointers& gl, QObject* parent)
  : QObject(parent) {
  Q_ASSUME(gl.gl30 != nullptr);

  m_glslVersion = reinterpret_cast<const char*>(gl.gl30->glGetString(GL_SHADING_LANGUAGE_VERSION));
  m_renderer = reinterpret_cast<const char*>(gl.gl30->glGetString(GL_RENDERER));
  m_vendor = reinterpret_cast<const char*>(gl.gl30->glGetString(GL_VENDOR));
  m_version = reinterpret_cast<const char*>(gl.gl30->glGetString(GL_VERSION));
  // HACK: Gotta figure out a better way to do this later
}
}
