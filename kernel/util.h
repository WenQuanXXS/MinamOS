#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes);

int string_length(char s[]);

void reverse(char s[]);

void int_to_string(int n, char str[]);

int rand();

void append(char s[], char n);

bool backspace(char buffer[]);

void clear_buffer(char buffer[]);

int compare_string(const char s1[], const char s2[]);

int max(int a, int b);
int min(int a, int b);

void* memset(void *ptr, int value, size_t num);

void string_copy(char* a, char* b);