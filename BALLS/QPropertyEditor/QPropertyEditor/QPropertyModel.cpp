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
#include "QPropertyModel.h"

#include "Property.h"
#include "EnumProperty.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QItemEditorFactory>

using UserTypeCB = QPropertyModel::UserTypeCB;

QPropertyModel::QPropertyModel(QObject *parent) noexcept
    : QAbstractItemModel(parent),
      m_rootItem(new Property("Root", nullptr, this)) {
  _color = QApplication::palette("QTreeView")
               .brush(QPalette::Normal, QPalette::Button)
               .color();
}

QPropertyModel::~QPropertyModel() {}

QModelIndex QPropertyModel::index(int row, int column,
                                  const QModelIndex &parent) const {
  Property *parentItem = m_rootItem;

  if (parent.isValid()) {
    // If the supposed parent actually exists...
    parentItem = static_cast<Property *>(parent.internalPointer());
  }

  if (row >= parentItem->children().size() || row < 0) {
    // If the property we want doesn't actually exist...
    return QModelIndex();
  }

  return createIndex(row, column, parentItem->children().at(row));
}

QModelIndex QPropertyModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) {
    // If we're not looking for anything that's actually in this model...
    return QModelIndex();
  }

  Property *childItem = static_cast<Property *>(index.internalPointer());
  Property *parentItem = qobject_cast<Property *>(childItem->parent());

  if (!parentItem || parentItem == m_rootItem) {
    // If the model index already represents a parent...
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int QPropertyModel::rowCount(const QModelIndex &parent) const {
  Property *parentItem = m_rootItem;

  if (parent.isValid()) {
    parentItem = static_cast<Property *>(parent.internalPointer());
  }

  return parentItem->children().size();
}

int QPropertyModel::columnCount(const QModelIndex &) const { return 2; }

QVariant QPropertyModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    // If the index we're given doesn't actually exist...
    return QVariant();
  }

  Property *item = static_cast<Property *>(index.internalPointer());

  switch (role) {
  case Qt::ToolTipRole:
  case Qt::DecorationRole:
  case Qt::DisplayRole:
  case Qt::EditRole:
    if (index.column() == 0) {
      // If the index represents the property's name...
      return item->objectName().replace('_', ' ');
    } else if (index.column() == 1) {
      // If the index represents the property's value...
      return item->value(role);
    }
    break;

  case Qt::BackgroundRole:
    if (item->isRoot()) {
      // If the index represents the overall property...
      return _color;
    }

    break;
  };

  return QVariant();
}

// edit methods
bool QPropertyModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  if (index.isValid() && role == Qt::EditRole) {
    // If there's an editable property here and we're looking to edit it...
    Property *item = static_cast<Property *>(index.internalPointer());
    item->setValue(value);
    emit dataChanged(index, index);
    return true;
  }

  return false;
}

Qt::ItemFlags QPropertyModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    // If we're looking for a model index that doesn't exist...
    return Qt::ItemIsEnabled;
  }

  Property *item = static_cast<Property *>(index.internalPointer());

  // only allow change of value attribute
  if (item->isRoot()) {
    // If this index represents the overall property...
    return Qt::ItemIsEnabled;
  } else if (item->isReadOnly()) {
    // If this index represents a read-only value...
    return Qt::ItemIsDragEnabled | Qt::ItemIsSelectable;
  } else {
    return Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable |
           Qt::ItemIsEditable;
  }
}

QVariant QPropertyModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    switch (section) {
    case 0:
      return tr("Name");

    case 1:
      return tr("Value");
    }
  }

  return QVariant();
}

QModelIndex QPropertyModel::buddy(const QModelIndex &index) const {
  if (index.isValid() && index.column() == 0) {
    // If we're asking for somewhere with a valid property name...
    return createIndex(index.row(), 1, index.internalPointer());
    // "You may be clicking on me, but you *really* want to edit this guy."
  }

  return index;
}

