#ifndef MATRIXPROPERTY_HPP
#define MATRIXPROPERTY_HPP

#include <array>
#include <type_traits>

#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "QPropertyEditor/Property.h"
#include "ui/property/VectorProperty.hpp"
#include "ui/property/Vector2Property.hpp"
#include "ui/property/Vector3Property.hpp"
#include "ui/property/Vector4Property.hpp"
#include "Constants.hpp"

namespace balls {
using std::array;

template<class MatrixType, class VPropType>
class MatrixProperty : public Property {
public:
  MatrixProperty(const QString& name = "",
                 QObject* subject = nullptr,
                 QObject* parent = nullptr
              ) noexcept :
  Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < Cols; ++i) {
      this->rowProps[i] = new VPropType(properties::ROWS[i], this, this);
    }
  }

  virtual ~MatrixProperty() {}

  QVariant value(const int role = Qt::UserRole) const noexcept override final {
    const static QString matType = QString("mat%1x%2").arg(MatrixType::rows).arg(MatrixType::cols);
    QVariant data = Property::value();

    if (data.isValid() && role != Qt::UserRole) {
      return matType;
    }

    return data;
  }

  void setValue(const QVariant& value) noexcept override final {
    using namespace constants::patterns;
    using namespace constants;

    if (value.userType() == qMetaTypeId<MatrixType>()) {
      // If we got a matrix...
      MatrixType mat;

      Property::setValue(QVariant::fromValue<MatrixType>(mat));
    }
    else {
      Property::setValue(value);
    }
  }

protected:
  array<VPropType*, MatrixType::rows> rowProps;
};

}

#endif // MATRIXPROPERTY_HPP
