#include "VGA_display.h"
#include "ports.h"
#include "../kernel/util.h"
#include <stdint.h>

const uint8_t COLORS_ON_BLACK[] = {
    BLUE_ON_BLACK, GREEN_ON_BLACK, CYAN_ON_BLACK, RED_ON_BLACK,
    MAGENTA_ON_BLACK, BROWN_ON_BLACK, LIGHT_GREY_ON_BLACK,
    DARK_GREY_ON_BLACK, LIGHT_BLUE_ON_BLACK, LIGHT_GREEN_ON_BLACK,
    LIGHT_CYAN_ON_BLACK, LIGHT_RED_ON_BLACK, LIGHT_MAGENTA_ON_BLACK,
    YELLOW_ON_BLACK, WHITE_ON_BLACK
};

uint8_t get_random_color() {
    int i = rand() % (sizeof(COLORS_ON_BLACK) / sizeof(COLORS_ON_BLACK[0]));
    return COLORS_ON_BLACK[i];
}


void set_cursor(int offset) {
    // Set the cursor position
    offset /= 2; // Each character takes up 2 bytes
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_cursor(){
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; // Each character takes up 2 bytes
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
    //in VGA,first byte is character and second byte is color
}

void set_char_at_video_memory_in_color(char character, int offset,uint8_t color) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = color;
}

void print_string(char* string){
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        if (string[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory(string[i], offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}


void println_string(char* string){
    print_string(string);
    print_nl();
}

void print_string_in_color(char* string, uint8_t color){
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        if (string[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory_in_color(string[i], offset, color);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}

void print_string_in_random_color(char* string){
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        if (string[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory_in_color(string[i], offset, get_random_color());
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}

void println_string_in_color(char* string, uint8_t color){
    print_string_in_color(string, color);
    print_nl();
}
void println_string_in_random_color(char* string){
    print_string_in_random_color(string);
    print_nl();
}

int scroll_ln(int offset) {
    memory_copy(
            (char *) (get_offset(0, 1) + VIDEO_ADDRESS),
            (char *) (get_offset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}

void print_nl() {
    int newOffset = move_offset_to_new_line(get_cursor());
    if (newOffset >= MAX_ROWS * MAX_COLS * 2) {
        newOffset = scroll_ln(newOffset);
    }
    set_cursor(newOffset);
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    for (int i = 0; i < screen_size; ++i) {
        set_char_at_video_memory(' ', i * 2);
    }
    set_cursor(get_offset(0, 0));
}

void print_backspace() {
    //We should not delete the ">>>"
    int curCursor = get_cursor();
    if(curCursor % 160 > 6){
        int newCursor = curCursor - 2;
        set_char_at_video_memory(' ', newCursor);
        set_cursor(newCursor);
    }
    
}

void print_enter(){
    int newCursor = min(((get_cursor() / 160) + 1) , MAX_ROWS - 1) * 160 + 6;
    print_nl();
    print_string(">>>");
    set_cursor(newCursor);
}