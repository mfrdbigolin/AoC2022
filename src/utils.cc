// Copyright (C) 2022, 2023 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#include <fstream>
#include <ios>
#include <iterator>
#include <stdexcept>
#include <string>

std::string read_file(std::string filename) {
  std::ifstream file(filename, std::ios_base::binary | std::ios_base::in);

  if (!file.is_open()) {
    throw std::runtime_error("Unable to open " + filename);
  }

  std::istreambuf_iterator<char> it{file}, end;
  std::string content(it, end);

  if (!file) {
    throw std::runtime_error("Unable to read " + filename);
  }

  file.close();
  return content;
}

// Szudzik’s pairing function: this function assigns to each coordinate in the
// cartesian plane a unique natural number.
int pairing(int x, int y) {
  // Map each integer to an unique natural number.
  int nx = x >= 0 ? 2 * x : (-2 * x - 1);
  int ny = y >= 0 ? 2 * y : (-2 * y - 1);

  return nx < ny ? ny * ny + nx : nx * (nx + 1) + ny;
}

// Pairing function in which the number of columns is expected to be bounded.
int bounded_pair(int x, int y, int num_cols) {
  return num_cols * y + x;
}

int bounded_triple(int x, int y, int z, int max_space) {
  return z * max_space * max_space + y * max_space + x;
}
