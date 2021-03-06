.. _architecture_changelog:

MicroEJ Architectures Changelog
===============================

Notation
--------

A line prefixed by ``[]`` describes a change that only applies on a
specific configuration:
``[Core Engine Capability/Instruction Set/C Compiler]``:

-  Core Engine Capability

   -  ``Single``: Single Application (default)
   -  ``Tiny``: Tiny Application
   -  ``Multi``: Multi Applications

-  Instruction Set

   -  ``ARM9``: ARM ARM9
   -  ``Cortex-A``: ARM Cortex-A
   -  ``Cortex-M``: ARM Cortex-M
   -  ``ESP32``: Espressif ESP32
   -  ``RX``: Renesas RX
   -  ``x86``: Intel x86

-  C Compiler

   -  ``ARMCC5``: Keil ARMCC uVision v5
   -  ``IAR74``: IAR Embedded Workbench for ARM v7.4
   -  ``QNX65``: BlackBerry QNX 6.5
   -  ``QNX70``: BlackBerry QNX 7.0

[7.16.0] - 2021-06-24
---------------------

Notes
~~~~~

The ``Device`` module provided by the MicroEJ Architecture is deprecated
and will be removed in a future version. It has been moved to the
`Device Pack <https://repository.microej.com/modules/com/microej/pack/device/device-pack/>`_. Please update your Platforms.

Core Engine
~~~~~~~~~~~

-  Added a dedicated error code ``LLMJVM_E_INITIALIZE_ERROR (-23)`` when
   ``LLMJVM_IMPL_initialize()``, ``LLMJVM_IMPL_vmTaskStarted()``, or
   ``LLMJVM_IMPL_shutdown()`` fails. Previously the generic error code
   ``LLMJVM_E_MAIN_THREAD_ALLOC (-5)`` was returned.
-  Added automatic heap consumption monitoring when option ``com.microej.runtime.debug.heap.monitoring.enabled`` is set to ``true``
-  Fixed some parts of ``LLMJVM_checkIntegrity()`` code were embedded even if not called
-  [Multi] Fixed potential crash during the call of
   ``LLMJVM_checkIntegrity`` when analyzing a corrupted Java stack (make
   this function robust to object references with an invalid memory
   address)

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Added source code for ``KF``, ``SCHEDCONTROL``, ``SNI``, ``SP`` implementations
-  Updated ``KF`` API with annotations for Null analysis
-  Updated ``SNI`` API with annotations for Null analysis
-  Updated ``SP`` API with annotations for Null analysis
-  Updated ``ResourceManager`` implementation with annotations for Null analysis
-  Updated ``KF`` implementation:
  
   -  Added missing ``Kernel.getAllFeatureStateListeners()`` method
   -  Updated code for correct Null analysis detection
   -  Fixed ``Feature.getCriticality()`` to throw
      ``IllegalStateException`` if it is in state ``UNINSTALLED``
      (instead of returning ``NORM_CRITICALITY``)
   -  Fixed potential race condition between
      ``Kernel.addResourceControlListener()`` and
      ``Kernel.removeResourceControlListener()``. Adding a new listener
      may not register it if another one is removed at the same time.

Integration
~~~~~~~~~~~

-  Added a new task in ELF Utils library allowing to update the content of an ELF section:
   
   -  Declaration:
      
      .. code-block:: xml
        
         <taskdef classpath="${platform.dir}/tools/elfutils.jar" classname="com.is2t.elf.utils.AddSectionTask" name="addSection" />
   -  Usage: 
      
      .. code-block:: xml
         
         <addSection file="${executable.file}" sectionFile="${section.file}" sectionName="${section.name}" sectionAlignment="${section.alignment}" outputDir="${output.dir}" outputName="${output.name}" />
-  Updated Architecture End User License Agreement to version ``SDK 3.0-C``
-  Updated copyright notice of Low Level APIs header files to latest MicroEJ SDK default license
-  Updated Architecture module with required files and configurations for correct publication in a module repository (``README.md``,
   ``LICENSE.txt``, and ``CHANGELOG.md``)

Simulator
~~~~~~~~~

-  Added an option (``com.microej.simulator.hil.frame.size``) to
   configure the HIL engine max frame size
-  Fixed load of an immutable byte field (sign extension)
-  Fixed ``java.lang.String`` constructors ``String(byte[] bytes, ...)`` when passing
   characters in the range ``[0x80,0xFF]`` using default ``ISO-8859-1`` encoding
-  Fixed potential crash in debug mode when a breakpoint is set on a
   field access (introduced in version ``7.13.0``)
-  Fixed wrong garbage collection of an object only referenced by an
   immortal object

SOAR
~~~~

-  Fixed the following compilation issues in ``if`` statement with BON constant:

   -  too many code may be removed when the block contains a ``while``
      loop
   -  potential ``Stacks merging coherence error`` may be thrown when the
      block contains a nested ``try-catch`` statement
   -  potential ``Stacks merging coherence error`` when declaring a
      ternary expression with ``Constants.getBoolean()`` in condition
      expression

-  Fixed ``assert`` statement removal when it is located at the end of a
   ``then`` block: the ``else`` block may be executed instead of jumping
   over
-  Removed names of arrays of basetype unless ``soar.generate.classnames`` option is set to ``true``
-  [Multi] Fixed potential link exception when a Feature use one of the
   ``ej_bon_ByteArray`` methods
   (e.g. ``ej.kf.InvalidFormatException: code=51:ON_ej_bon_ByteArray_method_readUnsignedByte_AB_I_I``)
-  [Multi] Fixed SOAR error (``Invalid SNI method``) when one of the
   ``ej.bon.Constants.getXXX()`` methods is declared in a ``kernel.api``
   file. This issue was preventing from using BON Constants in Feature
   code.

Tools
~~~~~

