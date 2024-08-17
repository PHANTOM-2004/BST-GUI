/// \file
/// \brief the definition of ther binary tree node
#pragma once

#ifndef __BITNODE_HPP__
#define __BITNODE_HPP__

#include <algorithm>
#include <concepts>

namespace qbst {
class QBST;
};

namespace dsa {

/// \brief concept for binary tree node type
template <typename T>
concept Comparable = requires(T const &a, T const &b) {
  { a < b } -> std::convertible_to<bool>;
  { a == b } -> std::convertible_to<bool>;
};

template <Comparable T> class BST;

/// \brief Binary Tree Node, only valid when T is arithmetic type or string type
///
/// we need it to help maintain the binary tree,
/// also we overload the string comparison, so that
/// it behaves as if it was arithmetic type
template <Comparable T> class BiTNode {
  // only instancialize when basic arithmetic type or string
  friend class BST<T>;
  friend class qbst::QBST;

public:
  BiTNode(T const &val, BiTNode<T> *parent = nullptr,
          BiTNode<T> *lChild = nullptr, BiTNode<T> *rChild = nullptr);

  /// \brief get left child, readonly
  inline BiTNode<T> const *left() const;
  /// \brief get right child, readonly
  inline BiTNode<T> const *right() const;
  /// \brief get parent, readonly
  inline BiTNode<T> const *parent() const;
  /// \brief get data, readonly
  inline T const &data() const;

  BiTNode<T> *succ();

  /// \brief insert as left child
  BiTNode<T> *insert_as_left(BiTNode<T> *parent);
  /// \brief insert as right child
  BiTNode<T> *insert_as_right(BiTNode<T> *parent);

  bool is_left() const;
  bool is_right() const;

  /// \brief update the height of this node
  inline void update_height();
  /// \brief update the height from this node and update above
  void update_height_above();

  /// \brief get the height of the node, empty node is -1
  static inline int height(BiTNode<T> const *node);

protected:
  /// \brief store the height of the node
  int _height = 0;
  /// \brief store the data of the node
  T _data;
  /// \brief store the parent of the node
  BiTNode<T> *_parent;
  /// \brief store the left child of the node
  BiTNode<T> *_left;
  /// \brief store the right child of the node
  BiTNode<T> *_right;
};

// implementation
template <Comparable T>
BiTNode<T>::BiTNode(T const &val, BiTNode<T> *parent, BiTNode<T> *lChild,
                    BiTNode<T> *rChild)
    : _data(val), _parent(parent), _left(lChild), _right(rChild){};

template <Comparable T> BiTNode<T> *BiTNode<T>::succ() {
  BiTNode<T> *res = this;
  if (_right) {
    // succ is in right tree
    res = _right;
    while (res->_left) // has left child
      res = res->_left;

    return res;
  }

  // no right child
  // lowest left ancestor
  do
    res = res->_parent;
  while (res->is_right());
  // if res is nullptr, it means "this" is the last one

  return res;
}

template <Comparable T> void BiTNode<T>::update_height() {
  this->_height = 1 + std::max(height(_left), height(_right));
}

template <Comparable T> void BiTNode<T>::update_height_above() {
  for (BiTNode<T> *t = this; t != nullptr; t = t->_parent) {
    t->update_height();
  }
}

template <Comparable T>
BiTNode<T> *BiTNode<T>::insert_as_right(BiTNode<T> *parent) {
  return parent->_right = this;
}

template <Comparable T>
BiTNode<T> *BiTNode<T>::insert_as_left(BiTNode<T> *parent) {
  return parent->_left = this;
}

template <Comparable T> bool BiTNode<T>::is_right() const {
  return _parent && _parent->_right == this;
}

template <Comparable T> bool BiTNode<T>::is_left() const {
  return _parent && _parent->_left == this;
}

template <Comparable T> int BiTNode<T>::height(BiTNode<T> const *node) {
  // the height of empty node is -1
  return node ? node->_height : -1;
}

template <Comparable T> T const &BiTNode<T>::data() const { return _data; }

template <Comparable T> BiTNode<T> const *BiTNode<T>::left() const {
  return _left;
}

template <Comparable T> BiTNode<T> const *BiTNode<T>::right() const {
  return _right;
}

template <Comparable T> BiTNode<T> const *BiTNode<T>::parent() const {
  return _parent;
}

} // namespace dsa
#endif
