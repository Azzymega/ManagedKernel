#include "Reflector.h"


void World::Initialize(s4 Count) {

    Base();

    this->Count = Count;

    char* Pointer = reinterpret_cast<char *>(this);

    this->Experiences = reinterpret_cast<Array *>(Pointer + sizeof(World));

    this->Experiences->Initialize(Count);

    this->Experiences->Bootstrap(Count);

}

void *World::Allocate(s4 Size) {

    for (int i = 0; i < Count; ++i) {

        Experience* Block = (Experience*)(Experiences->GetObject(i));

        if (!Block->Full && Block->Free > Size) {

            return Block->Allocate(Size);

        }

    }

    return nullptr;

}

String *World::String(const char *Value) {

    auto* Object = static_cast<struct String *>(this->Allocate(sizeof(struct String), DefaultOffset+(strlen(Value)*sizeof(ArrayMember))));

    Object->Initialize(Value);

    return Object;

}

Array *World::List(s4 Length) {

    Array *Value = static_cast<Array *>(this->Allocate(sizeof(Array) + (sizeof(ArrayMember) * Length),DefaultOffset));

    Value->Initialize(Length);

    return Value;

}


Integer *World::Integer(s4 Value) {

    auto* Object = static_cast<struct Integer *>(this->Allocate(sizeof(struct Integer), DefaultOffset));

    Object->Initialize(Value);

    return Object;

}

void *World::Allocate(s4 Size, s4 Free) const {

    for (int i = 0; i < Count; ++i) {

        Experience* Block = (Experience*)(Experiences->GetObject(i));

        if (!Block->Full && Block->Free > Free + Size) {

            return Block->Allocate(Size);

        }

    }

    return nullptr;

}

Long *World::Long(s8 Value) {

    auto* Object = static_cast<struct Long *>(this->Allocate(sizeof(struct Long), DefaultOffset));

    Object->Initialize(Value);

    return Object;

}

Float* World::Float(fl Value) {

    auto* Object = static_cast<struct Float *>(this->Allocate(sizeof(struct Float), DefaultOffset));

    Object->Initialize(Value);

    return Object;

}

Double *World::Double(dl Value) {

    auto* Object = static_cast<struct Double *>(this->Allocate(sizeof(struct Double), DefaultOffset));

    Object->Initialize(Value);

    return Object;

}

Stack* World::Stack(s4 Length) {

    auto* Object = static_cast<struct Stack *>(this->Allocate(sizeof(struct Stack), DefaultOffset));

    Object->Initialize(Length);

    return Object;

}

Class *World::Class() {

    auto* Object = static_cast<struct Class *>(this->Allocate(sizeof(struct Class), DefaultOffset));

    Object->Initialize();

    return Object;

}

Method *World::Method() {

    auto* Object = static_cast<struct Method *>(this->Allocate(sizeof(struct Method), DefaultOffset));

    Object->Initialize();

    return Object;

}

Code *World::Code() {

    auto* Object = static_cast<struct Code *>(this->Allocate(sizeof(struct Code), DefaultOffset));

    Object->Initialize();

    return Object;

}

Field *World::Field() {

    auto* Object = static_cast<struct Field *>(this->Allocate(sizeof(struct Field), DefaultOffset));

    Object->Initialize();

    return Object;

}

Task *World::Task() {

    auto* Object = static_cast<struct Task *>(this->Allocate(sizeof(struct Task), DefaultOffset));

    Object->Initialize();

    return Object;

}

RandomAccessFile* World::File(ManagedInteger Length, void* Data) {

    auto* Object = static_cast<struct RandomAccessFile *>(this->Allocate(sizeof(struct RandomAccessFile), DefaultOffset));

    Object->Initialize(Length);

    memcpy(Object->Data->Bytes,Data,Length);

    return Object;

}

void *World::Allocate(struct Class *Instantiable) {

    ManagedLong Size = 0;

    struct Class* Check = Instantiable;

    while (Check) {

        for (int i = 0; i < Check->Fields->Length; ++i) {

            struct Field* Value = static_cast<struct Field *>(Check->Fields->GetObject(i));

            if ((Value->Flag & FAStatic) == 0) {
                Size += Value->Length;
            }

        }

        Check = Check->Super;

    }

    auto* Pointer = static_cast<Object *>(this->Allocate(Size, DefaultOffset));

    Pointer->Instance = Instantiable;
    Pointer->Size = Size;

    return Pointer;

}

Vector *World::Vector(s4 Length) {

    auto* Object = static_cast<struct Vector *>(this->Allocate(sizeof(struct Task), DefaultOffset));

    Object->Initialize(Length);

    return Object;
}


void Array::Initialize(s4 Length) {

    // FIXME HORRIBLE SIZE
    this->Size = sizeof(Array) + (sizeof(ArrayMember) * Length);

    this->Length = Length;

    this->Marked = false;

}

void Array::Set(s4 Index, Object *Value) {

    this->Objects[Index] = Value;

}

void Array::Set(s4 Index, ManagedByte Value) {

    this->Bytes[Index] = Value;

}

void Array::Set(s4 Index, ManagedInteger Value) {

    this->Integers[Index] = Value;

}

void Array::Set(s4 Index, ManagedBoolean Value) {

    this->Booleans[Index] = Value;

}

void Array::Set(s4 Index, ManagedChar Value) {

    this->Characters[Index] = Value;

}

void Array::Set(s4 Index, ManagedDouble Value) {

    this->Doubles[Index] = Value;

}

void Array::Set(s4 Index, ManagedShort Value) {

    this->Shorts[Index] = Value;

}

void Array::Set(s4 Index, ManagedLong Value) {

    this->Longs[Index] = Value;

}

void Array::Set(s4 Index, ManagedFloat Value) {

    this->Floats[Index] = Value;

}

Object *Array::GetObject(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");

    }

    return static_cast<Object *>(this->Objects[Index]);

}

ManagedByte Array::GetByte(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Bytes[Index];

}

ManagedInteger Array::GetInteger(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Integers[Index];

}

ManagedBoolean Array::GetBoolean(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Booleans[Index];

}

ManagedChar Array::GetCharacter(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Characters[Index];

}

ManagedDouble Array::GetDouble(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Doubles[Index];

}

ManagedShort Array::GetShort(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Shorts[Index];

}

ManagedLong Array::GetLong(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Longs[Index];

}

ManagedFloat Array::GetFloat(s4 Index) {

    if (Index > this->Length) {
        printf("Array index overflow\n");
    }

    return this->Floats[Index];

}

void Array::Bootstrap(s4 Length) {

    char* Pointer = reinterpret_cast<char *>(this);

    Pointer += sizeof(Array) + (sizeof(ArrayMember) * Length);

    for (int i = 0; i < Length; ++i) {

        auto* Block = reinterpret_cast<Experience *>(Pointer + ExperienceSize);

        Block->Initialize();

        Set(i,Block);

        Pointer = reinterpret_cast<char *>(Block);

    }

}

void Experience::Initialize() {

    char* Pointer = reinterpret_cast<char *>(this);

    Pointer += sizeof(Experience);

    this->Space = reinterpret_cast<Array *>(Pointer);

    this->Space->Initialize(ExperienceSize);

    this->Full = false;
    this->Allocated = 0;
    this->Objects = 0;
    this->Free = ExperienceSize;

}

void* Experience::Allocate(s4 Size) {

    u1* Pointer = reinterpret_cast<u1 *>(&Space->Bytes[Allocated]);

    Allocated+=Size;
    Objects+=1;
    Free-=Size;

    return Pointer;

}

