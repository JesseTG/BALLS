## Find GLM
#
# Try to find GLM : OpenGL Mathematics.
# This module defines
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
#
# The following variables can be set as arguments for the module.
# - GLM_ROOT_DIR : Root library directory of GLM
#
# References:
# - https://github.com/Groovounet/glm/blob/master/util/FindGLM.cmake
# - https://bitbucket.org/alfonse/gltut/src/28636298c1c0/glm-0.9.0.7/FindGLM.cmake
# - https://git.io/vMGyG
#

# Additional modules

include(FindPackageHandleStandardArgs)
include(LibFindMacros)

libfind_pkg_check_modules(PC_GENERATOR generator)

if (WIN32)
  # Find include files
  find_path(
    GENERATOR_INCLUDE_DIR
    NAMES generator/generator.hpp
    HINTS
      ${PC_GENERATOR_INCLUDE_DIRS}
      ${GENERATOR_ROOT_DIR}
      $ENV{USERPROFILE}
      $ENV{PROGRAMFILES}
      $ENV{PROGRAMDATA}
      $ENV{PROGRAMFILES\(X86\)}
      $ENV{COMMONPROGRAMW6432}
      $ENV{COMMONPROGRAMFILES\(X86\)}
      $ENV{COMMONPROGRAMFILES}
      $ENV{PROGRAMW6432}
    PATH_SUFFIXES
      include
      generator
      generator/generator
      generator/include
    DOC "The directory where generator/generator.hpp resides")

  # I use generator-glm in BALLS, if you find this file on GitHub later you may wish to adjust it
  find_library(GENERATOR_LIBRARY
    NAMES generator-glm "${PC_GENERATOR_LIBRARIES}"
    HINTS
      ${PC_GENERATOR_LIBRARY_DIRS}
      ${GENERATOR_ROOT_DIR}
      $ENV{USERPROFILE}
      $ENV{PROGRAMFILES}
      $ENV{PROGRAMDATA}
      $ENV{PROGRAMFILES\(X86\)}
      $ENV{COMMONPROGRAMW6432}
      $ENV{COMMONPROGRAMFILES\(X86\)}
      $ENV{COMMONPROGRAMFILES}
      $ENV{PROGRAMW6432}
    PATH_SUFFIXES
      lib
      lib/generator
      generator
      generator/generator
      bin
      bin/generator
    PATHS
    DOC "Path to the generator library."
  )
else()
  # Find include files
  find_path(
    GENERATOR_INCLUDE_DIR
    NAMES generator/generator.hpp
    HINTS
      ${PC_GENERATOR_INCLUDE_DIRS}
      ${GENERATOR_ROOT_DIR}
      ${GENERATOR_ROOT_DIR}/include
      $ENV{HOME}/include
    PATHS
      /opt
      /opt/include
      /opt/local/include
      /usr/local/include
      /usr/include
    DOC "The directory where generator/generator.hpp resides")

  find_library(GENERATOR_LIBRARY
    NAMES generator-glm "${PC_GENERATOR_LIBRARIES}"
    HINTS
      ${PC_GENERATOR_LIBRARY_DIRS}
      ${GENERATOR_ROOT_DIR}
      $ENV{HOME}/lib
    PATH_SUFFIXES
      x86_64-linux-gnu
    PATHS
      /opt
      /opt/lib
      /usr/local/lib
      /usr/lib
    DOC "Path to the generator library."
  )
endif()

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(generator
  FOUND_VAR GENERATOR_FOUND
  REQUIRED_VARS GENERATOR_LIBRARY GENERATOR_INCLUDE_DIR
  VERSION_VAR GENERATOR_VERSION
)

# Define GENERATOR_INCLUDE_DIR
if (GENERATOR_FOUND)
  set(GENERATOR_INCLUDE_DIRS ${GENERATOR_INCLUDE_DIR})
  set(GENERATOR_LIBRARIES ${GENERATOR_LIBRARY})
endif()

# Hide some variables
mark_as_advanced(GENERATOR_INCLUDE_DIRS GENERATOR_LIBRARIES)
