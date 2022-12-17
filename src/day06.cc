// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

// Day Six, Tuning Trouble.

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

int solve(std::string buffer, size_t marker_size) {
  if (buffer.size() < marker_size) {
    return -1;
  }

  for (size_t i = 0; i < buffer.size() - marker_size + 1;) {
    auto seq_start = buffer.begin() + i;
    auto seq_end = buffer.begin() + i + marker_size;

    for (auto j = marker_size - 2; j >= 0; --j) {
      if (std::count(seq_start + j, seq_end, buffer[i + j]) > 1) {
        i += j + 1;
        break;
      }

      // Distinct sequence found.
      if (j == 0) {
        return i + marker_size;
      }
    }
  }

  // No marker with such size found.
  return -1;
}

void day06(std::string input_file) {
  std::cout << solve(input_file, 4) << std::endl;
  std::cout << solve(input_file, 14) << std::endl;
}
