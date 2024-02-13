.. _tutorials_debug_gui_performances:

How to Validate GUIs
====================

This document explains how to validate Graphical User Interfaces. 
It describes common pitfalls that can affect GUI performances, provides tools that allow to detect performance issues and how to solve them, 
and finally offers ways to test GUIs automatically.

Implementing GUIs Efficiently
------------------------------

Before using more advanced UI debugging techniques, the global application code quality should be reviewed. An overall good code quality will help to get good UI performances. It will help to get more efficient code and allow easier debugging and maintenance.

Documents and Tools to Improve Application Code Quality
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is a list of documents or tools that help to improve the quality of application code:

- The :ref:`Improve the Quality of Java Code<improve_code_quality>` tutorial explains how to improve the Quality of Java Code.
- The :ref:`Get Started With GUI<tutorial_get_started_with_gui>` tutorial provides guidelines to start developing an efficient GUI.
- The `SonarQube™ <https://github.com/MicroEJ/ExampleTool-Sonar>`_ source code quality analyzer allows to analyze an Application or Library code quality.

Using Recent Versions of UI Libraries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using the latest UI libraries (MicroUI, MWT, Widget, etc.) available may solve some performance issues. The most recent UI libraries fix some bugs that may affect performance and they provide tools and libraries that allow to implement more performant UIs.

Memory Management
~~~~~~~~~~~~~~~~~

The Java management of memory may affect UI performances:

- Too much memory allocation/deallocation for UI resources (Images, Fonts).
- Too much object instantiation will lead to a big Java heap size. In some use cases, the garbage collection may lead to the UI slowing down.

To avoid those pitfalls:

- Calibrate the memories (Java heap, Images heap, etc.).
- Uses memory debugging tools:

  - :ref:`Optimize Memory Footprint<tutorial_optimize_memory_footprint>` tutorial.
  - :ref:`Memory inspection tools<tutorial_discover_embedded_debugging_techniques.tools.memory_inspection>`.
  - :ref:`Heap Analyzer<heapdumper>`.

Format of UI Resources
~~~~~~~~~~~~~~~~~~~~~~

One crucial aspect of optimizing an application is choosing the right image formats. Images can have a significant impact on an app's performance and memory usage. Therefore, selecting the best image format is essential. It helps reduce memory usage, speed up the app, and improve its overall performance. 

MicroUI manages two kind of images, mutable and immutable images.

Mutable images are graphical resources that can be created and modified at runtime. The application can draw into such images. More information about mutable images can be found :ref:`here<section_mutable_images>`.

As their name suggests, immutable images can not be modified. They are the most commonly used kind of images, this section will focus on them.

Decoding Immutable Images
*************************

Immutable images can be converted for display either during the build-time process, using the Image Generator, or at run-time, utilizing the appropriate decoder library.

The decision between these two approaches depends on the project's specific requirements. **Decoding at run-time** is a good choice when storage space is limited and offers greater flexibility. However, it may require more processing power and result in slower performance. Conversely, **decoding at build time** reduces the computational workload during run-time and is well-suited for devices with stringent performance demands, though it usually require more storage and it may sacrifice some flexibility in the process.

Format of Immutable Images
**************************

There are multiple output formats that can be used to convert the images, you can find them here: :ref:`Output Formats<section_image_standard_output>`.

Choosing the right output format is important to get the best performance:

- For opaque images, choose a format that has no transparency, RGB565 is usually sufficient.
- For a pictogram to colorize A4 is usually sufficient. The image can be colorized at runtime.
- The image format can be compressed, see :ref:`Compressed Output Formats<section_image_rle_output>`

The expected result of each format can be seen here: :ref:`Formats expected result<section_image_expected_result>`

Images Heap
***********

Mutable images and immutable images decoded at runtime require some memory to be used. Please go to the :ref:`Images Heap<images_heap>` section for more information. 

Benchmarking GUIs
-----------------

The process of rendering a frame of the UI consists of several parts:

- Drawing of the UI:

  - MWT processing (layout of widgets and widget rendering process).
  - Drawing of the UI (MicroUI drawing method execution).

- Display flush.
- (depends on the UI port) Backbuffer copy, see :ref:`Display Buffer Modes<section_display_policies>`.

Some tools are available to identify which part of this process affect the most the GUI performance.

SystemView
~~~~~~~~~~

The SystemView tool can be used to trace the UI actions (drawings, flush, etc.) and detect which ones are the most time-consuming. The documentation of SystemView is available :ref:`here<systemview>`. The MicroUI traces should be configured in SystemView in order to see the UI actions performed, it can be done by following :ref:`this documentation<microui_traces>`. Custom traces can be added and logged from the Java application to record specific actions.

MicroUI Flush Visualizer
~~~~~~~~~~~~~~~~~~~~~~~~

A perfect application has 100% of its display area drawn. This is the total area covered by the sum of the area drawn by the drawing operations. A value of 200% indicates the area drawn is equivalent to twice the surface of the entire display. A total area drawn between 100% to 200% is the norm in practice because widgets often overlap. However, if the total area drawn is bigger than 200%, that means that the total surface of the display was drawn more than twice, meaning that a lot of time could be spent drawing things that are never shown.

The MicroUI Flush Visualizer tool can be used to investigate potential performance bottlenecks in UI applications running on the Simulator by showing the pixel surface drawn between two MicroUI frame buffer flushes.

The documentation of MicroUI Flush Visualizer is available :ref:`here<microuiflushvisualizer>`.


Debugging GUIs
--------------

High-level Debugging and Optimizations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section provides insights into common issues affecting performances on the high-level side. The following advices will help reduce the MWT processing and drawing time.

Widget Hierarchy and Layout
***************************

Keeping the widget hierarchy as simple as possible will help to reduce the "MWT processing" part time. Improving the widget hierarchy design may help reduce the number of widgets or the number of them that are rendered when a certain part of the UI is updated.

Here are tools that allow to detect issues with the widget hierarchy:

- :ref:`Widget debug utilities<widget_library_debug_utilities>` provides tools to visualize the widget tree, count the numbers of widgets or see their bounds.
- :ref:`MWT bounds highlighting<mwt_how_to_debug>` allows to visualize the bounds of the widgets, it is useful to detect overlapping widgets.

Bad Use of requestRender and requestLayout
******************************************

The ``requestRender`` method requests a render of the widget on the display.

The ``requestLayout`` method requests a layout of all the widgets in the sub-hierarchy of this widget. It will compute the size and position of the widgets as setting their styles. ``requestLayout`` will trigger a render request after the layout.

A common mistake is to call ``requestRender`` just after a ``requestLayout``. This will trigger two renders and thus affect the UI performances.

Another common issue is to request a layout where a render request would have been enough. If the size, position or style of the widgets didn't change ``requestRender`` is enough, ``requestLayout`` would have a longer processing time. This is especially true for animation where we want each frame to be processed as fast as possible.

Documentation about rendering and layout is available :ref:`here<mwt_concepts>`.

Animations Implementation
*************************

There are a few implementations possible for animations with MicroEJ. The way widgets are animated should be chosen according to the use case and the limitation of the hardware.

Animator
++++++++

The MWT's `Animator <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animator.html>`_ allows to execute animations as fast as possible, it waits for the low-level screen flush to be done and directly triggers a new render. Thus the Animator will give the best framerate possible but will also consume a lot of CPU processing time.

TimerTask
+++++++++

A TimerTask can be used to execute an animation at a fixed framerate. This technique is very useful to set a fixed period for the animation but will cause issues if the time to render a frame is longer than that period, this will lead to missed frames. Some frames can take longer to render if their content is more complex or if the CPU is already used by another non-UI thread.

The framerate set when using a TimerTask for animation should be defined wisely, the time to render frames and the CPU utilization should be taken into consideration.

Animator and TimerTask mix
++++++++++++++++++++++++++

