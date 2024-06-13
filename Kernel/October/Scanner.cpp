#include "Scanner.h"

u2 Scanner::GetS() {

    u1 Temp[2];
    Temp[0] = ((u1*)(this->Binary))[this->Pointer++];
    Temp[1] = ((u1*)(this->Binary))[this->Pointer++];
    return Temp[0] << 8 | Temp[1];

}

u1 Scanner::GetB() {

    u1 Temp[1];
    Temp[0] = ((u1*)(this->Binary))[this->Pointer++];
    return Temp[0];

}

u4 Scanner::GetI() {

    u1 Temp[4];
    Temp[0] = ((u1*)(this->Binary))[this->Pointer++];
    Temp[1] = ((u1*)(this->Binary))[this->Pointer++];
    Temp[2] = ((u1*)(this->Binary))[this->Pointer++];
    Temp[3] = ((u1*)(this->Binary))[this->Pointer++];
    return Temp[3] << 0 | Temp[2] << 8 | Temp[1] << 16 | Temp[0] << 24;

}

void Scanner::Rewind(u4 Count) {

    this->Pointer-=Count;

}

void Scanner::Initialize(void *Binary) {

    this->Binary = Binary;
    this->Pointer = 0;

}

void Scanner::Wind(u4 Count) {

    this->Pointer+=Count;

}

void Scanner::Set(u4 Count) {

    this->Pointer = Count;

}

u4 Scanner::Check() const {

    return this->Pointer;

}

void LScanner::Initialize(void *Binary) {
    this->Binary = static_cast<char *>(Binary);
}

u1 LScanner::GetB() {

    if (Unwind) {

        return this->Binary[this->Pointer--];

    }

    return this->Binary[this->Pointer++];

}

u2 LScanner::GetS() {

    u1 Temp[2];

    if (Unwind) {

        Temp[0] = this->Binary[this->Pointer--];
        Temp[1] = this->Binary[this->Pointer--];
        return Temp[0] << 8 | Temp[1];

    }

    Temp[0] = this->Binary[this->Pointer++];
    Temp[1] = this->Binary[this->Pointer++];

    return Temp[1] << 8 | Temp[0];

}

u4 LScanner::GetI() {

    u1 Temp[4];

    if (Unwind) {

        Temp[0] = this->Binary[this->Pointer--];
        Temp[1] = this->Binary[this->Pointer--];
        Temp[2] = this->Binary[this->Pointer--];
        Temp[3] = this->Binary[this->Pointer--];

        return Temp[0] << 24 | Temp[1] << 16 | Temp[2] << 8 | Temp[3];

    }

    Temp[0] = this->Binary[this->Pointer++];
    Temp[1] = this->Binary[this->Pointer++];
    Temp[2] = this->Binary[this->Pointer++];
    Temp[3] = this->Binary[this->Pointer++];

    return Temp[3] << 24 | Temp[2] << 16 | Temp[1] << 8 | Temp[0];

}
