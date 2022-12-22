// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#include "days.hh"
#include "utils.hh"

#include <iostream>
#include <stdlib.h>
#include <string>

int main(int argc, char *argv[]) {
  if (argc <= 1 || argc > 3) {
    std::cerr << "usage: advent <day_id> [<input_extension>]" << std::endl;

    return EXIT_FAILURE;
  }

  std::string day_number(argv[1]);
  std::string input_extension(argc > 2 ? argv[2] : "");

  auto day = day_number.size() == 1 ? "0" + day_number : day_number;
  auto input_filename =
      "./inputs/day" + day + (argc > 2 ? "." + input_extension : "") + ".txt";

  if (DAYS.count(day) == 0) {
    std::cerr << "advent: Day " << day
              << " was not compiled or currently does not exist." << std::endl;

    return EXIT_FAILURE;
  }

  auto input_data = read_file(input_filename);

  DAYS.at(day)(input_data);

  return EXIT_SUCCESS;
}
