// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "tree.h"

void printVector(const std::vector<char>& vec) {
  for (char c : vec)
    std::cout << c;
  std::cout << "\n";
}

int factorial(int n) {
  int res = 1;
  for (int i = 2; i <= n; ++i)
    res *= i;
  return res;
}

int main() {
  std::srand(static_cast<unsigned>(std::time(0)));

  std::vector<char> base = {'1', '2', '3'};
  PMTree tree(base);

  std::cout << "All permutations for {1,2,3}:\n";
  auto all = getAllPerms(tree);
  for (const auto& p : all)
    printVector(p);

  std::cout << "\ngetPerm1 (num 4): ";
  printVector(getPerm1(tree, 4));

  std::cout << "getPerm2 (num 4): ";
  printVector(getPerm2(tree, 4));

  std::ofstream file("result/data.csv");
  file << "n,getAllPerms,getPerm1,getPerm2\n";

  std::cout << "\nBenchmark (n = 3 to 8):\n";

  for (int n = 3; n <= 8; ++n) {
    std::vector<char> input;
    for (int i = 0; i < n; ++i)
      input.push_back('a' + i);

    PMTree t(input);
    int total = factorial(n);
    int num = std::rand() % total + 1;

    auto t1_start = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto t1_end = std::chrono::high_resolution_clock::now();
    double time1 = std::chrono::duration_cast<std::chrono::microseconds>(
                     t1_end - t1_start)
                     .count() /
                   1000.0;

    auto t2_start = std::chrono::high_resolution_clock::now();
    getPerm1(t, num);
    auto t2_end = std::chrono::high_resolution_clock::now();
    double time2 = std::chrono::duration_cast<std::chrono::microseconds>(
                     t2_end - t2_start)
                     .count() /
                   1000.0;

    auto t3_start = std::chrono::high_resolution_clock::now();
    getPerm2(t, num);
    auto t3_end = std::chrono::high_resolution_clock::now();
    double time3 = std::chrono::duration_cast<std::chrono::microseconds>(
                     t3_end - t3_start)
                     .count() /
                   1000.0;

    std::cout << "n = " << n
              << " | getAllPerms = " << time1 << " ms"
              << " | getPerm1 = " << time2 << " ms"
              << " | getPerm2 = " << time3 << " ms\n";

    file << n << "," << time1 << "," << time2 << "," << time3 << "\n";
  }

  file.close();
  return 0;
}
