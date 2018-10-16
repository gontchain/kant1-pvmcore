/*
 *  mmap support for qemu
 *
 *  Copyright (c) 2003 Fabrice Bellard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#ifndef __CYGWIN__
#include <linux/mman.h>
#include <linux/unistd.h>
/*from unistd values*/
#define __NR_ni_syscall			1024
#define __NR_exit			1025
#define __NR_read			1026
#define __NR_write			1027
#define __NR_open			1028
#define __NR_close			1029
#define __NR_creat			1030
#define __NR_link			1031
#define __NR_unlink			1032
#define __NR_execve			1033
#define __NR_chdir			1034
#define __NR_fchdir			1035
#define __NR_utimes			1036
#define __NR_mknod			1037
#define __NR_chmod			1038
#define __NR_chown			1039
#define __NR_lseek			1040
#define __NR_getpid			1041
#define __NR_getppid			1042
#define __NR_mount			1043
#define __NR_umount			1044
#define __NR_setuid			1045
#define __NR_getuid			1046
#define __NR_geteuid			1047
#define __NR_ptrace			1048
#define __NR_access			1049
#define __NR_sync			1050
#define __NR_fsync			1051
#define __NR_fdatasync			1052
#define __NR_kill			1053
#define __NR_rename			1054
#define __NR_mkdir			1055
#define __NR_rmdir			1056
#define __NR_dup			1057
#define __NR_pipe			1058
#define __NR_times			1059
#define __NR_brk			1060
#define __NR_setgid			1061
#define __NR_getgid			1062
#define __NR_getegid			1063
#define __NR_acct			1064
#define __NR_ioctl			1065
#define __NR_fcntl			1066
#define __NR_umask			1067
#define __NR_chroot			1068
#define __NR_ustat			1069
#define __NR_dup2			1070
#define __NR_setreuid			1071
#define __NR_setregid			1072
#define __NR_getresuid			1073
#define __NR_setresuid			1074
#define __NR_getresgid			1075
#define __NR_setresgid			1076
#define __NR_getgroups			1077
#define __NR_setgroups			1078
#define __NR_getpgid			1079
#define __NR_setpgid			1080
#define __NR_setsid			1081
#define __NR_getsid			1082
#define __NR_sethostname		1083
#define __NR_setrlimit			1084
#define __NR_getrlimit			1085
#define __NR_getrusage			1086
#define __NR_gettimeofday		1087
#define __NR_settimeofday		1088
#define __NR_select			1089
#define __NR_poll			1090
#define __NR_symlink			1091
#define __NR_readlink			1092
#define __NR_uselib			1093
#define __NR_swapon			1094
#define __NR_swapoff			1095
#define __NR_reboot			1096
#define __NR_truncate			1097
#define __NR_ftruncate			1098
#define __NR_fchmod			1099
#define __NR_fchown			1100
#define __NR_getpriority		1101
#define __NR_setpriority		1102
#define __NR_statfs			1103
#define __NR_fstatfs			1104
#define __NR_gettid			1105
#define __NR_semget			1106
#define __NR_semop			1107
#define __NR_semctl			1108
#define __NR_msgget			1109
#define __NR_msgsnd			1110
#define __NR_msgrcv			1111
#define __NR_msgctl			1112
#define __NR_shmget			1113
#define __NR_shmat			1114
#define __NR_shmdt			1115
#define __NR_shmctl			1116
/* also known as klogctl() in GNU libc: */
#define __NR_syslog			1117
#define __NR_setitimer			1118
#define __NR_getitimer			1119
/* 1120 was __NR_old_stat */
/* 1121 was __NR_old_lstat */
/* 1122 was __NR_old_fstat */
#define __NR_vhangup			1123
#define __NR_lchown			1124
#define __NR_remap_file_pages		1125
#define __NR_wait4			1126
#define __NR_sysinfo			1127
#define __NR_clone			1128
#define __NR_setdomainname		1129
#define __NR_uname			1130
#define __NR_adjtimex			1131
#define __NR_create_module		1132
#define __NR_init_module		1133
#define __NR_delete_module		1134
#define __NR_get_kernel_syms		1135
#define __NR_query_module		1136
#define __NR_quotactl			1137
#define __NR_bdflush			1138
#define __NR_sysfs			1139
#define __NR_personality		1140
#define __NR_afs_syscall		1141
#define __NR_setfsuid			1142
#define __NR_setfsgid			1143
#define __NR_getdents			1144
#define __NR_flock			1145
#define __NR_readv			1146
#define __NR_writev			1147
#define __NR_pread64			1148
#define __NR_pwrite64			1149
#define __NR__sysctl			1150
#define __NR_mmap			1151
#define __NR_munmap			1152
#define __NR_mlock			1153
#define __NR_mlockall			1154
#define __NR_mprotect			1155
#define __NR_mremap			1156
#define __NR_msync			1157
#define __NR_munlock			1158
#define __NR_munlockall			1159
#define __NR_sched_getparam		1160
#define __NR_sched_setparam		1161
#define __NR_sched_getscheduler		1162
#define __NR_sched_setscheduler		1163
#define __NR_sched_yield		1164
#define __NR_sched_get_priority_max	1165
#define __NR_sched_get_priority_min	1166
#define __NR_sched_rr_get_interval	1167
#define __NR_nanosleep			1168
#define __NR_nfsservctl			1169
#define __NR_prctl			1170
/* 1171 is reserved for backwards compatibility with old __NR_getpagesize */
#define __NR_mmap2			1172
#define __NR_pciconfig_read		1173
#define __NR_pciconfig_write		1174
#define __NR_perfmonctl			1175
#define __NR_sigaltstack		1176
#define __NR_rt_sigaction		1177
#define __NR_rt_sigpending		1178
#define __NR_rt_sigprocmask		1179
#define __NR_rt_sigqueueinfo		1180
#define __NR_rt_sigreturn		1181
#define __NR_rt_sigsuspend		1182
#define __NR_rt_sigtimedwait		1183
#define __NR_getcwd			1184
#define __NR_capget			1185
#define __NR_capset			1186
#define __NR_sendfile			1187
#define __NR_getpmsg			1188
#define __NR_putpmsg			1189
#define __NR_socket			1190
#define __NR_bind			1191
#define __NR_connect			1192
#define __NR_listen			1193
#define __NR_accept			1194
#define __NR_getsockname		1195
#define __NR_getpeername		1196
#define __NR_socketpair			1197
#define __NR_send			1198
#define __NR_sendto			1199
#define __NR_recv			1200
#define __NR_recvfrom			1201
#define __NR_shutdown			1202
#define __NR_setsockopt			1203
#define __NR_getsockopt			1204
#define __NR_sendmsg			1205
#define __NR_recvmsg			1206
#define __NR_pivot_root			1207
#define __NR_mincore			1208
#define __NR_madvise			1209
#define __NR_stat			1210
#define __NR_lstat			1211
#define __NR_fstat			1212
#define __NR_clone2			1213
#define __NR_getdents64			1214
#define __NR_getunwind			1215
#define __NR_readahead			1216
#define __NR_setxattr			1217
#define __NR_lsetxattr			1218
#define __NR_fsetxattr			1219
#define __NR_getxattr			1220
#define __NR_lgetxattr			1221
#define __NR_fgetxattr			1222
#define __NR_listxattr			1223
#define __NR_llistxattr			1224
#define __NR_flistxattr			1225
#define __NR_removexattr		1226
#define __NR_lremovexattr		1227
#define __NR_fremovexattr		1228
#define __NR_tkill			1229
#define __NR_futex			1230
#define __NR_sched_setaffinity		1231
#define __NR_sched_getaffinity		1232
#define __NR_set_tid_address		1233
#define __NR_fadvise64			1234
#define __NR_tgkill			1235
#define __NR_exit_group			1236
#define __NR_lookup_dcookie		1237
#define __NR_io_setup			1238
#define __NR_io_destroy			1239
#define __NR_io_getevents		1240
#define __NR_io_submit			1241
#define __NR_io_cancel			1242
#define __NR_epoll_create		1243
#define __NR_epoll_ctl			1244
#define __NR_epoll_wait			1245
#define __NR_restart_syscall		1246
#define __NR_semtimedop			1247
#define __NR_timer_create		1248
#define __NR_timer_settime		1249
#define __NR_timer_gettime		1250
#define __NR_timer_getoverrun		1251
#define __NR_timer_delete		1252
#define __NR_clock_settime		1253
#define __NR_clock_gettime		1254
#define __NR_clock_getres		1255
#define __NR_clock_nanosleep		1256
#define __NR_fstatfs64			1257
#define __NR_statfs64			1258

