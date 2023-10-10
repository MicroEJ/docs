.. _tutorials_debug_gui_performances:

How to Debug GUI Performance Issues
===================================

This document explains how to debug Graphical User Interface performance issues. It describes common pitfalls that can affect GUI performances, provides tools that allow to detect performance issues causes and how to solve them.

General good coding practices
-----------------------------

Before using more advanced UI debugging techniques, the global application code quality should be reviewed. An overall good code quality will help to get good UI performances. It will help to get more efficient code and allow easier debugging and maintenance.

Documents and tools to improve application code quality
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is a list of documents or tools that help to improve the quality of application code:

- The :ref:`Improve the Quality of Java Code<improve_code_quality>` tutorial explains how to improve the Quality of Java Code.
- The :ref:`Get Started With GUI<tutorial_get_started_with_gui>` tutorial provides guidelines to start developing an efficient GUI.
- The `SonarQube™ <https://github.com/MicroEJ/ExampleTool-Sonar>`_ source code quality analyzer allows to analyze an Application or Library code quality.

Using recent versions of UI libraries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using the latest UI libraries (MicroUI, MWT, Widget, etc.) available may solve some performance issues. The most recent UI libraries fix some bugs that may affect performance and they provide tools and libraries that allow to implement more performant UIs.

Memory management
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

Identifying the causes of bad performances
------------------------------------------

The process of rendering a frame of the UI consists of several parts:

- Drawing of the UI:

  - MWT processing (layout of widgets and widget rendering process).
  - Drawing of the UI (MicroUI drawing method execution).

- Display flush.
- (depends on the UI port) Backbuffer copy, see :ref:`Display Buffer Modes<section_display_modes>`.

Some tools are available to identify which part of this process affect the most the GUI performance.

SystemView
~~~~~~~~~~

The SystemView tool can be used to trace the UI actions (drawings, flush, etc.) and detect which ones are the most time-consuming. The documentation of SystemView is available :ref:`here<systemview>`. The MicroUI traces should be configured in SystemView in order to see the UI actions performed, it can be done by following :ref:`this documentation<microui_traces>`. Custom traces can be added and logged from the Java application to record specific actions.

MicroUI Flush Visualizer
~~~~~~~~~~~~~~~~~~~~~~~~

A perfect application has 100% of its display area drawn. This is the total area covered by the sum of the area drawn by the drawing operations. A value of 200% indicates the area drawn is equivalent to twice the surface of the entire display. A total area drawn between 100% to 200% is the norm in practice because widgets often overlap. However, if the total area drawn is bigger than 200%, that means that the total surface of the display was drawn more than twice, meaning that a lot of time could be spent drawing things that are never shown.

The MicroUI Flush Visualizer tool can be used to investigate potential performance bottlenecks in UI applications running on the Simulator by showing the pixel surface drawn between two MicroUI frame buffer flushes.

The documentation of MicroUI Flush Visualizer is available :ref:`here<microuiflushvisualizer>`.

High-level debugging and optimizations
--------------------------------------

This section provides insights into common issues affecting performances on the high-level side. The following advices will help reduce the MWT processing and drawing time.

Format of UI resources
~~~~~~~~~~~~~~~~~~~~~~

Choosing the best resource format will reduce memory consumption and drawing time.

:ref:`This documentation<section_image_display_output>` explains the different image formats.

Storing UI resources in the fastest memory (internal flash or RAM) will also affect greatly performances.

Widget hierarchy and layout
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Keeping the widget hierarchy as simple as possible will help to reduce the "MWT processing" part time. Improving the widget hierarchy design may help reduce the number of widgets or the number of them that are rendered when a certain part of the UI is updated.

Here are tools that allow to detect issues with the widget hierarchy:

- :ref:`Widget debug utilities<widget_library_debug_utilities>` provides tools to visualize the widget tree, count the numbers of widgets or see their bounds.
- :ref:`MWT bounds highlighting<mwt_how_to_debug>` allows to visualize the bounds of the widgets, it is useful to detect overlapping widgets.

Bad use of requestRender and requestLayout
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``requestRender`` method requests a render of the widget on the display.

The ``requestLayout`` method requests a layout of all the widgets in the sub-hierarchy of this widget. It will compute the size and position of the widgets as setting their styles. ``requestLayout`` will trigger a render request after the layout.

A common mistake is to call ``requestRender`` just after a ``requestLayout``. This will trigger two renders and thus affect the UI performances.

Another common issue is to request a layout where a render request would have been enough. If the size, position or style of the widgets didn't change ``requestRender`` is enough, ``requestLayout`` would have a longer processing time. This is especially true for animation where we want each frame to be processed as fast as possible.

Documentation about rendering and layout is available :ref:`here<mwt_concepts>`.

Animations implementation
~~~~~~~~~~~~~~~~~~~~~~~~~

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

Hardware and low-level debugging and optimizations
--------------------------------------------------

This section provides insights into the main spots to check regarding the low-level and the hardware.

Please see the VEE Porting Guide :ref:`Graphical User Interface<pack_gui>` documentation for more information about the UI port.

At project level
~~~~~~~~~~~~~~~~

Compiling optimization options
++++++++++++++++++++++++++++++

The project should be configured to bring the best performances with compiling optimization options correctly set up.

RTOS tasks environment
++++++++++++++++++++++

The priority of the UI task should be set high enough to avoid too many preemptions that may induce bad UI performances.

Another point that should be taken into consideration is the amount of other tasks that are running at the same time as the UI task.
The total workload may be too high for the CPU, therefore, the UI task cannot get access to the required amount of computing power.

At hardware level
~~~~~~~~~~~~~~~~~

Hardware capabilities
+++++++++++++++++++++

MCUs and SoCs may have access to various hardware IPs to speed up the UI. The UI port should exploit all of them to get the best performance.
First of all, the GPU should be used if it is available on the system.
Then, driving a display implies intensive memory usage, a DMA should be used whenever it's possible.

For example, during the back copy if the flush policy is in switch mode or during your flush if your display is driven through SPI (if there is a DMA dedicated to the SPI port).
For more information about the flush policy, please read our documentation about :ref:`section_display`.

Hardware configuration
++++++++++++++++++++++

Each of the hardware components such as SPI, DMA or LCD controller must be configured to bring the best performances achievable.
This implies to read carefully the datasheet of the MCU and the display and determine for example the best frequency and communication mode possible.

Another example of configuration with DMAs, a DMA has often a burst mode to transfer data, the UI port should use this mode to maximize performance.

Buffers location in memory
++++++++++++++++++++++++++

An important step during the development of the UI integration is the memory location of the buffers that will use the GUI to draw to the display.
In an MCU, there may be different types of RAM available that have different properties in terms of quantity and speed.
The fastest RAM should be chosen for the buffers if its size allows it.

Flush policy
~~~~~~~~~~~~

As described in the :ref:`section_display` page, there are several flush policies that can be implemented.
The best flush policy should be selected according to the hardware capabilities. Generally, the best flush policy is the switch mode.


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

