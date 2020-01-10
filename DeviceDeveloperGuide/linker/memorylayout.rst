Memory Layout
=============

A memory layout contains an ordered set of statements describing what
shall be embedded. Memory positioning can be viewed as moving a cursor
into intervals, appending referenced sections in the order they appear.
A symbol can be defined as a "floating" item: Its value is the value of
the cursor when the symbol definition is encountered. In
`figure_title <#linker-memorylayout-example>`__, the memory layout sets
the ``FLASH`` section. First, all sections named ``.text`` are embedded.
The matching sections are appended in a undefined order. To reference a
specific section, the section shall have a unique name (for example a
reset vector is commonly called ``.reset`` or ``.vector``, etc.). Then,
the floating symbol ``dataStart`` is set to the absolute address of the
virtual cursor right after embedded ``.text`` sections. Finally all
sections named ``.data`` are embedded.

A memory layout can be relocated to a memory interval. The positioning
works in parallel with the layout ranges, as if there were two cursors.
The address of the section (used to resolve symbols) is the address in
the relocated interval. Floating symbols can refer either to the layout
cursor (by default), or to the relocated cursor, using the
``relocation`` attribute. A relocation layout is typically used to embed
data in a program image that will be used at runtime in a read-write
memory. Assuming the program image is programmed in a read only memory,
one of the first jobs at runtime, before starting the main program, is
to copy the data from read-only memory to ``RAM``, because the symbols
targeting the data have been resolved with the address of the sections
in the relocated space. To perform the copy, the program needs both the
start address in ``FLASH`` where the data has been put, and the start
address in ``RAM`` where the data shall be copied.

<memoryLayout ranges="FLASH" relocation="RAM" image="true"> <defSymbol
name="DataFlashStart" value="."/> <defSymbol name="DataRamStart" value="
." relocation="true"/> <sectionRef name=".data"/> <defSymbol
name="DataFlashLimit" value="."/> </memoryLayout>

Note: the symbol ``DataRamStart`` is defined to the start address where
``.data`` sections will be inserted in ``RAM`` memory.
