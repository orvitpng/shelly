SRCS = shell.c shell.s
LINK = link.ld

# my alpine installation uses these executables for cross compilation
# it is likely that your distro uses different names
CC = riscv-none-elf-gcc
OBJCOPY = riscv-none-elf-objcopy
OBJDUMP = riscv-none-elf-objdump

CFLAGS = -march=rv32im -mabi=ilp32 -nostdlib -ffreestanding -O2
LDFLAGS = -T$(LINK) -nostdlib -Wl,--no-warn-rwx-segments
DEPFLAGS = -MMD -MP

all: shell.bin

shell.elf: $(SRCS) $(LINK)
	$(CC) \
		$(CFLAGS) \
		$(LDFLAGS) \
		$(DEPFLAGS) \
		-o $@ \
		$(filter-out $(LINK),$^)

-include shell.d

shell.bin: shell.elf
	$(OBJCOPY) \
		-O binary \
		$< $@

run: shell.bin
	qemu-system-riscv32 \
		-nographic \
		-machine virt \
		-bios none \
		-kernel $<

dump: shell.bin
	$(OBJDUMP) \
		-m riscv:rv32 \
		-b binary \
		-D shell.bin

clean:
	rm -f shell.elf shell.bin shell.d

.PHONY: all run dump clean
