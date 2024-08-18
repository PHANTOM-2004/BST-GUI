/// \file
/// \brief implementation of RenderArea
///
#include "renderarea.hpp"
#include "common.hpp"
#include "qbst/QBST.hpp"
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <qdebug.h>

RenderArea::RenderArea(QWidget *parent) : QWidget{parent} {
  resize(common::RA_W, common::RA_H);
  this->tree = new QBST;
  this->timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, &RenderArea::unhighlight);

  // init the tree with some data here
  tree->insert(QBST_data("50"));
  tree->insert(QBST_data("150"));
  tree->insert(QBST_data("260"));
  tree->insert(QBST_data("10"));
  tree->insert(QBST_data("96"));
  tree->insert(QBST_data("85"));
  tree->insert(QBST_data("59"));
  tree->insert(QBST_data("20"));
  tree->insert(QBST_data("0"));
  tree->insert(QBST_data("350"));
  tree->insert(QBST_data("90"));
  tree->insert(QBST_data("299"));
  tree->insert(QBST_data("450"));
  tree->insert(QBST_data("450"));
  tree->insert(QBST_data("267"));
  tree->insert(QBST_data("129"));
  tree->insert(QBST_data("500"));
  tree->insert(QBST_data("ZZZZ"));

  qDebug() << width() << height();

  tree->set_color();

  adjust_render_size();

  focus_on_target();
}

void RenderArea::focus_on_target() {
  // if there is a target, focus on target
  //
  // else focus on root
  qbst::QBST_node const *focus = hl_valid ? target : tree->root();

  // send the signal
  emit center_on_target(focus->data().position());
}

void RenderArea::adjust_render_size() {
  // suppose we place it in the center
  tree->set_position({width() / 2, tree->dis_from_ceil()});

  QPoint const root_pos = tree->get_center_position();
  QRect const bound_box = tree->get_tree_bound();
  qDebug() << bound_box;
  qDebug() << root_pos;

  int const new_w = bound_box.width() + tree->horizontal_interval() * 2;
  int const new_h = bound_box.height() + tree->vertival_interval() * 2;

  // shift the tree
  QPoint const offset =
      -(bound_box.topLeft() -
        QPoint(tree->horizontal_interval(), tree->dis_from_ceil()));
  tree->translate_tree(offset);

  if (new_h > height() && new_w > width()) {
    resize(new_w, new_h);
  }
}

void RenderArea::rerender() {
  // rerender when there is insertion/deletion/searching
  //
  adjust_render_size();

  focus_on_target();

  // we must repaint here, or it will not update
  this->repaint();
}

void RenderArea::unhighlight() {
  if (!hl_valid)
    return;

  tree->set_color();
  hl_valid = false;

  // repaint immediately
  this->repaint();
}

void RenderArea::highlight() {
  hl_valid = true;
  tree->set_highlight_color(target);

  // set up the timer
  timer->setInterval(common::WAITING_TIME);
  timer->start();

  // repaint immediately
  this->repaint();
}

void RenderArea::update_handler(U_signals const signal, QString const &text) {
  bool ret = false;
  switch (signal) {
  case UPDATE_DELETE:

    ret = tree->erase(text);
    if (!ret)
      QMessageBox::information(this, tr("Information"), "deletion failed");
    break;

  case UPDATE_INSERT:
    target = tree->insert(text);
    highlight();
    break;

  case UPDATE_SEARCH:
    target = tree->search(text);
    if (target) {
      highlight();
    } else
      QMessageBox::information(this, tr("Information"), "search failed");
    break;

  default:
    Q_ASSERT(0);
  }

  rerender();
}

/// \brief overwrite the paintEvent to draw graph
/// \param event get QPaintEvent type event
void RenderArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
  //
  // painter.drawLine(80, 100, 950, 750);
  // QPoint const a(10, 10), b(100, 400);
  // painter.drawLine(a, b);
  // painter.drawRect(10, 10, 100, 400);
  // painter.drawRect(20, 20, 400, 300);
  //
  // painter.setPen(QPen(Qt::red, 5));
  // painter.setBrush(Qt::blue);
  // painter.drawEllipse(50, 150, 400, 200);
  //
  // painter.drawEllipse({500, 500}, 40, 40);
  //
  // QFont font = painter.font();
  // font.setPointSize(common::FONT_SIZE);
  // painter.setFont(font);
  //
  // painter.drawText(50 + 400 / 2, 150 + 200 / 2, "Hell World!");
  //

  tree->render(&painter);
}
