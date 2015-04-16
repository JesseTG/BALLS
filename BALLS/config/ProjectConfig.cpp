#include "precompiled.hpp"
#include "config/ProjectConfig.hpp"
#include "Constants.hpp"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QXmlStreamWriter>

namespace balls {
namespace config {

void saveToFile(const ProjectConfig& project, const QString& path) {
  using namespace Constants;
  QFile file(path);
  QXmlStreamWriter out(&file);

  out.writeStartDocument();
  {
    out.writeStartElement(BALLS_ELEMENT);
    {
      out.writeAttribute(VERSION_ATT, QString::number(VERSION_MAJOR));
      out.writeAttribute(GL_MAJOR_ATT, QString::number(project.glMajor));
      out.writeAttribute(GL_MINOR_ATT, QString::number(project.glMinor));

      out.writeStartElement(SHADERS_ELEMENT);
      {
        out.writeTextElement(VERT_ELEMENT, project.vertexShader);
        out.writeTextElement(FRAG_ELEMENT, project.fragmentShader);
      }
      out.writeEndElement();

      out.writeStartDocument();
    }
    out.writeEndElement();
  }
  out.writeEndDocument();

  file.flush();
}

ProjectConfig loadFromFile(const QString& path) {
  ProjectConfig p;
  return ProjectConfig();
}
}
}
