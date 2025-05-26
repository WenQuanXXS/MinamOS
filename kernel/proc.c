#include "proc.h"
#include <stddef.h>

#define MAX_PROCESSES 100

#include "../drivers/VGA_display.h"
#include "../kernel/util.h"
#include "../drivers/ports.h"
#include "mem.h"

pcb_t* current_process = NULL;
pcb_t* ready_queue = NULL;
int current_pid = 0;

void init_scheduler() {
    current_process = NULL;
    ready_queue = NULL;
}

extern void process_exit(); // 新增：进程返回时的死循环

pcb_t* create_process(void (*entry)()) {
    pcb_t* pcb = mem_alloc(sizeof(pcb_t));
    void* stack = mem_alloc(1024);  // 分配一页栈空间

    memset(pcb, 0, sizeof(pcb_t));
    pcb->pid = ++current_pid;
    pcb->stack = stack;
    pcb->state = 0;

    // 初始化栈顶，压入 process_exit 作为"返回地址"
    uint32_t* stack_top = (uint32_t*)((uint32_t)stack + 1024);
    *(--stack_top) = (uint32_t)process_exit; // 返回时进入死循环
    pcb->context.esp = (uint32_t)stack_top;
    pcb->context.ebp = 0;
    pcb->context.eip = (uint32_t)entry;
    pcb->context.eax = 0;
    pcb->context.ebx = 0;
    pcb->context.ecx = 0;
    pcb->context.edx = 0;
    pcb->context.esi = 0;
    pcb->context.edi = 0;
    pcb->context.eflags = 0x202; // IF=1, 使能中断

    pcb->next = NULL;

    // 添加到就绪队列
    if (!ready_queue) {
        ready_queue = pcb;
    } else {
        pcb_t* tmp = ready_queue;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = pcb;
    }

    return pcb;
}

// void schedule() {
//     if (!ready_queue) return;

//     if (!current_process) {
//         current_process = ready_queue;
//         context_switch(NULL, &current_process->context); // 如果需要上下文切换
//     } else {
//         pcb_t* next_process = current_process->next ? current_process->next : ready_queue;
//         if (next_process != current_process) {
//             pcb_t* prev_process = current_process;
//             current_process = next_process;
//             context_switch(&prev_process->context, &current_process->context); // 如果需要上下文切换
//         }
//     }
// }

void print_ready_queue(){
    pcb_t* tmp = ready_queue;
    print_string("Current process: ");
    while (tmp) {
        char pid_str[10];
        int_to_string(tmp->pid, pid_str);
        print_string(pid_str);
        print_string(" ");
        tmp = tmp->next;
    }
}

// 新增：进程返回时的死循环
void process_exit() {
    while (1) { }
}
