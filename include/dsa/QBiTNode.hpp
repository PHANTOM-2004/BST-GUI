/// \file
/// \breif the definition of the binary tree node for qt visualisation
///

#pragma once

#ifndef __QBITNODE_HPP__
#define __QBITNODE_HPP__

#include "dsa/BiTNode.hpp"
#include <QPoint>

namespace dsa {


class QBiTNode : public BiTNode<QString> {

friend class QBiTree;

public:
  QBiTNode(QString const &val, QBiTNode *parent = nullptr,
           QBiTNode *lChild = nullptr, QBiTNode *rChild = nullptr,
           Qt::GlobalColor bg_color = Qt::blue,
           Qt::GlobalColor eg_color = Qt::red);

private:
  QPoint position;
  Qt::GlobalColor bg_color;
  Qt::GlobalColor eg_color;
};
} // namespace dsa

#endif
