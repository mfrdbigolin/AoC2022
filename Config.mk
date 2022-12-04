# Configuration for the Makefile
# Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
# SPDX-License-Identifier: MIT

MAKENAME = "Advent"

MAIN = advent
MODULES = day01 day02 day03 utils

SRC_DIR = src
INCL_DIR = include
BUILD_DIR = build
BIN_DIR = bin

CC = g++
CCFLAGS = -Wall -pedantic -std=c++20 -O2
LDFLAGS = -lm
