// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

struct Node {
  char val;
  std::vector<std::shared_ptr<Node>> children;
  explicit Node(char value);
};

class PMTree {
 private:
  std::shared_ptr<Node> root;
  std::vector<std::vector<char>> permutations;

  void build(std::shared_ptr<Node> node, std::vector<char> remaining);
  void traverse(std::shared_ptr<Node> node, std::vector<char>& path);

 public:
  explicit PMTree(const std::vector<char>& items);
  std::shared_ptr<Node> getRoot();
  std::vector<std::vector<char>> getAllPerms();
};

// Глобальные функции:
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
