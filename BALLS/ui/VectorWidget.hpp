#ifndef VECTORWIDGET_HPP
#define VECTORWIDGET_HPP

#include <cstdint>
#include <vector>

#include <QtCore/QVariant>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

namespace balls {
using std::size_t;
using std::uint8_t;
using std::vector;
using Type = QMetaType::Type;

Q_CONSTEXPR double DOUBLE_STEP = .01;
Q_CONSTEXPR int INT_STEP = 1;
Q_CONSTEXPR int PRECISION = 4;

using IntLimits = std::numeric_limits<int>;
using FloatLimits = std::numeric_limits<float>;

class VectorWidget : public QWidget {
  Q_OBJECT

public:
  explicit VectorWidget(const GLenum type, QWidget* parent = 0);
  ~VectorWidget();
signals:
  void valueChanged(const QString&, const QVariant&);
public slots:
  void setValue(const QVector2D&);
  void setValue(const QVector3D&);
  void setValue(const QVector4D&);
  void setValue(const QVariant&);
private slots:
  void _updateValue(const double);
  void _updateValue(const int i) { _updateValue(static_cast<double>(i)); }
  void _updateValue(const bool b) { _updateValue(b ? 1.0 : 0.0); }

public /* getters */:
  GLenum getType() const Q_DECL_NOEXCEPT { return _glType; }
  int8_t getSize() const Q_DECL_NOEXCEPT { return _size; }
  QVector2D getVector2D() const Q_DECL_NOEXCEPT { return _getVector<QVector2D, 2>(); }
  QVector3D getVector3D() const Q_DECL_NOEXCEPT { return _getVector<QVector3D, 3>(); }
  QVector4D getVector4D() const Q_DECL_NOEXCEPT { return _getVector<QVector4D, 4>(); }
  QVariant getVector() const Q_DECL_NOEXCEPT;

private:
  GLenum _glType;
  GLenum _qType;
  int8_t _size;
  vector<QWidget*> _values;
  QVector2D _v2;
  QVector3D _v3;
  QVector4D _v4;

  template <class VecT, size_t N>
  VecT _getVector() const Q_DECL_NOEXCEPT {
    VecT vec;

    switch (_qType) {
    case Type::Bool: {
      for (size_t i = 0; i < N; ++i) {
        QCheckBox* check = static_cast<QCheckBox*>(this->_values[i]);
        Q_ASSERT(check->inherits("QCheckBox"));
        vec[i] = check->isChecked() ? 1.0 : 0.0;
      }

      break;
    }

    case Type::UInt:
    case Type::Int: {
      for (size_t i = 0; i < N; ++i) {
        QSpinBox* spin = static_cast<QSpinBox*>(this->_values[i]);
        Q_ASSERT(spin->inherits("QSpinBox"));
        vec[i] = spin->value();
      }

      break;
    }

    case Type::Float:
    case Type::Double: {
      for (size_t i = 0; i < N; ++i) {
        QDoubleSpinBox* spin = static_cast<QDoubleSpinBox*>(this->_values[i]);
        Q_ASSERT(spin->inherits("QDoubleSpinBox"));
        vec[i] = spin->value();
      }

      break;
    }

    default:
      Q_UNREACHABLE();
    }

    return vec;
  }
};
}

#endif // VECTORWIDGET_HPP
