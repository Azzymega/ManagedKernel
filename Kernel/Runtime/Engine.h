#pragma once

#include "Kernel/Ke/HAL.hpp"

#include "Kernel/Reflector/Embedded.h"
#include "Kernel/Reflector/Reflector.h"

#include "OpCodesNames.h"
#include "OperationCodes.h"

#include "Kernel/C/stdlib.hpp"
#include "Kernel/C/stdio.hpp"
#include "Kernel/C/string.hpp"
#include "Kernel/C/assert.hpp"
#include "Kernel/C/math.hpp"

#define ABISpace 12

struct Executive {

    //
    // Registers
    //

    static inline Class* BRVR;
    static inline Method* Route;

    static inline Task* CurrentTask;

    // FIXME CRAP TODO FIX
    static inline bool Interrupted;

    //
    // Base functions
    //

    //
    //  New engine: Return stack, struct stack, etc.
    //

    static void CriticalExecute(Task* task);

    static void Execute(Task* Current);

    static void Interrupt(s4 Index);

    // Native functions implemented via Native Bus

    static bool HALCall(Method* Executable, Object **Arguments, Task* currentTask);
};
