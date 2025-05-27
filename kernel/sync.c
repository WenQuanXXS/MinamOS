#include "sync.h"
#include "../drivers/VGA_display.h"
#include "../kernel/util.h"
#include <stddef.h>

// 使用固定地址的资源表
static res_t* res_table = (res_t*)RES_TABLE_ADDR;

void init_res_alloc() {
    // 使用memset初始化，避免直接访问可能冲突的内存
    memset(res_table, 0, sizeof(res_t) * MAX_RES);
    
    // 初始化每个资源项
    for (int i = 0; i < MAX_RES; i++) {
        res_table[i].is_allocated = 0;
        res_table[i].owner_id = -1;
        res_table[i].name[0] = '\0';
    }
}

// int alloc_res(const char* name, int owner_id) {
//     // 检查变量是否已存在
//     for (int i = 0; i < MAX_RES; i++) {
//         if (res_table[i].is_allocated && compare_string(res_table[i].name, name) == 0) {
//             return -1; // 变量已存在
//         }
//     }

//     // 查找空闲位置
//     for (int i = 0; i < MAX_RES; i++) {
//         if (!res_table[i].is_allocated) {
//             // 复制变量名
//             int j = 0;
//             while (name[j] != '\0' && j < MAX_RES_NAME_LEN - 1) {
//                 res_table[i].name[j] = name[j];
//                 j++;
//             }
//             res_table[i].name[j] = '\0';
            
//             res_table[i].is_allocated = 1;
//             res_table[i].owner_id = owner_id;
//             return 0; // 分配成功
//         }
//     }
    
//     return -2; // 表已满
// }

// int free_res(const char* name, int owner_id) {
//     for (int i = 0; i < MAX_RES; i++) {
//         if (res_table[i].is_allocated && 
//             compare_string(res_table[i].name, name) == 0) {
//             if (res_table[i].owner_id != owner_id) {
//                 return -1; // 不是所有者
//             }
//             res_table[i].is_allocated = 0;
//             res_table[i].owner_id = -1;
//             res_table[i].name[0] = '\0';
//             return 0; // 释放成功
//         }
//     }
//     return -2; // 变量不存在
// }

// int is_res_allocated(const char* name) {
//     for (int i = 0; i < MAX_RES; i++) {
//         if (res_table[i].is_allocated && 
//             compare_string(res_table[i].name, name) == 0) {
//             return 1;
//         }
//     }
//     return 0;
// }

// int get_res_owner(const char* name) {
//     for (int i = 0; i < MAX_RES; i++) {
//         if (res_table[i].is_allocated && 
//             compare_string(res_table[i].name, name) == 0) {
//             return res_table[i].owner_id;
//         }
//     }
//     return -1;
// }