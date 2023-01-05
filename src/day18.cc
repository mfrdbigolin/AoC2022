// Copyright (C) 2023 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Eighteen, Boiling Boulders.

#include "utils.hh"

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// All possible positions water can flow, does not includes diagonals.
const std::vector<std::array<int, 3>> MOVES{{1, 0, 0},  {-1, 0, 0}, {0, 1, 0},
                                            {0, -1, 0}, {0, 0, 1},  {0, 0, -1}};

int calculate_space_length(std::vector<std::array<int, 3>> cubes) {
  int max_axis = 0;

  for (auto [x, y, z] : cubes) {
    max_axis = std::max(max_axis, std::max(x, std::max(y, z)));
  }

  return max_axis + 1;
}

int solve1(std::vector<std::array<int, 3>> cubes) {
  auto space_length = calculate_space_length(cubes);
  std::vector<bool> used_cubes(space_length * space_length * space_length);

  int surface_count = 6 * cubes.size();

  for (auto [x, y, z] : cubes) {
    used_cubes[bounded_triple(x, y, z, space_length)] = true;

    for (auto [dx, dy, dz] : MOVES) {
      int nx{x + dx}, ny{y + dy}, nz{z + dz};

      if ((nx >= 0 && nx < space_length) && (ny >= 0 && ny < space_length) &&
          (nz >= 0 && nz < space_length)) {
        surface_count -=
            2 * used_cubes[bounded_triple(nx, ny, nz, space_length)];
      }
    }
  }

  return surface_count;
}

int solve2(std::vector<std::array<int, 3>> cubes) {
  // Allocate space for cubes plus additional padding.
  auto space_length = calculate_space_length(cubes) + 2;
  std::vector<bool> used_cubes(space_length * space_length * space_length);

  // Insert padding, by shifting all positions by one, to allow the checking of
  // extreme surfaces.
  for (auto [x, y, z] : cubes) {
    used_cubes[bounded_triple(x + 1, y + 1, z + 1, space_length)] = true;
  }

  int surface_count = 0;

  // An ordinary flooding algorithm to count the outside surfaces is used here.
  std::set<std::array<int, 3>> visited{};
  std::queue<std::array<int, 3>> go_to{};
  go_to.push({0, 0, 0});
  visited.insert({0, 0, 0});
  while (!go_to.empty()) {
    auto [x, y, z] = go_to.front();
    go_to.pop();

    for (auto [dx, dy, dz] : MOVES) {
      int nx{x + dx}, ny{y + dy}, nz{z + dz};

      if ((nx >= 0 && nx < space_length) && (ny >= 0 && ny < space_length) &&
          (nz >= 0 && nz < space_length)) {
        int index = bounded_triple(nx, ny, nz, space_length);
        bool has_droplet = used_cubes[index];

        surface_count += has_droplet;

        if (!has_droplet && visited.find({nx, ny, nz}) == visited.end()) {
          visited.insert({nx, ny, nz});
          go_to.push({nx, ny, nz});
        }
      }
    }
  }

  return surface_count;
}

const std::regex CUBE_REGEX(R"((\d+),(\d+),(\d+))");

std::vector<std::array<int, 3>> parse_cubes(std::string raw_cubes) {
  std::vector<std::array<int, 3>> cubes{};

  std::istringstream ss{raw_cubes};
  std::string raw_cube{};
  while (std::getline(ss, raw_cube)) {
    std::array<int, 3> cube{};

    std::smatch match_cube{};
    if (std::regex_match(raw_cube, match_cube, CUBE_REGEX)) {
      auto x = std::stoi(match_cube[1].str());
      auto y = std::stoi(match_cube[2].str());
      auto z = std::stoi(match_cube[3].str());

      cube = {x, y, z};
    }

    cubes.push_back(cube);
  }

  return cubes;
}

void day18(std::string input_file) {
  auto cubes = parse_cubes(input_file);

  std::cout << solve1(cubes) << std::endl;
  std::cout << solve2(cubes) << std::endl;
}
