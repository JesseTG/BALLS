#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

#include <cstdint>
#include <utility>
#include <unordered_map>

#include <QPropertyEditor/Property.h>

#include <qopengl.h>
#include <qopenglext.h>
#include <QtGui/QGenericMatrix>
#include <QtGui/QMatrix4x4>
#include <QtGui/QQuaternion>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

namespace balls {
namespace util {

namespace types {

using PropertyFactory = Property* (*)(const QString&, QObject*, Property*);
struct TypeInfo {
  GLenum gltype;
  PropertyFactory propertyFactory;
  int qMetaType;
};
using TypeInfoMap = std::unordered_map<int, TypeInfo>;

extern TypeInfoMap info;

struct UniformInfo {
  QString name;
  int index;
  GLenum type;
  GLint size;

  bool operator<(const UniformInfo& o) const noexcept {
    return index < o.index;
  }
};

using UniformCollection = std::vector<UniformInfo>;

void init() noexcept;
}

namespace Matrix {

using std::pair;

template<class M>
constexpr bool Generic = false;

template<>
constexpr bool Generic<QMatrix2x2> = true;

template<>
constexpr bool Generic<QMatrix2x3> = true;

template<>
constexpr bool Generic<QMatrix2x4> = true;

template<>
constexpr bool Generic<QMatrix3x2> = true;

template<>
constexpr bool Generic<QMatrix3x3> = true;

template<>
constexpr bool Generic<QMatrix3x4> = true;

template<>
constexpr bool Generic<QMatrix4x2> = true;

template<>
constexpr bool Generic<QMatrix4x3> = true;

template<class M>
constexpr pair<uint8_t, uint8_t> Dims {0, 0};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix2x2> {2, 2};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix2x3> {2, 3};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix2x4> {2, 4};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix3x2> {3, 2};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix3x3> {3, 3};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix3x4> {3, 4};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix4x2> {4, 2};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix4x3> {4, 3};

template<>
constexpr pair<uint8_t, uint8_t> Dims<QMatrix4x4> {4, 4};
}


}
}
#endif // TYPEINFO_HPP
