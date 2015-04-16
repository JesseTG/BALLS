#include "precompiled.hpp"
#include "Constants.hpp"

namespace Constants {
const char* DEFAULT_VERTEX_PATH = ":/glsl/default.vert";
const char* DEFAULT_FRAGMENT_PATH = ":/glsl/default.frag";
const char* DEFAULT_GEOMETRY_PATH = ":/glsl/default.geom";

const char* VERT_PROPERTY = "vertName";
const char* FRAG_PROPERTY = "fragName";
const char* OPTION_PROPERTY = "option";
const char* VALUE_PROPERTY = "value";
const char* INDEX_PROPERTY = "index";

const char* SHADER_PREFIX = ":/glsl/";
const char* VERT_EXT = "vert";
const char* GEOM_EXT = "geom";
const char* FRAG_EXT = "frag";

const char* AUTHOR_NAME = "Jesse Talavera-Greenberg";
const char* APP_NAME = "BALLS";

const char* BALLS_ELEMENT = "balls";
const char* SHADERS_ELEMENT = "shaders";
const char* CONFIG_ELEMENT = "config";
const char* VERT_ELEMENT = VERT_EXT;
const char* FRAG_ELEMENT = FRAG_EXT;
const char* GEOM_ELEMENT = GEOM_EXT;
const char* UNIFORMS_ELEMENT = "uniforms";

const char* VERSION_ATT = "version";
const char* GL_MAJOR_ATT = "glmajor";
const char* GL_MINOR_ATT = "glminor";

const char* DELETE_ICON = ":/icons/list-remove.png";
const char* COLOR_ICON = ":/icons/applications-graphics.png";
std::random_device RANDOM_DEVICE;
std::default_random_engine RANDOM(RANDOM_DEVICE());
}
