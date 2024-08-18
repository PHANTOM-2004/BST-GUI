/// \file
/// \brief implementation of MainWidget
///

#include "mainwidget.hpp"
#include "common.hpp"
#include "renderarea.hpp"
#include <QDebug>
#include <QHBoxLayout>
#include <QLayout>
#include <QScrollBar>
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
  static QString const tips =
      QString("Enter string(length < %1)").arg(common::MAX_INPUT_LEN);
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

  connect(renderArea, &RenderArea::center_on_target, this,
          &MainWidget::center_scroll_on_target);

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
  this->renderArea->update_handler(RenderArea::UPDATE_INSERT,
                                   insertInput->text());
}

void MainWidget::on_delete_button_clicked() {
  qDebug() << "delete clicked";
  qDebug() << deleteInput->text();
  this->renderArea->update_handler(RenderArea::UPDATE_DELETE,
                                   deleteInput->text());
}

void MainWidget::on_find_button_clicked() {
  qDebug() << "find clicked";
  qDebug() << findInput->text();
  this->renderArea->update_handler(RenderArea::UPDATE_SEARCH,
                                   findInput->text());
}

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

void MainWidget::center_scroll_on_target(QPoint const &target) {
  // center the scroll bar on target

  auto const view_size = scrollArea->viewport()->size();
  auto const widget_size = scrollArea->widget()->size();

  int x_off = target.x() - view_size.width() / 2;
  int y_off = target.y() - view_size.height() / 2;

  x_off = std::max(0, std::min(x_off, widget_size.width() - view_size.width()));
  y_off =
      std::max(0, std::min(y_off, widget_size.height() - view_size.height()));

  scrollArea->horizontalScrollBar()->setValue(x_off);
  scrollArea->verticalScrollBar()->setValue(y_off);
}