-  Updated Code Coverage Analyzer report generation:

   -  Automatically configure ``src/main/java`` source directory
      beside a ``/bin`` directory if available
   -  Added an option (``cc.src.folders``) to specify the source directory
      (require MicroEJ SDK ``5.4.1`` or higher)
   -  Removed the analysis of generated code for ``synchronized``
      statements
   -  Fixed crash when loading source code with annotations

-  Fixed Memory Map scripts: ``ClassNames`` group may contain duplicate
   sections with ``Types`` group
-  Fixed load of an ELF executable when a section overlaps a segment (updated ELF
   Utils, Kernel Packager and Firmware Linker)
-  Fixed Firmware Linker to generate output executable file at the same
   location than the input executable file
   
[7.15.1] - 2021-02-19
---------------------

SOAR
~~~~

-  [Multi] Fixed potential VM crash when declaring a Proxy class which
   is ``abstract``.

.. _section-1:

[7.15.0] - 2020-12-17
---------------------

Core Engine
~~~~~~~~~~~

-  Added support for applying Feature relocations

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``KF`` implementation to apply Feature relocations using the
   Core Engine. The former Java implementation is deprecated but can
   still be enabled using the option
   ``com.microej.runtime.kf.link.relocations.java.enabled``.

Integration
~~~~~~~~~~~

-  Updated the Architecture naming convention: the usage level is
   ``prod`` instead of ``dev`` .
-  Fixed generation of temporary properties file with a
   ``.properties.list`` extension instead of deprecated
   ``.system.properties`` extension.

.. _soar-1:

SOAR
~~~~

-  Fixed crash when declaring a clinit dependency rule on a class that
   is loaded but not embedded.

Tools
~~~~~

-  Fixed Memory Map Script ``All`` graph creation to prevent slow
   opening of large ``.map`` file in Memory Map Analyzer.

.. _section-2:

[7.14.1] - 2020-11-30
---------------------

.. _core-engine-1:

Core Engine
~~~~~~~~~~~

-  [Multi/x86/QNX7] Fixed missing multi-sandbox version

.. _tools-1:

Tools
~~~~~

-  Fixed categories for class names and SNI library in Memory Map
   Scripts

.. _section-3:

[7.14.0] - 2020-09-25
---------------------

Notes
~~~~~

The following set of Architecture properties are automatically provided
as ``BON`` constants:

-  ``com.microej.architecture.capability=[tiny|single|multi]``
-  ``com.microej.architecture.name=[architecture_uid]``
-  ``com.microej.architecture.level=[eval|prod]``
-  ``com.microej.architecture.toolchain=[toolchain_uid]``
-  ``com.microej.architecture.version=7.14.0``

The following set of Platform properties (customer defined) are
automatically provided as ``BON`` constants:

-  ``com.microej.platform.hardwarePartNumber``
-  ``com.microej.platform.name``
-  ``com.microej.platform.provider``
-  ``com.microej.platform.version``
-  ``com.microej.platform.buildLabel``

.. _foundation-libraries-1:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``EDC`` UTF-8 encoder to support Unicode code points as
   supplementary characters
-  Fixed ``java.lang.NullPointerException`` thrown when
   ``java.util.WeakHashMap.put()`` method is called with a ``null`` key
   (introduced in version :ref:`7.11.0 <changelog-7.11.0>`)

.. _integration-1:

Integration
~~~~~~~~~~~

-  Added all options starting with ``com.microej.`` prefix as ``BON``
   constants
-  Added all properties defined in ``architecture.properties`` as
   options prefixed by ``com.microej.architecture.``
-  Added all properties defined in ``release.properties`` as options
   prefixed by ``com.microej.platform.``
-  Added all properties defined in ``script/mjvm.properties`` as options
   prefixed by ``com.microej.architecture.``
-  Added an option
   (``com.microej.library.edc.supplementarycharacter.enabled``) to
   enable support for supplementary characters (enabled by default)
-  Updated Memory Map Scripts to extract Java static fields in a
   dedicated group named ``Statics``
-  Updated Memory Map Scripts to extract Java types in a dedicated group
   named ``Types``
-  Fixed generated Feature filename (unexpanded
   ``${feature.output.basename}`` variable, introduced in version
   :ref:`7.13.0 <changelog-7.13.0>`)
-  Fixed definition of missing default values for memory options (same
   values than launcher default ones)
-  [Tiny,Multi] - Added display of the Core Engine capability when
   launching SOAR

.. _soar-2:

SOAR
~~~~

-  [Multi] - Added a new attribute named ``api`` in Kernel ``soar.xml``
   file indicating which types, methods and static fields are exposed as
   Kernel APIs
-  [Multi] - Fixed potential link error when calling
   ``java.lang.Object.clone`` method on an array in Feature mode

.. _tools-2:

Tools
~~~~~

-  Updated serial PC connector to JSSC ``2.9.2`` (COM port could not be
   open on Windows 10 using a JRE ``8u261`` or higher)

.. _section-4:

[7.13.3] - 2020-09-18
---------------------

.. _core-engine-2:

Core Engine
~~~~~~~~~~~

-  [QNX70] - Embed method names and line numbers information in the
   application
-  [Cortex-A/QNX70] - Fixed wrong float/double arguments passed to the
   SNI natives (introduced in version :ref:`7.12.0 <changelog-7.12.0>`)

Simulator
~~~~~~~~~

-  Fixed unnecessary stacktrace dump on ``Long.parseLong()`` error
-  Fixed UTF-8 encoded Strings not correctly printed

.. _tools-3:

Tools
~~~~~

-  Updated Memory Map Scripts for ``ej.library.runtime.basictool``
   library

.. _section-5:

[7.13.2] - 2020-08-14
---------------------

.. _core-engine-3:

Core Engine
~~~~~~~~~~~

