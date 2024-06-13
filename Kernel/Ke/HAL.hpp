#pragma once

#include "stdint.h"
#include "stddef.h"

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

using s1 = int8_t;
using s2 = int16_t;
using s4 = int32_t;
using s8 = int64_t;

using uc = wchar_t;
using bl = bool;

using u1 = uint8_t;
using u2 = uint16_t;
using u4 = uint32_t;
using u8 = uint64_t;

using fl = float;
using dl = double;

using ManagedByte = s1;
using ManagedShort = s2;
using ManagedChar = uc;
using ManagedInteger = s4;
using ManagedLong = s8;
using ManagedFloat = fl;
using ManagedDouble = dl;
using ManagedBoolean = bl;

//
//  Services
//

extern "C" {
    extern void InitializeHAL();

    extern void CriticalStart();
    extern void CriticalEnd();

    // state save?

    extern void RouteInterrupt(u4 Index);

    extern void SpaceWrite(s4 Index, s4 Type, s4 Value);
    extern s4 SpaceRead(s4 Index, s4 Type);

    extern void out(const char* Message);
}

