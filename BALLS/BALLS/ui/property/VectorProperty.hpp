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

template<class Value>
class VectorProperty : public Property {
  using Component = typename Value::value_type;
  static const glm::length_t Size =  Value::components;

public:
  using Type = Value;

  VectorProperty(
    const QString& name = "",
    QObject* subject = nullptr,
    QObject* parent = nullptr
  ) : Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < Size; ++i) {
      // TODO: Section this off into a new, non-templated private helper
      // (maybe by passing in a pointer and a size instead of an array object)
      this->dimProps[i] = new Property(properties::XYZW[i], this, this);
    }
  }

  virtual ~VectorProperty() {}

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
      // If the user just modified the whole vector (as opposed to a single component)...
      const QRegularExpression& rx = this->regex();
      QRegularExpressionMatch match = rx.match(value.toString());

      Value vec;

      if (match.hasMatch()) {
        // If the vector string is in the format we want...
        for (int i = 0; i < Size; ++i) {
          QVariant v = match.captured(groups::XYZW[i]);
          Q_ASSERT(v.canConvert<Component>());
          Component t = v.template value<Component>();
          dimProps[i]->setValue(QVariant(t));
          vec[i] = t;
        }
      }

      Property::setValue(QVariant::fromValue<Value>(vec));
    }
    else if (value.userType() == qMetaTypeId<Value>()) {
      // Else if the vector's value was just changed directly...
      Property::setValue(value);
    }

    // Otherwise, don't change the value (we only want vectors!)
  }
protected:
  array<Property*, Size> dimProps;

  template<int C>
  Component _get() const noexcept {
    static_assert(0 <= C && C < Value::components, "");
    return value().template value<Value>()[C];
  }

  template<int C>
  void _set(const Component& c) noexcept {
    static_assert(0 <= C&&  C < Value::components, "");

    Value v = value().template value<Value>();
    v[C] = c;

    Property::setValue(QVariant::fromValue<Value>(v));
  }

  void setEditorHints(const QString& hints) noexcept override {
    for (int i = 0; i < Size; ++i) {
      dimProps[i]->setEditorHints(_impl_::parseHints(hints, "xyzw"[i]));
    }
  }
private:
  // TODO: Replace this (maybe with a constructor parameter)
  virtual const QRegularExpression& regex() const noexcept = 0;
};
}

#endif // VECTORPROPERTY_HPP
