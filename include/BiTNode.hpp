/// \file
/// \brief the definition of ther binary tree node
/// only valid when arithmetic type or string/qstring
#pragma once

#ifndef __BITNODE_HPP__
#define __BITNODE_HPP__

#include <QString>
#include <string>
#include <type_traits>

namespace dsa {

template <typename T>
concept BiTNodeType =
    std::is_arithmetic_v<T> || std::is_same_v<T, std::string> ||
    std::is_same_v<T, QString>;

/// \brief Binar Tree Node, only valid when T is arithmetic type or string type
template <typename T>
  requires BiTNodeType<T>
class BiTNode {
  // only instancialize when basic arithmetic type or string

public:
  explicit BiTNode(T const &val);
  inline bool operator<(BiTNode<T> const &other) const;
  inline bool operator<=(BiTNode<T> const &other) const;
  inline bool operator==(BiTNode<T> const &other) const;
  inline T *left() const;
  inline T *right() const;
  inline T *parent() const;

protected:
  T _data;
  T *_parent = nullptr;
  T *_left = nullptr;
  T *_right = nullptr;
};

// implementation
template <typename T>
  requires BiTNodeType<T>
T *BiTNode<T>::left() const {
  return _left;
}

template <typename T>
  requires BiTNodeType<T>
T *BiTNode<T>::right() const {
  return _right;
}

template <typename T>
  requires BiTNodeType<T>
T *BiTNode<T>::parent() const {
  return _parent;
}

template <typename T>
  requires BiTNodeType<T>
BiTNode<T>::BiTNode(T const &val) : _data(val){};

template <typename T>
  requires BiTNodeType<T>
bool BiTNode<T>::operator<(BiTNode<T> const &other) const {
  if constexpr (std::is_arithmetic_v<T>) {
    return this->_data < other._data;
  } else {
    if (this->_data.length() != other._data.length())
      return this->_data.length() < other._data.length();
    return this->_data < other._data;
  }
}

template <typename T>
  requires BiTNodeType<T>
bool BiTNode<T>::operator==(BiTNode<T> const &other) const {
  return this->_data == other._data;
}

template <typename T>
  requires BiTNodeType<T>
bool BiTNode<T>::operator<=(BiTNode<T> const &other) const {
  return *this < other || *this == other;
}

} // namespace dsa
#endif
