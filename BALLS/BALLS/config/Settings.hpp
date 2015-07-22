#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QtCore/QVariant>
#include <QtGui/QOpenGLFunctions>

namespace balls {
namespace config {

namespace SettingKey {
const extern QString WireFrame;
const extern QString DepthTestEnabled;
const extern QString FaceCullingEnabled;
const extern QString Dithering;
const extern QString ClipDistance;
};


enum class ProgramParameter {
  DeleteStatus = GL_DELETE_STATUS,
  LinkStatus = GL_LINK_STATUS,
  ValidateStatus = GL_VALIDATE_STATUS,
  InfoLogLength = GL_INFO_LOG_LENGTH,
  AttachedShaders = GL_ATTACHED_SHADERS,
  ActiveAtomicCounterBuffers = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
  ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
  ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
  ActiveUniforms = GL_ACTIVE_UNIFORMS,
  ActiveUniformBlocks = GL_ACTIVE_UNIFORM_BLOCKS,
  ActiveUniformBlockMaxNameLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
  ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH,
  ComputeWorkGroupSize = GL_COMPUTE_WORK_GROUP_SIZE,
  ProgramBinaryLength = GL_PROGRAM_BINARY_LENGTH,
  TransformFeedbackBufferMode = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
  TransformFeedbackVaryings = GL_TRANSFORM_FEEDBACK_VARYINGS,
  TransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
  GeometryVerticesOut = GL_GEOMETRY_VERTICES_OUT,
  GeometryInputType = GL_GEOMETRY_INPUT_TYPE,
  GeometryOutputType = GL_GEOMETRY_OUTPUT_TYPE,
};

enum class GLError {
  InvalidEnum = GL_INVALID_ENUM,
  InvalidValue = GL_INVALID_VALUE,
  InvalidOperation = GL_INVALID_OPERATION,
};

enum class QueryType {
  SamplesPassed = GL_SAMPLES_PASSED,
  AnySamplesPassed = GL_ANY_SAMPLES_PASSED,
  AnySamplesPassedConservative = GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
  PrimitivesGenerated = GL_PRIMITIVES_GENERATED,
  TransformFeedbackPrimtivesWritten = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
  TimeElapsed = GL_TIME_ELAPSED,
};

enum class Primitive {
  Points = GL_POINTS,
  Lines = GL_LINES,
  Triangles = GL_TRIANGLES,
};

enum class RenderPrimitive {
  Points = GL_POINTS,
  Lines = GL_LINES,
  Triangles = GL_TRIANGLES,
  LineLoop = GL_LINE_LOOP,
  LineStrip = GL_LINE_STRIP,
  LinesAdjacency = GL_LINES_ADJACENCY,
  LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
};

enum class BufferType {
  Array = GL_ARRAY_BUFFER,
  Vertex = BufferType::Array,
  AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
  CopyRead = GL_COPY_READ_BUFFER,
  CopyWrite = GL_COPY_WRITE_BUFFER,
  DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
  DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
  ElementArray = GL_ELEMENT_ARRAY_BUFFER,
  Index = BufferType::ElementArray,
  PixelPack = GL_PIXEL_PACK_BUFFER,
  PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
  Query = GL_QUERY_BUFFER,
  ShaderStorage = GL_SHADER_STORAGE_BUFFER,
  Texture = GL_TEXTURE_BUFFER,
  TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
  Uniform = GL_UNIFORM_BUFFER,
};

enum class BindBufferTarget {
  AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
  TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
  ShaderStorage = GL_SHADER_STORAGE_BUFFER,
  Uniform = GL_UNIFORM_BUFFER,
};

enum class BindRenderBufferTarget {
  RenderBuffer = GL_RENDERBUFFER,
};

enum class BindTransformFeedbackTarget {
  TransformFeedback = GL_TRANSFORM_FEEDBACK,
};


enum class TextureType {
  OneD = GL_TEXTURE_1D,
  TwoD = GL_TEXTURE_2D,
  ThreeD = GL_TEXTURE_3D,
  OneDArray = GL_TEXTURE_1D_ARRAY,
  TwoDArray = GL_TEXTURE_2D_ARRAY,
  Rectangle = GL_TEXTURE_RECTANGLE,
  CubeMap = GL_TEXTURE_CUBE_MAP,
  CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
  Buffer = GL_TEXTURE_BUFFER,
  TwoDMultisample = GL_TEXTURE_2D_MULTISAMPLE,
  TwoDMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
};

enum class MipMapTarget {
  OneD = GL_TEXTURE_1D,
  TwoD = GL_TEXTURE_2D,
  ThreeD = GL_TEXTURE_3D,
  OneDArray = GL_TEXTURE_1D_ARRAY,
  TwoDArray = GL_TEXTURE_2D_ARRAY,
  CubeMap = GL_TEXTURE_CUBE_MAP,
  CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
};

enum class FrameBufferType {
  FrameBuffer = GL_FRAMEBUFFER,
  DrawFrameBuffer = GL_DRAW_FRAMEBUFFER,
  ReadFrameBuffer = GL_READ_FRAMEBUFFER,
};

enum class ClampColorTarget {
  ClampReadColor = GL_CLAMP_READ_COLOR,
};

enum class FrameBufferStatus {
  Complete = GL_FRAMEBUFFER_COMPLETE,
  Undefined = GL_FRAMEBUFFER_UNDEFINED,
  IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
  IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
  IncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
  IncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
  Unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
  IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
  IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
};

enum class BlendEquation {
  Add = GL_FUNC_ADD,
  Subtract = GL_FUNC_SUBTRACT,
  ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
  Min = GL_MIN,
  Max = GL_MAX,
};

enum class BlendFunction {
  Zero = GL_ZERO,
  One = GL_ONE,
  SourceColor = GL_SRC_COLOR,
  OneMinusSourceColor = GL_ONE_MINUS_SRC_COLOR,
  DestinationColor = GL_DST_COLOR,
  OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,
  SourceAlpha = GL_SRC_ALPHA,
  OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
  DestinationAlpha = GL_DST_ALPHA,
  OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
  ConstantColor = GL_CONSTANT_COLOR,
  OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
  ConstantAlpha = GL_CONSTANT_ALPHA,
  OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
  SourceAlphaSaturate = GL_SRC_ALPHA_SATURATE,
  Source1Color = GL_SRC1_COLOR,
  OneMinusSource1Color = GL_ONE_MINUS_SRC1_COLOR,
  Source1Alpha = GL_SRC1_ALPHA,
  OneMinusSource1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
};

enum class BufferFlag {
  Color = GL_COLOR_BUFFER_BIT,
  Depth = GL_DEPTH_BUFFER_BIT,
  Stencil = GL_STENCIL_BUFFER_BIT,
};

enum class ClientWaitSyncFlags {
  SyncFlushCommands = GL_SYNC_FLUSH_COMMANDS_BIT,
};

enum class SyncStatus {
  AlreadySignaled = GL_ALREADY_SIGNALED,
  TimeoutExpired = GL_TIMEOUT_EXPIRED,
  ConditionSatisfied = GL_CONDITION_SATISFIED,
  WaitFailed = GL_WAIT_FAILED,
};

enum class Buffer {
  Color = GL_COLOR,
  Depth = GL_DEPTH,
  Stencil = GL_STENCIL,
};

enum class Filter {
  Nearest = GL_NEAREST,
  Linear = GL_LINEAR,
};

enum class ColorCopyFunction {
  Copy = GL_COPY,
  CopyInverted = GL_COPY_INVERTED,
  Clear = GL_CLEAR,
  Set = GL_SET,
  NoOp = GL_NOOP,
  Invert = GL_INVERT,
  And = GL_AND,
  Nand = GL_NAND,
  Or = GL_OR,
  Nor = GL_NOR,
  Xor = GL_XOR,
  Equivalent = GL_EQUIV,
  AndReverse = GL_AND_REVERSE,
  AndInverted = GL_AND_INVERTED,
  OrReverse = GL_OR_REVERSE,
  OrInverted = GL_OR_INVERTED,
};

enum class FaceCullMode {
  Front = GL_FRONT,
  Back = GL_BACK,
  FrontAndBack = GL_FRONT_AND_BACK,
};

enum class VertexWinding {
  Clockwise = GL_CW,
  CounterClockwise = GL_CCW,
};

enum class DepthFunction {
  Never = GL_NEVER,
  Less = GL_LESS,
  Equal = GL_EQUAL,
  LessEqual = GL_LEQUAL,
  Greater = GL_GREATER,
  NotEqual = GL_NOTEQUAL,
  GreaterEqual = GL_GEQUAL,
  Always = GL_ALWAYS,
};

struct Setting {
  QVariant value;
  bool changed;

Setting() noexcept :
  Setting(0) {}
Setting(const QVariant& var, const bool c) noexcept :
  value(var), changed(c) {}
Setting(const QVariant& var) noexcept :
  Setting(var, false) {}
};
}
}

#endif // OPTIONS_HPP
