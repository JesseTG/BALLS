project(QPropertyEditor)

set(QPROPERTYEDITOR_SOURCES
  precompiled.cpp
  QPropertyEditor/ColorCombo.cpp
  QPropertyEditor/Property.cpp
  QPropertyEditor/QPropertyEditorWidget.cpp
  QPropertyEditor/QPropertyModel.cpp
  QPropertyEditor/QVariantDelegate.cpp
  QPropertyEditor/EnumProperty.cpp
)

set(QPROPERTYEDITOR_HEADERS
  QPropertyEditor/ColorCombo.h
  QPropertyEditor/Property.h
  QPropertyEditor/QPropertyEditorWidget.h
  QPropertyEditor/QPropertyModel.h
  QPropertyEditor/QVariantDelegate.h
  QPropertyEditor/EnumProperty.h
  precompiled.hpp
)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/src
  .
)

find_package(Qt5Core ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Widgets ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Gui ${BALLS_MIN_QT_REQUIRED} REQUIRED)

add_library(${PROJECT_NAME} STATIC ${QPROPERTYEDITOR_SOURCES} ${QPROPERTYEDITOR_HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "precompiled.hpp")

add_precompiled_header(${PROJECT_NAME} precompiled.hpp SOURCE_CXX precompiled.cpp)