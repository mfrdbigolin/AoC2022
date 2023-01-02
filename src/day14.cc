// Copyright (C) 2023 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Fourteen, Regolith Reservoir.

#include "utils.hh"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

enum class Element { Air, Rock, Sand };

int solve(Matrix<Element> cave, bool has_ground_floor = false) {
  auto [height, width] = cave.sizes();
  int count = 0;

  bool fallen_or_blocked = false;
  while (!fallen_or_blocked) {
    size_t sand_x{500}, sand_y{0};

    bool at_rest = false;
    while (!at_rest) {
      if (sand_x == width - 1 || sand_y == height - 1) {
        if (has_ground_floor) {
          cave(sand_y, sand_x) = Element::Sand;
          count += 1;
        }

        fallen_or_blocked = !has_ground_floor;
        break;
      }

      if (cave(sand_y + 1, sand_x) != Element::Air) {
        if (cave(sand_y + 1, sand_x - 1) == Element::Air) {
          sand_x -= 1;
        } else if (cave(sand_y + 1, sand_x + 1) == Element::Air) {
          sand_x += 1;
        } else {
          cave(sand_y, sand_x) = Element::Sand;
          count += 1;

          at_rest = true;
          fallen_or_blocked = sand_x == 500 && sand_y == 0;
        }
      }

      sand_y += 1;
    }
  }

  return count;
}

const std::regex POINT_REGEX(R"((\d+),(\d+))");

Matrix<Element> parse_rocks(std::string raw_structures) {
  int width{-1}, height{-1};

  // First go through the rock structures to determine the extent of the
  // formations, later used to create the cave matrix, and to parse and store
  // these structures.
  std::vector<std::vector<std::pair<int, int>>> rock_structures{};
  std::istringstream ss{raw_structures};
  std::string line_path{};
  while (std::getline(ss, line_path)) {
    std::vector<std::pair<int, int>> path{};
    std::pair<int, int> previous{0, 0};

    std::smatch match_point;
    while (std::regex_search(line_path, match_point, POINT_REGEX)) {
      auto rock_x = std::stoi(match_point[1].str());
      auto rock_y = std::stoi(match_point[2].str());

      width = std::max(width, rock_x);
      height = std::max(height, rock_y);

      path.push_back(
          std::make_pair(rock_x - previous.first, rock_y - previous.second));
      previous = std::make_pair(rock_x, rock_y);
      line_path = match_point.suffix();
    }

    rock_structures.push_back(path);
  }

  // Guarantees that there will be space for part II.
  Matrix<Element> cave(height + 2, width + height + 2);

  for (auto structure : rock_structures) {
    auto [cur_x, cur_y] = structure[0];
    for (size_t i = 1; i < structure.size(); ++i) {
      auto [diff_x, diff_y] = structure[i];
      auto [dest_x, dest_y] = std::make_pair(cur_x + diff_x, cur_y + diff_y);

      while (cur_x != dest_x || cur_y != dest_y) {
        cave(cur_y, cur_x) = Element::Rock;

        cur_x += signal(diff_x);
        cur_y += signal(diff_y);
      }
      cave(cur_y, cur_x) = Element::Rock;
    }
  }

  return cave;
}

void day14(std::string input_file) {
  auto cave = parse_rocks(input_file);

  std::cout << solve(cave) << std::endl;
  std::cout << solve(cave, true) << std::endl;
}
