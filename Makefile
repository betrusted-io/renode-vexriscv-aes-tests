CROSS_COMPILE ?= riscv64-unknown-elf-
CFLAGS		:= -D__vexriscv__ -march=rv32ima  -mabi=ilp32 \
				-Wall -Wextra \
				-flto \
				-ggdb3 \
				-ffunction-sections -fdata-sections -fno-common \
				-fomit-frame-pointer -O0 \
				-I. \
				-DPRINTF_DISABLE_SUPPORT_FLOAT

LDFLAGS     := $(CFLAGS) $(ADD_LFLAGS) -L$(LD_DIR) \
			-nostartfiles \
			-nostdlib \
			-Wl,--gc-sections \
			-Wl,--no-warn-mismatch \
			-Wl,--script=linker.ld \
			-Wl,--build-id=none

main.elf: main.o crt0-vexriscv.o project.o printf.o mul.o div.o aes_core_vexriscv.o
	$(CROSS_COMPILE)gcc $(LDFLAGS) main.o crt0-vexriscv.o project.o mul.o div.o printf.o aes_core_vexriscv.o -o $@

main.o: main.c bsp.h aes_custom.h riscv.h type.h
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@

project.o: project.c project.h
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@

printf.o: printf.c printf.h
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@

crt0-vexriscv.o: crt0-vexriscv.S
	$(CROSS_COMPILE)gcc -x assembler-with-cpp -c $(CFLAGS) $< -o $@

div.o: div.S
	$(CROSS_COMPILE)gcc -x assembler-with-cpp -c $(CFLAGS) $< -o $@

mul.o: mul.S
	$(CROSS_COMPILE)gcc -x assembler-with-cpp -c $(CFLAGS) $< -o $@

aes_core_vexriscv.o: aes_core_vexriscv.c aes_custom.h
	$(CROSS_COMPILE)gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f main.elf main.o crt0-vexriscv.o mul.o div.o printf.o project.o
