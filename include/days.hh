// Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#ifndef DAYS_HH
# define DAYS_HH

# include <map>
# include <string>

// TODO: find an alternative to referencing every day file here.

void day01(std::string);

typedef void (*day_solve)(std::string);
std::map<std::string, day_solve> DAYS{
  {"01", day01}
};

#endif /* !DAYS_HH  */