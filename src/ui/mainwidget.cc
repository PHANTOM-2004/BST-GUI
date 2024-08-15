#include "mainwidget.hpp"
#include "common.hpp"
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget{parent} {
  // set render area
  initRenderArea();
  // set scroll area
  initScrollArea();

  setObjectName("centralwidget");
  resize(common::MW_W, common::MW_H);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(scrollArea);

  setLayout(layout);
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
