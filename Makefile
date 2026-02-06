CC = clang
LD = ld.lld
CP = llvm-objcopy

DIRS = src driver arch/$(ARCH)
IS = $(patsubst %,-I%/include,$(filter-out src,$(DIRS))) -Iinclude

CFLAGS += $(IS) -ffreestanding -fpie -Wall
LDFLAGS += -T$(BUILD)/link.ld -pie
CPFLAGS += -Obinary

ARCH ?= $(shell uname -m)
include arch/$(ARCH)/config.mk

BUILD = build/$(ARCH)

OBJS = $(foreach dir,$(DIRS),\
	   $(patsubst %.c,$(BUILD)/%.c.o,$(shell find $(dir) -name "*.c")) \
	   $(patsubst %.s,$(BUILD)/%.s.o,$(shell find $(dir) -name "*.s")) \
	   $(patsubst %.S,$(BUILD)/%.S.o,$(shell find $(dir) -name "*.S")))

all: $(BUILD)/exec

$(BUILD)/link.ld: link.ld.S
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) $(IS) \
		-E -P $< -o $@

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) $(CFLAGS) \
		-c $< -o $@

$(BUILD)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) $(IS) \
		-c $< -o $@

$(BUILD)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) $(IS) \
		-c $< -o $@

$(BUILD)/exec.o: $(OBJS) $(BUILD)/link.ld
	$(LD) $(LDFLAGS) \
		$(OBJS) -o $@

$(BUILD)/exec: $(BUILD)/exec.o
	$(CP) $(CPFLAGS) \
		$< $@

clean:
	rm -rf build
