Principle
=========

The MicroEJ C libraries have been built for a specific processor (a
specific MCU architecture) with a specific C compiler. The third-party
linker must make sure to link C libraries compatible with the MicroEJ C
libraries. This chapter details the compiler version, flags and options
used to build MicroEJ C libraries for each processor.

Some processors include an optional floating point unit (FPU). This FPU
is single precision (32 bits) and is compliant with IEEE 754 standard.
It can be disabled when not in use, thus reducing power consumption.
There are two steps to use the FPU in an application. The first step is
to tell the compiler and the linker that the microcontroller has an FPU
available so that they will produce compatible binary code. The second
step is to enable the FPU during execution. This is done by writing to
CPAR in the SystemInit() function. Even if there is an FPU in the
processor, the linker may still need to use runtime library functions to
deal with advanced operations. A program may also define calculation
functions with floating numbers, either as parameters or return values.
There are several Application Binary Interfaces (ABI) to handle floating
point calculations. Hence, most compilers provide options to select one
of these ABIs. This will affect how parameters are passed between caller
functions and callee functions, and whether the FPU is used or not.
There are three ABIs:

-  Soft ABI without FPU hardware. Values are passed via integer
   registers.

-  Soft ABI with FPU hardware. The FPU is accessed directly for simple
   operations, but when a function is called, the integer registers are
   used.

-  Hard ABI. The FPU is accessed directly for simple operations, and
   FPU-specific registers are used when a function is called, for both
   parameters and the return value.

It is important to note that code compiled with a particular ABI might
not be compatible with code compiled with another ABI. MicroEJ modules,
including the MicroEJ core engine, use the hard ABI.
