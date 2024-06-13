.global start
.extern Start

.set noreorder

.set STACKSIZE, 0x1000

.section .text

start:
   la $sp, stack
   addiu $sp, STACKSIZE - 32
   jal Start
   nop
   b .
   nop

.section .bss
stack:
   .space STACKSIZE