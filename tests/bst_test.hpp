
#pragma once
#ifndef __BST_TEST_HPP__
#define __BST_TEST_HPP__
#include "dsa/BST.hpp"
#include "dsa/QBVNode.hpp"
using dsa::BST;
using dsa::QBVNode;
using BST_type = BST<QBVNode>;
using node = QBVNode;

inline const char *split = "=========================================\n";

class BSTtest {
public:
  BSTtest(BST_type *tree, int const N = 10);

  void run_test();
  void print_property() const;

private:
  void insert_test();
  void delete_test();
  void search_test();
  void generate();
  static void print(node const &v);
  inline static node get_node(int const number) {
    return node(std::to_string(number).c_str());
  }

private:
  int const N;
  std::vector<int> nums;
  BST_type *tree;
};
#endif
