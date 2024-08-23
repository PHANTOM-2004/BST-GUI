
#pragma once
#ifndef __BST_TEST_HPP__
#define __BST_TEST_HPP__
#include "dsa/BST.hpp"
#include "qbst/QVBNode.hpp"

using dsa::BST;
using qbst::QVBNode;
using BST_type = BST<QVBNode>;
using node = QVBNode;

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
  void position_test();
  void generate();
  static void print(node const &v);
  static node get_node(int const number) {
    return node(std::to_string(number).c_str());
  }

private:
  int const N;
  std::vector<int> nums;
  BST_type *tree;

  static constexpr int output_limit = 10000;
};
#endif
