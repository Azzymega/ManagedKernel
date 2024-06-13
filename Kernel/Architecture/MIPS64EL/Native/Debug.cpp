#include "Debug.hpp"

#define SerialPort 0x3f8

void outb(const u2 address, const u1 data) {
    auto const value = reinterpret_cast<u1 *>(0x1fd00000)+address;
    *value = data;
}

u1 inb(const u2 address) {
    auto const value = reinterpret_cast<u1 *>(0x1fd00000)+address;
    return *value;
}

void InitializeHAL() {
    InitializeSerial();
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
    while ((inb(SerialPort + 5) & 0x20) == 0);

    outb(SerialPort,Data);
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