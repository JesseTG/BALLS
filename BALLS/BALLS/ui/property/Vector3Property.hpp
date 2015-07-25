#ifndef VECTOR3PROPERTY_HPP
#define VECTOR3PROPERTY_HPP

#include <glm/fwd.hpp>

#include "ui/property/VectorProperty.hpp"
#include "Constants.hpp"

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

class BVec3Property : public VectorProperty<bvec3> {
  Q_OBJECT

  Q_PROPERTY(bool x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(bool y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)
  Q_PROPERTY(bool z READ (_get<2>) WRITE (_set<2>) DESIGNABLE true FINAL)

public:
  using VectorProperty<bvec3>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::BVEC3; }
};

class IVec3Property : public VectorProperty<ivec3> {
  Q_OBJECT

  Q_PROPERTY(int x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(int y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)
  Q_PROPERTY(int z READ (_get<2>) WRITE (_set<2>) DESIGNABLE true FINAL)

public:
  using VectorProperty<ivec3>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::IVEC3; }
};

class UVec3Property : public VectorProperty<uvec3> {
  Q_OBJECT

  Q_PROPERTY(unsigned int x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)
  Q_PROPERTY(unsigned int z READ (_get<2>) WRITE (_set<2>) DESIGNABLE true FINAL)

public:
  using VectorProperty<uvec3>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::UVEC3; }
};

class Vec3Property : public VectorProperty<vec3> {
  Q_OBJECT

  Q_PROPERTY(float x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(float y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)
  Q_PROPERTY(float z READ (_get<2>) WRITE (_set<2>) DESIGNABLE true FINAL)

public:
  using VectorProperty<vec3>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC3; }
};

class DVec3Property : public VectorProperty<dvec3> {
  Q_OBJECT

  Q_PROPERTY(double x READ (_get<0>) WRITE (_set<0>) DESIGNABLE true FINAL)
  Q_PROPERTY(double y READ (_get<1>) WRITE (_set<1>) DESIGNABLE true FINAL)
  Q_PROPERTY(double z READ (_get<2>) WRITE (_set<2>) DESIGNABLE true FINAL)

public:
  using VectorProperty<dvec3>::VectorProperty;
protected:
  const QRegularExpression& regex() const noexcept override { return constants::regex::VEC3; }
};
}
#endif // VECTOR3PROPERTY_HPP
