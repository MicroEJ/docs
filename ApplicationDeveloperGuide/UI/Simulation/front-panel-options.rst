Front Panel Options
===================

Cache
-----

The configuration of the Front Panel is saved and restored for the next launch.
This configuration could be reset by deleting the `.cache/frontpanelstate.properties` in the application output folder.

The saved properties are: the :ref:`zoom<frontpanel_zoom>`, the :ref:`fit<frontpanel_zoom_fit>`, the :ref:`interpolation<frontpanel_zoom_interpolation>`, and the :ref:`device coordinates<frontpanel_device_coordinates>`.

Properties
----------

The configuration of the Front Panel can be configured through properties.

Some of the properties are used by the cache.
Defining these properties will overrule the cache.
In other words, the cache will not be used for these properties.

However, it is possible to define a default value for the very first launch of the Front Panel (or when the cache has been deleted).
It can be done by defining a property with the same name but with the ``.default`` suffix.

Please refer to the dedicated sections (:ref:`SDK 6<sdk_6_define_option>` or :ref:`SDK 5<define_option>`) to know how to define options.

.. list-table:: Front Panel Options
   :widths: 20 15 45 20
   :header-rows: 1

   * - Option
     - Chapter
     - Aim
     - Cached
   * - ``ej.fp.project``
     - :ref:`fp_installation`
     - Specify a local Front Panel project to avoid rebuilding VEE Port.
       Only available before Architecture 8 and before UI Pack 14.3.0.
     - false
   * - ``ej.fp.hil``
     - :ref:`fp_ui_classpath`
     - Run the Front Panel in the same VM as the standard mocks. 
     - false
   * - ``ej.fp.brs.drawnColor``
     - :ref:`refresh_drawn_regions`
     - Identify the drawn regions for each frame.
     - false
   * - ``ej.fp.brs.restoredColor``
     - :ref:`refresh_restored_regions`
     - Identify the restored regions for each frame.
     - false
   * - ``ej.fp.brs.dirtyColor``
     - :ref:`refresh_dirty_regions`
     - Identify the regions not fully filled by the drawings.
     - false
   * - ``ej.fp.zoom``
     - :ref:`frontpanel_zoom`
     - Set the zoom of the device at startup.
     - true (``ej.fp.zoom.default``)
   * - ``ej.fp.zoom.fit``
     - :ref:`frontpanel_zoom_fit`
     - Set whether the device is fitted to the Front Panel bounds at startup.
       In other words if the zoom changes when the user resizes the frame or the other way around.
     - true (``ej.fp.zoom.fit.default``)
   * - ``ej.fp.zoom.interpolate``
     - :ref:`frontpanel_zoom_interpolation`
     - Set whether the device is drawn with interpolation when zoomed in or out at startup.
     - true (``ej.fp.zoom.interpolate.default``)
   * - ``ej.fp.frame.coordinates``
     - :ref:`frontpanel_device_coordinates`
     - Set the location of the Front Panel frame at startup.
     - true (``ej.fp.frame.coordinates.default``)

