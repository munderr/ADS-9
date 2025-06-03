// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include "tree.h"

std::vector<char> generateAlphabet(int n) {
  std::vector<char> v;
  for (int i = 0; i < n; ++i)
    v.push_back('A' + i);
  return v;
}

int getRandomIndex(int max) {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(1, max);
  return dist(rng);
}

int main() {
  std::ofstream out("result/data.csv");
  out << "n,allPerms_ms,perm1_ms,perm2_ms\n";

  for (int n = 3; n <= 8; ++n) {
    std::vector<char> input = generateAlphabet(n);
    PMTree tree(input);

    auto start = std::chrono::high_resolution_clock::now();
    auto all = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    auto timeAll = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    int maxIndex = 1;
    for (int i = 2; i <= n; ++i) maxIndex *= i;
    int randIndex = getRandomIndex(maxIndex);

    start = std::chrono::high_resolution_clock::now();
    auto p1 = getPerm1(tree, randIndex);
    end = std::chrono::high_resolution_clock::now();
    auto timeP1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    auto p2 = getPerm2(tree, randIndex);
    end = std::chrono::high_resolution_clock::now();
    auto timeP2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    out << n << "," << timeAll << "," << timeP1 << "," << timeP2 << "\n";
    std::cout << "n=" << n << " done\n";
  }

  out.close();
  return 0;
}
