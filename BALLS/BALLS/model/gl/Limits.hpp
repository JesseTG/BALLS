#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <QObject>

namespace balls {

class Limits : public QObject {
  Q_OBJECT
public:
  explicit Limits(QObject *parent = 0);

signals:

public slots:
};
}

Q_DECLARE_METATYPE(balls::Limits*)

#endif // LIMITS_HPP
