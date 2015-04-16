#ifndef MESHGENERATOR_HPP
#define MESHGENERATOR_HPP

#include "mesh/MeshParameter.hpp"
#include "mesh/MeshFunction.hpp"
#include "mesh/Mesh.hpp"
#include "util/Util.hpp"

namespace balls {
namespace mesh {

class MeshGenerator {
public:
  MeshGenerator(const QString& name,
                const MeshFunction& function,
                const MeshParameters& params = MeshParameters());

  const QString& getName() const noexcept { return this->_name; }

  void set(const QString& name, const int i) noexcept {
    this->_params[name] = MeshParameter(i);
  }

  void set(const QString& name, const float f) noexcept {
    this->_params[name] = MeshParameter(f);
  }

  void set(const QString& name, const bool b) noexcept {
    this->_params[name] = MeshParameter(b);
  }

  int getInteger(const QString& name) const {
    return this->_params.at(name).getInteger();
  }

  float getFloat(const QString& name) const {
    return this->_params.at(name).getFloat();
  }

  bool getBool(const QString& name) const {
    return this->_params.at(name).getBool();
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
