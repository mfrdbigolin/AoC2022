// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Five, Supply Stacks.

#include <algorithm>
#include <cstddef>
#include <deque>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using CratePile = std::deque<char>;
using Procedure = std::tuple<int, int, int>;

const std::regex PROCEDURE_REGEX(R"(move (\d+) from (\d+) to (\d+))");

std::vector<CratePile> parse_piles(std::string raw_data) {
  // Find the number of piles with the first line’s character number.
  auto pile_number = (static_cast<int>(raw_data.find("\n")) + 1) / 4;

  std::vector<CratePile> crate_piles(pile_number);

  std::istringstream ss{raw_data};
  std::string line{};
  while (std::getline(ss, line) && line != "") {
    for (size_t i = 1; i < line.size(); i += 4) {
      if (line[i - 1] == '[' && line[i + 1] == ']') {
        auto pile_index = (i - 1) / 4;

        crate_piles[pile_index].push_back(line[i]);
      }
    }
  }

  return crate_piles;
}

std::vector<Procedure> parse_procedure(std::string raw_data) {
  std::istringstream ss{raw_data};
  std::string step_line{};

  // Skip the starting position and go straight to the procedure.
  while (std::getline(ss, step_line) && step_line != "")
    ;

  std::vector<std::tuple<int, int, int>> procedure{};

  while (std::getline(ss, step_line)) {
    int quantity{-1}, src{-1}, dest{-1};

    std::smatch match_assignment;
    if (std::regex_match(step_line, match_assignment, PROCEDURE_REGEX)) {
      quantity = stoi(match_assignment[1].str());
      src = stoi(match_assignment[2].str());
      dest = stoi(match_assignment[3].str());
    }

    std::tuple<int, int, int> step{quantity, src, dest};
    procedure.push_back(step);
  }

  return procedure;
}

std::string get_top_crates(std::vector<CratePile> crate_piles) {
  std::string top_crates{""};

  for (auto pile : crate_piles) {
    top_crates += pile[0];
  }

  return top_crates;
}

std::string solve(std::vector<CratePile> crate_piles,
                  std::vector<Procedure> procedure, bool reverse_order = true) {
  auto rearranged_piles = crate_piles;

  for (auto step : procedure) {
    auto quantity = std::get<0>(step);
    auto src = std::get<1>(step);
    auto dest = std::get<2>(step);

    auto &src_pile = rearranged_piles[src - 1];
    auto &dest_pile = rearranged_piles[dest - 1];

    std::vector<char> moved_crates(src_pile.begin(),
                                   src_pile.begin() + quantity);

    if (reverse_order) {
      std::reverse(moved_crates.begin(), moved_crates.end());
    }

    dest_pile.insert(dest_pile.begin(), moved_crates.begin(),
                     moved_crates.end());
    src_pile.erase(src_pile.begin(), src_pile.begin() + quantity);
  }

  return get_top_crates(rearranged_piles);
}

void day05(std::string input_file) {
  auto procedure = parse_procedure(input_file);
  auto crate_piles = parse_piles(input_file);

  std::cout << solve(crate_piles, procedure) << std::endl;
  std::cout << solve(crate_piles, procedure, false) << std::endl;
}
