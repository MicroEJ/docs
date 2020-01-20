ELF Overview
============

An ELF relocatable file is split into several sections:

-  allocation sections representing a part of the program

-  control sections describing the binary sections (relocation sections,
   symbol tables, debug sections, etc.)

An allocation section can hold some image binary bytes (assembler
instructions and raw data) or can refer to an interval of memory which
makes sense only at runtime (statics, main stack, heap, etc.). An
allocation section is an atomic block and cannot be split. A section has
a name that by convention, represents the kind of data it holds. For
example, ``.text`` sections hold binary instructions, ``.bss`` sections
hold read-write static data, ``.rodata`` hold read-only data, and
``.data`` holds read-write data (initialized static data). The name is
used in the .lsc file to organize sections.

A symbol is an entity made of a name and a value. A symbol may be
absolute (link-time constant) or relative to a section: Its value is
unknown until MicroEJ Linker has assigned a definitive position to the
target section. A symbol can be local to the relocatable file or global
to the system. All global symbol names should be unique in the system
(the name is the key that connects an unresolved symbol reference to a
symbol definition). A section may need the value of symbols to be fully
resolved: the address of a function called, address of a static
variable, etc.
