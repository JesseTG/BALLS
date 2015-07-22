#ifndef MESHPARAMETER_HPP
#define MESHPARAMETER_HPP

#include <cstdint>

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtCore/QVariant>

namespace balls {
namespace mesh {

class MeshParameter {
public:
  template<class T>
MeshParameter(const T& i, const int min, const int max) noexcept :
  min(min), max(max), _value(i) {}

MeshParameter() noexcept :
  min(0), max(0), _value(0) { }

  template<class T>
  void set(const T& t) noexcept { this->_value = t; }

  template<class T>
  T get() const noexcept { return this->_value.value<T>(); }

  int getMin() const noexcept { return this->min; }

  int getMax() const noexcept { return this->max; }

  void setMin(const int min) noexcept { this->min = min; }

  void setMax(const int max) noexcept { this->max = max; }
private:
  int min, max;

  QVariant _value;
};

typedef std::unordered_map<QString, MeshParameter> MeshParameters;
}
}

#endif // MESHPARAMETER_HPP
