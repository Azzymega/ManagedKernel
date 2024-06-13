#pragma once

#include "Kernel/Ke/HAL.hpp"

void InitializeGDT();

struct GDTEntry {
    u2 LowLimit;
    u2 BaseLow;
    u1 BaseMiddle;
    u1 Access;
    u1 Granularity;
    u1 BaseHigh;
} __attribute__((packed));

struct GDTPointer { // Segmentation crap
    u2 Limit;
    u4 Base;
} __attribute__((packed));

struct GDTController {
    static void Set(u4 Index, u4 Base, u4 Limit, u1 Access, u1 Granularity);
    static void Initialize();
};