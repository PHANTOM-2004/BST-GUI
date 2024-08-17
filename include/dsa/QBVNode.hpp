/// \file
/// \brief the definition of the binary tree node for qt visualisation
///

#pragma once

#include <qnamespace.h>
#ifndef __QBVNODE_HPP__
#define __QBVNODE_HPP__

#include <QPoint>
#include <QString>

namespace dsa {

class QBVNode {

public:
  QBVNode(QString const &val) : _val(val) {}
  QString const &str() const { return _val; }

  inline bool operator<(QBVNode const &other) const {
    auto const l1 = this->str().length();
    auto const l2 = other.str().length();
    if (l1 != l2) {
      return l1 < l2;
    }
    return str() < other.str();
  }

  inline bool operator==(QBVNode const &other) const {
    return str() == other.str();
  }

  Qt::GlobalColor get_bg_color() const { return _bg_color; }
  Qt::GlobalColor get_eg_color() const { return _eg_color; }

private:
  QString _val;
  QPoint _position;
  Qt::GlobalColor _bg_color = Qt::blue;
  Qt::GlobalColor _eg_color = Qt::red;
};

}; // namespace dsa

#endif
