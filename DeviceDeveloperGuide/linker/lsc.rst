Linker Specific Configuration File Specification
================================================

Description
-----------

A Linker Specific Configuration (Lsc) file contains directives to link
input library units. An lsc file is written in an XML dialect, and its
contents can be divided into two principal categories:

-  Symbols and sections definitions.

-  Memory layout definitions.

<?xml version="1.0" encoding="UTF-8"?> <!-- An example of linker
specific configuration file --> <lsc name="MyAppInFlash"> <include
name="subfile.lscf"/> <!-- Define symbols with arithmetical and logical
expressions --> <defSymbol name="FlashStart" value="0"/> <defSymbol
name="FlashSize" value="0x10000"/> <defSymbol name="FlashEnd"
value="FlashStart+FlashSize-1"/> <!-- Define FLASH memory interval -->
<defSection name="FLASH" start="FlashStart" size="FlashSize"/> <!-- Some
memory layout directives --> <memoryLayout ranges ="FLASH"> <sectionRef
name ="*.text"/> <sectionRef name ="*.data"/> </memoryLayout> </lsc>

File Fragments
--------------

An lsc file can be physically divided into multiple lsc files, which are
called lsc fragments. Lsc fragments may be loaded directly from the
linker path option, or indirectly using the include tag in an lsc file.

Lsc fragments start with the root tag ``lscFragment``. By convention the
lsc fragments file extension is ``.lscf``. From here to the end of the
document, the expression "the lsc file" denotes the result of the union
of all loaded (directly and indirectly loaded) lsc fragments files.

Symbols and Sections
--------------------

A new symbol is defined using ``defSymbol`` tag. A symbol has a name and
an expression value. All symbols defined in the lsc file are global
symbols.

A new section is defined using the ``defSection`` tag. A section may be
used to define a memory interval, or define a chunk of the final image
with the description of the contents of the section.
