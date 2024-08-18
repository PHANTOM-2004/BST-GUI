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
#include <chrono>
#include <ctime>

RenderArea::RenderArea(QWidget *parent) : QWidget{parent} {
  resize(common::RA_W, common::RA_H);
  this->tree = new QBST;
  this->timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, &RenderArea::unhighlight);

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

  tree->set_position({1000, 50});
  tree->set_color();
}

void RenderArea::rerender() {
  // rerender when there is insertion/deletion/searching
  qDebug() << "Rerender begin";
  tree->set_position(
      {common::RA_W / 2, common::NODE_INTERVAL + common::NODE_RADIUS});
  qDebug() << "Rerender end";

  // we must repaint here, or it will not update
  this->repaint();
}

void RenderArea::unhighlight() {
  if (!hl_valid)
    return;

  tree->set_color();
  hl_valid = false;

  this->repaint();
}

void RenderArea::highlight() {
  hl_valid = true;
  tree->set_highlight_color(target);

  timer->setInterval(common::WAITING_TIME);
  timer->start();

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

  tree->render({1000, 10}, &painter);
}
