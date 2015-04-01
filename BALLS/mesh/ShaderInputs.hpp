#ifndef SHADERINPUTS_HPP
#define SHADERINPUTS_HPP

namespace balls {
namespace shader {

using AttributeName = const char*;
using UniformName = const char*;
using OutName = const char*;

namespace attribute {

extern const AttributeName POSITION;
extern const AttributeName NORMAL;
}

namespace uniform {

extern const UniformName COLOR;
extern const UniformName MATRIX;
extern const UniformName LIGHT_COLOR;
extern const UniformName LIGHT_DIRECTION;
extern const UniformName LIGHT_INTENSITY;
}

namespace out {


extern const OutName FRAGMENT;
}
}
}
#endif // SHADERINPUTS_HPP
