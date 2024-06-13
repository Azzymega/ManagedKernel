#pragma once

#include "Kernel/Reflector/Reflector.h"
#include "Kernel/Reflector/Embedded.h"
#include "Kernel/C/stdio.hpp"

struct Linker {
    void Link(Vector* Classes);
};
