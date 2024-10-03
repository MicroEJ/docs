MicroEJ Runtime
===============

.. _mjvm_javalanguage:

Language
--------

MicroEJ allows to develop Applications in the `Java® Language Specification version 7 <https://docs.oracle.com/javase/specs/jls/se7/jls7.pdf>`_ with :ref:`some limitations <java_limitations>`, and supports code extensions written in :ref:`JavaScript <javascript>`.

Basically, Java source code is compiled by the Java compiler [1]_ into the binary format specified in the JVM specification [2]_. 
This binary code is linked by a tool named :ref:`SOAR <soar>` before execution: ``.class`` files and some other application-related files (see :ref:`Classpath <chapter.microej.classpath>` chapter) are linked to produce the final binary file that the :ref:`Core Engine <core_engine>` will execute.

.. note:: When opened in the SDK 5, make sure that the Compiler Compliance Level of your project is set to 1.7 to ensure the bytecode produced by the Java compiler is compatible with MicroEJ. The Compliance Level can be changed from the menu: :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Java` > :guilabel:`Compiler`.

.. [1]
   The JDT compiler from the Eclipse IDE.

.. [2]
   Tim Lindholm & Frank Yellin, The Java™ Virtual Machine Specification, Second Edition, 1999

.. _runtime_core_libraries:

Core Libraries
--------------

This section describes the core libraries which make up the runtime.
Theses Foundation Libraries are tightly coupled with the Core Engine.

.. _runtime_edc:

Embedded Device Configuration (EDC)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Embedded Device Configuration specification defines the minimal
standard runtime environment for embedded devices. 

This module is always required in the build path of an Application project; 
and all others libraries depend on it. This library provides a set of options.
Refer to the chapter :ref:`application_options` which lists all available options.

**Specification Summary:**

.. include:: edc_spec_summary.rst

.. _runtime_bon:

Beyond Profile (BON)
~~~~~~~~~~~~~~~~~~~~~

This profile defines a suitable and flexible approach to fully control both memory usage 
and startup sequences on devices with limited memory resources, while remaining within the boundaries of Java semantics.

More precisely, it allows:

-  Controlling the initialization sequence in a deterministic way.

-  Defining persistent, immutable, read-only objects (that may be placed
   into non-volatile memory areas), and which do not require copies to
   be made in RAM to be manipulated.

-  Defining immortal, read-write objects that are always alive.

-  Accessing compile-time :ref:`constants <section.classpath.elements.constants>`.

Read the :ref:`Beyond Profile specification <bon_specification>` for more details.

**Specification Summary:**

.. include:: bon_spec_summary.rst

.. _runtime_sni:

Simple Native Interface (SNI)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SNI provides a simple mechanism for implementing native Java methods in the C language.

SNI allows you to:

-  Call a C function from a Java method.
-  Access an Immortal array in a C function (see the :ref:`runtime_bon` to learn about immortal objects).

SNI also provides some Java APIs to manipulate some data arrays between Java and the native (C) world.

Read the :ref:`Simple Native Interface specification <sni_specification>` for more details.

**Specification Summary:**

.. include:: sni_spec_summary.rst

.. _runtime_kf:

Kernel & Features (KF)
~~~~~~~~~~~~~~~~~~~~~~

The Kernel & Features semantic (KF) extends the runtime for managing Multi-Sandboxed Applications.

Read the :ref:`Kernel & Features specification <kf_specification>` for more details, the :ref:`Multi-Sandbox capability <multisandbox>` of the Core Engine
and more generally the :ref:`kernel-developer-guide` chapter.

**Specification Summary:**

.. include:: kf_spec_summary.rst

Specifications
~~~~~~~~~~~~~~

.. toctree::
   :maxdepth: 1
   
   bon
   ../VEEPortingGuide/sni
   ../KernelDeveloperGuide/kf

.. _runtime_gt: 

Scheduler
---------

The Core Engine features a `Green Threads model <https://en.wikipedia.org/wiki/Green_threads>`_. The semantic is as follows:

-  preemptive for different priorities,
-  round-robin for same priorities,
-  "priority inheritance protocol" when priority inversion occurs. [3]_

Threads stacks automatically adapt their sizes according to the thread requirements: once a thread terminates,
its associated stack is reclaimed, freeing the corresponding RAM memory.


.. [3]

	This protocol raises the priority of a thread that is holding a monitor needed by a higher-priority thread,
	to the priority of that higher-priority thread (until exiting the monitor).

.. _runtime_gc: 

Garbage Collector
-----------------

The Core Engine includes a state-of-the-art memory management
system, the Garbage Collector (GC). It manages a bounded piece of RAM
memory, devoted to the Java world. The GC automatically frees dead Java
objects, and defragments the memory in order to optimize RAM usage. This
is done transparently while the Application keep running.

