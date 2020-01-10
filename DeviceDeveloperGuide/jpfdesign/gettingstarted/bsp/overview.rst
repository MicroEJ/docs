Principle
=========

When the MicroEJ platform is built, the user can compile a MicroEJ
application on that platform. However, the result of this compilation is
not sufficient. A third-party C project is required to obtain the final
binary file to flash on a board.

This third-party C project is usually configured to target only one
board. It contains some C files, header directories, C libraries, etc.
Using this C project, the user can build (compile and link) a binary
file which contains the specific MCU and board libraries, the foundation
libraries, and the MicroEJ application.

The BSP tool configures the third-party project, updating the
third-party C-IDE project file, adding some C libraries and filling some
header directories.
