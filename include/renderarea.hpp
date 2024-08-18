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
  enum U_signals { UPDATE_SEARCH, UPDATE_INSERT, UPDATE_DELETE };
  /// \brief initialize the size of RenderArea
  explicit RenderArea(QWidget *parent = nullptr);
  ~RenderArea() { delete tree; }

  void rerender();

  void highlight();

  void unhighlight();

  void update_handler(U_signals const signal, QString const &text);

  void adjust_render_size();

  void focus_on_target();

protected:
  /// \brief overwrite the virtual function to paint
  void paintEvent(QPaintEvent *event) override;

  QBST *tree;
  bool hl_valid = false;
  qbst::QBST_node *target;

  QTimer *timer;

signals:
  void center_on_target(QPoint const& target);
};

#endif // RENDERAREA_HPP
