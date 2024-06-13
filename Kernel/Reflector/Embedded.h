#pragma once

#include "Kernel/Ke/HAL.hpp"
#include "Kernel/C/string.hpp"
#include "Kernel/C/stdio.hpp"

struct Array;
struct Class;

//
// Type Definitions
//

enum FieldAccessType : ManagedShort {
    FAPublic = 0x0001,
    FAPrivate = 0x0002,
    FAProtected = 0x0004,
    FAStatic = 0x0008,
    FAFinal = 0x0010,
    FAVolatile = 0x0040,
    FATransient = 0x0080,
    FASynthetic = 0x1000,
    FAEnum = 0x4000
} __attribute__((__packed__));

enum NativeType : ManagedInteger {
    NClass = 23,
    NMethod = 44,
    NField = 566,
    NStruct = 234,
    NTask = 233,
    NInteger = 123,
    NFloat = 443,
    NLong = 32,
    NString = 13,
    NVector = 565
} __attribute__((__packed__));

//
// Main Definitions
//

struct Object {

    ManagedInteger Size;

    ManagedBoolean Marked;

    NativeType Native;

    ManagedBoolean Monitor;

    Array* Identifier;

    Array* Properties;

    Class* Instance;

    void Base();

    void Register();

} __attribute__((__packed__));

//
// Builtin Extension
//

struct Double : Object {

    ManagedDouble Value;

    void Initialize(dl Value);

} __attribute__((__packed__));

struct Float : Object {

    ManagedFloat Value;

    void Initialize(fl Value);

} __attribute__((__packed__));

struct Long : Object {

    ManagedLong Value;

    void Initialize(s8 Value);

} __attribute__((__packed__));

struct Integer : Object {

    ManagedInteger Value;

    void Initialize(ManagedInteger Value);

} __attribute__((__packed__));

struct String : Object {

    ManagedInteger Length;

    Array* Data;

    void Initialize(const char* String);

    ManagedBoolean Equals(String* Other);

    ManagedBoolean Equals(const char* String);

    // Debug only!

    void Log();
    void Print();

} __attribute__((__packed__));

struct Vector : Object {

    ManagedInteger Count;

    ManagedInteger Allocated;

    Array* Objects;

    void Initialize(ManagedInteger Length);

    void Add(Object* Value);

    Object* Get(ManagedInteger Index);

    void Set(ManagedInteger Index, Object* Value);

} __attribute__((__packed__));

struct Class : Object {

    ManagedInteger Minor;

    ManagedInteger Major;

    ManagedBoolean Linked;

    String* Name;

    Array* Pool;

    ManagedShort Flag;

    Class* Super;

    Array* Interfaces;

    Array* Fields;

    Array* Methods;

    Vector* Attributes;

    void Initialize();

} __attribute__((__packed__));

struct Method;

struct Code : Object {

    Method* Owner;

    ManagedInteger Stack;

    ManagedInteger Registers;

    Array* Bytecode;

    Array* Attributes;

    void Initialize();

} __attribute__((__packed__));

struct Method : Object {

    Class* Owner;

    String* Name;

    String* Signature;

    ManagedShort Flag;

    Code* Instructions;

    Vector* Attributes;

    void Initialize();

} __attribute__((__packed__));


struct Field : Object {

    Class* Owner;

    String* Name;

    String* Signature;

    ManagedShort Flag;

    ManagedInteger Length;

    Object* Value;

    Vector* Attributes;

    void Initialize();

} __attribute__((__packed__));

struct Stack : Object {

    ManagedInteger Count;

    Array* Objects;

    void Initialize(ManagedInteger Length);

    Object* TopAndPop();

    Object* Top();

    void Push(Object* Value);
    
    void Pop();

} __attribute__((__packed__));

struct RandomAccessFile : Object {

    ManagedInteger Length;

    Array* Data;

    void Initialize(ManagedInteger Length);

} __attribute__((__packed__));

struct Task : Object {

    Stack* Stack;

    Array* Registers;

    ManagedLong Counter;

    ManagedBoolean Switched;

    Code* Instructions;

    Class* Link;

    Array* Attributes;

    void Initialize();

} __attribute__((__packed__));
