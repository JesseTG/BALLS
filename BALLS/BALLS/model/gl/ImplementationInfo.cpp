#include "precompiled.hpp"
#include "model/gl/ImplementationInfo.hpp"

#include <QOpenGLFunctions_3_0>

#include "gl/OpenGLPointers.hpp"

namespace balls {

ImplementationInfo::ImplementationInfo(OpenGLPointers& gl, QObject* parent)
  : QObject(parent) {
  Q_ASSUME(gl.gl30 != nullptr);

  m_glslVersion = QString(gl.gl30->glGetString(GL_SHADING_LANGUAGE_VERSION));
  m_renderer = QString(gl.gl30->glGetString(GL_RENDERER));
  m_vendor = QString(gl.gl30->glGetString(GL_VENDOR));
  m_version = QString(gl.gl30->glGetString(GL_VERSION));
}
}
