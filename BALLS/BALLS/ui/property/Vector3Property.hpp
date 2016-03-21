#ifndef VECTOR3PROPERTY_HPP
#define VECTOR3PROPERTY_HPP

#include <glm/fwd.hpp>

#include "ui/property/VectorProperty.hpp"
#include "Constants.hpp"

namespace balls {

using glm::tvec3;

extern template class VectorProperty<tvec3, bool>;
extern template class VectorProperty<tvec3, double>;
extern template class VectorProperty<tvec3, int>;
extern template class VectorProperty<tvec3, unsigned int>;
extern template class VectorProperty<tvec3, float>;

class BVec3Property : public VectorProperty<tvec3, bool> {
  Q_OBJECT

  Q_PROPERTY(bool x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(bool y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(bool z READ _getz WRITE _setz STORED false FINAL)

public:
  using VectorProperty<tvec3, bool>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::BVEC3; }
};

class IVec3Property : public VectorProperty<tvec3, int> {
  Q_OBJECT

  Q_PROPERTY(int x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(int y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(int z READ _getz WRITE _setz STORED false FINAL)

public:
  using VectorProperty<tvec3, int>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::IVEC3; }
};

class UVec3Property : public VectorProperty<tvec3, unsigned int> {
  Q_OBJECT

  Q_PROPERTY(unsigned int x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(unsigned int y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(unsigned int z READ _getz WRITE _setz STORED false FINAL)

public:
  using VectorProperty<tvec3, unsigned int>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::UVEC3; }
};

class Vec3Property : public VectorProperty<tvec3, float> {
  Q_OBJECT

  Q_PROPERTY(float x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(float y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(float z READ _getz WRITE _setz STORED false FINAL)

public:
  using VectorProperty<tvec3, float>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC3; }
};

class DVec3Property : public VectorProperty<tvec3, double> {
  Q_OBJECT

  Q_PROPERTY(double x READ _getx WRITE _setx STORED false FINAL)
  Q_PROPERTY(double y READ _gety WRITE _sety STORED false FINAL)
  Q_PROPERTY(double z READ _getz WRITE _setz STORED false FINAL)

public:
  using VectorProperty<tvec3, double>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC3; }
};
}
#endif // VECTOR3PROPERTY_HPP
