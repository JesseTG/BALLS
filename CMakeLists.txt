cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(BALLS-Parent)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

set(BALLS_MIN_QT_REQUIRED 5.5)

#TODO: Add ppa:nschloe/boost-nightly and ppa:nschloe/cmake-nightly to Vagrantfile

add_subdirectory(BALLS)
add_subdirectory(QPropertyEditor)
add_subdirectory(BALLS-Tests)

add_dependencies(BALLS QPropertyEditor)
add_dependencies(BALLS-Tests BALLS)