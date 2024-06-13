#include "Embedded.h"

#include "Kernel/Reflector/Reflector.h"

extern World* Pointer;

void Object::Base() {

    this->Monitor = false;
    this->Instance = nullptr;
    this->Identifier = nullptr;
    this->Properties = nullptr;
    this->Marked = false;

}

void Object::Register() {

    Base();

    this->Identifier = Pointer->List(UUIDLength);

    GenerateUUID(this->Identifier->Characters);

}

void String::Initialize(const char *String) {

    Register();

    Size = sizeof(String);

    this->Native = NString;

    this->Length = strlen(String);

    this->Data = Pointer->List(Length);

    for (int i = 0; i < Length; ++i) {

        this->Data->Set(i,(ManagedChar)String[i]);

    }

}

ManagedBoolean String::Equals(String *Other) {

    if (this->Length != Other->Length) {
        return false;
    }

    ManagedChar First[this->Length];
    ManagedChar Second[Other->Length];

    memcpy(First,this->Data->Characters,sizeof(ManagedChar)*this->Length);
    memcpy(Second,Other->Data->Characters,sizeof(ManagedChar)*Other->Length);

    if (memcmp(First,Second,sizeof(ManagedChar)*this->Length) == 0) {
        return true;
    }

    return false;
}

void String::Log() {

    for (int i = 0; i < this->Length; ++i) {

        wchar_t val[1];
        val[0] = this->Data->GetCharacter(i);
        printf((const char*)val);

    }

}

ManagedBoolean String::Equals(const char *String) {

    ManagedInteger StringLength = strlen(String);

    if (this->Length != StringLength) {
        return false;
    }

    ManagedChar First[this->Length];
    ManagedChar Second[StringLength];

    memcpy(First,this->Data->Characters,sizeof(ManagedChar)*this->Length);

    for (int i = 0; i < StringLength; ++i) {
        Second[i] = String[i];
    }

    if (memcmp(First,Second,sizeof(ManagedChar)*this->Length) == 0) {
        return true;
    }

    return false;

}

void String::Print() {
    Log();
}

void Integer::Initialize(ManagedInteger Value) {

    Register();

    this->Native = NInteger;

    Size = sizeof(Integer);

    this->Value = Value;

}

void Double::Initialize(dl Value) {

    Register();

    Size = sizeof(Double);

    this->Value = Value;

}

void Long::Initialize(s8 Value) {

    Register();

    this->Native = NLong;

    Size = sizeof(Long);

    this->Value = Value;

}

void Float::Initialize(fl Value) {

    Register();

    this->Native = NFloat;

    Size = sizeof(Float);

    this->Value = Value;

}

void Class::Initialize() {

    Register();

    this->Native = NClass;

    Size = sizeof(Class);

}

void Code::Initialize() {

    Register();

    Size = sizeof(Code);

}

void Method::Initialize() {

    Register();

    this->Native = NMethod;

    Size = sizeof(Method);

}

void Field::Initialize() {

    Register();

    this->Native = NField;

    Size = sizeof(Field);

}

void Stack::Initialize(ManagedInteger Length) {

    Register();

    Size = sizeof(Stack);

    this->Count = 0;

    this->Objects = Pointer->List(Length);

}

Object* Stack::TopAndPop() {

    if (Count < 1) {
        return nullptr;
    }
    else {
        Object* Value = Objects->GetObject(Count-1);
        Count--;
        return Value;
    }

}

Object *Stack::Top() {
    if (Count < 1) {
        return nullptr;
    }
    else {
        return Objects->GetObject(Count-1);
    }
}

void Stack::Push(Object *Value) {

    Objects->Set(Count++,Value);

}

void Stack::Pop() {

    Count--;

}

void Task::Initialize() {

    Register();

    Size = sizeof(Task);

    this->Counter = 0;

    this->Switched = false;

    this->Native = NativeType::NTask;

}

void Vector::Initialize(ManagedInteger Length) {

    Register();

    Size = sizeof(Vector);

    this->Allocated = Length;

    this->Native = NVector;

    this->Count = 0;

    this->Objects = Pointer->List(Length);

}

void Vector::Add(Object *Value) {

    if (this->Count + 1 == this->Allocated) {

        Array* NewArray = Pointer->List(this->Allocated*2);

        this->Allocated *= 2;

        for (int i = 0; i < this->Objects->Length; ++i) {
            NewArray->Set(i,this->Objects->GetObject(i));
        }

        this->Objects = NewArray;

        this->Objects->Set(this->Count-1,Value);

        return;

    }

    this->Objects->Set(this->Count++,Value);

}

Object* Vector::Get(ManagedInteger Index) {

    return this->Objects->GetObject(Index);

}

void Vector::Set(ManagedInteger Index, Object *Value) {

    this->Objects->Set(Index,Value);

}

void RandomAccessFile::Initialize(ManagedInteger Length) {

    Register();

    Size = sizeof(Vector);

    this->Length = Length;

    this->Data = Pointer->List(Length);

}
