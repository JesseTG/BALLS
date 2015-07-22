#include "precompiled.hpp"
#include "shader/ShaderInputs.hpp"

namespace balls {
namespace shader {

namespace attribute {
const AttributeName POSITION = "position";
const AttributeName NORMAL = "normal";
}

namespace uniform {
const UniformName MODEL = "model";
const UniformName VIEW = "view";
const UniformName MODEL_VIEW = "modelView";
const UniformName PROJECTION = "projection";
const UniformName MATRIX = "matrix";

const UniformName MOUSE_COORDS = "mouseCoords";
const UniformName TIME = "time";
const UniformName RANDOM_UNIFORM = "randomUniform";
const UniformName RANDOM_NORMAL = "randomNormal";
const UniformName TRACKBALL = "trackball";
}

namespace out {
const OutName FRAGMENT = "fragment";
}
}
}
