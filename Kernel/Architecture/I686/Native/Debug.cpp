#include "Debug.hpp"

#include <Kernel/Runtime/Engine.h>

#define SerialPort 0x3f8

void InitializeHAL() {
    InitializeSerial();
    InitializeGDT();
    InitializeInterrupts();
}

void InitializeSerial() {
    outb(SerialPort + 1, 0x00);
    outb(SerialPort + 3, 0x80);
    outb(SerialPort + 0, 0x03);
    outb(SerialPort + 1, 0x00);
    outb(SerialPort + 3, 0x03);
    outb(SerialPort + 2, 0xC7);
    outb(SerialPort + 4, 0x0B);
    outb(SerialPort + 4, 0x1E);
    outb(SerialPort + 0, 0xAE);
    outb(SerialPort + 4, 0x0F);
}

void SendSerial(char Data) {
    while ((inb(SerialPort + 5) & 0x20) == 0) {}

    outb(SerialPort,Data);
}

//
//  Hal
//

void SpaceWrite(s4 Index, const s4 Type, s4 Value) {
    switch (Type) {
        case 1:
            outb(Index,Value);
            break;
        case 2:
            outw(Index,Value);
            break;
        case 3:
            outdw(Index,Value);
            break;
        default:
            break;
    }
}

s4 SpaceRead(const s4 Index, const s4 Type) {
    switch (Type) {
        case 1:
            return inb(Index);
        break;
        case 2:
            return inw(Index);
        break;
        case 3:
            return indw(Index);
        break;
        default:
            return -1;
            break;
    }
}

void RouteInterrupt(const u4 Index) {
    Executive::Interrupt(Index);
}


void CriticalStart() {
    if (!Executive::Interrupted) {
        asm ("cli");
    }

}

void CriticalEnd() {
    if (!Executive::Interrupted) {
        asm ("sti");
    }
}

void out(const char* Message) {
    size_t messageLength = strlen(Message);

    for (size_t i = 0; i < messageLength; ++i) {
        SendSerial(Message[i]);
    }
}
