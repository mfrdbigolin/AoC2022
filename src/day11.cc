// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Eleven, Monkey in the Middle.

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct Monkey {
  std::vector<long> starting_items;
  std::function<long(long)> operation;
  std::array<int, 3> test;
};

long solve(std::vector<Monkey> monkeys, int round_number = 20, int relief = 3) {
  auto monkey_number = monkeys.size();

  // This will act as a limiting factor to keep the worry levels from
  // overflowing. The product of all divisors retains the modularity of its
  // terms.
  long divisor_product = 1;
  std::vector<std::vector<long>> monkey_items{};
  for (auto monkey : monkeys) {
    monkey_items.push_back(monkey.starting_items);
    divisor_product *= monkey.test[0];
  }

  std::vector<long> inspections(monkey_number);
  for (auto round = 0; round < round_number; ++round) {
    for (size_t monkey_i = 0; monkey_i < monkey_number; ++monkey_i) {
      auto operation = monkeys[monkey_i].operation;
      auto [divisor, true_case, false_case] = monkeys[monkey_i].test;

      auto items = monkey_items[monkey_i];
      for (auto item : items) {
        auto worry_level = (operation(item) / relief) % divisor_product;

        auto receiver = worry_level % divisor == 0 ? true_case : false_case;

        monkey_items[receiver].push_back(worry_level);
      }

      inspections[monkey_i] += items.size();
      monkey_items[monkey_i].clear();
    }
  }

  std::sort(inspections.begin(), inspections.end());
  long monkey_business =
      inspections[monkey_number - 1] * inspections[monkey_number - 2];

  return monkey_business;
}

const std::regex NUMBER_REGEX(R"(\d+)");
const std::regex OPERATION_REGEX(R"(new = old (\+|\*) (\d+|old))");

std::vector<Monkey> parse_monkeys(std::string raw_data) {
  std::vector<Monkey> monkeys{};

  std::istringstream ss{raw_data};
  std::string line{};
  while (ss.rdbuf()->in_avail() != 0) {
    // Skip monkey header.
    std::getline(ss, line);

    std::getline(ss, line);
    std::vector<long> starting_items{};
    std::smatch match_items;
    while (std::regex_search(line, match_items, NUMBER_REGEX)) {
      starting_items.push_back(std::stoi(match_items.str()));
      line = match_items.suffix();
    }

    std::getline(ss, line);
    char symbol = '\0';
    std::variant<int, std::string> oper{};
    std::smatch match_operation;
    if (std::regex_search(line, match_operation, OPERATION_REGEX)) {
      symbol = match_operation[1].str()[0];

      try {
        oper = std::stoi(match_operation[2].str());
      } catch (const std::invalid_argument &) {
        oper = match_operation[2].str();
      }
    }

    std::function<long(long)> operation = [symbol, oper](long item) {
      int oper_value = item;

      if (std::holds_alternative<int>(oper)) {
        oper_value = std::get<int>(oper);
      }

      if (symbol == '+') {
        return item + oper_value;
      } else {
        return item * oper_value;
      }
    };

    int divisor{-1}, true_case{-1}, false_case{-1};
    std::smatch match_test;

    std::getline(ss, line);
    if (std::regex_search(line, match_test, NUMBER_REGEX)) {
      divisor = std::stoi(match_test.str());
    }

    std::getline(ss, line);
    if (std::regex_search(line, match_test, NUMBER_REGEX)) {
      true_case = std::stoi(match_test.str());
    }

    std::getline(ss, line);
    if (std::regex_search(line, match_test, NUMBER_REGEX)) {
      false_case = std::stoi(match_test.str());
    }

    std::array<int, 3> test{divisor, true_case, false_case};

    // Newline.
    std::getline(ss, line);

    struct Monkey monkey {
      starting_items, operation, test
    };
    monkeys.push_back(monkey);
  }

  return monkeys;
}

void day11(std::string input_file) {
  auto monkeys = parse_monkeys(input_file);

  std::cout << solve(monkeys) << std::endl;
  std::cout << solve(monkeys, 10000, 1) << std::endl;
}
