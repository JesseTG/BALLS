#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <utility>

#include <QtCore/QDebug>
#include <QtCore/QHash>
#include <QtCore/QJsonValue>
#include <QtCore/QMetaTypeId>
#include <QtCore/QString>

#include <QtGui/QGenericMatrix>
#include <QtGui/QMatrix4x4>

#include <qopengl.h>
#include <qopenglext.h>

namespace balls {
namespace util {

using std::pair;
using std::uint8_t;
using std::size_t;
using Type = QMetaType::Type;

QVariant getDefaultValue(const GLenum) noexcept;
Type getComponentType(const GLenum) noexcept;
GLenum getGlComponentType(const GLenum) noexcept;
Type getRepresentingType(const GLenum) noexcept;
uint8_t getNumComponents(const GLenum) noexcept;
bool isVectorType(const GLenum) noexcept;
bool isMatrixType(const GLenum) noexcept;
bool isScalarType(const GLenum) noexcept;

/// Returns a value suitable for storing in an OpenGL vector or matrix (e.g.
/// bvec2)
QVariant asGlComponent(const GLenum, const QVariant&) noexcept;

const char* resolveGLType(const GLenum) noexcept;
const char* resolveGLPrimitive(const GLenum) noexcept;
const char* resolveGLError(const GLenum) noexcept;

QJsonValue toJsonValue(const GLenum, const QVariant&) noexcept;

float fastInvSqrt(float number) noexcept;

template <class T>
T mapRange(T x, T in_min, T in_max, T out_min, T out_max) noexcept {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
}
}

namespace std {
template <>
struct hash<QString> {
  using argument_type = QString;
  using result_type = size_t;

  result_type operator()(argument_type const& s) const Q_DECL_NOEXCEPT {
    return qHash(s);
  }
};

template <>
struct hash<QByteArray> {
  using argument_type = QByteArray;
  using result_type = size_t;

  result_type operator()(argument_type const& b) const Q_DECL_NOEXCEPT {
    return qHash(b);
  }
};
}

#endif // UTIL_HPP
