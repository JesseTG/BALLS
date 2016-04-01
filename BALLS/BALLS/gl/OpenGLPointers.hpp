#ifndef OPENGLPOINTERS_HPP
#define OPENGLPOINTERS_HPP

#include <QObject>

class QOpenGLContext;
class QOpenGLFunctions_3_0;
class QOpenGLFunctions_3_1;
class QOpenGLFunctions_3_2_Core;
class QOpenGLFunctions_3_3_Core;
class QOpenGLFunctions_4_0_Core;
class QOpenGLFunctions_4_1_Core;
class QOpenGLFunctions_4_2_Core;
class QOpenGLFunctions_4_3_Core;

namespace balls {

/**
 * @brief Contains pointers to all QOpenGLFunctions that refer to OpenGL
 * functionality supported by the hardware.  Assumes that if version X is
 * supported, then all features for versions < X are too.
 * @todo Support OpenGL 4.4 and 4.5 (when I can upgrade to Qt 5.5 or 5.6)
 */
struct OpenGLPointers {
  Q_GADGET

public:
  OpenGLPointers(QOpenGLContext*);
  OpenGLPointers();

  QOpenGLContext* context;
  QOpenGLFunctions_3_0* gl30;
  QOpenGLFunctions_3_1* gl31;
  QOpenGLFunctions_3_2_Core* gl32;
  QOpenGLFunctions_3_3_Core* gl33;
  QOpenGLFunctions_4_0_Core* gl40;
  QOpenGLFunctions_4_1_Core* gl41;
  QOpenGLFunctions_4_2_Core* gl42;
  QOpenGLFunctions_4_3_Core* gl43;
};
}

Q_DECLARE_METATYPE(balls::OpenGLPointers*)

#endif // OPENGLPOINTERS_HPP
