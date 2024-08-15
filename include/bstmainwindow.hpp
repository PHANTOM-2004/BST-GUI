#ifndef BSTMAINWINDOW_HPP
#define BSTMAINWINDOW_HPP

#include "renderarea.hpp"
#include <QMainWindow>
#include <QScrollArea>

class BstMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit BstMainWindow (QWidget *parent = nullptr);

private:
  QScrollArea *scrollArea;
  RenderArea *renderArea;
  QWidget *centralwidget;

  void showSoftwareInfo(); 
  void showBuildInfo(); 

signals:
};

#endif // BSTMAINWINDOW_HPP
