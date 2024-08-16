/// \file
/// \brief definition of the binary tree for qt visualization
///
#pragma once

#ifndef __QBITREE_HPP
#define __QBITREE_HPP

#include "dsa/QBiTNode.hpp"
namespace dsa {

class QBiTree {

public:
  QBiTree() = default;

private:
  mutable QBiTNode *_hit = nullptr;
  QBiTNode *_root = nullptr;
};

}; // namespace dsa

#endif
