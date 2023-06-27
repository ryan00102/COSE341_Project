# CPU Scheduling Overhead analysis
This is for an assignment of Operation System

## Outline
Measures and analyzes the performance and context switching overhead of user programs according to time slice.

## Code description

### call_my_stack.c
- applications that use added system calls
- Calling a system call using a macro function called "syscall()"
  
### oslab_my_stack.c
- system call source to add

### syscall_64.tbl
- save the unique number of all system calls provided by Linux
- symbol information set for system calls
- After adding a system call, add the number and information for that system call

### syscalls.h
- define the prototype of system call functions
- After adding a system call, define the prototype for that system call
