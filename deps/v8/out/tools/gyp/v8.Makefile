# This file is generated by gyp; do not edit.

export builddir_name ?= ./out/tools/gyp/out
.PHONY: all
all:
	$(MAKE) -C ../.. js2c v8_libbase v8_libplatform v8_base v8_nosnapshot mksnapshot v8_snapshot v8
