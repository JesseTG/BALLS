#ifndef UNIFORMDOCK_HPP
#define UNIFORMDOCK_HPP

#include <string>
#include <unordered_map>

#include <QtGui/QIcon>
#include <QtGui/QOpenGLContext>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QWidget>

#include "shader/ShaderUniform.hpp"

namespace balls {

struct UniformInfo;

class UniformWidget : public QWidget {
  Q_OBJECT
  Q_ENUMS(UserUniformType)
public:
  UniformWidget(QWidget* parent = nullptr);
  virtual ~UniformWidget();
  
signals:
  void uniformValueChanged(const QString&, const QVariant&);
public slots:
  void addUniforms(const balls::shader::UniformMap&);
  void removeUniforms(const QStringList&);
private slots:
  void _boolChanged(const bool);
  void _intChanged(const int);
  void _floatChanged(const float);
  void _uintChanged(const unsigned int);
  void _doubleChanged(const double);

private:
  Q_DISABLE_COPY(UniformWidget)
  QIcon _colorPickerIcon;
};
}
#endif // UNIFORMDOCK_HPP
