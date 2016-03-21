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
#ifndef QPROPERTYEDITORWIDGET_H_
#define QPROPERTYEDITORWIDGET_H_

#include <QtWidgets/QTreeView>

class QPropertyModel;
class Property;
class QListWidgetItem;

/**
 * \mainpage QPropertyEditor
 *
 * \section intro_sec Introduction
 *
 * Visualizes and allows manipulation of properties defined via the Q_PROPERTY
 * macro in QObject subclasses.
 */

/**
 * \brief An easy to use mechanism to visualize properties of a QObject subclass.
 *
 * Qt provides a nice way to define class properties by using the Q_PROPERTY
 * macro. The purpose of the QPropertyEditor is to visualize these properties in
 * an easy way.
 *
 * To use the property editor, all you have to do is to create a class that
 * defines it's properties by using Q_PROPERTY and to add this class by using
 * the addObject() method of this QPropertyEditorWidget class. The
 * QPropertyEditorWidget is inherited from QTreeView and will display the
 * properties in a tree with two columns: Name and Value
 *
 * For basic data types the build in editor widgets of Qt will be used. The
 * QPropertyEditor itself only defines an additional editor for QColor (based on
 * the Color Editor Factory Example from Trolltech). But it can easily be
 * extended by yourself either within the library or for special datatypes also
 * outside of the library in your application.
 */
class QPropertyEditorWidget : public QTreeView {
  Q_OBJECT
public:

  /**
   * A typedef for a callback used to create user defined properties for custom
   * datatypes
   */
  typedef Property* (*UserTypeCB)(const QString& name, QObject* subject,
                                  Property* parent);

  /**
   * \brief Constructor
   *
   * Creates a new editor widget based on QTreeView
   * @param parent optional parent widget
   */
  QPropertyEditorWidget(QWidget* parent = nullptr) noexcept;

  /// Destructor
  virtual ~QPropertyEditorWidget();

  QPropertyModel* propertyModel() noexcept { return this->m_model; }
  const QPropertyModel* propertyModel() const noexcept { return this->m_model; }

public slots:
  /**
   * Adds the user properties of the given class to the QPropertyModel
   * associated with this view
   *
   * @param subject the class inherited from QObject that contains user
   *        properties that should be managed by the QPropertyModel associated
   *        with this view
   */
  void addObject(QObject* subject) noexcept;

  /**
   * Similar to the addObject() method this method adds the properties of the
   * given class to the QPropertyModel associated with this view. But in
   * contrast to addObject() it will clear the model before, removing all
   * previously added objects.
   *
   * @param subject the class inherited from QObject that contains user
   *        properties that should be managed by the QPropertyModel associated
   *        with this view
   */
  void setObject(QObject* subject) noexcept;

  /**
   * Updates the view for the given object. This can be useful if a property was
   * changed programmatically instead of using the view. In this case the view
   * normally will display the new property values only after the user clicked
   * on it. To overcome this problem you can call updateObject with the object
   * whose property was changed.
   */
  void updateObject(QObject* subject) noexcept;
public:
  /**
   * If you define custom datatypes outside of this library the QPropertyModel
   * will check if you also defined a callback that is responsible to create
   * custom property classes inherited from Property to handle these datatypes.
   * With this method you can register such a callback that will create custom
   * properties for custom datatypes.
   */
  void registerCustomPropertyCB(UserTypeCB callback) noexcept;

  /**
   * You can register more than one callback. If one such callback is no longer
   * in use, unregister it with this method.
   */
  void unregisterCustomPropertyCB(UserTypeCB callback) noexcept;

private:
  /// The Model for this view
  QPropertyModel*     m_model;

};
#endif
