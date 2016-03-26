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
#include "QPropertyModel.h"

#include "Property.h"
#include "EnumProperty.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QItemEditorFactory>

using UserTypeCB = QPropertyModel::UserTypeCB;


QPropertyModel::QPropertyModel(QObject* parent) noexcept :
QAbstractItemModel(parent), m_rootItem(new Property("Root", 0, this))
{
  _color = QApplication::palette("QTreeView").brush(QPalette::Normal,
           QPalette::Button).color();
}


QPropertyModel::~QPropertyModel()
{
}

QModelIndex QPropertyModel::index(int row, int column,
                                  const QModelIndex& parent) const
{
  Property* parentItem = m_rootItem;

  if (parent.isValid()) {
    parentItem = static_cast<Property*>(parent.internalPointer());
  }

  if (row >= parentItem->children().size() || row < 0) {
    return QModelIndex();
  }

  return createIndex(row, column, parentItem->children().at(row));

}

QModelIndex QPropertyModel::parent(const QModelIndex& index) const
{
  if (!index.isValid()) {
    return QModelIndex();
  }

  Property* childItem = static_cast<Property*>(index.internalPointer());
  Property* parentItem = qobject_cast<Property*>(childItem->parent());

  if (!parentItem || parentItem == m_rootItem) {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int QPropertyModel::rowCount(const QModelIndex& parent) const
{
  Property* parentItem = m_rootItem;

  if (parent.isValid()) {
    parentItem = static_cast<Property*>(parent.internalPointer());
  }

  return parentItem->children().size();
}

int QPropertyModel::columnCount(const QModelIndex&) const
{
  return 2;
}

QVariant QPropertyModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  Property* item = static_cast<Property*>(index.internalPointer());

  switch (role)
  {
  case Qt::ToolTipRole:
  case Qt::DecorationRole:
  case Qt::DisplayRole:
  case Qt::EditRole:
    if (index.column() == 0) {
      return item->objectName().replace('_', ' ');
    }

    if (index.column() == 1) {
      return item->value(role);
    }

  case Qt::BackgroundRole:
    if (item->isRoot()) { return _color; }

    break;
  };

  return QVariant();
}

// edit methods
bool QPropertyModel::setData(const QModelIndex& index, const QVariant& value,
                             int role)
{
  if (index.isValid() && role == Qt::EditRole)
  {
    Property* item = static_cast<Property*>(index.internalPointer());
    item->setValue(value);
    emit dataChanged(index, index);
    return true;
  }

  return false;
}

Qt::ItemFlags QPropertyModel::flags(const QModelIndex& index) const
{
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }

  Property* item = static_cast<Property*>(index.internalPointer());

  // only allow change of value attribute
  if (item->isRoot()) {
    return Qt::ItemIsEnabled;
  }
  else if (item->isReadOnly()) {
    return Qt::ItemIsDragEnabled | Qt::ItemIsSelectable;
  }
  else {
    return Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable |
           Qt::ItemIsEditable;
  }
}


QVariant QPropertyModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    switch (section)
    {
    case 0:
      return tr("Name");

    case 1:
      return tr("Value");
    }
  }

  return QVariant();
}

QModelIndex QPropertyModel::buddy(const QModelIndex& index) const
{
  if (index.isValid() && index.column() == 0) {
    return createIndex(index.row(), 1, index.internalPointer());
  }

  return index;
}

