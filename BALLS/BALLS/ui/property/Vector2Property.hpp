#ifndef VECTOR2PROPERTY_HPP
#define VECTOR2PROPERTY_HPP

#include <glm/fwd.hpp>

#include "Constants.hpp"
#include "ui/property/VectorProperty.hpp"

namespace balls {

using glm::tvec2;

extern template class VectorProperty<tvec2, int>;
extern template class VectorProperty<tvec2, bool>;
extern template class VectorProperty<tvec2, double>;
extern template class VectorProperty<tvec2, float>;
extern template class VectorProperty<tvec2, unsigned int>;

class BVec2Property : public VectorProperty<tvec2, bool> {
  Q_OBJECT

  Q_PROPERTY(bool x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(bool y READ _gety WRITE _sety STORED false FINAL)

public:
  using VectorProperty<tvec2, bool>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::BVEC2;
  }
};

class IVec2Property : public VectorProperty<tvec2, int> {
  Q_OBJECT

  Q_PROPERTY(int x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(int y READ _gety WRITE _sety STORED false FINAL)

public:
  using VectorProperty<tvec2, int>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::IVEC2;
  }
};

class UVec2Property : public VectorProperty<tvec2, unsigned int> {
  Q_OBJECT

  Q_PROPERTY(unsigned int x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(unsigned int y READ _gety WRITE _sety STORED false FINAL)

public:
  using VectorProperty<tvec2, unsigned int>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::UVEC2;
  }
};

class DVec2Property : public VectorProperty<tvec2, double> {
  Q_OBJECT

  Q_PROPERTY(double x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(double y READ _gety WRITE _sety STORED false FINAL)

public:
  using VectorProperty<tvec2, double>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::VEC2;
  }
};

class Vec2Property : public VectorProperty<tvec2, float> {
  Q_OBJECT

  Q_PROPERTY(float x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(float y READ _gety WRITE _sety STORED false FINAL)

public:
  using VectorProperty<tvec2, float>::VectorProperty;

protected:
  const QRegularExpression& regex() const noexcept override {
    return constants::regex::VEC2;
  }
};
}

#endif // VECTOR2PROPERTY_HPP
