#include "common.hpp"
#include "qbst/QBST.hpp"
#include <limits>

using qbst::QBST;
using qbst::QBST_data;
using qbst::QBST_node;

void QBST::set_painter(QPainter *painter) const { this->painter = painter; }

void QBST::estimate_next_center(QPoint const &center, QPoint &lcenter,
                                QPoint &rcenter, QBST_node const *rt) {
  int const hleft = QBST_node::height(rt->left());
  int const hright = QBST_node::height(rt->right());
  int const balance = hleft - hright;
  int const mini_h = std::max(0, std::min(hleft, hright));

  int step_x_l = base_width * (1 << hleft),
      step_x_r = base_width * (1 << hright), step_y = base_height;

  if (std::abs(balance) > 1 || hleft <= 0 || hright <= 0) {
    step_x_l = base_width * (1 << mini_h);
    step_x_r = base_width * (1 << mini_h);
  }

  lcenter = {center.x() - step_x_l, center.y() + step_y};
  rcenter = {center.x() + step_x_r, center.y() + step_y};
}

bool QBST::adjust_next_center(QBST_node *rt) {
  qDebug() << "Call at: " << rt->data().str();

  int rl_off = 0, lr_off = 0;
  // for left tree
  get_subtree_bound(rt->left());
  // we care about rbound
  lr_off = rightmost;
  // for right tree
  get_subtree_bound(rt->right());
  // we care about lbound
  rl_off = leftmost;

  int const distance = rl_off - lr_off - 2 * radius - interval;

  qDebug() << "l: " << lr_off << " r: " << rl_off
           << " at: " << rt->data().position() << " With: " << rt->data().str()
           << " Dis: " << distance;

  qDebug() << "LCHILD: " << (rt->left() ? rt->left()->data().str() : "NULL")
           << (rt->left() ? rt->left()->data().position() : QPoint(-1, -1));
  qDebug() << "RCHILD: " << (rt->right() ? rt->right()->data().str() : "NULL")
           << (rt->right() ? rt->right()->data().position() : QPoint(-1, -1));

  auto shift_lChild = [distance](QBST_data &data) {
    auto const pos = data.position();
    data.set_position(pos.x() + distance / 2, pos.y());
  };

  mid_traverse(shift_lChild, rt->_left);

  auto shift_rChild = [distance](QBST_data &data) {
    auto const pos = data.position();
    data.set_position(pos.x() - distance / 2, pos.y());
  };

  mid_traverse(shift_rChild, rt->_right);

  return true;
}

void QBST::set_color() {
  auto color_set = [this](QBST_node *node) {
    if (node == this->root()) {
      node->_data._bg_color = ROOT_COLOR;
    } else if (node->is_left()) {
      node->_data._bg_color = LCHILD_COLOR;
    } else if (node->is_right()) {
      node->_data._bg_color = RCHILD_COLOR;
    }
  };

  mid_traverse(color_set, _root);
}

void QBST::adjust_position(QBST_node *rt) {
  if (!rt)
    return;

  qDebug() << "Adjust at " << rt->data().str();

  // when there is an empty subtree, no need to adjust
  if (rt->has_both())
    adjust_next_center(rt);

  adjust_position(rt->_left);
  adjust_position(rt->_right);
}

void QBST::get_subtree_bound(QBST_node const *rt) {
  Q_ASSERT(rt);

  qDebug() << "sub bound for: " << rt->data().str();

  leftmost = std::numeric_limits<int>::max();
  rightmost = std::numeric_limits<int>::min();

  get_subtree_bound_helper(rt);
}

void QBST::get_subtree_bound_helper(QBST_node const *rt) {
  if (!rt)
    return;

  auto const pos = rt->data().position();
  leftmost = std::min(pos.x(), leftmost);
  rightmost = std::max(pos.x(), rightmost);

  // qDebug() << "l at " << rt->data().str() << " " << pos.x() << " " <<
  // leftmost; qDebug() << "r at " << rt->data().str() << " " << pos.x() << " "
  // << rightmost;

  get_subtree_bound_helper(rt->left());
  get_subtree_bound_helper(rt->right());
}

void QBST::set_position(QPoint const &center) {

  // here we set once, propably it is not perfect

  estimate_position(center, this->_root);

  // so we need to adjust the position according to the tree
  adjust_position(this->_root);
  adjust_position(this->_root);
}

void QBST::estimate_position(QPoint const &center, QBST_node *rt) {
  // set the position of the tree node
  if (!rt)
    return;
  rt->_data.set_position(center.x(), center.y());

  Q_ASSERT(center.x() && center.y());
  qDebug() << "estimate position: " << center << " with: " << rt->data().str();

  QPoint lcenter, rcenter;
  estimate_next_center(center, lcenter, rcenter, rt);

  estimate_position(lcenter, rt->_left);
  estimate_position(rcenter, rt->_right);
}

void QBST::render(QPoint const &center, QPainter *painter) {

  // only render when the tree is not empty
  if (empty())
    return;

  /// \brief helper function to render node
  auto render_node = [painter](QBST_node const *node) {
    if (!node)
      return;

    auto const &data = node->data();

    painter->setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
    painter->setPen(QPen(data.get_eg_color(), common::LINE_WIDTH));
    data.render(painter, radius);
  };

  // \brief helper function to render line
  auto render_line = [painter](QBST_node const *node) {
    if (!node)
      return;

    auto const &data = node->data();

    // draw the line to its parent
    painter->setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
    painter->setPen(QPen(data.get_eg_color(), common::LINE_WIDTH));

    if (node->parent())
      painter->drawLine(data.position(), node->parent()->data().position());
  };

  // traverse
  // line first
  post_traverse(render_line);
  // node second
  post_traverse(render_node);
}
