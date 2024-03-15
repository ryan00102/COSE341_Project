# Korea University Operating System Projects

## SystemCall_Addition
This is for an assignment of Operation System

### Outline
Add a new System Call to an existing Kernel and then implement a Use Application to invoke it

### Code description

#### call_my_stack.c
- applications that use added system calls
- Calling a system call using a macro function called "syscall()"
  
#### oslab_my_stack.c
- system call source to add

#### syscall_64.tbl
- save the unique number of all system calls provided by Linux
- symbol information set for system calls
- After adding a system call, add the number and information for that system call

#### syscalls.h
- define the prototype of system call functions
- After adding a system call, define the prototype for that system call



## CPU Scheduling Overhead analysis
This is for an assignment of Operation System

### Outline
Measures and analyzes the performance and context switching overhead of user programs according to time slice.

#### Implementing user programs for performance analysis 
- Implement a C program that performs simple matrix operations for CPU use
- As an output value, the number of operations performed at each epoch and the actual execution time of each epoch are outputted every 100 ms from the time the matrix operation for each process is started during execution, and the total number and time calculated by the process at the end of the process.

#### Analysis of matrix operation performance changes according to Time Slice
- The CPU scheduling method for the generated program is changed to Round Robin, and the time slice of the RR scheduler is changed to 1ms, 10ms, and 100ms, and the performance difference according to the time slice change is analyzed.
- Experiment: Measure the sum of the number of matrix operations performed by each process for a unit time (30 seconds)
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/8ed9ac40-464d-4932-8241-e83f99f3cfd7"  width="400" height="250">
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/0d0bea70-b634-4e0c-8ca6-47c8cd3a7e54"  width="400" height="250">
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/da8a132e-82d7-4b21-8014-ee092e267537"  width="400" height="250">
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/67a1ec9c-b973-466b-935d-b7da26e95def"  width="400" height="250">

#### Analysis of Performance Changes Using CPU Burst Time
- To analyze more accurate performance changes, we analyze the amount of matrix operations performed by each matrix operation process per unit time based on CPU Burst Time.
- To measure the CPU execution time, the CPU burst time is measured at the kernel level
- While changing the RR scheduler's Time Slice to 1ms, 10ms, and 100ms, the performance difference according to the change in Time Slice is analyzed.
- Processes are classified using pid, and the sum of CPU Burst for each process is calculated using programs such as Excel.
- Experiment: Measure the number of matrix operations relative to CPU Burst Time

<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/bf108684-3389-496f-9a5a-417da4b68b67"  width="400" height="250">
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/86360a13-1e01-424f-86ae-ca31fc91e309"  width="400" height="250">
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/acd01fef-0b3b-4013-ab04-2c70fd115bff"  width="400" height="250">
<img src="https://github.com/ryan00102/CPU_Scheduling_Overhead_Analysis/assets/101000358/2be13eb0-f6f5-49a7-832c-0b686f81dea2"  width="400" height="250">

