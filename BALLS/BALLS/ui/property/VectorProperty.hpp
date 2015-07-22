#ifndef VECTORPROPERTY_HPP
#define VECTORPROPERTY_HPP

#include <array>

#include <QObject>
#include <QPropertyEditor/Property.h>

#include "Constants.hpp"

class QRegularExpression;
class QRegularExpressionMatch;

namespace balls {
using std::array;

namespace _impl_ {
template<int Size>
QString _getDisplayText(const array<Property*, Size>&,
                        const int) noexcept;

template<> QString _getDisplayText<2>(const array<Property*, 2>&,
                                      const int) noexcept;

template<> QString _getDisplayText<3>(const array<Property*, 3>&,
                                      const int) noexcept;

template<> QString _getDisplayText<4>(const array<Property*, 4>&,
                                      const int) noexcept;

extern template QString _getDisplayText<2>(const array<Property*, 2>&,
    const int) noexcept;

extern template QString _getDisplayText<3>(const array<Property*, 3>&,
    const int) noexcept;

extern template QString _getDisplayText<4>(const array<Property*, 4>&,
    const int) noexcept;

QString parseHints(const QString& hints, const QChar component) noexcept;
}

template<class VectorType>
class VectorProperty : public Property {
  using ScalarType = typename VectorType::value_type;
  static constexpr glm::length_t Size =  VectorType::components;

public:
  VectorProperty(
    const QString& name = "",
    QObject* subject = nullptr,
    QObject* parent = nullptr
  ) : Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < Size; ++i) {
      this->dimProps[i] = new Property(properties::XYZW[i], this, this);
    }
  }
  virtual ~VectorProperty() {}

  ScalarType x() const noexcept {
    return this->component(0);
  }

  void set_x(const ScalarType x) noexcept {
    this->set_component(0, x);
  }

  ScalarType y() const noexcept {
    return this->component(1);
  }

  void set_y(const ScalarType y) noexcept {
    this->set_component(1, y);
  }

  QVariant value(const int role = Qt::UserRole) const noexcept override final {
    QVariant data = Property::value();

    if (data.isValid() && role != Qt::UserRole) {
      QString text = _impl_::_getDisplayText<Size>(this->dimProps, role);

      if (!text.isEmpty()) { return text; }
    }

    return data;
  }

  void setValue(const QVariant& value) noexcept override final {
    using namespace constants::patterns;
    using namespace constants;

    if (value.userType() == QVariant::String) {
      const QRegularExpression& rx = this->regex();
      QRegularExpressionMatch match = rx.match(value.toString());

      VectorType vec;

      if (match.hasMatch()) {
        for (int i = 0; i < Size; ++i) {
          QVariant v = match.captured(groups::XYZW[i]);
          Q_ASSERT(v.canConvert<ScalarType>());
          ScalarType t = v.template value<ScalarType>();
          dimProps[i]->setProperty(properties::XYZW[i], t);
          vec[i] = t;
        }
      }

      Property::setValue(QVariant::fromValue<VectorType>(vec));
    }
    else {
      Property::setValue(value);
    }
  }
protected:
  array<Property*, Size> dimProps;

  ScalarType component(const int c) const noexcept {
    Q_ASSERT(0 <= c && c < Size);
    return value().template value<VectorType>()[c];
  }

  void set_component(const int I, const ScalarType s) noexcept {
    Q_ASSERT(0 <= I&&    I < Size);
    VectorType v;

    for (int i = 0; i < Size; ++i) {
      v[i] = (i == I) ? s : component(i);
    }

    Property::setValue(QVariant::fromValue<VectorType>(v));
  }

  void setEditorHints(const QString& hints) noexcept override {
    for (int i = 0; i < Size; ++i) {
      dimProps[i]->setEditorHints(_impl_::parseHints(hints, "xyzw"[i]));
    }
  }

  virtual const QRegularExpression& regex() const noexcept = 0;
};
}

#endif // VECTORPROPERTY_HPP
