# Makefile
# Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
# SPDX-License-Identifier: MIT

include Config.mk
include Utils.mk

vpath %.cc $(SRC_DIR)

ifdef INCL_DIR
	CCFLAGS += -I$(INCL_DIR)
endif

OBJS = $(patsubst %, $(BUILD_DIR)/%.o, $(MAIN) $(MODULES))

.PHONY: clean

$(BIN_DIR)/$(MAIN): $(OBJS) | $(BIN_DIR)
	@$(link_binary)

$(BUILD_DIR)/%.o: %.cc | $(BUILD_DIR)
	@$(assemble_object)

# Create missing output directories.
$(BUILD_DIR) $(BIN_DIR):
	@$(create_dir)

clean:
	@$(clean)
