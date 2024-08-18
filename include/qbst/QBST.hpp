/// \file
/// \brief the definition of QBST
///
#pragma once

#ifndef __QBST_HPP__
#define __QBST_HPP__

#include "common.hpp"
#include "dsa/BST.hpp"
#include "qbst/QVBNode.hpp"

#include <QObject>
#include <QPainter>
#include <QString>

class RenderArea;

namespace qbst {

/// \brief abbr for BST<QVBNode> base tree type
using QBST_base = dsa::BST<QVBNode>;
/// \brief abbr for QBST node type
using QBST_node = dsa::BiTNode<QVBNode>;
/// \brief abbr for QBST data type
using QBST_data = QVBNode;

/// \brief the class to visualize binary search tree
///
/// it inherits BST<QVBNode>, and QObject.
/// We inherit QObject inorder to use signal and slots
/// when the insert/delete button is trigger, the tree need to
/// adjust its position
class QBST : public QBST_base {

  friend class BSTtest;
  friend class ::RenderArea;

public:
  /// \brief default constructor
  QBST() = default;

  /// \brief overwrite the search
  ///
  /// it will set _hit, which is always the parent of
  /// the node just searched
  /// it will also set the color of the node hit to special
  /// color for seconds
  ///
  /// \param val the value to search for
  /// \return the reference to the node hit
  ///
  QBST_node *&search(QBST_data const &val) override;

  QRect get_tree_bound() const;

  void translate_tree(QPoint const &offset);

  /// \brief insert a node
  ///
  /// it will insert a node, when the value exists, it will
  /// do nothing.
  /// it will also set the color of the node inserted to special
  /// color for seconds
  ///
  /// \param val the value to insert
  /// \return always point to the node inserted(whether it is really inserted)
  QBST_node *insert(QBST_data const &val) override;

  /// \brief delete a node
  ///
  /// \param val the value to delete
  /// \return whether or not it is deleted successfully
  bool erase(QVBNode const &val) override;

  /// \brief render the entire tree
  ///
  /// \param center the position of the root
  /// \param painter painter from painEvent()
  void render(QPainter *painter);

  /// \brief set the position of each node of the tree
  /// according to the center
  ///
  /// \param center the position of the root
  void set_position(QPoint const &center);

  QPoint const &get_center_position() const { return center_position; }

  void set_color();

  void set_node_color(QBST_node *node);

  void set_highlight_color(QBST_node *node);

  static constexpr int vertival_interval() { return BASE_HEIGHT; }
  static constexpr int horizontal_interval() { return BASE_WIDTH; }
  static constexpr int dis_from_ceil() { return DIS_FROM_CEIL; }

private:
  /// \brief adjust the position of each node of the tree
  ///
  /// after insertion/deletion, the area that the tree covers will
  /// change. we need to update through this function
  ///
  /// \param center the position of the root
  void adjust_position(QBST_node *rt);

  void translate_subtree(QPoint const &offset, QBST_node *rt);

  /// \brief helper function to get width
  /// \param center position of param rt
  /// \param rt current node to set
  /// \param h current height
  void get_subtree_bound(QBST_node const *rt) const;

  /// \brief helper function to get position
  /// \param center position of param rt
  /// \param rt current node to set
  /// \param h current height
  void estimate_position(QPoint const &center, QBST_node *rt);

  /// \brief helper function for get_width and set_position
  ///
  /// get the position of the left and right node  or rt
  ///
  /// \param center the position of rt
  /// \param lcenter set as left node position
  /// \param rcenter set as reft node position
  /// \param rt current node
  /// \param h current height
  void estimate_next_center(QPoint const &center, QPoint &lcenter,
                            QPoint &rcenter, QBST_node const *rt);

  bool adjust_next_center(QBST_node *rt);

private:
  void get_subtree_bound_helper(QBST_node const *rt) const;
  /// \brief record the leftmost relative position of the tree
  mutable int leftmost = 0;
  /// \brief record the rightmost relative position of the tree
  mutable int rightmost = 0;

  QPoint center_position;

  /// \brief we draw the node as a circle
  static int constexpr RADIUS = common::NODE_RADIUS;

  /// \brief it is the interval of the nodes at the bottom level
  static int constexpr HINTERVAL = common::NODE_H_INTERVAL;

  /// \brief the basic width between the nodes center and its parent center
  /// at the bottom level
  static int constexpr BASE_WIDTH = RADIUS + HINTERVAL;

  /// \brief the height between node of different level
  static int constexpr BASE_HEIGHT = RADIUS + RADIUS + common::NODE_V_INTERVAL;

  static int constexpr DIS_FROM_CEIL = RADIUS + HINTERVAL;

  static constexpr Qt::GlobalColor ROOT_COLOR = Qt::gray;
  static constexpr Qt::GlobalColor LCHILD_COLOR = Qt::blue;
  static constexpr Qt::GlobalColor RCHILD_COLOR = Qt::yellow;
  static constexpr Qt::GlobalColor HL_COLOR = Qt::green;
};

}; // namespace qbst
#endif
