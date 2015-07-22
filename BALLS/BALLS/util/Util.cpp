#include "precompiled.hpp"
#include "util/Util.hpp"
#include "util/Logging.hpp"
#include "Constants.hpp"

#include <QtCore/QJsonObject>

#define BALLS_GL_CONSTANT(T) case T: return #T

namespace balls {
namespace util {

using namespace logs;

uint8_t getNumComponents(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_FLOAT:
  case GL_DOUBLE:
    return 1;

  case GL_INT_VEC2:
  case GL_FLOAT_VEC2:
  case GL_DOUBLE_VEC2:
  case GL_UNSIGNED_INT_VEC2:
  case GL_BOOL_VEC2:
    return 2;

  case GL_INT_VEC3:
  case GL_FLOAT_VEC3:
  case GL_DOUBLE_VEC3:
  case GL_UNSIGNED_INT_VEC3:
  case GL_BOOL_VEC3:
    return 3;

  case GL_INT_VEC4:
  case GL_FLOAT_VEC4:
  case GL_DOUBLE_VEC4:
  case GL_UNSIGNED_INT_VEC4:
  case GL_BOOL_VEC4:
  case GL_FLOAT_MAT2:
  case GL_DOUBLE_MAT2:
    return 4;

  case GL_FLOAT_MAT2x3:
  case GL_FLOAT_MAT3x2:
  case GL_DOUBLE_MAT2x3:
  case GL_DOUBLE_MAT3x2:
    return 6;

  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT4x2:
  case GL_DOUBLE_MAT2x4:
  case GL_DOUBLE_MAT4x2:
    return 8;

  case GL_FLOAT_MAT3:
  case GL_DOUBLE_MAT3:
    return 9;

  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT4x3:
  case GL_DOUBLE_MAT3x4:
  case GL_DOUBLE_MAT4x3:
    return 12;

  case GL_FLOAT_MAT4:
  case GL_DOUBLE_MAT4:
    return 16;

  default:
    qCDebug(logs::gl::Type).nospace().noquote() <<
    "Cannot get component count of GLSL type " << resolveGLType(type)
    << " (" << QString(type).toInt(nullptr, 16) << ')';
    return 0;
  }
}

Type getComponentType(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
  case GL_BOOL_VEC2:
  case GL_BOOL_VEC3:
  case GL_BOOL_VEC4:
    return Type::Bool;

  case GL_INT:
  case GL_INT_VEC2:
  case GL_INT_VEC3:
  case GL_INT_VEC4:
    return Type::Int;

  case GL_UNSIGNED_INT:
  case GL_UNSIGNED_INT_VEC2:
  case GL_UNSIGNED_INT_VEC3:
  case GL_UNSIGNED_INT_VEC4:
    return Type::UInt;

  case GL_FLOAT:
  case GL_FLOAT_VEC2:
  case GL_FLOAT_VEC3:
  case GL_FLOAT_VEC4:
  case GL_FLOAT_MAT2:
  case GL_FLOAT_MAT2x3:
  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT3x2:
  case GL_FLOAT_MAT3:
  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT4x2:
  case GL_FLOAT_MAT4x3:
  case GL_FLOAT_MAT4:
    return Type::Float;

  case GL_DOUBLE:
  case GL_DOUBLE_VEC2:
  case GL_DOUBLE_VEC3:
  case GL_DOUBLE_VEC4:
  case GL_DOUBLE_MAT2:
  case GL_DOUBLE_MAT2x3:
  case GL_DOUBLE_MAT2x4:
  case GL_DOUBLE_MAT3x2:
  case GL_DOUBLE_MAT3:
  case GL_DOUBLE_MAT3x4:
  case GL_DOUBLE_MAT4x2:
  case GL_DOUBLE_MAT4x3:
  case GL_DOUBLE_MAT4:
    return Type::Double;

  default:
    qCDebug(logs::gl::Type).nospace().noquote() << "Cannot get component type of GLSL type "
    << resolveGLType(type) << " (" << QString(type).toInt(nullptr, 16) << ')';
    return Type::UnknownType;
  }
}

