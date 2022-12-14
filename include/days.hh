// Copyright (C) 2022, 2023 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
// SPDX-License-Identifier: MIT

#ifndef DAYS_HH
#define DAYS_HH

#include <functional>
#include <map>
#include <string>

// TODO: find an alternative to referencing every day file here.

void day01(std::string);
void day02(std::string);
void day03(std::string);
void day04(std::string);
void day05(std::string);
void day06(std::string);
void day08(std::string);
void day09(std::string);
void day10(std::string);
void day11(std::string);
void day12(std::string);
void day14(std::string);
void day15(std::string);
void day18(std::string);

using Day = std::function<void(std::string)>;

const std::map<std::string, Day> DAYS{
    {"01", day01}, {"02", day02}, {"03", day03}, {"04", day04}, {"05", day05},
    {"06", day06}, {"08", day08}, {"09", day09}, {"10", day10}, {"11", day11},
    {"12", day12}, {"14", day14}, {"15", day15}, {"18", day18}};

#endif /* !DAYS_HH  */
