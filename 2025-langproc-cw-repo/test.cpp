f:
        addi    sp,sp,-32
        sw      s0,28(sp)
        addi    s0,sp,32
        li      a5,5
        sw      a5,-20(s0)
        lw      a4,-20(s0)
        li      a5,10
        bne     a4,a5,.L2
        li      a5,20
        sw      a5,-20(s0)
        j       .L3
.L2:
        li      a5,15
        sw      a5,-20(s0)
.L3:
        lw      a5,-20(s0)
        mv      a0,a5
        lw      s0,28(sp)
        addi    sp,sp,32
        jr      ra
