#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>
#include <random>

#include <QMetaType>
#include <Qt>

namespace constants {

constexpr double EPSILON = 0.00001;
constexpr int MODEL_ROLE = Qt::ItemDataRole::UserRole;
constexpr Qt::ItemFlags RESOURCE_FLAGS = Qt::ItemNeverHasChildren
  | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
  | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

namespace json {
extern const char *VERSION;
extern const char *GL_MAJOR;
extern const char *GL_MINOR;
extern const char *NAME;
extern const char *META;
extern const char *VALUE;
extern const char *TYPE;
extern const char *BALLS;
extern const char *SHADERS;
extern const char *VERT;
extern const char *FRAG;
extern const char *GEOM;
extern const char *CONFIG;
extern const char *UNIFORMS;
extern const char *UNIFORM;
extern const char *GL;

extern const char *W;
extern const char *X;
extern const char *Y;
extern const char *Z;
}

namespace errors {
constexpr int NEED_BETTER_OPENGL = -1;
constexpr int SHADER_PROGRAMS_UNAVAILABLE = -2;
constexpr int SHADER_TYPES_UNAVAILABLE = -3;
constexpr int BUFFERS_UNAVAILABLE = -4;
}

namespace extensions {
extern const char *BALLS;
extern const char *BALLZ;
extern const char *CMPT;
extern const char *FRAG;
extern const char *GEOM;
extern const char *TESC;
extern const char *TESS;
extern const char *VERT;
extern const char *NUTS;
extern const char *NUTZ;
}

namespace filters {
extern const char *BALLS;
extern const char *BALLZ;
extern const char *CMPT;
extern const char *FRAG;
extern const char *GEOM;
extern const char *TESC;
extern const char *TESS;
extern const char *VERT;
extern const char *NUTS;
extern const char *NUTZ;
}

namespace meta {
constexpr int VERSION_MAJOR = 0;
constexpr int VERSION_MINOR = 0;

extern const char *AUTHOR;
extern const char *APP;
extern const char *AUTHOR_DOMAIN;
}

namespace paths {
extern const char *DEFAULT_VERTEX;
extern const char *DEFAULT_FRAGMENT;
extern const char *DEFAULT_GEOMETRY;
}

namespace patterns {
extern const QString BOOL;
extern const QString INT;
extern const QString FLOAT;
extern const QString UINT;
extern const QString BRACKETS;
extern const QString COMMA;
extern const QString POSSIBLE_SPACE;

namespace groups {
extern const QString X;
extern const QString Y;
extern const QString Z;
extern const QString W;

extern const std::array<QString, 4> XYZW;
}
}

namespace prefixes {
extern const char *SHADER;
extern const char *EXAMPLE;
}

namespace properties {
extern const char *EXAMPLE;
extern const char *OPTION;
extern const char *VALUE;
extern const char *VERT;
extern const char *W;
extern const char *X;
extern const char *Y;
extern const char *Z;

extern const char *COL0;
extern const char *COL1;
extern const char *COL2;
extern const char *COL3;

extern const char *ROW0;
extern const char *ROW1;
extern const char *ROW2;
extern const char *ROW3;

extern const std::array<const char *, 4> XYZW;
extern const std::array<const char *, 4> ROWS;
extern const std::array<const char *, 4> COLS;
}

namespace regex {
extern const QRegularExpression VEC2;
extern const QRegularExpression BVEC2;
extern const QRegularExpression IVEC2;
extern const QRegularExpression UVEC2;

extern const QRegularExpression VEC3;
extern const QRegularExpression BVEC3;
extern const QRegularExpression IVEC3;
extern const QRegularExpression UVEC3;

extern const QRegularExpression VEC4;
extern const QRegularExpression BVEC4;
extern const QRegularExpression IVEC4;
extern const QRegularExpression UVEC4;
}

extern std::random_device RANDOM_DEVICE;
extern std::default_random_engine RANDOM;
}

#endif // CONSTANTS_HPP
