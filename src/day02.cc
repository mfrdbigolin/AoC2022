// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Two, Rock Paper Scissors.

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Round = std::pair<int, int>;

enum Outcome { Lose = 1, Draw, Win };

static Outcome find_round_outcome(int opponent_move, int your_move) {
  Outcome round_outcome = Lose;

  if (opponent_move == your_move) {
    round_outcome = Draw;
  } else if ((opponent_move % 3) == ((your_move - 1) % 3)) {
    round_outcome = Win;
  }

  return round_outcome;
}

static int find_correct_move(int opponent_move, Outcome round_outcome) {
  int your_move = opponent_move;

  if (round_outcome == Lose) {
    your_move = (opponent_move + 1) % 3 + 1;
  } else if (round_outcome == Win) {
    your_move = opponent_move % 3 + 1;
  }

  return your_move;
}

static int solve(std::vector<Round> rounds, bool is_missing_move = false) {
  auto your_score = 0;

  for (auto round : rounds) {
    auto [opponent_move, your_move] = round;
    Outcome round_outcome = Outcome(round.second);

    if (!is_missing_move) {
      round_outcome = find_round_outcome(opponent_move, your_move);
    } else {
      your_move = find_correct_move(opponent_move, round_outcome);
    }

    your_score += your_move + 3 * (round_outcome - 1);
  }

  return your_score;
}

static std::vector<Round> parse_input(std::string raw_data) {
  std::istringstream ss{raw_data};

  std::vector<Round> input_data{};
  std::string line{};
  while (std::getline(ss, line)) {
    input_data.push_back({line[0] - '@', line[2] - 'W'});
  }

  return input_data;
}

void day02(std::string input_file) {
  auto input_data = parse_input(input_file);

  std::cout << solve(input_data) << std::endl;
  std::cout << solve(input_data, true) << std::endl;
}
