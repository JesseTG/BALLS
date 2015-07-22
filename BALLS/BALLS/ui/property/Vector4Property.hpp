#ifndef VECTOR4PROPERTY_HPP
#define VECTOR4PROPERTY_HPP

#include <QPropertyEditor/Property.h>

#include <glm/vec4.hpp>

#include "ui/property/VectorProperty.hpp"
#include "Constants.hpp"
#include "util/Util.hpp"

namespace balls {

using glm::bvec4;
using glm::dvec4;
using glm::ivec4;
using glm::vec4;
using glm::uvec4;

extern template class VectorProperty<ivec4>;
extern template class VectorProperty<bvec4>;
extern template class VectorProperty<dvec4>;
extern template class VectorProperty<vec4>;
extern template class VectorProperty<uvec4>;

template<class VectorType>
class Vector4PropertyBase : public VectorProperty<VectorType> {
  using ScalarType = typename VectorType::value_type;
public:
  using VectorProperty<VectorType>::VectorProperty;
  virtual ~Vector4PropertyBase() {}

  ScalarType z() const noexcept {
    return this->component(2);
  }

  void set_z(const ScalarType z) noexcept {
    this->set_component(2, z);
  }

  ScalarType w() const noexcept {
    return this->component(3);
  }

  void set_w(const ScalarType w) noexcept {
    this->set_component(3, w);
  }
};

extern template class Vector4PropertyBase<bvec4>;
extern template class Vector4PropertyBase<dvec4>;
extern template class Vector4PropertyBase<ivec4>;
extern template class Vector4PropertyBase<uvec4>;
extern template class Vector4PropertyBase<vec4>;

class BVec4Property : public Vector4PropertyBase<bvec4> {
  Q_OBJECT
  Q_CLASSINFO("Type", "bvec4")
  Q_PROPERTY(bool x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(bool y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(bool z READ z WRITE set_z DESIGNABLE true FINAL)
  Q_PROPERTY(bool w READ w WRITE set_w DESIGNABLE true FINAL)
public:
  using Vector4PropertyBase::Vector4PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::BVEC4; }
};

class IVec4Property : public Vector4PropertyBase<ivec4> {
  Q_OBJECT
  Q_CLASSINFO("Type", "ivec4")
  Q_PROPERTY(int x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(int y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(int z READ z WRITE set_z DESIGNABLE true FINAL)
  Q_PROPERTY(int w READ w WRITE set_w DESIGNABLE true FINAL)
public:
  using Vector4PropertyBase::Vector4PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::IVEC4; }
};

class UVec4Property : public Vector4PropertyBase<uvec4> {
  Q_OBJECT
  Q_CLASSINFO("Type", "uvec4")
  Q_PROPERTY(unsigned int x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int z READ z WRITE set_z DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int w READ w WRITE set_w DESIGNABLE true FINAL)
public:
  using Vector4PropertyBase::Vector4PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::UVEC4; }
};

class Vec4Property : public Vector4PropertyBase<vec4> {
  Q_OBJECT
  Q_CLASSINFO("Type", "vec4")
  Q_PROPERTY(float x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(float y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(float z READ z WRITE set_z DESIGNABLE true FINAL)
  Q_PROPERTY(float w READ w WRITE set_w DESIGNABLE true FINAL)
public:
  using Vector4PropertyBase::Vector4PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC4; }
};

class DVec4Property : public Vector4PropertyBase<dvec4> {
  Q_OBJECT
  Q_CLASSINFO("Type", "dvec4")
  Q_PROPERTY(double x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(double y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(double z READ z WRITE set_z DESIGNABLE true FINAL)
  Q_PROPERTY(double w READ w WRITE set_w DESIGNABLE true FINAL)
public:
  using Vector4PropertyBase::Vector4PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC4; }
};
}
#endif // VECTOR4PROPERTY_HPP
