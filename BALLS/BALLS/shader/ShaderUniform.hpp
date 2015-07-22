#ifndef SHADERUNIFORM_HPP
#define SHADERUNIFORM_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtGui/QOpenGLFunctions>

#include <QPropertyEditor/Property.h>
#include "util/Util.hpp"
#include "ui/property/Vector2Property.hpp"

namespace balls {
namespace shader {
using std::function;

using Type = QMetaType::Type;

Property* createShaderProperty(const QString&, QObject*, Property*);

}
}

#endif // SHADERUNIFORM_HPP
