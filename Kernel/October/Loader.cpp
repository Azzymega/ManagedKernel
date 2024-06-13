#include "Loader.h"

extern World *Pointer;

Class *Loader::Load(void *Binary) {

    Reader.Initialize(Binary);

    Class *Value = Pointer->Class();

    Buffer = Value;

    u4 Magic = Reader.GetI();

    if (Magic != 0xcafebabe) {

        return nullptr;

    }

    Value->Minor = Reader.GetS();
    Value->Major = Reader.GetS();

    Value->Pool = LoadPool();
    Value->Flag = Reader.GetS();

    u2 ThisClass = Reader.GetS();
    u2 SuperIndex = Reader.GetS();

    if (SuperIndex != 0) {

        Value->Super = static_cast<Class *>(Value->Pool->GetObject(SuperIndex));

    }

    Value->Name = ((Class *) Value->Pool->GetObject(ThisClass))->Name;

    printf("[Draco] Class ");
    Value->Name->Log();
    println(" loaded!");

    Value->Pool->Set(ThisClass, Value);

    Value->Interfaces = LoadInterfaces();
    Value->Fields = LoadFields();
    Value->Methods = LoadMethods();

    return Value;

}

Array *Loader::LoadPool() {

    u2 Count = Reader.GetS();

    NAT CMap[Count + 1];
    OType Map[Count + 1];

    memset((char *) CMap, 0, (((size_t) Count + 1) * sizeof(NAT)));
    memset((char *) Map, 0, (((size_t) Count + 1) * sizeof(OType)));

    Array *Pool = Pointer->List(Count);

    for (s4 i = 1; i < Count; ++i) {

        OType Tag = (OType) Reader.GetB();

        Map[i] = Tag;
        // SWITCH прыгает за память. Стек уничтожен или я хз что вообще происходит
        switch (Tag) {

            case TInteger: {
                Pool->Set(i, Pointer->Integer(Reader.GetI()));

                break;

            }

            case TFloat: {
                Pool->Set(i, Pointer->Float(Reader.GetI()));

                break;

            }

            case TLong: {

                u4 High = Reader.GetI();
                u4 Low = Reader.GetI();

                Pool->Set(i, Pointer->Long(High | Low));

                i++;

                break;

            }

            case TDouble: {

                u4 High = Reader.GetI();
                u4 Low = Reader.GetI();

                Pool->Set(i, Pointer->Double(High | Low));

                i++;

                break;

            }

            case TUTF: {

                u2 Length = Reader.GetS();

                char StringPool[Length + 2];

                for (int j = 0; j < Length; ++j) {

                    StringPool[j] = Reader.GetB();

                }

                StringPool[Length] = '\0';

                Pool->Set(i, Pointer->String(StringPool));

                break;

            }

            case TClass: {
                CMap[i].ClassIndex = Reader.GetS();

                break;
            }


            case TField:
            case TMethod:
            case TInterfaceMethod: {
                CMap[i].ClassIndex = Reader.GetS();
                CMap[i].NATIndex = Reader.GetS();

                break;
            }


            case TString: {
                CMap[i].First = Reader.GetS();

                break;

            }


            case TNAT: {
                CMap[i].First = Reader.GetS();
                CMap[i].Second = Reader.GetS();

                break;


            }


        }

    }

    // First roll

    for (int i = 1; i < Count + 1; ++i) {

        switch (Map[i]) {

            case TString: {

                Pool->Set(i, Pool->GetObject(CMap[i].First));

                break;

            }
            case TClass : {

                Class *Instantiable = Pointer->Class();

                Instantiable->Name = static_cast<String *>(Pool->GetObject(CMap[i].ClassIndex));

                Pool->Set(i, Instantiable);

                break;
            }

            default: {
                break;
            }

        }

    }

    // Second roll

    for (int i = 1; i < Count + 1; ++i) {

        switch (Map[i]) {

            case TMethod:
            case TInterfaceMethod: {

                Method *Value = Pointer->Method();

                Value->Name = static_cast<String *>(Pool->GetObject(CMap[CMap[i].NATIndex].First));
                Value->Signature = static_cast<String *>(Pool->GetObject(CMap[CMap[i].NATIndex].Second));
                Value->Owner = static_cast<Class *>(Pool->GetObject(CMap[i].ClassIndex));

                Pool->Set(i, Value);

                Pool->Set(CMap[i].NATIndex, Value);

                break;

            }

            case TField: {


                Field *Value = Pointer->Field();

                Value->Name = static_cast<String *>(Pool->GetObject(CMap[CMap[i].NATIndex].First));
                Value->Signature = static_cast<String *>(Pool->GetObject(CMap[CMap[i].NATIndex].Second));
                Value->Owner = static_cast<Class *>(Pool->GetObject(CMap[i].ClassIndex));

                Pool->Set(i, Value);

                Pool->Set(CMap[i].NATIndex, Value);

                break;

            }
            default: {
                break;
            }

        }

    }

    return Pool;

}

