struct syscall_replace_table {
        long syscall_num;
        void *symbol_addr;
        void *orig;
};

extern const char *sys_call_table_name[];
extern struct syscall_replace_table syscall_to_replace[];
