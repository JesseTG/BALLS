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

#include <QListWidgetItem>

#include "QPropertyEditorWidget.h"
#include "QPropertyModel.h"
#include "QVariantDelegate.h"
#include "Property.h"

QPropertyEditorWidget::QPropertyEditorWidget(QWidget* parent) noexcept :
QTreeView(parent), m_model(new QPropertyModel(this))
{
  setModel(m_model);
  setItemDelegate(new QVariantDelegate(this));
  setUniformRowHeights(true);
}


QPropertyEditorWidget::~QPropertyEditorWidget()
{
}

void QPropertyEditorWidget::addObject(QObject* subject) noexcept
{
  m_model->addItem(subject);
  expandToDepth(0);
  qCDebug(Properties) << subject->metaObject()->className() << subject->objectName()
  << "added to property manager" << this->objectName();
}

void QPropertyEditorWidget::setObject(QObject* subject) noexcept
{
  m_model->clear();
  qCDebug(Properties) << "Cleared property manager" << this->objectName();

  if (subject) {
    // If the desired subject actually exists...
    addObject(subject);
  }
}

void QPropertyEditorWidget::updateObject(QObject* subject) noexcept
{
  if (subject) {
    // If the desired subject actually exists...
    m_model->updateItem(subject);
    qCDebug(Properties) << "Object" << subject->objectName() <<
    "updated in property manager" << this->objectName();
  }
}

void QPropertyEditorWidget::registerCustomPropertyCB(UserTypeCB cb)
noexcept
{
  if (cb) {
    // If the desired callback actually exists...
    qCDebug(Properties) << "Custom property callback" << reinterpret_cast<void*>(cb)
    << "registered";
    m_model->registerCustomPropertyCB(cb);
  }
}

void QPropertyEditorWidget::unregisterCustomPropertyCB(UserTypeCB cb)
noexcept
{
  m_model->unregisterCustomPropertyCB(cb);
}

