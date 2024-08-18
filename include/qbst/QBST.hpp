/// \file
/// \brief the definition of QBST
///
#pragma once

#include "common.hpp"
#include <qnamespace.h>
#ifndef __QBST_HPP__
#define __QBST_HPP__

#include "dsa/BST.hpp"
#include "qbst/QVBNode.hpp"
#include <QObject>
#include <QPainter>
#include <QString>

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
  void render(QPoint const &center, QPainter *painter);

  /// \brief set the position of each node of the tree
  /// according to the center
  ///
  /// \param center the position of the root
  void set_position(QPoint const &center);

  void set_color();

  void set_node_color(QBST_node* node);

  void set_highlight_color(QBST_node *node);

private:
  /// \brief adjust the position of each node of the tree
  ///
  /// after insertion/deletion, the area that the tree covers will
  /// change. we need to update through this function
  ///
  /// \param center the position of the root
  void adjust_position(QBST_node *rt);

  /// \brief set the painter
  void set_painter(QPainter *painter) const;

  /// \brief helper function to get width
  /// \param center position of param rt
  /// \param rt current node to set
  /// \param h current height
  void get_subtree_bound(QBST_node const *rt);

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
  void get_subtree_bound_helper(QBST_node const *rt);
  /// \brief record the leftmost relative position of the tree
  int leftmost = 0;
  /// \brief record the rightmost relative position of the tree
  int rightmost = 0;

  /// \brief save the painter
  mutable QPainter *painter = nullptr;

  /// \brief we draw the node as a circle
  static int constexpr radius = common::NODE_RADIUS;

  /// \brief it is the interval of the nodes at the bottom level
  static int constexpr interval = common::NODE_INTERVAL;

  /// \brief the basic width between the nodes center and its parent center
  /// at the bottom level
  static int constexpr base_width = radius + interval;

  /// \brief the height between node of different level
  static int constexpr base_height = radius + radius + interval;

  static constexpr Qt::GlobalColor ROOT_COLOR = Qt::gray;
  static constexpr Qt::GlobalColor LCHILD_COLOR = Qt::blue;
  static constexpr Qt::GlobalColor RCHILD_COLOR = Qt::yellow;
  static constexpr Qt::GlobalColor HL_COLOR = Qt::green;
};

}; // namespace qbst
#endif
