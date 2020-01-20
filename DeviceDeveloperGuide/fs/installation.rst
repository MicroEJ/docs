Installation
============

FS is an additional module. In the platform configuration file, check
``FS`` to install it. When checked, the properties file ``fs
            > 
            fs.properties`` are required during platform creation in
order to configure the module.

The properties file must / can contain the following properties:

-  ``fs`` [optional, default value is "Custom"]: Defines the kind of
   File System native stack used in the C project.

   -  ``Custom``: select this configuration to make a specific File
      System portage.

   -  ``FatFS``: select this configuration to use FatFS native File
      System-compliant settings.

-  ``root.dir`` [optional, for a FatFS File System. Mandatory, for a
   Custom File System.]: Defines the native File System root volume
   (default value is "/" for FatFS).

-  ``user.dir`` [optional, for a FatFS File System. Mandatory, for a
   Custom File System.]: Defines the native File System user directory
   (default value is "/usr" for FatFS).

-  ``tmp.dir`` [optional, for a FatFS File System. Mandatory, for a
   Custom File System.]: Defines the native File System temporary
   directory (default value is "/tmp" for FatFS).

-  ``file.separator`` [optional, for a FatFS File System. Mandatory, for
   a Custom File System.]: Defines the native File System file separator
   (default value is "/" for FatFS).

-  ``path.separator`` [optional, for a FatFS File System. Mandatory, for
   a Custom File System.]: Defines the native File System path separator
   (default value is ":" for FatFS).
