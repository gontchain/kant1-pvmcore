#ifndef UNAME_H
#define UNAME_H 1

#include <sys/utsname.h>
#ifdef __CYGWIN__
#define __NEW_UTS_LEN 255
typedef struct new_utsname {
          char sysname[__NEW_UTS_LEN + 1];
          char nodename[__NEW_UTS_LEN + 1];
          char release[__NEW_UTS_LEN + 1];
          char version[__NEW_UTS_LEN + 1];
          char machine[__NEW_UTS_LEN + 1];
          char domainname[__NEW_UTS_LEN + 1];
};
#endif

#ifndef __CYGWIN__
#include <linux/utsname.h>
#endif
const char *cpu_to_uname_machine(void *cpu_env);
int sys_uname(struct new_utsname *buf);

#endif /* UNAME _H */
