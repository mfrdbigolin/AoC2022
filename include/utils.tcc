// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#ifndef UTILS_TCC
# define UTILS_TCC

template <typename T>
int signal(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif /* !UTILS_TCC  */
