#ifndef SHADERINPUTS_HPP
#define SHADERINPUTS_HPP

#include <unordered_map>

#include <QtCore/QMetaType>
#include <QtGui/QOpenGLFunctions>

namespace balls {
namespace shader {

using AttributeName = QString;
using UniformName = QString;
using OutName = QString;

namespace attribute {
extern const AttributeName POSITION;
extern const AttributeName NORMAL;
}

namespace uniform {
extern const UniformName MODEL;
extern const UniformName VIEW;
extern const UniformName MODEL_VIEW;
extern const UniformName PROJECTION;
extern const UniformName MATRIX;

extern const UniformName MOUSE_COORDS;
extern const UniformName TIME;
extern const UniformName RANDOM_UNIFORM;
extern const UniformName RANDOM_NORMAL;
}

namespace out {
extern const OutName FRAGMENT;
}
}
}
#endif // SHADERINPUTS_HPP
