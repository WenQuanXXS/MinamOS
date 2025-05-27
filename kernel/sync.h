#pragma once

#include <stdint.h>

#define MAX_RES_NAME_LEN 32
#define MAX_RES 100

// 定义资源表的固定地址，避免与VGA显存冲突
#define RES_TABLE_ADDR 0x100000  // 1MB处，与栈空间分开

typedef struct {
    char name[MAX_RES_NAME_LEN];
    int owner_id;
    int is_allocated;
} res_t;

// 初始化变量分配系统
void init_res_alloc();

// 分配变量
int alloc_res(const char* name, int owner_id);

// 释放变量
int free_res(const char* name, int owner_id);

// 检查变量是否被分配
int is_res_allocated(const char* name);

// 获取变量所有者
int get_res_owner(const char* name);