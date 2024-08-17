
#pragma once

#include <qpoint.h>
#ifndef __QBST_HPP__
#define __QBST_HPP__

#include "dsa/BST.hpp"
#include "qbst/QVBNode.hpp"
#include <QPainter>
#include <QString>

namespace qbst {

using QBST_base = dsa::BST<QVBNode>;
using QBST_node = dsa::BiTNode<QVBNode>;
using QBST_data = QVBNode;

/// \brief the class to visualize binary search tree
class QBST : public QBST_base {
public:
  QBST() = default;


  QBST_node *&search(QBST_data const &val) override;
  QBST_node *insert(QBST_data const &val) override;
  bool erase(QVBNode const &val) override;

  void adjust_position(QPoint const &center, int const h);

  bool render_node(QBST_data const *node) const;

  int get_width();

  void set_position(QPoint const & center);


private:

  void set_painter(QPainter *painter) const;

  int get_leftmost_rpos(int const h) const;
  int get_rightmost_rpos(int const h) const;

  void get_width_helper(QPoint const &center, QBST_node const *rt, int const h);
  static void set_position_helper(QPoint const &center, QBST_node *rt,
                                  int const h);
  static void get_next_center(QPoint const &center, QPoint &lcenter,
                              QPoint &rcenter, int const h,
                              QBST_node const *rt);

private:
  int leftmost = 0, rightmost = 0;

  mutable QPainter *painter = nullptr;

  /// \brief we draw the node as a circle
  static int constexpr radius = 20;

  /// \brief it is the interval of the nodes at the bottom level
  static int constexpr interval = 5;

  /// \brief the basic width between the nodes center and its parent center
  /// at the bottom level
  static int constexpr base_width = radius + interval;

  static int constexpr base_height = radius + radius + 50;
};

}; // namespace qbst
#endif