#endif

#include "qemu.h"
#include "qemu-common.h"

#ifdef __CYGWIN__
#define MREMAP_MAYMOVE 1
#define MREMAP_FIXED 2
#endif
//#define DEBUG_MMAP

static pthread_mutex_t mmap_mutex = PTHREAD_MUTEX_INITIALIZER;
static __thread int mmap_lock_count;

void mmap_lock(void)
{
    if (mmap_lock_count++ == 0) {
        pthread_mutex_lock(&mmap_mutex);
    }
}

void mmap_unlock(void)
{
    if (--mmap_lock_count == 0) {
        pthread_mutex_unlock(&mmap_mutex);
    }
}

/* Grab lock to make sure things are in a consistent state after fork().  */
void mmap_fork_start(void)
{
    if (mmap_lock_count)
        abort();
    pthread_mutex_lock(&mmap_mutex);
}

void mmap_fork_end(int child)
{
    if (child)
        pthread_mutex_init(&mmap_mutex, NULL);
    else
        pthread_mutex_unlock(&mmap_mutex);
}

/* NOTE: all the constants are the HOST ones, but addresses are target. */
int target_mprotect(abi_ulong start, abi_ulong len, int prot)
{
    abi_ulong end, host_start, host_end, addr;
    int prot1, ret;

#ifdef DEBUG_MMAP
    printf("mprotect: start=0x" TARGET_ABI_FMT_lx
           "len=0x" TARGET_ABI_FMT_lx " prot=%c%c%c\n", start, len,
           prot & PROT_READ ? 'r' : '-',
           prot & PROT_WRITE ? 'w' : '-',
           prot & PROT_EXEC ? 'x' : '-');
#endif

    if ((start & ~TARGET_PAGE_MASK) != 0)
        return -EINVAL;
    len = TARGET_PAGE_ALIGN(len);
    end = start + len;
    if (end < start)
        return -EINVAL;
    prot &= PROT_READ | PROT_WRITE | PROT_EXEC;
    if (len == 0)
        return 0;

    mmap_lock();
    host_start = start & qemu_host_page_mask;
    host_end = HOST_PAGE_ALIGN(end);
    if (start > host_start) {
        /* handle host page containing start */
        prot1 = prot;
        for(addr = host_start; addr < start; addr += TARGET_PAGE_SIZE) {
            prot1 |= page_get_flags(addr);
        }
        if (host_end == host_start + qemu_host_page_size) {
            for(addr = end; addr < host_end; addr += TARGET_PAGE_SIZE) {
                prot1 |= page_get_flags(addr);
            }
            end = host_end;
        }
        ret = mprotect(g2h(host_start), qemu_host_page_size, prot1 & PAGE_BITS);
        if (ret != 0)
            goto error;
        host_start += qemu_host_page_size;
    }
    if (end < host_end) {
        prot1 = prot;
        for(addr = end; addr < host_end; addr += TARGET_PAGE_SIZE) {
            prot1 |= page_get_flags(addr);
        }
        ret = mprotect(g2h(host_end - qemu_host_page_size), qemu_host_page_size,
                       prot1 & PAGE_BITS);
        if (ret != 0)
            goto error;
        host_end -= qemu_host_page_size;
    }

    /* handle the pages in the middle */
    if (host_start < host_end) {
        ret = mprotect(g2h(host_start), host_end - host_start, prot);
        if (ret != 0)
            goto error;
    }
    page_set_flags(start, start + len, prot | PAGE_VALID);
    mmap_unlock();
    return 0;
error:
    mmap_unlock();
    return ret;
}

