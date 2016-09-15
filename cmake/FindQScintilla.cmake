# - Try to find the QScintilla2 includes and library
# which defines
#
# QSCINTILLA_FOUND - system has QScintilla2
# QSCINTILLA_INCLUDE_DIR - where to find qextscintilla.h
# QSCINTILLA_LIBRARIES - the libraries to link against to use QScintilla
# QSCINTILLA_LIBRARY - where to find the QScintilla library (not for general use)

# copyright (c) 2007 Thomas Moenicke thomas.moenicke@kdemail.net
# Heavily based on https://git.io/viwyp
#
# Redistribution and use is allowed according to the terms of the FreeBSD license.

include(FindPackageHandleStandardArgs)
include(LibFindMacros)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5PrintSupport)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(PC_QSCINTILLA QScintilla)

if (APPLE)
  find_program(BREW_EXECUTABLE brew)

  if (BREW_EXECUTABLE)
    execute_process(
      COMMAND "${BREW_EXECUTABLE}" "ls" "qscintilla2"
      RESULT_VARIABLE QSCINTILLA_INSTALLED_BREW
      OUTPUT_QUIET
      ERROR_QUIET
    )

    if (QSCINTILLA_INSTALLED_BREW EQUAL 0)
      # If the user has the qscintilla2 formula installed...
      execute_process(
        COMMAND "${BREW_EXECUTABLE}" "--prefix" "qscintilla2"
        RESULT_VARIABLE BREW_PREFIX_RESULT
        OUTPUT_VARIABLE BREW_PREFIX_OUTPUT
        OUTPUT_QUIET
        ERROR_QUIET
      )

      if (BREW_PREFIX_RESULT EQUAL 0)
        # brew --prefix will list where qscintilla2 would be installed, whether
        # or not it actually is.  I'd rather play it safe and not assume the
        # command succeeded, though.
        set(QSCINTILLA_BREW_ROOT "${BREW_PREFIX_OUTPUT}")
        message(STATUS "qscintilla2's brew root is ${QSCINTILLA_BREW_ROOT}")
      endif()

    else()
      message(WARNING "Couldn't find the qscintilla2 formula.")
    endif()
  else()
    message(WARNING "Couldn't find brew.  You should really install it.")
  endif()
endif()

find_path(QSCINTILLA_INCLUDE_DIR
  NAMES Qsci qsciglobal.h
  PATHS "${Qt5Core_INCLUDE_DIRS}" "${PC_QSCINTILLA_INCLUDE_DIRS}" "${QSCINTILLA_BREW_ROOT}/include" /usr/include/x86_64-linux-gnu/qt5
  PATH_SUFFIXES Qsci
)

find_library(QSCINTILLA_LIBRARY
  NAMES qt5scintilla2 libqt5scintilla2 "${PC_QSCINTILLA_LIBRARIES}"
  PATHS "${Qt5Core_LIBRARIES}" "${PC_QSCINTILLA_LIBRARY_DIRS}" "${QSCINTILLA_BREW_ROOT}/lib"
)

set(QSCINTILLA_PROCESS_LIBRARIES QSCINTILLA_LIBRARY QSCINTILLA_LIBRARIES)
set(QSCINTILLA_PROCESS_INCLUDE_DIRS QSCINTILLA_INCLUDE_DIR QSCINTILLA_INCLUDE_DIRS)

find_package_handle_standard_args(QScintilla
  FOUND_VAR QSCINTILLA_FOUND
  REQUIRED_VARS QSCINTILLA_LIBRARY QSCINTILLA_INCLUDE_DIR
  VERSION_VAR QSCINTILLA_VERSION
)

unset(BREW_EXECUTABLE CACHE)
# The usage of brew on OSX should be considered an implementation detail

mark_as_advanced(QSCINTILLA_INCLUDE_DIR QSCINTILLA_LIBRARY)