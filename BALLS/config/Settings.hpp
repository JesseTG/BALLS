#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QtCore/QVariant>
#include <QtGui/QOpenGLFunctions>

namespace balls {
namespace config {

namespace SettingKey {
const extern QString WireFrame;
const extern QString DepthTestEnabled;
const extern QString FaceCullingEnabled;
const extern QString Dithering;
const extern QString ClipDistance;
};

enum class BlendFunction {
  None = -1,
  Zero = GL_ZERO,
  One = GL_ONE,
  SourceColor = GL_SRC_COLOR,
  OneMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,
  DestinationColor = GL_DST_COLOR,
  OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,
  SourceAlpha = GL_SRC_ALPHA,
  OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
  DestinationAlpha = GL_DST_ALPHA,
  OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
  ConstantColor = GL_CONSTANT_COLOR,
  OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
  ConstantAlpha = GL_CONSTANT_ALPHA,
  OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
};

enum class ColorCopyFunction {
  Copy = GL_COPY,
  CopyInverted = GL_COPY_INVERTED,
  Clear = GL_CLEAR,
  Set = GL_SET,
  NoOp = GL_NOOP,
  Invert = GL_INVERT,
  And = GL_AND,
  Nand = GL_NAND,
  Or = GL_OR,
  Nor = GL_NOR,
  Xor = GL_XOR,
  Equivalent = GL_EQUIV,
  AndReverse = GL_AND_REVERSE,
  AndInverted = GL_AND_INVERTED,
  OrReverse = GL_OR_REVERSE,
  OrInverted = GL_OR_INVERTED,
};

enum class FaceCullMode {
  None = 0,
  Front = GL_FRONT,
  Back = GL_BACK,
  FrontAndBack = GL_FRONT_AND_BACK,
};

enum class VertexWinding {
  Clockwise = GL_CW,
  CounterClockwise = GL_CCW,
};

enum class DepthFunction {
  Off,
  Never = GL_NEVER,
  Less = GL_LESS,
  Equal = GL_EQUAL,
  LessEqual = GL_LEQUAL,
  Greater = GL_GREATER,
  NotEqual = GL_NOTEQUAL,
  GreaterEqual = GL_GEQUAL,
  Always = GL_ALWAYS,
};

const char* to_cstring(const BlendFunction);
const char* to_cstring(const ColorCopyFunction);

struct Setting {
  QVariant value;
  bool changed;

  Setting() : Setting(0) {}
  Setting(const QVariant& var, const bool c) : value(var), changed(c) {}
  Setting(const QVariant& var) : Setting(var, false) {}
};
}
}

#endif // OPTIONS_HPP
