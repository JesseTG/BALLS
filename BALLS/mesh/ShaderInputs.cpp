#include "mesh/ShaderInputs.hpp"

namespace balls {
namespace shader {

namespace attribute {
const AttributeName POSITION = "position";
const AttributeName NORMAL = "normal";
}

namespace uniform {
const UniformName COLOR = "color";
const UniformName MATRIX = "matrix";
const UniformName LIGHT_COLOR = "lightColor";
const UniformName LIGHT_DIRECTION = "lightDirection";
const UniformName LIGHT_INTENSITY = "lightIntensity";
}

namespace out {
const OutName FRAGMENT = "fragment";
}
}
}
