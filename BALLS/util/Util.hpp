#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>

#include <QtCore/QDebug>
#include <QtCore/QHash>
#include <QtCore/QMetaTypeId>
#include <QtCore/QString>
#include <QtGui/QOpenGLShader>

namespace balls {
namespace util {

using std::uint8_t;
using std::size_t;
using Type = QMetaType::Type;

QDebug& operator<<(QDebug&, const QOpenGLShader::ShaderType&);
Type getComponentType(const GLenum) Q_DECL_NOTHROW;
uint8_t getNumComponents(const GLenum) Q_DECL_NOTHROW;
bool isVectorType(const GLenum) Q_DECL_NOTHROW;
bool isMatrixType(const GLenum) Q_DECL_NOTHROW;
bool isScalarType(const GLenum) Q_DECL_NOTHROW;
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
}
#endif // UTIL_HPP
