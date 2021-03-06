#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <QObject>

#include "model/OpenGLState.hpp"

namespace balls {

struct OpenGLPointers;

class Limits : public OpenGLState {
  Q_OBJECT

  /*
   * GL_ALIASED_LINE_WIDTH_RANGE
   * GL_COMPRESSED_TEXTURE_FORMATS
   * GL_NUM_COMPRESSED_TEXTURE_FORMATS
   * GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS
   * GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS
   * GL_MAX_COMPUTE_UNIFORM_BLOCKS
   * GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS
   * GL_MAX_COMPUTE_UNIFORM_COMPONENTS
   * GL_MAX_COMPUTE_ATOMIC_COUNTERS
   * GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS
   * GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS
   * GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS
   * GL_MAX_COMPUTE_WORK_GROUP_COUNT
   * GL_MAX_COMPUTE_WORK_GROUP_SIZE
      GL_MAX_DEBUG_GROUP_STACK_DEPTH
      GL_DEBUG_GROUP_STACK_DEPTH
      GL_DOUBLEBUFFER
      GL_MAJOR_VERSION
      GL_MAX_3D_TEXTURE_SIZE
      GL_MAX_ARRAY_TEXTURE_LAYERS
      GL_MAX_CLIP_DISTANCES
      GL_MAX_COLOR_TEXTURE_SAMPLES
      GL_MAX_COMBINED_ATOMIC_COUNTERS
      GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS
      GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS
      GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
      GL_MAX_COMBINED_UNIFORM_BLOCKS
      GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS
      GL_MAX_CUBE_MAP_TEXTURE_SIZE
      GL_MAX_DEPTH_TEXTURE_SAMPLES
      GL_MAX_DRAW_BUFFERS
      GL_MAX_DUAL_SOURCE_DRAW_BUFFERS
      GL_MAX_ELEMENTS_INDICES
      GL_MAX_ELEMENTS_VERTICES
      GL_MAX_FRAGMENT_ATOMIC_COUNTERS
      GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS
      GL_MAX_FRAGMENT_INPUT_COMPONENTS
      GL_MAX_FRAGMENT_UNIFORM_COMPONENTS
      GL_MAX_FRAGMENT_UNIFORM_VECTORS
      GL_MAX_FRAGMENT_UNIFORM_BLOCKS
      GL_MAX_FRAMEBUFFER_WIDTH
      GL_MAX_FRAMEBUFFER_HEIGHT
      GL_MAX_FRAMEBUFFER_LAYERS
      GL_MAX_FRAMEBUFFER_SAMPLES
      GL_MAX_GEOMETRY_ATOMIC_COUNTERS
      GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS
      GL_MAX_GEOMETRY_INPUT_COMPONENTS
      GL_MAX_GEOMETRY_OUTPUT_COMPONENTS
      GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS
      GL_MAX_GEOMETRY_UNIFORM_BLOCKS
      GL_MAX_GEOMETRY_UNIFORM_COMPONENTS
      GL_MAX_INTEGER_SAMPLES
      GL_MIN_MAP_BUFFER_ALIGNMENT
      GL_MAX_LABEL_LENGTH
      GL_MAX_PROGRAM_TEXEL_OFFSET
      GL_MIN_PROGRAM_TEXEL_OFFSET
      GL_MAX_RECTANGLE_TEXTURE_SIZE
      GL_MAX_RENDERBUFFER_SIZE
      GL_MAX_SAMPLE_MASK_WORDS
      GL_MAX_SERVER_WAIT_TIMEOUT
      GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS
      GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS
      GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS
      GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS
      GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS
      GL_MAX_TEXTURE_BUFFER_SIZE
      GL_MAX_TEXTURE_IMAGE_UNITS
      GL_MAX_TEXTURE_LOD_BIAS
      GL_MAX_TEXTURE_SIZE
      GL_MAX_UNIFORM_BUFFER_BINDINGS
      GL_MAX_UNIFORM_BLOCK_SIZE
      GL_MAX_UNIFORM_LOCATIONS
      GL_MAX_VARYING_COMPONENTS
      GL_MAX_VARYING_VECTORS
      GL_MAX_VARYING_FLOATS
      GL_MAX_VERTEX_ATOMIC_COUNTERS
      GL_MAX_VERTEX_ATTRIBS
      GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS
      GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
      GL_MAX_VERTEX_UNIFORM_COMPONENTS
      GL_MAX_VERTEX_UNIFORM_VECTORS
      GL_MAX_VERTEX_OUTPUT_COMPONENTS
      GL_MAX_VERTEX_UNIFORM_BLOCKS
      GL_MAX_VIEWPORT_DIMS
      GL_MAX_VIEWPORTS
      GL_MINOR_VERSION
      GL_NUM_COMPRESSED_TEXTURE_FORMATS
      GL_NUM_EXTENSIONS
      GL_NUM_PROGRAM_BINARY_FORMATS
      GL_NUM_SHADER_BINARY_FORMATS
GL_POINT_SIZE_GRANULARITY
GL_POINT_SIZE_RANGE
GL_SMOOTH_LINE_WIDTH_RANGE
GL_SMOOTH_LINE_WIDTH_GRANULARITY
GL_STEREO
GL_SUBPIXEL_BITS
GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET
GL_MAX_VERTEX_ATTRIB_BINDINGS
GL_VIEWPORT_BOUNDS_RANGE
GL_VIEWPORT_SUBPIXEL_BITS
GL_MAX_ELEMENT_INDEX
   */
public:
  Limits(OpenGLPointers&, QObject* = nullptr);

private /* fields */:
};
}

Q_DECLARE_METATYPE(balls::Limits*)

#endif // LIMITS_HPP
