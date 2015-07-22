#ifndef MATRIXPROPERTY_HPP
#define MATRIXPROPERTY_HPP

#include <array>
#include <type_traits>

#include <QGenericMatrix>

#include "QPropertyEditor/Property.h"
#include "ui/property/VectorProperty.hpp"
#include "ui/property/Vector2Property.hpp"
#include "ui/property/Vector3Property.hpp"
#include "ui/property/Vector4Property.hpp"
#include "Constants.hpp"

namespace balls {
using std::array;

template<class ScalarType, class VPropType, int Rows, int Cols>
class MatrixProperty : public Property {
private:
  using QMatrixType = std::conditional < Rows == 4 && Cols == 4,
        QMatrix4x4,
        QGenericMatrix<Cols, Rows, ScalarType>
        >;

  static_assert(2 <= Rows&&  Rows <= 4, "Must have 2, 3, or 4 rows");
  static_assert(2 <= Cols&&  Cols <= 4, "Must have 2, 3, or 4 columns");
public:
  MatrixProperty(const QString& name = "",
                 QObject* subject = nullptr,
                 QObject* parent = nullptr
              ) noexcept :
  Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < Cols; ++i) {
      this->columnProps[i] = new VPropType(properties::COLS[i], this, this);
    }
  }

  virtual ~MatrixProperty() {}

  QVariant value(const int role = Qt::UserRole) const noexcept override
  final {
    const static QString matType = QString("mat%1x%2").arg(Rows).arg(Cols);
    QVariant data = Property::value();

    if (data.isValid() && role != Qt::UserRole) {
      return matType;
    }

    return data;
  }

  void setValue(const QVariant& value) noexcept override final {
    using namespace constants::patterns;
    using namespace constants;

    if (value.userType() == qMetaTypeId<QMatrixType>()) {
      QMatrixType mat;

      Property::setValue(QVariant::fromValue<QMatrixType>(mat));
    }
    else {
      Property::setValue(value);
    }
  }

protected:
  array<VPropType*, Cols> columnProps;
};


}

#endif // MATRIXPROPERTY_HPP
