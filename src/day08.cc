// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Eight, Treetop Tree House.

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

size_t solve1(std::vector<std::vector<int>> tree_map) {
  // N.B.: this solution assumes that the height of the map equals its width.

  auto size = tree_map.size();
  size_t visible_count = 4 * size - 4;
  std::vector<bool> visible(size * size, false);

  for (size_t i = 1; i < (size - 1); ++i) {
    std::array<int, 4> maxima{// Left maximum
                              tree_map[i][0],
                              // Top maximum
                              tree_map[0][i],
                              // Right maximum
                              tree_map[i][size - 1],
                              // Bottom maximum
                              tree_map[size - 1][i]};

    for (size_t j = 1; j < (size - 1); ++j) {
      std::array<std::pair<size_t, size_t>, 4> moves{
          std::make_pair(i, j), std::make_pair(j, i),
          std::make_pair(i, size - j - 1), std::make_pair(size - j - 1, i)};

      for (auto k = 0; k < 4; ++k) {
        auto row = moves[k].first;
        auto column = moves[k].second;

        if (!visible[size * row + column] &&
            tree_map[row][column] > maxima[k]) {
          visible_count += 1;
          visible[size * row + column] = true;
        }

        maxima[k] = std::max(maxima[k], tree_map[row][column]);
      }
    }
  }

  return visible_count;
}

size_t get_row(std::vector<std::vector<int>> map,
               std::pair<size_t, size_t> start_point,
               std::pair<int, int> direction) {
  auto size = map.size();

  size_t scenic_score = 0;

  auto i = start_point.first;
  auto j = start_point.second;
  auto initial_tree = map[i][j];
  while ((0 < i && i < size - 1) && (0 < j && j < size - 1)) {
    i += direction.first;
    j += direction.second;

    scenic_score += 1;

    if (map[i][j] >= initial_tree) {
      break;
    }
  }

  return scenic_score;
}

const std::vector<std::pair<int, int>> DIRECTIONS{
    std::make_pair(1, 0), std::make_pair(-1, 0), std::make_pair(0, 1),
    std::make_pair(0, -1)};

size_t solve2(std::vector<std::vector<int>> tree_map) {
  auto size = tree_map.size();
  auto max_score = 0;

  for (size_t i = 1; i < (size - 1); ++i) {
    for (size_t j = 1; j < (size - 1); ++j) {
      auto current_point = std::make_pair(i, j);

      auto scenic_score = 1;
      for (auto direction : DIRECTIONS) {
        scenic_score *= get_row(tree_map, current_point, direction);
      }

      max_score = std::max(max_score, scenic_score);
    }
  }

  return max_score;
}

std::vector<std::vector<int>> parse_tree_map(std::string raw_map) {
  std::vector<std::vector<int>> tree_map{};

  std::istringstream ss{raw_map};
  std::string row{};
  while (std::getline(ss, row)) {
    std::vector<int> row_map{};

    for (auto tree_height : row) {
      row_map.push_back(tree_height - '0');
    }

    tree_map.push_back(row_map);
  }

  return tree_map;
}

void day08(std::string input_file) {
  auto tree_map = parse_tree_map(input_file);

  std::cout << solve1(tree_map) << std::endl;
  std::cout << solve2(tree_map) << std::endl;
}
