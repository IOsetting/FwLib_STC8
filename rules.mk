# 'make V=1' will show command details
V              ?= 0
ifeq ($(V),0)
Q              := @
NULL           := 2>/dev/null
endif

CC             = $(TOOCHAIN_PREFIX)sdcc
AR             = $(TOOCHAIN_PREFIX)sdar
PACKIHX        = $(TOOCHAIN_PREFIX)packihx
SDRANLIB       = $(TOOCHAIN_PREFIX)sdranlib
LD             = $(PREFIX)ld
OBJCOPY        = $(PREFIX)objcopy
# `$(shell pwd)` or `.`, both works
TOP            = .
BDIR           = $(TOP)/$(BUILD_DIR)

# Library folders
LIB_CDIR            := src
LIB_INCLUDE         := include


LIB_CSOURCES   := $(shell find $(TOP)/$(LIB_CDIR) -name '*.c')
LIB_RELS       = $(LIB_CSOURCES:$(TOP)/%.c=$(BDIR)/%.rel)
LIB_FWLIB      := fw_stc8.lib
LIB_INCFLAGS   := -I$(TOP)/$(LIB_INCLUDE)

USER_CSOURCES  := $(foreach dir, $(USER_CDIRS), $(shell find $(TOP)/$(dir) -maxdepth 1 -name '*.c'))
USER_CSOURCES  += $(addprefix $(TOP)/, $(USER_CFILES))
# Fill rel files with c files (keep source directory structure)
USER_RELS      = $(USER_CSOURCES:$(TOP)/%.c=$(BDIR)/%.rel)
# include paths
USER_INCFLAGS  := $(addprefix -I$(TOP)/, $(USER_INCLUDES))


# Arch and target specified flags: --model-large
ARCH_FLAGS    := -mmcs51
DEBUG_FLAGS   ?= 
# c flags
OPT           ?= --opt-code-size
CSTD          ?= --std-sdcc99
CC_CFLAGS    += $(ARCH_FLAGS) $(DEBUG_FLAGS) $(OPT) $(CSTD) $(addprefix -D, $(LIB_FLAGS))
LD_CFLAGS    += $(ARCH_FLAGS) $(DEBUG_FLAGS) $(OPT) \
				--iram-size $(MCU_IRAM) --xram-size $(MCU_XRAM) --code-size $(MCU_CODE_SIZE) --out-fmt-ihx

# Generate and export AFLAGS
#     -c      do not warn if the library had to be created
#     -s      act as ranlib
#     -r      replace existing or insert new file(s) into the archive
TGT_AFLAGS    += -rcs

.PHONY: all clean flash

all: $(BDIR)/$(PROJECT).hex
	@cat $(BDIR)/$(PROJECT).mem

lib: $(BDIR)/$(LIB_FWLIB)

$(BDIR)/$(LIB_CDIR)/%.rel: $(TOP)/$(LIB_CDIR)/%.c
	@printf "  CC $<\n"
	@mkdir -p $(dir $@)
	$(Q)$(CC) $< -c $(CC_CFLAGS) $(LIB_INCFLAGS) -o $@

$(BDIR)/%.rel: $(TOP)/%.c
	@printf "  CC $<\n"
	@mkdir -p $(dir $@)
	$(Q)$(CC) $< -c $(CC_CFLAGS) $(USER_INCFLAGS) $(LIB_INCFLAGS) -o $@

# Generate static library
$(BDIR)/$(LIB_FWLIB): $(LIB_RELS)
	@printf "  AR $@\n"
	$(Q)$(AR) $(TGT_AFLAGS) $@ $^
	$(Q)$(SDRANLIB) $@

$(BDIR)/$(PROJECT).hex: $(USER_RELS) $(BDIR)/$(LIB_FWLIB)
	@printf "  CC $@\n"
	$(Q)$(CC) $(LD_CFLAGS) $^ $(BDIR)/$(LIB_FWLIB) -o $@

# $(BDIR)/$(PROJECT).ihx: $(USER_RELS) $(BDIR)/$(LIB_FWLIB)
# 	@printf "  CC $@\n"
# 	$(Q)$(CC) $^ $(BDIR)/$(LIB_FWLIB) $(TGT_CFLAGS) -o $@

# $(BDIR)/$(PROJECT).hex: $(BDIR)/$(PROJECT).ihx
# 	@printf "  PACKIHX $@\n"
# 	$(Q)$(PACKIHX) $< > $@

clean:
	rm -rf $(BDIR)/*