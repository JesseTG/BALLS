#ifndef VECTOR2PROPERTY_HPP
#define VECTOR2PROPERTY_HPP

#include <QObject>
#include <QString>
#include <QPropertyEditor/Property.h>

#include <glm/vec2.hpp>

#include "ui/property/VectorProperty.hpp"
#include "Constants.hpp"
#include "util/Util.hpp"

namespace balls {

using glm::bvec2;
using glm::dvec2;
using glm::ivec2;
using glm::vec2;
using glm::uvec2;

extern template class VectorProperty<ivec2>;
extern template class VectorProperty<bvec2>;
extern template class VectorProperty<dvec2>;
extern template class VectorProperty<vec2>;
extern template class VectorProperty<uvec2>;

template<class VectorType>
class Vector2PropertyBase : public VectorProperty<VectorType> {

public:
  using VectorProperty<VectorType>::VectorProperty;

  virtual ~Vector2PropertyBase() {}
};

extern template class Vector2PropertyBase<ivec2>;
extern template class Vector2PropertyBase<bvec2>;
extern template class Vector2PropertyBase<uvec2>;
extern template class Vector2PropertyBase<vec2>;
extern template class Vector2PropertyBase<dvec2>;

class BVec2Property : public Vector2PropertyBase<bvec2> {
  Q_OBJECT
  Q_CLASSINFO("Type", "bvec2")
  Q_PROPERTY(bool x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(bool y READ y WRITE set_y DESIGNABLE true FINAL)
public:
  using Vector2PropertyBase::Vector2PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::BVEC2; }
};

class IVec2Property : public Vector2PropertyBase<ivec2> {
  Q_OBJECT
  Q_CLASSINFO("Type", "ivec2")
  Q_PROPERTY(int x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(int y READ y WRITE set_y DESIGNABLE true FINAL)
public:
  using Vector2PropertyBase::Vector2PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::IVEC2; }
};

class UVec2Property : public Vector2PropertyBase<uvec2> {
  Q_OBJECT
  Q_CLASSINFO("Type", "uvec2")
  Q_PROPERTY(unsigned int x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int y READ y WRITE set_y DESIGNABLE true FINAL)
public:
  using Vector2PropertyBase::Vector2PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::UVEC2; }
};

class DVec2Property : public Vector2PropertyBase<dvec2> {
  Q_OBJECT
  Q_CLASSINFO("Type", "dvec2")
  Q_PROPERTY(double x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(double y READ y WRITE set_y DESIGNABLE true FINAL)

public:
  using Vector2PropertyBase::Vector2PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC2; }
};

class Vec2Property : public Vector2PropertyBase<vec2> {
  Q_OBJECT
  Q_CLASSINFO("Type", "vec2")
  Q_PROPERTY(float x READ x WRITE set_x DESIGNABLE true FINAL)
  Q_PROPERTY(float y READ y WRITE set_y DESIGNABLE true FINAL)

public:
  using Vector2PropertyBase::Vector2PropertyBase;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC2; }
};

}

#endif // VECTOR2PROPERTY_HPP