/* map an incomplete host page */
static int mmap_frag(abi_ulong real_start,
                     abi_ulong start, abi_ulong end,
                     int prot, int flags, int fd, abi_ulong offset)
{
    abi_ulong real_end, addr;
    void *host_start;
    int prot1, prot_new;

	#if 0
    {
        printf("mmap frag: rstart=0x" TARGET_ABI_FMT_lx
               " start=0x" TARGET_ABI_FMT_lx " end=0x" TARGET_ABI_FMT_lx "  prot=%c%c%c flags=",
               real_start,start,end,
               prot & PROT_READ ? 'r' : '-',
               prot & PROT_WRITE ? 'w' : '-',
               prot & PROT_EXEC ? 'x' : '-');
        if (flags & MAP_FIXED)
            printf("MAP_FIXED ");
        if (flags & MAP_ANONYMOUS)
            printf("MAP_ANON ");
        switch(flags & MAP_TYPE) {
        case MAP_PRIVATE:
            printf("MAP_PRIVATE ");
            break;
        case MAP_SHARED:
            printf("MAP_SHARED ");
            break;
        default:
            printf("[MAP_TYPE=0x%x] ", flags & MAP_TYPE);
            break;
        }
        printf("fd=%d offset=" TARGET_ABI_FMT_lx "\n", fd, offset);
    }
#endif
	
    real_end = real_start + qemu_host_page_size;
    host_start = g2h(real_start);
	//host_start = real_start;
	/* get the protection of the target pages outside the mapping */
    prot1 = 0;
    for(addr = real_start; addr < real_end; addr++) {
        if (addr < start || addr >= end)
            prot1 |= page_get_flags(addr);
    }

    if (prot1 == 0) {
        /* no page was there, so we allocate one */
	    void *p = mmap(host_start, qemu_host_page_size, prot,
                       flags | MAP_ANONYMOUS , -1, 0);
        if (p == MAP_FAILED) {
            return -1;
		}
        prot1 = prot;
    }
    prot1 &= PAGE_BITS;

    prot_new = prot | prot1;
    if (!(flags & MAP_ANONYMOUS)) {
        /* msync() won't work here, so we return an error if write is
           possible while it is a shared mapping */
        if ((flags & MAP_TYPE) == MAP_SHARED &&
            (prot & PROT_WRITE))
            {
            return -1;
			
        }

        /* adjust protection to be able to read */
        if (!(prot1 & PROT_WRITE))
            mprotect(host_start, qemu_host_page_size, prot1 | PROT_WRITE);

        /* read the corresponding file data */
        if (pread(fd, g2h(start), end - start, offset) == -1)
		{
            return -1;
		}

        /* put final protection */
        if (prot_new != (prot1 | PROT_WRITE))
            mprotect(host_start, qemu_host_page_size, prot_new);
    } else {
        /* just update the protection */
        if (prot_new != prot1) {
            mprotect(host_start, qemu_host_page_size, prot_new);
        }
    }
    return 0;
}