See also :ref:`Garbage Collector options <options_gc>` for more details.

Death Notification
~~~~~~~~~~~~~~~~~~

Most objects are reclaimable objects. Sometimes, they interact with the
native or system resources using handles. Those handles represent underlying data
that needs to be closed/freed/acknowledged/… when the object that holds
the handle dies.

The Application can get notified when an object is dead through the use of `WeakReference`_ objects. 
When such objects get their weak reference set to ``null`` by the system, they are
added to the `ReferenceQueue`_ they were assigned to at their creation.

Death Notification Actions
~~~~~~~~~~~~~~~~~~~~~~~~~~

Once an object has expired, it cannot be brought to life again. It is
the responsibility of the application to make provisions for all actions
that have to be taken on an object death. Such provisions are
materialized by subclasses of the `WeakReference`_ class.

`ReferenceQueue.poll()`_ and `ReferenceQueue.remove()`_ methods allow the
execution of a hook at the death of the object referenced by the weak
reference. The first one returns ``null`` when queue is empty whereas the
second one blocks while the queue is empty.

The Application is responsible of the execution of such hook.

.. _java_limitations:

Limitations
-----------

Primitive Types
~~~~~~~~~~~~~~~

Getting a Class instance of a primitive type is not supported:

- ``boolean.class``,
- ``byte.class``,
- ``char.class``,
- ``short.class``,
- ``int.class``,
- ``long.class``,
- ``float.class``,
- ``double.class``.

On Architecture ``8.x``, you will get the following dedicated error message:

.. code-block::

    SOAR-L ERROR :
    [M79] - Unsupported access to the Class instance of a primitive type (found 'boolean.class' in method 'com.mycompany.MyClass.myMethod()void')

On Architecture ``7.x`` you will get the following default error message:

.. code-block::

    No such field TYPE at com/mycompany/MyClass.myMethod()V.


.. _architecture_characteristics:

Architecture Characteristics
----------------------------

The Application can retrieve some characteristics of the Architecture on which it is running.
Architecture characteristics are automatically provided as :ref:`constants <section.classpath.elements.constants>`. Here are the most notable ones:

-  ``com.microej.architecture.capability=[tiny|single|multi]``: :ref:`Core Engine Capability <core_engine_capabilities>`
-  ``com.microej.architecture.name=[architecture_uid]``: Architecture name.
-  ``com.microej.architecture.level=[eval|prod]``: Usage level (Evaluation or Production).
-  ``com.microej.architecture.toolchain=[toolchain_uid]``: Toolchain name.
-  ``com.microej.architecture.version=[M.m.p]``: Architecture version.

See also :ref:`Architecture Naming Convention <architecture_naming_convention>` for more details.

The following code prints the formatted Architecture characteristics on standard output. You can copy-paste and adapt it to your needs.

.. code-block:: java
      
      String name = Constants.getString("com.microej.architecture.name");
      String version = Constants.getString("com.microej.architecture.version");
      String buildLabel = Constants.getString("com.microej.architecture.buildLabel");

      String usage = Constants.getString("com.microej.architecture.level");
      String usageStr;
      if (usage.equals("prod") || usage.equals("dev")) {
      	usageStr = "Production";
      } else if (usage.equals("eval")) {
      	usageStr = "Evaluation";
      } else {
      	usageStr = usage;
      }

      String capability = Constants.getString("com.microej.architecture.capability");
      String capabilityStr;
      if (capability.equals("multi")) {
      	capabilityStr = "Multi";
      } else if (capability.equals("tiny")) {
      	capabilityStr = "Tiny";
      } else if (capability.equals("single") || capability.equals("mono")) {
      	capabilityStr = "Mono";
      } else {
      	capabilityStr = capability;
      }

      String isaStr = Constants.getString("com.microej.architecture.architecturePrintableName");
      String toolchainName = Constants.getString("com.microej.architecture.toolchainPrintableName");
      String toolchainFullName = Constants.getString("com.microej.architecture.toolchain");

      System.out.println("- Name:                         " + name);
      System.out.println("- Version:                      " + version + " (" + buildLabel + ")");
      System.out.println("- Usage:                        " + usageStr);
      System.out.println("- Core Engine Capability:       " + capabilityStr + "-Sandbox");
      System.out.println("- Instruction Set Architecture: " + isaStr);
      System.out.println("- Compilation Toolchain:        " + toolchainName + " (" + toolchainFullName + ")");

.. _WeakReference: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ref/WeakReference.html
.. _ReferenceQueue: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ref/ReferenceQueue.html
.. _ReferenceQueue.poll(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ref/ReferenceQueue.html#poll--
.. _ReferenceQueue.remove(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ref/ReferenceQueue.html#remove--

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
