#include "precompiled.hpp"
#include "ui/property/VectorProperty.hpp"

namespace balls {

using namespace glm;

namespace _impl_ {
template <>
QString _getDisplayText<2>(
  const array<Property *, 2> &dims, const int role) noexcept {
  switch (role) {

  case Qt::DisplayRole:
    return Property::tr("[ %1, %2 ]")
      .arg(dims[0]->value().toString(), dims[1]->value().toString());

  case Qt::EditRole:
    return Property::tr("%1, %2").arg(
      dims[0]->value().toString(), dims[1]->value().toString());

  default:
    return "";
  };
}

template <>
QString _getDisplayText<3>(
  const array<Property *, 3> &dims, const int role) noexcept {
  switch (role) {

  case Qt::DisplayRole:
    return Property::tr("[ %1, %2, %3 ]")
      .arg(
        dims[0]->value().toString(),
        dims[1]->value().toString(),
        dims[2]->value().toString());

  case Qt::EditRole:
    return Property::tr("%1, %2, %3")
      .arg(
        dims[0]->value().toString(),
        dims[1]->value().toString(),
        dims[2]->value().toString());

  default:
    return "";
  };
}

template <>
QString _getDisplayText<4>(
  const array<Property *, 4> &dims, const int role) noexcept {
  switch (role) {

  case Qt::DisplayRole:
    return Property::tr("[ %1, %2, %3, %4 ]")
      .arg(
        dims[0]->value().toString(),
        dims[1]->value().toString(),
        dims[2]->value().toString(),
        dims[3]->value().toString());

  case Qt::EditRole:
    return Property::tr("%1, %2, %3, %4")
      .arg(
        dims[0]->value().toString(),
        dims[1]->value().toString(),
        dims[2]->value().toString(),
        dims[3]->value().toString());

  default:
    return "";
  };
}
} // _impl_

} // balls
