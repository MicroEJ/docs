.. _sdk_6_limitations:

Scope and Limitations
=====================

The SDK 6 allows to:

- build the Java artifact of Applications and Add-On Libraries.
- execute the tests of a project with the Simulator.
- execute the Artifact Checker on a project.
- load of the VEE Port from the dropins folder.
- run Applications with the Simulator.

Therefore, it does not support all the features of the SDK 5, especially:

- build of Foundation Libraries, Mocks, VEE Ports or any other component type except Applications and Add-On Libraries.
- build of a Standalone Application Executable.
- build of the Virtual Device of an Standalone Application.
- build of the Feature file (.fo) of a Sandboxed Application.
- build of the WPK of a Sandboxed Application.
- execution of tests on a device.
- execution of a test project on a device.
- resolve dependencies in the IDE.

If you need these features, you have to use :ref:`the SDK 5 <sdk_user_guide>`.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
