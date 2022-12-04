// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Three, Rucksack Reorganization.

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static int find_common_item(std::vector<std::vector<int>> storages,
                            int element_range) {
  std::vector<size_t> item_counter(element_range, 0);

  for (auto storage : storages) {
    std::sort(storage.begin(), storage.end());

    auto new_end = std::unique(storage.begin(), storage.end());
    storage.erase(new_end, storage.end());

    for (auto item : storage) {
      item_counter[item - 1] += 1;

      if (item_counter[item - 1] == storages.size()) {
        return item;
      }
    }
  }

  return -1;
}

static int solve1(std::vector<std::vector<int>> inventory) {
  auto priority_sum = 0;

  for (auto rucksack : inventory) {
    auto middle = rucksack.begin() + rucksack.size() / 2;

    auto first_compartment = std::vector(rucksack.begin(), middle);
    auto second_compartment = std::vector(middle, rucksack.end());
    auto whole_sack = std::vector({first_compartment, second_compartment});

    auto common_item = find_common_item(whole_sack, 52);

    priority_sum += common_item;
  }

  return priority_sum;
}

static int solve2(std::vector<std::vector<int>> inventory) {
  auto priority_sum = 0;

  for (size_t i = 0; i < inventory.size(); i += 3) {
    auto rucksack_1 = inventory[i];
    auto rucksack_2 = inventory[i + 1];
    auto rucksack_3 = inventory[i + 2];

    auto group_rucksack = std::vector({rucksack_1, rucksack_2, rucksack_3});

    auto badge = find_common_item(group_rucksack, 52);

    priority_sum += badge;
  }

  return priority_sum;
}

static std::vector<std::vector<int>> parse_input(std::string raw_data) {
  std::istringstream ss{raw_data};

  std::vector<std::vector<int>> inventory{};
  std::string rucksack{};
  while (std::getline(ss, rucksack)) {
    std::vector<int> priorities{};

    for (auto item : rucksack) {
      auto priority = item >= 'a' && item <= 'z' ? item - 96 : item - 38;

      priorities.push_back(priority);
    }

    inventory.push_back(priorities);
  }

  return inventory;
}

void day03(std::string input_file) {
  auto inventory = parse_input(input_file);

  std::cout << solve1(inventory) << std::endl;
  std::cout << solve2(inventory) << std::endl;
}
