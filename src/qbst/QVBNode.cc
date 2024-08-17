
#include "qbst/QVBNode.hpp"
#include "common.hpp"

using qbst::QVBNode;

void QVBNode::render(QPainter *painter, int const radius) const{
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
  int const l = str().length();

  // set font properties
  QPoint const start = {position().x() - l / 2, position().y()};
  auto f = painter->font();
  f.setPointSize(common::FONT_SIZE);

  painter->drawText(start, str());
}
