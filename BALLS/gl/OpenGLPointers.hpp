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
class QOpenGLFunctions_4_4_Core;
class QOpenGLFunctions_4_5_Core;

namespace balls {

/**
 * @brief Contains pointers to all QOpenGLFunctions that refer to OpenGL
 * functionality supported by the hardware.  Assumes that if version X is
 * supported, then all features for versions < X are too.
 */
struct OpenGLPointers {
  Q_GADGET

public:
  explicit OpenGLPointers(QOpenGLContext*);
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
  QOpenGLFunctions_4_4_Core* gl44;
  QOpenGLFunctions_4_5_Core* gl45;

  QOpenGLFunctions_3_0* gl30Current() noexcept;
  QOpenGLFunctions_3_1* gl31Current() noexcept;
  QOpenGLFunctions_3_2_Core* gl32Current() noexcept;
  QOpenGLFunctions_3_3_Core* gl33Current() noexcept;
  QOpenGLFunctions_4_0_Core* gl40Current() noexcept;
  QOpenGLFunctions_4_1_Core* gl41Current() noexcept;
  QOpenGLFunctions_4_2_Core* gl42Current() noexcept;
  QOpenGLFunctions_4_3_Core* gl43Current() noexcept;
  QOpenGLFunctions_4_4_Core* gl44Current() noexcept;
  QOpenGLFunctions_4_5_Core* gl45Current() noexcept;
private:
  void ensureContext() noexcept;
};
}

Q_DECLARE_METATYPE(balls::OpenGLPointers*)

#endif // OPENGLPOINTERS_HPP
