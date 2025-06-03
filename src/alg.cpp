// Copyright 2022 NNTU-CS
#include "tree.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

Node::Node(char value) : val(value) {}

PMTree::PMTree(const std::vector<char>& items) {
  root = std::make_shared<Node>('*');
  build(root, items);
}

void PMTree::build(std::shared_ptr<Node> node, std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::sort(remaining.begin(), remaining.end());

  for (size_t i = 0; i < remaining.size(); ++i) {
    char current = remaining[i];
    auto child = std::make_shared<Node>(current);
    node->children.push_back(child);

    std::vector<char> next = remaining;
    next.erase(next.begin() + i);

    build(child, next);
  }
}

void PMTree::traverse(std::shared_ptr<Node> node, std::vector<char>& path) {
  if (node->val != '*') {
    path.push_back(node->val);
  }

  if (node->children.empty()) {
    permutations.push_back(path);
  } else {
    for (const auto& child : node->children) {
      traverse(child, path);
    }
  }

  if (node->val != '*') {
    path.pop_back();
  }
}

std::vector<std::vector<char>> PMTree::getAllPerms() {
  permutations.clear();
  std::vector<char> path;
  traverse(root, path);
  return permutations;
}

std::shared_ptr<Node> PMTree::getRoot() {
  return root;
}

// -----------------------------
// Глобальные функции:
// -----------------------------

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = tree.getAllPerms();
  if (num <= 0 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  std::shared_ptr<Node> current = tree.getRoot();
  int index = num - 1;

  std::vector<int> factorials(10, 1);
  for (int i = 1; i < 10; ++i) {
    factorials[i] = factorials[i - 1] * i;
  }

  int n = static_cast<int>(current->children.size());

  while (!current->children.empty()) {
    int f = factorials[n - 1];
    int pos = index / f;
    index %= f;

    std::sort(current->children.begin(), current->children.end(),
              [](const std::shared_ptr<Node>& a,
                 const std::shared_ptr<Node>& b) {
                return a->val < b->val;
              });

    current = current->children[pos];
    result.push_back(current->val);
    --n;
  }

  return result;
}
