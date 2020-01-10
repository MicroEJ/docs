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
