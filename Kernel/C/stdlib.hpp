#pragma once

#include "Kernel/Ke/HAL.hpp"

extern "C" {
    char *itoa(int value, char *str, int base);
    int rand();
    void srand(int value);
}