-  [ARM9/QNX65] - Fixed custom convention call
-  [x86/QNX70] - Fixed SIGFPE raised when overflow occurs on division
-  [x86/QNX70] - Fixed issue with NaN conversion to int or long

.. _tools-4:

Tools
~~~~~

-  Fixed Feature build script for MicroEJ SDK 5.x (introduced in version
   :ref:`7.13.0 <changelog-7.13.0>`)
-  Updated Memory Map Scripts for MicroUI 3 and Service libraries

.. _section-6:

[7.13.1] - 2020-07-20
---------------------

.. _core-engine-4:

Core Engine
~~~~~~~~~~~

-  [ESP32] - Fixed potential PSRAM access faults by rebuilding using
   `esp-idf v3.3.0
   toolchain <https://github.com/espressif/esp-idf/commit/ff29e3e7a24a715bc7f5ba453c83d694ba0ec1e2>`__
   (``simikou2``)

.. _changelog-7.13.0:

[7.13.0] - 2020-07-03
---------------------

.. _core-engine-5:

Core Engine
~~~~~~~~~~~

-  Added ``SNI-1.4`` support, with the following new ``LLSNI.h`` Low
   Level APIs:

   -  Added function ``SNI_registerResource()``
   -  Added function ``SNI_unregisterResource()``
   -  Added function ``SNI_registerScopedResource()``
   -  Added function ``SNI_unregisterScopedResource()``
   -  Added function ``SNI_getScopedResource()``
   -  Added function ``SNI_retrieveArrayElements()``
   -  Added function ``SNI_flushArrayElements()``
   -  Added function ``SNI_isResumePending()``
   -  Added function ``SNI_clearCurrentJavaThreadPendingResumeFlag()``
   -  Added define ``SNI_VERSION``
   -  Added define ``SNI_IGNORED_RETURNED_VALUE``
   -  Added define ``SNI_ILLEGAL_ARGUMENT``
   -  Updated the documentation of some functions to clarify the
      behavior

-  Added a message to ``IllegalArgumentException`` thrown in an SNI call
   when passing a non-immortal array in SNI (only in case the Platform
   is configured to disallow the use of non-immortal arrays in SNI
   native calls)
-  Added function ``LLMJVM_CheckIntegrity()`` to ``LLMJVM.h`` Low Level
   API to perform heap and internal structures integrity check
-  Updated ``KF`` implementation to use ``SNI-1.4`` to close native
   resources when the Feature is stopped (``ej.lang.ResourceManager`` is
   now deprecated)
-  Updated ``LLMJVM_dump()`` output with the following new information
   related to ``SNI-1.4`` native resource management:

   -  Last native method called (per thread)
   -  Current native method being invoked (per thread)
   -  Last native resource close hook called (per thread)
   -  Current native resource close hook being invoked (per thread)
   -  Pending Native Exception (per thread)
   -  Pending ``SNI`` Scoped Resource to close (per thread)
   -  Current Garbage Collector state: (running or not, last scanned
      object address, last scanned object class)
   -  ``LLMJVM`` schedule request (global and per thread)

-  Updated non-immortal object access from SNI default behavior (now
   allowed by default)
-  Fixed thread state displayed by ``LLMJVM_dump`` for threads in
   ``SLEEP`` state
-  Fixed ``sni.h`` header file function prototypes using the
   ``SNI_callback`` typedef
-  Fixed crash when an ``OutOfMemoryError`` is thrown while creating a
   native exception in SNI
-  [Multi] - Fixed runtime exceptions that can be implicitly thrown
   (such as ``NullPointerException``) which were not automatically
   exposed by the Kernel
-  [Multi] - Fixed passing Kernel array parameters through a shared
   interface method call. These parameters were passed by copy instead
   of by reference as specified by ``KF`` specification
-  [Multi] - Fixed execution context when jumping in a catch block of a
   ``ej.kf.Proxy`` method (the catch block was executed in the Kernel
   context instead of the Feature context)
-  [ARMCC5] - Fixed link error
   ``Undefined symbol _java_Ljava_lang_OutOfMemoryError_field_OOMEMethodAddr_I``
   with ARM Compiler 5 linker (introduced in version :ref:`7.12.0 <changelog-7.12.0>`)

.. _foundation-libraries-2:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``SNI`` to version ``1.4``
-  Updated internal library ``Resource-Manager-1.0`` as deprecated. Use
   ``SNI-1.4`` native resources instead
-  Updated ``java.lang.Thread.getId()`` method implementation to return
   the same value than ``SNI_getCurrentJavaThreadID()`` function
-  Optimized ``ej.sni.SNI.toCString()`` method by removing a useless
   temporary buffer copy
-  Fixed ``EDC`` implementation of ``String(byte[],int,int)``
   constructor which could allocate a too large temporary buffer
-  Fixed ``EDC`` implementation of ``Thread.interrupt()`` method to
   throw a ``java.lang.SecurityException`` when the interrupted thread
   cannot be modified by the the current thread
-  Fixed ``EDC`` implementation to remove remaining references to
   ``java.util.SecurityManager`` class when it is disabled
-  Fixed ``EDC`` implementation of ``java.lang.Thread.interrupt()``
   method that was declared ``final``
-  Fixed ``EDC`` API of ``java.lang.Thread.interrupt()`` to clarify the
   behavior of the method
-  Fixed ``EDC`` API of ``java.util.Calendar`` method to specify that
   non-lenient mode is not supported
-  Fixed ``EDC`` API of ``java.io.FilterInputStream.in`` field to be
   marked ``@Nullable``

.. _integration-2:

Integration
~~~~~~~~~~~

-  Updated Architecture End User License Agreement to version
   ``SDK 3.0-B``

.. _simulator-1:

Simulator
~~~~~~~~~

