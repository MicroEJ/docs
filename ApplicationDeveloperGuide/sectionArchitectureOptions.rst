Category: Runtime
=================


.. figure:: images/architecture_options/img1.png
   :scale: 100%
   :align: center

Group: Types
------------

Option(checkbox): Embed all type names
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


*Option Name*: ``soar.generate.classnames``

*Default value*: ``true``

*Description*:

Embed the name of all types. When this option is disabled, only names of
declared required types are embedded.

.. _enable_group_methods:

Option(checkbox): Group Methods by Type
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``com.microej.soar.groupMethodsByType.enabled``

*Default value*: ``false``

*Description*:

Group all embedded methods of a Java type in single ELF section in ``microejapp.o``. 
This avoids to reach the following SOAR error while building a large application and the maximum number of ELF sections (65536) is reached.

.. code-block:: console

   1 : ELF ERROR
      [M1] - Invalid value for U2 field. Overflow detected when writing 102092.


.. warning::
   
   This option affects the application code size (especially inline methods are embedded even if they are not used).

Group: Assertions
-----------------

.. _enable_assertions_sim:

Option(checkbox): Execute assertions on Simulator
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``core.assertions.sim.enabled``

*Default value*: ``false``

*Description*:

When this option is enabled, ``assert`` statements are executed. Please note
that the executed code may produce side effects or throw
``java.lang.AssertionError``.

.. _enable_assertions_emb:

Option(checkbox): Execute assertions on Device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``core.assertions.emb.enabled``

*Default value*: ``false``

*Description*:

When this option is enabled, ``assert`` statements are executed. Please note
that the executed code may produce side effects or throw
``java.lang.AssertionError``.

.. _architecture_options_group_trace:

Group: Trace
------------

Option(checkbox): Enable execution traces
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``core.trace.enabled``

*Default value*: ``false``

Option(checkbox): Start execution traces automatically
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``core.trace.autostart``

*Default value*: ``false``

Category: Memory
----------------


.. figure:: images/architecture_options/img2.png
   :scale: 100%
   :align: center

Group: Heaps
^^^^^^^^^^^^

.. _option_managed_heap:

Option(text): Managed heap size (in bytes)
""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.javaheap.size``

*Default value*: ``65536``

*Description*:

Specifies the Managed heap size in bytes.

A Managed heap contains live objects. An OutOfMemory error can occur if the
heap is too small.

.. _option_immortal_heap:

Option(text): Immortal heap size (in bytes)
"""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.immortal.size``

*Default value*: ``4096``

*Description*:

Specifies the Immortal heap size in bytes.

The Immortal heap contains allocated Immortal objects. An OutOfMemory error can
occur if the heap is too small.

Group: Threads
^^^^^^^^^^^^^^

*Description*:

This group allows the configuration of application and library thread(s).
See :ref:`runtime_threads_and_stacks` section for more details.

.. _option_number_of_threads:

Option(text): Number of threads
"""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.threads.size``

*Default value*: ``5``

*Description*:

Specifies the number of threads the application will be able to use at the same
time.

.. _option_number_of_stack_blocks:

Option(text): Number of blocks in pool
""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.threads.pool.size``

*Default value*: ``15``

*Description*:

Specifies the number of blocks in the stacks pool.

.. _option_stack_block_size:

