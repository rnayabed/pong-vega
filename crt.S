.section .text.init

.globl _start

_start:

.option push
.option norelax
  la gp, __global_pointer$
.option pop

/* align and setting up stack - taken from Aries SDK */

la  tp, _end + 63
and tp, tp, -64

#define STKSHIFT 15
sll a2, a0, STKSHIFT
add tp, tp, a2
add sp, a0, 1
sll sp, sp, STKSHIFT
add sp, sp, tp

j main
