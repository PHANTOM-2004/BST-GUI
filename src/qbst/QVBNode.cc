
#include "qbst/QVBNode.hpp"
#include "common.hpp"
#include <QDebug>
#include <qfontmetrics.h>

using qbst::QVBNode;

void QVBNode::render(QPainter *painter, int const radius) const {
  Q_ASSERT(painter);
  // render hints
  painter->setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);

  // set the color
  painter->setPen(QPen(get_eg_color(), common::LINE_WIDTH));
  painter->setBrush(get_bg_color());

  // draw circle
  painter->drawEllipse(position(), radius, radius);

  // draw text
  // set font properties
  painter->setPen(QPen(FONT_COLOR, common::LINE_WIDTH));

  QPoint const start = {position().x(), position().y()};
  auto f = painter->font();
  f.setPointSize(common::FONT_SIZE);
  painter->setFont(f);

  QFontMetrics const fmetric(f);

  // Calculate bounding rectangle for the text
  QRect textRect(0, 0, 2 * radius,
                 2 * radius); // Assuming the text fits inside the circle

  // Move the rectangle so it's
  // centered at the circle's center
  textRect.moveCenter(
      position() +
      QPoint(0, -fmetric.xHeight())); // Draw the text aligned to the
                                      // center of the rectangle
  Qt::AlignmentFlag alignment = Qt::AlignCenter;
  painter->drawText(textRect, alignment, str());
}