#if HOST_LONG_BITS == 64 && TARGET_ABI_BITS == 64
# define TASK_UNMAPPED_BASE  (1ul << 38)
#elif defined(__CYGWIN__)
/* Cygwin doesn't have a whole lot of address space.  */
# define TASK_UNMAPPED_BASE  0x18000000
#else
# define TASK_UNMAPPED_BASE  0x40000000
#endif
abi_ulong mmap_next_start = TASK_UNMAPPED_BASE;

unsigned long last_brk;

#ifdef CONFIG_USE_GUEST_BASE
/* Subroutine of mmap_find_vma, used when we have pre-allocated a chunk
   of guest address space.  */
static abi_ulong mmap_find_vma_reserved(abi_ulong start, abi_ulong size)
{
    abi_ulong addr;
    abi_ulong end_addr;
    int prot;
    int looped = 0;

    if (size > RESERVED_VA) {
        return (abi_ulong)-1;
    }

    size = HOST_PAGE_ALIGN(size);
    end_addr = start + size;
    if (end_addr > RESERVED_VA) {
        end_addr = RESERVED_VA;
    }
    addr = end_addr - qemu_host_page_size;

    while (1) {
        if (addr > end_addr) {
            if (looped) {
                return (abi_ulong)-1;
            }
            end_addr = RESERVED_VA;
            addr = end_addr - qemu_host_page_size;
            looped = 1;
            continue;
        }
        prot = page_get_flags(addr);
        if (prot) {
            end_addr = addr;
        }
        if (addr + size == end_addr) {
            break;
        }
        addr -= qemu_host_page_size;
    }

    if (start == mmap_next_start) {
        mmap_next_start = addr;
    }

    return addr;
}
#endif

/*
 * Find and reserve a free memory area of size 'size'. The search
 * starts at 'start'.
 * It must be called with mmap_lock() held.
 * Return -1 if error.
 */
