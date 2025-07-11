.. _tutorial_optimize_memory_footprint:

Optimize the Memory Footprint of an Application
===============================================

Description
-----------

This training explains how to analyze the memory footprint of an application and provides a set of common rules aimed at optimizing both ROM and RAM footprint.

Intended Audience
-----------------

This training is designed for Java engineers and Firmware integrators who want to execute a MicroEJ Application on a memory-constrained device.

Prerequisites
-------------

To get the most out of this training, participants should have a good knowledge of Java programming language.

Introduction
------------

Usually, the application development is already started when the developer starts thinking about its memory footprint.
Before jumping into code optimizations, it is recommended to list every area of improvement and estimate for each area how much memory can be saved and how much effort it requires.

Without performing the memory analysis first, the developer might start working on a minor optimization that takes a lot of effort for little improvements. In contrast, he could work on a major optimization, allowing faster and bigger improvements.
Moreover, each optimization described hereafter may allow significant memory savings for an application while it may not be relevant for another application.

How to Analyze the Footprint of an Application
----------------------------------------------

This section explains the process of analyzing the footprint of a MicroEJ Application and the tools used during the analysis.

Suggested footprint analysis process:

1. Build the MicroEJ Application
2. Analyze ``SOAR.map`` with the :ref:`memorymapanalyzer`
3. Analyze ``soar/*.xml`` with an XML editor
4. Link the MicroEJ Application with the BSP
5. Analyze the map file generated by the third-party linker with a text editor

Footprint analysis tools:

- The :ref:`memorymapanalyzer` allows to analyze the memory consumption of different features in the RAM and ROM.
- The :ref:`heapdumper` allow to understand the contents of the Managed heap and find problems such as memory leaks.
- The `API Dependency Discoverer <https://github.com/MicroEJ/Tool-DependencyDiscoverer>`_  allows to analyze a piece of code to detect all its dependencies.

How to Analyze the Files Generated by the MicroEJ Linker
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The MicroEJ Application linker generates files useful for footprint analysis, such as the SOAR map file and the SOAR information file.
To understand how to read these files, please refer to the :ref:`outputfiles` documentation.

How to Analyze a Map File Generated by a Third-Party Linker
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A ``<firmware>.map`` file is generated by the C toolchain after linking the MicroEJ Application with the BSP.
This section explains how a map file generated by GCC is structured and how to browse it. The structure is not the same on every compiler, but it is often similar.

File Structure
^^^^^^^^^^^^^^

This file is composed of 5 parts:

- ``Archive member included to satisfy reference by file``. Each entry contains two lines. The first line contains the referenced archive file location and the compilation unit. The second line contains the compilation unit referencing the archive and the symbol called.	
- ``Allocating common symbols``. Each entry contains the name of a global variable, its size, and the compilation unit where it is defined.
- ``Discarded input sections``. Each entry contains the name and the size of a section that has not been embedded in the firmware.
- ``Memory Configuration``. Each entry contains the name of a memory, its address, its size, and its attributes.
- ``Linker script and memory map``. Each entry contains a line with the name and compilation unit of a section and one line per symbol defined in this section. Each of these lines contains the name, the address, and the size of the symbol.

Finding the Size of a Section or Symbol
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For example, to know the thread stacks' size, search for the ``.bss.vm.stacks.java`` section in the ``Linker script and memory map`` part. The size associated with the compilation unit is the size used by the thread stacks.

The following snippet shows that the ``.bss.vm.stacks.java`` section takes 0x800 bytes.

.. code-block::

 .bss.vm.stacks.java
                0x20014070      0x800 ..\..\..\..\..\..\..\.microej\CM4hardfp_GCC48\application\microejapp.o
                0x20014070                __icetea___6bss_6vm_6stacks_6java$$Base
                0x20014870                __icetea___6bss_6vm_6stacks_6java$$Limit

See :ref:`Core Engine Link <core_engine_link>` documentation for more information on Core Engine sections.

How to Reduce the Image Size of an Application
----------------------------------------------

Generic coding rules can be found in the following training: :ref:`improve_code_quality`.

This section provides additional coding rules and good practices to reduce the image size (ROM) of an application.

Application Resources
~~~~~~~~~~~~~~~~~~~~~

Resources such as images and fonts take a lot of memory.
For every ``.list`` file, make sure that it does not embed any unused resource.

Only resources declared in a ``.list`` file will be embedded.
Other resources available in the :ref:`application classpath <application.classpath.mapping>` will not be embedded and will not have an impact on the application footprint.

Fonts
^^^^^

Default Font
""""""""""""
 
By default, in a :ref:`MicroEJ Platform configuration <platform_configuration_creation>` project, a so-called system font is declared in the ``microui.xml`` file.

When generating the MicroEJ Platform, this file is copied from the configuration project to the actual MicroEJ Platform project. It will later be converted to binary format and linked with your MicroEJ Application, even if you use fonts different from the system font.

Therefore, you can comment the system font from the ``microui.xml`` file to reduce the ROM footprint of your MicroEJ Application if this one does not rely on the system font. Note that you will need to rebuild the MicroEJ Platform and then the application to benefit from the footprint reduction.

See the *Display Element* section of the :ref:`section_static_init` documentation for more information on system fonts.

Character Ranges
""""""""""""""""

When creating a font, you can reduce the list of characters embedded in the font at several development stages:

- On font creation: see the *Removing Unused Characters* section of :ref:`section.tool.fontdesigner` documentation.
- On application build: see the *Fonts* section of :ref:`chapter.microej.classpath` documentation.

Pixel Transparency
""""""""""""""""""

You can also make sure that the BPP encoding used to achieve transparency for your fonts do not exceed the following values:

- The pixel depth of your display device.
- The required alpha level for a good rendering of your font in the application.

See the *Fonts* section of :ref:`chapter.microej.classpath` documentation for more information on how to achieve that.

External Storage
""""""""""""""""

To save storage on internal flash, you can access fonts from an external storage device.

See the *External Resources* section of the :ref:`section_fontgen` documentation for more information on how to achieve that.

Internationalization Data
^^^^^^^^^^^^^^^^^^^^^^^^^

Implementation
""""""""""""""

MicroEJ provides the :ref:`Native Language Support (NLS) <chapter.nls>` library to handle internationalization.

See https://github.com/MicroEJ/Example-NLS for an example of the use of the NLS library.

External Storage
""""""""""""""""

The default NLS implementation fetches text resources from internal flash, but you can replace it with your own implementation to fetch them from another location.

See :ref:`section_externalresourceloader` documentation for additional information on external resources management.

Images
^^^^^^

Encoding
""""""""

If you are tight on ROM but have enough RAM and CPU power to decode PNG images on the fly, consider storing your images as PNG resources.
If you are in the opposite configuration (lots of ROM, but little RAM and CPU power), consider storing your images in raw format.

See :ref:`section_image_generator` documentation for more information on how to achieve that.

Color Depth (BPP)
"""""""""""""""""

Make sure to use images with a color depth not exceeding the one of your display to avoid the following issues:

- Waste of memory.
- Differences between the rendering on the target device and the original image resource.

External Storage
""""""""""""""""

To save storage on internal flash, the application can access the images from an external storage device.

See :ref:`section_externalresourceloader` documentation for more information on how to achieve that.

Application Code
~~~~~~~~~~~~~~~~

The following application code guidelines are recommended in order to minimize the size of the application:

- Check libraries versions and changelogs regularly. Latest versions may be more optimized.
- Avoid manipulating `String`_ objects:
  
  - For example, prefer using integers to represent IDs.
  - Avoid overriding `Object.toString()`_ for debugging purposes. This method will always be embedded even if it is not called explicitly.
  - Avoid using the :ref:`logging library <log_logging_library>` or ``System.out.println()``, use the :ref:`trace library <log_trace_library>` or the :ref:`message library <log_message_library>` instead. The logging library uses strings, while the trace and message libraries use integer-based error codes.
  - Avoid using the string concatenation operator (``+``), use an explicit `StringBuilder`_ instead. The code generated by the ``+`` operator is not optimal and is bigger than when using manual ``StringBuilder`` operations.

- Avoid manipulating wrappers such as `Integer`_ and `Long`_ objects, use primitive types instead. Such objects have to be allocated in Managed heap memory and require additional code for boxing and unboxing.
- Avoid declaring Java Enumerations (``enum``), declare compile-time constants of primitives types instead (e.g. ``static final int I = 0;``). 
  The Java compiler creates an `Enum`_ object  in the Managed heap for each enumeration item, as well as complex class initialization code.
- Avoid using the `service`_ library, use singletons or `Constants.getClass()`_ instead. The service library requires embedding class reflection methods and the type names of both interfaces and implementations.
- Avoid using the Java Collections Framework. This OpenJDK standard library has not been designed for memory constrained devices.
  
  - Use raw arrays instead of `List`_ objects. The `ArrayTools`_ class provides utility methods for common array operations.
  - Use `PackedMap`_ objects instead of `Map`_ objects. It provides similar APIs and features with lower Managed heap usage.

- Use `ej.bon.Timer`_ instead of deprecated ``java.util.Timer``. When both class are used, almost all the code is embedded twice.
- Use :ref:`BON constants <section.classpath.elements.constants>` in the following cases if possible:
  
  - when writing debug code or optional code, use the ``if (Constants.getBoolean()) { ... }`` pattern. That way, the optional code will not be embedded in the production firmware if the constant is set to ``false``.
  - replace the use of :ref:`System Properties <system_properties>` by BON constants when both keys and values are known at compile-time. System Properties should be reserved for runtime lookup. Each property requires embedding its key and its value as intern strings.

- Check for useless or duplicate synchronization operations in call stacks, in order reduce the usage of ``synchronized`` statements. Each statement generates additional code to acquire and release the monitor.
- Avoid declaring exit statements (``break``, ``continue``, ``throw`` or ``return``) that jump out of a ``synchronized`` block. At each exit point, additional code is generated to release the monitor properly.
- Avoid declaring exit statements (``break``, ``continue``, ``throw`` or ``return``) that jump out of a ``try/finally`` block. At each exit point, the code of the ``finally`` block is generated (duplicated). This also applies on every ``try-with-resources`` block since a ``finally`` block is generated to close the resource properly.
- Avoid overriding `Object.equals(Object)`_ and `Object.hashCode()`_, use ``==`` operator instead if it is sufficient. The :ref:`correct implementation of these methods <equals_hashcode>` requires significant code.
- Avoid calling ``equals()`` and ``hashCode()`` methods directly on ``Object`` references. Otherwise, the method of every embedded class which overrides the method will be embedded.
- Avoid creating inlined anonymous objects (such as ``new Runnable() { ... }`` objects), implement the interface in a existing class instead. Indeed, a new class is created for each inlined object. Moreover, each enclosed final variable is added as a field of this anonymous class.
- Avoid accessing a private field of a nested class. The Java compiler will generate a dedicated method instead of a direct field access. This method is called `synthetic`, and is identified by its name prefix: ``access$``.
- Replace constant arrays and objects initialization in ``static final`` fields by :ref:`immutables objects <section.classpath.elements.immutables>`. Indeed, initializing objects dynamically generates code which takes significant ROM and requires execution time.
- Check if some features available in software libraries are not already provided by the device hardware. For example, avoid using `java.util.Calendar`_ (full Gregorian calendar implementation) if the application only requires basic date manipulation provided by the internal real-time clock (RTC).

.. _Enum: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Enum.html
.. _String: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html
.. _Object.toString(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#toString--
.. _StringBuilder: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/StringBuilder.html
.. _Integer: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Integer.html
.. _Long: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Long.html
.. _service: https://repository.microej.com/modules/ej/library/runtime/service/
.. _Constants.getClass(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Constants.html#getClass-java.lang.String-
.. _List: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/List.html
.. _ArrayTools: https://repository.microej.com/javadoc/microej_5.x/apis/ej/basictool/ArrayTools.html
.. _PackedMap: https://repository.microej.com/javadoc/microej_5.x/apis/ej/basictool/map/PackedMap.html
.. _Map: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Map.html
.. _ej.bon.Timer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Timer.html
.. _Object.equals(Object): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#equals-java.lang.Object-
.. _Object.hashCode(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#hashCode--
.. _java.util.Calendar: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Calendar.html


MicroEJ Platform Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following configuration guidelines are recommended in order to minimize the size of the application:

- Check MicroEJ Architecture and Packs versions and changelogs regularly. Latest versions may be more optimized.
- Configure the Platform to use the :ref:`tiny <tinysandbox>` capability of the Core Engine. It reduces application code size by ~20%, provided that the application code size is lower than 256KB (resources excluded).
- Disable unnecessary modules in the ``.platform`` file. For example, disable the ``Image PNG Decoder`` module if the application does not load PNG images at runtime.
- Don't embed unnecessary :ref:`pixel conversion <display_pixel_conversion>` algorithms. This can save up to ~8KB of code size but it requires knowing the format of the resources used in the application.
- Select your embedded C compilation toolchain with care, prefer one which will allow low ROM footprint with optimal performance. Check the compiler options:
   
  - Check documentation for available optimization options (``-Os`` on GCC). These options can also be overridden per source file.
  - Separate each function and data resource in a dedicated section (``-ffunction-sections  -fdata-sections`` on GCC).
  
- Check the linker optimization options. The linker command line can be found in the project settings, and it may be printed during link.

  - Only embed necessary sections (``--gc-sections`` option on GCC/LD).
  - Some functions, such as the ``printf`` function, can be configured to only implement a subset of the public API (for example, remove ``-u _printf_float`` option on GCC/LD to disable printing floating point values).

- In the map file generated by the third-party linker, check that every embedded function is necessary. For example, hardware timers or HAL components may be initialized in the BSP but not used in the application. Also, debug functions such as :ref:`systemview` may be disconnected when building the production firmware.

Application Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

The following application configuration guidelines are recommended in order to minimize the size of the application:

- Disable class names generation by setting the ``soar.generate.classnames`` option to ``false``. Class names are only required when using Java reflection. In such case, the name of a specific class will be embedded only if is explicitly required. See :ref:`stripclassnames` section for more information.
- Remove UTF-8 encoding support by setting the ``cldc.encoding.utf8.included`` option to ``false``. The default encoding (``ISO-8859-1``) is enough for most applications.
- Remove ``SecurityManager`` checks by setting the ``com.microej.library.edc.securitymanager.enabled`` option to ``false``. This feature is only useful for Multi-Sandbox firmwares.

For more information on how to set an option, please refer to the :ref:`define_option` section.

.. _stripclassnames:

Stripping Class Names from an Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, when a Java class is used, its name is embedded too. A class is used when one of its methods is called, for example.
Embedding the name of every class is convenient when starting a new MicroEJ Application, but it is rarely necessary and takes a lot of ROM.
This section explains how to embed only the required class names of an application.

Removing All Class Names
^^^^^^^^^^^^^^^^^^^^^^^^

First, the default behavior is inverted by defining the :ref:`Application option <application_options>` ``soar.generate.classnames`` to ``false``.

For more information on how to set an option, please refer to the :ref:`define_option` section.

Listing Required Class Names
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Some class names may be required by an application to work properly.
These class names must be explicitly specified in a ``*.types.list`` file.

The code of the application must be checked for all uses of the `Class.forName()`_, `Class.getName()`_ and `Class.getSimpleName()`_ methods.
For each of these method calls, if the class name if absolutely required and can not be known at compile-time, add it to a ``*.types.list`` file. Otherwise, remove the use of the class name.

The following sections illustrates this on concrete use cases.

.. _Class.forName(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#forName-java.lang.String-
.. _Class.getName(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getName--
.. _Class.getSimpleName(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getSimpleName--

Case of Service Library
"""""""""""""""""""""""

The `ej.service.ServiceLoader`_ class of the `service`_ library is a dependency injection facility.
It can be used to dynamically retrieve the implementation of a service.

The assignment between a service API and its implementation is done in ``*.properties.list`` files. Both the service class name and the implementation class name must be embedded (i.e., added in a ``*.types.list`` file).

For example:

.. code-block::

	# example.properties.list
	com.example.MyService=com.example.MyServiceImpl

.. code-block::

	# example.types.list
	com.example.MyService
	com.example.MyServiceImpl

.. _ej.service.ServiceLoader: https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/ServiceLoader.html

Case of Properties Loading
""""""""""""""""""""""""""

Some properties may be loaded by using the name of a class to determine the full name of the property. For example: 

.. code-block:: java

	Integer.getInteger(MyClass.class.getName() + ".myproperty");

In this case, it can be replaced with the actual string. For example:

.. code-block:: java

	Integer.getInteger("com.example.MyClass.myproperty");

Case of Logger and Other Debugging Facilities
"""""""""""""""""""""""""""""""""""""""""""""

Logging mechanisms usually display the name of the classes in traces.
It is not necessary to embed these class names. The :ref:`stack_trace_reader` can decipher the output.

How to Reduce the Runtime Size of an Application
------------------------------------------------

You can find generic coding rules in the following training: :ref:`improve_code_quality`.

This section provides additional coding rules and good practices in order to reduce the runtime size (RAM) of an application.

Application Code
~~~~~~~~~~~~~~~~

The following application code guidelines are recommended in order to minimize the size of the application:

- Avoid using the default constructor of collection objects, use constructors that allow to set the initial capacity. For example, use the `ArrayList(int initialCapacity)`_ constructor instead of the `default one`_ which will allocate space for ten elements.
- Adjust the type of ``int`` fields (32 bits) according to the expected range of values being stored (``byte`` for 8 bits signed integers, ``short`` for 16 bits signed integers, ``char`` for 16 bits unsigned integers).
- When designing a generic and reusable component, allow the user to configure the size of any buffer allocated internally (either at runtime using a constructor parameter, or globally using a BON constant). That way, the user can select the optimal buffer size depending on his use-case and avoid wasting memory.
- Avoid allocating immortal arrays to call native methods, use regular arrays instead. Immortal arrays are never reclaimed and they are not necessary anymore when calling a native method.
- Reduce the maximum number of parallel threads. Each thread requires a dedicated internal structure and one or more stack blocks.
  
  - Avoid creating threads on the fly for asynchronous execution, use shared thread instances instead (`ej.bon.Timer`_, `Executor`_, `MicroUI.callSerially(Runnable)`_, ...). 

- When designing Graphical User Interface:
  
  - Avoid creating mutable images (`BufferedImage`_ instances) to draw in them and render them later, render graphics directly on the display instead. Mutable images require allocating a lot of memory from the images heap.
  - Make sure that your `Widget`_ hierarchy is as flat as possible (avoid any unnecessary `Container`_). Deep widget hierarchies take more memory and can reduce performance.

.. _ArrayList(int initialCapacity): https://repository.microej.com/javadoc/microej_5.x/apis/java/util/ArrayList.html#ArrayList-int-
.. _default one: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/ArrayList.html#ArrayList--
.. _Executor: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/concurrent/Executor.html
.. _MicroUI.callSerially(Runnable): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html#callSerially-java.lang.Runnable-
.. _BufferedImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html
.. _Widget: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html
.. _Container: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html

MicroEJ Platform Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following configuration guidelines are recommended in order to minimize the runtime size of the application:

- Check the size of the stack of each RTOS task. For example, 1.0KB may be enough for the Core Engine task but it can be increased to allow deep native calls. See :ref:`debugstackoverflows` section for more information.
- Check the size of the heap allocated by the RTOS (for example, ``configTOTAL_HEAP_SIZE`` for FreeRTOS).
- Check that the size of the back buffer matches the size of the display. Use a :ref:`partial buffer <section_display_partial>` if the back buffer does not fit in the RAM.

.. _debugstackoverflows:

Debugging Stack Overflows
^^^^^^^^^^^^^^^^^^^^^^^^^

If the size you allocate for a given RTOS task is too small, a stack overflow will occur. To be aware of stack overflows, proceed with the following steps when using FreeRTOS:

1. Enable the stack overflow check in ``FreeRTOS.h``:

.. code-block:: c

	#define configCHECK_FOR_STACK_OVERFLOW 1

2. Define the hook function in any file of your project (``main.c`` for example):

.. code-block:: c

	void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName) { }

3. Add a new breakpoint inside this function
4. When a stack overflow occurs, the execution will stop at this breakpoint

For further information, please refer to the `FreeRTOS documentation <https://www.freertos.org/Stacks-and-stack-overflow-checking.html>`_.

Application Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

The following application configuration guidelines are recommended in order to minimize the size of the application.

For more information on how to set an option, please refer to the :ref:`define_option` documentation.

Managed heap and Immortals Heap
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Configure the :ref:`immortals heap <option_immortal_heap>` option to be as small as possible. You can get the minimum value by calling `Immortals.freeMemory()`_ after the creation of all the immortal objects.
- Configure the :ref:`Managed heap <option_managed_heap>` option to fit the needs of the application. You can get it by using the :ref:`Heap Usage Monitoring Tool <heap_usage_monitoring>`.

.. _Immortals.freeMemory(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Immortals.html

Thread Stacks
^^^^^^^^^^^^^

- Configure the :ref:`maximum number of threads <option_number_of_threads>` option. This number can be known accurately by counting in the code how many ``Thread`` and ``Timer`` objects may run concurrently. You can call `Thread.getAllStackTraces()`_ or `Thread.activeCount()`_ to know what threads are running at a given moment.
- Configure the :ref:`number of allocated thread stack blocks <option_number_of_stack_blocks>` option. This can be done empirically by starting with a low number of blocks and increasing this number as long as the application throws a ``StackOverflowError``.
- Configure the :ref:`maximum number of blocks per thread <option_maximum_number_of_stack_blocks_per_thread>` option. The best choice is to set it to the number of blocks required by the most greedy thread. Another acceptable option is to set it to the same value as the total number of allocated blocks.
- Configure the :ref:`maximum number of monitors per thread <option_maximum_number_of_monitors_per_thread>` option. This number can be known accurately by counting the number of concurrent ``synchronized`` blocks. This can also be done empirically by starting with a low number of monitors and increasing this number as long as no exception occurs. Either way, it is recommended to set a slightly higher value than calculated.

.. _Thread.getAllStackTraces(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.html#getAllStackTraces--
.. _Thread.activeCount(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.html#activeCount--
 
Core Engine Dump
""""""""""""""""

The ``LLMJVM_dump()`` function declared in ``LLMJVM.h`` may be called to print information on alive threads such as their current and maximum stack block usage.
This function may be called from the application by exposing it in a :ref:`native function <sni_specification>`. See :ref:`vm_dump` section for usage.

More specifically, the ``Peak java threads count`` value printed in the dump can be used to configure the maximum number of threads.
The ``max_java_stack`` and ``current_java_stack`` values printed for each thread can be used to configure the number of stack blocks.

MicroUI Images Heap
^^^^^^^^^^^^^^^^^^^

- Configure the :ref:`images heap <images_heap>` to be as small as possible. You can compute the optimal size empirically. It can also be calculated accurately by adding the size of every image that may be stored in the images heap at a given moment. One way of doing this is to inspect every occurrence of `BufferedImage()`_ allocations and `ResourceImage`_ usage of ``loadImage()`` methods.

.. _BufferedImage(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#BufferedImage-int-int-
.. _ResourceImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
