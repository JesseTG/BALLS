#ifndef OPENGLINFO_HPP
#define OPENGLINFO_HPP

#include "ui_OpenGLInfo.h"

class OpenGLInfo : public QDockWidget {
  Q_OBJECT

public:
  explicit OpenGLInfo(QWidget *parent = 0);

private:
  Ui::OpenGLInfo ui;
};

#endif // OPENGLINFO_HPP
