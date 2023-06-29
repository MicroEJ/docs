.. _microuiflushvisualizer:

MicroUI Flush Visualizer
========================

Building smooth and visually appealing UI applications require a keen focus on performance.
To achieve efficient UI rendering, minimizing unnecessary work that consumes valuable CPU time is essential.

This article introduces the MicroUI Flush Visualizer, a tool designed to investigate potential performance bottlenecks in UI applications running on the Simulator by showing the pixel surface drawn between 2 MicroUI frame buffer flushes.

- Requirements: VEE Port with UI Pack 13.0.0 or higher.

Understanding the Rendering Pipeline
------------------------------------

One key element to successful smooth UI applications is performance.
An efficient UI application must only draw what is necessary to achieve the visual effects desired.
For example, assuming the application targets 60 FPS to perform a transition between two screens, that means the application has 1/60s ~= 16ms in total to execute the *Rendering Pipeline*.

The *Rendering Pipeline* of an UI application consists of three main phases: Layout, Rendering, and Flush.


1. *Layout*: This phase determines which widgets should be displayed on the screen and their respective positions.
   It is typically triggered when widgets are added or removed from the widget hierarchy.
   To ensure efficiency, an application should only modify the widget hierarchy when necessary and avoid doing so during animations.

2. *Rendering*: During this phase, each widget executes its rendering code to perform the necessary drawing operations.
   It is crucial for widgets to render only what is necessary and minimize overlapping with other widgets to ensure optimal performance.

3. *Flush*: This phase involves copying the UI working buffer to the screen buffer.
   This operation is performed by the VEE Port, and it is the responsibility of the Firmware developer to optimize this process, for example, by utilizing a GPU.


The MicroUI Flush Visualizer is a tool designed to visualize the drawing operations requested by widgets during the *Rendering* phase between each flush.


The MicroUI Flush Visualizer provides the following information:


- A screenshot of the result of the Rendering Pipeline (what was shown on the screen).
- A list of drawing operations that were performed during the *Rendering* phase.
- The total area covered by the sum of the area drawn by the drawing operations as percentage.
  A value of 100% indicates that the entire display was drawn once; a value of 200% indicates that the entire display was drawn twice; etc.

Here are examples of the MicroUI Flush Visualizer in action:

+----------------------------------------------------------------+--------------------------------------------------------------------+
|Simple GFX                                                      | Demo Wearable                                                      |
+================================================================+====================================================================+
| .. image:: images/small-demo-ui-flush-visualizer-simpleGFX.png | .. image:: images/small-demo-ui-flush-visualizer-demo-wearable.png |
+----------------------------------------------------------------+--------------------------------------------------------------------+

This tool is helpful to identify potential bottlenecks in the application's rendering by looking for flushes that exceed 200% of the display area.

A perfect application has 100% of its display area drawn.
In practice, a total area drawn between 100% to 200% is the norm because widgets often overlap.
However, if the total area drawn is bigger than 200%, that means that the total surface of the display was drawn more than twice, meaning that a lot of time could be spent drawing things that are never shown.

As always, when conducting a performance study, measure.
Use :ref:`systemview` to identify the bottlenecks in your application on the embedded target.
A total area drawn over 200% is inefficient, but your application may have bigger bottlenecks.
Confirm it by measuring the time spent drawing vs. the time spent elsewhere between flushes.

Installation
------------

1. Open the Front Panel file ``.fp``.

2. Replace the ``ej.fp.widget.Display`` widget by ``ej.fp.widget.FlushVisualizerDisplay``

3. Set the shape of the display to either ``RECTANGLE`` or ``CIRCLE``:

For example:

.. code-block:: xml

   <ej.fp.widget.FlushVisualizerDisplay x="10" y="10" width="200" height="200" filter="f.png" shape="CIRCLE" />

Usage
-----

1. Run the application in the Simulator.

2. Open the file ``MicroUIFlushVisualizer/MicroUIFlushVisualizer.html`` that was generated in the :ref:`application output folder <outputfiles>`.

.. image:: images/MicroUIFlushVisualizerApplicationOutputFolder.png


Known Limitations
-----------------

- Do not take into account the clip of the GraphicsContext.
  Regardless of the clip, the complete area of the drawing is accounted for.
- Do not take into account Vector Graphics (VG) operations.
  VG drawings are not accounted for in the total of area drawn.
- Do not take into account drawing that are done outside of the screen (even partially).
  Such drawing are accounted as if they were done on the screen.
- Do not take into account drawing of thick shapes and rendering with transformations from `ej.drawing <https://repository.microej.com/modules/ej/api/drawing/>`__ package. 