Array *Loader::LoadInterfaces() {

    u2 Count = Reader.GetS();

    Array *Interfaces = Pointer->List(Count);

    for (int i = 0; i < Count; ++i) {

        u2 ClassIndex = Reader.GetS();

        Class *Value = static_cast<Class *>(Buffer->Pool->GetObject(ClassIndex));

        Interfaces->Set(i, Value);

    }

    return Interfaces;

}

Array *Loader::LoadFields() {

    u2 Count = Reader.GetS();

    Array *Fields = Pointer->List(Count);

    for (int i = 0; i < Count; ++i) {

        Field *Value = Pointer->Field();

        Value->Flag = Reader.GetS();
        Value->Owner = Buffer;

        u2 Name = Reader.GetS();
        u2 Descriptor = Reader.GetS();

        Value->Name = static_cast<String *>(Buffer->Pool->GetObject(Name));
        Value->Signature = static_cast<String *>(Buffer->Pool->GetObject(Descriptor));

        switch (Value->Signature->Data->GetCharacter(0)) {
            case 'B':
            case 'Z': {
                Value->Length = sizeof(ManagedBoolean);
                break;
            }
            case 'C':
            case 'S': {
                Value->Length = sizeof(ManagedChar);
                break;
            }
            case 'I':
            case 'F': {
                Value->Length = sizeof(ManagedInteger);
                break;
            }
            case 'J':
            case 'D' : {
                Value->Length = sizeof(ManagedLong);
            }
            default: {
                Value->Length = sizeof(uintptr_t);
                break;
            }
        }

        Fields->Set(i, Value);

        u2 AttributeCount = Reader.GetS();

        for (int j = 0; j < AttributeCount; ++j) {
            Reader.GetS();
            Reader.Wind(Reader.GetI());
        }

    }

    return Fields;

}

Array *Loader::LoadMethods() {

    u2 Count = Reader.GetS();

    Array *Methods = Pointer->List(Count);

    for (int i = 0; i < Count; ++i) {

        Method *Value = Pointer->Method();

        Value->Flag = Reader.GetS();
        Value->Owner = Buffer;

        u2 Name = Reader.GetS();
        u2 Descriptor = Reader.GetS();

        Value->Name = static_cast<String *>(Buffer->Pool->GetObject(Name));
        Value->Signature = static_cast<String *>(Buffer->Pool->GetObject(Descriptor));

        u2 Attributes = Reader.GetS();

        Methods->Set(i, Value);

        for (int j = 0; j < Attributes; ++j) {

            if (((String*)Buffer->Pool->GetObject(Reader.GetS()))->Equals("Code")) {

                Code *MethodCode = Pointer->Code();

                u4 AttributeLength = Reader.GetI();

                u4 PointerBack = Reader.Check();

                MethodCode->Stack = Reader.GetS();
                MethodCode->Registers = Reader.GetS();

                u4 Length = Reader.GetI();

                Array *Bytecode = Pointer->List(Length);

                MethodCode->Bytecode = Bytecode;
                MethodCode->Owner = Value;

                for (int k = 0; k < Length; ++k) {

                    Bytecode->Set(k, (ManagedByte) Reader.GetB());

                }

                Value->Instructions = MethodCode;

                Reader.Set(PointerBack);

                Reader.Wind(AttributeLength);
            }
            else {
                for (int z = 1; z < Attributes; ++z) {
                    Reader.Wind(Reader.GetI());
                }
            }

        }


    }

    return Methods;

}

