#ifndef TARGET_CPU_H
#define TARGET_CPU_H

static inline void cpu_clone_regs(CPUPPDLState *env, target_ulong newsp)
{
    // [TODO] remove old (another) cpu_clone_regs
    if (newsp) {
        env->gr[1] = newsp;
    }
    //env->gr[7] = 0;
}

static inline void cpu_set_tls(CPUPPDLState *env, target_ulong newtls)
{
    /* Linux kernel 3.10 does not pay any attention to CLONE_SETTLS
     * in copy_thread(), so QEMU need not do so either.
     */
}

#endif