GLenum getGlComponentType(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
  case GL_BOOL_VEC2:
  case GL_BOOL_VEC3:
  case GL_BOOL_VEC4:
    return GL_BOOL;

  case GL_INT:
  case GL_INT_VEC2:
  case GL_INT_VEC3:
  case GL_INT_VEC4:
    return GL_INT;

  case GL_UNSIGNED_INT:
  case GL_UNSIGNED_INT_VEC2:
  case GL_UNSIGNED_INT_VEC3:
  case GL_UNSIGNED_INT_VEC4:
    return GL_UNSIGNED_INT;

  case GL_FLOAT:
  case GL_FLOAT_VEC2:
  case GL_FLOAT_VEC3:
  case GL_FLOAT_VEC4:
  case GL_FLOAT_MAT2:
  case GL_FLOAT_MAT2x3:
  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT3x2:
  case GL_FLOAT_MAT3:
  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT4x2:
  case GL_FLOAT_MAT4x3:
  case GL_FLOAT_MAT4:
    return GL_FLOAT;

  case GL_DOUBLE:
  case GL_DOUBLE_VEC2:
  case GL_DOUBLE_VEC3:
  case GL_DOUBLE_VEC4:
  case GL_DOUBLE_MAT2:
  case GL_DOUBLE_MAT2x3:
  case GL_DOUBLE_MAT2x4:
  case GL_DOUBLE_MAT3x2:
  case GL_DOUBLE_MAT3:
  case GL_DOUBLE_MAT3x4:
  case GL_DOUBLE_MAT4x2:
  case GL_DOUBLE_MAT4x3:
  case GL_DOUBLE_MAT4:
    return GL_DOUBLE;

  default:
    qCDebug(logs::gl::Type).nospace().noquote() << "Cannot get component type of GLSL type "
    << resolveGLType(type) << " (" << QString(type).toInt(nullptr, 16) << ')';
    return 0;
  }
}

Type getRepresentingType(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
    return Type::Bool;

  case GL_INT:
    return Type::Int;

  case GL_UNSIGNED_INT:
    return Type::UInt;

  case GL_FLOAT:
    return Type::Float;

  case GL_DOUBLE:
    return Type::Double;

  case GL_INT_VEC2:
  case GL_FLOAT_VEC2:
  case GL_DOUBLE_VEC2:
  case GL_UNSIGNED_INT_VEC2:
  case GL_BOOL_VEC2:
    return Type::QVector2D;

  case GL_INT_VEC3:
  case GL_FLOAT_VEC3:
  case GL_DOUBLE_VEC3:
  case GL_UNSIGNED_INT_VEC3:
  case GL_BOOL_VEC3:
    return Type::QVector3D;

  case GL_INT_VEC4:
  case GL_FLOAT_VEC4:
  case GL_DOUBLE_VEC4:
  case GL_UNSIGNED_INT_VEC4:
  case GL_BOOL_VEC4:
    return Type::QVector4D;

  case GL_FLOAT_MAT2:
  case GL_DOUBLE_MAT2:
  case GL_FLOAT_MAT2x3:
  case GL_FLOAT_MAT3x2:
  case GL_DOUBLE_MAT2x3:
  case GL_DOUBLE_MAT3x2:
  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT4x2:
  case GL_DOUBLE_MAT2x4:
  case GL_DOUBLE_MAT4x2:
  case GL_FLOAT_MAT3:
  case GL_DOUBLE_MAT3:
  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT4x3:
  case GL_DOUBLE_MAT3x4:
  case GL_DOUBLE_MAT4x3:
  case GL_FLOAT_MAT4:
  case GL_DOUBLE_MAT4:
    return Type::QMatrix4x4;

  default:
    qCDebug(logs::gl::Type).nospace().noquote() << "No Qt type to represent GLSL type "
    << resolveGLType(type) << " (" << QString(type).toInt(nullptr, 16) << ')';
    return Type::UnknownType;
  }
}

bool isVectorType(const GLenum type) noexcept {
  switch (type) {
  case GL_INT_VEC2:
  case GL_INT_VEC3:
  case GL_INT_VEC4:
  case GL_UNSIGNED_INT_VEC2:
  case GL_UNSIGNED_INT_VEC3:
  case GL_UNSIGNED_INT_VEC4:
  case GL_FLOAT_VEC2:
  case GL_FLOAT_VEC3:
  case GL_FLOAT_VEC4:
  case GL_DOUBLE_VEC2:
  case GL_DOUBLE_VEC3:
  case GL_DOUBLE_VEC4:
  case GL_BOOL_VEC2:
  case GL_BOOL_VEC3:
  case GL_BOOL_VEC4:
    return true;

  default:
    return false;
  }
}

