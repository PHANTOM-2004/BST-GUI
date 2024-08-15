/// \file
/// \brief definition of RenderArea
///
#pragma once

#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include <QWidget>

/// \brief we paint the binary tree in the RenderArea
class RenderArea : public QWidget {
  Q_OBJECT
public:
  /// \brief initialize the size of RenderArea
  explicit RenderArea(QWidget *parent = nullptr);

protected:
  /// \brief overwrite the virtual function to paint
  void paintEvent(QPaintEvent *event) override;

signals:
};

#endif // RENDERAREA_HPP