Option(text): Block size (in bytes)
"""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.thread.block.size``

*Default value*: ``512``

*Description*:

Specifies the thread stack block size (in bytes).

.. _option_maximum_number_of_stack_blocks_per_thread:

Option(text): Maximum size of thread stack (in blocks)
""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.thread.max.size``

*Default value*: ``4``

*Description*:

Specifies the maximum number of blocks a thread can use. If a thread requires
more blocks a StackOverflow error will occur.

Category: Simulator
===================


.. figure:: images/architecture_options/img3.png
   :scale: 100%
   :align: center

Group: Options
--------------

*Description*:

This group specifies options for MicroEJ Simulator.

Option(checkbox): Use target characteristics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``s3.board.compliant``

*Default value*: ``false``

*Description*:

When selected, this option forces the MicroEJ Simulator to use the MicroEJ
Platform exact characteristics. It sets the MicroEJ Simulator scheduling policy
according to the MicroEJ Platform one. It forces resources to be explicitly
specified. It enables log trace and gives information about the RAM memory size
the MicroEJ Platform uses.

Option(text): Slowing factor (0 means disabled)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``s3.slow``

*Default value*: ``0``

*Description*:




*Format:* Positive ``integer``


This option allows the MicroEJ Simulator to be slowed down in order to match
the MicroEJ Platform execution speed. The greater the slowing factor, the
slower the MicroEJ Simulator runs.

Group: HIL Connection
---------------------

*Description*:

This group enables the control of HIL (Hardware In the Loop) connection
parameters (connection between MicroEJ Simulator and the Mocks).

Option(checkbox): Specify a port
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``s3.hil.use.port``

*Default value*: ``false``

*Description*:

When selected allows the use of a specific HIL connection port, otherwise a
random free port is used.

Option(text): Port
^^^^^^^^^^^^^^^^^^

*Option Name*: ``s3.hil.port``

*Default value*: ``8001``

*Description*:


*Format:* Positive ``integer``


*Values:* [1024-65535]


It specifies the port used by the MicroEJ Simulator to accept HIL connections.

Option(text): Timeout (s)
^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``s3.hil.timeout``

*Default value*: ``10``

*Description*:


*Format:* Positive ``integer``


It specifies the time the MicroEJ Simulator should wait before failing when
it invokes native methods.

.. _option_hil_maximum_frame_size:

Option(text): Maximum frame size (bytes)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``com.microej.simulator.hil.frame.size``

*Default value*: ``262144``

*Description*:

Maximum frame size in bytes. Must be increased to transfer large arrays to
native side.

Group: Shielded Plug server configuration
-----------------------------------------

*Description*:

This group allows configuration of the Shielded Plug database.

Option(text): Server socket port
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``sp.server.port``

*Default value*: ``10082``

*Description*:

Set the Shielded Plug server socket port.

.. include:: sectionSimulatorOptions.rst

.. _category.code.coverage:

Category: Code Coverage
-----------------------


.. figure:: images/architecture_options/img4.png
   :scale: 100%
   :align: center

Group: Code Coverage
^^^^^^^^^^^^^^^^^^^^

*Description*:

This group is used to set parameters of the code coverage analysis tool.

Option(checkbox): Activate code coverage analysis
"""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``s3.cc.activated``

*Default value*: ``false``

*Description*:

When selected it enables the code coverage analysis by the MicroEJ Simulator.
Resulting files are output in the cc directory inside the output directory.
You can process these files to an HTML report afterward with the built-in :ref:`Code Coverage Analyzer <code_coverage_analyzer>` .

Option(text): Saving coverage information period (in sec.)
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``s3.cc.thread.period``

*Default value*: ``15``

*Description*:

It specifies the period between the generation of .cc files.

Category: Debug
---------------


.. figure:: images/architecture_options/img5.png
   :scale: 100%
   :align: center

.. _simulator-remote-debug-options:

Group: Remote Debug
^^^^^^^^^^^^^^^^^^^

Option(text): Debug port
""""""""""""""""""""""""

*Option Name*: ``debug.port``

*Default value*: ``12000``

*Description*:

Configures the JDWP debug port.


*Format:* Positive ``integer``


*Values:* [1024-65535]




Category: Heap Dumper
---------------------


.. figure:: images/architecture_options/img6.png
   :scale: 100%
   :align: center

Group: Heap Inspection
^^^^^^^^^^^^^^^^^^^^^^

*Description*:

This group is used to specify heap inspection properties.

Option(checkbox): Activate heap dumper
""""""""""""""""""""""""""""""""""""""

*Option Name*: ``s3.inspect.heap``

*Default value*: ``false``

*Description*:

When selected, this option enables a dump of the heap each time the System.gc()
method is called by the MicroEJ Application.

Category: Logs
--------------


.. figure:: images/architecture_options/img7.png
   :scale: 100%
   :align: center

Group: Logs
^^^^^^^^^^^

*Description*:

This group defines parameters for MicroEJ Simulator log activity. Note that
logs can only be generated if the ``Simulator > Use target characteristics``
option is selected.

Some logs are sent when the Simulator executes some specific action (such as
start thread, start GC, etc), other logs are sent periodically (according to
defined log level and the log periodicity).

Option(checkbox): system
""""""""""""""""""""""""

*Option Name*: ``console.logs.level.low``

*Default value*: ``false``

*Description*:

When selected, System logs are sent when the Simulator executes the following
actions:


start and terminate a thread


start and terminate a GC


exit




Option(checkbox): thread
""""""""""""""""""""""""

*Option Name*: ``console.logs.level.thread``

*Default value*: ``false``

*Description*:

When selected, thread information is sent periodically. It gives information
about alive threads (status, memory allocation, stack size).

