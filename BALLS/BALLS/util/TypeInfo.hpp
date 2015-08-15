#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

#include <cstdint>
#include <utility>
#include <unordered_map>

#include <QString>

#include <qopengl.h>
#include <qopenglext.h>

class QObject;
class Property;

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
}
}
#endif // TYPEINFO_HPP
