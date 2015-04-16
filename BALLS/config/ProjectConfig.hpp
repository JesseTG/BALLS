#ifndef PROJECTCONFIG_HPP
#define PROJECTCONFIG_HPP

#include <cstdint>
#include <tuple>
#include <unordered_map>

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QOpenGLContext>

#include "config/Settings.hpp"
#include "util/Util.hpp"

namespace balls {
namespace config {
using std::uint8_t;
using std::tuple;
using std::unordered_map;
struct ProjectConfig {

  /// The vertex shader of this project (required)
  QString vertexShader;

  /// The fragment shader of this project (required)
  QString fragmentShader;

  /// The geometry shader of this project (optional)
  QString geometryShader;

  /// The name of each uniform and their types and values
  unordered_map<QString, tuple<GLenum, QVariant>> uniforms;

  /// The major version of BALLS that exported this project
  uint8_t major : 4;

  /// The minor version of BALLS that exported this project
  uint8_t minor : 4;

  /// The OpenGL major version of the computer that exported this project
  uint8_t glMajor : 4;

  /// The OpenGL minor version of the computer that exported this project
  uint8_t glMinor : 4;

  bool dithering : 1;

  FaceCullMode cullMode;

  VertexWinding winding;
};

void saveToFile(const ProjectConfig&, const QString&);
ProjectConfig loadFromFile(const QString&);
}
}

#endif // PROJECTCONFIG_HPP
