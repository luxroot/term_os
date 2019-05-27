# OS Term project for 2019-1

## CPU scheduler for these algorithms
* FCFS
* Preemptive / Non-preemptive SJF
* Preemptive / Non-preemptive Priority
* Round robin
* Preemptive / Non-preemptive HRRN (to be updated)

## Dependencies
* GCC
* Make
* CMake

You can install these packages using apt

``` sudo apt install gcc make cmake -y```

## Usage
You can execute my program after compiling it

Compile
```
cmake CMakeLists.txt
make
```
Execution
```
usage : ./term [number of processes] [[time quantum=3]] [[arrival weight]=50] [[printing lines=10]]
```
Note that Time Quantum, Arrival weight and Printing lines are optional argument