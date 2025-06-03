// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <algorithm>

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
  if (node->val != '*') path.push_back(node->val);

  if (node->children.empty()) {
    permutations.push_back(path);
  } else {
    for (const auto& child : node->children) {
      traverse(child, path);
    }
  }

  if (node->val != '*') path.pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPerms() {
  permutations.clear();
  std::vector<char> path;
  traverse(root, path);
  return permutations;
}

std::vector<char> PMTree::getPerm1(int num) {
  auto all = getAllPerms();
  if (num <= 0 || num > (int)all.size()) return {};
  return all[num - 1];
}

std::vector<char> PMTree::getPerm2(int num) {
  std::vector<char> result;
  std::shared_ptr<Node> current = root;
  int index = num - 1;

  std::vector<int> factorials(10, 1);
  for (int i = 1; i < 10; ++i)
    factorials[i] = factorials[i - 1] * i;

  int n = root->children.size();
  std::vector<char> used;

  while (!current->children.empty()) {
    int f = factorials[n - 1];
    int pos = index / f;
    index %= f;
    std::sort(current->children.begin(), current->children.end(), [](auto a, auto b) {
      return a->val < b->val;
    });

    current = current->children[pos];
    result.push_back(current->val);
    --n;
  }

  return result;
}
