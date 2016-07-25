#ifndef SHADERUNIFORM_HPP
#define SHADERUNIFORM_HPP

#include <QtCore/QMetaType>

#include "util/Util.hpp"

class Property;
class QString;
class QObject;

namespace balls {
namespace shader {

using Type = QMetaType::Type;

Property* createShaderProperty(const QString&, QObject*, Property*);
}
}

#endif // SHADERUNIFORM_HPP
