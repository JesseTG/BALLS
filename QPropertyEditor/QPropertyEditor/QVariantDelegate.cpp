// *************************************************************************************************
//
// QPropertyEditor v 0.3
//
// --------------------------------------
// Copyright (C) 2007 Volker Wiendl
// Acknowledgements to Roman alias banal from qt-apps.org for the Enum
// enhancement
//
//
// The QPropertyEditor Library is free software; you can redistribute it and/or
// modify
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

#include "QVariantDelegate.h"

#include <QtCore/QSignalMapper>
#include <QtWidgets/QAbstractItemView>

#include "Property.h"

static const QRegularExpression HINTS(
  R"%(([a-zA-Z_][\d\w]+)=([\d\w.]+))%",
  QRegularExpression::CaseInsensitiveOption
    | QRegularExpression::OptimizeOnFirstUsageOption);

QVariantDelegate::QVariantDelegate(QObject *parent) noexcept
  : QItemDelegate(parent),
    m_finishedMapper(new QSignalMapper(this)) {
  connect(
    m_finishedMapper,
    SIGNAL(mapped(QWidget *)),
    this,
    SIGNAL(commitData(QWidget *)));
  connect(
    m_finishedMapper,
    SIGNAL(mapped(QWidget *)),
    this,
    SIGNAL(closeEditor(QWidget *)));
}

QVariantDelegate::~QVariantDelegate() {}

QWidget *QVariantDelegate::createEditor(
  QWidget *parent,
  const QStyleOptionViewItem &option,
  const QModelIndex &index) const {
  QWidget *editor = nullptr;
  Property *p = static_cast<Property *>(index.internalPointer());

  switch (p->value().type()) {
  case QVariant::Color:
  case QVariant::Int:
  case QMetaType::Float:
  case QVariant::Double:
  case QVariant::Bool:
  case QVariant::UserType:
    editor = p->createEditor(parent, option);

    if (editor) {
      // If we could create an editor for this property...
      if (editor->metaObject()->indexOfSignal("editFinished()") != -1) {
        // If the new editor has a "editFinished()" signal...
        connect(editor, SIGNAL(editFinished()), m_finishedMapper, SLOT(map()));
        m_finishedMapper->setMapping(editor, editor);
      }

      break; // if no editor could be created take default case
    }

  default:
    editor = QItemDelegate::createEditor(parent, option, index);
  }

  parseEditorHints(editor, p->editorHints());
  return editor;
}

void QVariantDelegate::setEditorData(
  QWidget *editor, const QModelIndex &index) const {
  m_finishedMapper->blockSignals(true);
  {
    QVariant data = index.model()->data(index, Qt::EditRole);

    switch (data.type()) {
    case QVariant::Color:
    case QMetaType::Double:
    case QMetaType::Float:
    case QVariant::UserType:
    case QVariant::Bool:
    case QVariant::Int: {
      Property *p = static_cast<Property *>(index.internalPointer());
      if (p->setEditorData(editor, data)) {
        // If we gave the editor the right type of data...
        break;
      }
    }

    default:
      QItemDelegate::setEditorData(editor, index);
      break;
    }
  }
  m_finishedMapper->blockSignals(false);
}

void QVariantDelegate::setModelData(
  QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  QVariant data = index.model()->data(index, Qt::EditRole);

  switch (data.type()) {
  case QVariant::Color:
  case QMetaType::Double:
  case QMetaType::Float:
  case QVariant::UserType:
  case QVariant::Bool:
  case QVariant::Int: {
    QVariant data =
      static_cast<Property *>(index.internalPointer())->editorData(editor);

    if (data.isValid()) {
      // If the property's editor has something valid...
      model->setData(index, data, Qt::EditRole);
      break;
    }
  }

  default:
    QItemDelegate::setModelData(editor, model, index);
    break;
  }
}

void QVariantDelegate::parseEditorHints(
  QWidget *editor, const QString &editorHints) const noexcept {
  if (editor && !editorHints.isEmpty()) {
    // If we have a valid property editor and some hints to give it...
    editor->blockSignals(true);
    {
      QRegularExpressionMatchIterator matches = HINTS.globalMatch(editorHints);
      if (matches.isValid() && matches.hasNext()) {
        // If there were any hints to use...
        do {
          auto m = matches.next();
          QString property = m.captured(1);
          QString value = m.captured(2);
          qDebug() << "Setting" << property << "to" << value;

          editor->setProperty(qPrintable(property), value);
        } while (matches.hasNext());
      }
    }
    editor->blockSignals(false);
  }
}
