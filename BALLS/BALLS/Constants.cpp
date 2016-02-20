#include "precompiled.hpp"
#include "Constants.hpp"

namespace constants {

namespace json {
const char* GL_MAJOR = "glmajor";
const char* GL_MINOR = "glminor";
const char* VERSION = "version";
const char* NAME = "name";
const char* TYPE = "type";
const char* VALUE = "value";
const char* BALLS = "balls";
const char* CONFIG = "config";
const char* FRAG = "frag";
const char* GEOM = "geom";
const char* SHADERS = "shaders";
const char* UNIFORMS = "uniforms";
const char* VERT = "vert";
const char* UNIFORM = "uniform";
const char* GL = "gl";
const char* META = "meta";

const char* W = "w";
const char* X = "x";
const char* Y = "y";
const char* Z = "z";
}

namespace extensions {
const char* BALLS = "balls";
const char* BALLZ = "ballz";
const char* CMPT = "cmpt";
const char* FRAG = "frag";
const char* GEOM = "geom";
const char* TESC = "tctl";
const char* TESS = "tess";
const char* VERT = "vert";
const char* NUTS = "nuts";
const char* NUTZ = "nutz";
}

namespace filters {
const char* BALLS = "*.balls";
const char* BALLZ = "*.ballz";
const char* CMPT = "*.cmpt";
const char* FRAG = "*.frag";
const char* GEOM = "*.geom";
const char* TESC = "*.tctl";
const char* TESS = "*.tess";
const char* VERT = "*.vert";
const char* NUTS = "*.nuts";
const char* NUTZ = "*.nutz";
}

namespace meta {
const char* APP = "BALLS";
const char* AUTHOR = "Jesse Talavera-Greenberg";
const char* AUTHOR_DOMAIN = "jessetg.github.io";
}

namespace paths {
const char* DEFAULT_VERTEX = ":/glsl/default.vert";
const char* DEFAULT_FRAGMENT = ":/glsl/default.frag";
const char* DEFAULT_GEOMETRY = ":/glsl/default.geom";
}

namespace patterns {
// NOTE: QVariant only converts "false" and "0" (or varying capitalizations
// thereof) to false.  Everything else is true.
const QString BOOL = R"|(\w|0|false)|";
const QString FLOAT = R"|([-+]?\d+\.?\d*([eE][-+]?\d+)?)|";
const QString INT = R"|([+-]?\d+)|";
const QString UINT = R"|(\+?(\d+))|";

const QString BRACKETS = R"|(\s*\[\s*%1\s*\]\s*)|";
const QString COMMA = R"|(\s*\,\s*)|";
const QString POSSIBLE_SPACE = R"|(\s*%1\s*)|";
const QString NAMED_CAPTURE = R"|((?'%1'%2))|";

const QString V2 = R"|(\s*(?'x'%1)\s*,\s*(?'y'%1)\s*)|";
const QString V3 = V2 + R"|(,\s*(?'z'%1)\s*)|";
const QString V4 = V3 + R"|(,\s*(?'w'%1)\s*)|";

namespace groups {
const QString X = "x";
const QString Y = "y";
const QString Z = "z";
const QString W = "w";

const std::array<QString, 4> XYZW = {X, Y, Z, W};
}
}

namespace prefixes {
const char* SHADER = ":/glsl/";
const char* EXAMPLE = ":/example/";
}

namespace properties {
const char* EXAMPLE = "example";
const char* INDEX = "index";
const char* OPTION = "option";
const char* VALUE = "value";
const char* W = "w";
const char* X = "x";
const char* Y = "y";
const char* Z = "z";

const char* COL0 = "col0";
const char* COL1 = "col1";
const char* COL2 = "col2";
const char* COL3 = "col3";

const std::array<const char*, 4> XYZW = {X, Y, Z, W};
const std::array<const char*, 4> COLS = {COL0, COL1, COL2, COL3};

const char* ROW0 = "row0";
const char* ROW1 = "row1";
const char* ROW2 = "row2";
const char* ROW3 = "row3";

const std::array<const char*, 4> ROWS = {ROW0, ROW1, ROW2, ROW3};
}

namespace regex {
using namespace patterns;

const QRegularExpression VEC2(
  V2.arg(FLOAT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression BVEC2(
  V2.arg(BOOL),
  QRegularExpression::OptimizeOnFirstUsageOption |
  QRegularExpression::CaseInsensitiveOption
);

const QRegularExpression IVEC2(
  V2.arg(INT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression UVEC2(
  V2.arg(UINT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression VEC3(
  V3.arg(FLOAT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression BVEC3(
  V3.arg(BOOL),
  QRegularExpression::OptimizeOnFirstUsageOption |
  QRegularExpression::CaseInsensitiveOption
);

const QRegularExpression IVEC3(
  V3.arg(INT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression UVEC3(
  V3.arg(UINT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression VEC4(
  V4.arg(FLOAT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression BVEC4(
  V4.arg(BOOL),
  QRegularExpression::OptimizeOnFirstUsageOption |
  QRegularExpression::CaseInsensitiveOption
);

const QRegularExpression IVEC4(
  V4.arg(INT),
  QRegularExpression::OptimizeOnFirstUsageOption
);

const QRegularExpression UVEC4(
  V4.arg(UINT),
  QRegularExpression::OptimizeOnFirstUsageOption
);
}

std::random_device RANDOM_DEVICE;
std::default_random_engine RANDOM(RANDOM_DEVICE());
}
