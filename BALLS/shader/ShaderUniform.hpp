#ifndef SHADERUNIFORM_HPP
#define SHADERUNIFORM_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtGui/QOpenGLFunctions>

#include "util/Util.hpp"

namespace balls {
namespace shader {
using std::function;

using UniformFunction = function<QVariant(const GLenum)>;
using UniformMap = std::unordered_map<QString, GLenum>;
using OrderedUniformMap = std::map<QString, GLenum>;
}
}

#endif // SHADERUNIFORM_HPP
