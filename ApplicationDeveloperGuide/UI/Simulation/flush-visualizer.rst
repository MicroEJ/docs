.. _flush_visualizer:

Flush Visualizer
================

Presentation
------------

Building smooth and visually appealing UI applications requires a keen focus on performance.
To achieve efficient UI rendering, minimizing unnecessary work that consumes valuable CPU time is essential.

For example, assuming the application targets 60 FPS to perform a transition between two screens, that means the application has 1/60s ~= 16ms in total to execute the rendering and the flush (see :ref:`rendering_pipeline`).

The Flush Visualizer is a tool designed to investigate potential performance bottlenecks in UI applications running on the Simulator.
The Flush Visualizer provides the following information:

- A timeline with a step for each flush.
- A screenshot of what is shown on the display at flush time.
- The list of what is done before this flush (and after the previous one) organized as a tree.
- A node of the tree can be either a region (the display or a clip) or a drawing operation.
- Each region defines its bounds and can contain one or several other nodes.
- Each region also displays the percentage of their parent region they cover.
- Some of the drawings can compute the percentage of their parent region they cover.
- The others are either negligeable or unknown.
- At the end of each region, there is a summary of the percentage covered by the drawings in this region (recursively).

.. image:: images/flush-visualizer-annotated.png

Consider this part of the tree:

.. code::

  |  |  |_ Clip #3 (0,0) 44x46 [16% of Clip #2]
  |  |  |  |_ fillRectangle (0,0) 44x46 color=0xffee502e [100% of Clip #3]
  |  |  |  |_ fillRectangle (0,44) 44x2 color=0xffcf4520 [4% of Clip #3]
  |  |  |  |
  |  |  |  |_ Clip #4 (10,10) 24x24 [28% of Clip #3]
  |  |  |  |  |_ drawImage (0,0) 24x24 at (10,10) alpha=255 color=0xffffffff [100% of Clip #4]
  |  |  |  |  [100% drawn of Clip #4]
  |  |  |  [132% drawn of Clip #3]

We can see that:

- The clip #3 is 16% of the clip #2.
- It draws 2 rectangles and an image that take respectively 100%, 4% and 100% of their parent region.
- The clip #4 is fully covered by the image (100%).
- The clip #3 is covered at 132% (100% for the 1st rectangle, 4% for the 2nd, 28% for the clip #4 and its inner image).

A value of 100% indicates that the area drawn is equivalent to the surface of the region.
A value of 200% indicates that the area drawn is equivalent to twice the surface of the region.
A perfect application has 100% of its root region drawn but its very unlikely for an application that draws anything else than a rectangle or an image.
A total area drawn between 100% to 200% is the norm in practice because widgets often overlap.
However, if the total area drawn is bigger than 200%, that means that the total surface of the region was drawn more than twice.
Probably meaning that a lot of drawings are done above others.
Identifying this drawing (and the ones below) can help reducing the number of drawings done (or their surface).

As always, when conducting a performance study, measure.
Use :ref:`systemview` to identify the bottlenecks in your application on the embedded target.
A total area drawn over 200% is inefficient, but your application may have bigger bottlenecks.
Confirm it by measuring the time spent drawing vs. the time spent elsewhere between flushes.

Installation
------------

The Flush Visualizer option is available for the ``Display`` widget in
`frontpanel widget module <https://forge.microej.com/artifactory/microej-developer-repository-release/ej/tool/frontpanel/widget/>`__
version 4.+ for UI Pack 14.0.0 or later.

Set the option ``ej.fp.display.flushVisualizer`` to ``true`` to enable the flush visualizer.

Refer to the :ref:`application_options` documentation to set the option.

Usage
-----

1. Run the application in the Simulator.
2. Since UI Pack 14.3.0, the button |FlushVizualizer| in the toolbar of the Front Panel opens the Flush Vizualizer.
3. The file ``MicroUIFlushVisualizer/MicroUIFlushVisualizer.html`` is generated in the :ref:`application output folder <outputfiles>` and can be opened during or after the execution.

.. |FlushVizualizer| image:: images/monitoring.png
.. image:: images/MicroUIFlushVisualizerApplicationOutputFolder.png

.. note::

  Since MICROEJ SDK 6, the application output folder is located under the ``build/output/`` folder.

Examples
--------

Here are examples of the Flush Visualizer in action:

+--------------------------------------------+---------------------------------------------------+
| MVC Demo                                   | Widget Example                                    |
+============================================+===================================================+
| .. image:: images/flush-visualizer-mvc.png | .. image:: images/flush-visualizer-checkboxes.png |
+--------------------------------------------+---------------------------------------------------+

..
   | Copyright 2023-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.