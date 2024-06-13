.global start
.extern Start

.set noreorder

.section .text

start:
   ehb
   la $sp, stack
   add $sp, 2048576
   jal Start
   nop
   b .
   nop

.section .bss
stack:
   .space 2048576