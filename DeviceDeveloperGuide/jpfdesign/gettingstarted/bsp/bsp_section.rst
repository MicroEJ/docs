BSP Tool
========


Principle
---------

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


Third-party C Project
---------------------

The BSP tool is able to configure automatically the board C project.
Fill the ``bsp`` > ``bsp.properties`` properties file to enable the
third-party C project configuration during the MicroEJ platform build.

The properties file can contain the following properties:

-  ``project.file`` [optional, default value is "" (*empty*)]: Defines
   the full path of the C project file. This file will be updated with
   the platform libraries. If not set or empty, no C project is updated.

-  ``project.libs.group.name`` [optional, default value is ""
   (*empty*)]: Defines the libraries group name of the C project file.
   This property is required if property ``project.file`` is set.

-  ``project.includes.output.dir`` [optional, default value is ""
   (*empty*)]: Defines the full path of the C project's other header
   files (*.h) output directory. All platform header files (*.h) will be
   copied into that directory. If not set or empty, no header platform
   files are copied.


.. _section_bsp_xml:

BSP Files
---------

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


Dependencies
------------

No dependency.


.. _section_bsp_installation:

Installation
------------

The BSP tool is automatically called during the MicroEJ platform build.
