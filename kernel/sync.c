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