# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := unittests
DEFS_Debug := \
	'-DV8_TARGET_ARCH_X64' \
	'-DENABLE_GDB_JIT_INTERFACE' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_I18N_SUPPORT' \
	'-DGTEST_HAS_POSIX_RE=0' \
	'-DGTEST_LANG_CXX11=0' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-DENABLE_DISASSEMBLER' \
	'-DV8_ENABLE_CHECKS' \
	'-DOBJECT_PRINT' \
	'-DVERIFY_HEAP' \
	'-DDEBUG' \
	'-DENABLE_EXTRA_CHECKS' \
	'-DENABLE_HANDLE_ZAPPING'

# Flags passed to all source files.
CFLAGS_Debug := \
	-O0 \
	-gdwarf-2 \
	-fvisibility=hidden \
	-Werror \
	-mmacosx-version-min=10.5 \
	-arch x86_64 \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers

# Flags passed to only C files.
CFLAGS_C_Debug := \
	-std=c99 \
	-fno-strict-aliasing

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-std=gnu++0x \
	-fno-rtti \
	-fno-exceptions \
	-fvisibility-inlines-hidden \
	-fno-threadsafe-statics \
	-fno-strict-aliasing

# Flags passed to only ObjC files.
CFLAGS_OBJC_Debug :=

# Flags passed to only ObjC++ files.
CFLAGS_OBJCC_Debug :=

INCS_Debug := \
	-I$(srcdir)/. \
	-I$(srcdir)/testing/gmock/include \
	-I$(srcdir)/testing/gtest/include \
	-I$(srcdir)/include

DEFS_Optdebug := \
	'-DV8_TARGET_ARCH_X64' \
	'-DENABLE_GDB_JIT_INTERFACE' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_I18N_SUPPORT' \
	'-DGTEST_HAS_POSIX_RE=0' \
	'-DGTEST_LANG_CXX11=0' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-DENABLE_DISASSEMBLER' \
	'-DV8_ENABLE_CHECKS' \
	'-DOBJECT_PRINT' \
	'-DVERIFY_HEAP' \
	'-DDEBUG' \
	'-DENABLE_EXTRA_CHECKS' \
	'-DENABLE_HANDLE_ZAPPING'

# Flags passed to all source files.
CFLAGS_Optdebug := \
	-O3 \
	-gdwarf-2 \
	-fstrict-aliasing \
	-fvisibility=hidden \
	-Werror \
	-mmacosx-version-min=10.5 \
	-arch x86_64 \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers

# Flags passed to only C files.
CFLAGS_C_Optdebug := \
	-std=c99 \
	-fno-strict-aliasing

# Flags passed to only C++ files.
CFLAGS_CC_Optdebug := \
	-std=gnu++0x \
	-fno-rtti \
	-fno-exceptions \
	-fvisibility-inlines-hidden \
	-fno-threadsafe-statics \
	-fno-strict-aliasing

# Flags passed to only ObjC files.
CFLAGS_OBJC_Optdebug :=

# Flags passed to only ObjC++ files.
CFLAGS_OBJCC_Optdebug :=

INCS_Optdebug := \
	-I$(srcdir)/. \
	-I$(srcdir)/testing/gmock/include \
	-I$(srcdir)/testing/gtest/include \
	-I$(srcdir)/include

DEFS_Release := \
	'-DV8_TARGET_ARCH_X64' \
	'-DENABLE_GDB_JIT_INTERFACE' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_I18N_SUPPORT' \
	'-DGTEST_HAS_POSIX_RE=0' \
	'-DGTEST_LANG_CXX11=0' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-DENABLE_HANDLE_ZAPPING'

# Flags passed to all source files.
CFLAGS_Release := \
	-O3 \
	-gdwarf-2 \
	-fstrict-aliasing \
	-fvisibility=hidden \
	-Werror \
	-mmacosx-version-min=10.5 \
	-arch x86_64 \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers

# Flags passed to only C files.
CFLAGS_C_Release := \
	-std=c99 \
	-fno-strict-aliasing

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-std=gnu++0x \
	-fno-rtti \
	-fno-exceptions \
	-fvisibility-inlines-hidden \
	-fno-threadsafe-statics \
	-fno-strict-aliasing

