#include "precompiled.hpp"
#include "model/gl/BlendState.hpp"

#include <QOpenGLFunctions_3_0>

namespace balls {

BlendState::BlendState(
  QOpenGLContext* context, QObject* parent = nullptr)
  : QObject(parent), m_gl(context) {}

BlendState::BlendFunction BlendState::func(GLenum param) {
  GLenum g;
  glGetIntegerv(param, &g);
  return static_cast<BlendFunction>(g);
}

BlendState::BlendEquation BlendState::eq(GLenum param) {
  GLenum g;
  glGetIntegerv(param, &g);
  return static_cast<BlendEquation>(g);
}


void BlendState::setSrcRgb(BlendState::BlendFunction) {

}

void BlendState::setDstRgb(BlendState::BlendFunction) {

}

void BlendState::setSrcAlpha(BlendState::BlendFunction) {

}

void BlendState::setDstAlpha(BlendState::BlendFunction) {

}
}
