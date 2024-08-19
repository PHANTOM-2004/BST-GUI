/// \file
/// \brief definition of the binary tree for qt visualization
///
#pragma once

#ifndef __BST_HPP__
#define __BST_HPP__

#include "dsa/BiTNode.hpp"
#include <QDebug>
#include <functional>

namespace dsa {

/// \brief binary search tree template
template <Comparable T> class BST {

public:
  /// \brief default constructor
  BST() = default;

  virtual ~BST() {
    int const ret = clear(_root);
    Q_ASSERT(ret == _size);
  }

  /// \brief search the node, readonly
  ///
  /// also the function set the _hit, which is
  /// designed for later insertion of deletion
  ///
  /// \param val the value to search for
  /// \return return the refernce of the node found
  virtual BiTNode<T> *&search(T const &val);

  /// \brief insert a node
  ///
  /// return the pointer to the node inserted,
  /// no matter whether the value existed or not
  ///
  /// \param val the value to insert
  /// \return pointer to the node inserted
  virtual BiTNode<T> *insert(T const &val);

  /// \brief delete a node
  ///
  /// return whether or not val is deleted
  /// \param val the value to delete
  /// \return success or fail
  virtual bool erase(T const &val);

  /// \brief judge node in tree
  bool exist(BiTNode<T> const *target) const;

  /// \brief const getter for root
  inline BiTNode<T> const *root() const { return _root; }

  /// \brief const getter for tree _size
  ///
  /// it record the number of nodes in the tree
  /// \return the size of the tree
  inline int size() const {
    /// assertion of the size
    Q_ASSERT((!_size && !_root) || (_size && _root));
    return _size;
  };

  /// \brief return true the tree is empty
  /// \return true when the tree is empty
  inline bool empty() const {
    /// assertion of the size
    Q_ASSERT((!_size && !_root) || (_size && _root));
    return !_size;
  }

  /// \brief getter for the tree height
  /// \return the size of the tre
  inline int height() const { return BiTNode<T>::height(root()); }

  /// \brief mid order traverse
  /// readonly
  /// \param f visit function for data
  void mid_traverse(std::function<void(T const &data)> f) const;

  /// \brief mid order traverse
  /// readonly
  /// \param f visit function for node
  void mid_traverse(std::function<void(BiTNode<T> const *node)> f) const;

  /// \brief post order traverse
  /// readonly
  /// \param f visit function for node
  void post_traverse(std::function<void(BiTNode<T> const *node)> f) const;

protected:
  /// \brief clear the tree rooted as rt
  ///
  /// \param rt the root of the subtree to clear
  /// \return return the node it clears
  int clear(BiTNode<T> *rt);

  /// \brief mid traverse
  /// readonly
  /// \param rt the root of the subtree to visit
  /// \param f visit function for data
  void mid_traverse(std::function<void(T const &data)> f,
                    BiTNode<T> const *rt) const;

  /// \brief mid traverse
  /// \param rt the root of the subtree to visit
  /// \param f visit function for data
  void mid_traverse(std::function<void(T &data)> f, BiTNode<T> *rt);

  /// \brief mid traverse
  /// \param rt the root of the subtree to visit
  /// \param f visit function for node
  void mid_traverse(std::function<void(BiTNode<T> *node)> f, BiTNode<T> *rt);

  /// \brief mid traverse
  /// readonly
  /// \param rt the root of the subtree to visit
  /// \param f visit function for node
  void mid_traverse(std::function<void(BiTNode<T> const *node)> f,
                    BiTNode<T> const *rt) const;

  /// \brief post order traverse
  /// readonly
  /// \param rt the root of the subtree to visit
  /// \param f visit function for node
  void post_traverse(std::function<void(BiTNode<T> const *node)> f,
                     BiTNode<T> const *rt) const;

  /// \brief helper function
  ///
  /// set hot as the father of the node deleted, and delete
  /// the node at target
  ///
  /// \param target refernce to the node to delete
  /// \param hot the father of the node to delete
  bool erase_at(BiTNode<T> *&target, BiTNode<T> *&hot);

  /// \brief check if target exist in subtree rt
  ///
  /// \param rt the root of the subtree
  /// \param target the node to check
  /// \return return true when exist
  bool exist(BiTNode<T> const *target, BiTNode<T> const *rt) const;

protected:
  /// \brief record the node number of the tree
  int _size = 0;

  /// \brief record the parent of the node just searched
  mutable BiTNode<T> *_hit = nullptr;

  /// \brief the root of the tree
  BiTNode<T> *_root = nullptr;
};

}; // namespace dsa

