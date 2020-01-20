Third-party C Project
=====================

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
