#ifndef METATYPECONVERTERS_HPP
#define METATYPECONVERTERS_HPP

#include <QtCore/QMetaType>
#include <QtGui/QQuaternion>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

#include <boost/mpl/count.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/single_view.hpp>

#include <glm/glm.hpp>


namespace balls {
void registerMetaTypeConverters() noexcept;

namespace types {
using namespace glm;
using boost::mpl::list;
using boost::mpl::joint_view;
using boost::mpl::single_view;
using boost::mpl::count;
using std::integral_constant;


using Scalars = list<bool, int, uint, float, double>;

namespace glm {
using Vec2s = list<vec2, ivec2, bvec2, dvec2, uvec2>;
using Vec3s = list<vec3, ivec3, bvec3, dvec3, uvec3>;
using Vec4s = list<vec4, ivec4, bvec4, dvec4, uvec4>;
using Vec34s = joint_view<Vec3s, Vec4s>;
using Quats = list<quat, dquat>;
using Fmats =
  list<mat2, mat2x3, mat2x4, mat3x2, mat3, mat3x4, mat4x2, mat4x3, mat4>;
using Dmats = list<dmat2,
                   dmat2x3,
                   dmat2x4,
                   dmat3x2,
                   dmat3,
                   dmat3x4,
                   dmat4x2,
                   dmat4x3,
                   dmat4>;
using Mats = joint_view<Fmats, Dmats>;

using Vecs = joint_view<Vec2s, joint_view<Vec3s, Vec4s>>;
using VecsQuats = joint_view<Vecs, Quats>;
using Vec34sQuats = joint_view<Vec34s, Quats>;
using Len4s = joint_view<Vec4s, Quats>;

using All = joint_view<VecsQuats, Mats>;
}

namespace qt {
using Quats = single_view<QQuaternion>;
using Vecs = list<QVector2D, QVector3D, QVector4D>;
using Vec2s = single_view<QVector2D>;
using Vec3s = single_view<QVector3D>;
using Vec4s = single_view<QVector4D>;
using Vec34s = list<QVector3D, QVector4D>;
using VecsQuats = joint_view<Vecs, Quats>;
using Len4s = list<QVector4D, QQuaternion>;

using All = VecsQuats;
using BuiltIn = joint_view<All, Scalars>;
}

namespace all {
using Vecs = joint_view<glm::Vecs, qt::Vecs>;
using Vec2s = joint_view<glm::Vec2s, qt::Vec2s>;
using Vec3s = joint_view<glm::Vec3s, qt::Vec3s>;
using Vec4s = joint_view<glm::Vec4s, qt::Vec4s>;
using Vec34s = joint_view<glm::Vec34s, qt::Vec34s>;
using Quats = joint_view<glm::Quats, qt::Quats>;
using VecsQuats = joint_view<glm::VecsQuats, qt::VecsQuats>;
using Mats = glm::Mats;
using Len4s = joint_view<glm::Len4s, qt::Len4s>;
using Len4Subscripts = joint_view<glm::Len4s, single_view<QVector4D>>;

using JsonObj = list<QJsonObject, QJsonValue>;
using JsonArr = list<QJsonArray, QJsonValue>;
using String = single_view<QString>;
}

template <class Seq, class T>
struct contains : integral_constant<bool, count<Seq, T>::type::value> {};

template <class A, class B>
struct is_builtin_conv
  : integral_constant<bool,
                      contains<types::qt::BuiltIn, A>()
                        && contains<types::qt::BuiltIn, B>()> {};
}
}
#endif // METATYPECONVERTERS_HPP
