/// \file
/// \brief the definition of the binary tree node for qt visualisation
///

#pragma once

#ifndef __QBVNODE_HPP__
#define __QBVNODE_HPP__

#include <QPoint>
#include <QString>
#include <QPainter>

namespace qbst {

class QVBNode {
  friend class QBST;
public:
  QVBNode(QString const &val) : _val(val) {}
  QString const &str() const { return _val; }

  inline bool operator<(QVBNode const &other) const {
    auto const l1 = this->str().length();
    auto const l2 = other.str().length();
    if (l1 != l2) {
      return l1 < l2;
    }
    return str() < other.str();
  }

  inline bool operator==(QVBNode const &other) const {
    return str() == other.str();
  }

  QPoint const &position() const { return _position; }

  void set_position(int const x, int const y) {
    _position.setX(x);
    _position.setY(y);
  }

  constexpr Qt::GlobalColor get_bg_color() const { return _bg_color; }
  constexpr Qt::GlobalColor get_eg_color() const { return _eg_color; }

void  render (QPainter* painter, int const radius);

private:
  QString _val;
  QPoint _position;
  Qt::GlobalColor _bg_color = Qt::blue;
  Qt::GlobalColor _eg_color = Qt::red;
};

}; // namespace qbst

#endif