abi_ulong mmap_find_vma(abi_ulong start, abi_ulong size)
{
    void *ptr, *prev;
    abi_ulong addr;
    int wrapped, repeat;

    /* If 'start' == 0, then a default start address is used. */
    if (start == 0) {
        start = mmap_next_start;
    } else {
        start &= qemu_host_page_mask;
    }

    size = HOST_PAGE_ALIGN(size);

#ifdef CONFIG_USE_GUEST_BASE
    if (RESERVED_VA) {
        return mmap_find_vma_reserved(start, size);
    }
#endif

    addr = start;
    wrapped = repeat = 0;
    prev = 0;

    for (;; prev = ptr) {
        /*
         * Reserve needed memory area to avoid a race.
         * It should be discarded using:
         *  - mmap() with MAP_FIXED flag
         *  - mremap() with MREMAP_FIXED flag
         *  - shmat() with SHM_REMAP flag
         */
        ptr = mmap(g2h(addr), size, PROT_NONE,
                   MAP_ANONYMOUS|MAP_PRIVATE|MAP_NORESERVE, -1, 0);

        /* ENOMEM, if host address space has no memory */
        if (ptr == MAP_FAILED) {
            return (abi_ulong)-1;
        }

        /* Count the number of sequential returns of the same address.
           This is used to modify the search algorithm below.  */
        repeat = (ptr == prev ? repeat + 1 : 0);

        if (h2g_valid(ptr + size - 1)) {
            addr = h2g(ptr);

            if ((addr & ~TARGET_PAGE_MASK) == 0) {
                /* Success.  */
                if (start == mmap_next_start && addr >= TASK_UNMAPPED_BASE) {
                    mmap_next_start = addr + size;
                }
                return addr;
            }

            /* The address is not properly aligned for the target.  */
            switch (repeat) {
            case 0:
                /* Assume the result that the kernel gave us is the
                   first with enough free space, so start again at the
                   next higher target page.  */
                addr = TARGET_PAGE_ALIGN(addr);
                break;
            case 1:
                /* Sometimes the kernel decides to perform the allocation
                   at the top end of memory instead.  */
                addr &= TARGET_PAGE_MASK;
                break;
            case 2:
                /* Start over at low memory.  */
                addr = 0;
                break;
            default:
                /* Fail.  This unaligned block must the last.  */
                addr = -1;
                break;
            }
        } else {
            /* Since the result the kernel gave didn't fit, start
               again at low memory.  If any repetition, fail.  */
            addr = (repeat ? -1 : 0);
        }

        /* Unmap and try again.  */
        munmap(ptr, size);

        /* ENOMEM if we checked the whole of the target address space.  */
        if (addr == (abi_ulong)-1) {
            return (abi_ulong)-1;
        } else if (addr == 0) {
            if (wrapped) {
                return (abi_ulong)-1;
            }
            wrapped = 1;
            /* Don't actually use 0 when wrapping, instead indicate
               that we'd truly like an allocation in low memory.  */
            addr = (mmap_min_addr > TARGET_PAGE_SIZE
                     ? TARGET_PAGE_ALIGN(mmap_min_addr)
                     : TARGET_PAGE_SIZE);
        } else if (wrapped && addr >= start) {
            return (abi_ulong)-1;
        }
    }
}

