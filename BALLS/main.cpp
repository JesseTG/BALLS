#include "ui/BallsWindow.hpp"

#include <QApplication>
#include <QtGlobal>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  balls::BallsWindow w;
  w.show();

  return a.exec();
}