bool isMatrixType(const GLenum type) noexcept {
  switch (type) {
  case GL_FLOAT_MAT2:
  case GL_FLOAT_MAT2x3:
  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT3x2:
  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT3:
  case GL_FLOAT_MAT4x2:
  case GL_FLOAT_MAT4x3:
  case GL_FLOAT_MAT4:
  case GL_DOUBLE_MAT2:
  case GL_DOUBLE_MAT2x3:
  case GL_DOUBLE_MAT2x4:
  case GL_DOUBLE_MAT3x2:
  case GL_DOUBLE_MAT3:
  case GL_DOUBLE_MAT3x4:
  case GL_DOUBLE_MAT4x2:
  case GL_DOUBLE_MAT4x3:
  case GL_DOUBLE_MAT4:
    return true;

  default:
    return false;
  }
}

bool isScalarType(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_HALF_FLOAT:
  case GL_FLOAT:
  case GL_DOUBLE:
    return true;

  default:
    return false;
  }
}

const char* resolveGLType(const GLenum type) noexcept {

  switch (type) {
    /*
    // GL constants
    {
      BALLS_GL_CONSTANT(GL_TRUE);
      BALLS_GL_CONSTANT(GL_FALSE);
      BALLS_GL_CONSTANT(GL_ONE);
      BALLS_GL_CONSTANT(GL_ZERO);
    }
    // glGet() state
    {
      BALLS_GL_CONSTANT(GL_ACTIVE_TEXTURE);
      BALLS_GL_CONSTANT(GL_ALIASED_LINE_WIDTH_RANGE);
      BALLS_GL_CONSTANT(GL_ARRAY_BUFFER_BINDING);
      BALLS_GL_CONSTANT(GL_BLEND);
      BALLS_GL_CONSTANT(GL_BLEND_COLOR);
      BALLS_GL_CONSTANT(GL_BLEND_DST_ALPHA);
      BALLS_GL_CONSTANT(GL_BLEND_DST_RGB);
      BALLS_GL_CONSTANT(GL_BLEND_EQUATION_ALPHA);
      BALLS_GL_CONSTANT(GL_BLEND_SRC_ALPHA);
      BALLS_GL_CONSTANT(GL_BLEND_SRC_RGB);
      BALLS_GL_CONSTANT(GL_BLEND_EQUATION_RGB);
      BALLS_GL_CONSTANT(GL_COLOR_CLEAR_VALUE);
      BALLS_GL_CONSTANT(GL_COLOR_LOGIC_OP);
      BALLS_GL_CONSTANT(GL_COLOR_WRITEMASK);
    }
    // glClear() bits
    {
      BALLS_GL_CONSTANT(GL_COLOR_BUFFER_BIT);
      BALLS_GL_CONSTANT(GL_DEPTH_BUFFER_BIT);
      BALLS_GL_CONSTANT(GL_STENCIL_BUFFER_BIT);
    }

    // glGetString() parameters
    {
      BALLS_GL_CONSTANT(GL_VENDOR);
      BALLS_GL_CONSTANT(GL_RENDERER);
      BALLS_GL_CONSTANT(GL_VERSION);
      BALLS_GL_CONSTANT(GL_SHADING_LANGUAGE_VERSION);
      BALLS_GL_CONSTANT(GL_EXTENSIONS);
    }
    */
    {
      BALLS_GL_CONSTANT(GL_SHORT);
      BALLS_GL_CONSTANT(GL_UNSIGNED_SHORT);
      BALLS_GL_CONSTANT(GL_BYTE);
      BALLS_GL_CONSTANT(GL_UNSIGNED_BYTE);
      BALLS_GL_CONSTANT(GL_HALF_FLOAT);

      BALLS_GL_CONSTANT(GL_BOOL);
      BALLS_GL_CONSTANT(GL_BOOL_VEC2);
      BALLS_GL_CONSTANT(GL_BOOL_VEC3);
      BALLS_GL_CONSTANT(GL_BOOL_VEC4);
      BALLS_GL_CONSTANT(GL_INT);
      BALLS_GL_CONSTANT(GL_INT_VEC2);
      BALLS_GL_CONSTANT(GL_INT_VEC3);
      BALLS_GL_CONSTANT(GL_INT_VEC4);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_VEC2);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_VEC3);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_VEC4);
      BALLS_GL_CONSTANT(GL_FLOAT);
      BALLS_GL_CONSTANT(GL_FLOAT_VEC2);
      BALLS_GL_CONSTANT(GL_FLOAT_VEC3);
      BALLS_GL_CONSTANT(GL_FLOAT_VEC4);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT2);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT2x3);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT2x4);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT3x2);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT3);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT3x4);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT4x2);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT4x3);
      BALLS_GL_CONSTANT(GL_FLOAT_MAT4);
      BALLS_GL_CONSTANT(GL_DOUBLE);
      BALLS_GL_CONSTANT(GL_DOUBLE_VEC2);
      BALLS_GL_CONSTANT(GL_DOUBLE_VEC3);
      BALLS_GL_CONSTANT(GL_DOUBLE_VEC4);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT2);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT2x3);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT2x4);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT3x2);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT3);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT3x4);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT4x2);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT4x3);
      BALLS_GL_CONSTANT(GL_DOUBLE_MAT4);
      BALLS_GL_CONSTANT(GL_SAMPLER);
      BALLS_GL_CONSTANT(GL_SAMPLER_1D);
      BALLS_GL_CONSTANT(GL_SAMPLER_1D_ARRAY);
      BALLS_GL_CONSTANT(GL_SAMPLER_1D_ARRAY_SHADOW);
      BALLS_GL_CONSTANT(GL_SAMPLER_1D_SHADOW);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_1D);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_1D_ARRAY);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_1D);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_1D_ARRAY);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D_ARRAY);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D_ARRAY_SHADOW);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D_MULTISAMPLE);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D_RECT);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D_RECT_SHADOW);
      BALLS_GL_CONSTANT(GL_SAMPLER_2D_SHADOW);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_2D);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_2D_ARRAY);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_2D_MULTISAMPLE);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_2D_RECT);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_2D);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_2D_ARRAY);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_2D_RECT);
      BALLS_GL_CONSTANT(GL_SAMPLER_3D);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_3D);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_3D);
      BALLS_GL_CONSTANT(GL_SAMPLER_CUBE);
      BALLS_GL_CONSTANT(GL_SAMPLER_CUBE_MAP_ARRAY);
      BALLS_GL_CONSTANT(GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW);
      BALLS_GL_CONSTANT(GL_SAMPLER_CUBE_SHADOW);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_CUBE);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_CUBE_MAP_ARRAY);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_CUBE);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY);
      BALLS_GL_CONSTANT(GL_SAMPLER_BUFFER);
      BALLS_GL_CONSTANT(GL_INT_SAMPLER_BUFFER);
      BALLS_GL_CONSTANT(GL_UNSIGNED_INT_SAMPLER_BUFFER);
    }

  default:
    return nullptr;
  }
}

