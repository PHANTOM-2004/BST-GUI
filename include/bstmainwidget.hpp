#ifndef BSTMAINWIDGET_HPP
#define BSTMAINWIDGET_HPP

#include "renderarea.hpp"
#include <QScrollArea>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class BSTMainWidget;
}
QT_END_NAMESPACE

class BSTMainWidget : public QWidget {
  Q_OBJECT

public:
  BSTMainWidget(QWidget *parent = nullptr);
  ~BSTMainWidget();

private:
  Ui::BSTMainWidget *ui;
  QScrollArea *scrollArea;
  RenderArea *renderArea;
  QWidget *centralwidget;
  QAction openAction;
};
#endif // BSTMAINWIDGET_HPP
