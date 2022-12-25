// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Ten, Cathode-Ray Tube.

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<int> execute_program(std::vector<std::pair<int, int>> program) {
  std::vector<int> program_state{1};

  for (auto instruction : program) {
    auto [op_cycles, oper] = instruction;

    auto register_x = program_state[program_state.size() - 1];

    if (op_cycles == 2) {
      program_state.push_back(register_x);
    }

    program_state.push_back(register_x + oper);
  }

  return program_state;
}

int solve1(std::vector<int> state) {
  int strength = 0;

  for (auto interest = 20; interest <= 220; interest += 40) {
    strength += interest * state[interest - 1];
  }

  return strength;
}

void solve2(std::vector<int> state) {
  for (auto i = 0; i < 6; ++i) {
    for (auto crt = 0; crt < 40; ++crt) {
      auto register_x = state[40 * i + crt];

      if (crt >= register_x - 1 && crt <= register_x + 1) {
        std::cout << '#';
      } else {
        std::cout << '.';
      }
    }

    std::cout << std::endl;
  }
}

const std::map<std::string, int> CYCLES{{"noop", 1}, {"addx", 2}};

std::vector<std::pair<int, int>> parse_program(std::string source_code) {
  std::vector<std::pair<int, int>> program{};

  std::istringstream ss{source_code};
  std::string line{};
  while (std::getline(ss, line)) {
    auto opcode = line.substr(0, 4);
    auto oper = line.substr(4);

    auto instruction =
        std::make_pair(CYCLES.at(opcode), oper == "" ? 0 : std::stoi(oper));

    program.push_back(instruction);
  }

  return program;
}

void day10(std::string input_file) {
  auto program = parse_program(input_file);
  auto state = execute_program(program);

  std::cout << solve1(state) << std::endl;
  solve2(state);
}
