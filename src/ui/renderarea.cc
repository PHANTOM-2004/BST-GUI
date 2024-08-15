#include "renderarea.hpp"
#include <QPainter>

RenderArea::RenderArea (QWidget *parent) : QWidget{ parent } {
  resize(1000, 800);
}



void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);

  painter.drawLine(80, 100, 950, 750);
  QPoint const a(10, 10), b(100, 400);
  painter.drawLine(a, b);
  painter.drawRect(10, 10, 100, 400);

  painter.setPen(QPen(Qt::green, 5));
  painter.setBrush(Qt::red);
  painter.drawEllipse(50, 150, 400, 200);
}
