#include "renderarea.hpp"
#include "common.hpp"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget{parent} { 
  resize(common::RA_W, common::RA_H); 
}

/// \brief overwrite the paintEvent to draw graph
/// \param get QPaintEvent type event
/// \return none
void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);

  painter.drawLine(80, 100, 950, 750);
  QPoint const a(10, 10), b(100, 400);
  painter.drawLine(a, b);
  painter.drawRect(10, 10, 100, 400);
  painter.drawRect(20, 20, 400, 300);

  painter.setPen(QPen(Qt::green, 5));
  painter.setBrush(Qt::red);
  painter.drawEllipse(50, 150, 400, 200);
}
