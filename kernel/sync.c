#include "sync.h"
#include "../drivers/VGA_display.h"
#include "../kernel/util.h"
#include <stddef.h>

/**
 * return:
 * 1 :success
 * 0 :not found
 * -1:not owner/error
 * -2:occupied
 */

res_t example_res;

void init_res_alloc() {
    example_res.is_allocated = 0;
    string_copy(example_res.name, "resource");
    example_res.owner_id = -1;

    // println_string("Ini Suc");
}

int alloc_res(const char* name, int owner_id){
    if(owner_id < 0) return -1;
    if(compare_string(example_res.name, name) == 0){
        if(example_res.is_allocated == 0){
            example_res.owner_id = owner_id;
            example_res.is_allocated = 1;
            return 1;
        }
        return -2;
    }
    return 0;
}

int free_res(const char* name, int owner_id){
    if(owner_id < 0) return -1;
    if(compare_string(example_res.name, name) == 0){
        if(example_res.owner_id == owner_id){
            example_res.owner_id = -1;
            example_res.is_allocated = 0;
            return 1;
        }
        else return -2;
    }
    return 0;
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