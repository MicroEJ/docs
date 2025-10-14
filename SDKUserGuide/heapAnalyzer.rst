.. _heapdumper:

Heap Dumper & Heap Analyzer
===========================

Introduction
------------

Heap Dumper is a tool that takes a snapshot of the heap. Generated files
(with the ``.heap`` extension) are available in the application output
folder.

The Heap Analyzer is a set of tools to help developers understand the
contents of the Managed Heap and find problems such as memory leaks.
For its part, the Heap Analyzer plugin is able to open dump files. It
helps you analyze their contents thanks to the following features:

-  memory leaks detection

-  objects instances browse

-  heap usage optimization (using immortal or immutable objects)


The Heap
~~~~~~~~

The heap is a memory area used to hold Java objects created at runtime.
Objects persist in the heap until they are garbage collected. An object
becomes eligible for garbage collection when there are no longer any
references to it from other objects.

Heap Dump
~~~~~~~~~

A heap dump is an XML file that provides a snapshot of the heap contents
at the moment the file is created. It contains a list of all the
instances of both class and array types that exist in the heap. For each
instance, it records:

-  The time at which the instance was created

-  The thread that created it

-  The method that created it

For instances of class types, it also records:

-  The class

-  The values in the instance’s non-static fields

For instances of array types, it also records:

-  The type of the contents of the array

-  The contents of the array

For each referenced class type, it records the values in the static
fields of the class.

Heap Analyzer Tools
~~~~~~~~~~~~~~~~~~~

The Heap Analyzer is an Eclipse plugin that adds three tools to the
MicroEJ environment.

    +-----------------------+---------------+-------------------------------+
    | Tool name             | Number of     | Purpose                       |
    |                       | input files   |                               |
    +=======================+===============+===============================+
    | Heap Viewer           | 1             | Shows what instances are in   |
    |                       |               | the heap, when they were      |
    |                       |               | created, and attempts to      |
    |                       |               | identify problem areas        |
    +-----------------------+---------------+-------------------------------+
    | Progressive Heap      | 1 or more     | Shows how the number of       |
    | Usage                 |               | instances in the heap has     |
    |                       |               | changed over time             |
    +-----------------------+---------------+-------------------------------+
    | Compare               | 2             | Compares two heap dumps,      |
    |                       |               | showing which objects were    |
    |                       |               | created, or garbage           |
    |                       |               | collected, or have changed    |
    |                       |               | values                        |
    +-----------------------+---------------+-------------------------------+

Heap Dumper
------------

The Heap Dumper generates ``.heap`` files. There are two implementations:

1. **Integrated with the Simulator**: Dumps ``.heap`` files directly from the Managed Heap.
2. **Heap Dumper Tool**: Generates ``.heap`` files from ``.hex`` files, which must be retrieved from the device using tools like GDB.

Heap dumps should be performed after a call to `System.gc()`_ to exclude discardable objects.

Simulator
~~~~~~~~~

To generate a Heap dump of an application running on the Simulator:

1. Set the ``s3.inspect.heap`` application property to ``true``.
2. Update your application code to call the `System.gc()`_ method where you need a Heap dump.
3. Run the application on the Simulator.

When the `System.gc()`_ method is called:

- If called from the application, the ``.heap`` file is generated in the ``build/output/<fqnMainClass>/heapDump/`` folder of the project, where ``<fqnMainClass>`` is the Fully Qualified Name of the application's main class, e.g., ``com.mycompany.Main``.
- If called from a test class, the ``.heap`` file is generated in the ``build/testsuite/output/<buildDate>/bin/<fqnMainClass>/heapDump/`` folder of the project, where ``<fqnMainClass>`` is the Fully Qualified Name of the generated main class and ``<buildDate>`` is the test execution date, e.g., ``build/testsuite/output/20240625-1605-24/bin/com.mycompany._AllTests_MyTest/heapDump/``.

Device
~~~~~~

To generate a Heap dump of an application running on a device:

