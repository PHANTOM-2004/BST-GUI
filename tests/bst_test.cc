#include "bst_test.hpp"
#include <algorithm>
#include <iostream>

BSTtest::BSTtest(BST_type *tree, int const N) : N(N), tree(tree) {
  nums.resize(N);
  // generate random number
  for (auto &i : nums)
    i = std::abs(rand()) % (3 * N);
}

void BSTtest::insert_test() {
  // insert
  for (auto const &i : nums) {
    if (N < 10000)
      std::cout << "insert: " << i << std::endl;

    auto const node_ins = node(std::to_string(i).c_str());
    auto const res = tree->insert(node_ins);
    Q_ASSERT(res->data() == node_ins);
  }
  print_property();
}

void BSTtest::delete_test() {
  int cnt = tree->size();
  // delete
  std::vector<int> vis(N);
  for (int i = 0; i < N;) {
    int const pos = std::abs(rand()) % N;
    if (vis[pos])
      continue;
    i++;
    vis[pos] = 1;

    int const ret = tree->erase(get_node(nums[pos]));

    if (N < 10000) {
      std::cout << "delete: " << nums[pos] << " ";
      std::cout << ret << std::endl;
    }
    cnt -= ret;
  }
  print_property();
  Q_ASSERT(cnt == 0);
}

void BSTtest::search_test() {
  std::sort(nums.begin(), nums.end());

  for (int i = 0; i < 2 * N; i++) {
    int const pos = std::abs(rand()) % N;
    int target = 0;
    bool ans = false;
    if (i & 1) {
      target = nums[pos];
      ans = true;
    } else {
      target = (unsigned)rand();
      ans = std::binary_search(nums.begin(), nums.end(), target);
    }
    bool const ret = !!tree->search(get_node(target));

    if (N < 10000)
      std::cout << (ret ? "YES" : "NO") << '\n';
    Q_ASSERT(ret == ans);
  }
}

void BSTtest::run_test() {
  insert_test();
  search_test();
  delete_test();
}

void BSTtest::print_property() const {
  std::cout << "Mid traverse:\n";
  tree->mid_traverse(print);
  std::cout << "Root: ";
  auto rt = tree->root();
  if (!rt)
    std::cout << "NULL\n";
  else
    print(rt->data());

  std::cout << "Size: " << tree->size() << '\n';
  std::cout << "Height: " << tree->height() << '\n';
  std::cout << split;
}

void BSTtest::print(node const &v) {
  std::cout << v.str().toStdString() << '\n';
};

int main() {
  std::cout << "BST test\n";
  BST_type T1;
  BSTtest test1(&T1, 100000);
  test1.run_test();
}
