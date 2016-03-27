#ifndef IMPLEMENTATIONINFO_HPP
#define IMPLEMENTATIONINFO_HPP

#include <QObject>

namespace balls {

class ImplementationInfo : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString glslVersion READ glslVersion CONSTANT FINAL)
  Q_PROPERTY(QString renderer READ renderer CONSTANT FINAL)
  Q_PROPERTY(QString vendor READ vendor CONSTANT FINAL)
  Q_PROPERTY(QString version READ version CONSTANT FINAL)
public:
  ImplementationInfo();

signals:

public slots:
};
}

#endif // IMPLEMENTATIONINFO_HPP