void QPropertyModel::addItem(QObject* subject) noexcept
{
  using std::unordered_map;
  using std::vector;

  // first create property <-> class hierarchy
  QList<const QMetaObject*> classList;
  unordered_map<const QMetaObject*, vector<QMetaProperty>> properties;

  for (const QMetaObject* meta = subject->metaObject(); meta; meta = meta->superClass())
  {
    int count = meta->propertyCount();

    properties[meta] = vector<QMetaProperty>();

    for (int i = 0; i < count; ++i) {
      QMetaProperty property = meta->property(i);

      if (property.isDesignable(subject)) {
        // Hide Qt specific properties
        properties[meta].push_back(property);
      }
    }

    classList.push_front(meta);
  }

  vector<const QMetaObject*> toRemove;
  // remove empty classes from hierarchy list
  for (const QMetaObject* obj : classList) {
    if (properties[obj].empty()) {
      toRemove.push_back(obj);
    }
  }

  for (const QMetaObject* obj : toRemove) {
    properties.erase(obj);
  }

  // finally insert properties for classes containing them
  int r = rowCount();
  Property* propertyItem = nullptr;
  beginInsertRows(QModelIndex(), r, r + properties.size());

  for (const auto& obj : properties) {
    const QMetaObject* metaObject = obj.first;
    // Set default name of the hierarchy property to the class name
    QString name = subject->objectName();
    // Check if there is a special name for the class
    int index = metaObject->indexOfClassInfo(qPrintable(name));

    if (index != -1) {
      name = metaObject->classInfo(index).value();
    }

    // Create Property Item for class node
    propertyItem = new Property(name, nullptr, m_rootItem);

    for (const QMetaProperty& property : obj.second) {
      Property* p = nullptr;
      const char* pname = property.name();

      if (!Property::isBasicType(property.type())) {
        for (UserTypeCB cb : m_userCallbacks) {
          p = cb(pname, subject, propertyItem);

          if (p) { break; }
        }
      }

      if (p == nullptr) {
        if (property.isEnumType()) {
          p = new EnumProperty(pname, subject, propertyItem);
        }
        else {
          p = new Property(pname, subject, propertyItem);
        }
      }

      int index = metaObject->indexOfClassInfo(pname);

      if (index != -1) {
        p->setEditorHints(metaObject->classInfo(index).value());
      }
    }
  }

  endInsertRows();

  if (propertyItem) {
    addDynamicProperties(propertyItem, subject);
  }
}

void QPropertyModel::updateItem(QObject* subject,
                                const QModelIndex& parent) noexcept
{
  Property* parentItem = m_rootItem;

  if (parent.isValid()) {
    parentItem = static_cast<Property*>(parent.internalPointer());
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
      QObject* obj = childs[i];

      if (!(!obj->property("__Dynamic").toBool()
      || dynamicProperties.contains(qPrintable(obj->objectName())))) {
        beginRemoveRows(itemIndex.parent(), i - removed, i - removed);
        ++removed;
        delete obj;
        endRemoveRows();
      }
    }

    addDynamicProperties(static_cast<Property*>(parentItem->parent()), subject);
  }
}

void QPropertyModel::addDynamicProperties(Property* parent,
    QObject* subject) noexcept
{
  // Get dynamic property names
  QByteArrayList dynamicProps = subject->dynamicPropertyNames();

  QObjectList childs = parent->children();

  // Remove already existing properties from list
  for (int i = 0; i < childs.count(); ++i) {
    if (childs[i]->property("__Dynamic").toBool()) {

      int index = dynamicProps.indexOf(qPrintable(childs[i]->objectName()));

      if (index != -1) {
        dynamicProps.removeAt(index);
      }
    }
  }

  std::remove_if(dynamicProps.begin(), dynamicProps.end(), [&](const QByteArray & d) {
    return d.startsWith("_") || !subject->property(d.data()).isValid();
  });

  if (!dynamicProps.empty()) {
    QModelIndex parentIndex = createIndex(parent->row(), 0, parent);
    int rows = rowCount(parentIndex);
    beginInsertRows(parentIndex, rows, rows + dynamicProps.count() - 1);

    // Add properties left in the list
    for (const QByteArray& dynProp : dynamicProps) {
      QVariant v = subject->property(dynProp);
      Property* p = nullptr;

      if (!Property::isBasicType(v.type())) {
        for (UserTypeCB cb : m_userCallbacks) {
          p = cb(dynProp, subject, parent);

          if (p) { break; }
        }
      }

      if (p == nullptr) {
        p = new Property(dynProp, subject, parent);
      }

      p->setProperty("__Dynamic", true);
    }

    endInsertRows();
  }
}

void QPropertyModel::clear() noexcept
{
  beginRemoveRows(QModelIndex(), 0, rowCount());
  delete m_rootItem;
  m_rootItem = new Property("Root", nullptr, this);
  endRemoveRows();
}

void QPropertyModel::registerCustomPropertyCB(UserTypeCB callback) noexcept
{
  Q_ASSERT(callback != nullptr);

  if (!m_userCallbacks.contains(callback)) {
    m_userCallbacks.push_back(callback);
  }
}

void QPropertyModel::unregisterCustomPropertyCB(UserTypeCB callback) noexcept
{
  Q_ASSERT(callback != nullptr);

  int index = m_userCallbacks.indexOf(callback);

  if (index != -1) {
    m_userCallbacks.removeAt(index);
  }
}
