#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <random>

#include <Qt>
#include <QMetaType>

namespace Constants {
Q_CONSTEXPR int MODEL_ROLE = Qt::ItemDataRole::UserRole;
Q_CONSTEXPR int NEED_BETTER_OPENGL = -1;
Q_CONSTEXPR int SHADER_PROGRAMS_UNAVAILABLE = -2;
Q_CONSTEXPR int SHADER_TYPES_UNAVAILABLE = -3;
Q_CONSTEXPR int BUFFERS_UNAVAILABLE = -4;

Q_CONSTEXPR int VERSION_MAJOR = 0;
Q_CONSTEXPR int VERSION_MINOR = 0;

extern const char* DEFAULT_VERTEX_PATH;
extern const char* DEFAULT_FRAGMENT_PATH;
extern const char* DEFAULT_GEOMETRY_PATH;

extern const char* VERT_PROPERTY;
extern const char* FRAG_PROPERTY;
extern const char* OPTION_PROPERTY;
extern const char* VALUE_PROPERTY;
extern const char* INDEX_PROPERTY;

extern const char* SHADER_PREFIX;
extern const char* VERT_EXT;
extern const char* GEOM_EXT;
extern const char* FRAG_EXT;

extern const char* AUTHOR_NAME;
extern const char* APP_NAME;

extern const char* BALLS_ELEMENT;
extern const char* SHADERS_ELEMENT;
extern const char* VERT_ELEMENT;
extern const char* FRAG_ELEMENT;
extern const char* GEOM_ELEMENT;
extern const char* CONFIG_ELEMENT;
extern const char* UNIFORMS_ELEMENT;

extern const char* VERSION_ATT;
extern const char* GL_MAJOR_ATT;
extern const char* GL_MINOR_ATT;

extern const char* DELETE_ICON;
extern const char* COLOR_ICON;

extern std::random_device RANDOM_DEVICE;
extern std::default_random_engine RANDOM;
}

#endif // CONSTANTS_HPP
