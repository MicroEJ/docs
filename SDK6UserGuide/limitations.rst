.. _sdk_6_limitations:

Scope and Limitations
=====================

The SDK 6 allows to:

- build the Java artifact of an Application and an Add-On Library.
- execute the tests of a project with the Simulator and on a device.
- execute the Artifact Checker on a project.
- run an Application with the Simulator.
- load the VEE Port from its archive file path, its folder path, a dependency or from the ``dropins`` folder.
- build the Executable of an Application.
- build the WPK of an Application.

Therefore, it does not support all the features of the SDK 5, especially:

- build of Foundation Libraries, Mocks, VEE Ports or any other component type except Applications and Add-On Libraries.
- build of the Virtual Device of an Application.
- build of the Feature file (.fo) of an Application.
- resolve dependencies in the IDE.

If you need these features, you have to use :ref:`the SDK 5 <sdk_user_guide>`.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
