#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include "renderarea.hpp"
#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>

class MainWidget : public QWidget {
  Q_OBJECT
public:
  explicit MainWidget(QWidget *parent = nullptr);

private:
  QScrollArea *scrollArea;
  RenderArea *renderArea;

  QLineEdit *insertInput;
  QLineEdit *deleteInput;
  QLineEdit *findInput;

  QPushButton* insertButton;
  QPushButton* deleteButton;
  QPushButton* findButton;

  void initScrollArea();
  void initRenderArea();
  void on_insert_button_clicked();
  void on_delete_button_clicked();

signals:
};

#endif // MAINWIDGET_HPP
