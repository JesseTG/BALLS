#include "precompiled.hpp"

#include "gl/OpenGLPointers.hpp"

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_1>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLFunctions_4_4_Core>
#include <QOpenGLFunctions_4_5_Core>

namespace balls {

namespace {
template <class QOpenGLF>
QOpenGLF* _getGl(QOpenGLContext* context) noexcept {
  QOpenGLF* gl = context->versionFunctions<QOpenGLF>();

  if (gl) {
    // If we have this version of OpenGL available...
    if (!gl->initializeOpenGLFunctions()) {
      qDebug() << "Cannot initialize" << typeid(QOpenGLF).name() << gl;
    }
  }

  return gl;
}
}

OpenGLPointers::OpenGLPointers(QOpenGLContext* ctx)
  : context(ctx),
    gl31(_getGl<QOpenGLFunctions_3_1>(context)),
    gl32(_getGl<QOpenGLFunctions_3_2_Core>(context)),
    gl33(_getGl<QOpenGLFunctions_3_3_Core>(context)),
    gl40(_getGl<QOpenGLFunctions_4_0_Core>(context)),
    gl41(_getGl<QOpenGLFunctions_4_1_Core>(context)),
    gl42(_getGl<QOpenGLFunctions_4_2_Core>(context)),
    gl43(_getGl<QOpenGLFunctions_4_3_Core>(context)),
    gl44(_getGl<QOpenGLFunctions_4_4_Core>(context)),
    gl45(_getGl<QOpenGLFunctions_4_5_Core>(context)) {
}

OpenGLPointers::OpenGLPointers()
  : context(nullptr),
    gl31(nullptr),
    gl32(nullptr),
    gl40(nullptr),
    gl41(nullptr),
    gl42(nullptr),
    gl43(nullptr),
    gl44(nullptr),
    gl45(nullptr) {}

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

QOpenGLFunctions_4_4_Core* OpenGLPointers::gl44Current() noexcept {
  ensureContext();

  return gl44;
}

QOpenGLFunctions_4_5_Core* OpenGLPointers::gl45Current() noexcept {
  ensureContext();

  return gl45;
}

void OpenGLPointers::ensureContext() noexcept {
  if (context != nullptr) {
    if (!context->makeCurrent(context->surface())) {
      qDebug() << "Cannot make context current";
    }
  }
}
}
