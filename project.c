#include <stdarg.h>
#include <stdint.h>

#include <project.h>
#include <printf.h>

#define CONFIG_CLOCK_FREQUENCY 100000000

#undef printf
int panic(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = vprintf(fmt, ap);
    va_end(ap);
    asm("ebreak");
    return ret;
}

void _putchar(char character)
{
    static const uint32_t LITEX_UART_BASE = 0xf0001000;
    volatile uint32_t *litex_uart_rxtx = (uint32_t *)(LITEX_UART_BASE + 0);
    volatile uint32_t *litex_uart_txfull = (uint32_t *)(LITEX_UART_BASE + 4);
    while ((*litex_uart_txfull) & 1) {}
    *litex_uart_rxtx = character;
}

void udelay(int usec) {
    static const uint32_t LITEX_TIMER0_BASE = 0xf0000800;
    volatile uint32_t *litex_timer0_load = (uint32_t *)(LITEX_TIMER0_BASE + 0);
    volatile uint32_t *litex_timer0_reload = (uint32_t *)(LITEX_TIMER0_BASE + 4);
    volatile uint32_t *litex_timer0_en = (uint32_t *)(LITEX_TIMER0_BASE + 8);
    volatile uint32_t *litex_timer0_update_value = (uint32_t *)(LITEX_TIMER0_BASE + 12);
    volatile uint32_t *litex_timer0_value = (uint32_t *)(LITEX_TIMER0_BASE + 16);
    *litex_timer0_en = 0;
    *litex_timer0_reload = 0;
    *litex_timer0_load = CONFIG_CLOCK_FREQUENCY/1000000*usec;
    *litex_timer0_en = 1;
    *litex_timer0_update_value = 1;
        while(*litex_timer0_value) *litex_timer0_update_value = 1;
}
