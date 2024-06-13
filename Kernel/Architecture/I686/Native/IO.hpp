#pragma once

#include "Kernel/Ke/HAL.hpp"

static inline void outb(uint32_t port, u1 data)
{
    __asm__ volatile("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

static inline u1 inb(uint32_t port)
{
    u1 data;
    __asm__ volatile("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void outw(uint32_t port, u2 data)
{
    __asm__ volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

static inline u2 inw(uint32_t port)
{
    u2 data;
    __asm__ volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void outdw(uint32_t port, u4 data)
{
    __asm__ volatile("outl %0, %w1" : : "a" (data), "Nd" (port));
}

static inline u4 indw(uint32_t port)
{
    u4 data;
    __asm__ volatile("inl %w1, %0" : "=a" (data) : "Nd" (port));
    return data;
}