// implementation
namespace dsa {

template <Comparable T> int BST<T>::clear(BiTNode<T> *rt) {
  if (rt == nullptr)
    return 0;

  int const l = clear(rt->_left);
  int const r = clear(rt->_right);
  delete rt;
  return l + r + 1;
}

template <Comparable T>
bool BST<T>::exist(BiTNode<T> const *target, BiTNode<T> const *rt) const {
  if (target == nullptr || rt == nullptr)
    return false;
  // find recursively
  return rt == target || exist(target, rt->left()) ||
         exist(target, rt->right());
}

template <Comparable T> bool BST<T>::exist(BiTNode<T> const *target) const {
  return exist(target, this->root());
}

template <Comparable T> BiTNode<T> *&BST<T>::search(T const &val) {

  // tree empty or just hit the root
  if (empty() || _root->data() == val) {
    qDebug() << "Hit at root\t" << "Empty: " << empty();
    _hit = nullptr; // hit at nullptr
    return _root;
  }

  // the tree is not empty
  _hit = _root;
  do {
    BiTNode<T> *&v = val < _hit->data() ? _hit->_left : _hit->_right;
    if (v == nullptr || val == v->data()) {
      // when reach the leaf node, or hit the node
      qDebug() << "found " << (v ? "YES" : "NO");
      return v;
    }

    _hit = v; // go down the tree
  } while (1);

  Q_ASSERT(0); // should not reach here
  return _hit;
}

template <Comparable T> BiTNode<T> *BST<T>::insert(T const &val) {
  BiTNode<T> *&v = search(val);
  if (v) {
    // val already exist in the tree
    return v;
  }

  // increase the size
  _size++;

  // now v is nullptr, _hit point to the parent
  // change the value of v
  v = new (std::nothrow) BiTNode<T>(val, _hit);

  Q_ASSERT(v);

  // update the height above
  v->update_height_above();

  return v;
}

template <Comparable T>
bool BST<T>::erase_at(BiTNode<T> *&target, BiTNode<T> *&hot) {
  Q_ASSERT(target);

  // no left child
  BiTNode<T> *removed = target; // the one to be remove

  BiTNode<T> *sub = nullptr;
  //
  if (!target->left()) {
    sub = target->_right;
    target = target->_right;
  }
  // no right child
  else if (!target->right()) {
    sub = target->_left;
    target = target->_left;
  }
  // no child
  else {
    removed = target->succ();
    std::swap(removed->_data, target->_data);
    // as a succ, when left child and right child both exists
    // removed might be
    // 1. a left child
    // 2. a right child, when succ->parrent == target

    if (removed->is_left()) {
      // removed as lchild
      Q_ASSERT(removed->parent());
      sub = removed->_right;

      removed->_parent->_left = sub;
    } else {
      // removed as rchild
      sub = removed->_right;
      // removed has no left child
      Q_ASSERT(!removed->_left);

      removed->_parent->_right = sub;
    }
  }
  // hot point to the parent of the removed
  hot = removed->_parent;
  if (sub)
    sub->_parent = hot;

  delete removed;
  return true;
}

template <Comparable T> bool BST<T>::erase(T const &val) {
  BiTNode<T> *&v = search(val);
  if (v == nullptr) {
    // the val does not exist
    qDebug() << "Deletion Failed";
    return false;
  }

  // if there is only one child
  // v is not nullptr
  erase_at(v, _hit);
  _size--;
  _hit->update_height_above();
  return true;
}

template <Comparable T>
void BST<T>::mid_traverse(std::function<void(T const &data)> f,
                          BiTNode<T> const *rt) const {
  if (!rt)
    return;

  mid_traverse(f, rt->left());
  f(rt->data());
  mid_traverse(f, rt->right());
}
template <Comparable T>
void BST<T>::post_traverse(std::function<void(BiTNode<T> const *node)> f,
                           BiTNode<T> const *rt) const {
  if (!rt)
    return;

  mid_traverse(f, rt->left());
  mid_traverse(f, rt->right());
  f(rt);
}

template <Comparable T>
void BST<T>::post_traverse(
    std::function<void(BiTNode<T> const *node)> f) const {
  if (empty())
    return;
  post_traverse(f, root());
}

template <Comparable T>
void BST<T>::mid_traverse(std::function<void(T &data)> f, BiTNode<T> *rt) {
  if (!rt)
    return;

  mid_traverse(f, rt->_left);
  f(rt->_data);
  mid_traverse(f, rt->_right);
}

template <Comparable T>
void BST<T>::mid_traverse(std::function<void(BiTNode<T> *node)> f,
                          BiTNode<T> *rt) {
  if (!rt)
    return;

  mid_traverse(f, rt->_left);
  f(rt);
  mid_traverse(f, rt->_right);
}

template <Comparable T>
void BST<T>::mid_traverse(std::function<void(BiTNode<T> const *node)> f,
                          BiTNode<T> const *rt) const {
  if (!rt)
    return;

  mid_traverse(f, rt->left());
  f(rt);
  mid_traverse(f, rt->right());
}

template <Comparable T>
void BST<T>::mid_traverse(std::function<void(BiTNode<T> const *node)> f) const {
  if (empty())
    return;
  mid_traverse(f, root());
}

template <Comparable T>
void BST<T>::mid_traverse(std::function<void(T const &data)> f) const {
  if (empty())
    return;
  mid_traverse(f, root());
}

} // namespace dsa
#endif
