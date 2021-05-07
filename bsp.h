#ifndef BSP_H__
#define BSP_H__

#define __bswap_constant_32(x) \
     ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |                      \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))
# define __bswap_32(x) \
     (__extension__                                                              \
      ({ register unsigned int __x = (x); __bswap_constant_32 (__x); }))

#define BSP_PLIC SYSTEM_PLIC_APB
#define BSP_PLIC_CPU_0 SYSTEM_PLIC_SYSTEM_CPU_EXTERNAL_INTERRUPT
#define BSP_MACHINE_TIMER SYSTEM_MACHINE_TIMER_APB
#define BSP_MACHINE_TIMER_HZ SYSTEM_MACHINE_TIMER_HZ
#define BSP_MACHINE_TIMER_PLIC_ID SYSTEM_PLIC_SYSTEM_MACHINE_TIMER_INTERRUPT

#define BSP_UART_TERMINAL SYSTEM_UART_A_APB
#define BSP_LED_GPIO SYSTEM_GPIO_A_APB
#define BSP_LED_MASK 0x01

void udelay(int usec);
void _putchar(char character);
int printf_(const char* format, ...);

#define bsp_init() {}
#define bsp_putChar(c) _putchar(c)
#define bsp_uDelay(usec) udelay(usec)
#define bsp_putString(s) printf_("%s", s)

#endif /* BSP_H__ */
