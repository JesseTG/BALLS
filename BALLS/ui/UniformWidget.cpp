#include "precompiled.hpp"
#include "ui/UniformWidget.hpp"

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStyle>
#include <QtWidgets/QVBoxLayout>

#include "Constants.hpp"
#include "ui/VectorWidget.hpp"

namespace balls {

template <class T>
using UChangeMemFunc = void (T::*)(const QString&, const QVariant&);

template <class T, class U>
using Change = void (T::*)(const U);

UniformWidget::UniformWidget(QWidget* parent)
  : QWidget(parent), _colorPickerIcon(Constants::COLOR_ICON) {}

UniformWidget::~UniformWidget() {
  #ifdef DEBUG
  qDebug() << Q_FUNC_INFO << "called";
  #endif
}

void UniformWidget::addUniforms(const balls::shader::UniformMap& uniforms) {
  Q_ASSERT(this->layout() != nullptr);

  for (const auto& u : uniforms) {
    // For each new uniform that just came in...
    QWidget* uniform = new QWidget(this);
    {
      uniform->setObjectName(u.first);
      QHBoxLayout* layout = new QHBoxLayout(uniform);
      {
        layout->setContentsMargins(0, 0, 0, 0);
        QLabel* uniformName = new QLabel(uniform);
        {
          uniformName->setText(u.first);
        }
        layout->addWidget(uniformName);

        if (util::isVectorType(u.second)) {
          // If this is a vector type...
          VectorWidget* vw = new VectorWidget(u.second, uniform);
          {
            vw->setObjectName(u.first);
            bool connected =
              QObject::connect <
              UChangeMemFunc<VectorWidget>,
              UChangeMemFunc<UniformWidget>
              > (
                vw,
                &VectorWidget::valueChanged,
                this,
                &UniformWidget::uniformValueChanged
              );
            Q_ASSERT(connected);
          }
          layout->addWidget(vw);
        }
        else if (util::isScalarType(u.second)) {
          // So since this is a scalar type...

          switch (util::getComponentType(u.second)) {
          case Type::Bool: {
            QCheckBox* check = new QCheckBox(uniform);
            {
              check->setObjectName(u.first);
              bool connected =
                QObject::connect <
                Change<QCheckBox, bool>,
                Change<UniformWidget, bool>
                > (
                  check,
                  &QCheckBox::toggled,
                  this,
                  &UniformWidget::_boolChanged
                );
              Q_ASSERT(connected);
            }
            layout->addWidget(check);
            break;
          }

          case Type::UInt:
          case Type::Int:
          case Type::Float:
          case Type::Double: {
            QDoubleSpinBox* spin = new QDoubleSpinBox(uniform);
            {
              spin->setObjectName(u.first);
              spin->setSingleStep(DOUBLE_STEP);
              spin->setRange(-FloatLimits::infinity(), FloatLimits::infinity());
              spin->setDecimals(PRECISION);
              spin->setProperty(Constants::INDEX_PROPERTY, 0);
              bool connected =
                QObject::connect <
                Change<QDoubleSpinBox, double>,
                Change<UniformWidget, double>
                > (
                  spin,
                  &QDoubleSpinBox::valueChanged,
                  this,
                  &UniformWidget::_doubleChanged
                );
              Q_ASSERT(connected);
            }
            layout->addWidget(spin);
            break;
          }
          }
        }
        else {
          QLabel* notSupported = new QLabel(
            "Direct modifications not supported",
            uniform
          );
          layout->addWidget(notSupported);
        }

        uniform->setLayout(layout);
      }
    }
    this->layout()->addWidget(uniform);
    #ifdef DEBUG
    qDebug() << "Added uniform" << u.first;
    #endif
  }
}

void UniformWidget::removeUniforms(const QStringList& uniforms) {
  for (const QString& u : uniforms) {
    QWidget* child = this->findChild<QWidget*>(u);
    Q_ASSERT(child != nullptr);
    delete child;
    #ifdef DEBUG
    qDebug() << "Removed uniform" << u;
    #endif
  }
}

void UniformWidget::_boolChanged(const bool b) {
  QObject* send = sender();
  Q_ASSERT(send != nullptr);
  this->uniformValueChanged(send->objectName(), b);
}

void UniformWidget::_intChanged(const int i) {
  QObject* send = sender();
  Q_ASSERT(send != nullptr);
  this->uniformValueChanged(send->objectName(), i);
}

void UniformWidget::_floatChanged(const float f) {
  QObject* send = sender();
  Q_ASSERT(send != nullptr);
  this->uniformValueChanged(send->objectName(), f);
}

void UniformWidget::_doubleChanged(const double d) {
  QObject* send = sender();
  Q_ASSERT(send != nullptr);
  this->uniformValueChanged(send->objectName(), d);
}

void UniformWidget::_uintChanged(const unsigned int u) {
  QObject* send = sender();
  Q_ASSERT(send != nullptr);
  this->uniformValueChanged(send->objectName(), u);
}
}
