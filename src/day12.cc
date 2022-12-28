// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Twelve, Hill Climbing Algorithm.

#include "utils.hh"

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Arbitrary integer constant to represent infinity.
const int INFINITY = 0x3f3f3f3f;

const std::array<std::pair<int, int>, 4> MOVES{
    std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, -1),
    std::make_pair(0, 1)};

int find_shortest_path(Matrix<int> heightmap, std::pair<int, int> source,
                       std::pair<int, int> destiny) {
  auto [num_rows, num_cols] = heightmap.sizes();

  int src_idx = bounded_pair(source.second, source.first, num_cols);
  int dest_idx = bounded_pair(destiny.second, destiny.first, num_cols);

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      to_visit;

  std::vector<int> dist(num_rows * num_cols, INFINITY);
  std::vector<bool> visited(num_rows * num_cols, false);

  to_visit.push(std::make_pair(0, src_idx));
  dist[src_idx] = 0;

  auto cur_idx = src_idx;
  while (cur_idx != dest_idx && !to_visit.empty()) {
    cur_idx = to_visit.top().second;
    to_visit.pop();
    visited[cur_idx] = true;

    auto i = cur_idx / num_cols;
    auto j = cur_idx % num_cols;
    for (auto [di, dj] : MOVES) {
      auto ni = i + di, nj = j + dj;
      bool cantPass = heightmap(i, j) < heightmap(ni, nj) - 1;
      if (cantPass || ni < 0 || ni >= num_rows || nj < 0 || nj >= num_cols) {
        continue;
      }

      auto adj_idx = bounded_pair(nj, ni, num_cols);

      auto rel_dist = dist[cur_idx] + 1;

      if (!visited[adj_idx] && rel_dist < dist[adj_idx]) {
        dist[adj_idx] = rel_dist;
        to_visit.push(std::make_pair(dist[adj_idx], adj_idx));
      }
    }
  }

  return dist[dest_idx];
}

int solve(Matrix<int> heightmap, int max_starting_elevation = -1) {
  auto [num_rows, num_cols] = heightmap.sizes();

  std::vector<std::pair<int, int>> sources{};
  std::pair<int, int> destiny{-1, -1};
  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_cols; ++j) {
      auto height = heightmap(i, j);

      if (height <= max_starting_elevation) {
        sources.push_back(std::make_pair(i, j));
      } else if (height == 'z' - 'a' + 1) {
        destiny = std::make_pair(i, j);
      }
    }
  }

  int shortest_dist = INFINITY;
  for (auto source : sources) {
    auto dist = find_shortest_path(heightmap, source, destiny);

    shortest_dist = std::min(shortest_dist, dist);
  }

  return shortest_dist;
}

Matrix<int> parse_heightmap(std::string raw_map) {
  auto num_rows = std::count(raw_map.begin(), raw_map.end(), '\n') + 1;
  auto num_cols = raw_map.find('\n');
  Matrix<int> heightmap(num_rows, num_cols);

  std::istringstream ss{raw_map};
  std::string row{};
  auto i = 0;
  while (std::getline(ss, row)) {
    for (auto height : row) {
      if (height == 'S') {
        heightmap(i++) = -1;
      } else if (height == 'E') {
        heightmap(i++) = 'z' - 'a' + 1;
      } else {
        heightmap(i++) = height - 'a';
      }
    }
  }

  return heightmap;
}

void day12(std::string input_file) {
  auto heightmap = parse_heightmap(input_file);

  std::cout << solve(heightmap) << std::endl;
  std::cout << solve(heightmap, 0) << std::endl;
}