1. Update your application code to call the `System.gc()`_ method where you need a Heap dump.
2. Build the executable and deploy it on the device.
3. Start a debug session.
4. Add a breakpoint to the ``LLMJVM_on_Runtime_gc_done`` Core Engine hook. This function is called by the Core Engine when the `System.gc()`_ method is done. Alternatively, for out of memory errors, add a breakpoint to the ``LLMJVM_on_OutOfMemoryError_thrown`` Core Engine hook.
5. Resume execution until the breakpoint is reached. You are now ready to dump the memory. 

.. note::

   Core Engine hooks may be inlined by the third-party linker. If the symbol is not accessible to the debugger, declare them in your VEE Port:

   .. code:: c

      void LLMJVM_on_Runtime_gc_done(){
         //No need to add code to the function
      }

      void LLMJVM_on_OutOfMemoryError_thrown(){
         //No need to add code to the function
      }

Retrieve the ``.hex`` file from the device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you are in a Mono-Sandbox context, you only need to dump the Core Engine heap section. Example GDB commands:

.. code-block:: console
      
      b LLMJVM_on_Runtime_gc_done
      b LLMJVM_on_OutOfMemoryError_thrown
      continue
      dump ihex memory heap.hex &_java_heap_start &_java_heap_end

You now have the ``.hex`` file and need to extract the Heap dump.

In a Multi-Sandbox context, additionally dump the following sections:

- Installed features table:
  
  .. code-block:: console
   
      dump ihex memory &java_features_dynamic_start &java_features_dynamic_end

- Installed features sections specific to your VEE Port, depending on the :ref:`LLKERNEL implementation<LLKF-API-SECTION>`:
  
  .. code-block:: console
   
      dump ihex memory <installed_features_start_address> <installed_features_end_address>

To simplify the dump commands, consider:

- Dumping the entire memory where MicroEJ runtime and code sections are linked.
- Generating the :ref:`VEE memory dump script <generate_vee_memory_dump_script>` to dump all required sections.

.. note:: 
   If the heap is :ref:`dynamically configured at Core Engine startup<dynamic_heap_config>`, the correct method for retrieving a ``.hex`` file is by :ref:`Generating a VEE memory dump script<generate_vee_memory_dump_script>`.


Convert ``.hex`` dump to ``.heap`` dump
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To convert the Heap dump from ``.hex`` to ``.heap``, use the Heap Dumper tool.

The Heap Dumper should be available in your VEE Port and can be configured and executed from the SDK Run Configurations.

From the SDK top menu, go to ``Run`` > ``Run Configurations...``

1. Right-click on ``MicroEJ Tool`` and select ``New Configuration``.

2. Configure the ``Execution`` tab:

   1. Set the tool name, e.g., ``Convert Hex to Heap``.
   2. Select the platform in the ``Target`` > ``Platform`` field.
   3. Select the ``Heap Dumper`` tool from the ``Execution`` > ``Settings`` list.
   4. Set the ``Output folder`` path, where the ``.heap`` file will be generated.
   
   .. figure:: images/heapdumper_options/tool_heapdumper_execution_tab.png
      :scale: 50%
      :align: center



3. Switch to the ``Configuration`` tab and configure it:

   1. Set the path to the firmware executable ELF file.
   2. Add the full path of application files with debug information (``.fodbg`` files).
   3. Set the full path of the heap memory dump, in Intel Hex format.
   4. Add the full path of additional memory files in Intel Hex format (installed feature areas, dynamic features table, etc.).
   5. Set the heap file output name, e.g., ``application.heap``.

   .. figure:: images/heapdumper_options/tool_heapdumper_config_tab.png
      :scale: 50%
      :align: center

4. Finally, click ``Apply`` and ``Run``.

Now you can open the generated ``.heap`` file in the Heap Viewer.

.. _heapviewer:

Heap Viewer
-----------

To open the Heap Viewer tool, select a heap dump XML file in the :guilabel:`Package
Explorer`, right-click on it and select :guilabel:`Open With` > :guilabel:`Heap Viewer`

