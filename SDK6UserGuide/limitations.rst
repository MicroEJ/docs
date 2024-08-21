.. _sdk_6_limitations:

Scope and Limitations
=====================

The SDK 6 allows to:

- Build the Java artifact of an Application and an Add-On Library.
- Execute the tests of a project with the Simulator and on a device.
- Execute the Artifact Checker on a project.
- Run an Application with the Simulator.
- Load the VEE Port from its archive file path, its folder path or a dependency.
- Build the Executable of an Application.
- Build the WPK of an Application.
- Build the Feature file (.fo) of an Application.
- Build the Virtual Device of an Application.
- Use the Stack Trace Reader.
- Use the Code Coverage Analyzer.
- Use the Font Designer, Memory Map Analyzer, Heap Analyzer and Front Panel Designer tools.
- Build a Kernel Application.

Therefore, it does not support all the features of the SDK 5, especially:

- Build of Foundation Libraries, VEE Ports or any other component type except Applications, Add-On Libraries and Mocks.
- Launch of some MicroEJ tools, such as the Local Deploy, the Serial to Socket Transmitter or the Kernel Metadata Generator.


If you need these features, you have to use :ref:`the SDK 5 <sdk_user_guide>`.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
