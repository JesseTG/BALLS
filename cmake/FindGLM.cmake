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

libfind_pkg_check_modules(PC_GLM glm)

if (WIN32)
  # Find include files
  find_path(
    GLM_INCLUDE_DIR
    NAMES glm/glm.hpp
    HINTS
      ${PC_GLM_INCLUDE_DIRS}
      ${GLM_ROOT_DIR}
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
      glm
      glm/glm
      glm/include
    DOC "The directory where glm/glm.hpp resides")
else()
  # Find include files
  find_path(
    GLM_INCLUDE_DIR
    NAMES glm/glm.hpp
    HINTS
      ${PC_GLM_INCLUDE_DIRS}
      ${GLM_ROOT_DIR}/include
      $ENV{HOME}/include
    PATHS
      /opt
      /opt/include
      /opt/local/include
      /usr/local/include
      /usr/include
    DOC "The directory where glm/glm.hpp resides")
endif()

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLM
  FOUND_VAR GLM_FOUND
  REQUIRED_VARS GLM_INCLUDE_DIR
  VERSION_VAR GLM_VERSION
)

# Define GLM_INCLUDE_DIRS
if (GLM_FOUND)
  set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLM_INCLUDE_DIRS)
