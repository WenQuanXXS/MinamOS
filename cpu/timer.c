#include "timer.h"
#include "../drivers/VGA_display.h"
#include "../drivers/ports.h"
#include "../kernel/util.h"
#include "isr.h"

volatile uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
    // char num[10];
    // int_to_string(tick, num);
    // println_string(num);
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}

void sleep(unsigned int ms) {
    unsigned int start = tick;
    while ((tick - start) < ms) {
        // 可以加CPU halt指令节省能耗
        __asm__ volatile("hlt");
    }
}