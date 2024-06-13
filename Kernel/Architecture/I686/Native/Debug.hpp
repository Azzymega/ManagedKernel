
#include "Kernel/Ke/HAL.hpp"
#include "Kernel/C/string.hpp"
#include "IO.hpp"
#include "Interrupt.hpp"
#include "GDT.hpp"

extern "C" {
    void InitializeHAL();

    void InitializeSerial();
    void SendSerial(char Data);
}

extern "C" {
    void CriticalStart();
    void CriticalEnd();

    void RouteInterrupt(u4 Index);

    void SpaceWrite(s4 Index, s4 Type, s4 Value);
    s4 SpaceRead(s4 Index, s4 Type);

    void out(const char* Message);
}
