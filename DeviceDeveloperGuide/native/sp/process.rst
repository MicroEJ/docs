Functional Description
======================

The usage of the Shielded Plug (SP) starts with the definition of a
database. The implementation of the SP for the PLATFORM uses an XML file
description to describe the database; the syntax follows the one
proposed by the SP specification [SP].

Once this database is defined, it can be accessed within the MicroEJ
application or the C application. The SP foundation library is
accessible from the classpath variable ``SP-SP.VERSION``. This library
contains the classes and methods to read and write data in the database.
See also the Java documentation from the MicroEJ workbench resources
center ("Javadoc" menu). The C header file sp.h available in the MicroEJ
platform ``source/MICROJVM/include`` folder contains the C functions for
accessing the database.

To embed the SP database in your binary file, the XML file description
must be processed by the SP compiler. This compiler generates a binary
file (.o) that will be linked to the overall application by the linker.
It also generates two descriptions of the block ID constants, one in
Java and one in C. These constants can be used by either the Java or the
C application modules.
