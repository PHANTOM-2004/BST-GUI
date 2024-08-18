/// \file
/// \brief definition of RenderArea
///
#pragma once

#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include "qbst/QBST.hpp"
#include <QWidget>

using qbst::QBST;
using qbst::QBST_data;

/// \brief we paint the binary tree in the RenderArea
class RenderArea : public QWidget {
  Q_OBJECT
public:
  /// \brief type of event for update_handler
  enum U_signals { UPDATE_SEARCH, UPDATE_INSERT, UPDATE_DELETE };
  /// \brief initialize the size of RenderArea
  explicit RenderArea(QWidget *parent = nullptr);
  ~RenderArea() { delete tree; }

  /// \brief rerender the tree, when the tree is updated
  void rerender();

  /// \brief highlight the target of search/insert
  /// the node will change color for seconds
  void highlight();

  /// \brief unhighlight the target of search/insert
  void unhighlight();

  /// \brief handler for different event(insert, search, delete)
  /// \param signal type of event
  /// \param text the input data to insert/search/delete
  void update_handler(U_signals const signal, QString const &text);

  /// \brief adjust the render size according to the tree size
  /// the minimal size is the initial size in namespace common
  void adjust_render_size();

  /// \brief helper function of signals: center_on_target
  /// in order to focus the scroll area
  void focus_on_target();

protected:
  /// \brief overwrite the virtual function to paint
  void paintEvent(QPaintEvent *event) override;

  /// \brief the binary search tree
  QBST *tree;
  /// \brief record whether the target is valid
  bool hl_valid = false;
  /// \brief point to the target
  qbst::QBST_node *target;

  /// \brief timer to time highlight time
  QTimer *timer;

signals:
  /// \brief signals of focusing on target
  /// \param target the position of the target
  void center_on_target(QPoint const& target);
};

#endif // RENDERAREA_HPP
