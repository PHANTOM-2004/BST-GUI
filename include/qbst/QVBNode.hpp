/// \file
/// \brief the definition of the binary tree node for qt visualisation
///

#pragma once

#ifndef __QBVNODE_HPP__
#define __QBVNODE_HPP__

#include <QPainter>
#include <QPoint>
#include <QString>

namespace qbst {

/// \brief data for QBST,
/// store the string to show, position , and color
/// also, it provide operator== and operator<
class QVBNode {
  friend class QBST;

public:
  /// \brief trivial constructor
  QVBNode(QString const &val) : _val(val) {}

  /// \brief getter for _val
  QString const &str() const { return _val; }

  /// \brief operator<
  inline bool operator<(QVBNode const &other) const {
    auto const l1 = this->str().length();
    auto const l2 = other.str().length();
    if (l1 != l2) {
      return l1 < l2;
    }
    return str() < other.str();
  }

  /// \brief operator==
  inline bool operator==(QVBNode const &other) const {
    return str() == other.str();
  }

  /// \brief getter for _position
  QPoint const &position() const { return _position; }

  /// \brief setter for _position
  void set_position(int const x, int const y) {
    _position.setX(x);
    _position.setY(y);
  }

  /// \brief getter for _bg_color
  constexpr Qt::GlobalColor get_bg_color() const { return _bg_color; }

  /// \brief getter for _eg_color
  constexpr Qt::GlobalColor get_eg_color() const { return _eg_color; }

  /// \brief render the node
  /// \param painter trivial
  /// \param radius radius of the circle
  void render(QPainter *painter, int const radius) const;

private:

  /// \brief store the string
  QString _val;

  /// \brief store the position
  QPoint _position;

  /// \brief store the background color
  Qt::GlobalColor _bg_color = Qt::blue;

  /// \brief store the egde color
  Qt::GlobalColor _eg_color = Qt::red;
};

}; // namespace qbst

#endif
