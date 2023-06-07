.. _architecture_changelog:

Architectures Changelog
========================

Notation
--------

A line prefixed by ``[]`` describes a change that only applies on a
specific configuration:
``[Core Engine Capability/Instruction Set/C Compiler]``:

-  Core Engine Capability

   -  ``Single``: Mono-Sandbox (default)
   -  ``Tiny``: Tiny-Sandbox
   -  ``Multi``: Multi-Sandbox

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
   -  ``Clang``: Clang



.. _changelog-8.0.0:

[8.0.0] - 2023-MM-DD
--------------------

This major Architecture version update introduces the following main features:

- Added compatibility with dynamic linkers enabling Address Space Layout Randomization (ASLR).
- Added :ref:`Feature build on device <build_feature_on_device>`. For that, the SOAR has been deeply redesigned and split into multiple phases.
  The most noticeable change is about the :ref:`SOAR Information File <soar_info_file>` that is now composed of 3 files.
- Added Feature portability. The same ``.fo`` file can now be installed:    
  
  - On any Executable built from the same Kernel Application (``microejapp.o``). 
    The VEE Port C code can be modified and relinked without requiring to rebuild the ``.fo`` file anymore.
  
  - On different Kernel Applications provided some conditions are met. 
    Basically, a ``.fo`` built on Kernel 1 can be installed on Kernel 2 if the exposed Kernel APIs are left unchanged.
    See :ref:`feature_portability_control` for more details.
- Redesigned :ref:`Feature installation <feature_memory_installation>` flow. A Feature can now be installed in any byte-addressable memory, including ROM.
  Former Feature installation in RAM is preserved and is now called :ref:`In-Place Installation <feature_inplace_installation>`. 
  For that, ``LLKERNEL`` Low Level APIs have been fully rewritten.

If you plan to migrate a VEE Port from Architecture ``7.x`` to Architecture ``8.x``, consider the :ref:`architecture7_migration` chapter.

Core Engine
~~~~~~~~~~~

- Renamed :ref:`Core Engine sections <core_engine_link>` to fully respect the ELF standard naming convention. 
- Removed check when passing a non-immortal array in SNI if VEE Port option ``core.sni.nonimmortal.access`` was set to ``false``.
- Removed ``LLBSP_isInReadOnlyMemory`` in Core Engine Abstraction Layer (``LLBSP.h`` file).
- Clarified ``LLMJVM_IMPL_getCurrentTime`` API contract in Core Engine Abstraction Layer (``LLMJVM_impl.h`` file).
- Fixed potential crash when Core Engine is restarted after a call to `System.exit(int)`_.
- Updated ``Trace`` C library from version ``1.0.0`` to ``2.0.0``:

  - Renamed header file ``trace.h`` into ``LLTRACE.h`` to avoid filename conflicts.
  
  - Renamed C functions ``TRACE_xxx`` into ``LLTRACE_xxx``.

- [Multi] - Added option :ref:`com.microej.runtime.kernel.dynamicfeatures.max <option_maximum_number_of_dynamic_features>` to configure the maximum number of Features that can be dynamically installed.
- [Multi] - Added option :ref:`com.microej.runtime.kf.waitstop.delay <option_feature_stop_timeout>` to configure the maximum time allowed for a Feature to stop.
- [Multi] - Fixed missing release of allocated Feature buffers after Core Engine exits (:ref:`In-Place Installation <feature_inplace_installation>` mode).

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``KF`` to version ``1.7``:
  
   -  Added heap memory control: `Module.getAllocatedMemory()`_, `Kernel.setReservedMemory()`_ and `Feature.setMemoryLimit()`_ methods.
   -  Added load of a Feature resource (`Feature.getResourceAsStream()`_ method).
- Updated ``KF`` dynamic loader to support :ref:`Feature Custom Installation <feature_custom_installation>` mode.
- Removed Foundation Libraries API Jars and Javadoc.
- Fixed :ref:`option_embed_utf8` defaults to ``true`` when building a Standalone Application using MMM.
- Fixed ``KF`` to call the registered `Thread.UncaughtExceptionHandler`_ when an exception is thrown in `FeatureEntryPoint.stop()`_.
- Removed `Unknown product - Unknown version` comment in auto-generated Low Level API header files.
- Removed the ``Serial Communication`` modules group, including the Foundation Libraries ``ECOM`` and ``ECOM-COMM``. See :ref:`architecture7_migration_ecom`.
- Removed the deprecated ``Device Information`` module group, including the Foundation Library ``Device``. See :ref:`architecture7_migration_device`.
- [Single] Fixed an unexpected ``FeatureFinalizer`` exception or infinite loop when a Standalone Application touches a ``KF`` API in some cases.
- [Tiny] Fixed an unexpected SOAR error when a Standalone Application touches a ``KF`` API.
- [Multi] Fixed exception thrown when calling `Kernel.removeConverter()`_.
- [Multi] Fixed an unexpected ``NullPointerException`` thrown by ``ej.kf.Kernel.<clinit>`` method in some cases.
- [Multi] Fixed KF watchdogs not triggered correctly when several expire at the same time.
- Fixed NullPointerException in the skip method of an InputStream returned by the external resource loader.
- Fixed the behavior of the available, read, skip, mark, reset and close method when one of these methods is called after the input stream has been closed.
- Fixed the javadoc of the LLEXT_RES_read native function (the buffer passed cannot be null).

