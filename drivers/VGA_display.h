#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define BLUE_ON_BLACK        0x01
#define GREEN_ON_BLACK       0x02
#define CYAN_ON_BLACK        0x03
#define RED_ON_BLACK         0x04
#define MAGENTA_ON_BLACK     0x05
#define BROWN_ON_BLACK       0x06
#define LIGHT_GREY_ON_BLACK  0x07
#define DARK_GREY_ON_BLACK   0x08
#define LIGHT_BLUE_ON_BLACK  0x09
#define LIGHT_GREEN_ON_BLACK 0x0A
#define LIGHT_CYAN_ON_BLACK  0x0B
#define LIGHT_RED_ON_BLACK   0x0C
#define LIGHT_MAGENTA_ON_BLACK 0x0D
#define YELLOW_ON_BLACK      0x0E
#define WHITE_ON_BLACK       0x0F

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void print_string(char* string);
void println_string(char* string);
void print_nl();
void clear_screen();
int scroll_ln(int offset);
void print_string_in_random_color(char* string);
void print_string_in_color(char* string, uint8_t color);
void println_string_in_random_color(char* string);
void println_string_in_color(char* string, uint8_t color);
void print_backspace();
void print_enter();