<!--
  - Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
  - SPDX-License-Identifier: MIT
  -->

# *AoC2022*: My Advent of Code 2022 Solutions

[![Public license](https://img.shields.io/badge/MIT_(Expat)-yellow?logo=spdx&logoColor=white)](./LICENSE)
[![Programming Language](https://img.shields.io/badge/C%2B%2B_Language-red?logo=C%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp)

My C++ solutions to [Advent of Code 2022](https://adventofcode.com/2022/) (also
known as *AoC2022*) in this cheerful month of Noël.

When working on my solutions, I strive to make them as general as possible, that
is, they could be adaptated to solve similar problems.  Elegance, readability, and
efficiency, in this order, are also my concerns, though secondary after generality.

## Building

Use `make` to build the program; the executable file `advent` is in the `bin`
directory. To clean the output directories, use `make clean`.

## Usage

The general usage of `advent`, for a particular *DAY*, is

* `advent `*`DAY`*

Additionally, if you have another input for a particular day stored in the `inputs`’
folder, name it in the format `day`*`DAY`*`.`*`EXT`*`.txt`, where *EXT* is any
arbitrary extension. To use it, append *EXT* to the end of the command, like this:

* `advent `*`DAY`*` `*`EXT`*

## Licensing

This repository is licensed with the [MIT (Expat)](./LICENSE)
(*SPDX-License-Identifier: [MIT](https://spdx.org/licenses/MIT.html)*); everyone
with a copy of this software is permitted to use, modify, distribute and/or
sublicense it, provided that the [LICENSE](./LICENSE) and the copyright headers on
the top of each source file are preserved in copies of this package.

There is no warranty of any kind for this material, nor the author is liable for any
third-party use of this collection.  For more details and clarification, please
read the [LICENSE](./LICENSE) in full text.
