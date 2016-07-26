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
#ifndef QPROPERTYMODEL_H_
#define QPROPERTYMODEL_H_

#include <QtCore/QAbstractItemModel>
#include <QRegularExpression>

class Property;

/**
 * The QPropertyModel handles the user defined properties of QObjects
 */
class QPropertyModel : public QAbstractItemModel {
  Q_OBJECT

public:
  /**
   * A typedef for a callback used to create user defined properties for custom
   * datatypes
   */
  typedef Property *(*UserTypeCB)(const QString &, QObject *, Property *);

  /**
   * Constructor
   * @param parent optional parent object
   */
  explicit QPropertyModel(QObject *parent = nullptr) noexcept;
  /// Destructor
  virtual ~QPropertyModel();

  QModelIndex
    index(int, int, const QModelIndex & = QModelIndex()) const override;

  QModelIndex parent(const QModelIndex &) const override;

  int rowCount(const QModelIndex & = QModelIndex()) const override;

  int columnCount(const QModelIndex & = QModelIndex()) const override;

  QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;

  bool
    setData(const QModelIndex &, const QVariant &, int = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &) const override;

  QVariant
    headerData(int, Qt::Orientation, int = Qt::DisplayRole) const override;

  QModelIndex buddy(const QModelIndex &) const override;

  /**
   * Adds the user properties of the given class to the QPropertyModel instance
   *
   * @param subject the QObject-derived object that contains user properties
   * that should be managed by this instance
   */
  void addItem(QObject *subject) noexcept;

  /**
   * Creates a dataChanged signal for the given object
   * @param subject the instance of a QObject based class that should be updated
   * @param parent optional model index the propertyObject is child of
   */
  void updateItem(
    QObject *subject, const QModelIndex &parent = QModelIndex()) noexcept;

  /**
   * Removes all objects from the model
   */
  void clear() noexcept;

  /**
   * Adds custom callback that will be used to create Property instances for
   * custom datatypes
   */
  void registerCustomPropertyCB(UserTypeCB callback) noexcept;

  /**
   * Adds custom callback that will be used to create Property instances for
   * custom datatypes
   */
  void unregisterCustomPropertyCB(UserTypeCB callback) noexcept;

  void setNameFilter(const QRegularExpression &filter) noexcept {
    m_filter = filter;
  }

  const QRegularExpression &getNameFilter() const noexcept {
    return m_filter;
  }


  // TODO: Add the ability to hide properties
  // TODO: Add the ability to remove objects
  // TODO: Set stuff in different roles (e.g. tooltips)
  // TODO: Add ability to sort properties

private:
  QColor _color;

  /// Adds dynamic properties to the model
  void addDynamicProperties(Property *parent, QObject *propertyObject) noexcept;

  /// The Root Property for all objects
  Property *m_rootItem;

  /// Any property names that match this filter will not be visible.
  QRegularExpression m_filter;

  /// Custom callback
  QList<UserTypeCB> m_userCallbacks;
};
#endif
