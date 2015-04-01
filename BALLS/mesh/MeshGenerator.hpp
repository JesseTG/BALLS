#ifndef MESHGENERATOR_HPP
#define MESHGENERATOR_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

#include "mesh/MeshParameter.hpp"
#include "mesh/MeshFunction.hpp"
#include "mesh/Mesh.hpp"

namespace balls {
namespace mesh {

using std::pair;
using std::string;
using std::unordered_map;

class MeshGenerator {
    public:
    MeshGenerator(const string &name,
                  const MeshFunction &function,
                  const MeshParameters &params = MeshParameters());

    const string &getName() const noexcept { return this->_name; }

    void set(const string &name, const int i) noexcept {
        this->_params[name.c_str()] = MeshParameter(i);
    }

    void set(const string &name, const float f) noexcept {
        this->_params[name.c_str()] = MeshParameter(f);
    }

    void set(const string &name, const bool b) noexcept {
        this->_params[name.c_str()] = MeshParameter(b);
    }

    int getInteger(const string &name) const {
        return this->_params.at(name.c_str()).getInteger();
    }

    float getFloat(const string &name) const {
        return this->_params.at(name.c_str()).getFloat();
    }

    bool getBool(const string &name) const {
        return this->_params.at(name.c_str()).getBool();
    }

    Mesh getMesh() const;

    private:
    string _name;
    MeshFunction _function;
    MeshParameters _params;
};
}
}

#endif  // MESHGENERATOR_HPP
