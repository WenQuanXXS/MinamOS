#include "ports.h"
#include "../cpu/isr.h"
#include "VGA_display.h"
#include "../kernel/util.h"
#include "keyboard.h"
#include "shell.h"

#define SC_MAX 57

static char key_buffer[256];



static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);

    handle_input(scancode);

    
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}
