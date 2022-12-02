// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
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