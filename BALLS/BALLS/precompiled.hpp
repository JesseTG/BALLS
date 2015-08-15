#ifndef PRECOMPILED_HPP
#define PRECOMPILED_HPP

// Standard Library
#include <array>
#include <cmath>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// Qt Core
#include <qmath.h>
#include <QtCore/Qt>
#include <QtCore/QtGlobal>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QLoggingCategory>
#include <QtCore/QMetaClassInfo>
#include <QtCore/QMetaEnum>
#include <QtCore/QMetaMethod>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QMetaType>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtCore/QPointer>
#include <QtCore/QRegularExpression>
#include <QtCore/QRegularExpressionMatch>
#include <QtCore/QRegularExpressionMatchIterator>
#include <QtCore/QSize>
#include <QtCore/QSizeF>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QVector>

// Qt GUI
#include <QtGui/qopengl.h>
#include <QtGui/qopenglext.h>
#include <QtGui/QColor>
#include <QtGui/QQuaternion>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

// glm common types
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// glm stable extensions
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

// glm experimental extensions
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/normalize_dot.hpp>
// #include <glm/gtx/simd_mat4.hpp>
// #include <glm/gtx/simd_quat.hpp>
// #include <glm/gtx/simd_vec4.hpp>
#include <glm/gtx/transform.hpp>

// Defines
#ifndef M_PI
constexpr float M_PI = 3.141592653589793f;
#endif

// Template class instantiations

using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::ivec2;
using glm::ivec3;
using glm::ivec4;

using glm::uvec2;
using glm::uvec3;
using glm::uvec4;

using glm::bvec2;
using glm::bvec3;
using glm::bvec4;

using glm::dvec2;
using glm::dvec3;
using glm::dvec4;

using glm::mat2;
using glm::mat2x2;
using glm::mat2x3;
using glm::mat2x4;
using glm::mat3x2;
using glm::mat3;
using glm::mat3x3;
using glm::mat3x4;
using glm::mat4x2;
using glm::mat4x3;
using glm::mat4x4;
using glm::mat4;

using glm::dmat2x2;
using glm::dmat2;
using glm::dmat2x3;
using glm::dmat2x4;
using glm::dmat3x2;
using glm::dmat3;
using glm::dmat3x3;
using glm::dmat3x4;
using glm::dmat4x2;
using glm::dmat4x3;
using glm::dmat4;
using glm::dmat4x4;

using glm::quat;
using glm::dquat;

// glm meta type declarations
Q_DECLARE_METATYPE(vec2)
Q_DECLARE_METATYPE(vec3)
Q_DECLARE_METATYPE(vec4)
// Q_DECLARE_METATYPE(glm::simdVec4)

Q_DECLARE_METATYPE(ivec2)
Q_DECLARE_METATYPE(ivec3)
Q_DECLARE_METATYPE(ivec4)

Q_DECLARE_METATYPE(uvec2)
Q_DECLARE_METATYPE(uvec3)
Q_DECLARE_METATYPE(uvec4)

Q_DECLARE_METATYPE(bvec2)
Q_DECLARE_METATYPE(bvec3)
Q_DECLARE_METATYPE(bvec4)

Q_DECLARE_METATYPE(dvec2)
Q_DECLARE_METATYPE(dvec3)
Q_DECLARE_METATYPE(dvec4)

Q_DECLARE_METATYPE(mat2)
Q_DECLARE_METATYPE(mat2x3)
Q_DECLARE_METATYPE(mat2x4)
Q_DECLARE_METATYPE(mat3x2)
Q_DECLARE_METATYPE(mat3)
Q_DECLARE_METATYPE(mat3x4)
Q_DECLARE_METATYPE(mat4x2)
Q_DECLARE_METATYPE(mat4x3)
Q_DECLARE_METATYPE(mat4)
// Q_DECLARE_METATYPE(glm::simdMat4)

Q_DECLARE_METATYPE(dmat2)
Q_DECLARE_METATYPE(dmat2x3)
Q_DECLARE_METATYPE(dmat2x4)
Q_DECLARE_METATYPE(dmat3x2)
Q_DECLARE_METATYPE(dmat3)
Q_DECLARE_METATYPE(dmat3x4)
Q_DECLARE_METATYPE(dmat4x2)
Q_DECLARE_METATYPE(dmat4x3)
Q_DECLARE_METATYPE(dmat4)

Q_DECLARE_METATYPE(quat)
Q_DECLARE_METATYPE(dquat)
// Q_DECLARE_METATYPE(glm::simdQuat)
//==============================================================================

// glm explicit template instantiations
namespace glm {

// Can't instantiate the bool specializations for some reason; I suppose doing so
// tries to instantiate all methods, including any decrement/increment operators
extern template struct tvec2<double>;
extern template struct tvec2<float>;
extern template struct tvec2<int>;
extern template struct tvec2<glm::uint>;

extern template struct tvec3<double>;
extern template struct tvec3<float>;
extern template struct tvec3<int>;
extern template struct tvec3<glm::uint>;

extern template struct tvec4<double>;
extern template struct tvec4<float>;
extern template struct tvec4<int>;
extern template struct tvec4<glm::uint>;

extern template struct tquat<float>;
extern template struct tquat<double>;

extern template struct tmat2x2<float>;
extern template struct tmat2x2<double>;
extern template struct tmat2x3<float>;
extern template struct tmat2x3<double>;
extern template struct tmat2x4<float>;
extern template struct tmat2x4<double>;
extern template struct tmat3x2<float>;
extern template struct tmat3x2<double>;
extern template struct tmat3x3<float>;
extern template struct tmat3x3<double>;
extern template struct tmat3x4<float>;
extern template struct tmat3x4<double>;
extern template struct tmat4x2<float>;
extern template struct tmat4x2<double>;
extern template struct tmat4x3<float>;
extern template struct tmat4x3<double>;
extern template struct tmat4x4<float>;
extern template struct tmat4x4<double>;
}

// STL template instantiations
namespace std {
extern template struct array<uint16_t, 3>;

template<> struct hash<QString>;
template<> struct hash<QByteArray>;

extern template struct pair<GLenum, GLenum>;
extern template struct pair<QString, QVariant>;

//extern template class unordered_map<GLenum, GLenum>;

extern template class vector<float>;
extern template class vector<uint16_t>;
extern template class vector<glm::vec3>;
}

#endif // PRECOMPILED_HPP
