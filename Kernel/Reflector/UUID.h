#pragma once

// FIXME

#define UUIDLength 20

#include "Kernel/C/string.hpp"
#include "Kernel/C/stdio.hpp"
#include "Kernel/C/stdlib.hpp"
#include "Kernel/Ke/HAL.hpp"

void GenerateUUID(uc* Value);
void GenerateNullUUID(uc* Buffer);
bool IsNullUUID(uc* Value);