
#include "Kernel/Ke/HAL.hpp"
#include "Kernel/C/string.hpp"

extern "C" {
    void InitializeHAL();

    void InitializeSerial();
    void SendSerial(char Data);
}

extern "C" {
    void CriticalStart();
    void CriticalEnd();
    void out(const char* Message);
}
