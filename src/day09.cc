// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Nine, Rope Bridge.

#include "utils.hh"

#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Maximum number of storable points along an axis of the cartesian plane.
const int MAX_SIZE = 600;

int solve(std::vector<std::pair<int, int>> motions, int knots = 2) {
  std::vector<bool> visited(MAX_SIZE * MAX_SIZE, false);
  std::vector<std::array<int, 2>> rope(knots, std::array<int, 2>{0, 0});

  visited[pairing(0, 0)] = true;
  int visited_count = 1;

  for (auto motion : motions) {
    auto [motion_x, motion_y] = motion;

    while (motion_x != 0 || motion_y != 0) {
      rope[0][0] += signal(motion_x);
      rope[0][1] += signal(motion_y);

      for (auto i = 1; i < knots; ++i) {
        int delta_x = rope[i - 1][0] - rope[i][0];
        int delta_y = rope[i - 1][1] - rope[i][1];

        if (std::abs(delta_x) == 2 || std::abs(delta_y) == 2) {
          rope[i][0] += signal(delta_x);
          rope[i][1] += signal(delta_y);
        }
      }

      auto id = pairing(rope[knots - 1][0], rope[knots - 1][1]);
      if (!visited[id]) {
        visited[id] = true;
        visited_count += 1;
      }

      motion_x += -signal(motion_x);
      motion_y += -signal(motion_y);
    }
  }

  return visited_count;
}

std::vector<std::pair<int, int>> parse_motions(std::string raw_data) {
  std::vector<std::pair<int, int>> motions{};

  std::istringstream ss{raw_data};
  std::string step{};
  while (std::getline(ss, step)) {
    auto direction = step[0];
    auto magnitude = std::stoi(step.substr(2));

    std::pair<int, int> orientation{};
    switch (direction) {
    case 'R':
      orientation = std::make_pair(0, magnitude);
      break;
    case 'L':
      orientation = std::make_pair(0, -magnitude);
      break;
    case 'D':
      orientation = std::make_pair(magnitude, 0);
      break;
    case 'U':
      orientation = std::make_pair(-magnitude, 0);
    }

    motions.push_back(orientation);
  }

  return motions;
}

void day09(std::string input_file) {
  auto motions = parse_motions(input_file);

  std::cout << solve(motions) << std::endl;
  std::cout << solve(motions, 10) << std::endl;
}
