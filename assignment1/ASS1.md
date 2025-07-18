## Question 1 - /proc

a. "core" is an individual unit of the CPU which does computation. "processor" is the thing which is used to assign the work. Each core has one processor if hyper-threading is not enabled. Otherwise, each core pretends to behave like 2 cores. E.g. while executing a code, there may be parts of the core which are idle. If there exists another code which needs those parts, these two codes can run in parallel so that all parts of the core can run in parallel (giving an illusion of 2 cores). But if both the "logical CPUs" or "processors" want to use the same component of the core, then one processor has to wait till the other finishes. Thus, hyperthreading is just a bonus and not equivalent to having two cores.

b. 6 <br>
Command used: `cat /proc/cpuinfo`

c. 6 <br>
Command used: `cat /proc/cpuinfo`

d. 2496 MHz <br>
Command used: `cat /proc/cpuinfo`

e. x86\_64 <br>
Command used: `lscpu`

f. Total Memory: 4039356 kB <br>
Command used: `cat /proc/meminfo`

g. Free Memory: 3190768 kB <br>
Command used: `cat /proc/meminfo`

h. context switches (ctxt) - 524145, forks (processes) - 2915 <br>
Command used: `cat /proc/stat`

## Question 2 - top

a. 3204

b. CPU - 99.7%, Memory - 0.0%

c. Running

## Question 3 - Memory

For `memory1.c`:
RSS: 864 KiB, VSZ: 8300 Kib

For `memory2.c`:
RSS: 3188 KiB, VSZ: 8300 Kib

This is because in the first case, no array index is accessed. So the system does not allocate memory for the array. However, the second program accesses the elements. When the programs accesses a particular index, the system grants memory for it. Probably that is why about half the virtual memory allocated is used as physical memory (half the array is accessed).

## Question 6
![Image showing process list](q6/Screenshot_Q6.png)
