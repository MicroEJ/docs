Principle
=========

A *resource* is, for a MicroEJ application, the contents of a file. This
file is known by its path (its relative path from the MicroEJ
application classpath) and its name. The file may be stored in RAM,
flash, or external flash; and it is the responsibility of the MicroEJ
core engine and/or the BSP to retrieve and load it.

MicroEJ platform makes the distinction between two kinds of resources:

-  Internal resource: The resource is taken into consideration during
   the MicroEJ application build. The SOAR step loads the resource and
   copies it into the same C library as the MicroEJ application. Like
   the MicroEJ application, the resource is linked into the CPU address
   space range (internal device memories, external parallel memories,
   etc.).

   The available list of internal resources to embed must be specified
   in the MicroEJ application launcher (MicroEJ launch). Under the tab
   “Resources”, select all internal resources to embed in the final
   binary file.

-  External resource: The resource is not taken into consideration by
   MicroEJ. It is the responsibility of the BSP project to manage this
   kind of resource. The resource is often programmed outside the CPU
   address space range (storage media like SD card, serial NOR flash,
   EEPROM, etc.).

   The BSP must implement some specific Low Level API (LLAPI) C
   functions: ``LLEXT_RES_impl.h``. These functions allow the MicroEJ
   application to load some external resources.