void QPropertyModel::addItem(QObject *subject) noexcept {
  using std::vector;

  // first create property <-> class hierarchy
  vector<QMetaProperty> properties;

  for (const QMetaObject *m = subject->metaObject(); m; m = m->superClass()) {
    // For each class in this object's ancestry...
    int offset = m->propertyOffset();
    int count = m->propertyCount();

    for (int p = offset; p < offset + count; ++p) {
      // For each property this class defines...
      QMetaProperty property = m->property(p);

      if (property.isDesignable(subject)) {
        // If this class is meant to be user-modified...
        properties.push_back(property);
      }
    }
  }

  // finally insert properties for classes containing them
  int r = rowCount();
  Property *propertyItem =
      new Property(subject->objectName(), nullptr, m_rootItem);
  // Root property
  beginInsertRows(QModelIndex(), r, r + properties.size());
  {
    for (const QMetaProperty &property : properties) {
      // For each static property this class defines...
      Property *p = nullptr;
      const char *pname = property.name();

      if (!Property::isBasicType(property.type())) {
        // If this property is not one of the built-in types...

        for (UserTypeCB cb : m_userCallbacks) {
          // For each of the custom callbacks we've registered...
          p = cb(pname, subject, propertyItem);

          if (p) {
            // If this callback provided a Property, we're done
            break;
          }
        }
      }

      if (p == nullptr) {
        // If we haven't managed to create a custom property...
        if (property.isEnumType()) {
          // If this property is an enum...
          p = new EnumProperty(pname, subject, propertyItem);
        } else {
          // Then just create a Property for one of the built-in types
          p = new Property(pname, subject, propertyItem);
        }
      }

      const QMetaObject* metaObject = subject->metaObject();
      int index = metaObject->indexOfClassInfo(pname);

      if (index != -1) {
        // If we defined a classinfo with the same name as the property...
        p->setEditorHints(metaObject->classInfo(index).value());
      }
    }
  }
  endInsertRows();

  if (propertyItem) {
    addDynamicProperties(propertyItem, subject);
  }
}

void QPropertyModel::updateItem(QObject *subject,
                                const QModelIndex &parent) noexcept {
  Property *parentItem = m_rootItem;

  if (parent.isValid()) {
    parentItem = static_cast<Property *>(parent.internalPointer());
  }

  if (parentItem->subject() != subject) {
    parentItem = parentItem->findSubject(subject);
  }

  if (parentItem) {
    // Indicate view that the data for the indices have changed
    QModelIndex itemIndex = createIndex(parentItem->row(), 0, parentItem);
    dataChanged(itemIndex, createIndex(parentItem->row(), 1, parentItem));
    QByteArrayList dynamicProperties = subject->dynamicPropertyNames();
    QObjectList childs = parentItem->parent()->children();

    for (int i = 0, removed = 0; i < childs.count(); ++i) {
      QObject *obj = childs[i];

      if (!(!obj->property("__Dynamic").toBool() ||
            dynamicProperties.contains(qPrintable(obj->objectName())))) {
        beginRemoveRows(itemIndex.parent(), i - removed, i - removed);
        {
          ++removed;
          delete obj;
        }
        endRemoveRows();
      }
    }

    addDynamicProperties(static_cast<Property *>(parentItem->parent()),
                         subject);
  }
}

void QPropertyModel::addDynamicProperties(Property *parent,
                                          QObject *subject) noexcept {
  // Get dynamic property names
  QByteArrayList dynamicProps = subject->dynamicPropertyNames();

  // Remove already existing properties from list
  for (QObject *child : parent->children()) {
    if (child->property("__Dynamic").toBool()) {
      // If this QObject has any dynamic properties...

      int index = dynamicProps.indexOf(qPrintable(child->objectName()));

      if (index != -1) {
        dynamicProps.removeAt(index);
      }
    }
  }

  std::remove_if(
      dynamicProps.begin(), dynamicProps.end(), [&](const QByteArray &d) {
        return d.startsWith("_") || !subject->property(d.data()).isValid();
      });
  // Remove any properties that are invalid or reserved

  if (!dynamicProps.empty()) {
    // If we have any dynamic properties left to add...
    QModelIndex parentIndex = createIndex(parent->row(), 0, parent);
    int rows = rowCount(parentIndex);
    beginInsertRows(parentIndex, rows, rows + dynamicProps.count() - 1);
    {
      for (const QByteArray &dynProp : dynamicProps) {
        // For each property left in the list...
        QVariant v = subject->property(dynProp);
        Property *p = nullptr;

        if (!Property::isBasicType(v.type())) {
          for (UserTypeCB cb : m_userCallbacks) {
            p = cb(dynProp, subject, parent);

            if (p) {
              break;
            }
          }
        }

        if (p == nullptr) {
          p = new Property(dynProp, subject, parent);
        }

        p->setProperty("__Dynamic", true);
      }
    }
    endInsertRows();
  }
}

void QPropertyModel::clear() noexcept {
  beginRemoveRows(QModelIndex(), 0, rowCount());
  {
    delete m_rootItem;
    m_rootItem = new Property("Root", nullptr, this);
  }
  endRemoveRows();
}

void QPropertyModel::registerCustomPropertyCB(UserTypeCB callback) noexcept {
  Q_ASSERT(callback != nullptr);

  if (!m_userCallbacks.contains(callback)) {
    m_userCallbacks.push_back(callback);
  }
}

void QPropertyModel::unregisterCustomPropertyCB(UserTypeCB callback) noexcept {
  Q_ASSERT(callback != nullptr);

  int index = m_userCallbacks.indexOf(callback);

  if (index != -1) {
    m_userCallbacks.removeAt(index);
  }
}
