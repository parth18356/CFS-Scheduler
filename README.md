Part 1: Compiling the source code The linux 3.19.0 source code is downloaded and it's extracted.

cd to that directory
do 'cp /boot/config-$(uname -r) .config' to copy the kernel's .config file then followed by 'make menuconfig'
use 'sudo make -j 4 && sudo make modules_install -j 4 && sudo make install -j 4'.The kernel and modules are compiled.
do 'update-initramfs -c -k 3.19.0' to update the kernel, and 'update-grub' to add it to the grub.
Part 2: Modifying CFS

Updated /include/linux/sched.h task struct to include srt flags and requirements.
Updated /kernel/sched/fair.c to include the required scheduling policy for SRT tasks.
Part 3: Making 'rtnice' System Call

Made info directory in the kernel.

'info' directory includes: ---- rtnice.c - C code for System call implementation. ---- rtnice.h - header file. ---- Makefile - Makefile for c code.

Updated arch/x86/syscalls/syscall64.tbl to include the 'rtnice' system call.

Updated Linux kernel main Makefile to include the 'rtnice' system call.

Part 4: Testing

rtnicetest.c tests the rtnice system call and the modified cfs scheduler. -- ERRORS:
if no task with given PID exists.
if timeslice < 1 or greater than a certain value.
