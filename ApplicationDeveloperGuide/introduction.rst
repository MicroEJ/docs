.. _Standalone_vs_Sandboxed:
.. _concepts-microejapplications:

Introduction
============

The following sections of this document shall prove useful as a
reference when developing applications for MicroEJ. They cover concepts
essential to MicroEJ Applications design.

In addition to these sections, by going to
`<https://developer.microej.com/>`_, you can access a number of helpful
resources such as:

-  Libraries from the MicroEJ Central Repository
   (`<https://developer.microej.com/central-repository/>`_);

-  Application Examples as source code from MicroEJ Github Repositories
   (`<https://github.com/MicroEJ>`_);

-  Documentation (HOWTOs, Reference Manuals, APIs javadoc...).


MicroEJ Applications are developed as standard Java applications on
Eclipse JDT, using Foundation Libraries. MicroEJ SDK allows you to
run / debug / deploy MicroEJ Applications on a MicroEJ Platform.

Two kinds of applications can be developed on MicroEJ: MicroEJ
Standalone Applications and MicroEJ Sanboxed Applications.

A MicroEJ Standalone Application is a MicroEJ Application that is
directly linked to the C code to produce a MicroEJ Firmware. Such
application must define a main entry point, i.e. a class containing a
``public static void main(String[])`` method. MicroEJ Standalone
Applications are developed using MicroEJ SDK.

A MicroEJ Sandboxed Application is a MicroEJ Application that can run
over a Multi-Sandbox Firmware. It can be linked either statically or
dynamically. If it is statically linked, it is then called a System
Application as it is part of the initial image and cannot be removed.
MicroEJ Sandboxed Applications are developed using MicroEJ Studio.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
