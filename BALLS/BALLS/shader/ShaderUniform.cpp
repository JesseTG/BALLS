#include "precompiled.hpp"
#include "shader/ShaderUniform.hpp"

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

  if (subject != nullptr) {
    QVariant var = subject->property(qPrintable(name));

    Q_ASSERT(var.isValid());

    auto type = var.userType();

    if (info.count(type) && info[type].propertyFactory) {
      const util::types::TypeInfo& i = info[type];

      qDebug()
          << "Creating property" << var.typeName() << name << "for" <<
          subject->objectName();

      return i.propertyFactory(name, subject, parent);
    }
    else {
      qDebug()
          << "Using default property" << var.typeName() << name << "for" <<
          subject->objectName();
    }
  }

  return nullptr;
}

}
}