/* NOTE: all the constants are the HOST ones */
abi_long target_mmap(abi_ulong start, abi_ulong len, int prot,
                     int flags, int fd, abi_ulong offset)
{
    abi_ulong ret, end, real_start, real_end, retaddr, host_offset, host_len;
	
    // [FIXME] Why do READ and WRITE flags not set?
    prot |= PROT_READ;
    prot |= PROT_WRITE;

    mmap_lock();
#ifdef DEBUG_MMAP
    {
        printf("mmap: start=0x" TARGET_ABI_FMT_lx
               " len=0x" TARGET_ABI_FMT_lx " prot=%c%c%c flags=",
               start, len,
               prot & PROT_READ ? 'r' : '-',
               prot & PROT_WRITE ? 'w' : '-',
               prot & PROT_EXEC ? 'x' : '-');
        if (flags & MAP_FIXED)
            printf("MAP_FIXED ");
        if (flags & MAP_ANONYMOUS)
            printf("MAP_ANON ");
        switch(flags & MAP_TYPE) {
        case MAP_PRIVATE:
            printf("MAP_PRIVATE ");
            break;
        case MAP_SHARED:
            printf("MAP_SHARED ");
            break;
        default:
            printf("[MAP_TYPE=0x%x] ", flags & MAP_TYPE);
            break;
        }
        printf("fd=%d offset=" TARGET_ABI_FMT_lx "\n", fd, offset);
    }
#endif

    // [FIXME] Why do we need this check?
    /*
    if (offset & ~TARGET_PAGE_MASK) {
        errno = EINVAL;
        goto fail;
    }
    */

    len = TARGET_PAGE_ALIGN(len);
    if (len == 0)
        goto the_end;
    real_start = start & qemu_host_page_mask;
    host_offset = offset & qemu_host_page_mask;

    /* If the user is asking for the kernel to find a location, do that
       before we truncate the length for mapping files below.  */
    if (!(flags & MAP_FIXED)) {
        host_len = len + offset - host_offset;
        host_len = HOST_PAGE_ALIGN(host_len);
        start = mmap_find_vma(real_start, host_len);
        if (start == (abi_ulong)-1) {
            errno = ENOMEM;
            goto fail;
        }
    }

    /* When mapping files into a memory area larger than the file, accesses
       to pages beyond the file size will cause a SIGBUS. 

       For example, if mmaping a file of 100 bytes on a host with 4K pages
       emulating a target with 8K pages, the target expects to be able to
       access the first 8K. But the host will trap us on any access beyond
       4K.  

       When emulating a target with a larger page-size than the hosts, we
       may need to truncate file maps at EOF and add extra anonymous pages
       up to the targets page boundary.  */

    if ((qemu_real_host_page_size < TARGET_PAGE_SIZE)
        && !(flags & MAP_ANONYMOUS)) {
       struct stat sb;

       if (fstat (fd, &sb) == -1)
           goto fail;

       /* Are we trying to create a map beyond EOF?.  */
       if (offset + len > sb.st_size) {
           /* If so, truncate the file map at eof aligned with 
              the hosts real pagesize. Additional anonymous maps
              will be created beyond EOF.  */
           len = (sb.st_size - offset);
           len += qemu_real_host_page_size - 1;
           len &= ~(qemu_real_host_page_size - 1);
       }
    }

    if (!(flags & MAP_FIXED)) {
        unsigned long host_start;
        void *p;

        host_len = len + offset - host_offset;
        host_len = HOST_PAGE_ALIGN(host_len);

        /* Note: we prefer to control the mapping address. It is
           especially important if qemu_host_page_size >
           qemu_real_host_page_size */
        p = mmap(g2h(start), host_len, prot,
                 flags | MAP_FIXED | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED)
            goto fail;
        /* update start so that it points to the file position at 'offset' */
        host_start = (unsigned long)p;
        if (!(flags & MAP_ANONYMOUS)) {
            p = mmap(g2h(start), len, prot,
                     flags | MAP_FIXED, fd, host_offset);
            if (p == MAP_FAILED) {
                munmap(g2h(start), host_len);
                goto fail;
            }
            host_start += offset - host_offset;
        }
        start = h2g(host_start);
    } else {
        if (start & ~TARGET_PAGE_MASK) {
            errno = EINVAL;
            goto fail;
        }
        end = start + len;
        real_end = HOST_PAGE_ALIGN(end);

	/*
	 * Test if requested memory area fits target address space
	 * It can fail only on 64-bit host with 32-bit target.
	 * On any other target/host host mmap() handles this error correctly.
	 */
        if ((unsigned long)start + len - 1 > (abi_ulong) -1) {
            errno = EINVAL;
            goto fail;
        }

        /* worst case: we cannot map the file because the offset is not
           aligned, so we read it */
        if (!(flags & MAP_ANONYMOUS) &&
            (offset & ~qemu_host_page_mask) != (start & ~qemu_host_page_mask)) {
            /* msync() won't work here, so we return an error if write is
               possible while it is a shared mapping */
            if ((flags & MAP_TYPE) == MAP_SHARED &&
                (prot & PROT_WRITE)) {
		        errno = EINVAL;
                goto fail;
            }
            retaddr = target_mmap(start, len, prot | PROT_WRITE,
                                  MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS,
                                  -1, 0);
            if (retaddr == -1)
                goto fail;
            if (pread(fd, g2h(start), len, offset) == -1)
                goto fail;
            if (!(prot & PROT_WRITE)) {
                ret = target_mprotect(start, len, prot);
                if (ret != 0) {
                    start = ret;
                    goto the_end;
                }
            }
            goto the_end;
        }
        
        /* handle the start of the mapping */
        if (start > real_start) {
            if (real_end == real_start + qemu_host_page_size) {
                /* one single host page */
                ret = mmap_frag(real_start, start, end,
                                prot, flags, fd, offset);
                if (ret == -1)
                    goto fail;
                goto the_end1;
            }
            ret = mmap_frag(real_start, start, real_start + qemu_host_page_size,
                            prot, flags, fd, offset);
			if (ret == -1)
                goto fail;
            real_start += qemu_host_page_size;
        }
        /* handle the end of the mapping */
        if (end < real_end) {
            ret = mmap_frag(real_end - qemu_host_page_size,
                            real_end - qemu_host_page_size, real_end,
                            prot, flags, fd,
                            offset + real_end - qemu_host_page_size - start);
			if (ret == -1)
			{
                goto fail;
            }
			real_end -= qemu_host_page_size;
        }

        /* map the middle (easier) */
        if (real_start < real_end) {
            void *p;
            unsigned long offset1;
            if (flags & MAP_ANONYMOUS)
                offset1 = 0;
            else
                offset1 = offset + real_start - start;
			p = mmap(g2h(real_start), real_end - real_start,
                     prot, flags, fd, offset1);
            if (p == MAP_FAILED)
                goto fail;
        }
    }
 the_end1:
    page_set_flags(start, start + len, prot | PAGE_VALID);
 the_end:
#ifdef DEBUG_MMAP
    printf("ret=0x" TARGET_ABI_FMT_lx "\n", start);
    page_dump(stdout);
    printf("\n");
#endif
    tb_invalidate_phys_range(start, start + len, 0);
    mmap_unlock();
    return start;
fail:
    mmap_unlock();
    return -1;
}

