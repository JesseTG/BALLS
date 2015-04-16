#include "precompiled.hpp"
#include "ui/VectorWidget.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLayout>

#include "Constants.hpp"
#include "util/Util.hpp"

namespace balls {

using std::array;

template <class T>
using DoubleChange = void (T::*)(double);

VectorWidget::VectorWidget(const GLenum type, QWidget* parent)
  : QWidget(parent),
    _glType(type),
    _qType(util::getComponentType(type)),
    _size(util::getNumComponents(type)),
    _values(_size, nullptr) {

  QLayout* layout = new QHBoxLayout();
  this->setLayout(layout);

  auto makeIntSpins = [this, &layout](const int min, const int max) {
    for (int i = 0; i < _size; ++i) {
      QSpinBox* spin = new QSpinBox(this);
      {
        spin->setSingleStep(INT_STEP);
        spin->setRange(min, max);
        spin->setProperty(Constants::INDEX_PROPERTY, i);
      }
      layout->addWidget(spin);
    }
  };

  switch (_qType) {
  case Type::Bool: {
    for (int i = 0; i < _size; ++i) {
      QCheckBox* check = new QCheckBox(this);
      { check->setProperty(Constants::INDEX_PROPERTY, i); }
      layout->addWidget(check);

      _values[i] = check;
    }

    break;
  }

  case Type::Int: {
    makeIntSpins(IntLimits::min(), IntLimits::max());
    break;
  }

  case Type::UInt: {
    makeIntSpins(0, IntLimits::max());
    break;
  }

  case Type::Float:
  case Type::Double: {
    for (int i = 0; i < _size; ++i) {
      QDoubleSpinBox* spin = new QDoubleSpinBox(this);
      {
        spin->setSingleStep(DOUBLE_STEP);
        spin->setRange(-FloatLimits::infinity(), FloatLimits::infinity());
        spin->setDecimals(PRECISION);
        spin->setProperty(Constants::INDEX_PROPERTY, i);
        bool connected =
          QObject::connect <
          DoubleChange<QDoubleSpinBox>,
          DoubleChange<VectorWidget>
          > (
            spin,
            &QDoubleSpinBox::valueChanged,
            this,
            &VectorWidget::_updateValue
          );
        Q_ASSERT(connected);
      }
      layout->addWidget(spin);
    }

    break;
  }

  default:
    Q_UNREACHABLE();
  }
}

VectorWidget::~VectorWidget() {
  for (QWidget* w : this->_values) {
    delete w;
  }

  #ifdef DEBUG
  qDebug() << Q_FUNC_INFO << "called";
  #endif
}

void VectorWidget::setValue(const QVector2D& v) {
  this->_size = 2;
  this->_v2 = v;
}

void VectorWidget::setValue(const QVector3D& v) {
  this->_size = 3;
  this->_v3 = v;
}

void VectorWidget::setValue(const QVector4D& v) {
  this->_size = 4;
  this->_v4 = v;
}

void VectorWidget::setValue(const QVariant& var) {
  switch (var.type()) {
  case QVariant::Vector2D:
    this->setValue(var.value<QVector2D>());
    break;

  case QVariant::Vector3D:
    this->setValue(var.value<QVector3D>());
    break;

  case QVariant::Vector4D:
    this->setValue(var.value<QVector4D>());
    break;

  default:
    Q_UNREACHABLE();
  }
}

QVariant VectorWidget::getVector() const Q_DECL_NOEXCEPT {
  switch (_size) {
  case 2:
    return getVector2D();

  case 3:
    return getVector3D();

  case 4:
    return getVector3D();

  default:
    Q_UNREACHABLE();
    return 0;
  }
}

void VectorWidget::_updateValue(const double value) {
  QObject* send = sender();
  Q_ASSERT(send != nullptr);

  QVariant index = send->property(Constants::INDEX_PROPERTY);
  Q_ASSERT(index.isValid() && index.canConvert(QVariant::Int));
  int i = index.toInt();

  Q_ASSERT(2 <= _size && _size <= 4);

  switch (this->_size) {
  case 2: {
    Q_ASSERT(0 <= i && i < 2);
    this->_v2[i] = value;
    this->valueChanged(objectName(), _v2);
    break;
  }

  case 3: {
    Q_ASSERT(0 <= i && i < 3);
    this->_v3[i] = value;
    this->valueChanged(objectName(), _v3);
    break;
  }

  case 4: {
    Q_ASSERT(0 <= i && i < 4);
    this->_v4[i] = value;
    this->valueChanged(objectName(), _v4);
    break;
  }

  default:
    Q_UNREACHABLE();
  }
}
}
