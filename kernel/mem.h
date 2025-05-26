#pragma once

#include <stdint.h>
#include <stddef.h>

#define NULL_POINTER ((void*)0)

void init_dynamic_mem();

void print_dynamic_node_size();

void print_dynamic_mem();

void *mem_alloc(size_t size);

void mem_free(void *p);