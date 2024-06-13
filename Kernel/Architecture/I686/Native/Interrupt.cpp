#include "Interrupt.hpp"

#include "Debug.hpp"

IDTEntry IEntries[256];
IDTPointer IDTPointer;

__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler0(Frame *frame) {
    RouteInterrupt(0);
}

__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler1(Frame *frame) {
    RouteInterrupt(1);
}

__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler2(Frame *frame) {
    RouteInterrupt(2);
}

__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler3(Frame *frame) {
    RouteInterrupt(3);
}

__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler4(Frame *frame) {
    RouteInterrupt(4);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler5(Frame *frame) {
    RouteInterrupt(5);
}

__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler6(Frame *frame) {
    RouteInterrupt(6);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler7(Frame *frame) {
    RouteInterrupt(7);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler8(Frame *frame) {
    RouteInterrupt(8);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler9(Frame *frame) {
    RouteInterrupt(9);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler10(Frame *frame) {
    RouteInterrupt(10);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler11(Frame *frame) {
    RouteInterrupt(11);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler12(Frame *frame) {
    RouteInterrupt(12);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler13(Frame *frame) {
    RouteInterrupt(13);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler14(Frame *frame) {
    RouteInterrupt(14);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler15(Frame *frame) {
    RouteInterrupt(15);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler16(Frame *frame) {
    RouteInterrupt(16);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler17(Frame *frame) {
    RouteInterrupt(17);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler18(Frame *frame) {
    RouteInterrupt(18);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler19(Frame *frame) {
    RouteInterrupt(19);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler20(Frame *frame) {
    RouteInterrupt(20);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler21(Frame *frame) {
    RouteInterrupt(21);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler22(Frame *frame) {
    RouteInterrupt(22);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler23(Frame *frame) {
    RouteInterrupt(23);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler24(Frame *frame) {
    RouteInterrupt(24);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler25(Frame *frame) {
    RouteInterrupt(25);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler26(Frame *frame) {
    RouteInterrupt(26);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler27(Frame *frame) {
    RouteInterrupt(27);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler28(Frame *frame) {
    RouteInterrupt(28);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler29(Frame *frame) {
    RouteInterrupt(29);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler30(Frame *frame) {
    RouteInterrupt(30);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler31(Frame *frame) {
    RouteInterrupt(31);
}


__attribute__((interrupt,isr, general_regs_only)) void RouterEntryInterrupt(Frame *frame) {
    RouteInterrupt(RouterCall);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler32(Frame *frame) {
    RouteInterrupt(32);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler33(Frame *frame) {
    RouteInterrupt(33);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler34(Frame *frame) {
    RouteInterrupt(34);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler35(Frame *frame) {
    RouteInterrupt(35);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler36(Frame *frame) {
    RouteInterrupt(36);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler37(Frame *frame) {
    RouteInterrupt(37);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler38(Frame *frame) {
    RouteInterrupt(38);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler39(Frame *frame) {
    RouteInterrupt(39);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler40(Frame *frame) {
    RouteInterrupt(40);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler41(Frame *frame) {
    RouteInterrupt(41);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler42(Frame *frame) {
    RouteInterrupt(42);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler43(Frame *frame) {
    RouteInterrupt(43);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler44(Frame *frame) {
    RouteInterrupt(44);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler45(Frame *frame) {
    RouteInterrupt(45);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler46(Frame *frame) {
    RouteInterrupt(46);
}


__attribute__((interrupt,isr, general_regs_only)) void InterruptHandler47(Frame *frame) {
    RouteInterrupt(47);
}


char *Exceptions[] = {
        "Division by zero",
        "Debug",
        "Non-maskable interrupt",
        "Breakpoint",
        "Detected overflow",
        "Out-of-bounds",
        "Invalid opcode",
        "No coprocessor",
        "Double fault",
        "Coprocessor segment overrun",
        "Bad TSS",
        "Segment not present",
        "Stack fault",
        "General protection fault",
        "Page fault",
        "Unknown interrupt",
        "Coprocessor fault",
        "Alignment check",
        "Machine check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
};

void IDTController::Set(u1 Index, u4 Base, u2 Selector, u1 Flags) {
    IEntries[Index].BaseLow = (Base & 0xFFFF);
    IEntries[Index].BaseHigh = (Base >> 16) & 0xFFFF;
    IEntries[Index].Selector = Selector;
    IEntries[Index].Zero = 0;
    IEntries[Index].Flags = Flags | 0x60;
}

void InitializeInterrupts() {
    IDTController::Initialize();
}

void IDTController::Initialize() {
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    IDTPointer.Limit = (sizeof(IDTEntry) * 256) - 1;
    IDTPointer.Base = (uintptr_t) &IEntries;
    memset(reinterpret_cast<char *>(&IEntries), 0, sizeof(IDTEntry) * 256);
    __asm__ __volatile__ ("lidt %0" : : "m"(IDTPointer));
    Install();
}

void IDTController::Install() {
    Set(0, (unsigned) InterruptHandler0, 0x08, 0x8E);
    Set(1, (unsigned) InterruptHandler1, 0x08, 0x8E);
    Set(2, (unsigned) InterruptHandler2, 0x08, 0x8E);
    Set(3, (unsigned) InterruptHandler3, 0x08, 0x8E);
    Set(4, (unsigned) InterruptHandler4, 0x08, 0x8E);
    Set(5, (unsigned) InterruptHandler5, 0x08, 0x8E);
    Set(6, (unsigned) InterruptHandler6, 0x08, 0x8E);
    Set(7, (unsigned) InterruptHandler7, 0x08, 0x8E);
    Set(8, (unsigned) InterruptHandler8, 0x08, 0x8E);
    Set(9, (unsigned) InterruptHandler9, 0x08, 0x8E);
    Set(10, (unsigned) InterruptHandler10, 0x08, 0x8E);
    Set(11, (unsigned) InterruptHandler11, 0x08, 0x8E);
    Set(12, (unsigned) InterruptHandler12, 0x08, 0x8E);
    Set(13, (unsigned) InterruptHandler13, 0x08, 0x8E);
    Set(14, (unsigned) InterruptHandler14, 0x08, 0x8E);
    Set(15, (unsigned) InterruptHandler15, 0x08, 0x8E);
    Set(16, (unsigned) InterruptHandler16, 0x08, 0x8E);
    Set(17, (unsigned) InterruptHandler17, 0x08, 0x8E);
    Set(18, (unsigned) InterruptHandler18, 0x08, 0x8E);
    Set(19, (unsigned) InterruptHandler19, 0x08, 0x8E);
    Set(20, (unsigned) InterruptHandler20, 0x08, 0x8E);
    Set(21, (unsigned) InterruptHandler21, 0x08, 0x8E);
    Set(22, (unsigned) InterruptHandler22, 0x08, 0x8E);
    Set(23, (unsigned) InterruptHandler23, 0x08, 0x8E);
    Set(24, (unsigned) InterruptHandler24, 0x08, 0x8E);
    Set(25, (unsigned) InterruptHandler25, 0x08, 0x8E);
    Set(26, (unsigned) InterruptHandler26, 0x08, 0x8E);
    Set(27, (unsigned) InterruptHandler27, 0x08, 0x8E);
    Set(28, (unsigned) InterruptHandler28, 0x08, 0x8E);
    Set(29, (unsigned) InterruptHandler29, 0x08, 0x8E);
    Set(30, (unsigned) InterruptHandler30, 0x08, 0x8E);
    Set(31, (unsigned) InterruptHandler31, 0x08, 0x8E);
    Set(32, (unsigned) InterruptHandler32, 0x08, 0x8E);
    Set(33, (unsigned) InterruptHandler33, 0x08, 0x8E);
    Set(34, (unsigned) InterruptHandler34, 0x08, 0x8E);
    Set(35, (unsigned) InterruptHandler35, 0x08, 0x8E);
    Set(36, (unsigned) InterruptHandler36, 0x08, 0x8E);
    Set(37, (unsigned) InterruptHandler37, 0x08, 0x8E);
    Set(38, (unsigned) InterruptHandler38, 0x08, 0x8E);
    Set(39, (unsigned) InterruptHandler39, 0x08, 0x8E);
    Set(40, (unsigned) InterruptHandler40, 0x08, 0x8E);
    Set(41, (unsigned) InterruptHandler41, 0x08, 0x8E);
    Set(42, (unsigned) InterruptHandler42, 0x08, 0x8E);
    Set(43, (unsigned) InterruptHandler43, 0x08, 0x8E);
    Set(44, (unsigned) InterruptHandler44, 0x08, 0x8E);
    Set(45, (unsigned) InterruptHandler45, 0x08, 0x8E);
    Set(46, (unsigned) InterruptHandler46, 0x08, 0x8E);
    Set(47, (unsigned) InterruptHandler47, 0x08, 0x8E);
    Set(RouterCall, (unsigned) RouterEntryInterrupt, 0x08, 0x8E);
}