Alternatively, right-click on it and select :guilabel:`Heap Analyzer` > :guilabel:`Open heap viewer`

This will open a Heap Viewer tool window for the selected heap dump [1]_.

The Heap Viewer works in conjunction with two views:

1. The Outline view

2. The Instance Browser view

These views are described below.

The Heap Viewer tool has three tabs, each described below.

.. [1]
   Although this is an Eclipse ‘editor’, it is not possible to edit the
   contents of the heap dump.

Outline View
~~~~~~~~~~~~

The Outline view shows a list of all the types in the heap dump, and for
each type shows a list of the instances of that type. When an instance
is selected it also shows a list of the instances that refer to that
instance. The Outline view is opened automatically when an Heap Viewer
is opened.

.. figure:: images/outline-view.png
   :alt: Outline View
   :align: center
   :width: 882px
   :height: 408px

   Outline View

Instance Browser View
~~~~~~~~~~~~~~~~~~~~~

The Instance Browser view opens automatically when a type or instance is
selected in the Outline view. It has two modes, selected using the
buttons in the top right corner of the view. In ‘Fields’ mode it shows
the field values for the selected type or instance, and where those
fields hold references it shows the fields of the referenced instance,
and so on. In ‘Reference’ mode it shows the instances that refer to the
selected instance, and the instances that refer to them, and so on.

.. figure:: images/fields-and-ref-showing-fields.png
   :alt: Instance Browser View - Fields mode
   :align: center
   :width: 588px
   :height: 268px

   Instance Browser View - Fields mode

.. figure:: images/fields-and-ref-showing-refs.png
   :alt: Instance Browser View - References mode
   :align: center
   :width: 586px
   :height: 248px

   Instance Browser View - References mode

Heap Usage Tab
~~~~~~~~~~~~~~

The Heap usage page of the Heap Viewer displays four bar charts. Each
chart divides the total time span of the heap dump (from the time stamp
of the earliest instance creation to the time stamp of the latest
instance creation) into a number of  periods along the x axis, and
shows, by means of a vertical bar, the number of instances created
during the period.

-  The top-left chart shows the total number of instances created in
   each period, and is the only chart displayed when the Heap Viewer is
   first opened.

-  When a type or instance is selected in the Outline view the top-right
   chart is displayed. This chart shows the number of instances of the
   selected type created in each time period.

-  When an instance is selected in the Outline view the bottom-left
   chart is displayed. This chart shows the number of instances created
   in each time period by the thread that created the selected instance.

-  When an instance is selected in the Outline view the bottom-right
   chart is displayed. This chart shows the number of instances created
   in each time period by the method that created the selected instance.

.. figure:: images/heap-usage-tab.png
   :alt: Heap Viewer - Heap Usage Tab
   :align: center
   :width: 709px
   :height: 568px

   Heap Viewer - Heap Usage Tab

Clicking on the graph area in a chart restricts the Outline view to just
the types and instances that were created during the selected time
period. Clicking on a chart but outside of the graph area restores the
Outline view to showing all types and instances  [2]_.

The button Generate graphViz file in the top-right corner of the Heap
Usage page generates a file compatible with graphviz (www.graphviz.org).

The section :ref:`heap_usage_monitoring` shows how to compute the maximum
heap usage.

.. [2]
   The Outline can also be restored by selecting the All types and
   instances option on the drop-down menu at the top of the Outline
   view.

Dominator Tree Tab
~~~~~~~~~~~~~~~~~~

The Dominator tree page of the Heap Viewer allows the user to browse the
instance reference tree which contains the greatest number of instances.
This can be useful when investigating a memory leak because this tree is
likely to contain the instances that should have been garbage collected.

The page contains two tree viewers. The top viewer shows the instances
that make up the tree, starting with the root. The left column shows the
ids of the instances – initially just the root instance is shown. The
Shallow instances column shows the number of instances directly
referenced by the instance, and the Referenced instances column shows
the total number of instances below this point in the tree (all
descendants).

The bottom viewer groups the instances that make up the tree either
according to their type, the thread that created them, or the method
that created them.

