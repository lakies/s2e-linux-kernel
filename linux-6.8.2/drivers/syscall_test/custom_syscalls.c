#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/trace_events.h>

int global_var = 0;
int global_array[10];

struct GlobalStruct {
    int value;
};
struct GlobalStruct global_struct = {42};

asmlinkage long sys_write_global_var(void) {
    global_var = 42;
    printk(KERN_INFO "sys_write_global_var called\n");
    return 0;
}

asmlinkage long sys_write_global_var_with_param(int param) {
    if (param == 42) {
        global_var = 1;
    }
    printk(KERN_INFO "sys_write_global_var_with_param called with param: %d\n", param);
    return 0;
}

asmlinkage long sys_read_global_var(void) {
    if (global_var == 42) {
        printk(KERN_INFO "The answer to life, the universe, and everything.\n");
    } else {
        printk(KERN_INFO "Not the answer.\n");
    }
    return 0;
}

asmlinkage long sys_read_global_var_explicit(void) {
    int local_var = global_var;
    if (local_var == 42) {
        printk(KERN_INFO "The answer to life, the universe, and everything.\n");
    } else {
        printk(KERN_INFO "Not the answer.\n");
    }
    return 0;
}

asmlinkage long sys_read_global_var_implicit(void) {
    int local_var = 0;
    if (global_var == 42) {
        local_var = 1;
    }
    if (local_var == 1) {
        printk(KERN_INFO "The answer to life, the universe, and everything.\n");
    } else {
        printk(KERN_INFO "Not the answer.\n");
    }
    return 0;
}

asmlinkage long sys_read_global_var_with_param(int param) {
    if (param == 1 && global_var == 42) {
        printk(KERN_INFO "The answer to life, the universe, and everything.\n");
    } else {
        printk(KERN_INFO "Not the answer.\n");
    }
    return 0;
}

asmlinkage long sys_write_global_array(void) {
    global_array[0] = 42;
    printk(KERN_INFO "sys_write_global_array called\n");
    return 0;
}

asmlinkage long sys_read_global_struct(void) {
    if (global_struct.value == 42) {
        printk(KERN_INFO "The answer to life, the universe, and everything.\n");
    } else {
        printk(KERN_INFO "Not the answer.\n");
    }
    return 0;
}

asmlinkage long sys_write_param_into_var(int param) {
    global_var = param;
    printk(KERN_INFO "sys_write_param_into_var called.\n");
    return 0;
}

asmlinkage long sys_write_param_into_struct(int param) {
    global_struct.value = param;
    printk(KERN_INFO "sys_write_param_into_struct called.\n");
    return 0;
}

SYSCALL_DEFINE0(write_global_var) {
    return sys_write_global_var();
}

SYSCALL_DEFINE1(write_global_var_with_param, int, param) {
    return sys_write_global_var_with_param(param);
}

SYSCALL_DEFINE0(read_global_var) {
    return sys_read_global_var();
}

SYSCALL_DEFINE0(read_global_var_explicit) {
    return sys_read_global_var_explicit();
}

SYSCALL_DEFINE0(read_global_var_implicit) {
    return sys_read_global_var_implicit();
}

SYSCALL_DEFINE1(read_global_var_with_param, int, param) {
    return sys_read_global_var_with_param(param);
}

SYSCALL_DEFINE0(write_global_array) {
    return sys_write_global_array();
}

SYSCALL_DEFINE0(read_global_struct) {
    return sys_read_global_struct();
}

SYSCALL_DEFINE1(write_param_into_struct, int, param) {
    return sys_write_param_into_struct(param);
}

SYSCALL_DEFINE1(write_param_into_var, int, param) {
    return sys_write_param_into_var(param);
}
