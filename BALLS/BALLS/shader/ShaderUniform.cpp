#include "precompiled.hpp"
#include "shader/ShaderUniform.hpp"

#include "ui/property/VectorProperty.hpp"
#include "ui/property/Vector2Property.hpp"
#include "ui/property/Vector3Property.hpp"
#include "ui/property/Vector4Property.hpp"
#include "ui/Uniforms.hpp"
#include "util/Util.hpp"
#include "util/Logging.hpp"
#include "util/TypeInfo.hpp"
#include "Constants.hpp"

#include <QPropertyEditor/Property.h>

namespace balls {
namespace shader {

using namespace logs;

Property* createShaderProperty(const QString& name, QObject* subject,
                               Property* parent) {
  using util::types::info;
  Uniforms* uniform = dynamic_cast<Uniforms*>(subject);

  if (uniform != nullptr) {
    QVariant var = uniform->property(qPrintable(name));

    Q_ASSERT(var.isValid());

    auto type = var.userType();

    if (info.count(type) && info[type].propertyFactory) {
      const util::types::TypeInfo& i = info[type];

      qCDebug(logs::uniform::Name)
          << "Creating property" << var.typeName() << name << "for" <<
          uniform->objectName();

      return i.propertyFactory(name, subject, parent);
    }
    else {
      qCDebug(logs::uniform::Name)
          << "Using default property" << var.typeName() << name << "for" <<
          uniform->objectName();
    }
  }

  return nullptr;
}

}
}
