// *************************************************************************************************
//
// QPropertyEditor v 0.3
//
// --------------------------------------
// Copyright (C) 2007 Volker Wiendl
// Acknowledgements to Roman alias banal from qt-apps.org for the Enum enhancement
//
//
// The QPropertyEditor Library is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 3 of the License
//
// The Horde3D Scene Editor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// *************************************************************************************************
#include "precompiled.hpp"
#include "Property.h"
#include "ColorCombo.h"

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>

Q_DECL_CONSTEXPR int DECIMALS = 2;
const float INCREMENT = std::pow(10, -DECIMALS);

    Property::Property(const QString& name, QObject* subject,
                   QObject* parent) noexcept :
QObject(parent), m_subject(subject)
{
  setObjectName(name);
}

QVariant Property::value(const int) const noexcept
{
  return (m_subject) ? m_subject->property(qPrintable(objectName())) : QVariant();
}

void Property::setValue(const QVariant& value) noexcept
{
  if (m_subject) {
    Q_ASSERT(value.isValid());
    m_subject->setProperty(qPrintable(objectName()), value);
  }
}

bool Property::isReadOnly() const noexcept
{
  if (!m_subject) {
    // If there is no subject...
    return true;
  }

  QByteArray name_b = objectName().toLocal8Bit();
  const char* name = name_b.data();
  // Just storing one const char* from qPrintable() is apparently undefined
  // I think it's because the temporary QByteArray that's created dies

  if (m_subject->dynamicPropertyNames().contains(name)) {
    // If the subject has a dynamic property with this name...
    return false;
  }

  const QMetaObject* meta = m_subject->metaObject();

  int index = meta->indexOfProperty(name);
  if (index != -1 && meta->property(index).isWritable()) {
    // If the static property with this name exists and is writable...
    return false;
  }

  return true;
}

template<class C, class P>
using Prop = void (C::*)(P);

QWidget* Property::createEditor(QWidget* parent,
                                const QStyleOptionViewItem&) noexcept
{
  using IntLimits = std::numeric_limits<int>;
  using UIntLimits = std::numeric_limits<unsigned int>;
  using FloatLimits = std::numeric_limits<float>;
  QWidget* editor = nullptr;

  switch (value().type())
  {
  case QVariant::Color : {
    editor = new ColorCombo(parent);
    break;
  }

  case QVariant::UInt: {
    QSpinBox* spin = new QSpinBox(parent);
    spin->setRange(UIntLimits::min(), IntLimits::max());
    connect<Prop<QSpinBox, int>, Prop<Property, unsigned int>>(
          spin,
          &QSpinBox::valueChanged,
          this,
          &Property::setValue
        );
    editor = spin;
    break;
  }

  case QVariant::Int: {
    QSpinBox* spin = new QSpinBox(parent);
    spin->setRange(IntLimits::min(), IntLimits::max());
    connect<Prop<QSpinBox, int>, Prop<Property, int>>(
          spin,
          &QSpinBox::valueChanged,
          this,
          &Property::setValue
        );
    editor = spin;
    break;
  }

  case QVariant::Bool: {
    QCheckBox* check = new QCheckBox(parent);
    check->setChecked(false);
    connect<Prop<QCheckBox, bool>, Prop<Property, bool>>(
          check,
          &QCheckBox::toggled,
          this,
          &Property::setValue
        );
    editor = check;
    break;
  }

  case QMetaType::Float:
  case QVariant::Double: {
    QDoubleSpinBox* spin = new QDoubleSpinBox(parent);
    spin->setRange(-FloatLimits::infinity(), FloatLimits::infinity());
    spin->setDecimals(DECIMALS);
    spin->setSingleStep(INCREMENT);
    connect<Prop<QDoubleSpinBox, double>, Prop<Property, double>>(
          spin,
          &QDoubleSpinBox::valueChanged,
          this,
          &Property::setValue
        );
    editor = spin;
    break;
  }

  default:
    return editor;
  }

  return editor;
}

bool Property::setEditorData(QWidget* editor,
                             const QVariant& data) noexcept
{
  Q_ASSERT(editor != nullptr);
  Q_ASSERT(value().isValid());

  switch (value().type())
  {
  case QVariant::Color:
    static_cast<ColorCombo*>(editor)->setColor(data.value<QColor>());
    return true;

  case QVariant::Bool:
    editor->blockSignals(true);
    static_cast<QCheckBox*>(editor)->setChecked(data.toBool());
    editor->blockSignals(false);
    return true;

  case QVariant::UInt:
  case QVariant::Int:
    editor->blockSignals(true);
    static_cast<QSpinBox*>(editor)->setValue(data.toInt());
    editor->blockSignals(false);
    return true;

  case QMetaType::Float:
  case QVariant::Double:
    editor->blockSignals(true);
    static_cast<QDoubleSpinBox*>(editor)->setValue(data.toDouble());
    editor->blockSignals(false);
    return true;

  default:
    return false;
  }

  return false;
}

QVariant Property::editorData(QWidget* editor) const noexcept
{
  Q_ASSERT(editor != nullptr);
  Q_ASSERT(value().isValid());

  switch (value().type())
  {
  case QVariant::Color:
    return static_cast<ColorCombo*>(editor)->color();

  case QVariant::Bool:
    return static_cast<QCheckBox*>(editor)->isChecked();

  case QVariant::UInt:
  case QVariant::Int:
    return static_cast<QSpinBox*>(editor)->value();

  case QMetaType::Float:
  case QVariant::Double:
    return static_cast<QDoubleSpinBox*>(editor)->value();

  default:
    return QVariant();
  }
}

Property* Property::findSubject(const QObject* subject) noexcept
{
  if (m_subject == subject) {
    return this;
  }

  for (QObject* o : children()) {
    Q_ASSERT(o != nullptr);
    Q_ASSERT(dynamic_cast<Property*>(o) != nullptr);

    Property* child = static_cast<Property*>(o)->findSubject(subject);

    if (child) {
      return child;
    }
  }

  return nullptr;
}

void Property::setValue(const double value) noexcept {
  setValue(QVariant(value));
}

void Property::setValue(const int value) noexcept {
  setValue(QVariant(value));
}

void Property::setValue(const bool value) noexcept {
  setValue(QVariant(value));
}

void Property::setValue(const unsigned int value) noexcept {
  setValue(QVariant(value));
}
