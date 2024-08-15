#include "bstmainwidget.hpp"
#include "./ui_bstmainwidget.h"
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

BSTMainWidget::BSTMainWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::BSTMainWidget) {
  ui->setupUi(this);
  scrollArea = new QScrollArea(this);
  scrollArea->resize(200, 100);

  // set render area
  renderArea = new RenderArea(this);
  // set child widget
  scrollArea->setWidget(renderArea);

  scrollArea->setWidgetResizable(false);
  scrollArea->horizontalScrollBar();
  scrollArea->verticalScrollBar();

  // label
  QLabel *title = new QLabel(this);
  title->setText(tr("Son Of The Bitch"));

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(title);
  layout->addWidget(scrollArea);

  centralwidget = new QWidget(this);
  centralwidget->setObjectName("centralwidget");
  centralwidget->setLayout(layout);
}

BSTMainWidget::~BSTMainWidget() { delete ui; }