Option(checkbox): monitoring
""""""""""""""""""""""""""""

*Option Name*: ``console.logs.level.monitoring``

*Default value*: ``false``

*Description*:

When selected, thread monitoring logs are sent periodically. It gives
information about time execution of threads.

Option(checkbox): memory
""""""""""""""""""""""""

*Option Name*: ``console.logs.level.memory``

*Default value*: ``false``

*Description*:

When selected, memory allocation logs are sent periodically. This level
allows to supervise memory allocation.

Option(checkbox): schedule
""""""""""""""""""""""""""

*Option Name*: ``console.logs.level.schedule``

*Default value*: ``false``

*Description*:

When selected, a log is sent when the Simulator schedules a thread.

Option(checkbox): monitors
""""""""""""""""""""""""""

*Option Name*: ``console.logs.level.monitors``

*Default value*: ``false``

*Description*:

When selected, monitors information is sent periodically. This level permits
tracing of all thread state by tracing monitor operations.

Option(text): period (in sec.)
""""""""""""""""""""""""""""""

*Option Name*: ``console.logs.period``

*Default value*: ``2``

*Description*:


*Format:* Positive ``integer``


*Values:* [0-60]


Defines the periodicity of periodical logs.

Category: Mock
--------------


.. figure:: images/architecture_options/img8.png
   :scale: 100%
   :align: center

*Description*:

Specify Hardware In the Loop Mock client options

.. _option_mock_debug:

Group: Debug
^^^^^^^^^^^^

Option(checkbox): Enable Mock debug
"""""""""""""""""""""""""""""""""""

*Option Name*: ``com.microej.simulator.hil.debug.enabled``

*Default value*: ``false``

Option(text): Port
""""""""""""""""""

*Option Name*: ``com.microej.simulator.hil.debug.port``

*Default value*: ``8002``

Category: Kernel
----------------


.. figure:: images/architecture_options/img9.png
   :scale: 100%
   :align: center

Group: Kernel UID
^^^^^^^^^^^^^^^^^

Option(checkbox): Enable
""""""""""""""""""""""""

*Option Name*: ``com.microej.simulator.kf.kernel.uid.enabled``

*Default value*: ``false``

Option(text): UID
"""""""""""""""""

*Option Name*: ``com.microej.simulator.kf.kernel.uid``

*Default value*: ``(empty)``

Category: Libraries
===================


.. figure:: images/architecture_options/img10.png
   :scale: 100%
   :align: center

Category: EDC
-------------


.. figure:: images/architecture_options/img11.png
   :scale: 100%
   :align: center

Group: Java System.out
^^^^^^^^^^^^^^^^^^^^^^

Option(checkbox): Use a custom Java output stream
"""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.outputstream.disable.uart``

*Default value*: ``false``

*Description*:

Select this option to specify another Java ``System.out`` print stream.

If selected, the default Java output stream is not used by the Java
application. The Core Engine will not use the default Java output stream at startup.

Option(text): Class
"""""""""""""""""""

*Option Name*: ``core.outputstream.class``

*Default value*: ``(empty)``

*Description*:


*Format:* ``Java`` class like ``packageA.packageB.className``


Defines the Java class used to manage ``System.out``.

At startup the Core Engine will try to load this class using the ``Class.forName()``
method. If the given class is not available, it will use the default
Java output stream as usual. The specified class must be available in the
application classpath.

Group: Runtime options
^^^^^^^^^^^^^^^^^^^^^^

*Description*:

Specifies the additional classes to embed at runtime.

.. _option_embed_utf8:

Option(checkbox): Embed UTF-8 encoding
""""""""""""""""""""""""""""""""""""""

*Option Name*: ``cldc.encoding.utf8.included``

*Default value*: ``true``

*Description*:

Embed UTF-8 encoding.

.. _option_enable_security_manager:

Option(checkbox): Enable SecurityManager checks
"""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``com.microej.library.edc.securitymanager.enabled``

*Default value*: ``false``

*Description*:

Enable the security manager Permission checks.

Category: Shielded Plug
-----------------------


.. figure:: images/architecture_options/img12.png
   :scale: 100%
   :align: center

Group: Shielded Plug configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Description*:

Choose the database XML definition.

Option(browse): Database definition
"""""""""""""""""""""""""""""""""""

*Option Name*: ``sp.database.definition``

*Default value*: ``(empty)``

*Description*:

Choose the database XML definition.

Category: External Resources Loader
-----------------------------------


.. figure:: images/architecture_options/img13.png
   :scale: 100%
   :align: center

Group: External Resources Loader
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Description*:

This group allows to specify the external resources input folder. The content
of this folder will be copied in an application output folder and used by
SOAR and the Simulator. If empty, the default location will be [output
folder]/externalResources, where [output folder] is the location defined in
Execution tab.

