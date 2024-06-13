#include "string.hpp"

void* memcpy(void* dest, const void* src, size_t n) {
    const u4 aligned = n / 4;
    const u4 out = n % 4;

    for (size_t i = 0; i < aligned; ++i) {

        u4* FirstValue = (u4 *) dest;
        const u4* SecondValue = (u4 *) src;

        FirstValue[i] = SecondValue[i];

    }

    for (size_t i = 0; i < out; i++) {
        u1* FirstValue = (u1*)dest+(aligned*4);
        const u1* SecondValue = (u1*)src+(aligned*4);

        FirstValue[i] = SecondValue[i];
    }

    return dest;

}

void* memmove(void* dstptr, const void* srcptr, size_t size) {

    auto* dst = (unsigned char*) dstptr;
    const auto* src = (const unsigned char*) srcptr;

    if (dst < src) {

        for (size_t i = 0; i < size; i++)

            dst[i] = src[i];

    } else {

        for (size_t i = size; i != 0; i--)

            dst[i-1] = src[i-1];
    }
    return dstptr;
}

int memcmp(const void* aptr, const void* bptr, size_t size) {

    const u4 aligned = size / 4;
    const u4 out = size % 4;

    for (size_t i = 0; i < aligned; ++i) {

        const u4* FirstValue = (const u4 *) aptr;
        const u4* SecondValue = (const u4 *) bptr;

        if (FirstValue[i] < SecondValue[i]) {
            return -1;
        }
        else if (FirstValue[i] > SecondValue[i]) {
            return 1;
        }

    }

    const unsigned char* a = ( unsigned char*) aptr+(aligned*4);
    const unsigned char* b = ( unsigned char*) bptr+(aligned*4);

    for (size_t i = 0; i < out; i++) {

        if (a[i] < b[i])

            return -1;

        else if (b[i] < a[i])

            return 1;
    }

    return 0;
}

void* memset(char* dest, int z, size_t n) {

    for (size_t i = 0; i < n; i++) {
        dest[i] = z;
    }

    return dest;
}

size_t strlen(const char* string) {
    size_t Length = 0;

    while (string[Length]) {
        Length++;
    }

    return Length;
}

int strcmp(const char* firstString, const char* secondString) {

    while (( *firstString ) && ( *firstString == *secondString ))
    {

        ++firstString;
        ++secondString;

    }

    return ( *firstString - *secondString );
}
