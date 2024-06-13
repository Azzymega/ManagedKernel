#include "Kernel/Ke/HAL.hpp"
#include "Kernel/Ke/Entry.hpp"

extern "C" void Start() {
    InitializeHAL();

    Entry();
}
