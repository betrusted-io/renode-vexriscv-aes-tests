CROSS_COMPILE ?= riscv-none-embed-
main.elf: main.c bsp.h aes_custom.h riscv.h type.h
	$(CROSS_COMPILE)gcc main.c -o $@ -nostdlib -ggdb3

clean:
	rm -f main.elf