static void mmap_reserve(abi_ulong start, abi_ulong size)
{
    abi_ulong real_start;
    abi_ulong real_end;
    abi_ulong addr;
    abi_ulong end;
    int prot;

    real_start = start & qemu_host_page_mask;
    real_end = HOST_PAGE_ALIGN(start + size);
    end = start + size;
    if (start > real_start) {
        /* handle host page containing start */
        prot = 0;
        for (addr = real_start; addr < start; addr += TARGET_PAGE_SIZE) {
            prot |= page_get_flags(addr);
        }
        if (real_end == real_start + qemu_host_page_size) {
            for (addr = end; addr < real_end; addr += TARGET_PAGE_SIZE) {
                prot |= page_get_flags(addr);
            }
            end = real_end;
        }
        if (prot != 0)
            real_start += qemu_host_page_size;
    }
    if (end < real_end) {
        prot = 0;
        for (addr = end; addr < real_end; addr += TARGET_PAGE_SIZE) {
            prot |= page_get_flags(addr);
        }
        if (prot != 0)
            real_end -= qemu_host_page_size;
    }
    if (real_start != real_end) {
        mmap(g2h(real_start), real_end - real_start, PROT_NONE,
                 MAP_FIXED | MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE,
                 -1, 0);
    }
}

int target_munmap(abi_ulong start, abi_ulong len)
{
    abi_ulong end, real_start, real_end, addr;
    int prot, ret;

#ifdef DEBUG_MMAP
    printf("munmap: start=0x" TARGET_ABI_FMT_lx " len=0x"
           TARGET_ABI_FMT_lx "\n",
           start, len);
#endif
    if (start & ~TARGET_PAGE_MASK)
        return -EINVAL;
    len = TARGET_PAGE_ALIGN(len);
    if (len == 0)
        return -EINVAL;
    mmap_lock();
    end = start + len;
    real_start = start & qemu_host_page_mask;
    real_end = HOST_PAGE_ALIGN(end);

    if (start > real_start) {
        /* handle host page containing start */
        prot = 0;
        for(addr = real_start; addr < start; addr += TARGET_PAGE_SIZE) {
            prot |= page_get_flags(addr);
        }
        if (real_end == real_start + qemu_host_page_size) {
            for(addr = end; addr < real_end; addr += TARGET_PAGE_SIZE) {
                prot |= page_get_flags(addr);
            }
            end = real_end;
        }
        if (prot != 0)
            real_start += qemu_host_page_size;
    }
    if (end < real_end) {
        prot = 0;
        for(addr = end; addr < real_end; addr += TARGET_PAGE_SIZE) {
            prot |= page_get_flags(addr);
        }
        if (prot != 0)
            real_end -= qemu_host_page_size;
    }

    ret = 0;
    /* unmap what we can */
    if (real_start < real_end) {
        if (RESERVED_VA) {
            mmap_reserve(real_start, real_end - real_start);
        } else {
            ret = munmap(g2h(real_start), real_end - real_start);
        }
    }

    if (ret == 0) {
        page_set_flags(start, start + len, 0);
        tb_invalidate_phys_range(start, start + len, 0);
    }
    mmap_unlock();
    return ret;
}

