#include "MeshGenerator.hpp"

#include "mesh/Mesh.hpp"
#include "mesh/MeshFunction.hpp"
#include "mesh/MeshParameter.hpp"

namespace balls {
namespace mesh {

MeshGenerator::MeshGenerator(const string& name,
                             const MeshFunction& function,
                             const MeshParameters& params)
    : _name(name), _function(function), _params(params) {}

Mesh MeshGenerator::getMesh() const {
#ifdef DEBUG
  for (const auto& param : this->_params) {
    float min = param.second.getMin();
    float max = param.second.getMax();
    switch (param.second.getType()) {
    case MeshParameter::Type::Integer: {
      int i = param.second.getInteger();
      Q_ASSERT(min <= i && i <= max);
      break;
    }
    case MeshParameter::Type::Real: {
      float f = param.second.getFloat();
      Q_ASSERT(min <= f && f <= max);
      break;
    }
    default:
      ; // nop
    }
  }
#endif
  return this->_function(this->_params);
}
}
}
