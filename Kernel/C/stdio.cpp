#include "stdio.hpp"

void printf(const char* Message) {
    out(Message);
}

void puts(const char* Message) {
    printf(Message);
}

void println(const char* Message) {
    out(Message);
    out("\r");
    out("\n");
}

void printInteger(u4 Value) {
    char Buffer[35];

    printf(itoa(Value,Buffer,10));
}
