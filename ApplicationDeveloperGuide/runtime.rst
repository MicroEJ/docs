MicroEJ Runtime
===============

.. _mjvm_javalanguage:

Language
--------

MicroEJ is compatible with the Java language version 7.

Java source code is compiled by the Java compiler [1]_ into the binary format specified in the JVM specification [2]_. 
This binary code needs to be linked before execution: .class files and some other application-related files (see :ref:`MicroEJ Classpath <chapter.microej.classpath>`) are compiled to produce the final application that the MicroEJ Runtime can execute.

MicroEJ complies with the deterministic class initialization (<clinit>) order specified in :ref:`[BON] <runtime_bon>`. The application is statically analyzed from its entry points in order to generate a clinit dependency graph. The computed clinit sequence is the result of the topological sort of the dependency graph. An error is thrown if the clinit dependency graph contains cycles.

.. [1]
   The JDT compiler from the Eclipse IDE.

.. [2]
   Tim Lindholm & Frank Yellin, The Java™ Virtual Machine Specification, Second Edition, 1999

Scheduler
---------

The Architecture features a green thread platform that can
interact with the C world :ref:`[SNI] <runtime_sni>`. The (green) thread policy is as
follows:

-  preemptive for different priorities,

-  round-robin for same priorities,

-  "priority inheritance protocol" when priority inversion occurs. [3]_

MicroEJ stacks (associated with the threads) automatically adapt their
sizes according to the thread requirements: Once the thread has
finished, its associated stack is reclaimed, freeing the corresponding
RAM memory.

.. [3]
   This protocol raises the priority of a thread (that is holding a
   resource needed by a higher priority task) to the priority of that
   task.

Garbage Collector
-----------------

The Architecture includes a state-of-the-art memory management
system, the Garbage Collector (GC). It manages a bounded piece of RAM
memory, devoted to the Java world. The GC automatically frees dead Java
objects, and defragments the memory in order to optimize RAM usage. This
is done transparently while the MicroEJ Applications keep running.

.. _runtime_core_libraries:

Core Libraries
--------------

This section describes the core libraries which make up the runtime.
Theses Foundation Libraries are tightly coupled with the Core Engine.

.. _runtime_edc:

Embedded Device Configuration (EDC)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Embedded Device Configuration specification defines the minimal
standard runtime environment for embedded devices. It defines all
default API packages:

-  java.io
-  java.lang
-  java.lang.annotation
-  java.lang.ref
-  java.lang.reflect
-  java.util

.. list-table::
   :widths: 10 30

   * - **Documentation**
     - **Link**
   * - Java APIs
     - https://repository.microej.com/javadoc/microej_5.x/libraries/edc-1.3-api/
   * - Module
     - https://repository.microej.com/modules/ej/api/edc/


.. _runtime_bon:

Beyond Profile (BON)
~~~~~~~~~~~~~~~~~~~~~

This profile defines a suitable and flexible way to fully control both memory
usage and start-up sequences on devices with limited memory resources.
It does so within the boundaries of Java semantics. More precisely, it
allows:

-  Controlling the initialization sequence in a deterministic way.

-  Defining persistent, immutable, read-only objects (that may be placed
   into non-volatile memory areas), and which do not require copies to
   be made in RAM to be manipulated.

-  Defining immortal, read-write objects that are always alive.

- Defining and accessing compile-time constants.

.. list-table::
   :widths: 10 30

   * - **Documentation**
     - **Link**
   * - Java APIs
     - https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/package-summary.html
   * - Specification
     - http://e-s-r.net/download/specification/ESR-SPE-0001-BON-1.2-F.pdf
   * - Module
     - https://repository.microej.com/modules/ej/api/bon/
 

.. _runtime_sni:

Simple Native Interface (SNI)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SNI provides a simple mechanism for implementing native Java methods in the C language.

SNI allows you to:

-  Call a C function from a Java method.
-  Access an Immortal array in a C function (see the :ref:`runtime_bon` to learn about immortal objects).

SNI does not allow you to:

-  Access or create a Java object in a C function (except byte arrays).
-  Access Java static variables in a C function.
-  Call Java methods from a C function.

SNI also provides some Java APIs to manipulate some data arrays between Java and the native (C) world.

.. list-table::
   :widths: 10 30

   * - **Documentation**
     - **Link**
   * - Java APIs
     - https://repository.microej.com/javadoc/microej_5.x/apis/ej/sni/package-summary.html
   * - Specification
     - http://e-s-r.net/download/specification/ESR-SPE-0012-SNI_GT-1.2-H.pdf
   * - Module
     - https://repository.microej.com/modules/ej/api/sni/

Please refer to :ref:`sni` section for more details.

.. _runtime_kf:

Kernel & Features (KF)
~~~~~~~~~~~~~~~~~~~~~~

The Kernel & Features semantic (KF) extends the runtime for managing Multi-Sandboxed Applications.

Please refer to the :ref:`kf_specification` for more details, the :ref:`Multi-Sandbox capability <multisandbox>` of the Core Engine
and more generally the :ref:`kernel-developer-guide` chapter.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
