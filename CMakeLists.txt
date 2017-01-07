cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(BALLS-Parent)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTORCC_OPTIONS --threshold 0 --compress 9)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set(BALLS_MIN_QT_REQUIRED 5.5)
set(BALLS_MIN_BOOST_REQUIRED 1.50)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(PrecompiledHeader)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(
    -DDEBUG
  )

  message("Building in Debug mode")
endif()

add_definitions(
  -DGLM_META_PROG_HELPERS
  -DGENERATOR_USE_GLM
  -DGLM_ENABLE_EXPERIMENTAL
)

find_package(Qt5Core ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Widgets ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Gui ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(GLM REQUIRED)
find_package(Generator REQUIRED)
find_package(QScintilla REQUIRED)

add_custom_target(BALLS-Parent
  SOURCES
    Vagrantfile
    README.md
    CONTRIBUTING.md
    .gitignore
    .clang-format
)
add_subdirectory(BALLS)
add_subdirectory(QPropertyEditor)
add_subdirectory(BALLS-Tests)
add_subdirectory(BALLS-Main)

add_dependencies(BALLS QPropertyEditor)
add_dependencies(BALLS-Tests BALLS)
add_dependencies(BALLS-Main BALLS)

