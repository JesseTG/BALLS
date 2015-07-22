#include "precompiled.hpp"
#include "util/MetaTypeConverters.hpp"

#include <boost/mpl/count.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/single_view.hpp>

#include <glm/glm.hpp>
#include <QtGlobal>
#include <QMetaType>

namespace balls {

using std::enable_if;
using std::is_same;
using std::is_arithmetic;
using std::decay;
using std::integral_constant;
using boost::mpl::count;
using boost::mpl::joint_view;
using types::is_builtin_conv;
using types::contains;

template<bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

/// Element type of T
template<class T>
struct Element {
  using type = const typename decay<decltype(T()[0])>::type;
};

template<>
struct Element<QQuaternion> {
  using type = const typename decay<decltype(QQuaternion().x())>::type;
};

template<class T>
using E = typename Element<T>::type;

template<class T>
using is_QQuaternion = is_same<QQuaternion, T>;

template<class T>
using is_scalar = contains<types::Scalars, T>;

template<class T>
using is_vecquat = contains<types::all::VecsQuats, T>;

template<class T>
using is_vec2 = contains<types::all::Vec2s, T>;

template<class T>
using is_vec3 = contains<types::all::Vec3s, T>;

template<class T>
using is_vec34 = contains<types::all::Vec34s, T>;

template<class T>
using is_vec4 = contains<types::all::Vec4s, T>;

template<class T>
using is_quat = contains<types::all::Quats, T>;

template<class T>
using is_glm_quat = contains<types::glm::Quats, T>;

template<class T>
using is_glm_vecquat = contains<types::glm::VecsQuats, T>;

template<class T>
using is_mat = contains<types::all::Mats, T>;

// convert to scalars ======================================================== 1

// all GLM vecs/quats to scalars (can't do Qt vecs/quats, those are built-in)
template<class From, class To>
inline enable_if_t < is_glm_vecquat<From>()&&  is_scalar<To>(), To >
convert(const From& from) noexcept {
  return static_cast<To>(from[0]);
}

// 1 ========================================================================= 1

// convert to vec2 =========================================================== 2
// glm::vec3 and glm::vec4 implicitly convert to glm::vec2

// scalar -> vec2
template<class From, class To>
inline enable_if_t < is_scalar<From>()&&  is_vec2<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from),
    static_cast<E<To>>(0)
  );
}

// vecquat -> vec2
template<class From, class To>
inline enable_if_t < is_vecquat<From>()&& is_vec2<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]),
    static_cast<E<To>>(from[1])
  );
}

// QQuaternion -> vec2
template<class From, class To>
inline enable_if_t < is_QQuaternion<From>()&&   is_vec2<To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from.x()), // quat x -> vec2 x
    static_cast<E<To>>(from.y()) // quat y -> vec2 y
  );
}
// TODO: glm vec's operator[] might return a reference, while QQuaternion's
// x() returns an actual float; try a decay?

// 2 ========================================================================= 2

// convert to vec3 =========================================================== 3

// scalar -> vec3
template<class From, class To>
inline enable_if_t < is_scalar<From>()&&  is_vec3<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from),
    static_cast<E<To>>(0),
    static_cast<E<To>>(0)
  );
}

// vec2 -> vec3
template<class From, class To>
inline enable_if_t < is_vec2<From>()&& is_vec3<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]),
    static_cast<E<To>>(from[1]),
    static_cast<E<To>>(0)
  );
}

// quat/vec3/4 -> vec3
template<class From, class To>
inline enable_if_t < (is_vec34<From>() || is_glm_quat<From>())&&  is_vec3<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]),
    static_cast<E<To>>(from[1]),
    static_cast<E<To>>(from[2])
  );
}

// QQuaternion -> vec3
template<class From, class To>
inline enable_if_t < is_QQuaternion<From>()&&   is_vec3<To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from.x()), // quat x -> vec3 x
    static_cast<E<To>>(from.y()), // quat y -> vec3 y
    static_cast<E<To>>(from.z()) // quat z -> vec3 z
  );
}

// 3 ========================================================================= 3

// convert to vec4 =========================================================== 4

// scalar -> vec4 or quat
template<class From, class To>
inline enable_if_t < is_scalar<From>()&&  (is_vec4<To>() || is_quat<To>())&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from),
    static_cast<E<To>>(0),
    static_cast<E<To>>(0),
    static_cast<E<To>>(0)
  );
}

// vec2 -> vec4
template<class From, class To>
inline enable_if_t < is_vec2<From>()&&  is_vec4<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]),
    static_cast<E<To>>(from[1]),
    static_cast<E<To>>(0),
    static_cast<E<To>>(0)
  );
}

// vec3 -> vec4
template<class From, class To>
inline enable_if_t < is_vec3<From>()&&  is_vec4<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]),
    static_cast<E<To>>(from[1]),
    static_cast<E<To>>(from[2]),
    static_cast<E<To>>(0)
  );
}

