project(BALLS-Tests)

add_custom_target(BALLS-Tests)

find_package(Qt5Core ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Gui ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Widgets ${BALLS_MIN_QT_REQUIRED} REQUIRED)
find_package(Qt5Test ${BALLS_MIN_QT_REQUIRED} REQUIRED)

add_subdirectory(TestConversions)
add_subdirectory(TestJSONConversions)
add_subdirectory(TestUniforms)
add_subdirectory(PropertyObjectTests)
