Shielded Plug Compiler
======================

A MicroEJ tool is available to launch the SP compiler tool. The tool
name is Shielded Plug Compiler. It outputs:

-  A description of the requested resources of the database as a binary
   file (``.o``) that will be linked to the overall application by the
   linker. It is an ELF format description that reserves both the
   necessary RAM and the necessary Flash memory for the database of the
   Shielded Plug.

-  Two descriptions, one in Java and one in C, of the block ID constants
   to be used by either Java or C application modules.
