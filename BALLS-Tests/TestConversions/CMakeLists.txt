project(TestConversions)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../../BALLS
  ${CMAKE_CURRENT_LIST_DIR}/../../QPropertyEditor
  .
)
# Note: It is important that BALLS's directory be listed before QPropertyEditor's,
# as they both have a file named "precompiled.hpp"

add_definitions(
  -DGLM_META_PROG_HELPERS
  -DGENERATOR_USE_GLM
  -DGLM_ENABLE_EXPERIMENTAL
)

add_executable(${PROJECT_NAME} WIN32 tst_TestConversions.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Test QPropertyEditor BALLS)
