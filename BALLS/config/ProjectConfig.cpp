#include "precompiled.hpp"
#include "config/ProjectConfig.hpp"
#include "Constants.hpp"

#include "exception/FileException.hpp"
#include "exception/JsonException.hpp"
#include "shader/ShaderUniform.hpp"
#include "util/Logging.hpp"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonValue>

namespace balls {
namespace config {

void saveToFile(const ProjectConfig& project, const QString& path,
                const QObject* unis) {
  using namespace constants;
  using std::get;

  QFile file(path);
  bool opened = file.open(QFile::Text | QFile::WriteOnly);

  if (Q_UNLIKELY(!opened)) {
    throw FileException(file);
  }

  QJsonDocument out;
  QJsonObject balls;
  {
    QJsonObject meta {
      {json::VERSION, constants::meta::VERSION_MAJOR},
    };
    balls.insert(json::META, meta);

    QJsonObject shaders {
      {json::VERT, project.vertexShader},
      {json::FRAG, project.fragmentShader},
    };
    balls.insert(json::SHADERS, shaders);

    QJsonObject uniforms;
    {
      for (const auto& u : project.uniforms) {

//        uniforms.insert(u.first, util::toJsonValue(uniform->glType(), u.second));
      }
    }
    balls.insert(json::UNIFORMS, uniforms);


    QJsonObject gl {
      {json::GL_MAJOR, project.glMajor},
      {json::GL_MINOR, project.glMinor},
    };
    balls.insert(json::GL, gl);
  }
  out.setObject(balls);

  QByteArray o = out.toJson();

  auto wrote = file.write(o);
  bool flushed = file.flush();

  if (Q_UNLIKELY(wrote == -1 || !flushed)) {
    throw FileException(file);
  }

  qCDebug(logs::app::project::Name) << "Saved project" << path;
}

ProjectConfig loadFromFile(const QString& path) {
  using namespace constants;
  ProjectConfig p;
  QFile file(path);

  bool opened = file.open(QFile::Text | QFile::ReadOnly);

  if (Q_UNLIKELY(!opened)) {
    throw FileException(file);
  }

  QJsonParseError error;
  QJsonDocument in = QJsonDocument::fromJson(file.readAll(), &error);

  if (error.error != QJsonParseError::NoError) {
    throw JsonException(error);
  }

  QJsonObject root = in.object();

  QJsonObject gl = root[json::GL].toObject();
  {
    p.glMajor = gl[json::GL_MAJOR].toInt();
    p.glMajor = gl[json::GL_MINOR].toInt();
  }

  QJsonObject meta = root[json::META].toObject();
  {
    p.major = meta[json::VERSION].toInt();
  }

  QJsonObject shaders = root[json::SHADERS].toObject();
  {
    p.vertexShader = shaders[json::VERT].toString();
    p.fragmentShader = shaders[json::FRAG].toString();
  }

  QJsonObject uniforms = root[json::UNIFORMS].toObject();
  {
    for (const QString& u : uniforms.keys()) {
      // p.uniforms[u] = util::convert<QJsonValue, QVariant>::to(uniforms[u]);
      // TODO: Write a dedicated QJSonValue -> QVariant converter
    }
  }

  return p;
}
}
}