A mix of the Animator and TimeTask approaches could be implemented in order to set a fixed framerate but also to rely on the screen flush.

Hardware and Low-level Debugging and Optimizations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section provides insights into the main spots to check regarding the low-level and the hardware.

Please see the VEE Porting Guide :ref:`Graphical User Interface<pack_gui>` documentation for more information about the UI port.

At Project Level
****************

Compiling Optimization Options
++++++++++++++++++++++++++++++

The project should be configured to bring the best performances with compiling optimization options correctly set up.

RTOS Tasks Environment
++++++++++++++++++++++

The priority of the UI task should be set high enough to avoid too many preemptions that may induce bad UI performances.

Another point that should be taken into consideration is the amount of other tasks that are running at the same time as the UI task.
The total workload may be too high for the CPU, therefore, the UI task cannot get access to the required amount of computing power.

At Hardware Level
*****************

Hardware Capabilities
+++++++++++++++++++++

MCUs and SoCs may have access to various hardware IPs to speed up the UI. The UI port should exploit all of them to get the best performance.
First of all, the GPU should be used if it is available on the system.
Then, driving a display implies intensive memory usage, a DMA should be used whenever it's possible.

For example, during the back copy if the flush policy is in switch mode or during your flush if your display is driven through SPI (if there is a DMA dedicated to the SPI port).
For more information about the flush policy, please read our documentation about :ref:`section_display`.

Hardware Configuration
++++++++++++++++++++++

Each of the hardware components such as SPI, DMA or LCD controller must be configured to bring the best performances achievable.
This implies to read carefully the datasheet of the MCU and the display and determine for example the best frequency and communication mode possible.

Another example of configuration with DMAs, a DMA has often a burst mode to transfer data, the UI port should use this mode to maximize performance.

Buffers Location in Memory
++++++++++++++++++++++++++

An important step during the development of the UI integration is the memory location of the buffers that will use the GUI to draw to the display.
In an MCU, there may be different types of RAM available that have different properties in terms of quantity and speed.
The fastest RAM should be chosen for the buffers if its size allows it.

Flush Policy
************

As described in the :ref:`section_display` page, there are several flush policies that can be implemented.
The best flush policy should be selected according to the hardware capabilities. Generally, the best flush policy is the switch mode.


Testing GUIs
------------

Before applying UI debugging or optimization techniques, the application behaviour should be tested. There are different ways of doing this.

Test a GUI Application with a Software Robot
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possible to test the GUI of an application via robotic process automation (RPA).
Robot tests mimic the human user behavior in the GUI and can help detect various errors by
automating behavior which otherwise would cost too much effort and/or time to execute manually. 

Here are the steps required to use a robot in the MicroEJ environment:

- Record the robot input events

  - For this, you need a simple EventHandler which intercepts incoming events, for example from a Pointer, then passes them on to the real event handler.

- Start the usage of the new 'Watcher' logic after the UI has started

  - With this, the watching of the Pointer envents is initiated for the whole application.   

- Create a Robot

  - The robot is a simple class which uses its own Pointer to move and press at the coordinates it has been instructed.  
  - The robot should have a method which starts a series of instructions to move the Pointer.

- Execute the Robot method containing the instructions

  - The intercepting Event Handling will record and for example log the input.   

This simple way of automating GUI actions can be used to carry out real use cases and evaluate the results.

The :ref:`How to test a GUI application with a (software) robot<tutorials_software_robot>` tutorial provides detailed insight into this topic. 

Test a GUI Application with the Test Automation Tool
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To execute regression tests automatically and monitor minor changes in a GUI, you can use the `Test Automation <https://github.com/MicroEJ/Tool-UITestAutomation>`_ Tool.
The Test Automation Tool allows to automatically test UIs.

The tool comparison functionality can be integrated with JUnit tests.

For detailed information about the tool usage, please 
check the `README <https://github.com/MicroEJ/Tool-UITestAutomation/blob/master/TestAutomationTool/README.md>`_ in the repository.


..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

