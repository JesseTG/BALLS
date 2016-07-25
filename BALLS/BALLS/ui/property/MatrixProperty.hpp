#ifndef MATRIXPROPERTY_HPP
#define MATRIXPROPERTY_HPP

#include <QString>
#include <array>
#include <type_traits>

#include <glm/gtx/type_trait.hpp>

#include "Constants.hpp"
#include "QPropertyEditor/Property.h"

namespace balls {
using std::array;

template <template <typename, glm::precision> class T, class ColProp>
class MatrixProperty : public Property {
  using Matrix = T<typename ColProp::Type::value_type, glm::defaultp>;
  static_assert(
    std::is_same<typename ColProp::Type, typename Matrix::col_type>::value,
    "ColProp's value type must be Matrix's column type");

  using Column = typename Matrix::col_type;
  static const glm::length_t Size = glm::type<T, typename ColProp::Type::value_type, glm::defaultp>::components;

public:
  using Type = Matrix;
  MatrixProperty(
    const QString& name = "",
    QObject* subject = nullptr,
    QObject* parent = nullptr) noexcept : Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < ColProp::Size; ++i) {
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

      for (int i = 0; i < ColProp::Size; ++i) {
        colProps[i]->setValue(QVariant::fromValue(mat[i]));
      }

      Property::setValue(QVariant::fromValue<Matrix>(mat));
    }

    // Otherwise do nothing, the user can't edit a matrix on the whole (gotta
    // do it through the columns)
  }

protected:
  array<ColProp*, ColProp::Size> colProps;

  inline Column _getx() const noexcept {
    return _get<0>();
  }
  inline void _setx(const Column c) noexcept {
    _set<0>(c);
  }

  inline Column _gety() const noexcept {
    return _get<1>();
  }
  inline void _sety(const Column c) noexcept {
    _set<1>(c);
  }

  inline Column _getz() const noexcept {
    return _get<2>();
  }
  inline void _setz(const Column c) noexcept {
    _set<2>(c);
  }

  inline Column _getw() const noexcept {
    return _get<3>();
  }
  inline void _setw(const Column c) noexcept {
    _set<3>(c);
  }

private:
  template <int C>
  Column _get() const noexcept {
    return value().template value<Matrix>()[C];
  }

  template <int C>
  void _set(const Column& c) noexcept {
    Matrix v = value().template value<Matrix>();
    v[C] = c;

    Property::setValue(QVariant::fromValue<Matrix>(v));
  }
};
}

#endif // MATRIXPROPERTY_HPP
