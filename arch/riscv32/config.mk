TARGET = -target riscv32-unknown-elf -march=rv32im
QEMU = qemu-system-riscv32 -nographic -machine virt -bios none
