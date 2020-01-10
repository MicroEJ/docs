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
