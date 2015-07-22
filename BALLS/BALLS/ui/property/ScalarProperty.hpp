#ifndef SCALARPROPERTY_HPP
#define SCALARPROPERTY_HPP

#include <QObject>
#include <QPropertyEditor/Property.h>

namespace balls {

template<class ScalarType>
class ScalarProperty : public Property {
public:
  ScalarProperty(
    const QString& name,
    QObject* subject,
    QObject* parent
) noexcept :
  Property(name, subject, parent) {
  }

  ScalarType scalar() const noexcept {
    return value().template value<ScalarType>();
  }

  void set_scalar(const ScalarType v) noexcept {
    return setValue(QVariant(v));
  }
};

extern template class ScalarProperty<int>;
extern template class ScalarProperty<bool>;
extern template class ScalarProperty<unsigned int>;
extern template class ScalarProperty<float>;
extern template class ScalarProperty<double>;

class IntProperty : public ScalarProperty<int> {
  Q_OBJECT
  Q_CLASSINFO("Type", "int")
  Q_PROPERTY(int scalar READ scalar WRITE set_scalar USER true FINAL)

  using ScalarProperty::ScalarProperty;
};

class FloatProperty : public ScalarProperty<float> {
  Q_OBJECT
  Q_CLASSINFO("Type", "float")
  Q_PROPERTY(float scalar READ scalar WRITE set_scalar USER true FINAL)

  using ScalarProperty::ScalarProperty;
};

class BoolProperty : public ScalarProperty<bool> {
  Q_OBJECT
  Q_CLASSINFO("Type", "bool")
  Q_PROPERTY(bool scalar READ scalar WRITE set_scalar USER true FINAL)

  using ScalarProperty::ScalarProperty;
};

class UIntProperty : public ScalarProperty<unsigned int> {
  Q_OBJECT
  Q_CLASSINFO("Type", "uint")
  Q_PROPERTY(unsigned int scalar READ scalar WRITE set_scalar USER true FINAL)

  using ScalarProperty::ScalarProperty;
};

class DoubleProperty : public ScalarProperty<double> {
  Q_OBJECT
  Q_CLASSINFO("Type", "double")
  Q_PROPERTY(double scalar READ scalar WRITE set_scalar USER true FINAL)

  using ScalarProperty::ScalarProperty;
};

}

#endif // SCALARPROPERTY_HPP