Double-clicking an instance in either viewer opens the Instance Browser
view (if not already open) and shows details of the instance in that
view.

.. figure:: images/dominator-tree-tab.png
   :alt: Heap Viewer - Dominator Tree Tab
   :align: center
   :width: 708px
   :height: 566px

   Heap Viewer - Dominator Tree Tab

Leak Suspects Tab
~~~~~~~~~~~~~~~~~

The Leak suspects page of the Heap Viewer shows the result of applying
heuristics to the relationships between instances in the heap to
identify possible memory leaks.

The page is in three parts.

-  The top part lists the suspected types (classes). Suspected types are
   classes which, based on numbers of instances and instance creation
   frequency, may be implicated in a memory leak.

-  The middle part lists accumulation points. An accumulation point is
   an instance that references a high number of instances of a type that
   may be implicated in a memory leak.

-  The bottom part lists the instances accumulated at an accumulation
   point.

.. figure:: images/leak-suspects-tab.png
   :alt: Heap Viewer - Leak Suspects Tab
   :align: center
   :width: 709px
   :height: 567px

   Heap Viewer - Leak Suspects Tab

Progressive Heap Usage
----------------------

To open the Progressive Heap Usage tool, select one or more heap dump
XML files in the :guilabel:`Package Explorer`, right-click and select :guilabel:`Heap Analyzer` > :guilabel:`Show progressive heap usage`

This tool is much simpler than the Heap Viewer described above. It
comprises three parts.

-  The top-right part is a line graph showing the total number of
   instances in the heap over time, based on the creation times of the
   instances found in the heap dumps.

-  The left part is a pane with three tabs, one showing a list of types
   in the heap dump, another a list of threads that created instances in
   the heap dump, and the third a list of methods that created instances
   in the heap dump.

-  The bottom-left is a line graph showing the number of instances in
   the heap over time restricted to those instances that match with the
   selection in the left pane. If a type is selected, the graph shows
   only instances of that type; if a thread is selected the graph shows
   only instances created by that thread; if a method is selected the
   graph shows only instances created by that method.

.. figure:: images/progressive.png
   :alt: Progressive Heap Usage
   :align: center
   :width: 710px
   :height: 568px

   Progressive Heap Usage

Compare Heap Dumps
------------------

The Compare tool compares the contents of two heap dump files. To open
the tool select two heap dump XML files in the Package Explorer,
right-click and select :guilabel:`Heap Analyzer` > :guilabel:`Compare`

The Compare tool shows the types in the old heap on the left-hand side,
and the types in the new heap on the right-hand side, and marks the
differences between them using different colors.

Types in the old heap dump are colored red if there are one or more
instances of this type which are in the old dump but not in the new
dump. The missing instances have been garbage collected.

Types in the new heap dump are colored green if there are one or more
instances of this type which are in the new dump but not in the old
dump. These instances were created after the old heap dump was written.

Clicking to the right of the type name unfolds the list to show the
instances of the selected type.

.. figure:: images/compare-all.png
   :alt: Compare Heap Dumps
   :align: center
   :width: 712px
   :height: 544px

   Compare Heap Dumps

The combo box at the top of the tool allows the list to be restricted in
various ways:

-  All instances – no restriction.

-  Garbage collected and new instances – show only the instances that
   exist in the old heap dump but not in the new dump, or which exist in
   the new heap dump but not in the old dump.

-  Persistent instances – show only those instances that exist in both
   the old and new dumps.

-  Persistent instances with value changed – show only those instances
   that exist in both the old and new dumps and have one or more
   differences in the values of their fields.

Instance Fields Comparison View
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Compare tool works in conjunction with the Instance Fields
Comparison view, which opens automatically when an instance is selected
in the tool.

The view shows the values of the fields of the instance in both the old
and new heap dumps, and highlights any differences between the values.

.. figure:: images/compare-fields.png
   :alt: Instance Fields Comparison view
   :align: center
   :width: 715px
   :height: 480px

   Instance Fields Comparison view


.. _System.gc(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#gc--

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
