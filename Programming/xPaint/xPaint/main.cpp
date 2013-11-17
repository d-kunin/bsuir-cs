#include "xpaintwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  xPaintWindow w;
  w.show();

  return a.exec();
}
