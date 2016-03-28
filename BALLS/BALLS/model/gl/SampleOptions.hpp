#ifndef SAMPLEOPTIONS_HPP
#define SAMPLEOPTIONS_HPP

#include <QObject>

namespace balls {

class SampleOptions : public QObject {
  Q_OBJECT

  // clang-format off
  Q_PROPERTY(float sampleCoverage MEMBER m_sampleCoverage WRITE setSampleCoverage FINAL)
  Q_PROPERTY(bool invertSampleCoverage MEMBER m_invertSampleCoverage WRITE setInvertSampleCoverage FINAL)
  // clang-format on

public:
  explicit SampleOptions(QObject *parent = 0);

private /* setters */:
private /* fields */:
  float m_sampleCoverage;
  bool m_invertSampleCoverage;
};
}

#endif // SAMPLEOPTIONS_HPP
