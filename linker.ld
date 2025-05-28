ENTRY(_start)

SECTIONS
{
    /* 内核加载基址 */
    . = 0x1000;

    /* 代码段 */
    .text : {
        *(.text)
    }

    /* 只读数据段（字符串常量等） */
    .rodata : {
        *(.rodata*)
    }

    /* 数据段 */
    .data : {
        *(.data)
    }

    /* 未初始化数据段 */
    .bss : {
        *(.bss)
        *(COMMON)
    }

    /* 预留栈空间，放在高地址 */
    . = 0x80000;
    stack_top = .;
    . = . + 0x20000; /* 增加到128KB栈空间 */
    stack_bottom = .;
}