const char* resolveGLPrimitive(const GLenum type) noexcept {
  switch (type) {
    BALLS_GL_CONSTANT(GL_POINTS);
    BALLS_GL_CONSTANT(GL_LINE_STRIP);
    BALLS_GL_CONSTANT(GL_LINE_LOOP);
    BALLS_GL_CONSTANT(GL_LINES);
    BALLS_GL_CONSTANT(GL_LINE_STRIP_ADJACENCY);
    BALLS_GL_CONSTANT(GL_LINES_ADJACENCY);
    BALLS_GL_CONSTANT(GL_TRIANGLE_STRIP);
    BALLS_GL_CONSTANT(GL_TRIANGLE_FAN);
    BALLS_GL_CONSTANT(GL_TRIANGLES);
    BALLS_GL_CONSTANT(GL_TRIANGLE_STRIP_ADJACENCY);
    BALLS_GL_CONSTANT(GL_TRIANGLES_ADJACENCY);
    BALLS_GL_CONSTANT(GL_PATCHES);

  default:
    return nullptr;
  }
}

const char* resolveGLError(const GLenum error) noexcept {
  switch (error) {
    BALLS_GL_CONSTANT(GL_NO_ERROR);
    BALLS_GL_CONSTANT(GL_INVALID_ENUM);
    BALLS_GL_CONSTANT(GL_INVALID_VALUE);
    BALLS_GL_CONSTANT(GL_INVALID_OPERATION);
    BALLS_GL_CONSTANT(GL_INVALID_FRAMEBUFFER_OPERATION);
    BALLS_GL_CONSTANT(GL_OUT_OF_MEMORY);
    BALLS_GL_CONSTANT(GL_STACK_UNDERFLOW);
    BALLS_GL_CONSTANT(GL_STACK_OVERFLOW);

  default:
    return nullptr;
  }
}

