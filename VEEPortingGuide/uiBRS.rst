.. include:: uiReplaces.rst

.. _section_brs:

=======================
Buffer Refresh Strategy
=======================

Overview
========

The Buffer Refresh Strategy (BRS) ensures the display buffer (front buffer) contains all the drawings before letting the display driver flushing this buffer to the display device.
The drawings are the drawings made since last *flush* **and** the *past*.
The *past* symbolizes the drawings made before the last *flush*  and that has not be altered by the new drawings.

.. table:: Automatic Refresh

   +-------------------+-------------------------------+-------------------------------+
   | Drawing Steps     | Back Buffer                   | Front Buffer                  |
   +===================+===============================+===============================+
   | Startup           | .. image:: images/ui_brs0.png | .. image:: images/ui_brs0.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "background" | .. image:: images/ui_brs1.png | .. image:: images/ui_brs0.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "A"          | .. image:: images/ui_brs2.png | .. image:: images/ui_brs0.png |
   +-------------------+-------------------------------+-------------------------------+
   | Flush (swap)      | .. image:: images/ui_brs0.png | .. image:: images/ui_brs2.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "B"          | .. image:: images/ui_brs3.png | .. image:: images/ui_brs2.png |
   +-------------------+-------------------------------+-------------------------------+
   | Refresh the past  | .. image:: images/ui_brs4.png | .. image:: images/ui_brs2.png |
   +-------------------+-------------------------------+-------------------------------+
   | Flush (swap)      | .. image:: images/ui_brs2.png | .. image:: images/ui_brs4.png |
   +-------------------+-------------------------------+-------------------------------+

This refreshing avoids running again all drawings algorithms (and layout) to fill the back buffer (here: the entire background, the "A" background and the "A").
Without this refreshing, the display will show the incomplete frame *Draw "B"*:  

.. table:: Missing Refresh

   +-------------------+-------------------------------+-------------------------------+
   | Drawing Steps     | Back Buffer                   | Front Buffer                  |
   +===================+===============================+===============================+
   | Startup           | .. image:: images/ui_brs0.png | .. image:: images/ui_brs0.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "background" | .. image:: images/ui_brs1.png | .. image:: images/ui_brs0.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "A"          | .. image:: images/ui_brs2.png | .. image:: images/ui_brs0.png |
   +-------------------+-------------------------------+-------------------------------+
   | Flush (swap)      | .. image:: images/ui_brs0.png | .. image:: images/ui_brs2.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "B"          | .. image:: images/ui_brs3.png | .. image:: images/ui_brs2.png |
   +-------------------+-------------------------------+-------------------------------+
   | Flush (swap)      | .. image:: images/ui_brs2.png | .. image:: images/ui_brs3.png |
   +-------------------+-------------------------------+-------------------------------+

When the new drawings overlap the *past*, it is useless to refresh the past:

.. table:: Useless Refresh

   +-------------------+-------------------------------+-------------------------------+
   | Drawing Steps     | Back Buffer                   | Front Buffer                  |
   +===================+===============================+===============================+
   |                   | .. image:: images/ui_brs2.png | .. image:: images/ui_brs4.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "C"          | .. image:: images/ui_brs5.png | .. image:: images/ui_brs4.png |
   +-------------------+-------------------------------+-------------------------------+
   | Flush (swap)      | .. image:: images/ui_brs4.png | .. image:: images/ui_brs5.png |
   +-------------------+-------------------------------+-------------------------------+
   | Draw "D"          | .. image:: images/ui_brs6.png | .. image:: images/ui_brs5.png |
   +-------------------+-------------------------------+-------------------------------+
   | Flush (swap)      | .. image:: images/ui_brs5.png | .. image:: images/ui_brs6.png |
   +-------------------+-------------------------------+-------------------------------+


Timeline
========

Basic Principle
---------------

The basic principle of the Graphics Engine's timeline can be symbolized by this illustration:

.. image:: images/ui_brs_line4.png
      :width: 50%
      :align: center

* *drawing(s)* symbolizes one or several drawings in the back buffer.
* *flush* symbolizes the call to the LLAPI ``LLUI_DISPLAY_IMPL_flush()`` that allows to the display driver to update the display panel content according to the :ref:`display connection<section_display_connection>` (swap buffers, send or copy buffer).
* *post-flush* symbolizes the moment between the end of flush (end of swap, send or copy) and the unlocking of the Graphics Engine (the call to ``LLUI_DISPLAY_setDrawingBuffer()``). Before this call, the Graphics Engine is not allowed to draw in the buffer. 

.. note:: The time between the *post-flush* and *drawing(s)* depends on the application: the first drawing after a *flush* can occur immediately after the *post-flush* or later.

Additional Hooks
----------------

The Graphics Engine gives some hooks (through dedicated LLAPI) to be notified of further details:

.. image:: images/ui_brs_line5.png
      :width: 50%
      :align: center

* *new region* symbolizes that the following drawing(s) will draw in another region than the previous drawings.
* *refresh* symbolizes that the last drawing has been done and a call to ``LLUI_DISPLAY_IMPL_flush()`` will be performed just after. This moment can be used to refresh the back buffer with the *past* (see above).

.. * *...*  symbolizes a random time: the first drawing after a *flush* can occur immediately after the *post-flush* or later (depends on the application).

