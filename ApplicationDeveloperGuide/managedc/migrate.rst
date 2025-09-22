Migrate Existing from Linux Code to Managed C
=============================================
**Draft**

This section describes things to consider for updating an existing C code that has been written for Linux target, migrating that you want to migrate to Managed C.
By migrating to Managed C, your code will be portable code for across all MicroEJ VEE Ports, for any MCU/MPU, RTOS or Linux targets.
- Cross-Platform: Ensuring the codebase can run on both Linux and non-Linux embedded systems.
- Performance: Optimizing for low-resource or specialized hardware without full Linux support.
The process of making software compatible with non-Linux environments, by removing or abstracting dependencies on Linux-specific features is called "unlinuxify".

1. Compile with WASI-SDK
You have to update your project build using xxx compilation page. As WASI-SDK is based on the clang/llvm toolchain, it is usually just about setuping an other cross compilation toolchain. 
    Signals
        -D_WASI_EMULATED_SIGNAL
        -lwasi-emulated-signal
    Pid
        -D_WASI_EMULATED_GETPID
        -lwasi-emulated-getpid


    -D_WASI_EMULATED_PROCESS_CLOCKS \
    ?
    -D_WASI_EMULATED_MMAN \

    Exceptions
        C++ code is supported with -fno-exceptions compiler option


    pthreads
        see xxx enable
    
    process (fork)
-Wno-c23-extensions
--no-export-dynamic
2. Run the Dependency Discoverer. It will show up the list of instructions.

2.