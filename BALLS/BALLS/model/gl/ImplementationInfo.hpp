#ifndef IMPLEMENTATIONINFO_HPP
#define IMPLEMENTATIONINFO_HPP

#include <QObject>

namespace balls {

class OpenGLPointers;

class ImplementationInfo : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString glslVersion MEMBER m_glslVersion CONSTANT FINAL)
  Q_PROPERTY(QString renderer MEMBER m_renderer CONSTANT FINAL)
  Q_PROPERTY(QString vendor MEMBER m_vendor CONSTANT FINAL)
  Q_PROPERTY(QString version MEMBER m_version CONSTANT FINAL)
public:
  ImplementationInfo(OpenGLPointers&, QObject* = nullptr);

private /* fields */:
  QString m_glslVersion;
  QString m_renderer;
  QString m_vendor;
  QString m_version;
  // TODO: Get the extensions (glGet number of extensions, then glGetString them)
};
}

#endif // IMPLEMENTATIONINFO_HPP
