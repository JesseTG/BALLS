#ifndef HINTS_HPP
#define HINTS_HPP

#include <QObject>

namespace balls {

class Hints : public QObject {
  Q_OBJECT

  Q_ENUMS(HintMode)

  // clang-format off
  Q_PROPERTY(HintMode fragmentDerivative READ fragmentDerivative WRITE setFragmentDerivative STORED false FINAL)
  Q_PROPERTY(HintMode lineSmooth READ lineSmooth WRITE setLineSmooth STORED false FINAL)
  Q_PROPERTY(HintMode polygonSmooth READ polygonSmooth WRITE setPolygonSmooth STORED false FINAL)
  Q_PROPERTY(HintMode textureCompression READ textureCompression WRITE setTextureCompression STORED false FINAL)
  // clang-format on

public /* enums */:
  enum HintMode {
    Fastest = GL_FASTEST,
    Nicest = GL_NICEST,
    DontCare = GL_DONT_CARE,
  };

public:
  explicit Hints(QObject *parent = 0);

signals:

public slots:
};
}

#endif // HINTS_HPP
