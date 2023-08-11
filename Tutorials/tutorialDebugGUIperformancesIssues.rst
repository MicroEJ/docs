.. _tutorials_debug_gui_performances:

How to debug GUI performance issue
==================================

This document explains how to debug Graphical User Interface performances issues. It describes common pitfalls that can affect GUI performances, provides tools that allow to detect performances issues causes and how to solve them.

General good coding practices
-----------------------------

Before using more advanced UI debugging techniques, the global application code quality should be reviewed. An overall good code quality will help to get good UI performances. It will help getting more efficient code and allow easier debugging and maintenance.

Documents and tools to improve application code quality
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is a list of documents or tools that help improving the quality of application code:

- The :ref:`Improve the Quality of Java Code<improve_code_quality>` tutorial explains how to improve the Quality of Java Code.
- The :ref:`Get Started With GUI<tutorial_get_started_with_gui>` tutorial provides guidelines to start developping an efficient GUI.
- The `SonarQube™<https://github.com/MicroEJ/ExampleTool-Sonar>`_ source code quality analyzer allows to analyze an Application or Library code quality.

Using recent version of UI libraries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using the latest UI libraries (MicroUI, MWT, Widget, etc) available may solve some performances issues. The most recent UI libraries fix some bugs that may affect performance and they provide tools/libraries that allow to implement more performant UIs.

Memory management
~~~~~~~~~~~~~~~~~

The Java management of memory may affect UI performances:

- Too much memory allocation/deallocation for UI resources (Images, Fonts).
- Too much objects intanciation will lead to a big Java heap size. In some usecases the garbage collection may lead to the UI slowing down.

To avoid those pitfalls:

- Calibrate the memories (Java heap, Images heap, etc).
- Uses Memory debugging tools:

    - :ref:`Optimize Memory Footprint<tutorial_optimize_memory_footprint>` tutorial.
    - :ref:`Memory inspection tools<tutorial_discover_embedded_debugging_techniques.tools.memory_inspection>`.
    - :ref:`Heap Analyzer<heapdumper>`.

Causes of UI bad performances
-----------------------------

The process to render a frame of the UI consists of several parts:

- Drawing of the UI

    - MWT processing (layout of widgets and widget rendering process)
    - Drawing of the UI (MicroUI drawing method execution)

- Display flush
- (depends on the UI port) Backbuffer copy, see :ref:`Display Buffer Modes<section_display_modes>`. 

This tutorial focuses on reducing processing time for the "Drawing of the UI" parts. To get more information about the other parts, please see the VEE Porting Guide :ref:`Graphical User Interface<pack_gui>` section.

SystemView
~~~~~~~~~~

The SystemView tool can be used to trace the UI actions (drawings, flush, etc) and detect which ones are the more time consuming. The documentation of SystemView is available :ref:`here<systemview>`. The MicroUI traces should be configured in SystemView in order to see the UI actions performed, it can be done by following :ref:`this documentation<microui_traces>`. Custom traces can be added and logged from the Java application to record specific actions.

Format of UI resources
~~~~~~~~~~~~~~~~~~~~~~

The format of UI resources should be chosen according to the usecase. Choosing the best resource format will reduce memory consumption and reduce drawing time.

:ref:`This documentation<section_image_display_output>` explains the different images formats.

Widget hierarchy and layout
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Keeping the widget hierarchy as simple as possible will help reducing the "MWT processing" part time. Improving the widgets hierarchy design may help reducing the number of widgets or the number of them that are rendered when a certain part of the UI is updated.

Here are tools that allow to detect issues with the widgets hierarchy:

- :ref:`Widget debug utilities<widget_library_debug_utilities>` provides tools to visualize the widget tree, count the numbers of widgets or see their bounds.
- :ref:`MWT bounds highlighting<mwt_how_to_debug>` allows to visualize the bounds of the widgets, it is useful to detect overlapping widgets.

Bad use of requestRender and requestLayout
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``requestRender`` method requests a render of the widget on the display.

The ``requestLayout`` method requests a lay out of all the widgets in the sub hierarchy of this widget. It will compute the size and position of the widgets as setting their styles. ``requestLayout`` will trigger a render request after the layout.

A common mistake is to call ``requestRender`` just after a ``requestLayout``. This will trigger two renders and thus affect the UI performances.

Another common issue is to request a layout where a render request would have been enough. If the size, position or style of the widgets didn't change ``requestRender`` is enough, ``requestLayout`` would have a longer processing time. This is especially true for animation where we want each frame to be processed as fast as possible.

Documentation about rendering and layout is available :ref:`here<mwt_concepts>`.

Animations implementation
~~~~~~~~~~~~~~~~~~~~~~~~~

There are a few implementations possible for animations with MicroEJ. The way widgets are animated should be chosen according to the usecase and the limitation of the hardware.

Animator
++++++++

The MWT's `Animator<https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animator.html>`_ allows to execute animations as fast as possible, it waits for the low level screen flush to be done and directly triggers a new render. Thus the Animator will give the best framerate possible but will also consume a lot of CPU processing time.

TimerTask
+++++++++

A TimerTask can be used to execute an animation at a fixed framerate. This technique is very useful to set a fixed period for the animation but will cause issues if the time to render a frame is longer than that period, this will lead to missed frames. Some frame can be longer to render if their content is more complex or if the CPU is already used by another non UI thread.

The framerate set when using a TimerTask for animation should be defined wisely, the time to render frames and the CPU utilization should be taken into consideration.

Animator and TimerTask mix
++++++++++++++++++++++++++

A mix of the Animator and TimeTask approaches could be implemented in order to set a fixed framerate but also to rely on the screen flush.


..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

