# SPDX-License-Identifier: GPL-2.0
#
# Makefile for LoongArch old-world syscall compatible layer.
#

ifdef KBUILD_EXTMOD
CONFIG_LOONGARCH_OW_SYSCALL := m
endif

obj-$(CONFIG_LOONGARCH_OW_SYSCALL) += la_ow_syscall.o
la_ow_syscall-y += fsstat.o la_ow_syscall_main.o signal.o
