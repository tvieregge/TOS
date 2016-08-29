.text
.globl   default_wrapper
.align   4
 
isr_wrapper:
    pushal
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call default_handler
    popal
    iret
