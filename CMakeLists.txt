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

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(PrecompiledHeader)

#TODO: Add ppa:nschloe/boost-nightly and ppa:nschloe/cmake-nightly to Vagrantfile

add_subdirectory(BALLS)
add_subdirectory(QPropertyEditor)
add_subdirectory(BALLS-Tests)
add_subdirectory(BALLS-Main)

add_dependencies(BALLS QPropertyEditor)
add_dependencies(BALLS-Tests BALLS)
add_dependencies(BALLS-Main BALLS)
