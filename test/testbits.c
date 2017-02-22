#include <stdio.h>
#include "bits.h"

unsigned float2Int(float f) {
    union {
        float f;
        unsigned i;
    } x;
    x.f = f;
    return x.i;
}

float int2Float(unsigned i) {
    union {
        float f;
        unsigned i;
    } x;
    x.i = i;
    return x.f;
}

int main(){
    printf("Testing bitNor(0x6, 0x5)\n");
    printf("%x\n", bitNor(0x6, 0x5));
    printf("Testing copyLSB(5) = 0xFFFFFFFF\n");
    printf("%x\n",  copyLSB(5));
    printf("Testing isEqual(5,5)=1, isEqual(4,5)=0\n");
    printf("%d\n", isEqual(5, 5));
    printf("%d\n", isEqual(4, 5));
    printf("Testing bitMask(5, 3) = 0x38\n");
    printf("%x\n", bitMask(5, 3));
    printf("Testing bitCount(5) = 2, bitCount(7) = 3\n");
    printf("%d\n", bitCount(5));
    printf("%d\n", bitCount(7));
    printf("Testing tmax\n");
    printf("%d\n", tmax());
    printf("Testing isNonNegative(-1) = 0, (1) = 1, (0) = 1\n");
    printf("%d\n", isNonNegative(-1));
    printf("%d\n", isNonNegative(1));
    printf("%d\n", isNonNegative(0));
    printf("Testing addOK, should yield 0 and 1\n");
    printf("%d\n", addOK(0x80000000,0x80000000));
    printf("%d\n", addOK(0x80000000,0x70000000));
    printf("Testing rempwr2(15,2)=3,rempwr2(-35,3)=-3, (0, 2) = 0\n");
    printf("%d\n", rempwr2(15,2));
    printf("%d\n", rempwr2(-35,3));
    printf("%d\n", rempwr2(0,2));
    printf("Testing isLessOrEqual(4,5) = 1\n");
    printf("%d\n", isLess(4,5));
    printf("Testing absVal(-1) = 1, (2) = 2\n");
    printf("%d\n", absVal(-1));
    printf("%d\n", absVal(2));
    printf("Testing isPower2(5) = 0, isPower2(8) = 1\n");
    printf("%d\n", isPower2(5));
    printf("%d\n", isPower2(8));
    printf("Testing float_neg(10.0)\n");
    printf("%f\n", int2Float(float_neg(float2Int(10.0))));
    printf("Testing float_abs(-10.0)\n");
    printf("%f\n", int2Float(float_abs(float2Int(-10.0))));
    printf("DONE.\n");
}