During these two new steps, the implementation can render into the back buffer (to restore the past), prepare the next flush (store the regions to flush), etc.

Implicit Region
---------------

A *region* is considered as a *new implicit region* as soon as the MicroUI clip is updated **and** a drawing is performed.
As soon as a clip is considered as an *implicit* region, a call to the LLAPI ``LLUI_DISPLAY_IMPL_newDrawingRegion(...)`` is performed.
The following sequence illustrates when the LLAPI  is called:

.. list-table:: 
   :widths: 10 45 45
   :header-rows: 1

   * - 
     - Application Calls
     - LLAPI
   * - **1**
     - ``gc.setClip(...)``
     - 
   * - **2** [1]_
     - ``Painter.draw(...)``
     - | ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., true)`` 
       | ``LLUI_PAINTER_IMPL_draw(...)``
   * - **3** [2]_
     - ``Painter.draw(...)``
     - ``LLUI_PAINTER_IMPL_draw(...)``
   * - **4** [3]_
     - ``gc.setClip(...)``
     - 
   * - **5**
     - ``gc.setClip(...)``
     - 
   * - **6**
     - ``Painter.draw(...)``
     - | ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., true)`` 
       | ``LLUI_PAINTER_IMPL_draw(...)``

.. [1] The LLAPI argument ``drawing_now`` is valued to ``true``: this means a call to a drawing action will be call just after (*implicit* region).
.. [2] The second drawing uses the same region than first one: the region is not notified again.
.. [3] The clip is not recognized as an **implicit** region because no drawing is performed just after.

.. note:: The very first drawing's region after a *flush* is systematically considered as *implicit*.

Explicit Region
---------------

The application can *explicitly* call the LLAPI ``LLUI_DISPLAY_IMPL_newDrawingRegion(...)`` by calling the API ``GraphicsContext.notifyDrawingRegion()``. 
The LLAPI parameters are:

  * the region is the current MicroUI clip,
  * the argument ``drawing_now`` is valued to ``false``: this means no drawing will follow this call (*explicit* region).

This call (only one or several ones) is often useful when it is performed before the very first drawing: it indicates to the implementation about several regions will be altered: these regions don't need to be restored with the past (their content will change).

.. list-table:: 
   :widths: 10 45 45
   :header-rows: 1

   * - 
     - Application Calls
     - LLAPI
   * - **1**
     - ``gc.setClip(...)``
     - 
   * - **2** [4]_
     - ``gc.notifyDrawingRegion(...)``
     - ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., false)`` 
   * - **3** [5]_
     - ``Painter.draw(...)``
     - | ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., true)`` 
       | ``LLUI_PAINTER_IMPL_draw(...)``
   * - **4**
     - ``Painter.draw(...)``
     - ``LLUI_PAINTER_IMPL_draw(...)``
   * - **5** [6]_
     - ``gc.notifyDrawingRegion(...)``
     - ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., true)``
   * - **6** [7]_
     - ``Painter.draw(...)``
     - ``LLUI_PAINTER_IMPL_draw(...)``

.. [4] The LLAPI is immediately called.
.. [5] The step **2** doesn't change the flow of the *implicit region*: a call to ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., true)`` is always performed even if a call to ``LLUI_DISPLAY_IMPL_newDrawingRegion(..., false)`` is performed just before.
.. [6] The clip has not changed but the LLAPI is explicitly called again.
.. [7] The clip has not changed so the *implicit region* is not notified.

Flush vs Refresh
----------------

The Graphics Engine does not store the regions (implicit or explicit): it just calls the LLAPI (the hooks, see above) and lets the implementation manages the regions. 
The implementation (a Buffer Refresh Strategy) has the responsibility to manage these regions.

When the application calls ``Display.flush()``, the Graphics Engine immediately calls the LLAPI ``LLUI_DISPLAY_IMPL_refresh()``.
This call allows the BRS: 

  * to finalize (if required) the back buffer (no drawing will be performed into the buffer until the next call to ``LLUI_DISPLAY_setDrawingBuffer()``),
  * **and** to call the LCD driver flush function ``LLUI_DISPLAY_IMPL_flush()`` by giving the region(s) to update on the display panel.

Strategies
==========



Single
------

This strategy is the recommanded strategy of the UI Pack 14.x when the LCD frame buffer cannot be mapped dynamically: the same buffer is always used as back buffer.
However, the LCD frame buffer can be mapped on a memory buffer that is in the CPU addresses range.


(see `UI_DISPLAY_BRS_SINGLE`): the UI Pack 14.x single-buffer strategy: the drawings are always performed in the same buffer.

* use case
* how it works
* options
* 

Predraw
-------

This strategy is the recommanded strategy of the UI Pack 14.x when the LCD frame buffer can be mapped dynamically: the back buffer becomes the frame buffer on demand.


 (see `UI_DISPLAY_BRS_PREDRAW`): the UI Pack 14.x double-buffer default strategy: it consists to let the CCO MicroUI manages the past restoration.

Custom
------

Legacy
------

(see `UI_DISPLAY_BRS_LEGACY`): the UI Pack 13.x legacy strategy: it consists to manage the past restoration before unlocking the MicroUI Graphics Engine.

MicroUI C Module
----------------

* Defines
* conf for each (table ?)

Simulation
----------

* explain buffer policy here ?
* how to enable
* default options

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.