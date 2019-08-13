# mono_thread_problem
demo code for a problem when using embedded mono and native threads

seen for mono 6.0.0.319

# Description
C++ code calling a method on a c# object
The execution hangs when there is a combination of c++ threads and large memory allocations in the c# code.
Only tested on Ubuntu 18.04

# Usage
Run "test.sh" to build and demonstrate the problem

