.. _heap_usage_monitoring:

Heap Usage Monitoring
=====================

Introduction
------------

When building a :ref:`standalone_application`, the Managed Heap size must be specified
as an :ref:`Application Option <application_options>` (see :ref:`option_managed_heap`).
The value to set in this option depends on the maximum heap usage, and the 
developer can estimate it by running the application.

The Core Engine provides a Java API to introspect the heap usage at runtime. 
Additionally, heap usage monitoring can be enabled to compute the maximum heap 
usage automatically.

Here are the descriptions of the different notions related to heap usage:

-  **Heap:** memory area used to store the objects allocated by the application.

-  **Heap Size:** current size of the heap.

-  **Maximum Heap Size:** maximum size of the heap. The heap size cannot exceed 
   this value. See :ref:`option_managed_heap`.

-  **Heap Usage:** the amount of the heap currently being used to store alive 
   objects.

-  **Garbage Collector (GC):** a memory manager in charge of recycling unused 
   objects to increase free memory.

.. figure:: images/heap_usage.png
   :alt: Heap Structure Summary
   :align: center
   :scale: 50%

   Heap Structure Summary

The Java class `java.lang.Runtime`_ 
defines the following methods:

-  `Runtime.gc()`_: 
   Runs the garbage collector. This is a blocking operation that reclaims all unreachable objects and defragments the Managed Heap.
   `System.gc()`_ 
   is an alternative means of invoking this method.

-  `Runtime.freeMemory()`_: 
   Returns the amount of free memory in the heap. 
   Starting from :ref:`Architecture 8.6.0 <changelog-8.6.0>`, this method considers only live objects when computing free space. 
   Therefore invoking `System.gc()`_ or `Runtime.gc()`_ prior to calling this method is no longer necessary to obtain an accurate free memory value.

-  `Runtime.totalMemory()`_: 
   Returns the current size of the heap. 
   The value returned by this method may vary over time.

-  `Runtime.maxMemory()`_: 
   Returns the maximum size of the heap.

.. _java.lang.Runtime: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html
.. _Runtime.gc(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html#gc--
.. _System.gc(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#gc--
.. _Runtime.freeMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html#freeMemory--
.. _Runtime.totalMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html#totalMemory--
.. _Runtime.maxMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html#maxMemory--

Heap Usage Introspection
------------------------

The methods provided by the `Runtime`_ 
class allow introspecting the heap usage by comparing the heap size and the free memory size. 
A garbage collection must be executed before computing the heap usage to recycle 
all the unused objects and count only alive objects.

The application can compute the current heap usage by executing the following 
code:

.. tabs::

   .. tab:: Architecture 8.6.0 or higher

      .. code-block:: java
      
         Runtime runtime = Runtime.getRuntime(); // get Runtime instance
         long heapUsage = runtime.totalMemory() - runtime.freeMemory();

   .. tab:: Architecture lower than 8.6.0

      .. code-block:: java
      
         Runtime runtime = Runtime.getRuntime(); // get Runtime instance
         runtime.gc(); // Ensure unused objects are recycled
         long heapUsage = runtime.totalMemory() - runtime.freeMemory();

This example gives the heap usage at a given point but not the maximum heap 
usage of the application.

.. note::
   When heap usage monitoring is disabled, the heap size is fixed, and so 
   `Runtime.totalMemory()`_ 
   and `Runtime.maxMemory()`_ 
   return the same value.

.. _Runtime: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html

Automatic Heap Usage Monitoring
-------------------------------

The maximum heap usage of an application's execution can be computed 
automatically by enabling heap usage monitoring.

.. note::
   This feature is available in the Architecture versions 7.16.0 or higher for the Applications deployed on hardware devices (not on Simulator).

When this option is activated, an initial size for the heap must be specified, 
and the Core Engine increases the heap size dynamically. 
The value returned by `Runtime.totalMemory()`_ 
is the current heap size. 
`Runtime.maxMemory()`_ 
returns the maximum size of the heap. 
A call to `Runtime.gc()`_ 
decreases the heap size to the higher value of either the heap usage or the 
initial heap size.

At any moment, `Runtime.totalMemory()`_ 
returns the maximum heap usage of the current execution (assuming the maximum 
heap usage is higher than the initial heap size, and 
`Runtime.gc()`_ 
has not been called).

See the section :ref:`option_enable_heap_usage` to enable this option and 
configure the initial heap size.

Even if the heap size can vary during time, a memory section of 
`Runtime.maxMemory()`_ 
bytes is allocated at link time or during the Core Engine startup. 
No dynamic allocation is performed when increasing the heap size.

.. warning::
   A small initial heap size will impact the performances as the GC will be 
   executed every time the heap size needs to be increased. 
   
   Furthermore, the smaller the heap size is, the more frequent the GC will 
   occur. 
   This feature should be used only for heap usage benchmarking.

Heap Usage Analysis
-------------------

To analyze heap usage and see what objects are alive in the application, use the
Heap Dumper & Heap Analyzer tools (:ref:`on SDK 6<sdk6_heapdumper>`, :ref:`on SDK 5<heapdumper>`).

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
