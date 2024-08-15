#include "mainwidget.hpp"
#include "common.hpp"
#include <QDebug>
#include <QHBoxLayout>
#include <QLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>

MainWidget::MainWidget(QWidget *parent) : QWidget{parent} {
  qDebug() << "Initializing MainWidget";
  // set render area
  initRenderArea();
  // set scroll area
  initScrollArea();

  setObjectName("centralwidget");
  resize(common::MW_W, common::MW_H);
  
  // init insert/find/delete button
  insertInput = new QLineEdit(this);
  deleteInput = new QLineEdit(this);
  findInput = new QLineEdit(this);
  insertButton = new QPushButton("Insert", this);
  deleteButton = new QPushButton("Delete", this);
  findButton = new QPushButton("Find", this);

  // set horizontal layout of insert/find/delete
  auto *edit_layout = new QHBoxLayout;
  edit_layout->addWidget(insertInput);
  edit_layout->addWidget(insertButton);
  edit_layout->addWidget(deleteInput);
  edit_layout->addWidget(deleteButton);
  edit_layout->addWidget(findInput);
  edit_layout->addWidget(findButton);

  // set layout of scrollArea
  auto *scroll_layout = new QHBoxLayout;
  scroll_layout->addWidget(scrollArea);

  // hlayout + hlayout => vlayout
  auto *layout = new QVBoxLayout(this);
  layout->addLayout(scroll_layout);
  layout->addLayout(edit_layout);
  
  //set widget layout
  setLayout(layout);
}

void MainWidget::on_insert_button_clicked() { qDebug() << "insert clicked"; }

void MainWidget::on_delete_button_clicked() { qDebug() << "delete clicked"; }

void MainWidget::initRenderArea() { renderArea = new RenderArea(this); }

void MainWidget::initScrollArea() {
  // set scroll area size
  scrollArea = new QScrollArea(this);
  scrollArea->resize(common::SA_W, common::SA_H);
  // set child widget
  scrollArea->setWidget(renderArea);
  scrollArea->setWidgetResizable(false);
  scrollArea->horizontalScrollBar();
  scrollArea->verticalScrollBar();
}
