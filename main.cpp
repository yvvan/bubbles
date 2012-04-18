#include <QtGui/QApplication>
#include "glwidget.h"

static const int x = 50;
static const int y = 50;
static const int width = 500;
static const int height = 500;

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  QApplication a(argc, argv);
  GLWidget w(QRect(x,y,width,height), 500, 10, 50, 20.0);
  w.show();

  return a.exec();
}
