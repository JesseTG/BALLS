#ifndef VECTORPROPERTY_HPP
#define VECTORPROPERTY_HPP

#include <array>

#include <QObject>
#include "Constants.hpp"

#include <QPropertyEditor/Property.h>

#include <glm/gtx/type_trait.hpp>

class QRegularExpression;
class QRegularExpressionMatch;

namespace balls {
using std::array;

namespace _impl_ {
template <int Size>
QString _getDisplayText(const array<Property*, Size>&, const int) noexcept;

// clang-format off
template<> QString _getDisplayText<2>(const array<Property*, 2>&, const int) noexcept;
template<> QString _getDisplayText<3>(const array<Property*, 3>&, const int) noexcept;
template<> QString _getDisplayText<4>(const array<Property*, 4>&, const int) noexcept;

extern template QString _getDisplayText<2>(const array<Property*, 2>&, const int) noexcept;
extern template QString _getDisplayText<3>(const array<Property*, 3>&, const int) noexcept;
extern template QString _getDisplayText<4>(const array<Property*, 4>&, const int) noexcept;
// clang-format on
}

template <template <typename, glm::precision> class T,
          class Component,
          glm::precision P = glm::defaultp>
class VectorProperty : public Property {

public:
  using Type = T<Component, P>;
  static constexpr glm::length_t Size = glm::type<T>::components;

  VectorProperty(
    const QString& name = "",
    QObject* subject = nullptr,
    QObject* parent = nullptr)
    : Property(name, subject, parent) {
    using namespace constants;

    for (int i = 0; i < Size; ++i) {
      // TODO: Section this off into a new, non-templated private helper
      // (maybe by passing in a pointer and a size instead of an array object)
      this->dimProps[i] = new Property(properties::XYZW[i], this, this);
    }
  }

  virtual ~VectorProperty() noexcept {}

  QVariant value(const int role = Qt::UserRole) const noexcept override final {
    QVariant data = Property::value();

    if (data.isValid() && role != Qt::UserRole) {
      QString text = _impl_::_getDisplayText<Size>(this->dimProps, role);

      if (!text.isEmpty()) {
        return text;
      }
    }

    return data;
  }

  void setValue(const QVariant& value) noexcept override final {
    using namespace constants::patterns;
    using namespace constants;

    if (value.userType() == QVariant::String) {
      // If the user just modified the whole vector (as opposed to a single
      // component)...
      const QRegularExpression& rx = this->regex();
      QRegularExpressionMatch match = rx.match(value.toString());

      Type vec;

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

      Property::setValue(QVariant::fromValue<Type>(vec));
    } else if (value.userType() == qMetaTypeId<Type>()) {
      // Else if the vector's value was just changed directly...
      Property::setValue(value);
    }

    // Otherwise, don't change the value (we only want vectors!)
  }

protected:
  array<Property*, Size> dimProps;

  inline Component _getx() const noexcept {
    return _get<0>();
  }
  inline void _setx(const Component c) noexcept {
    _set<0>(c);
  }

  inline Component _gety() const noexcept {
    return _get<1>();
  }
  inline void _sety(const Component c) noexcept {
    _set<1>(c);
  }

  inline Component _getz() const noexcept {
    return _get<2>();
  }
  inline void _setz(const Component c) noexcept {
    _set<2>(c);
  }

  inline Component _getw() const noexcept {
    return _get<3>();
  }
  inline void _setw(const Component c) noexcept {
    _set<3>(c);
  }
  // I'm delegating these to one internal templated method for the sake of DRY.
  // I'd just use these methods in Q_PROPERTY directly, but it turns out that's
  // undocumented behavior, so different versions of Qt aren't consistent in
  // allowing it.


  void setEditorHints(const QString& hints) noexcept override {
    for (int i = 0; i < Size; ++i) {
      dimProps[i]->setEditorHints(hints);
    }
  }

private:
  // TODO: Replace this (maybe with a constructor parameter)
  virtual const QRegularExpression& regex() const noexcept = 0;

  template <int C>
  Component _get() const noexcept {
    return value().template value<Type>()[C];
  }

  template <int C>
  void _set(const Component& c) noexcept {
    Type v = value().template value<Type>();
    v[C] = c;

    Property::setValue(QVariant::fromValue<Type>(v));
  }
};
}

#endif // VECTORPROPERTY_HPP
