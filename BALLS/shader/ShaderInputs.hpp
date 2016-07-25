#ifndef SHADERINPUTS_HPP
#define SHADERINPUTS_HPP

class QString;

namespace balls {
namespace shader {

using AttributeName = QString;
using UniformName = QString;
using OutName = QString;

namespace attribute {
extern const AttributeName POSITION;
extern const AttributeName NORMAL;
extern const AttributeName TEXCOORDS;
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
extern const UniformName TRACKBALL;
}

namespace out {
extern const OutName FRAGMENT;
}
}
}
#endif // SHADERINPUTS_HPP
