#include "precompiled.hpp"
#include "MeshGenerator.hpp"

#include "mesh/Mesh.hpp"
#include "mesh/MeshFunction.hpp"
#include "mesh/MeshParameter.hpp"

namespace balls {
namespace mesh {

MeshGenerator::MeshGenerator(const QString& name,
                             const MeshFunction& function,
                             const MeshParameters& params)
  : _name(name), _function(function), _params(params) {}

Mesh MeshGenerator::getMesh() const {
  #ifdef DEBUG

  for (const auto& param : this->_params) {
    int min = param.second.getMin();
    int max = param.second.getMax();
    float f = param.second.get<float>();

    Q_ASSERT(min <= f && f <= max);
  }

  #endif
  return this->_function(this->_params);
}

}
}
