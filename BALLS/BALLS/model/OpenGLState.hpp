#ifndef OPENGLSTATE_HPP
#define OPENGLSTATE_HPP

#include <QObject>

namespace balls {

class OpenGLState : public QObject
{
  Q_OBJECT
public:
  explicit OpenGLState(QObject *parent = 0);

signals:

public slots:
};
}

#endif // OPENGLSTATE_HPP
