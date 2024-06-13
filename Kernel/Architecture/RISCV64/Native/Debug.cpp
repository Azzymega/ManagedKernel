#include "Debug.hpp"

#define UART 0x10000000

void InitializeHAL() {
    InitializeSerial();
}

void InitializeSerial() {

}

void SendSerial(char Data) {
    memset(((char*)UART),Data,sizeof(char));
}

//
//  Hal
//

void CriticalStart() {

}

void CriticalEnd() {

}

void out(const char* Message) {
    size_t messageLength = strlen(Message);

    for (size_t i = 0; i < messageLength; ++i) {
        SendSerial(Message[i]);
    }
}