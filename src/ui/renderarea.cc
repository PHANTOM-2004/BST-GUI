/// \file
/// \brief implementation of RenderArea
///

#include "renderarea.hpp"
#include "common.hpp"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget{parent}{
  resize(common::RA_W, common::RA_H);
  
  this->tree = new QBST;

  tree->insert(QBST_data("50"));
  tree->insert(QBST_data("120"));
  tree->insert(QBST_data("200"));
  tree->insert(QBST_data("10"));
  tree->insert(QBST_data("96"));
  tree->insert(QBST_data("85"));
  tree->insert(QBST_data("59"));
  tree->insert(QBST_data("20"));
  tree->insert(QBST_data("0"));
  tree->insert(QBST_data("350"));
  tree->insert(QBST_data("90"));
  tree->insert(QBST_data("299"));
  tree->insert(QBST_data("450"));
  tree->insert(QBST_data("450"));
  tree->insert(QBST_data("267"));
  tree->insert(QBST_data("129"));
  tree->insert(QBST_data("500"));

  tree->set_position({500, 50});
  tree->set_color();
}

/// \brief overwrite the paintEvent to draw graph
/// \param event get QPaintEvent type event
void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
  //
  // painter.drawLine(80, 100, 950, 750);
  // QPoint const a(10, 10), b(100, 400);
  // painter.drawLine(a, b);
  // painter.drawRect(10, 10, 100, 400);
  // painter.drawRect(20, 20, 400, 300);
  //
  // painter.setPen(QPen(Qt::red, 5));
  // painter.setBrush(Qt::blue);
  // painter.drawEllipse(50, 150, 400, 200);
  //
  // painter.drawEllipse({500, 500}, 40, 40);
  //
  // QFont font = painter.font();
  // font.setPointSize(common::FONT_SIZE);
  // painter.setFont(font);
  //
  // painter.drawText(50 + 400 / 2, 150 + 200 / 2, "Hell World!");

  tree->render({1000, 10}, &painter);
}
