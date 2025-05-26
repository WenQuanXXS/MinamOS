#include "VGA_display.h"
#include <stdint.h>
#include "keyboard.h"
#include "../kernel/util.h"
#include "../kernel/mem.h"
#include <stdbool.h>

const char scancode_to_char_upper_case[] = {
    '?', '?', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', '0', '-', '=',
    '?', '?', 'Q', 'W', 'E', 'R', 'T',
    'Y', 'U', 'I', 'O', 'P', '[', ']',
    '?', '?', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\\', '`',
    '?', '\\', 'Z', 'X', 'C', 'V', 'B',
    'N', 'M', ',', '.', '/', '?', '?',
    '?', ' '
};

const char scancode_to_char_lower_case[] = {
    '?', '?', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', '0', '-', '=',
    '?', '?', 'q', 'w', 'e', 'r', 't',
    'y', 'u', 'i', 'o', 'p', '[', ']',
    '?', '?', 'a', 's', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', ';', '\\', '`',
    '?', '\\', 'z', 'x', 'c', 'v', 'b',
    'n', 'm', ',', '.', '/', '?', '?',
    '?', ' '
};



#define SC_MAX 57

static volatile char key_buffer[1024] = {0};

bool is_Shift = true;

void init_shell(){
    print_string(">>>");
}

void execute_command(char *input){
    print_nl();
    // print_string("[DEBUG]");
    // print_string(input);
    // print_nl();
    if (compare_string(input, "clear") == 0) {
        clear_screen();

    } else if (compare_string(input, "help") == 0) {
        println_string("Available commands: clear, help, mem");
    
    } else if (compare_string(input,"mem") == 0) {
        print_dynamic_mem();
    } else if (compare_string(input,"test alloc") == 0) {
        mem_alloc(16);
        mem_alloc(32);
        mem_alloc(64);
    } else if (compare_string(input,"test free") == 0){
        int *p = (int*)mem_alloc(sizeof(int));
        mem_free(p);
    }
    else {
        print_string_in_color(input, LIGHT_RED_ON_BLACK);
    }
}

void handle_input(uint8_t scancode){
    if (scancode > SC_MAX) return;
    if(scancode == KEY_BACKSPACE){
        backspace(key_buffer);
        print_backspace();
        return;
    }else if (scancode == KEY_LEFT_SHIFT){
        is_Shift = !is_Shift;
    }else if (scancode == KEY_ENTER){
        execute_command(key_buffer);
        clear_buffer(key_buffer);
        print_enter();
    }
    
    else if(scancode_to_char_upper_case[(int) scancode] != '?' && is_Shift){
        char letter = scancode_to_char_upper_case[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        print_string(str);
    }else if(scancode_to_char_lower_case[(int) scancode] != '?' && !is_Shift){
        char letter = scancode_to_char_lower_case[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        print_string(str);
    }
}