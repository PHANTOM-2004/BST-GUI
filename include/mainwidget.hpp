#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "renderarea.hpp"
#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>

class MainWidget : public QWidget {
  Q_OBJECT
public:
  explicit MainWidget(QWidget *parent = nullptr);

private:
  QScrollArea *scrollArea;
  RenderArea *renderArea;

  QLineEdit *insertInput;
  QLineEdit *deleteInput;

  void initScrollArea();
  void initRenderArea();
signals:
};

#endif // MAINWIDGET_HPP
