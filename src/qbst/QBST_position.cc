#include "qbst/QBST.hpp"

using qbst::QBST;
using qbst::QBST_data;
using qbst::QBST_node;

void QBST::adjust_position(QBST_node *rt) {
  if (!rt)
    return;

  // qDebug() << "Adjust at " << rt->data().str();

  // when there is an empty subtree, no need to adjust
  if (rt->has_both())
    adjust_next_center(rt);

  adjust_position(rt->_left);
  adjust_position(rt->_right);
}

void QBST::get_subtree_bound(QBST_node const *rt) const {
  Q_ASSERT(rt);

  // qDebug() << "sub bound for: " << rt->data().str();

  leftmost = std::numeric_limits<int>::max();
  rightmost = std::numeric_limits<int>::min();

  get_subtree_bound_helper(rt);
  // qDebug() << "sub bound end " << rt->data().str();
}

void QBST::get_subtree_bound_helper(QBST_node const *rt) const {
  if (!rt)
    return;

  auto const pos = rt->data().position();
  leftmost = std::min(pos.x(), leftmost);
  rightmost = std::max(pos.x(), rightmost);

  // qDebug() << "l at " << rt->data().str() << " " << pos.x() << " " <<
  // leftmost; qDebug() << "r at " << rt->data().str() << " " << pos.x() << " "
  // << rightmost;
  if (rt->left())
    get_subtree_bound_helper(rt->left());
  if (rt->right())
    get_subtree_bound_helper(rt->right());
}

void QBST::set_position(QPoint const &center) {
  Q_ASSERT(!empty());

  // here we set once, propably it is not perfect

  estimate_position(center, this->_root);

  // so we need to adjust the position according to the tree
  adjust_position(this->_root);
  adjust_position(this->_root);

  // set the center position
  center_position = root()->data().position();
}

void QBST::estimate_position(QPoint const &center, QBST_node *rt) {
  // set the position of the tree node
  if (!rt)
    return;

  rt->_data.set_position(center.x(), center.y());

  Q_ASSERT(center.x() && center.y());
  // qDebug() << "estimate position: " << center << " with: " <<
  // rt->data().str();

  QPoint lcenter, rcenter;
  estimate_next_center(center, lcenter, rcenter, rt);

  estimate_position(lcenter, rt->_left);
  estimate_position(rcenter, rt->_right);
}

void QBST::estimate_next_center(QPoint const &center, QPoint &lcenter,
                                QPoint &rcenter, QBST_node const *rt) {
  int const hleft = QBST_node::height(rt->left());
  int const hright = QBST_node::height(rt->right());
  int const balance = hleft - hright;
  int const mini_h = std::max(0, std::min(hleft, hright));

  int step_x_l = BASE_WIDTH * (1 << hleft),
      step_x_r = BASE_WIDTH * (1 << hright), step_y = BASE_HEIGHT;

  if (std::abs(balance) > 1 || hleft <= 0 || hright <= 0) {
    step_x_l = BASE_WIDTH * (1 << mini_h);
    step_x_r = BASE_WIDTH * (1 << mini_h);
  }

  // qDebug() << "minih: " << mini_h;
  // if (rt->left())
  //   qDebug() << "L: " << step_x_l << " at " << rt->left()->data().str();
  // if (rt->right())
  //   qDebug() << "R: " << step_x_l << " at " << rt->right()->data().str();

  lcenter = {center.x() - step_x_l, center.y() + step_y};
  rcenter = {center.x() + step_x_r, center.y() + step_y};
}

bool QBST::adjust_next_center(QBST_node *rt) {
  // qDebug() << "Call ANC at: " << rt->data().str();

  int rl_off = 0, lr_off = 0;
  // for left tree
  get_subtree_bound(rt->left());
  // we care about rbound
  lr_off = rightmost;
  // for right tree
  get_subtree_bound(rt->right());
  // we care about lbound
  rl_off = leftmost;

  int const distance = rl_off - lr_off - 2 * RADIUS - HINTERVAL;

  // qDebug() << "l: " << lr_off << " r: " << rl_off
  //          << " at: " << rt->data().position() << " With: " << rt->data().str()
  //          << " Dis: " << distance;
  //
  // qDebug() << "LCHILD: " << (rt->left() ? rt->left()->data().str() : "NULL")
  //          << (rt->left() ? rt->left()->data().position() : QPoint(-1, -1));
  // qDebug() << "RCHILD: " << (rt->right() ? rt->right()->data().str() : "NULL")
  //          << (rt->right() ? rt->right()->data().position() : QPoint(-1, -1));

  translate_subtree({distance / 2, 0}, rt->_left);
  translate_subtree({-distance / 2, 0}, rt->_right);

  return true;
}

QRect QBST::get_tree_bound() const {
  get_subtree_bound(root());

  // root point is clear
  // add the radius width
  QPoint const topleft = {-RADIUS + leftmost, center_position.y() - RADIUS};
  // add the radius  width
  QPoint const bottomright = {RADIUS + rightmost, height() * BASE_HEIGHT +
                                                      center_position.y() +
                                                      RADIUS};

  return QRect(topleft, bottomright);
}

void QBST::translate_tree(QPoint const &offset) {
  translate_subtree(offset, _root);
}

void QBST::translate_subtree(QPoint const &offset, QBST_node *rt) {
  auto trans = [&offset](QBST_data &data) { data._position += offset; };
  // traverse
  mid_traverse(trans, rt);
}
