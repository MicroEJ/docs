===========================
Heap Dumper & Heap Analyzer
===========================


Principle
=========

The heap is a memory area used to hold Java objects created at runtime.
Objects persist in the heap until they are garbage-collected. An object
becomes eligible for garbage collection when there are no longer any
references to it from other objects.

Heap Dumper is a tool that takes a snapshot of the heap. Generated files
(with the ``.heap`` extension) are available on the application output
folder. Note that it works only on simulations.

For its part, the Heap Analyzer plug-in is able to open dump files. It
helps you analyze their contents thanks to the following features:

-  memory leaks detection

-  objects instances browse

-  heap usage optimization (using immortal or immutable objects)


Dependencies
============

No dependency.


Installation
============

This tool is a built-in platform tool.


Use
===

When the Heap Dumper option is activated, the garbage collector process
ends by performing a dump file that represent a snapshot of the heap at
this moment. Thus, to generate such dump files, you must explicitly call
the System.gc() method in your code, or wait long enough for garbage
collector activation.

The heap dump file contains the list of all instances of both class and
array types that exist in the heap. For each instance it records:

-  the time at which the instance was created

-  the thread that created it

-  the method that created it

For instances of class types, it also records:

-  the class

-  the values in the instance’s non-static fields

For instances of array types, it also records:

-  the type of the contents of the array

-  the contents of the array

For each referenced class type, it records the values in the static
fields of the class.

For more information about using the Heap Analyzer plug-in, please refer
to the menu ``Help > Help Contents > Heap Analyzer User Guide``.
