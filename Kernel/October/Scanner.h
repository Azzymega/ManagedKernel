#pragma once

#include "Kernel/Ke/HAL.hpp"

struct Scanner {
    void* Binary;

    u4 Pointer;

    void Initialize(void* Binary);

    u1 GetB();
    u2 GetS();
    u4 GetI();

    u4 Check() const;

    void Rewind(u4 Count);
    void Wind(u4 Count);
    void Set(u4 Count);

};

struct LScanner {

    char* Binary;

    u4 Pointer;

    bool Unwind;

    void Initialize(void* Binary);

    u1 GetB();
    u2 GetS();
    u4 GetI();

};

