#ifndef VECTOR4PROPERTY_HPP
#define VECTOR4PROPERTY_HPP

#include <glm/fwd.hpp>

#include "Constants.hpp"
#include "ui/property/VectorProperty.hpp"

namespace balls {

using glm::tvec4;

extern template class VectorProperty<tvec4, int>;
extern template class VectorProperty<tvec4, bool>;
extern template class VectorProperty<tvec4, double>;
extern template class VectorProperty<tvec4, float>;
extern template class VectorProperty<tvec4, unsigned>;

class BVec4Property : public VectorProperty<tvec4, bool> {
  Q_OBJECT

  Q_PROPERTY(bool x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(bool y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(bool z READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(bool w READ _getw WRITE _setw STORED false FINAL)

public:
  using VectorProperty<tvec4, bool>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::BVEC4;
  }
};

class IVec4Property : public VectorProperty<tvec4, int> {
  Q_OBJECT

  Q_PROPERTY(int x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(int y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(int z READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(int w READ _getw WRITE _setw STORED false FINAL)

public:
  using VectorProperty<tvec4, int>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::IVEC4;
  }
};

class UVec4Property : public VectorProperty<tvec4, unsigned int> {
  Q_OBJECT

  Q_PROPERTY(unsigned int x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(unsigned int y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(unsigned int z READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(unsigned int w READ _getw WRITE _setw STORED false FINAL)

public:
  using VectorProperty<tvec4, unsigned int>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::UVEC4;
  }
};

class Vec4Property : public VectorProperty<tvec4, float> {
  Q_OBJECT

  Q_PROPERTY(float x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(float y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(float z READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(float w READ _getw WRITE _setw STORED false FINAL)

public:
  using VectorProperty<tvec4, float>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::VEC4;
  }
};

class DVec4Property : public VectorProperty<tvec4, double> {
  Q_OBJECT

  Q_PROPERTY(double x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(double y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(double z READ _getz WRITE _setz STORED false FINAL)
  Q_PROPERTY(double w READ _getw WRITE _setw STORED false FINAL)

public:
  using VectorProperty<tvec4, double>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::VEC4;
  }
};
}
#endif // VECTOR4PROPERTY_HPP
