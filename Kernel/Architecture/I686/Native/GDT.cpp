#include "GDT.hpp"

static GDTEntry Entries[6];
static GDTPointer GDTSegmentPointer;

void InitializeGDT() {
    GDTController::Initialize();
}


void GDTController::Initialize() {

    GDTSegmentPointer.Limit = (sizeof(GDTEntry) * 6) - 1;
    GDTSegmentPointer.Base = reinterpret_cast<unsigned int>(&Entries);

    Set(0, 0, 0, 0, 0);
    Set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    Set(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    Set(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    Set(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    asm volatile ("lgdt %0" : "=m" (GDTSegmentPointer));

}

void GDTController::Set(const u4 Index, const u4 Base, const u4 Limit, const u1 Access, const u1 Granularity) {
    Entries[Index].BaseLow = (Base & 0xFFFF);
    Entries[Index].BaseMiddle = (Base >> 16) & 0xFF;
    Entries[Index].BaseHigh = (Base >> 24) & 0xFF;
    Entries[Index].LowLimit = (Limit & 0xFFFF);
    Entries[Index].Granularity = (Limit >> 16) & 0X0F;
    Entries[Index].Granularity |= (Granularity & 0xF0);
    Entries[Index].Access = Access;
}
