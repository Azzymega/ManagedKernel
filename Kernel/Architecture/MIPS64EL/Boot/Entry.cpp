#include "Kernel/Ke/HAL.hpp"
#include "Kernel/Ke/Entry.hpp"
#include "Kernel/Reflector/Reflector.h"

extern World* Pointer;

extern "C" void Start() {
    InitializeHAL();

    Pointer = reinterpret_cast<World *>(100000);

    Pointer->Initialize(15);

    Entry();
}
