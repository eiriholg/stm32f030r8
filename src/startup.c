#include <stdint.h>

extern uint32_t _sdata, _edata, _sidata, _sbss, _ebss, _estack;

int main(void);

void Reset_Handler(void) {
    uint32_t *src = &_sidata;
    for (uint32_t *dst = &_sdata; dst < &_edata; ) *dst++ = *src++;
    for (uint32_t *dst = &_sbss;  dst < &_ebss;  ) *dst++ = 0;
    main();
    for (;;);
}

void Default_Handler(void) { for (;;); }

__attribute__((section(".isr_vector"), used))
void (* const vector_table[])(void) = {
    (void (*)(void)) &_estack,
    Reset_Handler,
    Default_Handler, /* NMI */
    Default_Handler, /* HardFault */
};