abi_long target_mremap(abi_ulong old_addr, abi_ulong old_size,
                       abi_ulong new_size, unsigned long flags,
                       abi_ulong new_addr)
{
    int prot;
    void *host_addr;

    mmap_lock();

    if (flags & MREMAP_FIXED) {
        #ifndef __CYGWIN__
            host_addr = (void *) syscall(__NR_mremap, g2h(old_addr),
                                     old_size, new_size,
                                     flags,
                                     g2h(new_addr));
        #endif
        if (RESERVED_VA && host_addr != MAP_FAILED) {
            /* If new and old addresses overlap then the above mremap will
               already have failed with EINVAL.  */
            mmap_reserve(old_addr, old_size);
        }
    } else if (flags & MREMAP_MAYMOVE) {
        abi_ulong mmap_start;

        mmap_start = mmap_find_vma(0, new_size);

        if (mmap_start == -1) {
            errno = ENOMEM;
            host_addr = MAP_FAILED;
        } else {
        #ifndef __CYGWIN__
            host_addr = (void *) syscall(__NR_mremap, g2h(old_addr),
                                         old_size, new_size,
                                         flags | MREMAP_FIXED,g2h(mmap_start));
        #endif
            if ( RESERVED_VA ) {
                mmap_reserve(old_addr, old_size);
            }
        }
    } else {
        int prot = 0;
        if (RESERVED_VA && old_size < new_size) {
            abi_ulong addr;
            for (addr = old_addr + old_size;
                 addr < old_addr + new_size;
                 addr++) {
                prot |= page_get_flags(addr);
            }
        }
        if (prot == 0) {
            #ifndef __CYGWIN__
                host_addr = mremap(g2h(old_addr), old_size, new_size, flags);
            #endif
            if (host_addr != MAP_FAILED && RESERVED_VA && old_size > new_size) {
                mmap_reserve(old_addr + old_size, new_size - old_size);
            }
        } else {
            errno = ENOMEM;
            host_addr = MAP_FAILED;
        }
        /* Check if address fits target address space */
        if ((unsigned long)host_addr + new_size > (abi_ulong)-1) {
            /* Revert mremap() changes */
            #ifndef __CYGWIN__
                host_addr = mremap(g2h(old_addr), new_size, old_size, flags);
            #endif
            errno = ENOMEM;
            host_addr = MAP_FAILED;
        }
    }

    if (host_addr == MAP_FAILED) {
        new_addr = -1;
    } else {
        new_addr = h2g(host_addr);
        prot = page_get_flags(old_addr);
        page_set_flags(old_addr, old_addr + old_size, 0);
        page_set_flags(new_addr, new_addr + new_size, prot | PAGE_VALID);
    }
    tb_invalidate_phys_range(new_addr, new_addr + new_size, 0);
    mmap_unlock();
    return new_addr;
}

int target_msync(abi_ulong start, abi_ulong len, int flags)
{
    abi_ulong end;

    if (start & ~TARGET_PAGE_MASK)
        return -EINVAL;
    len = TARGET_PAGE_ALIGN(len);
    end = start + len;
    if (end < start)
        return -EINVAL;
    if (end == start)
        return 0;

    start &= qemu_host_page_mask;
    return msync(g2h(start), end - start, flags);
}
