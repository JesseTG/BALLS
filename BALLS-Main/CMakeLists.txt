project(BALLS-Main)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/../BALLS
  ${CMAKE_CURRENT_LIST_DIR}/../QPropertyEditor
  ${CMAKE_CURRENT_BINARY_DIR}/../BALLS
  .
)

add_definitions(
  -DGLM_META_PROG_HELPERS
  -DGENERATOR_USE_GLM
  -DGLM_ENABLE_EXPERIMENTAL
)

find_package(Qt5Core ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Widgets ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Gui ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Boost)
find_package(QScintilla REQUIRED)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE main.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets QPropertyEditor generator-glm "${QSCINTILLA_LIBRARY}" BALLS)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "precompiled.hpp")
