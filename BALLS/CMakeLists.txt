project(BALLS)

set(BALLS_SOURCES
  precompiled.cpp
  config/ProjectConfig.cpp
  Constants.cpp
  exception/FileException.cpp
  exception/JsonException.cpp
  gl/OpenGLPointers.cpp
  main.cpp
  model/gl/BlendState.cpp
  model/gl/ClipOptions.cpp
  model/gl/ColorOptions.cpp
  model/gl/DepthOptions.cpp
  model/gl/GeometryOptions.cpp
  model/gl/Hints.cpp
  model/gl/ImplementationInfo.cpp
  model/gl/Limits.cpp
  model/gl/SampleOptions.cpp
  model/gl/StencilOptions.cpp
  model/ImageTexture.cpp
  model/mesh/BaseCylindricalMesh.cpp
  model/mesh/BaseSphereMesh.cpp
  model/mesh/BoxMesh.cpp
  model/mesh/CapsuleMesh.cpp
  model/mesh/ConeMesh.cpp
  model/mesh/CylinderMesh.cpp
  model/mesh/DiskMesh.cpp
  model/mesh/DodecahedronMesh.cpp
  model/mesh/IcosahedronMesh.cpp
  model/mesh/IcoSphereMesh.cpp
  model/mesh/Mesh.cpp
  model/mesh/MeshMesh.cpp
  model/mesh/PlaneMesh.cpp
  model/mesh/RoundedBoxMesh.cpp
  model/mesh/SphereMesh.cpp
  model/mesh/SphericalConeMesh.cpp
  model/mesh/SphericalTriangleMesh.cpp
  model/mesh/SpringMesh.cpp
  model/mesh/TorusKnotMesh.cpp
  model/mesh/TorusMesh.cpp
  model/mesh/TriangleMesh.cpp
  model/mesh/TubeMesh.cpp
  model/Meshes.cpp
  model/OpenGLState.cpp
  model/Texture.cpp
  model/Uniforms.cpp
  shader/ShaderInputs.cpp
  shader/ShaderUniform.cpp
  ui/BallsCanvas.cpp
  ui/BallsWindow.cpp
  ui/docks/MeshManagerWidget.cpp
  ui/docks/OpenGLStateWidget.cpp
  ui/docks/TextureManager.cpp
  ui/glslsyntax.cpp
  ui/property/MatrixProperties.cpp
  ui/property/MatrixProperty.cpp
  ui/property/Vector2Property.cpp
  ui/property/Vector3Property.cpp
  ui/property/Vector4Property.cpp
  ui/property/VectorProperty.cpp
  ui/QsciLexerGLSL.cpp
  ui/UniformWidget.cpp
  util/AABB.cpp
  util/ArcBall.cpp
  util/ArcLookAt.cpp
  util/Logging.cpp
  util/MetaTypeConverters.cpp
  util/TypeInfo.cpp
  util/Util.cpp
)

set(BALLS_HEADERS
  config/ProjectConfig.hpp
  Constants.hpp
  exception/FileException.hpp
  exception/JsonException.hpp
  gl/OpenGLPointers.hpp
  model/gl/BlendState.hpp
  model/gl/ClipOptions.hpp
  model/gl/ColorOptions.hpp
  model/gl/DepthOptions.hpp
  model/gl/GeometryOptions.hpp
  model/gl/Hints.hpp
  model/gl/ImplementationInfo.hpp
  model/gl/Limits.hpp
  model/gl/SampleOptions.hpp
  model/gl/StencilOptions.hpp
  model/ImageTexture.hpp
  model/mesh/BaseCylindricalMesh.hpp
  model/mesh/BaseSphereMesh.hpp
  model/mesh/BoxMesh.hpp
  model/mesh/CapsuleMesh.hpp
  model/mesh/ConeMesh.hpp
  model/mesh/CylinderMesh.hpp
  model/mesh/DiskMesh.hpp
  model/mesh/DodecahedronMesh.hpp
  model/mesh/IcosahedronMesh.hpp
  model/mesh/IcoSphereMesh.hpp
  model/mesh/Mesh.hpp
  model/mesh/MeshMesh.hpp
  model/mesh/PlaneMesh.hpp
  model/mesh/RoundedBoxMesh.hpp
  model/mesh/SphereMesh.hpp
  model/mesh/SphericalConeMesh.hpp
  model/mesh/SphericalTriangleMesh.hpp
  model/mesh/SpringMesh.hpp
  model/mesh/TorusKnotMesh.hpp
  model/mesh/TorusMesh.hpp
  model/mesh/TriangleMesh.hpp
  model/mesh/TubeMesh.hpp
  model/Meshes.hpp
  model/OpenGLState.hpp
  model/Texture.hpp
  model/Uniforms.hpp
  precompiled.hpp
  shader/ShaderInputs.hpp
  shader/ShaderUniform.hpp
  ui/BallsCanvas.hpp
  ui/BallsWindow.hpp
  ui/docks/MeshManagerWidget.hpp
  ui/docks/OpenGLStateWidget.hpp
  ui/docks/TextureManager.hpp
  ui/glslsyntax.hpp
  ui/property/MatrixProperties.hpp
  ui/property/MatrixProperty.hpp
  ui/property/Vector2Property.hpp
  ui/property/Vector3Property.hpp
  ui/property/Vector4Property.hpp
  ui/property/VectorProperty.hpp
  ui/QsciLexerGLSL.h
  ui/UniformWidget.hpp
  util/AABB.hpp
  util/ArcBall.hpp
  util/ArcLookAt.hpp
  util/Logging.hpp
  util/MetaTypeConverters.hpp
  util/TypeInfo.hpp
  util/Util.hpp
)

set(BALLS_RESOURCES
  resources.qrc
)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/../QPropertyEditor
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

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${BALLS_SOURCE} ${BALLS_HEADERS} ${BALLS_RESOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "precompiled.hpp")

add_precompiled_header(${PROJECT_NAME} precompiled.hpp SOURCE_CXX precompiled.cpp)