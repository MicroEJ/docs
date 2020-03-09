.. _Standalone_vs_Sandboxed:

Introduction
============

Application Development
=======================

The following sections of this document shall prove useful as a
reference when developing applications for MicroEJ. They cover concepts
essential to MicroEJ applications design.

In addition to these sections, by going to
:http:`https://developer.microej.com/`, you can access a number of helpful
resources such as:

-  Libraries from the MicroEJ Central Repository
   (:http:`https://repository.microej.com/`);

-  Application Examples as source code from MicroEJ Github Repositories
   (:http:`https://github.com/MicroEJ`);

-  Documentation (HOWTOs, Reference Manuals, APIs javadoc...).

Two kinds of applications can be developed on MicroEJ: MicroEJ
Standalone Applications and MicroEJ Sanboxed Applications.

A MicroEJ Standalone Application is a MicroEJ application that is
directly linked to the C code to produce a MicroEJ Firmware. Such
application must define a main entry point, i.e. a class containing a
``public static void main(String[])`` method. MicroEJ Standalone
Applications are developed using MicroEJ SDK.

A MicroEJ Sandboxed Application is a MicroEJ application that can run
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
