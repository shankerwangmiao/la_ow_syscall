# SPDX-License-Identifier: GPL-2.0
#
# Makefile for LoongArch old-world syscall compatible layer.
#

ifdef KBUILD_EXTMOD
CONFIG_LOONGARCH_OW_SYSCALL := m
endif

obj-$(CONFIG_LOONGARCH_OW_SYSCALL) += la_ow_syscall.o
la_ow_syscall-y += fsstat.o la_ow_syscall_main.o signal.o systable.o
targets += feat_test.o

$(obj)/kernel_feature.h: $(obj)/feat_test.syms
	@$(kecho) '  GEN     $@'
	$(Q)if grep "kernel_have_new_stat" $< >/dev/null; then \
		echo "#define KERNEL_HAVE_NEW_STAT"; \
	    else \
		echo "/* KERNEL_HAVE_NEW_STAT is not defined */"; \
	    fi > $@
	$(Q)if grep "kernel_have_systbl" $< >/dev/null; then \
                echo "#define KERNEL_HAVE_SYSTBL"; \
            else \
                echo "/* KERNEL_HAVE_SYSTBL is not defined */"; \
            fi >> $@

$(obj)/feat_test.syms: $(obj)/feat_test.o
	@$(kecho) '  GEN     $@'
	$(Q)$(OBJDUMP) -t --section=.text $< >$@

$(obj)/module_version.h: $(src)/VERSION
	@$(kecho) '  GEN     $@'
	$(Q)echo "#define THIS_MODULE_VERSION \"$(shell cat $<)\"" > $@

$(obj)/systable.o $(obj)/fsstat.o: $(obj)/kernel_feature.h
$(obj)/la_ow_syscall_main.o: $(obj)/module_version.h

clean-files += kernel_feature.h feat_test.syms module_version.h
