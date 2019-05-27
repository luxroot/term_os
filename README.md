# OS Term project for 2019-1

## CPU scheduler for these algorithms
* FCFS
* Preemptive / Non-preemptive SJF
* Preemptive / Non-preemptive Priority
* Round robin (To be updated)

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
./term
```
Execution
```$xslt
usage : ./term [number of processes] [[arrival weight]] [[printing lines]]
```
Note that Arrival weight and Printing lines are optional argument

(default value : arrival_weight=10, printLines=50) 