-  Added ``SNI-1.4`` support, with the following new HIL APIs:

   -  Added methods ``NativeInterface.suspendStart()`` and
      ``NativeInterface.suspendStop()`` to notify the simulator that a
      native is suspended so that it can schedule a thread with a lower
      priority

-  Added ``KF`` support to dynamically install Features (``.fs3`` files)
-  Added the capability to specify the Kernel UID from an option (see
   options in ``Simulator`` > ``Kernel`` > ``Kernel UID``)
-  Added object size in generated ``.heap`` dump files
-  Optimized file accesses from the Application
-  Fixed crash in debug mode when paused on a breakpoint in MicroEJ SDK
   and hovering a Java variable with the mouse
-  Fixed potential crash in debug mode when putting a breakpoint in
   MicroEJ SDK on a line of code declared in an inner class
-  Fixed potential crash in debug mode
   (``java.lang.NullPointerException``) when a breakpoint set on a field
   access is hit
-  Fixed potential crash in debug mode
   (``ArrayIndexOutOfBoundsException``)
-  Added support for JDWP commands ``DisableCollection`` /
   ``EnableCollection`` in the debugger
-  Fixed invalid heap dump generation in debug mode.
-  Fixed crash when a Mockup implements ``com.is2t.hil.StartListener``
   and this implementation throws an uncaught exception in the clinit
-  Fixed verbose of missing resource only when a resource is available
   in the classpath but not declared in a ``.resources.list`` file
-  Fixed heap consumption simulation for objects instances of classes
   declaring fields of type ``float`` or ``double``
-  Fixed Device UID not displayed in the Front Panel window title
   (introduced in version :ref:`7.11.0 <changelog-7.11.0>`)
-  Fixed loading of a resource from a JAR when the path starts with
   ``/``
-  Fixed potential deadlock on Front Panel startup in some cases
-  Fixed ``Thread.getState()`` returning ``TERMINATED`` whereas the
   thread is running
-  Fixed Simulator which may not stop properly when closing the Front
   Panel window
-  Fixed Front Panel which stops sending widget events when dragging out
   of a widget
-  [Multi] - Fixed monitor that may not be released when an exception
   occurs in a synchronized block (introduced in version ``7.10.0``)
-  [Multi] - Fixed invalid heap dump generation that causes heap
   analyzer crash
-  [Multi] - Fixed potential crash (``java.lang.NullPointerException``)
   in debug mode when debugging an Application (introduced in version
   :ref:`7.10.0 <changelog-7.10.0>`)
-  [Multi] - Fixed error when using ``KF`` library without defining a
   ``kernel.kf`` file in the Kernel (introduced in version :ref:`7.10.0 <changelog-7.10.0>`)

.. _soar-3:

SOAR
~~~~

-  Added an option (``soar.bytecode.verifier``) to enable or disable the
   bytecode verifier (disabled by default)
-  Removed size related limits in Architecture Evaluation version

.. _tools-5:

Tools
~~~~~

-  Added ``SNI-1.4`` support to HIL Engine
-  Updated Heap Dumper to verbose information about the memory section
   when an overlap is detected in the HEX file
-  Updated Memory Map Scripts (Security, DTLS, Device)
-  Fixed License Manager (Evaluation) random crash on Windows 10 when a
   Platform is built using ``Build Module`` button
-  Fixed License Manager (Evaluation) wrong UID computation after reboot
   when Windows 10 Hyper-V feature is enabled
-  Fixed HIL Engine to exit as soon as the Simulator is disconnected
   (avoid remaining detached processes)
-  Fixed ELF to Map generating symbol addresses different from the ELF
   symbol addresses (introduice in version :ref:`7.11.0 <changelog-7.11.0>`)
-  Fixed Heap Dumper crash when a wrong object header is encountered
-  Fixed Heap Dumper failure when a memory dump is larger than the heap
   section
-  Fixed Heap Dumper crash when loading an Intel HEX file that contains
   lines of type ``02``

.. _changelog-7.12.0:

[7.12.0] - 2019-10-16
---------------------

.. _core-engine-6:

Core Engine
~~~~~~~~~~~

-  Updated implementation of internal ``java.lang.OutOfMemoryError``
   thrown with the maximum number of frames that can be dumped
-  Updated ``LLMJVM_dump()`` output with the following new information:

   -  Maximum number of alive threads
   -  Total number of created threads
   -  Maximum number of stack blocks used
   -  Current number of stack blocks used
   -  Objects referenced by each stack frame: address, type, length (in
      case of arrays), string content (in case of String objects)
   -  [Multi] Kernel stale references with the name of the Feature
      stopped

.. _foundation-libraries-3:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Fixed ``EDC`` implementation of ``Throwable.getStackTrace()`` when
   called on a ``java.lang.OutOfMemoryError`` thrown by Core Engine or
   Simulator (either the returned stack trace array was empty or a
   ``java.lang.NullPointerException`` was thrown)
-  [Tiny] Fixed ``EDC`` implementation of
   ``StackTraceElement.toString()`` (removed the character ``.`` before
   the type)
-  [Multi] Fixed ``KF`` implementation of ``Feature.start()`` to throw a
   ``java.lang.ExceptionInInitializerError`` when an exception is thrown
   in a Feature clinit method

.. _simulator-2:

Simulator
~~~~~~~~~

-  Updated implementation of internal ``java.lang.OutOfMemoryError``
   thrown with more than one frames dumped per thread

   -  By default the ``20`` top frames per thread are dumped. This can
      be modified using ``S3.OutOfMemoryErrorNbFrames`` system property

-  Fixed wrong parsing of an array of ``long`` when an element is
   declared with only 2 digits (e.g. ``25`` was parsed as ``2``)