Option(browse):
""""""""""""""""

*Option Name*: ``ej.externalResources.input.dir``

*Default value*: ``(empty)``

*Description*:

Browse to specify the external resources folder..

Category: Device
================


.. figure:: images/architecture_options/img14.png
   :scale: 100%
   :align: center

Category: Core Engine
---------------------


.. figure:: images/architecture_options/img15.png
   :scale: 100%
   :align: center

Group: Memory
^^^^^^^^^^^^^

.. _option_maximum_number_of_monitors_per_thread:

Option(text): Maximum number of monitors per thread
"""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.thread.max.nb.monitors``

*Default value*: ``8``

*Description*:

Specifies the maximum number of monitors a thread can own at the same time.

Option(text): Maximum number of frames dumpers on OutOfMemoryError
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``core.memory.oome.nb.frames``

*Default value*: ``1``

*Description*:

Specifies the maximum number of call frames that can be dumped to the standard
output when Core Engine throws an OutOfMemoryError.

.. _option_enable_heap_usage:

Option(checkbox): Enable Managed heap usage monitoring
""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``com.microej.runtime.debug.heap.monitoring.enabled``

*Default value*: ``false``

Option(text): Managed heap initial size
"""""""""""""""""""""""""""""""""""""""

*Option Name*: ``com.microej.runtime.debug.heap.monitoring.init.size``

*Default value*: ``0``

*Description*:

Specify the initial size (in bytes) of the Managed heap.

Group: SOAR
^^^^^^^^^^^

.. _option_enable_bytecode_verifier:

Option(checkbox): Enable Bytecode Verifier
""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``soar.bytecode.verifier``

*Default value*: Standalone Application: ``false``, Sandboxed Application: ``true``

*Description*:

Enables :ref:`soar_binary_code_verifier` during application build.

In the context of building a Standalone Application, the bytecode verifier is, by default, disabled to prioritize performance. In this case, the code is considered trusted.
Conversely, when building a Sandboxed Application, the bytecode verifier is automatically enabled by default. This is particularly important when dealing with untrusted third-party code.

.. _options_gc:

Group: Garbage Collector
^^^^^^^^^^^^^^^^^^^^^^^^

.. _option_gc_stack_size:

Option(text): GC mark stack size
""""""""""""""""""""""""""""""""

*Option Name*: ``com.microej.runtime.core.gc.markstack.levels.max``

*Default value*: ``32``

*Description*:

Indicates the quantity of items in the :ref:`Garbage Collector <runtime_gc>`'s mark stack.
The mark stack is used by the Garbage Collector for identifying live objects within the heap through a depth-first search approach.
Once the mark stack reaches its capacity, the Garbage Collector proceeds to inspect heap memory,
which may slow down garbage collection performance.

You can receive a notification when the mark stack limit is reached by implementing the following hook:

.. code-block:: c

   void LLMJVM_on_GC_MarkStackOverflow_reached(void) {
      // When entering here, the GC mark stack is undersized, which may affect GC performance.
      // It is recommended to either increase the GC mark stack size or reduce the object graph depth.
   }

Category: Kernel
^^^^^^^^^^^^^^^^


.. figure:: images/architecture_options/img16.png
   :scale: 100%
   :align: center

Group: Threads
""""""""""""""

Option(text): Maximum number of threads per Feature
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``core.memory.feature.max.threads``

*Default value*: ``5``

*Description*:

Specifies the maximum number of threads a Feature is allowed to use at the same
time.

.. _option_feature_stop_timeout:

Option(text): Feature stop timeout
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``com.microej.runtime.kf.waitstop.delay``

*Default value*: ``2000``

*Description*:

Specifies the maximum time allowed for the `FeatureEntryPoint.stop()`_ method to return (value in milliseconds).

.. _FeatureEntryPoint.stop(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/FeatureEntryPoint.html#stop--

Group: Features Installation
""""""""""""""""""""""""""""

.. _option_maximum_number_of_dynamic_features:

Option(text): Maximum number of installed Features
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``com.microej.runtime.kernel.dynamicfeatures.max``

*Default value*: ``16``

*Description*:

Specifies the maximum number of Features that can be installed to
this Kernel (see `Kernel.install()`_ method).

