.. _section_bsp_xml:

BSP Files
=========

The MicroEJ platform needs some information about the board project (the
BSP). This information is required for building a MicroEJ application
that is compatible with the BSP.

Some BSP files (XML files) are required to configure the MicroEJ
platform modules. The name of these files must be ``bsp.xml``. They must
be stored in each module's configuration folder.

This file must start with the node ``<bsp>``. It can contain several
lines like this one:
``<nativeName="A_LLAPI_NAME" nativeImplementation name="AN_IMPLEMENTATION_NAME"/>``
where:

-  ``A_LLAPI_NAME`` refers to a Low Level API native name. It is
   specific to the MicroEJ C library which provides the Low Level API.

-  ``AN_IMPLEMENTATION_NAME`` refers to the implementation name of the
   Low Level API. It is specific to the BSP; and more specifically, to
   the C file which does the link between the MicroEJ C library and the
   C driver.

Example:

::

   <bsp>
       <nativeImplementation name="COMM_DRIVER" nativeName="LLCOMM_BUFFERED_CONNECTION"/>
   </bsp>

The BSP tool converts these files into an internal format during the
MicroEJ platform build.
