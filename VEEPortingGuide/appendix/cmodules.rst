.. _CMODULES-CHAPTER:

======================
C Modules Installation
======================

To manually install a C module for a VEE Port follow these steps:

- Go to the location of your C module, for example the C module for microUI 14.2.0 is located `here <https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/14.2.0/>`_.
- Download the archive file ``.cco``.
- Unzip the content of this file.
- The source files are located in the folder ``bsp/``.
- Copy the content of this folder into your VEE Port BSP.
- Update the build of your BSP (IAR, CMake, etc) to include any new files if this is case.
- Configure the module if required (typically the configration is located in files suffixed with ``*_configuration.h``).
- Now you should be able to build your BSP.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
