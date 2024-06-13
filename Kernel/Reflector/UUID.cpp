#include "UUID.h"

void GenerateUUID(uc* Value) {

    srand ((uintptr_t)Value);
    int t = 0;
    const char *szTemp = "xxxxxxxxxxxxxxxxxxx";
    const char *szHex = "0123456789ABCDEFabcdef";
    size_t nLen = strlen (szTemp);

    for (size_t t=0; t<nLen+1; t++)
    {
        int r = rand () % 16;
        char c = ' ';

        switch (szTemp[t])
        {
            case 'x' : { c = szHex [r]; } break;
            case 'y' : { c = szHex [r & 0x03 | 0x08]; } break;
            case '-' : { c = '-'; } break;
            case '4' : { c = '4'; } break;
        }

        ((uc*)Value)[t] = ( t < nLen ) ? c : 0x00;
    }

}

void GenerateNullUUID(uc* Buffer) {


    for (int i = 0; i < sizeof(UUIDLength); ++i) {

        Buffer[i] = '\0';

    }


}

bool IsNullUUID(uc* Value) {

    for (int i = 0; i < sizeof(UUIDLength); ++i) {

        if (Value[i] != '\0') {
            return false;
        }

    }

    return true;

}