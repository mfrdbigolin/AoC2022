// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#ifndef UTILS_TCC
#define UTILS_TCC

#include <utility>
#include <vector>

template <typename T> int signal(T val) {
  return (T(0) < val) - (val < T(0));
}

template <typename T> class Matrix {
private:
  size_t rows;
  size_t cols;
  std::vector<T> data;

public:
  Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows * cols) {
  }

  T &operator()(size_t i, size_t j) {
    return data[i * cols + j];
  }

  T operator()(size_t i, size_t j) const {
    return data[i * cols + j];
  }

  T &operator()(size_t i) {
    return data[i];
  }

  T operator()(size_t i) const {
    return data[i];
  }

  std::pair<size_t, size_t> sizes() {
    return std::make_pair(rows, cols);
  }
};

#endif /* !UTILS_TCC  */
