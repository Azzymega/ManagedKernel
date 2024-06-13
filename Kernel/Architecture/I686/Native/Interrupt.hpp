#pragma once

#include "Kernel/Ke/HAL.hpp"

#define RouterCall 80

void InitializeInterrupts();

//
//  Hal
//

void InitializeInterrupts();

struct IDTController {
    static void Initialize();
    static void Set(u1 Index, u4 Base, u2 Selector, u1 Flags);
    static void Install();
};

struct Frame {
    u2 IP;
    u2 CS;
    u2 Flags;
    u2 SP;
    u2 SS;
} __attribute__((packed));

struct IDTEntry {
    u2 BaseLow;
    u2 Selector;
    u1 Zero;
    u1 Flags;
    u2 BaseHigh;
} __attribute__((packed));

struct IDTPointer {
    u2 Limit;
    u4 Base;
} __attribute__((packed));

typedef void (*InterruptCall)(Frame * );

//
// Exceptions
//

__attribute__((isr, general_regs_only)) void InterruptHandler0(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler1(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler2(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler3(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler4(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler5(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler6(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler7(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler8(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler9(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler10(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler11(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler12(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler13(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler14(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler15(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler16(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler17(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler18(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler19(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler20(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler21(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler22(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler23(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler24(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler25(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler26(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler27(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler28(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler29(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler30(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler31(Frame *frame);

//
//  IRQ
//

__attribute__((isr, general_regs_only)) void InterruptHandler32(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler33(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler34(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler35(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler36(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler37(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler38(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler39(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler40(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler41(Frame *frame);

__attribute__((isr, general_regs_only)) void InterruptHandler42(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler43(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler44(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler45(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler46(Frame *frame);
__attribute__((isr, general_regs_only)) void InterruptHandler47(Frame *frame);

__attribute__((isr, general_regs_only)) void RouterEntryInterrupt(Frame *frame);
