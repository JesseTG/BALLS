#include "precompiled.hpp"
#include "util/TypeInfo.hpp"
#include "ui/property/ScalarProperty.hpp"
#include "ui/property/Vector2Property.hpp"
#include "ui/property/Vector3Property.hpp"
#include "ui/property/Vector4Property.hpp"

namespace balls {
namespace util {

namespace types {

template<class P>
Property* makeProp(const QString& name, QObject* subject,
                       Property* parent) noexcept {
  return new P(name, subject, parent);
}

TypeInfoMap info;
void init() noexcept {
  using namespace glm;

  info[QMetaType::Bool] = { GL_BOOL, makeProp<BoolProperty>, QMetaType::Bool };
  info[QMetaType::Int] = { GL_INT, makeProp<IntProperty>, QMetaType::Int };
  info[QMetaType::Float] = { GL_FLOAT, makeProp<FloatProperty>, QMetaType::Float };
  info[QMetaType::Double] = { GL_DOUBLE, makeProp<DoubleProperty>, QMetaType::Double };
  info[QMetaType::UInt] = { GL_UNSIGNED_INT, makeProp<UIntProperty>, QMetaType::UInt };

  info[GL_BOOL] = info[QMetaType::Bool];
  info[GL_INT] = info[QMetaType::Int];
  info[GL_FLOAT] = info[QMetaType::Float];
  info[GL_DOUBLE] = info[QMetaType::Double];
  info[GL_UNSIGNED_INT] = info[QMetaType::UInt];

  info[qMetaTypeId<bvec2>()] = { GL_BOOL_VEC2, makeProp<BVec2Property>, qMetaTypeId<bvec2>() };
  info[qMetaTypeId<ivec2>()] = { GL_INT_VEC2, makeProp<IVec2Property>, qMetaTypeId<ivec2>() };
  info[qMetaTypeId<dvec2>()] = { GL_DOUBLE_VEC2, makeProp<DVec2Property>, qMetaTypeId<dvec2>() };
  info[qMetaTypeId<vec2>()] = { GL_FLOAT_VEC2, makeProp<Vec2Property>, qMetaTypeId<vec2>() };
  info[qMetaTypeId<uvec2>()] = { GL_UNSIGNED_INT_VEC2, makeProp<UVec2Property>, qMetaTypeId<uvec2>() };
  info[QMetaType::QVector2D] = { GL_FLOAT_VEC2, makeProp<Vec2Property>, QMetaType::QVector2D };

  info[GL_BOOL_VEC2] = info[qMetaTypeId<bvec2>()];
  info[GL_INT_VEC2] = info[qMetaTypeId<ivec2>()];
  info[GL_DOUBLE_VEC2] = info[qMetaTypeId<dvec2>()];
  info[GL_FLOAT_VEC2] = info[qMetaTypeId<vec2>()];
  info[GL_UNSIGNED_INT_VEC2] = info[qMetaTypeId<uvec2>()];

  info[qMetaTypeId<bvec3>()] = { GL_BOOL_VEC3, makeProp<BVec3Property>, qMetaTypeId<bvec3>() };
  info[qMetaTypeId<ivec3>()] = { GL_INT_VEC3, makeProp<IVec3Property>, qMetaTypeId<ivec3>() };
  info[qMetaTypeId<dvec3>()] = { GL_DOUBLE_VEC3, makeProp<DVec3Property>, qMetaTypeId<dvec3>() };
  info[qMetaTypeId<vec3>()] = { GL_FLOAT_VEC3, makeProp<Vec3Property>, qMetaTypeId<vec3>() };
  info[qMetaTypeId<uvec3>()] = { GL_UNSIGNED_INT_VEC3, makeProp<UVec3Property>, qMetaTypeId<uvec3>() };
  info[QMetaType::QVector3D] = { GL_FLOAT_VEC3, makeProp<Vec3Property>, QMetaType::QVector3D };

  info[GL_BOOL_VEC3] = info[qMetaTypeId<bvec3>()];
  info[GL_INT_VEC3] = info[qMetaTypeId<ivec3>()];
  info[GL_DOUBLE_VEC3] = info[qMetaTypeId<dvec3>()];
  info[GL_FLOAT_VEC3] = info[qMetaTypeId<vec3>()];
  info[GL_UNSIGNED_INT_VEC3] = info[qMetaTypeId<uvec3>()];

  info[qMetaTypeId<bvec4>()] = { GL_BOOL_VEC4, makeProp<BVec4Property>, qMetaTypeId<bvec4>() };
  info[qMetaTypeId<ivec4>()] = { GL_INT_VEC4, makeProp<IVec4Property>, qMetaTypeId<ivec4>() };
  info[qMetaTypeId<dvec4>()] = { GL_DOUBLE_VEC4, makeProp<DVec4Property>, qMetaTypeId<dvec4>() };
  info[qMetaTypeId<vec4>()] = { GL_FLOAT_VEC4, makeProp<Vec4Property>, qMetaTypeId<vec4>() };
  info[qMetaTypeId<uvec4>()] = { GL_UNSIGNED_INT_VEC4, makeProp<UVec4Property>, qMetaTypeId<uvec4>() };
  info[qMetaTypeId<quat>()] = { GL_FLOAT_VEC4, makeProp<Vec4Property>, qMetaTypeId<quat>() };
  info[qMetaTypeId<dquat>()] = { GL_DOUBLE_VEC4, makeProp<DVec4Property>, qMetaTypeId<dquat>() };
  info[QMetaType::QVector4D] = { GL_FLOAT_VEC4, makeProp<Vec4Property>, QMetaType::QVector4D };
  info[QMetaType::QQuaternion] = { GL_FLOAT_VEC4, makeProp<Vec4Property>, QMetaType::QQuaternion };

  info[GL_BOOL_VEC4] = info[qMetaTypeId<bvec4>()];
  info[GL_INT_VEC4] = info[qMetaTypeId<ivec4>()];
  info[GL_DOUBLE_VEC4] = info[qMetaTypeId<dvec4>()];
  info[GL_FLOAT_VEC4] = info[qMetaTypeId<vec4>()];
  info[GL_UNSIGNED_INT_VEC4] = info[qMetaTypeId<uvec4>()];

  info[qMetaTypeId<mat2>()] = { GL_FLOAT_MAT2, nullptr, qMetaTypeId<mat2>() };
  info[qMetaTypeId<mat4>()] = { GL_FLOAT_MAT4, nullptr, qMetaTypeId<mat4>() };
  info[GL_FLOAT_MAT4] = info[qMetaTypeId<mat4>()];
}
}
}
}
