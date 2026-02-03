CC = clang
LD = lld
COPY = llvm-objcopy

ARCH ?= $(shell uname -m)
ARCHES = riscv32
ifeq ($(filter $(ARCH),$(ARCHES)),)
	$(error Unsupported architecture \"$(ARCH)\")
endif

CFLAGS += -fuse-ld=$(LD) -O2 -fPIC -Wno-main-return-type
LDFLAGS += -nostdlib -Tlink.ld
IFLAGS += -Iinclude -Iarch/$(ARCH)/include

include arch/$(ARCH)/config.mk

DIRS = src driver arch/$(ARCH)
SRC_C = $(foreach dir,$(DIRS),$(shell find $(dir) -name "*.c"))
SRC_S = $(foreach dir,$(DIRS),$(shell find $(dir) -name "*.s"))
SRC = $(SRC_C) $(SRC_S)

all: kernel.bin

kernel.elf: $(SRC) link.ld
	$(CC) $(TARGET) $(CFLAGS) $(LDFLAGS) $(IFLAGS) \
		-o $@ $(SRC)

kernel.bin: kernel.elf
	$(COPY) -O binary $< $@

link.ld: link.ld.S
	$(CC) $(TARGET) $(IFLAGS) \
		-E $< -o $@

run: kernel.bin
	$(QEMU) -kernel $<

clean:
	rm -f link.ld kernel.elf kernel.bin
