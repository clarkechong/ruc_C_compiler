.text
.globl f 
f:
addi    sp,sp,-100
sw      ra,96(sp)
sw      s0,92(sp)
addi    s0,sp,100
sw       a0,-20(s0)
sw       a1,-24(s0)
lw      a5,-20(s0)
add      a4,a5,0
lw      a5,-24(s0)
add     a5,a4,a5
mv      a0,a5
lw      ra,96(sp)
lw      s0,92(sp)
addi    sp,sp,100
jr      ra
