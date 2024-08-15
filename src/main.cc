#include "bstmainwidget.hpp"

#include <QApplication>

int
main (int argc, char *argv[])
{
  QApplication a (argc, argv);
  BSTMainWidget w;
  w.show ();
  return a.exec ();
}
