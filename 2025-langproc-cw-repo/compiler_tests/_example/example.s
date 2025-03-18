   .text
.globl f 
f:
addi    sp,sp,-100
sw      ra,96(sp)
sw      s0,92(sp)
addi    s0,sp,100
li      a5, 1
mv       a0,a5 
li      a5, 2
mv       a1,a5 
li      a5, 3
mv       a2,a5 
li      a5, 4
mv       a3,a5 
li      a5, 5
mv       a4,a5 
call    g
mv      a5,a0
mv      a0,a5
lw      ra,96(sp)
lw      s0,92(sp)
addi    sp,sp,100
jr      ra
