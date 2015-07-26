#ifndef VECTOR2PROPERTY_HPP
#define VECTOR2PROPERTY_HPP

#include <glm/fwd.hpp>

#include "ui/property/VectorProperty.hpp"
#include "Constants.hpp"

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

class BVec2Property : public VectorProperty<bvec2> {
  Q_OBJECT

  Q_PROPERTY(bool x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(bool y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)

public:
  using VectorProperty<bvec2>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::BVEC2; }
};

class IVec2Property : public VectorProperty<ivec2> {
  Q_OBJECT

  Q_PROPERTY(int x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(int y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)

public:
  using VectorProperty<ivec2>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::IVEC2; }
};

class UVec2Property : public VectorProperty<uvec2> {
  Q_OBJECT

  Q_PROPERTY(unsigned int x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)

public:
  using VectorProperty<uvec2>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::UVEC2; }
};

class DVec2Property : public VectorProperty<dvec2> {
  Q_OBJECT

  Q_PROPERTY(double x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(double y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)

public:
  using VectorProperty<dvec2>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC2; }
};

class Vec2Property : public VectorProperty<vec2> {
  Q_OBJECT

  Q_PROPERTY(float x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(float y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)

public:
  using VectorProperty<vec2>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC2; }
};

}

#endif // VECTOR2PROPERTY_HPP
