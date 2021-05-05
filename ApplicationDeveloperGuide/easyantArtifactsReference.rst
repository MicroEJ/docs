Build types
=========

build-firmware-singleapp
------------------------

The build type `build-firmware-singleapp` allows to produces a firmware from an application and a platform.

Inputs:
- properties files in the `build` folder
- Java sources of the application in `src/main/java`, containing at least a `main` class.
- a platform, which can be provided by one of the ways described in the chapter "Loading a platform"

Outputs:
- firmware
- virtual device

The available properties of this build type are:

   +-------------------------------+----------------------------------------------------------+----------+---------+
   | Name                          | Description                                              | Required | Default |
   +===============================+==========================================================+==========+=========+
   | application.main.class        | Full Qualified Name of the main class of the application | Yes      |         |
   +-------------------------------+----------------------------------------------------------+----------+---------+
   | virtual.device.sim.only       | When this property is set (any value), the firmware is   | No       | Not set |
   |                               | not built                                                |          |         |
   +-------------------------------+----------------------------------------------------------+----------+---------+
   | skip.build.virtual.device     | When this property is set (any value), the virtual       | No       | Not set |
   |                               | device is not created                                    |          |         |
   +-------------------------------+----------------------------------------------------------+----------+---------+

..
   | Copyright 2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
