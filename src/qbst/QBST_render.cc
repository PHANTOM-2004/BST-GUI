#include "qbst/QBST.hpp"
#include <qassert.h>
#include <qpainter.h>

using qbst::QBST;
using qbst::QBST_data;
using qbst::QBST_node;

void QBST::set_painter(QPainter *painter) const { this->painter = painter; }

int QBST::get_leftmost_rpos(int const h) const {
  Q_ASSERT(h < 10);

  int res = 0;

  // for level h, we add 2 ^ h * base_width offset
  int H = h;
  QBST_node const *p = root();
  while (p) {
    res -= (1 << H) * base_width;
    p = p->left();
    H--;
  }

  Q_ASSERT(res <= 0);
  return res;
}

void QBST::get_next_center(QPoint const &center, QPoint &lcenter,
                           QPoint &rcenter, int const h, QBST_node const *rt) {
  int step_x = base_width * (1 << h), step_y = base_height;

  if ((!rt->_left && rt->_right) || (!rt->_right && rt->_left)) {
    step_x = base_width;
  }

  lcenter = {center.x() - step_x, center.y() + step_y};
  rcenter = {center.x() + step_x, center.y() + step_y};
}

int QBST::get_width() {
  leftmost = 0, rightmost = 0;
  get_width_helper({0, 0}, root(), height());
  return rightmost - leftmost;
}

void QBST::get_width_helper(QPoint const &center, QBST_node const *rt,
                            int const h) {
  if (!rt)
    return;

  QPoint lcenter, rcenter;
  get_next_center(center, lcenter, rcenter, h, rt);

  leftmost = std::min(leftmost, lcenter.x());
  rightmost = std::max(rightmost, rcenter.y());

  get_width_helper(lcenter, rt->left(), h - 1);
  get_width_helper(rcenter, rt->right(), h - 1);
}

void QBST::set_position(QPoint const &center) {
  set_position_helper(center, this->_root, height());
}

void QBST::set_position_helper(QPoint const &center, QBST_node *rt,
                               int const h) {
  // set the position of the tree node
  if (!rt)
    return;
  rt->_data.set_position(center.x(), center.y());

  Q_ASSERT(center.x() && center.y());
  qDebug() << "set position: " << center;

  QPoint lcenter, rcenter;
  get_next_center(center, lcenter, rcenter, h, rt);

  set_position_helper(lcenter, rt->_left, h - 1);
  set_position_helper(rcenter, rt->_right, h - 1);
}