.. _Module.getAllocatedMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Module.html#getAllocatedMemory--
.. _Kernel.setReservedMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#setReservedMemory-long-
.. _Feature.setMemoryLimit(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Feature.html#setMemoryLimit-long-
.. _Feature.getResourceAsStream(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Feature.html#getResourceAsStream-java.lang.String-
.. _FeatureEntryPoint.stop(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/FeatureEntryPoint.html#stop--
.. _Kernel.removeConverter(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#removeConverter-ej.kf.Converter-

Integration
~~~~~~~~~~~

- Added support for resolving :ref:`Front Panel in Workspace <resolve_foundation_libraries_in_workspace>` before the included Front Panel.
- Added Memory Map Scripts for Eclasspath ``Math``, ``Formatter`` and ``DateFormat``.
- Updated default value of VEE Port configuration option ``vendorURL``.
- Updated Memory Map Scripts for ``MicroVG`` library.
- Updated Memory Map Scripts for Eclasspath ``Executor`` library.
- Updated output Map file location to ``soar/[application_main_class].map`` (formerly named ``SOAR.map``).
- Removed unused ``SOAR.o`` file. It is available at ``bsp/microejapp.o``.
- Renamed MicroEJ launch :guilabel:`Build dynamic Feature` to :guilabel:`Build Feature`.
- [Multi] Fixed the SOAR output files from being deleted when the :guilabel:`Clean intermediate files` option is enabled.

Simulator
~~~~~~~~~

- Added :ref:`Mock debug <option_mock_debug>` mode.
- Added missing default values for the properties ``s3.slow``, ``console.logs.period``, and ``s3.hil.timeout`` when launching the Simulator from the command line.
- Added a check for unsupported access to the Class instance of a primitive type (e.g. ``byte.class``).
- Fixed "Internal limits" error in HIL engine when too many array arguments are used at the same time by one or several native methods.
- Fixed slow reading with an array of bytes of the input stream returned by `Class.getResourceAsStream(String)`_.
- Added HIL Engine debug logs when verbose option is enabled.
- Added log of the Mock classpath when verbose option is enabled.
- Added log of Mock resolution errors (class or method not found).
- Fixed configuration of the Java heap size using :ref:`option_java_heap`. The legacy ``core.memory.javaheapsum.size`` option is not more supported.
- Fixed :ref:`option_immortal_heap` default value when running a Standalone Application using MMM.
- Fixed stop of the HIL Engine if Simulator was terminated before the connection is established.
- Fixed load of the Mock classes in the classpath order (left-to-right).
- Fixed the missing error check when loading an immutable file referencing an external object id (the ``importObject`` directive is required).
- [Multi] Fixed the computation of object sizes. The 4-byte KF header was missing.
- Added support for mark/reset on the input stream returned by Class.getResourceAsStream

SOAR
~~~~

 - Added support for :ref:`Resource <section.classpath.elements.raw_resources>` alignment constraint.
 - Added a check for legacy ``.system.properties`` files in the :ref:`Application Classpath <chapter.microej.classpath>`. The build process is stopped and an error is reported.
   These files must be migrated to :ref:`system_properties`.
 - Added a check for unsupported access to the Class instance of a primitive type (e.g. ``byte.class``).

Tools
~~~~~

- Updated the serial PC connector to JSSC ``2.9.4``, including support for macOS aarch64 (M1 chip).
- Removed :ref:`Test Suite Engine <testsuite_engine>`. If needed, the Test Suite Engine is available in the :ref:`Build Kit <mmm_build_kit>`.
- Removed Immutables NLS library. Use :ref:`Binary NLS <chapter.nls>` add-on library instead. 
- Fixed an incorrect generation of a debug file beside the memory file when launching the Heap Dumper.
- [Multi] Added Heap Dumper support for dynamically installed Features.


.. _changelog-7.20.1:

[7.20.1] - 2023-04-10
---------------------

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Fixed `Float.parseFloat(...)`_ and `Double.parseDouble(...)`_ that don't throw a `NumberFormatException`_ when the given string is empty.
-  Fixed float and double to string conversions that contain an unecessary ``+`` sign in the exponent.

.. _Float.parseFloat(...): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Float.html#parseFloat-java.lang.String-
.. _Double.parseDouble(...): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Double.html#parseDouble-java.lang.String-
.. _NumberFormatException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/NumberFormatException.html

.. _changelog-7.20.0:

[7.20.0] - 2023-04-04
---------------------

Known Issues
~~~~~~~~~~~~

-  `Float.parseFloat(...)`_ and `Double.parseDouble(...)`_ don't throw a `NumberFormatException`_ when the given string is empty.
-  Float and double to string conversions contain an unecessary ``+`` sign in the exponent.

Core Engine
~~~~~~~~~~~

- Added the capability to customize implementation of the function that performs an atomic exchange operation.
- [ESP32] - Remove default implementation of the function that performs an atomic exchange operation. The Core Engine abstraction layer implementation has to implement the C function ``int32_t LLBSP_IMPL_atomic_exchange(int32_t* ptr, int32_t value)``.

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

- Fixed uninitialized pointer access in the :ref:`External Resources Loader<section_externalresourceloader>`, which can cause a system crash when reading data from a resource.

.. _Class.getResourceAsStream(String): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getResourceAsStream-java.lang.String-
.. _System.exit(int): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#exit-int-


.. _changelog-7.19.0:

[7.19.0] - 2023-02-16
---------------------

Known Issues
~~~~~~~~~~~~

-  `Float.parseFloat(...)`_ and `Double.parseDouble(...)`_ don't throw a `NumberFormatException`_ when the given string is empty.
-  Float and double to string conversions contain an unecessary ``+`` sign in the exponent.

Core Engine
~~~~~~~~~~~

- Added the capability to customize implementation of the functions that convert strings to float/double values and vice-versa.
- [Cortex-A/Clang] - Fixed wrong float/double arguments passed to the SNI natives.

Tools
~~~~~

- Removed dependency on GNU ``ar`` program to create ``microejruntime.a`` archive file.


.. _changelog-8.0.0:

[8.0.0] - 2023-MM-DD
--------------------

This major Architecture version update introduces the following main features:

- Added compatibility with dynamic linkers enabling Address Space Layout Randomization (ASLR).
- Added :ref:`Feature build on device <build_feature_on_device>`. For that, the SOAR has been deeply redesigned and split into multiple phases.
  The most noticeable change is about the :ref:`SOAR Information File <soar_info_file>` that is now composed of 3 files.
- Added Feature portability. The same ``.fo`` file can now be installed:    
  
  - On any Executable built from the same Kernel Application (``microejapp.o``). 
    The VEE Port C code can be modified and relinked without requiring to rebuild the ``.fo`` file anymore.
  
  - On different Kernel Applications provided some conditions are met. 
    Basically, a ``.fo`` built on Kernel 1 can be installed on Kernel 2 if the exposed Kernel APIs are left unchanged.
    See :ref:`feature_portability_control` for more details.

If you plan to migrate a VEE Port from Architecture ``7.x`` to Architecture ``8.x``, consider the :ref:`architecture7_migration` chapter.

Core Engine
~~~~~~~~~~~

- Renamed :ref:`Core Engine sections <core_engine_link>` to fully respect the ELF standard naming convention. 
- Removed check when passing a non-immortal array in SNI if VEE Port option ``core.sni.nonimmortal.access`` was set to ``false``.
- Removed ``LLBSP_isInReadOnlyMemory`` in Core Engine Abstraction Layer (``LLBSP.h`` file).

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

- Removed Foundation Libraries API Jars and Javadoc.

Integration
~~~~~~~~~~~


Simulator
~~~~~~~~~

- Added missing default values for the properties ``s3.slow``, ``console.logs.period``, and ``s3.hil.timeout`` when launching the Simulator from the command line.

SOAR
~~~~

Tools
~~~~~

- Removed :ref:`Test Suite Engine <testsuite_engine>`. If needed, the Test Suite Engine is available in the :ref:`Build Kit <mmm_build_kit>`.
- Removed Immutables NLS library. Use :ref:`Binary NLS <chapter.nls>` add-on library instead. 


.. _changelog-7.18.1:

[7.18.1] - 2022-10-26
---------------------

Integration
~~~~~~~~~~~

- Fixed License Manager issue with JDK 8u351 or higher (``[M65] - License check failed [tampered (3)].``).

.. _changelog-7.18.0:

[7.18.0] - 2022-09-14
---------------------

Integration
~~~~~~~~~~~

- Added support for Windows 11.
- Added License Manager support for macOS aarch64 (M1 chip).
- Removed warning when launching Applications or Tools with JDK 11 (`Warning: Nashorn engine is planned to be removed from a future JDK release`).

SOAR
~~~~

- Added grouping of all immutables objects in a single ELF section.

.. _changelog-7.17.0:

[7.17.0] - 2022-06-13
---------------------

Core Engine
~~~~~~~~~~~

-  Fixed potential premature evaluation timeout when Core Engine is not started at the same time as the device.
-  Fixed potential crash during the call of ``LLMJVM_dump`` when printing information about the Garbage Collector.
-  Added new functions to Low Level API ``LLMJVM_MONITOR_impl.h`` (see :ref:`Advanced-Event-Tracing`):

  
   -  ``void LLMJVM_MONITOR_IMPL_on_invoke_method(void* method)``: called by the Core Engine when an method is invoked.
   -  ``void LLMJVM_MONITOR_IMPL_on_return_method(void* method)``: called by the Core Engine when a method returns.

-  [Cortex-M] - Added support for MCU configuration with unaligned access traps enabled (``UNALIGN_TRP`` bit set in ``CCR`` register).

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``KF`` to version ``1.6``:
  
   -  Added `Kernel.canUninstall()`_ method.

.. _Kernel.canUninstall(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#canUninstall-ej.kf.Feature-

Integration
~~~~~~~~~~~

-  Fixed some Architecture tools compatibility issues with SDKs running on JDK 11.
-  Fixed missing default value for ShieldedPlug server port when running it with MMM (``10082``).
-  Updated Memory Map Scripts for ``ej.microvg`` library.
-  Updated Architecture End User License Agreement to version ``SDK 3.1-A``.

Simulator
~~~~~~~~~

-  Added class file major version check (<=51). Classes must be compiled for Java 7 or lower. Set the options property ``S3.DisableClassFileVersionCheck`` to ``false`` to disable this verification.
-  Added native method signature in the stack trace of the `UnsatisfiedLinkError`_ thrown when a native method is missing.
-  Fixed HIL engine method ``NativeInterface.getResourceContent()`` that generates a runtime error in the Simulator.
-  Fixed error "Internal limits reached ... S3 internal heap is full" when repeatedly loading a resource that is available in the classpath but not referenced in a ``.resources.list`` file.
-  Fixed `OutOfMemoryError`_ when loading a large resource with `Class.getResourceAsStream()`_.
-  Fixed ``A[].class.isAssignableFrom(B[].class)`` returning ``false`` instead of ``true`` when  ``B`` is a subclass of ``A``.
-  Fixed potential "Internal limits reached" error when an `OutOfMemoryError`_ is thrown. 
-  Fixed error "Cannot pin objects anymore" when passing repeatedly immutable objects to a native method.
-  Fixed properties not passed correctly to the mocks when the Virtual Device is executed from a path that contains spaces.
-  [Multi] - Fixed an unexpected error when ``kernel.kf`` file is missing and KF library is used: "Please specify a 'kernel.kf' file to enable Kernel & Features semantics."
-  [Multi] - Fixed type ``double[]`` not recognized in ``kernel.api`` file.

.. _UnsatisfiedLinkError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/UnsatisfiedLinkError.html
.. _OutOfMemoryError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/OutOfMemoryError.html
.. _Class.getResourceAsStream(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getResourceAsStream-java.lang.String-

SOAR
~~~~

-  Fixed internal error when using a BON constant in an if statement at the end of a ``try`` block.
-  Fixed internal error when a ``try`` block ends with an ``assert`` expression while assertions are disabled.
-  [Multi] - Raise a warning instead of an error when duplicated ``.kf`` files are detected in the Kernel classpath. Usual classpath resolution order is used to load the file (see :ref:`chapter.microej.classpath`).
-  [Multi] - Fixed SOAR error when building a Feature that uses an array of basetypes that is not explicitly declared in the ``kernel.api`` file of the Kernel.
-  [Multi] - Optimized "Build Dynamic Feature" scripts speed by removing unnecessary steps.


[7.16.0] - 2021-06-24
---------------------

Known Issues
~~~~~~~~~~~~

- [Multi] - SOAR may fail to build a Feature with the following message:
  
  .. code-block:: 
  
     1 : KERNEL/FEATURE ERROR
         [M25] - Type double[] is expected to be owned by the Kernel but is not embedded. 

  Workaround is to explicitly declare each array of basetypes in your ``kernel.api`` file:
  
  .. code-block:: xml
     
      <type name="int[]"/>
      <type name="long[]"/>
      <type name="short[]"/>
      <type name="double[]"/>
      <type name="float[]"/>
      <type name="byte[]"/>
      <type name="char[]"/>
      <type name="boolean[]"/>

Notes
~~~~~

The ``Device`` module provided by the Architecture is deprecated
and will be removed in a future version. It has been moved to the
`Device Pack`_. Please update your VEE Ports.

.. _Device Pack: https://repository.microej.com/modules/com/microej/pack/device/device-pack/

Core Engine
~~~~~~~~~~~

-  Added a dedicated error code ``LLMJVM_E_INITIALIZE_ERROR (-23)`` when
   ``LLMJVM_IMPL_initialize()``, ``LLMJVM_IMPL_vmTaskStarted()``, or
   ``LLMJVM_IMPL_shutdown()`` fails. Previously the generic error code
   ``LLMJVM_E_MAIN_THREAD_ALLOC (-5)`` was returned.
-  Added automatic heap consumption fing when option ``com.microej.runtime.debug.heap.monitoring.enabled`` is set to ``true``
-  Fixed some parts of ``LLMJVM_checkIntegrity()`` code were embedded even if not called
-  [Multi] - Fixed potential crash during the call of
   ``LLMJVM_checkIntegrity()`` when analyzing a corrupted Java stack (make
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
  
   -  Added missing `Kernel.getAllFeatureStateListeners()`_ method
   -  Updated code for correct Null analysis detection
   -  Fixed `Feature.getCriticality()`_ to throw
      `IllegalStateException`_ 
      if it is in state ``UNINSTALLED`` (instead of returning ``NORM_CRITICALITY``)
   -  Fixed potential race condition between
      `Kernel.addResourceControlListener()`_ and
      `Kernel.removeResourceControlListener()`_. Adding a new listener
      may not register it if another one is removed at the same time.

.. _Kernel.getAllFeatureStateListeners(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#getAllFeatureStateListeners--
.. _Feature.getCriticality(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Feature.html#getCriticality--
.. _IllegalStateException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalStateException.html
.. _Kernel.addResourceControlListener(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#addResourceControlListener-ej.kf.ResourceControlListener-
.. _Kernel.removeResourceControlListener(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#removeResourceControlListener-ej.kf.ResourceControlListener-

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
-  Updated copyright notice of Low Level APIs header files to latest SDK default license
-  Updated Architecture module with required files and configurations for correct publication in a module repository (``README.md``,
   ``LICENSE.txt``, and ``CHANGELOG.md``)

Simulator
~~~~~~~~~

-  Added an option (``com.microej.simulator.hil.frame.size``) to
   configure the HIL engine max frame size
-  Fixed load of an immutable byte field (sign extension)
-  Fixed `java.lang.String`_ constructors ``String(byte[] bytes, ...)`` when passing
   characters in the range ``[0x80,0xFF]`` using default ``ISO-8859-1`` encoding
-  Fixed potential crash in debug mode when a breakpoint is set on a
   field access (introduced in version ``7.13.0``)
-  Fixed wrong garbage collection of an object only referenced by an
   immortal object

.. _java.lang.String: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html

SOAR
~~~~

-  Fixed the following compilation issues in ``if`` statement with BON constant:

   -  too many code may be removed when the block contains a ``while``
      loop
   -  potential ``Stacks merging coherence error`` may be thrown when the
      block contains a nested ``try-catch`` statement
   -  potential ``Stacks merging coherence error`` when declaring a
      ternary expression with `Constants.getBoolean()`_ in condition
      expression

-  Fixed ``assert`` statement removal when it is located at the end of a
   ``then`` block: the ``else`` block may be executed instead of jumping
   over
-  Removed names of arrays of basetype unless ``soar.generate.classnames`` option is set to ``true``
-  [Multi] - Fixed potential link exception when a Feature use one of the
   ``ej_bon_ByteArray`` methods
   (e.g. ``ej.kf.InvalidFormatException: code=51:ON_ej_bon_ByteArray_method_readUnsignedByte_AB_I_I``)
-  [Multi] - Fixed SOAR error (``Invalid SNI method``) when one of the
   `ej.bon.Constants.getXXX()`_ methods is declared in a ``kernel.api``
   file. This issue was preventing from using BON Constants in Feature
   code.

.. _Constants.getBoolean(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Constants.html#getBoolean-java.lang.String-
.. _ej.bon.Constants.getXXX(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Constants.html

Tools
~~~~~

-  Updated Code Coverage Analyzer report generation:

   -  Automatically configure ``src/main/java`` source directory
      beside a ``/bin`` directory if available
   -  Added an option (``cc.src.folders``) to specify the source directory
      (require SDK ``5.4.1`` or higher)
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

-  [Multi] - Fixed potential VM crash when declaring a Proxy class which
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

-  [Multi/x86/QNX7] - Fixed missing multi-sandbox version

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

The following set of VEE Port properties (customer defined) are
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
-  Fixed `java.lang.NullPointerException`_ thrown when
   `java.util.WeakHashMap.put()`_ method is called with a ``null`` key
   (introduced in version :ref:`7.11.0 <changelog-7.11.0>`)

.. _java.lang.NullPointerException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/NullPointerException.html
.. _java.util.WeakHashMap.put(): https://repository.microej.com/javadoc/microej_5.x/apis/java/util/WeakHashMap.html#put-K-V-

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
   `Object.clone()`_ method on an array in Feature mode

.. _tools-2:

Tools
~~~~~

-  Updated the serial PC connector to JSSC ``2.9.2`` (COM port could not be
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

-  Fixed unnecessary stacktrace dump on `Long.parseLong(...)`_ error
-  Fixed UTF-8 encoded Strings not correctly printed

.. _Long.parseLong(...): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Long.html#parseLong-java.lang.String-

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

-  Fixed Feature build script for SDK 5.x (introduced in version
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

-  Added a message to `IllegalArgumentException`_ thrown in an SNI call
   when passing a non-immortal array in SNI (only in case the VEE Port
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

-  Updated non-immortal array access from SNI default behavior (now
   allowed by default)
-  Fixed thread state displayed by ``LLMJVM_dump`` for threads in
   ``SLEEP`` state
-  Fixed ``sni.h`` header file function prototypes using the
   ``SNI_callback`` typedef
-  Fixed crash when an `OutOfMemoryError`_ is thrown while creating a
   native exception in SNI
-  [Multi] - Fixed runtime exceptions that can be implicitly thrown
   (such as `NullPointerException`_)
   which were not automatically exposed by the Kernel
-  [Multi] - Fixed passing Kernel array parameters through a shared
   interface method call. These parameters were passed by copy instead
   of by reference as specified by ``KF`` specification
-  [Multi] - Fixed execution context when jumping in a catch block of a
   `ej.kf.Proxy`_
   method (the catch block was executed in the Kernel context instead of the Feature context)
-  [ARMCC5] - Fixed link error
   ``Undefined symbol _java_Ljava_lang_OutOfMemoryError_field_OOMEMethodAddr_I``
   with ARM Compiler 5 linker (introduced in version :ref:`7.12.0 <changelog-7.12.0>`)

.. _NullPointerException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/NullPointerException.html
.. _IllegalArgumentException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalArgumentException.html
.. _ej.kf.Proxy: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html

.. _foundation-libraries-2:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``SNI`` to version ``1.4``
-  Updated internal library ``Resource-Manager-1.0`` as deprecated. Use
   ``SNI-1.4`` native resources instead
-  Updated `Thread.getId()`_
   method implementation to return the same value than ``SNI_getCurrentJavaThreadID()`` function
-  Optimized `SNI.toCString()`_
   method by removing a useless temporary buffer copy
-  Fixed ``EDC`` implementation of `String(byte[],int,int)`_
   constructor which could allocate a too large temporary buffer
-  Fixed ``EDC`` implementation of `Thread.interrupt()`_
   method to throw a `java.lang.SecurityException`_
   when the interrupted thread cannot be modified by the the current thread
-  Fixed ``EDC`` implementation to remove remaining references to
   `java.util.SecurityManager`_ class when it is disabled
-  Fixed ``EDC`` implementation of `Thread.interrupt()`_
   method that was declared ``final``
-  Fixed ``EDC`` API of `Thread.interrupt()`_
   to clarify the behavior of the method
-  Fixed ``EDC`` API of `java.util.Calendar`_
   method to specify that non-lenient mode is not supported
-  Fixed ``EDC`` API of `java.io.FilterInputStream.in`_ field to be
   marked ``@Nullable``

.. _Thread.getId(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.html#getId--
.. _SNI.toCString(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/sni/SNI.html#toCString-java.lang.String-byte:A-
.. _String(byte[],int,int): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html#String-byte:A-int-int-
.. _Thread.interrupt(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.html#interrupt--
.. _java.lang.SecurityException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/SecurityException.html
.. _java.util.SecurityManager: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/SecurityManager.html
.. _java.util.Calendar: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Calendar.html
.. _java.io.FilterInputStream.in: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/FilterInputStream.html#in

.. _integration-2:

Integration
~~~~~~~~~~~

-  Updated Architecture End User License Agreement to version
   ``SDK 3.0-B``

.. _simulator-1:

Simulator
~~~~~~~~~

-  Added ``SNI-1.4`` support, with the following new HIL engine APIs:

   -  Added methods ``NativeInterface.suspendStart()`` and
      ``NativeInterface.suspendStop()`` to notify the simulator that a
      native is suspended so that it can schedule a thread with a lower
      priority

-  Added ``KF`` support to dynamically install Features (``.fs3`` files)
-  Added the capability to specify the Kernel UID from an option (see
   options in ``Simulator`` > ``Kernel`` > ``Kernel UID``)
-  Added object size in generated ``.heap`` dump files
-  Optimized file accesses from the Application
-  Fixed crash in debug mode when paused on a breakpoint in SDK
   and hovering a Java variable with the mouse
-  Fixed potential crash in debug mode when putting a breakpoint in
   the SDK on a line of code declared in an inner class
-  Fixed potential crash in debug mode
   (`java.lang.NullPointerException`_) when a breakpoint set on a field
   access is hit
-  Fixed potential crash in debug mode
   (`ArrayIndexOutOfBoundsException`_)
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
-  Fixed `Thread.getState()`_ returning ``TERMINATED`` whereas the
   thread is running
-  Fixed Simulator which may not stop properly when closing the Front
   Panel window
-  Fixed Front Panel which stops sending widget events when dragging out
   of a widget
-  [Multi] - Fixed monitor that may not be released when an exception
   occurs in a synchronized block (introduced in version ``7.10.0``)
-  [Multi] - Fixed invalid heap dump generation that causes heap
   analyzer crash
-  [Multi] - Fixed potential crash (`java.lang.NullPointerException`_)
   in debug mode when debugging an Application (introduced in version
   :ref:`7.10.0 <changelog-7.10.0>`)
-  [Multi] - Fixed error when using ``KF`` library without defining a
   ``kernel.kf`` file in the Kernel (introduced in version :ref:`7.10.0 <changelog-7.10.0>`)

.. _ArrayIndexOutOfBoundsException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ArrayIndexOutOfBoundsException.html
.. _Thread.getState(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.html#getState--

.. _soar-3:

SOAR
~~~~

-  Added an option (``soar.bytecode.verifier``) to enable or disable the
   bytecode verifier (disabled by default)
-  Removed size related limits in Architecture Evaluation version

.. _tools-5:

Tools
~~~~~

-  Added ``SNI-1.4`` support to HIL engine
-  Updated Heap Dumper to verbose information about the memory section
   when an overlap is detected in the HEX file
-  Updated Memory Map Scripts (Security, DTLS, Device)
-  Fixed License Manager (Evaluation) random crash on Windows 10 when a
   VEE Port is built using ``Build Module`` button
-  Fixed License Manager (Evaluation) wrong UID computation after reboot
   when Windows 10 Hyper-V feature is enabled
-  Fixed HIL engine to exit as soon as the Simulator is disconnected
   (avoid remaining detached processes)
-  Fixed ELF to Map generating symbol addresses different from the ELF
   symbol addresses (introduced in version :ref:`7.11.0 <changelog-7.11.0>`)
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

-  Updated implementation of internal `OutOfMemoryError`_
   thrown with the maximum number of frames that can be dumped
-  Updated ``LLMJVM_dump()`` output with the following new information:

   -  Maximum number of alive threads
   -  Total number of created threads
   -  Maximum number of stack blocks used
   -  Current number of stack blocks used
   -  Objects referenced by each stack frame: address, type, length (in
      case of arrays), string content (in case of String objects)
   -  [Multi] - Kernel stale references with the name of the Feature
      stopped

.. _foundation-libraries-3:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Fixed ``EDC`` implementation of `Throwable.getStackTrace()`_ when
   called on a `OutOfMemoryError`_
   thrown by Core Engine or Simulator (either the returned stack trace array was empty or a
   `java.lang.NullPointerException`_ was thrown)
-  [Tiny] - Fixed ``EDC`` implementation of
   `StackTraceElement.toString()`_
   (removed the character ``.`` before the type)
-  [Multi] - Fixed ``KF`` implementation of `Feature.start()`_ 
   to throw an `ExceptionInInitializerError`_ 
   when an exception is thrown in a Feature clinit method

.. _Throwable.getStackTrace(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html#getStackTrace--
.. _StackTraceElement.toString(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/StackTraceElement.html#toString--
.. _Feature.start(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Feature.html#start--
.. _ExceptionInInitializerError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ExceptionInInitializerError.html

.. _simulator-2:

Simulator
~~~~~~~~~

-  Updated implementation of internal `OutOfMemoryError`_
   thrown with more than one frames dumped per thread

   -  By default the ``20`` top frames per thread are dumped. This can
      be modified using ``S3.OutOfMemoryErrorNbFrames`` system property

-  Fixed wrong parsing of an array of ``long`` when an element is
   declared with only 2 digits (e.g. ``25`` was parsed as ``2``)
-  Fixed error parsing of an array of ``byte`` when an element is
   declared with the unsigned hexadecimal notation (e.g. ``0xFF``)
   (introduced in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed crash when `ResourceBuffer.readString()`_
   is called on a String greater than ``63`` characters (introduced in version
   :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed code coverage ``.cc`` generation of classpath directories
-  Fixed crash during a GC when computing the references map of a
   complex method (an error message is dumped with the involved method
   name and suggest to increase the internal stack using
   ``S3.JavaMemory.ThreadStackSize`` system property)
-  [Multi] - Added validity check of Shared Interface declaration files
   (``.si``) according to ``KF`` specification
-  [Multi] - Fixed processing of Resource Buffers declared in Feature
   classpath

.. _ResourceBuffer.readString(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/ResourceBuffer.html#readString--

.. _soar-4:

SOAR
~~~~

-  Added a new option ``core.memory.oome.nb.frames`` to configure the
   maximum number of stack frames that can be dumped when an internal
   `OutOfMemoryError`_
   is thrown by Core Engine

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
   the UI Pack. This allow to build a VEE Port with a Front Panel
   (splash screen, basic I/O, …), even if it does not provide a MicroUI
   port. Moreover, the Front Panel framework API has been redesigned and
   is now distributed using the ``ej.tool.frontpanel.framework`` module
   instead of the legacy Eclipse classpath variable.

Known Issues
~~~~~~~~~~~~

- SOAR ``Internal SOAR error`` or  ``Stacks merging coherence error`` thrown when an ``if`` statement (being removed)
  is declared at the end of a ``try`` block:
  
  .. code-block:: java
      
      try {
         ...
         if (Constants.getBoolean(XXX)) { // constant resolved to false
            ... // code being removed
         }
      } catch (Exception e) {
	      ...
      }

.. _core-engine-7:

Core Engine
~~~~~~~~~~~

-  Added ``EDC-1.3`` support for daemon threads
-  Added ``BON`` support for `ej.bon.Util.newArray(T[],int)`_
-  [Multi/ARMCC5] - Fixed unused undefined symbol that prevent Keil
   MDK-ARM to link properly

.. _ej.bon.Util.newArray(T[],int): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Util.html#newArray-java.lang.Class-int-

.. _foundation-libraries-4:

Foundation Libraries
~~~~~~~~~~~~~~~~~~~~

-  Updated ``EDC`` to version ``1.3`` (see `EDC-1.3 API
   Changelog <https://repository.microej.com/5/artifacts/ej/api/edc/1.3.0/CHANGELOG-1.3.0.md>`__)

   -  Updated the implementation code for correct Null analysis
      detection (added assertions, extracted multiple field accesses
      into a local)
   -  Fixed `PrintStream.PrintStream(OutputStream, boolean)`_
      writer initialization
   -  Removed useless String literals in `java.lang.Throwable`_

-  Updated UTF-8 decoder to support Unicode code points
-  Updated ``BON`` to version ``1.4`` (see `BON-1.4 API
   Changelog <https://repository.microej.com/5/artifacts/ej/api/bon/1.4.0/CHANGELOG-1.4.0.md>`__)
-  Updated ``TRACE`` to version ``1.1``

   -  Added `ej.trace.Tracer.getGroupID()`_
   -  Added a BON Constant (``core.trace.enabled``) to remove trace
      related code when tracing is disabled

-  Fixed ``KF`` to call the registered
   `Thread.UncaughtExceptionHandler`_
   when an exception is thrown by the first Feature thread

.. _PrintStream.PrintStream(OutputStream, boolean): https://repository.microej.com/javadoc/microej_5.x/apis/java/io/PrintStream.html#PrintStream-java.io.OutputStream-boolean-
.. _java.lang.Throwable: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html
.. _ej.trace.Tracer.getGroupID(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/trace/Tracer.html#getGroupID--
.. _Thread.UncaughtExceptionHandler: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.UncaughtExceptionHandler.html

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
-  Added ``BON-1.4`` support for `ej.bon.Util.newArray()`_
-  Added Front Panel framework
-  Updated error message when reaching S3 simulator limits
-  Removed the ``Bootstrapping a Smart Software Simulator`` message when
   verbose mode in enabled
-  Fixed `Object.clone()`_ on an immutable object to return a new
   (mutable) object instead of an immutable one
-  Fixed `Object.clone()`_ crash when an OutOfMemory occurs
-  Fixed potential crash when calling an abstract method (some
   interfaces of the hierarchy were not taken into account - introduced
   in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed ``OutOfMemory`` errors even if the heap is not full (resources
   loaded from `Class.getResourceAsStream()`_
   and `ResourceBuffer`_ creation were taken into account in simulated heap
   memory - introduced in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed potential crash when a GC occurs while a `ResourceBuffer`_
   is opened (introduced in version :ref:`7.10.0 <changelog-7.10.0>`)
-  Fixed potential debugger hangs when an exception was thrown but not
   caught in the same method
-  [Multi] - Fixed wrong class loading in some cases
-  [Multi] - Fixed wrong immutable loading in some cases

.. _ej.bon.Util.newArray(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Util.html#newArray-java.lang.Class-int-
.. _Object.clone(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#clone--
.. _Class.getResourceAsStream(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getResourceAsStream-java.lang.String-
.. _ResourceBuffer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/ResourceBuffer.html

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
   in an Architecture or VEE Port folder)
-  Updated License Manager (Production) to support dongle recognition
   on macOS ``10.14`` (Mojave)
-  Fixed ELF To Map to produce correct sizes from an executable
   generated by IAR Embedded Workbench for ARM
-  Fixed Firmware Linker ``.ARM.exidx`` section generation (missing
   section link content)
-  Updated deployment files policy for VEE Ports in Workspace, in order
   to be more flexible depending on the C project layout. This also
   allows to deploy to the same C project different Applications built
   with different VEE Ports

   -  VEE Port configuration: in ``bsp/bsp.properties``, a new option
      ``output.dir`` indicates where the files are deployed by default

      -  Application (``microejapp.o``) and Runtime library
         (``microejruntime.a``) are deployed to ``${output.dir}/lib``.
         Architecture header files (``*.h``) are deployed to
         ``${output.dir}/inc/``
      -  When this option is not set, the legacy behavior is left
         unchanged (``project.file`` option in collaboration with
         ``augmentCProject`` scripts)

   -  Launch configuration: ``Device > Deploy`` options allow to override the default VEE Port configuration in order to deploy each file into a separate folder.

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

-  Fixed `Object.getClass()`_
   may return a Class instance owned by a Feature for type owned by the Kernel

.. _Object.getClass(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#getClass--

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
-  [Multi] - Updated implementation of `ej.kf.Kernel`_:
   all APIs taking a Feature argument now will throw a
   `java.lang.IllegalStateException`_ 
   when the Feature is not started

.. _ej.kf.Kernel: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html
.. _java.lang.IllegalStateException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalStateException.html

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
   VEE Port. (Used by SDK ``5.x`` when manipulating
   VEE Ports & Virtual Devices)

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
      -  `Feature.stop()`_ does not perform the safe kill. The
         application cannot be stopped unless it has correctly removed
         all its shared references.

   -  Not implemented:

      -  Dynamic Feature installation from
         `Kernel.install(java.io.InputStream)`_
      -  Execution Rules Runtime checks

.. _Feature.stop(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Feature.html#stop--
.. _Kernel.install(java.io.InputStream): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream-

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

Core Engine
~~~~~~~~~~~

-  Fixed `OutOfMemoryError`_
   thrown when allocating an object of the size of free memory in immortals heap

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
   explicit `java.lang.Runtime.gc()`_
-  Updated internal heap header for memory dump

.. _java.lang.Runtime.gc(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html#gc--

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

-  [Multi] - Updated ``BON`` library: a Timer owned by the Kernel can
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

-  Updated `ej.bon.Timer`_
   to schedule `ej.bon.TimerTask`_
   owned by multiple Features

.. _ej.bon.Timer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Timer.html
.. _ej.bon.TimerTask: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/TimerTask.html

.. _simulator-6:

Simulator
~~~~~~~~~

-  Fixed implementation of `Class.getResourceAsStream()`_ 
   to throw an `IOException`_ when the stream is closed

.. _IOException: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/IOException.html

.. _soar-8:

SOAR
~~~~

-  [GCC] - Fixed ``microejapp.o`` link with GCC 6.3

.. _tools-12:

Tools
~~~~~

-  Added a retry mechanism in the Testsuite Engine
-  Added a message to suggest increasing the JVM heap when an
   `OutOfMemoryError`_ occurs in the ``Firmware Linker`` tool
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
   HIL engine startup
-  Added dump of loaded classes when ``verbose`` option is enabled
-  Fixed `Runtime.freeMemory()`_ 
   call freeze when ``Emb Characteristics`` option is enabled
-  Fixed ShieldedPlug server error after interrupting a thread that is
   waiting for a database block
-  Fixed crash ``Access to a wrong reference`` in some cases
-  Fixed `java.lang.NullPointerException`_
   when interrupting a thread that has not been started
-  Fixed crash when closing an HIL engine connection in some cases
-  [Multi] - Fixed KF & Watchdog library link when
   ``Emb Characteristics`` option is enabled
-  [Multi] - Fixed XML Parsing error when ``Emb Characteristics`` option
   is enabled

.. _Runtime.freeMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Runtime.html#freeMemory--

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

-  Fixed `Runtime.freeMemory()`_
   call freeze when ``Emb Characteristics`` option is enabled
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
   `Thread.interrupt()`_
   anymore

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

[6.17.0] - 2017-10-10
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

-  Added support for `ej.bon.ResourceBuffer`_

.. _ej.bon.ResourceBuffer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/ResourceBuffer.html

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

-  Added a trace when `IllegalMonitorStateException`_
   is thrown on a ``monitorexit``

.. _IllegalMonitorStateException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalMonitorStateException.html

.. _tools-20:

Tools
~~~~~

-  Added property ``skip.mergeLibraries`` for Platform Builder.
-  Updated the serial PC connector to JSSC ``2.8.0``.

.. _simulator-12:

Simulator
~~~~~~~~~

-  Fixed unexpexted `java.lang.NullPointerException`_ in some cases

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

-  Optimized `java.lang.Runtime.gc()`_ (removed useless heap compaction
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

*Base version, included into SDK 4.1.*


..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
