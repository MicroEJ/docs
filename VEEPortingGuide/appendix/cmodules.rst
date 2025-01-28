.. _CMODULES-CHAPTER:

======================
C Modules Installation
======================

This section describes how to install a C module on your VEE Port, depending on your SDK version the first steps will vary.

Fetching the module source files
++++++++++++++++++++++++++++++++

SDK 5
=====

Under the SDK 5 follow these steps:

- Go to the location of your C module, for example the C module for microUI 14.2.0 is located `here <https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/14.2.0/>`_.
- Get the dependency declaration, for the previous example this would be: ``<dependency org="com.microej.clibrary.llimpl" name="microui" rev="14.2.0" />``.
- Add it inside the block ``<dependencies>`` from the file ``module.ivy`` of your ``*-configuration`` project.
- Remove the ``.properties`` files in the folder ``*-bsp/projects/microej``.
- Build the module ``*-configuration/``.

SDK 6
=====

Under the SDK 6 follow these steps:

- Go to the location of your C module, for example the C module for microUI 14.2.0 is located `here <https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/14.2.0/>`_.
- Download the archive file ``.cco``.
- Unzip the content of this file.
- The source files are located in the folder ``bsp/``.
- Copy the content of this folder into your VEE Port BSP.

Configure and Build
+++++++++++++++++++

- Update the build of your BSP (IAR, CMake, etc) to include any new files if this is case.
- Configure the module if required (typically the configuration is located in files suffixed with ``*_configuration.h``).
- Now you should be able to build your BSP.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
