/// \file
/// \brief the immplementation of the function
/// related to the render of QBST

#include "common.hpp"
#include "qbst/QBST.hpp"

using qbst::QBST;
using qbst::QBST_data;
using qbst::QBST_node;


void QBST::set_highlight_color(QBST_node *node) {
  Q_ASSERT(exist(node));
  node->_data._bg_color = HL_COLOR;
}

void QBST::set_node_color(QBST_node *node) {
  // Q_ASSERT(exist(node));
  if (node == this->root()) {
    node->_data._bg_color = ROOT_COLOR;
  } else if (node->is_left()) {
    node->_data._bg_color = LCHILD_COLOR;
  } else if (node->is_right()) {
    node->_data._bg_color = RCHILD_COLOR;
  }
}

void QBST::set_color() {
  auto color_set = [this](QBST_node *node) { this->set_node_color(node); };
  mid_traverse(color_set, _root);
}

void QBST::render(QPainter *painter) {

  // only render when the tree is not empty
  if (empty())
    return;

  /// \brief helper function to render node
  auto render_node = [painter](QBST_node const *node) {
    if (!node)
      return;

    auto const &data = node->data();

    painter->setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
    painter->setPen(QPen(data.get_eg_color(), common::LINE_WIDTH));
    data.render(painter, RADIUS);
  };

  // \brief helper function to render line
  auto render_line = [painter](QBST_node const *node) {
    if (!node)
      return;

    auto const &data = node->data();

    // draw the line to its parent
    painter->setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform, true);
    painter->setPen(QPen(data.get_eg_color(), common::LINE_WIDTH));

    if (node->parent())
      painter->drawLine(data.position(), node->parent()->data().position());
  };

  // traverse
  // line first
  post_traverse(render_line);
  // node second
  post_traverse(render_node);
}
