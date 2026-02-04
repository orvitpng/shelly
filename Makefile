CC = clang
LD = ld.lld

ARCH ?= $(shell uname -m)
include arch/$(ARCH)/config.mk

DIRS = src driver arch/$(ARCH)
BUILD = build/$(ARCH)

CFLAGS += -ffreestanding -fpie -O2
LDFLAGS += -T$(BUILD)/link.ld -pie
IFLAGS += -Iinclude -Iarch/$(ARCH)/include

OBJS = $(foreach dir,$(DIRS),\
	   $(patsubst %.c,$(BUILD)/%.c.o,$(shell find $(dir) -name "*.c")) \
	   $(patsubst %.s,$(BUILD)/%.s.o,$(shell find $(dir) -name "*.s")))

all: $(BUILD)/exec

$(BUILD)/link.ld: link.ld.S
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) $(IFLAGS) \
		-E -P $< -o $@

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) $(CFLAGS) \
		$(IFLAGS) -c $< -o $@

$(BUILD)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(TARGET) \
		$(IFLAGS) -c $< -o $@

$(BUILD)/exec: $(OBJS) $(BUILD)/link.ld
	$(LD) $(LDFLAGS) \
		--oformat=binary -o $@ $(OBJS)

clean:
	rm -rf $(BUILD)
