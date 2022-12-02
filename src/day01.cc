// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day One, Calorie Counting.

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

static std::vector<int> solve(const std::vector<std::vector<int>> calory_list) {
  std::vector<int> summed_calories(calory_list.size(), 0);

  std::transform(calory_list.begin(), calory_list.end(),
                 summed_calories.begin(),
                 [](auto a) { return std::accumulate(a.begin(), a.end(), 0); });

  std::sort(summed_calories.begin(), summed_calories.end(),
            std::greater<int>());

  return std::vector<int>(summed_calories.begin(), summed_calories.begin() + 3);
}

static std::vector<std::vector<int>> parse_input(std::string raw_data) {
  std::istringstream ss{raw_data};
  std::vector<std::vector<int>> input_data{};

  std::string line{};
  std::vector<int> current{};
  while (std::getline(ss, line)) {
    if (line == "") {
      input_data.push_back(current);
      current.clear();

      continue;
    }

    current.push_back(std::stoi(line));
  }

  input_data.push_back(current);

  return input_data;
}

void day01(std::string input_file) {
  auto input_data = parse_input(input_file);

  auto most_calories = solve(input_data);

  auto sol1 = most_calories[0];
  auto sol2 = sol1 + most_calories[1] + most_calories[2];

  std::cout << sol1 << std::endl;
  std::cout << sol2 << std::endl;
}
