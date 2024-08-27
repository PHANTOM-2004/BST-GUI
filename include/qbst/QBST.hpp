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

  /// \brief get the bounding box of the tree
  /// \return the QRect as bounding box
  QRect get_tree_bound() const;

  /// \brief translate the tree
  /// \param offset the offset vector
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
  /// \param painter painter from painEvent()
  void render(QPainter *painter);

  /// \brief set the position of each node of the tree
  /// according to the center
  ///
  /// \param center the position of the root
  void set_position(QPoint const &center);

  /// \brief get the center position of the tree
  /// it is actually the position of root
  /// \return return the position
  QPoint const &get_center_position() const { return center_position; }

  /// \brief set the color of the node
  /// according to
  /// 1. root
  /// 2. is_left()
  /// 3. is_right
  void set_color();

  /// \brief set the color of a singl node
  /// according to
  /// 1. root
  /// 2. is_left()
  /// 3. is_right
  /// \param node the node to set
  void set_node_color(QBST_node *node);

  /// \brief highlight a node
  /// \brief the node to highlight
  void set_highlight_color(QBST_node *node);

  /// \brief getter for BASE_HEIGHT
  /// \return trivial
  static constexpr int vertical_interval() { return BASE_HEIGHT; }

  /// \brief getter for BASE_WIDTH
  /// \return trivial
  static constexpr int horizontal_interval() { return BASE_WIDTH; }

  /// \brief getter for DIS_FROM_CEIL
  /// \return trivial
  static constexpr int dis_from_ceil() { return DIS_FROM_CEIL; }

private:
  /// \brief adjust the position of each node of the tree
  ///
  /// after insertion/deletion, the area that the tree covers will
  /// change. we need to update through this function
  ///
  /// \param rt the position of the root
  void adjust_position(QBST_node *rt);

  /// \brief translate the subtree
  /// \param offset the offset vector
  /// \param rt the root of the subtree
  void translate_subtree(QPoint const &offset, QBST_node *rt);

  /// \brief helper function to get width
  /// \param rt current node to set
  void get_subtree_bound(QBST_node const *rt) const;

  /// \brief helper function to get position
  /// \param center position of param rt
  /// \param rt current node to set
  void estimate_position(QPoint const &center, QBST_node *rt);

  /// \brief helper function for get_width and set_position
  ///
  /// get the position of the left and right node  or rt
  ///
  /// \param center the position of rt
  /// \param lcenter set as left node position
  /// \param rcenter set as reft node position
  /// \param rt current node
  void estimate_next_center(QPoint const &center, QPoint &lcenter,
                            QPoint &rcenter, QBST_node const *rt);

  /// \brief adjust the position of the left child and right child
  /// \param rt the node to adjust
  /// it adjust according to the position of left tree and right tree
  /// \return whether adjusted
  bool adjust_next_center(QBST_node *rt);

private:
  /// \brief the helper function to get the bound of a subtree
  /// \param rt the root of the subtree
  void get_subtree_bound_helper(QBST_node const *rt) const;
  /// \brief record the leftmost relative position of the tree
  mutable int leftmost = 0;
  /// \brief record the rightmost relative position of the tree
  mutable int rightmost = 0;

  /// \brief the centor position of the tree, record the position of the root
  /// it is set bt set_position function, which set the tree according to the position
  /// and adjust the tree, and adjust the root position.
  /// no matter how it is set, center_position store the position of the root
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

  /// \brief the height between node of and the top of the render area
  static int constexpr DIS_FROM_CEIL = RADIUS + HINTERVAL;

  /// \brief trivial as name
  static constexpr Qt::GlobalColor ROOT_COLOR = Qt::gray;
  /// \brief trivial as name
  static constexpr Qt::GlobalColor LCHILD_COLOR = Qt::blue;
  /// \brief trivial as name
  static constexpr Qt::GlobalColor RCHILD_COLOR = Qt::yellow;
  /// \brief trivial as name
  static constexpr Qt::GlobalColor HL_COLOR = Qt::green;
};

}; // namespace qbst
#endif
