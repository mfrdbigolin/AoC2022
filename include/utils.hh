// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#ifndef UTILS_HH
#define UTILS_HH

#include <string>

std::string read_file(std::string filename);
int pairing(int x, int y);
int bounded_pair(int x, int y, int num_cols);

#include "utils.tcc"

#endif /* !UTILS_HH  */
