#include "precompiled.hpp"

#include "gl/OpenGLPointers.hpp"

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLFunctions_3_1>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLFunctions_4_3_Core>

namespace balls {

namespace {
template <class QOpenGLF>
QOpenGLF* _getGl(QOpenGLContext* context) noexcept {
  QOpenGLF* gl = context->versionFunctions<QOpenGLF>();

  if (gl) {
    // If we have this version of OpenGL available...
    gl->initializeOpenGLFunctions();
  }

  return gl;
}
}

OpenGLPointers::OpenGLPointers(QOpenGLContext* ctx)
  : context(ctx),
    gl30(_getGl<QOpenGLFunctions_3_0>(context)),
    gl31(_getGl<QOpenGLFunctions_3_1>(context)),
    gl32(_getGl<QOpenGLFunctions_3_2_Core>(context)),
    gl33(_getGl<QOpenGLFunctions_3_3_Core>(context)),
    gl40(_getGl<QOpenGLFunctions_4_0_Core>(context)),
    gl41(_getGl<QOpenGLFunctions_4_1_Core>(context)),
    gl42(_getGl<QOpenGLFunctions_4_2_Core>(context)),
    gl43(_getGl<QOpenGLFunctions_4_3_Core>(context)) {

  if (gl30) gl30->initializeOpenGLFunctions();
  if (gl31) gl31->initializeOpenGLFunctions();
  if (gl32) gl32->initializeOpenGLFunctions();
  if (gl33) gl33->initializeOpenGLFunctions();
  if (gl40) gl40->initializeOpenGLFunctions();
  if (gl41) gl41->initializeOpenGLFunctions();
  if (gl42) gl42->initializeOpenGLFunctions();
  if (gl43) gl43->initializeOpenGLFunctions();
}

OpenGLPointers::OpenGLPointers()
  : context(nullptr),
    gl30(nullptr),
    gl31(nullptr),
    gl32(nullptr),
    gl40(nullptr),
    gl41(nullptr),
    gl42(nullptr),
    gl43(nullptr) {}

QOpenGLFunctions_3_0* OpenGLPointers::gl30Current() noexcept {
  ensureContext();

  return gl30;
}

QOpenGLFunctions_3_1* OpenGLPointers::gl31Current() noexcept {
  ensureContext();

  return gl31;
}

QOpenGLFunctions_3_2_Core* OpenGLPointers::gl32Current() noexcept {
  ensureContext();

  return gl32;
}

QOpenGLFunctions_3_3_Core* OpenGLPointers::gl33Current() noexcept {
  ensureContext();

  return gl33;
}

QOpenGLFunctions_4_0_Core* OpenGLPointers::gl40Current() noexcept {
  ensureContext();

  return gl40;
}

QOpenGLFunctions_4_1_Core* OpenGLPointers::gl41Current() noexcept {
  ensureContext();

  return gl41;
}

QOpenGLFunctions_4_2_Core* OpenGLPointers::gl42Current() noexcept {
  ensureContext();

  return gl42;
}

QOpenGLFunctions_4_3_Core* OpenGLPointers::gl43Current() noexcept {
  ensureContext();

  return gl43;
}

void OpenGLPointers::ensureContext() noexcept {
  if (context != nullptr) {
    context->makeCurrent(context->surface());
  }
}
}