-  Fixed error parsing of an array of ``byte`` when an element is
   declared with the unsigned hexadecimal notation (e.g. ``0xFF``)
   (introduced in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed crash when ``ej.bon.ResourceBuffer.readString()`` is called on
   a String greater than ``63`` characters (introduced in version
   :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed code coverage ``.cc`` generation of classpath directories
-  Fixed crash during a GC when computing the references map of a
   complex method (an error message is dumped with the involved method
   name and suggest to increase the internal stack using
   ``S3.JavaMemory.ThreadStackSize`` system property)
-  [Multi] Added validity check of Shared Interface declaration files
   (``.si``) according to ``KF`` specification
-  [Multi] Fixed processing of Resource Buffers declared in Feature
   classpath

.. _soar-4:

SOAR
~~~~

-  Added a new option ``core.memory.oome.nb.frames`` to configure the
   maximum number of stack frames that can be dumped when an internal
   ``java.lang.OutOfMemoryError`` is thrown by Core Engine

.. _tools-6:

Tools
~~~~~

-  Updated Heap Dumper to verbose detected object references that are
   outside the heap
-  Updated Heap Dumper to throw a dedicated error when an object
   reference does not target the beginning of an object (most likely a
   corrupted heap)
-  Updated Heap Dumper to dump ``.heap.error`` partial file when a crash
   occurred during heap processing
-  Fixed Heap Dumper crash when processing an object owned by a Feature
   which type is also owned by the Feature (was working before only when
   the type is owned by the Kernel)
-  Fixed Firmware Linker potential negative offset generation when some
   sections do not appear in the same order in the ELF file than in
   their associated LOAD segment
-  Fixed Code Coverage Analyzer potential generated empty report (wrong
   load of classfiles from JAR files)

.. _changelog-7.11.0:

[7.11.0] - 2019-06-24
---------------------

Important Notes
~~~~~~~~~~~~~~~

-  Java assertions execution is now disabled by default. If you
   experience any runtime trouble when migrating from a previous
   Architecture, please enable Java assertions execution both on
   Simulator and on Device (maybe the application code requires Java
   assertions to be executed).
-  Calls to Security Manager are now disabled by default. If you are
   using the Security Manager, it must be explicitly enabled using the
   option described below (likely the case when building a Multi-Sandbox
   Firmware and its associated Virtual Device).
-  Front Panel framework is now provided by the Architecture instead of
   the UI Pack. This allow to build a Platform with a Front Panel
   (splash screen, basic I/O, …), even if it does not provide a MicroUI
   port. Moreover, the Front Panel framework API has been redesigned and
   is now distributed using the ``ej.tool.frontpanel.framework`` module
   instead of the legacy Eclipse classpath variable.

.. _core-engine-7:

Core Engine
~~~~~~~~~~~

-  Added ``EDC-1.3`` support for daemon threads
-  Added ``BON`` support for ``ej.bon.Util.newArray(T[],int)``
-  [Multi/ARMCC5] Fixed unused undefined symbol that prevent Keil
   MDK-ARM to link properly

.. _foundation-libraries-4:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``EDC`` to version ``1.3`` (see `EDC-1.3 API
   Changelog <https://repository.microej.com/5/artifacts/ej/api/edc/1.3.0/CHANGELOG-1.3.0.md>`__)

   -  Updated the implementation code for correct Null analysis
      detection (added assertions, extracted multiple field accesses
      into a local)
   -  Fixed ``java.io.PrintStream.PrintStream(OutputStream, boolean)``
      writer initialization
   -  Removed useless String literals in ``java.lang.Throwable``

-  Updated UTF-8 decoder to support Unicode code points
-  Updated ``BON`` to version ``1.4`` (see `BON-1.4 API
   Changelog <https://repository.microej.com/5/artifacts/ej/api/bon/1.4.0/CHANGELOG-1.4.0.md>`__)
-  Updated ``TRACE`` to version ``1.1``

   -  Added ``ej.trace.Tracer.getGroupID()``
   -  Added a BON Constant (``core.trace.enabled``) to remove trace
      related code when tracing is disabled

-  Fixed ``KF`` to call the registered
   ``Thread.UncaughtExceptionHandler`` when an exception is thrown by
   the first Feature thread

.. _integration-3:

Integration
~~~~~~~~~~~

-  Added new options for Java assertions execution in category
   ``Runtime`` (``core.assertions.sim.enabled`` and
   ``core.assertions.emb.enabled``). By default, Java assertions
   execution is disabled both on Simulator and on Device.
-  Updated options categories (options property names left unchanged)

   -  Added a new category named ``Runtime``
   -  Renamed ``Target`` to ``Device``
   -  Moved ``Embed All type names`` option from ``Core Engine`` to
      ``Runtime``
   -  Moved ``Core Engine`` under ``Device``
   -  Removed category ``Target > Debug`` and moved ``Trace`` options to
      ``Runtime``
   -  Removed category ``Debug`` and moved all sub categories under
      ``Simulator``
   -  Renamed category ``JDWP`` to ``Debug``

-  Added an option (``com.microej.library.edc.securitymanager.enabled``)
   to enable Security Manager runtime checks (disabled by default)

.. _simulator-3:

Simulator
~~~~~~~~~

-  Added a cache to speed-up classfile loading in JARs
-  Added ``EDC-1.3`` support for daemon threads
-  Added ``BON-1.4`` support for compile-time constants (load of
   ``.constants.list`` resources)
-  Added ``BON-1.4`` support for ``ej.bon.Util.newArray()``
-  Added Front Panel framework
-  Updated error message when reaching S3 simulator limits
-  Removed the ``Bootstrapping a Smart Software Simulator`` message when
   verbose mode in enabled
-  Fixed ``Object.clone()`` on an immutable object to return a new
   (mutable) object instead of an immutable one
-  Fixed ``Object.clone()`` crash when an OutOfMemory occurs
-  Fixed potential crash when calling an abstract method (some
   interfaces of the hierarchy were not taken into account - introduced
   in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed OutOfMemory errors even if the heap is not full (resources
   loaded from ``Class.getResourceAsStream`` and
   ``ResourceBuffer.open()`` were taken into account in simulated heap
   memory - introduced in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed potential crash when a GC occurs while a ``ResourceBuffer`` is
   open (introduced in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed potential debugger hangs when an exception was thrown but not
   caught in the same method
-  [Multi] Fixed wrong class loading in some cases
-  [Multi] Fixed wrong immutable loading in some cases

.. _soar-5:

SOAR
~~~~

-  Added ``BON-1.4`` support for compile-time constants (load of
   ``.constants.list`` resources)
-  Added bytecode removal for Java assertions (when option is disabled)
-  Added bytecode removal for ``if(ej.bon.Constants.getBoolean())``
   pattern

   -  ``then`` or ``else`` block is removed depending on the boolean
      condition
   -  *WARNING: Current limitation: the ``if`` statement cannot wrap or
      be nested in a ``try-catch-finally`` statement*

-  Added an option for grouping all the methods by type in a single ELF
   section

   -  ``com.microej.soar.groupMethodsByType.enabled`` (``false`` by
      default)
   -  *WARNING: this option avoids to reach the maximum number of ELF
      sections (65536) when building a large application, but affects
      the application code size (especially inline methods are embedded
      even if they are not used)*

-  Added an error message when ``microejapp.o`` cannot be generated
   because the maximum number of ELF sections (65536) is reached

.. _tools-7:

Tools
~~~~~

-  Updated License Manager (Production) to debug dongle recognition
   issues. (usage is
   ``java -Djava.library.path=resources/os/[OS_NAME] -jar licenseManager/licenseManagerUsbDongle.jar``
   in an Architecture or Platform folder)
-  Updated License Manager (Production ) to support dongle recognition
   on Mac OS ``10.14`` (Mojave)
-  Fixed ELF To Map to produce correct sizes from an executable
   generated by IAR Embedded Workbench for ARM
-  Fixed Firmware Linker ``.ARM.exidx`` section generation (missing
   section link content)
-  Updated deployment files policy for Platforms in Worskpace, in order
   to be more flexible depending on the C project layout. This also
   allows to deploy to the same C project different Applications built
   with different Platforms

   -  Platform configuration: in ``bsp/bsp.properties``, a new option
      ``output.dir`` indicates where the files are deployed by default

      -  Application (``microejapp.o``) and Platform library
         (``microejruntime.a``) are deployed to ``${output.dir}/lib``.
         Platform header files (``*.h``) are deployed to
         ``${output.dir}/inc/``
      -  When this option is not set, the legacy behavior is left
         unchanged (``project.file`` option in collaboration with
         ``augmentCProject`` scripts)

   -  Launch configuration: ``Device > Deploy`` options allow to override the default Platform configuration in order to deploy each MicroEJ file into a separate folder.

-  Fixed wrong ELF file generation when a section included in a LOAD
   segment was generated before one of the sections included in a LOAD
   segment declared before the first one (integrated in ELF Utils and
   Firmware Linker)
-  Fixed wrong ELF file generation when a section included in a LOAD
   segment had an address which was outside its LOAD segment virtual
   address space (integrated in ELF Utils and Firmware Linker)

.. _section-10:

[7.10.1] - 2019-04-03
---------------------

.. _simulator-4:

Simulator
~~~~~~~~~

-  Fixed ``Object.getClass()`` may return a Class instance owned by a
   Feature for type owned by the Kernel

.. _changelog-7.10.0:

[7.10.0] - 2019-03-29
---------------------

.. _core-engine-8:

Core Engine
~~~~~~~~~~~

-  Added internal memories checks at startup: heaps and statics memories
   are not allowed to overlap with ``LLBSP_IMPL_isInReadOnlyMemory()``
-  [Multi] - Updated Feature Kill implementation to prepare future RAM
   Control (fully managed by Core Engine)
-  [Multi] - Updated implementation of ``ej.kf.Kernel``: all APIs taking
   a Feature argument now will throw a
   ``java.lang.IllegalStateException`` when the Feature is not started

.. _foundation-libraries-5:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``KF`` library in sync with Core Engine Kill related fixes
   and Simulator with Kernel & Features semantic
-  Updated ``BON`` library on Simulator (now uses the same
   implementation than the one used by the Core Engine)

.. _integration-4:

Integration
~~~~~~~~~~~

-  Added generation of ``architecture.properties`` file when building a
   Platform. (Used by MicroEJ SDK/Studio ``5`` when manipulating
   Platforms & Virtual Devices)

.. _simulator-5:

Simulator
~~~~~~~~~

-  Added ``Embed all types names`` option for Simulation
-  Added memory size simulation for Java Heap and Immortal Heap
   (Enabling ``Use target characteristics`` option is no more required)
-  Added Kernel & Features semantic, as defined in the ``KF-1.4``
   specification

   -  Fully implemented:

      -  Ownership for types, object and thread execution context
      -  Kernel mode
      -  Context Local Static Field References

   -  Partially implemented:

      -  Kernel API (Type grained only)
      -  Shared Interfaces are binded using direct reference links (no
         Proxy execution)
      -  ``Feature.stop()`` does not perform the safe kill. The
         application cannot be stopped unless it has correctly removed
         all its shared references.

   -  Not implemented:

      -  Dynamic Feature installation from
         ``Kernel.install(java.io.InputStream)``
      -  Execution Rules Runtime checks

.. _tools-8:

Tools
~~~~~

-  Updated Memory Map Scripts (Bluetooth, MWT, NLS, Rcommand and AllJoyn
   libraries)
-  Fixed ``Kernel Packager`` internal limits error when the ELF
   executable does not contains a ``.debug.soar`` section
-  Fixed wrong ELF file generation when segment file size is different
   than the mem size (integrated in ``ELF Utils`` and
   ``Firmware Linker``)
-  Fixed Simulator COM port mapping default value (set to ``disabled``
   instead of ``UART<->UART`` in order to avoid an error when launch
   configuration is just created)
-  Fix ELF To Map: the total sections size were not equal to the
   segments size

.. _section-12:

[7.9.1] - 2019-01-08
--------------------

.. _tools-9:

Tools
~~~~~

-  Fixed ELF objcopy generation when ELF executable file contains ``0``
   size segments
-  Fixed ``Stack Trace Reader`` error when ELF executable file contains
   relocation sections

.. _section-13:

[7.9.0] - 2018-09-20
--------------------

.. _soar-6:

SOAR
~~~~

-  Optimized SOAR processing (up to 50% faster on applications with tens
   of classpath entries)

.. _section-14:

[7.8.0] - 2018-08-01
--------------------

.. _tools-10:

Tools
~~~~~

-  [ARMCC5] - Updated ``SOAR Debug Infos Post Linker`` tool to generate
   the full ELF executable file

.. _section-15:

[7.7.0] - 2018-07-19
--------------------

.. _core-engine-9:

Core Engine
~~~~~~~~~~~

-  Added a permanent hook ``LLMJVM_on_Runtime_gc_done`` called after an
   explicit ``java.lang.Runtime.gc()``
-  Updated internal heap header for memory dump

.. _soar-7:

SOAR
~~~~

-  Added check for the maximum number of allowed concrete types (avoids
   a Core Engine link error)

.. _tools-11:

Tools
~~~~~

-  Added ``Heap Dumper`` tool

.. _section-16:

[7.6.0] - 2018-06-29
--------------------

.. _foundation-libraries-6:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  [Multi] Updated ``BON`` library: a Timer owned by the Kernel can
   execute a TimerTask owned by a Feature

.. _section-17:

[7.5.0] - 2018-06-15
--------------------

*Internal Release - COTS Architecture left unchanged.*

.. _section-18:

[7.4.0] - 2018-06-13
--------------------

.. _core-engine-10:

Core Engine
~~~~~~~~~~~

-  Removed partial support of ``ej.bon.Util.throwExceptionInThread()``
   (deprecated)
-  [Multi/Linux] - Updated default configuration to always embed method
   names
-  [Multi/Cortex-M] - Optimized KF checks execution for array & field
   accesses

.. _foundation-libraries-7:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``ej.bon.Timer`` to schedule ``ej.bon.TimerTask`` owned by
   multiple Features

.. _simulator-6:

Simulator
~~~~~~~~~

-  Fixed implementation of ``java.lang.Class.getResourceAsStream()`` to
   throw a ``java.io.IOException`` when the stream is closed

.. _soar-8:

SOAR
~~~~

-  [GCC] - Fixed ``microejapp.o`` link with GCC 6.3

.. _tools-12:

Tools
~~~~~

-  Added a retry mechanism in the Testsuite Engine
-  Added a message to suggest increasing the JVM heap when an
   ``OutOfMemoryError`` occurs in the ``Firmware Linker`` tool
-  Fixed generation of LL header files for all cross compilation
   toolchains (file separator for included paths is ``/``)
-  [Cortex-A/ARMCC5] - Fixed SNI convention call issue
-  [ESP32,RX] - Fixed ``Firmware Linker`` tool internal limit

.. _section-19:

[7.3.0] - 2018-03-07
--------------------

.. _simulator-7:

Simulator
~~~~~~~~~

-  Added an option for the IDE to customize the mockups classpath
-  Fixed Deadlock in Shielded Plug remote client when interrupting a
   thread that waits for block modification

.. _section-20:

[7.2.0] - 2018-03-02
--------------------

.. _core-engine-11:

Core Engine
~~~~~~~~~~~

-  [Multi] - Enabled quantum counter computation only when Feature quota
   is set
-  [Cortex-M/IAR74] - Updated compilation flags to ``-Oh``

.. _simulator-8:

Simulator
~~~~~~~~~

-  Added a hook in the mockup that is automatically called during the
   HIL Engine startup
-  Added dump of loaded classes when ``verbose`` option is enabled
-  Fixed ``java.lang.Runtime.freeMemory()`` call freeze when
   ``Emb Characteristics`` option is enabled
-  Fixed ShieldedPlug server error after interrupting a thread that is
   waiting for a database block
-  Fixed crash ``Access to a wrong reference`` in some cases
-  Fixed ``java.lang.NullPointerException`` when interrupting a thread
   that has not been started
-  Fixed crash when closing an HIL connection in some cases
-  [Multi] - Fixed KF & Watchdog library link when
   ``Emb Characteristics`` option is enabled
-  [Multi] - Fixed XML Parsing error when ``Emb Characteristics`` option
   is enabled

.. _section-21:

[7.1.2] - 2018-02-02
--------------------

.. _soar-9:

SOAR
~~~~

-  Fixed SNI library was added in the classpath in some cases

[maintenance/6.18.0] - 2017-12-15
---------------------------------

.. _core-engine-12:

Core Engine
~~~~~~~~~~~

-  [Multi] - Enabled quantum counter computation only when Feature quota
   is set
-  [Cortex-M/IAR74] - Updated compilation flags to ``-Oh``

.. _simulator-9:

Simulator
~~~~~~~~~

-  Fixed ``java.lang.Runtime.freeMemory()`` call freeze when
   ``Emb Characteristics`` option is enabled
-  [Multi] - Fixed KF & Watchdog library link when
   ``Emb Characteristics`` option is enabled
-  [Multi] - Fixed XML Parsing error when ``Emb Characteristics`` option
   is enabled

.. _tools-13:

Tools
~~~~~

-  Updated ``Kernel API Generator`` tool with classes filtering

.. _section-22:

[7.1.1] - 2017-12-08
--------------------

.. _tools-14:

Tools
~~~~~

-  [Multi/RX] - Fixed ``Firmware Linker`` tool

.. _section-23:

[7.1.0] - 2017-12-08
--------------------

.. _core-engine-13:

Core Engine
~~~~~~~~~~~

-  [Multi/RX] - Added KF support

.. _integration-5:

Integration
~~~~~~~~~~~

-  Fixed ``SNI-1.3`` library name

.. _soar-10:

SOAR
~~~~

-  [RX] - Added support for ELF symbol prefix ``_``

.. _tools-15:

Tools
~~~~~

-  Updated ``Kernel API generator`` tool with classes filtering

.. _section-24:

[7.0.0] - 2017-11-07
--------------------

.. _core-engine-14:

Core Engine
~~~~~~~~~~~

-  Added SNI-1.3 support
-  ``SNI_suspendCurrentJavaThread()`` is not interruptible via
   ``java.lang.Thread.interrupt()`` anymore

.. _foundation-libraries-8:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated to ``SNI-1.3``

.. _section-25:

[6.17.2] - 2017-10-26
---------------------

.. _simulator-10:

Simulator
~~~~~~~~~

-  Fixed deadlock during bootstrap in some cases

.. _section-26:

[6.17.1] - 2017-10-25
---------------------

.. _core-engine-15:

Core Engine
~~~~~~~~~~~

-  Fixed conversion of ``-0.0`` into a positive value

.. _section-27:

[6.17.0) - 2017-10-10
---------------------

.. _tools-16:

Tools
~~~~~

-  Updated Memory Map Scripts for TRACE library

.. _section-28:

[6.16.0] - 2017-09-27
---------------------

.. _core-engine-16:

Core Engine
~~~~~~~~~~~

-  Fixed External Resource Loader link error (introduced in version
   :ref:`6.13.0 <changelog-6.13.0>`)

.. _section-29:

[6.15.0] - 2017-09-12
---------------------

.. _core-engine-17:

Core Engine
~~~~~~~~~~~

-  Added a new option to configure the maximum number of monitors that
   can be owned per thread (8 per thread by default, as it was fixed
   before)

.. _foundation-libraries-9:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Fixed ECOM-COMM internal heap calibration

.. _soar-11:

SOAR
~~~~

-  Added log of the class loading cause

.. _section-30:

[6.14.2] - 2017-08-24
---------------------

.. _tools-17:

Tools
~~~~~

-  Fixed ``Firmware Linker`` tool script (load ``activity.xml`` from the
   wrong folder)
-  Fixed load of symbol ``_java_Ljava_io_EOFException`` that can be
   required by some linkers even if this symbol is not touched

.. _section-31:

[6.14.1] - 2017-08-02
---------------------

.. _simulator-11:

Simulator
~~~~~~~~~

-  Fixed Device Mockup too long initialization that may block the Front
   Panel Mockup

.. _foundation-libraries-10:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Fixed BON ``.types.list`` potential conflicts with KF

.. _tools-18:

Tools
~~~~~

-  Modified ``Firmware Linker`` internal scripts structure for new
   Virtual Devices tools

.. _changelog-6.13.0:

[6.13.0] - 2017-07-21
---------------------

.. _core-engine-18:

Core Engine
~~~~~~~~~~~

-  Added support for ``ej.bon.ResourceBuffer``

.. _foundation-libraries-11:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated to ``BON-1.3``

.. _soar-12:

SOAR
~~~~

-  Added support for ``*.resourcesext.list`` (resources excluded from
   the firmware)

.. _tools-19:

Tools
~~~~~

-  Added BON Resource Buffer generator

.. _section-33:

[6.12.0] - 2017-07-07
---------------------

.. _core-engine-19:

Core Engine
~~~~~~~~~~~

-  Added a trace when ``java.lang.IllegalMonitorStateException`` is
   thrown on a ``monitorexit``

.. _tools-20:

Tools
~~~~~

-  Added property ``skip.mergeLibraries`` for Platform Builder.
-  Updated serial PC connector to ``JSSC v2.8.0``

.. _simulator-12:

Simulator
~~~~~~~~~

-  Fixed unexpexted ``java.lang.NullPointerException`` in some cases

.. _section-34:

[6.11.0] - 2017-06-13
---------------------

.. _integration-6:

Integration
~~~~~~~~~~~

-  Fixed useless watchdog library copied in root folder

[6.11.0-beta1] - 2017-06-02
---------------------------

.. _core-engine-20:

Core Engine
~~~~~~~~~~~

-  Added an option to enable execution traces
-  Added Low Level API ``LLMJVM_MONITOR_impl.h``
-  Added Low Level API ``LLTRACE_impl.h``

.. _foundation-libraries-12:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Added ``TRACE-1.0``

.. _section-35:

[6.10.0] - 2017-06-02
---------------------

.. _core-engine-21:

Core Engine
~~~~~~~~~~~

-  Optimized ``java.lang.Runtime.gc()`` (removed useless heap compaction
   in some cases)

.. _section-36:

[6.9.2] - 2017-06-02
--------------------

.. _integration-7:

Integration
~~~~~~~~~~~

-  Fixed missing properties in ``release.properties`` (introduced in
   version :ref:`v6.9.1 <changelog-6.9.1>`)
-  Fixed artifacts build dependencies to private dependencies

.. _changelog-6.9.1:

[6.9.1] - 2017-05-29
--------------------

.. _soar-13:

SOAR
~~~~

-  [Multi] - Fixed selected methods list in report generation (removed
   Kernel related method)

.. _section-38:

[6.9.0] - 2017-03-15
--------------------

*Base version, included into MicroEJ SDK 4.1.*


..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
