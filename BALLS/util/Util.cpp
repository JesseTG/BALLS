#include "precompiled.hpp"
#include "util/Util.hpp"

namespace balls {
namespace util {

QDebug& operator<<(QDebug& out, const QOpenGLShader::ShaderType& type) {
  switch (type) {
  case QOpenGLShader::Vertex:
    return out << "Vertex";

  case QOpenGLShader::Fragment:
    return out << "Fragment";

  case QOpenGLShader::Geometry:
    return out << "Geometry";

  case QOpenGLShader::TessellationControl:
    return out << "TessellationControl";

  case QOpenGLShader::TessellationEvaluation:
    return out << "TessellationEvaluation";

  case QOpenGLShader::Compute:
    return out << "Compute";

  default:
    Q_UNREACHABLE();
    return out << "Unknown";
  }
}

uint8_t getNumComponents(const GLenum type) Q_DECL_NOTHROW {
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
    Q_UNREACHABLE();
    return 0;
  }
}

Type getComponentType(const GLenum type) Q_DECL_NOTHROW {
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
    Q_UNREACHABLE();
    #ifdef DEBUG
    qDebug() << "Warning: Cannot get component type of OpenGL enum" << type;
    #endif
    return Type::UnknownType;
  }
}

bool isVectorType(const GLenum type) Q_DECL_NOTHROW {
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

bool isMatrixType(const GLenum type) Q_DECL_NOTHROW {
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

bool isScalarType(const GLenum type) Q_DECL_NOTHROW {
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
}
}
