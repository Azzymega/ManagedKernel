#pragma once

#include "Kernel/Ke/HAL.hpp"
#include "stdlib.hpp"

extern "C" {
    void printf(const char* Message);
    void puts(const char* Message);
    void println(const char* Message);
    void printInteger(u4 Value);
}