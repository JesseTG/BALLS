#ifndef MATRIXPROPERTY_HPP
#define MATRIXPROPERTY_HPP

#include <array>
#include <type_traits>
#include <QString>

#include "QPropertyEditor/Property.h"
#include "Constants.hpp"

namespace balls {
using std::array;

template<class Matrix, class ColProp>
class MatrixProperty : public Property {
  static_assert(
    std::is_same<typename ColProp::Type, typename Matrix::col_type>::value,
    "ColProp's value type must be Matrix's column type"
  );

  using Column = typename Matrix::col_type;
  static const glm::length_t Size =  Matrix::components;
public:
  using Type = Matrix;
  MatrixProperty(const QString& name = "",
                 QObject* subject = nullptr,
                 QObject* parent = nullptr
              ) noexcept :
  Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < Matrix::cols; ++i) {
      this->colProps[i] = new ColProp(properties::COLS[i], this, this);
    }
  }

  virtual ~MatrixProperty() noexcept {}

  QVariant value(const int role = Qt::UserRole) const noexcept override final {
    QVariant data = Property::value();

    if (data.isValid() && role != Qt::UserRole) {
      return "";
    }

    return data;
  }

  void setValue(const QVariant& value) noexcept override final {
    using namespace constants;

    if (value.userType() == qMetaTypeId<Matrix>()) {
      // If we got a matrix...
      Matrix mat = value.value<Matrix>();

      for (int i = 0; i < Matrix::cols; ++i) {
        colProps[i]->setValue(QVariant::fromValue(mat[i]));
      }

      Property::setValue(QVariant::fromValue<Matrix>(mat));
    }

    // Otherwise do nothing, the user can't edit a matrix on the whole (gotta
    // do it through the columns)
  }

protected:
  array<ColProp*, Matrix::cols> colProps;

  template<int C>
  Column _get() const noexcept {
    static_assert(0 <= C && C < Matrix::cols, "");
    return value().template value<Matrix>()[C];
  }

  template<int C>
  void _set(const Column& c) noexcept {
    static_assert(0 <= C&&  C < Matrix::cols, "");

    Matrix v = value().template value<Matrix>();
    v[C] = c;

    Property::setValue(QVariant::fromValue<Matrix>(v));
  }
};
}

#endif // MATRIXPROPERTY_HPP
