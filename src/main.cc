/// \file main.cc
/// \brief The entry of the program
///

#include "bstmainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  BstMainWindow w;
  w.show();
  return a.exec();
}
