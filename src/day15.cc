// Copyright (C) 2023 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Fifteen, Beacon Exclusion Zone.

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Sensor = std::array<std::pair<int, int>, 2>;

// N.b.: I choose to ignore the horizontal boundaries laid out in part II to
// create a nicer solution, because they don’t matter with my input set.

// Uses Klee’s algorithm to calculate the length of merged intervals and to find
// “holes” in this merge.  The second element of the output pair indicates if
// there is a hole.  If yes, returns the x coordinate of the hole along with
// `true`; otherwise, returns the number of positions that cannot contain a
// beacon along with `false`.
std::pair<long, bool> solve1(std::vector<Sensor> sensors, int row = 10) {
  std::vector<std::pair<int, bool>> points{};
  std::set<int> row_beacons{};

  for (auto [sensor, beacon] : sensors) {
    auto [sensor_x, sensor_y] = sensor;
    auto [beacon_x, beacon_y] = beacon;

    auto dist_beacon =
        std::abs(sensor_x - beacon_x) + std::abs(sensor_y - beacon_y);
    auto dist_row = std::abs(sensor_y - row);

    auto diff = std::abs(dist_beacon - dist_row);

    if (dist_beacon >= dist_row) {
      auto start = sensor_x - diff;
      auto end = sensor_x + diff;

      points.push_back(std::make_pair(start, false));
      points.push_back(std::make_pair(end, true));
    }

    if (beacon_y == row) {
      row_beacons.insert(beacon_x);
    }
  }

  std::sort(points.begin(), points.end());

  int result = 0, counter = 1;

  for (size_t i = 1; i < points.size(); ++i) {
    auto lb = row_beacons.lower_bound(points[i - 1].first);

    if (*lb <= points[i].first && lb != end(row_beacons)) {
      result -= 1;
      row_beacons.erase(lb);
    }

    auto diff = points[i].first - points[i - 1].first;

    if (counter == 0 && diff >= 2) {
      return std::make_pair(points[i - 1].first + 1l, true);
    }

    if (counter > 0) {
      result += diff;
    }

    if (points[i].second) {
      --counter;
    } else {
      ++counter;
    }

    result += counter == 0;
  }

  return std::make_pair(result, false);
}

long solve2(std::vector<Sensor> sensors, int upper_bound = 20) {
  for (auto row = 0; row <= upper_bound; ++row) {
    auto [x_coordinate, found_distress_signal] = solve1(sensors, row);

    if (found_distress_signal) {
      return 4000000 * x_coordinate + row;
    }
  }

  return -1;
}

const std::regex POINT_REGEX(R"(x=(-?\d+), y=(-?\d+))");

std::vector<Sensor> parse_sensors(std::string raw_sensors) {
  std::vector<Sensor> sensors{};

  std::istringstream ss{raw_sensors};
  std::string line_sensor{};
  while (std::getline(ss, line_sensor)) {
    std::pair<int, int> sensor{}, beacon{};

    std::smatch match_point{};
    if (std::regex_search(line_sensor, match_point, POINT_REGEX)) {
      auto sensor_x = std::stoi(match_point[1].str());
      auto sensor_y = std::stoi(match_point[2].str());

      sensor = std::make_pair(sensor_x, sensor_y);
    }

    line_sensor = match_point.suffix();

    if (std::regex_search(line_sensor, match_point, POINT_REGEX)) {
      auto beacon_x = std::stoi(match_point[1].str());
      auto beacon_y = std::stoi(match_point[2].str());

      beacon = std::make_pair(beacon_x, beacon_y);
    }

    Sensor sensor_beacon{sensor, beacon};
    sensors.push_back(sensor_beacon);
  }

  return sensors;
}

void day15(std::string input_file) {
  auto sensors = parse_sensors(input_file);

  std::cout << solve1(sensors, 2000000).first << std::endl;
  std::cout << solve2(sensors, 4000000) << std::endl;
}