// vec4 -> vec4
template<class From, class To>
inline enable_if_t < is_vec4<From>()&&  is_vec4<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]),
    static_cast<E<To>>(from[1]),
    static_cast<E<To>>(from[2]),
    static_cast<E<To>>(from[3])
  );
}

// quat -> vec4
template<class From, class To>
inline enable_if_t < is_quat<From>()&&  is_vec4<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[0]), // quat x -> vector x
    static_cast<E<To>>(from[1]), // quat y -> vector y
    static_cast<E<To>>(from[2]), // quat z -> vector z
    static_cast<E<To>>(from[3]) // quat w -> vector w
  );
}

// QQuaternion -> vec4
template<class From, class To>
inline enable_if_t < is_QQuaternion<From>()&&   is_vec4<To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from.x()), // quat x -> vec4 x
    static_cast<E<To>>(from.y()), // quat y -> vec4 y
    static_cast<E<To>>(from.z()), // quat z -> vec4 z
    static_cast<E<To>>(from.scalar()) // quat w -> vec4 w
  );
}
// 4 ========================================================================= 4

// convert to quaternion ===================================================== Q
// vec2 -> quat
template<class From, class To>
inline enable_if_t < is_vec2<From>()&&  is_quat<To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(0), // 0 -> scalar
    static_cast<E<To>>(from[0]), // vector x -> quat x
    static_cast<E<To>>(from[1]), // vector y -> quat y
    static_cast<E<To>>(0) // 0 -> vector z
  );
}

// vec3 -> quat
template<class From, class To>
inline enable_if_t < is_vec3<From>()&&  is_quat<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(0),
    static_cast<E<To>>(from[0]), // vector x
    static_cast<E<To>>(from[1]), // vector y
    static_cast<E<To>>(from[2]) // vector z
  );
}

// vec4 -> quat
template<class From, class To>
inline enable_if_t < is_vec4<From>()&&  is_quat<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from[3]), // scalar / vector w
    static_cast<E<To>>(from[0]), // vector x
    static_cast<E<To>>(from[1]), // vector y
    static_cast<E<To>>(from[2]) // vector z
  );
}

// quat -> quat
template<class From, class To>
inline enable_if_t < is_quat<From>()&&  is_quat<To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from.w),
    static_cast<E<To>>(from.x),
    static_cast<E<To>>(from.y),
    static_cast<E<To>>(from.z)
  );
}

// QQuaternion -> quat
template<class From, class To>
inline enable_if_t < is_QQuaternion<From>()&&   is_quat<To>(), To >
convert(const From& from) noexcept {
  return To(
    static_cast<E<To>>(from.scalar()), // quat scalar -> scalar
    static_cast<E<To>>(from.x()), // quat x -> vec3 x
    static_cast<E<To>>(from.y()), // quat y -> vec3 y
    static_cast<E<To>>(from.z()) // quat z -> vec3 z
  );
}
// Q ========================================================================= Q

// convert to matrix ======================================================= mxn

// glm mat -> glm mat
template<class From, class To>
inline enable_if_t < is_mat<From>()&&  is_mat<To>()&&
!is_builtin_conv<From, To>(), To >
convert(const From& from) noexcept {
  return To(from);
}
// mxn ===================================================================== mxn

template<typename From>
struct other_handler {
  template<typename To>
  inline void operator()(To&) noexcept {
    Q_ASSUME((QMetaType::registerConverter<From, To, To(*)(const From&)>(&convert<From, To>)));
  }
};

template<typename FromSeq>
struct handler {
  template<typename To>
  inline void operator()(To&) noexcept {
    boost::mpl::for_each<FromSeq>(other_handler<To>());
  }
};


/// Register a conversion from every type in SeqA to every type in SeqB
template<class SeqA, class SeqB>
inline void _registerTypes() noexcept {
  boost::mpl::for_each<SeqA>(handler<SeqB>());
}


void registerMetaTypeConverters() noexcept {
  using namespace glm;
  using boost::mpl::joint_view;
  using boost::mpl::list;
  using boost::mpl::single_view;

  _registerTypes<types::Scalars, types::glm::VecsQuats>();

  _registerTypes<types::glm::VecsQuats, types::Scalars>();
  _registerTypes<types::glm::VecsQuats, types::all::VecsQuats>();

  _registerTypes<types::qt::Vecs, types::glm::VecsQuats>();
  _registerTypes<types::qt::Quats, types::glm::Vec3s>();
  //_registerTypes<types::qt::Quats, types::glm::Vec4s>();
  // TODO: Support QQuaternion conversions properly

  _registerTypes<types::glm::Mats, types::glm::Mats>();
  // TODO: Convert between GLM <-> Qt matrices
}
}