Vector *Archiver::Load(void *Binary, int Size) {

    Vector *RAF = Pointer->Vector(10);

    Reader.Initialize(Binary);

    Reader.Pointer = Size - 1;

    Reader.Unwind = true;

    EOCD End = EOCD();

    End.CommentLength = Reader.GetS();
    End.CentralDirectoryOffset = Reader.GetI();
    End.RecordsSize = Reader.GetI();
    End.TotalRecords = Reader.GetS();
    End.DiskRecords = Reader.GetS();
    End.StartDisk = Reader.GetS();
    End.DiskNumber = Reader.GetS();
    End.Signature = Reader.GetI();

    Reader.Unwind = false;
    Reader.Pointer = End.CentralDirectoryOffset;

    CDFH CentralRecords[End.TotalRecords];
    char Filenames[End.TotalRecords][100];
    u2 FilenamesLength[End.TotalRecords];

    memset((char *) CentralRecords, 0, ((size_t) End.TotalRecords * sizeof(CDFH)));
    memset((char *) Filenames, 0, ((size_t) End.TotalRecords * 100 * sizeof(char)));
    memset((char *) FilenamesLength, 0, ((size_t) End.TotalRecords * sizeof(u2)));

    for (int i = 0; i < End.TotalRecords; ++i) {
        CentralRecords[i].Signature = Reader.GetI();
        CentralRecords[i].Version = Reader.GetS();
        CentralRecords[i].Extract = Reader.GetS();
        CentralRecords[i].GPFlag = Reader.GetS();
        CentralRecords[i].Method = Reader.GetS();
        CentralRecords[i].ModTime = Reader.GetS();
        CentralRecords[i].ModDate = Reader.GetS();
        CentralRecords[i].CRC = Reader.GetI();
        CentralRecords[i].CompSize = Reader.GetI();
        CentralRecords[i].NonCompSize = Reader.GetI();
        CentralRecords[i].NameLength = Reader.GetS();
        CentralRecords[i].Extra = Reader.GetS();
        CentralRecords[i].Comment = Reader.GetS();
        CentralRecords[i].DiskNumber = Reader.GetS();
        CentralRecords[i].Internal = Reader.GetS();
        CentralRecords[i].External = Reader.GetI();
        CentralRecords[i].LocalHeaderOffset = Reader.GetI();

        FilenamesLength[i] = CentralRecords[i].NameLength;

        for (int j = 0; j < CentralRecords[i].NameLength; ++j) {
            Filenames[i][j] = Reader.GetB();
        }

        Filenames[i][CentralRecords[i].NameLength] = '\0';

        printf("[DracoLd] loading: ");
        println(Filenames[i]);

    }

    LFH FileHeaders[End.TotalRecords];

    for (int i = 0; i < End.TotalRecords; ++i) {
        Reader.Pointer = CentralRecords[i].LocalHeaderOffset;
        FileHeaders[i].Signature = Reader.GetI();
        FileHeaders[i].ExtractVersion = Reader.GetS();
        FileHeaders[i].GPFlag = Reader.GetS();
        FileHeaders[i].Compression = Reader.GetS();
        FileHeaders[i].ModTime = Reader.GetS();
        FileHeaders[i].ModDate = Reader.GetS();
        FileHeaders[i].CRC = Reader.GetI();
        FileHeaders[i].CompSize = Reader.GetI();
        FileHeaders[i].NonCompSize = Reader.GetI();
        FileHeaders[i].NameLength = Reader.GetS();
        FileHeaders[i].ExtraLength = Reader.GetS();
        Reader.Pointer += FileHeaders[i].NameLength;
        Reader.Pointer += FileHeaders[i].ExtraLength;

        if (FileHeaders[i].NonCompSize > 0 && Filenames[i][FilenamesLength[i] - 6] == '.' &&
            Filenames[i][FilenamesLength[i] - 1] != '/') {
            u1 Data[FileHeaders[i].NonCompSize];

            for (int j = 0; j < FileHeaders[i].NonCompSize; ++j) {
                Data[j] = Reader.GetB();
            }

            RAF->Add(Pointer->File(FileHeaders[i].NonCompSize, Data));
        }

    }

    return RAF;
}
