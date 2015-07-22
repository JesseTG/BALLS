#include "precompiled.hpp"
#include "ui/property/VectorProperty.hpp"

namespace balls {

using namespace glm;

template class VectorProperty<bvec2>;
template class VectorProperty<dvec2>;
template class VectorProperty<ivec2>;
template class VectorProperty<uvec2>;
template class VectorProperty<vec2>;

template class VectorProperty<bvec3>;
template class VectorProperty<dvec3>;
template class VectorProperty<ivec3>;
template class VectorProperty<uvec3>;
template class VectorProperty<vec3>;

template class VectorProperty<bvec4>;
template class VectorProperty<dvec4>;
template class VectorProperty<ivec4>;
template class VectorProperty<uvec4>;
template class VectorProperty<vec4>;

namespace _impl_ {
template<>
QString _getDisplayText<2>(const array<Property*, 2>& dims,
                           const int role) noexcept {
  switch (role) {

  case Qt::DisplayRole:
    return Property::tr("[ %1, %2 ]")
    .arg(dims[0]->value().toString())
    .arg(dims[1]->value().toString());

  case Qt::EditRole:
    return Property::tr("%1, %2")
    .arg(dims[0]->value().toString())
    .arg(dims[1]->value().toString());

  default:
    return "";
  };
}

template<>
QString _getDisplayText<3>(const array<Property*, 3>& dims,
                           const int role) noexcept {
  switch (role) {

  case Qt::DisplayRole:
    return Property::tr("[ %1, %2, %3 ]")
    .arg(dims[0]->value().toString())
    .arg(dims[1]->value().toString())
    .arg(dims[2]->value().toString());

  case Qt::EditRole:
    return Property::tr("%1, %2, %3")
    .arg(dims[0]->value().toString())
    .arg(dims[1]->value().toString())
    .arg(dims[2]->value().toString());

  default:
    return "";
  };
}

template<>
QString _getDisplayText<4>(const array<Property*, 4>& dims,
                           const int role) noexcept {
  switch (role) {

  case Qt::DisplayRole:
    return Property::tr("[ %1, %2, %3, %4 ]")
    .arg(dims[0]->value().toString())
    .arg(dims[1]->value().toString())
    .arg(dims[2]->value().toString())
    .arg(dims[3]->value().toString());

  case Qt::EditRole:
    return Property::tr("%1, %2, %3, %4")
    .arg(dims[0]->value().toString())
    .arg(dims[1]->value().toString())
    .arg(dims[2]->value().toString())
    .arg(dims[3]->value().toString());

  default:
    return "";
  };
}

QString parseHints(const QString& hints, const QChar component) noexcept {
  if (hints.isEmpty()) return "";

  QRegExp rx(QString("(.*)(") + component + QString("{1})(=\\s*)(.*)(;{1})"));
  rx.setMinimal(true);
  int pos = 0;
  QString componentHints;

  while ((pos = rx.indexIn(hints, pos)) != -1) {
    // cut off additional front settings (TODO create correct RegExp for that)
    if (rx.cap(1).lastIndexOf(';') != -1) {
      componentHints += QString("%1=%2;").arg(rx.cap(1).remove(0,
      rx.cap(1).lastIndexOf(';') + 1)).arg(rx.cap(4));
    }
    else {
      componentHints += QString("%1=%2;").arg(rx.cap(1)).arg(rx.cap(4));
    }

    pos += rx.matchedLength();
  }

  return componentHints;
}
} // _impl_

} // balls
