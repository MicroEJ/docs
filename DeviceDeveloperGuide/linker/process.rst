Linking Process
===============

The linking process can be divided into three main steps:

1. Symbols and sections resolution. Starting from root symbols and root
   sections, the linker embeds all sections targeted by symbols and all
   symbols referred by sections. This process is transitive while new
   symbols and/or sections are found. At the end of this step, the
   linker may stop and output errors (unresolved symbols, duplicate
   symbols, unknown or bad input libraries, etc.)

2. Memory positioning. Sections are laid out in memory ranges according
   to memory layout constraints described by the lsc file. Relocations
   are performed (in other words, symbol values are resolved and section
   contents are modified). At the end of this step, the linker may stop
   and output errors (it could not resolve constraints, such as not
   enough memory, etc.)

3. An output ELF executable file and map file are generated.

A partial map file may be generated at the end of step 2. It provides
useful information to understand why the link phase failed. Symbol
resolution is the process of connecting a global symbol name to its
definition, found in one of the linker input units. The order the units
are passed to the linker may have an impact on symbol resolution. The
rules are :

-  Relocatable object files are loaded without order. Two global symbols
   defined with the same name result in an unrecoverable linker error.

-  Archive files are loaded on demand. When a global symbol must be
   resolved, the linker inspects each archive unit in the order it was
   passed to the linker. When an archive contains a relocatable object
   file that declares the symbol, the object file is extracted and
   loaded. Then the first rule is applied. It is recommended that you
   group object files in archives as much as possible, in order to
   improve load performances. Moreover, archive files are the only way
   to tie with relocatable object files that share the same symbols
   definitions.

-  A symbol name is resolved to a weak symbol if - and only if - no
   global symbol is found with the same name.
