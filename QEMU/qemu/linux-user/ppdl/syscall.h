// [TODO] should be reworked
#ifndef __CYGWIN__
struct target_pt_regs {
    union {
        struct {
            /* Named registers */
            uint32_t sr;       /* Stored in place of r0 */
            target_ulong sp;   /* r1 */
        };
    };
    target_ulong pc;
    uint32_t syscallno;        /* Syscall number (used by strace) */
};
#endif
#define UNAME_MACHINE "ppdl"
#define UNAME_MINIMUM_RELEASE "2.6.32"
