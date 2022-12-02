# Canned recipes for the Makefile
# Copyright (C) 2022 Matheus Fernandes Bigolin <mfrdrbigolin@disroot.org>
# SPDX-License-Identifier: MIT

define link_binary =
	$(CC) $(LDFLAGS) -o $@ $^
	echo $(MAKENAME) "Make: binary" $(@F) "linked ("$(^F)")"
endef

define assemble_object =
	$(CC) $(CCFLAGS) -c -o $@ $<
	echo $(MAKENAME) "Make: object" $(@F) "assembled ("$(^F)")"
endef

define create_dir =
	if ! [ -d $@ ]; then \
	  mkdir $@;          \
	fi
endef

define clean =
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*
	echo $(MAKENAME) "Make: cleansed binary and object files"
endef