.. _Kernel.install(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream-

Option(text): Code chunk size
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``com.microej.soar.kernel.featurecodechunk.size``

*Default value*: ``65536``

*Description*:

Specifies the size in bytes of the code chunk in RAM. See :ref:`feature_code_chunk_size` section for more details.

Option(text): InputStream transfer buffer size
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``com.microej.runtime.kf.link.transferbuffer.size``

*Default value*: ``512``

*Description*:

Specifies the size in bytes of the temporary byte array for reading in the Feature InputStream. See :ref:`inputstream_transfer_buffer_size` section for more details.

Option(text): Maximum number of relocations applied simultaneously
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``com.microej.runtime.kf.link.chunk.relocations.count``

*Default value*: ``128``

Group: Feature Portability Control
""""""""""""""""""""""""""""""""""

Option(checkbox): Enable Feature Portability Control
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*: ``com.microej.soar.kernel.featureportabilitycontrol.enabled``

*Default value*: ``false``

Option(browse): Kernel Metadata File
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Option Name*:
``com.microej.soar.kernel.featureportabilitycontrol.metadata.path``

*Default value*: ``(empty)``

*Description*:

Specifies the path to the Kernel metadata file for Feature Portability Control.

Category: Watchdog
^^^^^^^^^^^^^^^^^^


.. figure:: images/architecture_options/img17.png
   :scale: 100%
   :align: center

Option(checkbox): Enable watchdog support
"""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``enable.watchdog.support``

*Default value*: ``true``

Group: Watchdog
"""""""""""""""

Option(text):
~~~~~~~~~~~~~~

*Option Name*: ``maximum.active.watchdogs``

*Default value*: ``4``

*Description*:

Specifies the maximum number of active watchdogs at the same time.

Category: Deploy
----------------


.. figure:: images/architecture_options/img18.png
   :scale: 100%
   :align: center

*Description*:

Configures the output locations where store the Application, the Architecture
libraries and Abstraction Layer header files.

See :ref:`Board Support Package (BSP) connection <bsp_connection_application_options>` chapter for more details.

Group: Configuration
^^^^^^^^^^^^^^^^^^^^

Option(checkbox): Deploy the Application (microejapp.o) at a location known by the 3rd-party BSP project.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``deploy.bsp.microejapp``

*Default value*: ``true``

*Description*:

Deploy the Application (microejapp.o) at a location known by the 3rd-party
BSP project.

Option(browse):
""""""""""""""""

*Option Name*: ``deploy.dir.microejapp``

*Default value*: ``(empty)``

*Description*:

Choose an output folder where to deploy the Application. An empty value means
no deployment (file is available in the Application output folder).

Option(checkbox): Deploy the Architecture library (microejruntime.a) at a location known by the 3rd-party BSP project.
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``deploy.bsp.microejlib``

*Default value*: ``true``

*Description*:

Deploy the Architecture library (microejruntime.a) at a location known by the
3rd-party BSP project.

Option(browse):
""""""""""""""""

*Option Name*: ``deploy.dir.microejlib``

*Default value*: ``(empty)``

*Description*:

Choose an output folder where to deploy the Architecture library. An empty
value means no deployment (file is available in the Application output folder).

Option(checkbox): Deploy the Abstraction Layer header files (``*.h``) at a location known by the 3rd-party BSP project.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``deploy.bsp.microejinc``

*Default value*: ``true``

*Description*:

Deploy the Abstraction Layer header files (``*.h``) at a location known by the
3rd-party BSP project.

Option(browse):
""""""""""""""""

*Option Name*: ``deploy.dir.microejinc``

*Default value*: ``(empty)``

*Description*:

Choose an output folder where to deploy the Architecture library. An empty
value means no deployment (file is available in the Application output folder).

Option(checkbox): Execute the MicroEJ build script (build.bat) at a location known by the 3rd-party BSP project.
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

*Option Name*: ``deploy.bsp.microejscript``

*Default value*: ``false``

*Description*:

Execute the MicroEJ build script (build.bat) at a location known by the
3rd-party BSP project.

Option(browse):
""""""""""""""""

*Option Name*: ``deploy.dir.microejscript``

*Default value*: ``(empty)``

*Description*:

Choose an output folder where is located the MicroEJ build script (build.bat)
to execute. An empty value means no execution.

Option(browse):
""""""""""""""""

*Option Name*: ``deploy.bsp.root.dir``

*Default value*: ``(empty)``

*Description*:

Choose an output folder where is located the 3rd-party BSP project. An empty
value means not set (3rd-party BSP project location may have been configured by
the VEE Port).

Category: Feature
=================


.. figure:: images/architecture_options/img19.png
   :scale: 100%
   :align: center

*Description*:

Specify Feature options

Group: Build
------------

Option(text): Output Name
^^^^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``feature.output.basename``

*Default value*: ``application``

Option(browse): Kernel
^^^^^^^^^^^^^^^^^^^^^^

*Option Name*: ``kernel.filename``

*Default value*: ``(empty)``


..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
