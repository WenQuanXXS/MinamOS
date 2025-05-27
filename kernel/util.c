#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int string_length(char s[]) {
    int i = 0;
    // 限制最大长度，防止越界
    const int MAX_SAFE_LEN = 1024;
    while (s[i] != '\0' && i < MAX_SAFE_LEN) ++i;
    return i;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = string_length(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void int_to_string(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

unsigned int get_seed_from_cpu() {
    unsigned int lo, hi;
    __asm__("rdtsc" : "=a"(lo), "=d"(hi));
    return lo ^ hi; // 合并高低位，增强随机性
}

int rand() {
    unsigned int seed = get_seed_from_cpu(); // 获取 CPU 时间戳计数器作为种子
    // 常见的 LCG 参数（glibc 也用类似方式）
    seed = seed * 1103515245 + 12345;
    return (seed >> 16) & 0x7FFF; // 保证返回的是正整数，范围 [0, 32767]
}


void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len + 1] = '\0';
}

bool backspace(char buffer[]) {
    int len = string_length(buffer);
    if (len > 0) {
        buffer[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

void clear_buffer(char buffer[]) {
    for (int i = 0; i < 1024; i++) buffer[i] = '\0';
}

int compare_string(const char s1[], const char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void* memset(void* ptr, int value, size_t num) {
    uint8_t* p = (uint8_t*)ptr;
    for (; num > 0; num--, p++)
        *p = (uint8_t)value;
    return ptr;
}

void string_copy(char* a, char* b) {
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0'; // Copy the null terminator
}
