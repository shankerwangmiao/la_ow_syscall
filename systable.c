#include "systable.h"
#include "kernel_feature.h"

/*
  In 6.11 or newer, the asm-generic/unistd.h is not used by the loongarch
    asm/unistd.h. Instead, the definition of the syscall table and the syscall
    numbers is generated after commit 26a3b85bac08 ("loongarch: convert to
    generic syscall table"). As a result, we can no more get the definition of
    those syscalls that are not available on Loongarch.

  To solve this problem, we still use asm-generic/unistd.h to retrive the
    definitions.

  To avoid any possible conflicts, only syscall related data are defined here.
    No functions are implemented here, so the above hacks will not affect other
    parts of our module and will not introduce unexpected changes related to the
    syscall numbers, ensuring the consistence of our module with the kernel.
*/

#include <asm-generic/unistd.h>

/*
  And we also need those hacks to prevent including asm/unistd.h, which will
    cause redefinition of the syscall numbers.
*/

#define _LINUX_UNISTD_H_	/* prevent loading uapi/linux/unistd.h */
#define __ASM_VDSO_H		/* prevent loading asm/vdso.h */
#define _ASM_SECCOMP_H		/* prevent loading asm/seccomp.h */
#include <linux/syscalls.h>

#define __ARCH_WANT_SET_GET_RLIMIT
#define __ARCH_WANT_NEW_STAT

#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (#call),

const char *sys_call_table_name[__NR_syscalls] = {
	[0 ... __NR_syscalls - 1] = "sys_ni_syscall",
#include <asm-generic/unistd.h>
};

struct syscall_replace_table syscall_to_replace[] = {
#ifndef KERNEL_HAVE_NEW_STAT
	{ __NR_fstat, sys_newfstat },
	{ __NR_newfstatat, sys_newfstatat },
#endif
	{ __NR_getrlimit, NULL },
	{ __NR_setrlimit, NULL },
	{ __NR_rt_sigprocmask, sys_rt_sigprocmask },
	{ __NR_rt_sigpending, sys_rt_sigpending },
	{ __NR_rt_sigtimedwait, sys_rt_sigtimedwait },
	{ __NR_rt_sigaction, sys_rt_sigaction },
	{ __NR_rt_sigsuspend, sys_rt_sigsuspend },
	{ __NR_pselect6, sys_pselect6 },
	{ __NR_ppoll, sys_ppoll },
#ifdef CONFIG_SIGNALFD
	{ __NR_signalfd4, sys_signalfd4 },
#endif
#ifdef CONFIG_EPOLL
	{ __NR_epoll_pwait, sys_epoll_pwait },
	{ __NR_epoll_pwait2, sys_epoll_pwait2 },
#endif
	{ -1, NULL },
};
