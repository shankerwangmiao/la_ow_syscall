/*
  This file is used to test if the coresponding macro is defined in unistd.h
    If a macro is defined, the coresponding function will be defined, and
    the symbol will be shown in the .o file. Later, the Kbuild script will
    generate kernel_feature.h according to the existence of the symbols.
*/

#include <asm/unistd.h>
#ifdef __ARCH_WANT_NEW_STAT
void kernel_have_new_stat(void);
void kernel_have_new_stat(void){ }
#endif
#ifndef __SYSCALL
void kernel_have_systbl(void);
void kernel_have_systbl(void){ }
#endif
