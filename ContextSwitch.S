.globl ContextSwitch    // make the Symbol ContextSwitch available in link time
ContextSwitch:

        // According to x86_64 calling convention
        // first argument to ContextSwitch is stored in %rdi
        // second argument to ContextSwitch is stored in %rsi

        // Therefore %rdi -> addrss of Main Conext struct
        // Use Offset addressing to store each registers to Main Context
        movq     %rsp, 0x00(%rdi)
        movq     %r15, 0x08(%rdi)
        movq     %r14, 0x10(%rdi)
        movq     %r13, 0x18(%rdi)
        movq     %r12, 0x20(%rdi)
        movq     %rbp, 0x28(%rdi)
        movq     %rbx, 0x30(%rdi)

        // Therefore %rsi -> addrss of Child Conext struct
        // Use Offset addressing to load each registers from Child Context
        movq     0x00(%rsi), %rsp
        movq     0x08(%rsi), %r15
        movq     0x10(%rsi), %r14
        movq     0x18(%rsi), %r13
        movq     0x20(%rsi), %r12
        movq     0x28(%rsi), %rbp
        movq     0x30(%rsi), %rbx

        ret      // rip is loaded with [rsp,rsp + 8]
