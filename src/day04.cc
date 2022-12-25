// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Four, Camp Cleanup.

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using AssignmentPair = std::pair<std::pair<int, int>, std::pair<int, int>>;

const std::regex PAIR_REGEX(R"((\d+)-(\d+),(\d+)-(\d+))");

static int solve1(std::vector<AssignmentPair> assignments) {
  auto number_containments = 0;

  for (AssignmentPair elf_pair : assignments) {
    auto [first_elf, second_elf] = elf_pair;

    bool is_first_contained = first_elf.first >= second_elf.first &&
                              first_elf.second <= second_elf.second;
    bool is_second_contained = second_elf.first >= first_elf.first &&
                               second_elf.second <= first_elf.second;

    number_containments += is_first_contained || is_second_contained;
  }

  return number_containments;
}

static int solve2(std::vector<AssignmentPair> assignments) {
  auto number_overlaps = 0;

  for (AssignmentPair elf_pair : assignments) {
    auto [first_elf, second_elf] = elf_pair;

    number_overlaps += first_elf.second >= second_elf.first &&
                       first_elf.first <= second_elf.second;
  }

  return number_overlaps;
}

static std::vector<AssignmentPair> parse_input(std::string raw_data) {
  std::istringstream ss{raw_data};

  std::vector<AssignmentPair> assignments{};
  std::string elf_pair{};
  while (std::getline(ss, elf_pair)) {
    int first_section_start{-1}, first_section_end{-1};
    int second_section_start{-1}, second_section_end{-1};

    std::smatch match_assignment;
    if (std::regex_match(elf_pair, match_assignment, PAIR_REGEX)) {
      first_section_start = stoi(match_assignment[1].str());
      first_section_end = stoi(match_assignment[2].str());
      second_section_start = stoi(match_assignment[3].str());
      second_section_end = stoi(match_assignment[4].str());
    }

    std::pair first_elf = {first_section_start, first_section_end};
    std::pair second_elf = {second_section_start, second_section_end};
    assignments.push_back({first_elf, second_elf});
  }

  return assignments;
}

void day04(std::string input_file) {
  auto assignments = parse_input(input_file);

  std::cout << solve1(assignments) << std::endl;
  std::cout << solve2(assignments) << std::endl;
}
