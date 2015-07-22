#ifndef MESHGENERATOR_HPP
#define MESHGENERATOR_HPP

#include <QtCore/QCoreApplication>

#include "mesh/MeshParameter.hpp"
#include "mesh/MeshFunction.hpp"
#include "util/Util.hpp"

namespace balls {
namespace mesh {

class Mesh;

class MeshGenerator {
  Q_DECLARE_TR_FUNCTIONS(Mesh)

public:
  MeshGenerator(const QString& name,
                const MeshFunction& function,
                const MeshParameters& params = MeshParameters());

  const QString& getName() const noexcept { return this->_name; }

  template<class ParamType>
  void set(const QString& name, const ParamType i) noexcept {
    this->_params[name] = i;
  }

  template<class ParamType>
  ParamType get(const QString& name) const {
    return this->_params.at(name).get<ParamType>();
  }

  Mesh getMesh() const;

private:
  QString _name;
  MeshFunction _function;
  MeshParameters _params;
};
}
}

#endif // MESHGENERATOR_HPP
