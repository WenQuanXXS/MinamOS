#pragma once

#include <stdint.h>

#define MAX_RES_NAME_LEN 32


typedef struct {
    char name[MAX_RES_NAME_LEN];
    int owner_id;
    int is_allocated;
} res_t;

// 初始化资源分配
void init_res_alloc();

// 分配资源
int alloc_res(const char* name, int owner_id);

// 释放资源
int free_res(const char* name, int owner_id);