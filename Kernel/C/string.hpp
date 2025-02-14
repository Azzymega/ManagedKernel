#pragma once

#include "stdlib.hpp"
#include "Kernel/Ke/HAL.hpp"

extern "C" {
    void* memcpy(void* dest, const void* src, size_t n);
    int memcmp(const void* s1, const void* s2, size_t n);
    void* memmove(void* s1, const void* s2, size_t n);
    void* memset(char* dest, int z, size_t n);
    size_t strlen(const char* string);
    int strcmp(const char* firstString, const char* secondString);
}

