#pragma once

#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include <QWidget>

class RenderArea : public QWidget {
  Q_OBJECT
public:
  explicit RenderArea(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;

signals:
};

#endif // RENDERAREA_HPP
