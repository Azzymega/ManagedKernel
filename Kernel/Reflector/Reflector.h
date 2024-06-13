#pragma once

#include "Kernel/C/string.hpp"
#include "Kernel/C/stdio.hpp"
#include "Kernel/Ke/HAL.hpp"
#include "UUID.h"
#include "Embedded.h"

#define ExperienceSize 1000000
#define DefaultOffset 300
#define MinimalAllocation 4

//
// List Extensions
//

enum ArrayType : ManagedByte {
    ATObject,
    ATByte,
    ATInt,
    ATShort,
    ATChar,
    ATDouble,
    ATFloat,
    ATLong
};

using ArrayMember = s8;

struct Array {

    ManagedInteger Size;

    ManagedBoolean Marked;

    ManagedInteger Length;

    union {

        Object* Objects[];
        ManagedByte Bytes[0];
        ManagedInteger Integers[0];
        ManagedBoolean Booleans[0];
        ManagedChar Characters[0];
        ManagedDouble Doubles[0];
        ManagedShort Shorts[0];
        ManagedLong Longs[0];
        ManagedFloat Floats[0];

    };

    void Bootstrap(s4 Length);

    void Initialize(s4 Length);

    void Set(s4 Index, Object* Value);
    void Set(s4 Index, ManagedByte Value);
    void Set(s4 Index, ManagedInteger Value);
    void Set(s4 Index, ManagedBoolean Value);
    void Set(s4 Index, ManagedChar Value);
    void Set(s4 Index, ManagedDouble Value);
    void Set(s4 Index, ManagedShort Value);
    void Set(s4 Index, ManagedLong Value);
    void Set(s4 Index, ManagedFloat Value);

    Object* GetObject(s4 Index);
    ManagedByte GetByte(s4 Index);
    ManagedInteger GetInteger(s4 Index);
    ManagedBoolean GetBoolean(s4 Index);
    ManagedChar GetCharacter(s4 Index);
    ManagedDouble GetDouble(s4 Index);
    ManagedShort GetShort(s4 Index);
    ManagedLong GetLong(s4 Index);
    ManagedFloat GetFloat(s4 Index);

};

//
// Holders
//

struct World : Object {

    ManagedInteger Count;

    Array* Experiences;

    void Initialize(s4 Count);

    void* Allocate(s4 Size);
    void* Allocate(s4 Size, s4 Free) const;

    Array* List(s4 Length);

    // Smart Allocation Extension

    void* Allocate(Class* Instantiable);

    // Builtin Extension

    Vector* Vector(s4 Length);
    Integer* Integer(s4 Value);
    String* String(const char* Value);
    Long* Long(s8 Value);
    Float* Float(fl Value);
    Double* Double(dl Value);

    Stack* Stack(s4 Length);

    Class* Class();
    Method* Method();
    Code* Code();
    Field* Field();
    Task* Task();

    RandomAccessFile *File(ManagedInteger Length, void *Data);
};

struct Experience : Object {

    ManagedBoolean Full;

    ManagedInteger Allocated;
    ManagedInteger Objects;

    ManagedInteger Free;

    Array* Space;

    void Initialize();

    void* Allocate(s4 Size);

};



