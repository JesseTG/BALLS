#include "precompiled.hpp"
#include "ui/BallsCanvas.hpp"

#include <QtCore/QDateTime>

#include "Constants.hpp"
#include "util/Util.hpp"
#include "shader/ShaderUniform.hpp"
#include "shader/ShaderInputs.hpp"

namespace balls {
using namespace shader;
using namespace shader::uniform;

template <class RandomGenT>
UniformFunction _getRandomGeneratorUniform() {
  using Constants::RANDOM;

  return [](const GLenum type) -> QVariant {
    static RandomGenT rand;

    switch (type) {
    case GL_DOUBLE:
    case GL_FLOAT:
      return rand(RANDOM);
    case GL_DOUBLE_VEC2:
    case GL_FLOAT_VEC2:
      return QVector2D(rand(RANDOM), rand(RANDOM));
    case GL_DOUBLE_VEC3:
    case GL_FLOAT_VEC3:
      return QVector3D(rand(RANDOM), rand(RANDOM), rand(RANDOM));
    case GL_DOUBLE_VEC4:
    case GL_FLOAT_VEC4:
      return QVector4D(rand(RANDOM), rand(RANDOM), rand(RANDOM), rand(RANDOM));
    default:
      return 0;
    }
  };
}

void BallsCanvas::_initUniforms() {
  auto mf = [this](QMatrix4x4& m) {
    return [this, &m](const GLenum type) -> QVariant {
      switch (type) {
      case GL_DOUBLE_MAT4:
      case GL_FLOAT_MAT4:
        return m;
      default:
        return 0;
      }
    };
  };

  _builtInUniforms[uniform::TIME] = UniformInfo([](const GLenum type) -> QVariant {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    switch (type) {
    case GL_FLOAT:
      return static_cast<GLfloat>(now);
    case GL_INT:
      return static_cast<GLint>(now);
    case GL_UNSIGNED_INT:
      return static_cast<GLuint>(now);
    case GL_DOUBLE:
      return static_cast<GLdouble>(now);
    default:
      return 0;
    }
  }, UpdateFrequency::EveryFrame);


  _builtInUniforms[uniform::RANDOM_UNIFORM] =
   UniformInfo(_getRandomGeneratorUniform<std::uniform_real_distribution<float>>(),
               UpdateFrequency::EveryFrame);

  _builtInUniforms[uniform::RANDOM_NORMAL] =
   UniformInfo(_getRandomGeneratorUniform<std::normal_distribution<float>>(),
               UpdateFrequency::EveryFrame);

  _builtInUniforms[uniform::MATRIX] =
   UniformInfo(mf(_combined), UpdateFrequency::EveryFrame);
  _builtInUniforms[uniform::MODEL] =
   UniformInfo(mf(_model), UpdateFrequency::EveryFrame);
  _builtInUniforms[uniform::VIEW] =
   UniformInfo(mf(_view), UpdateFrequency::EveryFrame);
  _builtInUniforms[uniform::PROJECTION] =
   UniformInfo(mf(_projection), UpdateFrequency::EveryFrame);

  _builtInUniforms[uniform::MODEL_VIEW] =
   UniformInfo([this](const GLenum type) -> QVariant {
     switch (type) {
     case GL_DOUBLE_MAT4:
     case GL_FLOAT_MAT4:
       return _view * _model;
     default:
       return 0;
     }
   }, UpdateFrequency::EveryFrame);

  _builtInUniforms[uniform::MOUSE_COORDS] =
   UniformInfo([this](const GLenum type) -> QVariant {
     switch (type) {
     case GL_DOUBLE_VEC2:
     case GL_FLOAT_VEC2:
     case GL_INT_VEC2:
     case GL_UNSIGNED_INT_VEC2:
       return QVector2D(_lastMousePos.x(), _lastMousePos.y());
     case GL_DOUBLE_VEC3:
     case GL_FLOAT_VEC3:
     case GL_INT_VEC3:
     case GL_UNSIGNED_INT_VEC3:
       return QVector3D(_lastMousePos.x(), _lastMousePos.y(), 0);
     case GL_DOUBLE_VEC4:
     case GL_FLOAT_VEC4:
     case GL_INT_VEC4:
     case GL_UNSIGNED_INT_VEC4:
       return QVector4D(_lastMousePos.x(), _lastMousePos.y(), 0, 0);
     default:
       return 0;
     }
   }, UpdateFrequency::EveryFrame);
}
}
