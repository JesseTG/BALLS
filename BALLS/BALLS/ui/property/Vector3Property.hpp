#ifndef VECTOR3PROPERTY_HPP
#define VECTOR3PROPERTY_HPP

#include <QPropertyEditor/Property.h>
#include "ui/property/VectorProperty.hpp"
#include "Constants.hpp"
#include "util/Util.hpp"

#include <glm/vec3.hpp>

namespace balls {

using glm::bvec3;
using glm::dvec3;
using glm::ivec3;
using glm::vec3;
using glm::uvec3;

extern template class VectorProperty<bvec3>;
extern template class VectorProperty<dvec3>;
extern template class VectorProperty<ivec3>;
extern template class VectorProperty<uvec3>;
extern template class VectorProperty<vec3>;

template<class VectorType>
class Vector3PropertyBase : public VectorProperty<VectorType> {
  using ScalarType = typename VectorType::value_type;

public:
  using VectorProperty<VectorType>::VectorProperty;
  virtual ~Vector3PropertyBase() {}


  ScalarType z() const noexcept {
    return this->component(2);
  }

  void set_z(const ScalarType z) noexcept {
    this->set_component(2, z);
  }
};

extern template class Vector3PropertyBase<bvec3>;
extern template class Vector3PropertyBase<dvec3>;
extern template class Vector3PropertyBase<ivec3>;
extern template class Vector3PropertyBase<uvec3>;
extern template class Vector3PropertyBase<vec3>;

class BVec3Property : public Vector3PropertyBase<bvec3> {
  Q_OBJECT
  Q_CLASSINFO("Type", "bvec3")
  Q_PROPERTY(bool x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(bool y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(bool z READ z WRITE set_z DESIGNABLE true FINAL)
public:
  using Vector3PropertyBase::Vector3PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::BVEC3; }
};

class IVec3Property : public Vector3PropertyBase<ivec3> {
  Q_OBJECT
  Q_CLASSINFO("Type", "ivec3")
  Q_PROPERTY(int x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(int y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(int z READ z WRITE set_z DESIGNABLE true FINAL)
public:
  using Vector3PropertyBase::Vector3PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::IVEC3; }
};

class UVec3Property : public Vector3PropertyBase<uvec3> {
  Q_OBJECT
  Q_CLASSINFO("Type", "uvec3")
  Q_PROPERTY(unsigned int x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int z READ z WRITE set_z DESIGNABLE true FINAL)
public:
  using Vector3PropertyBase::Vector3PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::UVEC3; }
};

class Vec3Property : public Vector3PropertyBase<vec3> {
  Q_OBJECT
  Q_CLASSINFO("Type", "vec3")
  Q_PROPERTY(float x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(float y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(float z READ z WRITE set_z DESIGNABLE true FINAL)
public:
  using Vector3PropertyBase::Vector3PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC3; }
};

class DVec3Property : public Vector3PropertyBase<dvec3> {
  Q_OBJECT
  Q_CLASSINFO("Type", "dvec3")
  Q_PROPERTY(double x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(double y READ y WRITE set_y DESIGNABLE true FINAL)
  Q_PROPERTY(double z READ z WRITE set_z DESIGNABLE true FINAL)
public:
  using Vector3PropertyBase::Vector3PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC3; }
};
}
#endif // VECTOR3PROPERTY_HPP
