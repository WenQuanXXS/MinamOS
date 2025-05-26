#include <stdint.h>

typedef struct cpu_context {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;   // 通常不用保存，因为是栈顶
    uint32_t eip;   // 返回地址
    uint32_t eflags; // 新增：保存eflags
} cpu_context_t;

typedef struct pcb {
    uint32_t pid;           // 进程ID
    cpu_context_t context; // CPU上下文
    uint8_t  state;         // 进程状态（就绪、运行、阻塞等）
    void* stack;
    struct pcb* next;   // 用于进程队列
} pcb_t;

void init_scheduler();
pcb_t* create_process(void (*entry)());
void schedule();

//extern void context_switch(cpu_context_t*, cpu_context_t*);