# Flags passed to only ObjC files.
CFLAGS_OBJC_Release :=

# Flags passed to only ObjC++ files.
CFLAGS_OBJCC_Release :=

INCS_Release := \
	-I$(srcdir)/. \
	-I$(srcdir)/testing/gmock/include \
	-I$(srcdir)/testing/gtest/include \
	-I$(srcdir)/include

OBJS := \
	$(obj).target/$(TARGET)/test/unittests/base/bits-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/cpu-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/division-by-constant-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/flags-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/functional-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/platform/condition-variable-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/platform/mutex-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/platform/platform-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/platform/semaphore-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/platform/time-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/sys-info-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/base/utils/random-number-generator-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/char-predicates-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/change-lowering-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/common-operator-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/graph-reducer-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/graph-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/instruction-selector-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/js-builtin-reducer-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/js-operator-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/js-typed-lowering-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/machine-operator-reducer-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/machine-operator-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/node-test-utils.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/simplified-operator-reducer-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/simplified-operator-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/value-numbering-reducer-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/zone-pool-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/libplatform/default-platform-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/libplatform/task-queue-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/libplatform/worker-thread-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/heap/gc-idle-time-handler-unittest.o \
	$(obj).target/$(TARGET)/test/unittests/run-all-unittests.o \
	$(obj).target/$(TARGET)/test/unittests/test-utils.o \
	$(obj).target/$(TARGET)/test/unittests/compiler/x64/instruction-selector-x64-unittest.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(builddir)/libgmock.a $(builddir)/libgtest.a $(builddir)/libv8_libplatform.a $(obj).target/tools/gyp/v8.stamp $(obj).target/testing/gtest_prod.stamp $(builddir)/libv8_libbase.a $(builddir)/libv8_base.a $(builddir)/libicui18n.a $(builddir)/libicuuc.a $(builddir)/libicudata.a $(builddir)/libv8_snapshot.a $(obj).target/tools/gyp/js2c.stamp

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))
$(OBJS): GYP_OBJCFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE)) $(CFLAGS_OBJC_$(BUILDTYPE))
$(OBJS): GYP_OBJCXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE)) $(CFLAGS_OBJCC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-Wl,-search_paths_first \
	-mmacosx-version-min=10.5 \
	-arch x86_64 \
	-L$(builddir)

LIBTOOLFLAGS_Debug := \
	-Wl,-search_paths_first

LDFLAGS_Optdebug := \
	-Wl,-search_paths_first \
	-mmacosx-version-min=10.5 \
	-arch x86_64 \
	-L$(builddir)

LIBTOOLFLAGS_Optdebug := \
	-Wl,-search_paths_first

LDFLAGS_Release := \
	-Wl,-search_paths_first \
	-mmacosx-version-min=10.5 \
	-arch x86_64 \
	-L$(builddir)

LIBTOOLFLAGS_Release := \
	-Wl,-search_paths_first

LIBS :=

$(builddir)/unittests: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(builddir)/unittests: LIBS := $(LIBS)
$(builddir)/unittests: GYP_LIBTOOLFLAGS := $(LIBTOOLFLAGS_$(BUILDTYPE))
$(builddir)/unittests: LD_INPUTS := $(OBJS) $(builddir)/libgmock.a $(builddir)/libgtest.a $(builddir)/libv8_libplatform.a $(builddir)/libv8_libbase.a $(builddir)/libv8_base.a $(builddir)/libicui18n.a $(builddir)/libicuuc.a $(builddir)/libicudata.a $(builddir)/libv8_snapshot.a
$(builddir)/unittests: TOOLSET := $(TOOLSET)
$(builddir)/unittests: $(OBJS) $(builddir)/libgmock.a $(builddir)/libgtest.a $(builddir)/libv8_libplatform.a $(builddir)/libv8_libbase.a $(builddir)/libv8_base.a $(builddir)/libicui18n.a $(builddir)/libicuuc.a $(builddir)/libicudata.a $(builddir)/libv8_snapshot.a FORCE_DO_CMD
	$(call do_cmd,link)

all_deps += $(builddir)/unittests
# Add target alias
.PHONY: unittests
unittests: $(builddir)/unittests

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/unittests

