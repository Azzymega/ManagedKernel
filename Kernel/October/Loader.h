#pragma once

#include "Kernel/Reflector/Reflector.h"
#include "Kernel/Reflector/Embedded.h"

#include "Kernel/C/stdio.hpp"
#include "Kernel/C/string.hpp"

#include "Scanner.h"

enum OType : u1 {
    TClass = 7,
    TField = 9,
    TMethod = 10,
    TInterfaceMethod = 11,
    TString = 8,
    TInteger = 3,
    TFloat  = 4,
    TLong  = 5,
    TDouble = 6,
    TNAT = 12,
    TUTF = 1
};

enum OFlag : u2 {
    OPublic = 0x0001,
    OFinal = 0x0010,
    OSuper = 0x0020,
    OInterface = 0x0200,
    OAbstract = 0x0400
};

enum OField : u2 {
    OTPublic = 0x0001,
    OTPrivate = 0x0002,
    OTProtected = 0x0004,
    OTStatic = 0x0008,
    OTFinal = 0x0010,
    OTVolatile = 0x0040,
    OTTransient = 0x0080
};

enum OMethod : u2 {
    MTPublic = 0x0001,
    MTPrivate = 0x0002,
    MTProtected = 0x0004,
    MTStatic = 0x0008,
    MTFinal = 0x0010,
    MTSynchronized = 0x0020,
    MTNative = 0x0100,
    MTAbstract = 0x0400
};

struct NAT {

    u2 ClassIndex;
    u2 NATIndex;
    u2 First;
    u2 Second;

};

struct Loader {

    Scanner Reader;

    Class* Buffer;

    Class* Load(void* Binary);

    Array* LoadPool();

    Array* LoadInterfaces();
    Array* LoadFields();
    Array* LoadMethods();

};

//
//  ZIP Extension
//

struct Archiver {

    LScanner Reader;

    Vector* Load(void* Binary, int Size);

};

struct LFH {
    u4 Signature; // 0x04034b50
    u2 ExtractVersion;
    u2 GPFlag;
    u2 Compression;
    u2 ModTime;
    u2 ModDate;
    u4 CRC;
    u4 CompSize;
    u4 NonCompSize;
    u2 NameLength;
    u2 ExtraLength;
    char Filename[0];
    // Extra data
};

struct CDFH {
    u4 Signature; // 0x02014b50
    u2 Version;
    u2 Extract;
    u2 GPFlag;
    u2 Method;
    u2 ModTime;
    u2 ModDate;
    u4 CRC;
    u4 CompSize;
    u4 NonCompSize;
    u2 NameLength;
    u2 Extra;
    u2 Comment;
    u2 DiskNumber;
    u2 Internal;
    u4 External;
    u4 LocalHeaderOffset;
    char Filename[0];
};

struct EOCD {
    u4 Signature; // 0x06054b50
    u2 DiskNumber;
    u2 StartDisk;
    u2 DiskRecords;
    u2 TotalRecords;
    u4 RecordsSize;
    u4 CentralDirectoryOffset;
    u2 CommentLength;
    char Comment[0];
};