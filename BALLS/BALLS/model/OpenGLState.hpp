#ifndef OPENGLSTATE_HPP
#define OPENGLSTATE_HPP

#include <QColor>
#include <QObject>
#include <QOpenGLContext>

#include <glm/fwd.hpp>

#include "gl/OpenGLPointers.hpp"

namespace balls {

using glm::bvec4;

class OpenGLState : public QObject {
  Q_OBJECT

  /* Categories of OpenGL state:
   * - Blend State (DONE)
   * - Implementation info (DONE), except extensions
   * - Limits (GL_MAX_VARYING_COMPONENTS, etc.)
   * - Hints (DONE)
   * - Stencil (DONE)
   * - Depth (DONE)
   * - Color (DONE)
   * - Geometry (DONE)
   * - Sampling (DONE)
   * - View (scissor, viewport) (DONE)
   *
   */

  // GL_RASTERIZER_DISCARD
  // GL_CLIP_DISTANCE
  // GL_TEXTURE_CUBE_MAP_SEAMLESS

public:
  explicit OpenGLState(QOpenGLContext*, QObject* = nullptr);

private /* members */:
  OpenGLPointers m_gl;
};
}

#endif // OPENGLSTATE_HPP
