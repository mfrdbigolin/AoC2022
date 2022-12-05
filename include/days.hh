// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#ifndef DAYS_HH
# define DAYS_HH

# include <map>
# include <string>

// TODO: find an alternative to referencing every day file here.

void day01(std::string);
void day02(std::string);
void day03(std::string);
void day04(std::string);

typedef void (*Day)(std::string);
std::map<std::string, Day> DAYS{
  {"01", day01},
  {"02", day02},
  {"03", day03},
  {"04", day04}
};

#endif /* !DAYS_HH  */
