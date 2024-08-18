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
  /// \brief initialize the size of RenderArea
  explicit RenderArea(QWidget *parent = nullptr);
  ~RenderArea() { delete tree; }

protected:
  /// \brief overwrite the virtual function to paint
  void paintEvent(QPaintEvent *event) override;

  QBST *tree;

signals:
};

#endif // RENDERAREA_HPP
