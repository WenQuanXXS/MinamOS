#include "../drivers/VGA_display.h"
#include "../drivers/keyboard.h"
#include "../drivers/shell.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../cpu/idt.h"
#include "util.h"
#include "mem.h"
#include "sync.h"

extern char stack_top[];

void main() {
    asm volatile("movl %0, %%esp" : : "r"(stack_top));

    clear_screen();
    print_logo_in_random_color();
    show_version();
    
    isr_install();
    init_timer(50);
    asm volatile("sti");
    init_keyboard();

    init_dynamic_mem();

    init_res_alloc();

    print_nl();

    // test_res();

    // print_nl();

    // test_mem();

    init_shell();
}

void print_logo_in_random_color(){
    // 打印随机颜色的logo
    println_string_in_random_color(" __       __  __                                     ______    ______  ");
    println_string_in_random_color("|  \\     /  \\|  \\                                   /      \\  /      \\ ");
    println_string_in_random_color("| $$\\   /  $$ \\$$ _______    ______   ______ ____  |  $$$$$$\\|  $$$$$$\\");
    println_string_in_random_color("| $$$\\ /  $$$|  \\|       \\  |      \\ |      \\    \\ | $$  | $$| $$___\\$$");
    println_string_in_random_color("| $$$$\\  $$$$| $$| $$$$$$$\\  \\$$$$$$\\| $$$$$$\\$$$$\\| $$  | $$ \\$$    \\ ");
    println_string_in_random_color("| $$\\$$ $$ $$| $$| $$  | $$ /      $$| $$ | $$ | $$| $$  | $$ _\\$$$$$$\\");
    println_string_in_random_color("| $$ \\$$$| $$| $$| $$  | $$|  $$$$$$$| $$ | $$ | $$| $$__/ $$|  \\__| $$");
    println_string_in_random_color("| $$  \\$ | $$| $$| $$  | $$ \\$$    $$| $$ | $$ | $$ \\$$    $$ \\$$    $$");
    println_string_in_random_color(" \\$$      \\$$ \\$$ \\$$   \\$$  \\$$$$$$$ \\$$  \\$$  \\$$  \\$$$$$$   \\$$$$$$  ");
    println_string_in_random_color("                                                                 ");
}


void show_version(){
    println_string("Hello! Greet from MinamOS kernel.");
    println_string("MinamOS | Version 0.0.1");
}

void test_res(){
    if(alloc_res("resource",1) == 1){
        println_string("success alloc for 1");
    }

    if(alloc_res("resource",2) == -2){
        println_string("resource occupied");
    }

    if(free_res("resource",1) == 1){
        println_string("free resource by 1");
    }

    if(alloc_res("resource", 2) == 1){
        println_string("success alloc for 2");
    }
}

void test_mem(){
    println_string("alloc memory, size of int * 3");
    int *ptr1 = (int*)mem_alloc(sizeof(int));
    int *ptr2 = (int*)mem_alloc(sizeof(int));
    int *ptr3 = (int*)mem_alloc(sizeof(int));
    print_dynamic_mem();
    print_nl();
    println_string("free second memory block");
    mem_free(ptr2);
    print_dynamic_mem();
    print_nl();
    return ;
}