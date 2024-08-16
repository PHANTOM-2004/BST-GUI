/// \file
/// \brief implementation of MainWidget
///

#include "mainwidget.hpp"
#include "common.hpp"
#include <QDebug>
#include <QHBoxLayout>
#include <QLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget{parent} {
  qDebug() << "Initializing MainWidget";
  //  set render area
  initRenderArea();
  //  set scroll area
  initScrollArea();

  setObjectName("centralwidget");
  resize(common::MW_W, common::MW_H);

  //  init insert/find/delete button
  static QString const tips = "Enter string(length < 20)";
  insertInput = new QLineEdit(this);
  insertInput->setPlaceholderText(tips);
  insertButton = new QPushButton("Insert", this);
  connect(insertButton, &QPushButton::clicked, this,
          &MainWidget::on_insert_button_clicked);
  deleteInput = new QLineEdit(this);
  deleteInput->setPlaceholderText(tips);
  deleteButton = new QPushButton("Delete", this);
  connect(deleteButton, &QPushButton::clicked, this,
          &MainWidget::on_delete_button_clicked);
  findInput = new QLineEdit(this);
  findInput->setPlaceholderText(tips);
  findButton = new QPushButton("Find", this);
  connect(findButton, &QPushButton::clicked, this,
          &MainWidget::on_find_button_clicked);

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

  // set widget layout
  setLayout(layout);
}

void MainWidget::on_insert_button_clicked() {
  qDebug() << "insert clicked";
  qDebug() << insertInput->text();
}

void MainWidget::on_delete_button_clicked() { qDebug() << "delete clicked"; }

void MainWidget::on_find_button_clicked() { qDebug() << "find clicked"; }

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
