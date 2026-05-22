#include <stdint.h>

#define RCC_AHBENR   (*(volatile uint32_t *)0x40021014)
#define GPIOA_MODER  (*(volatile uint32_t *)0x48000000)
#define GPIOA_ODR    (*(volatile uint32_t *)0x48000014)

#define GPIOAEN      (1U << 17)
#define LED_PIN      5

static void delay(volatile uint32_t n) {
    while (n--) { __asm__ volatile ("nop"); }
}

int main(void) {
    RCC_AHBENR |= GPIOAEN;
    GPIOA_MODER &= ~(3U << (LED_PIN * 2));
    GPIOA_MODER |=  (1U << (LED_PIN * 2));

    for (;;) {
        GPIOA_ODR ^= (1U << LED_PIN);
        delay(400000);
    }
}
