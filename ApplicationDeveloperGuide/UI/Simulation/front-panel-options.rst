Front Panel Options
===================

The following options are available in the Front Panel.
Please refer to the dedicated sections (:ref:`SDK 6<sdk_6_define_option>` or :ref:`SDK 5<define_option>`) to know how to define options.

.. list-table:: Front Panel Options
   :widths: 20 20 60
   :header-rows: 1

   * - Options
     - Chapter
     - Aim
   * - ``ej.fp.project``
     - :ref:`fp_installation`
     - Specify a local Front Panel project to avoid rebuilding VEE Port.
   * - ``ej.fp.hil``
     - :ref:`fp_ui_classpath`
     - Run the Front Panel in the same VM as the standard mocks. 
   * - ``ej.fp.display.flushVisualizer``
     - :ref:`flush_visualizer`
     - Export all the frames drawn on the display and list the drawings done for each frame.
   * - ``ej.fp.brs.drawnColor``
     - :ref:`refresh_drawn_regions`
     - Identify the drawn regions for each frame.
   * - ``ej.fp.brs.restoredColor``
     - :ref:`refresh_restored_regions`
     - Identify the restored regions for each frame.
   * - ``ej.fp.brs.dirtyColor``
     - :ref:`refresh_dirty_regions`
     - Identify the regions not fully filled by the drawings.
