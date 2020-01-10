.. _linker-autosections:

Auto-generated Sections
=======================

The LINKER allows you to define sections that are automatically
generated with symbol values. This is commonly used to generate tables
whose contents depends on the linked symbols. Symbols eligible to be
embedded in an auto-generated section are of the form:
``prefix_tag_suffix``. An auto-generated section is viewed as a table
composed of lines and columns that organize symbols sharing the same
prefix. On the same column appear symbols that share the same tag. On
the same line appear symbols that share the same suffix. Lines are
sorted in the lexical order of the symbol name. The next line defines a
section which will embed symbols starting with ``zeroinit``. The first
column refers to symbols starting with ``zeroinit_start_``; the second
column refers to symbols starting with ``zeroinit_end_``.

::

   <defSection
           name=".zeroinit" 
           symbolPrefix="zeroInit" 
           symbolTags="start,end"
       />

Consider there are four defined symbols named ``zeroinit_start_xxx``,
``zeroinit_end_xxx``, ``zeroinit_start_yyy`` and ``zeroinit_end_yyy``.
The generated section is of the form:

::

   0x00: zeroinit_start_xxx
   0x04: zeroinit_end_xxx 
   0x08: zeroinit_start_yyy
   0x0C: zeroinit_end_yyy

If there are missing symbols to fill a line of an auto-generated
section, an error is thrown.