QVariant getDefaultValue(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
    return false;

  case GL_INT:
    return 0i;

  case GL_UNSIGNED_INT:
    return 0u;

  case GL_FLOAT:
    return 0.0f;

  case GL_DOUBLE:
    return 0.0;

  case GL_INT_VEC2:
  case GL_FLOAT_VEC2:
  case GL_DOUBLE_VEC2:
  case GL_UNSIGNED_INT_VEC2:
  case GL_BOOL_VEC2:
    return QVector2D(0, 0);

  case GL_INT_VEC3:
  case GL_FLOAT_VEC3:
  case GL_DOUBLE_VEC3:
  case GL_UNSIGNED_INT_VEC3:
  case GL_BOOL_VEC3:
    return QVector3D(0, 0, 0);

  case GL_INT_VEC4:
  case GL_FLOAT_VEC4:
  case GL_DOUBLE_VEC4:
  case GL_UNSIGNED_INT_VEC4:
  case GL_BOOL_VEC4:
    return QVector4D(0, 0, 0, 0);

  case GL_FLOAT_MAT2:
  case GL_DOUBLE_MAT2:
  case GL_FLOAT_MAT2x3:
  case GL_FLOAT_MAT3x2:
  case GL_DOUBLE_MAT2x3:
  case GL_DOUBLE_MAT3x2:
  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT4x2:
  case GL_DOUBLE_MAT2x4:
  case GL_DOUBLE_MAT4x2:
  case GL_FLOAT_MAT3:
  case GL_DOUBLE_MAT3:
  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT4x3:
  case GL_DOUBLE_MAT3x4:
  case GL_DOUBLE_MAT4x3:
  case GL_FLOAT_MAT4:
  case GL_DOUBLE_MAT4:
    return QMatrix4x4();

  default:
    qCDebug(logs::gl::Type).nospace().noquote() << "No Qt type to represent GLSL type "
    << resolveGLType(type) << " (" << QString(type).toInt(nullptr, 16) << ')';
    return QVariant();
  }
}

QVariant asGlComponent(const GLenum type, const QVariant& var) noexcept {
  switch (util::getGlComponentType(type)) {
  case GL_BOOL:
    return var.toBool();

  case GL_FLOAT:
    return var.toFloat();

  case GL_DOUBLE:
    return var.toDouble();

  case GL_INT:
    return var.toInt();

  case GL_UNSIGNED_INT:
    return var.toUInt();

  default:
    return var;
  }
}

QJsonValue toJsonValue(const GLenum gl, const QVariant& v) noexcept {
  using namespace constants;

  switch (util::getNumComponents(gl)) {
  case 1: {
    return QJsonValue::fromVariant(v);
  }

  case 2: {
    QVector2D v2 = v.value<QVector2D>();

    return QJsonObject {
      {json::X, QJsonValue::fromVariant(asGlComponent(gl, v2.x()))},
      {json::Y, QJsonValue::fromVariant(asGlComponent(gl, v2.y()))}
    };
  }

  case 3: {
    QVector3D v3 = v.value<QVector3D>();

    return QJsonObject {
      {json::X, QJsonValue::fromVariant(asGlComponent(gl, v3.x()))},
      {json::Y, QJsonValue::fromVariant(asGlComponent(gl, v3.y()))},
      {json::Z, QJsonValue::fromVariant(asGlComponent(gl, v3.z()))}
    };
  }

  case 4: {
    QVector4D v4 = v.value<QVector4D>();

    return QJsonObject {
      {json::X, QJsonValue::fromVariant(asGlComponent(gl, v4.x()))},
      {json::Y, QJsonValue::fromVariant(asGlComponent(gl, v4.y()))},
      {json::Z, QJsonValue::fromVariant(asGlComponent(gl, v4.z()))},
      {json::W, QJsonValue::fromVariant(asGlComponent(gl, v4.w()))}
    };
  }

  default:
    return QJsonValue();
  }
}

template int mapRange(int, int, int, int, int) noexcept;
template float mapRange(float, float, float, float, float) noexcept;

float fastInvSqrt(float number) noexcept
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * (long*)& y;                          // evil floating point bit level hacking
  i  = 0x5f3759df - (i >> 1);                 // what the fuck?
  y  = * (float*)& i;
  y  = y * (threehalfs - (x2* y * y));        // 1st iteration
  //      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  return y;
}

}
}
