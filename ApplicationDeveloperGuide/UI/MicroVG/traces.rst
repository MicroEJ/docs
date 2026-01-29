.. _microvg_traces:

Debug Traces
=============

MicroVG traces several actions when traces are enabled. 
This chapter explains the trace identifiers.

.. note:: The traces are only available on the Embedded VEE Port (not on the Simulator).

Trace format
------------

The trace output format is the following:

``[TRACE: MicroVG] Event AA(BB[CC])``

where:

- AA is the event identifier. See next table.
- BB is the event data.
- CC is the index of the event data (0x0).

For example, given the following trace output:

``[TRACE: MicroVG] Event 0x2(2[0x0])``

- 0x2 -> Execute drawing event
- 2 -> Event “Draw String” (index 0x0)

Trace identifiers
-----------------

The following tables describe some events data.

.. list-table:: MicroVG Traces
   :widths: 10 60 30
   :header-rows: 1

   * - Event ID
     - Description
     - End of Event
   * - 0x0 (0)
     - Image event  ``%0%`` (see Image Type)
     - End of ``%0%`` (see Image Type). 
   * - 0x1 (1)
     - Font event  ``%0%`` (see Font Type)
     - End of ``%0%`` (see Font Type). 
   * - 0x2 (2)
     - Drawing ``%0%`` (see Drawing type)
     - End of ``%0%`` (see Drawing Type). 
   * - 0x3 (3)
     - New image ``%0%`` (see Image Type)
     - Image created, image identifier is ``%0%``.
   * - 0x4 (4)
     - New image characteristics: ``%0%`` (see New Image), identifier is ``%1%`` and size is ``%2%`` x ``%3%``. 
     - 
   * - 0xA (10)
     - Draw Path dest ``%0%``, anchor= ``%1%``, ``%2%``
     - Drawing status ``%0%`` (see Drawing Status)
   * - 0xB (11)
     - Draw Path with Gradient dest ``%0%``, anchor= ``%1%``, ``%2%``
     - Drawing status ``%0%`` (see Drawing Status)
   * - 0xC (12)
     - Draw String dest ``%0%``, ``%1%`` characters, anchor= ``%2%``, ``%3%``
     - Drawing status ``%0%`` (see Drawing Status)
   * - 0xD (13)
     - Draw String with Gradient dest ``%0%``, ``%1%`` characters, anchor= ``%2%``, ``%3%``
     - Drawing status ``%0%`` (see Drawing Status)
   * - 0xE (14)
     - Draw String On Circle dest ``%0%``, ``%1%`` characters, anchor= ``%2%``, ``%3%``, radius= ``%4%``, direction= ``%5%`` (see Direction Type)
     - Drawing status ``%0%`` (see Drawing Status)
   * - 0xF (15)
     - Draw String On Circle with Gradient dest ``%0%``, ``%1%`` characters, anchor= ``%2%``, ``%3%``, radius= ``%4%``, direction= ``%5%`` (see Direction Type)
     - Drawing status ``%0%`` (see Drawing Status)
   * - 0x10 (16)
     - Draw Image dest ``%0%``, image= ``%1%``, anchor= ``%2%``, ``%3%``
     - Drawing status ``%0%`` (see Drawing Status)


.. table:: Image Type

   +-------------+----------------------------------------------------------------+
   | Event ID    | Description                                                    |
   +=============+================================================================+
   | 0x0 (0)     | Get or load image from RAW file                                |
   +-------------+----------------------------------------------------------------+
   | 0x1 (1)     | Create BufferedVectorImage                                     |
   +-------------+----------------------------------------------------------------+
   | 0x2 (2)     | Close image                                                    |
   +-------------+----------------------------------------------------------------+

.. table:: New Image

   +-------------+----------------------------------------------------------------+
   | Event ID    | Description                                                    |
   +=============+================================================================+
   | 0x0 (0)     | Get image from RAW file                                        |
   +-------------+----------------------------------------------------------------+
   | 0x1 (1)     | Load image from RAW file                                       |
   +-------------+----------------------------------------------------------------+
   | 0x2 (2)     | Create BufferedVectorImage                                     |
   +-------------+----------------------------------------------------------------+
   | 0x3 (3)     | Build image                                                    |
   +-------------+----------------------------------------------------------------+
   | 0x4 (4)     | New filtered image from RAW image                              |
   +-------------+----------------------------------------------------------------+
   | 0x5 (5)     | New filtered image from BufferedVectorImage                    |
   +-------------+----------------------------------------------------------------+
   | 0x6 (6)     | New filtered image from builder image                          |
   +-------------+----------------------------------------------------------------+

.. table:: Font Type

   +-------------+----------------------------------------------------------------+
   | Event ID    | Description                                                    |
   +=============+================================================================+
   | 0x0 (0)     | Load font from TTF / OTF file                                  |
   +-------------+----------------------------------------------------------------+
   | 0x1 (1)     | Retrieve font baseline                                         |
   +-------------+----------------------------------------------------------------+
   | 0x2 (2)     | Retrieve font height                                           |
   +-------------+----------------------------------------------------------------+
   | 0x3 (3)     | Measure string width                                           |
   +-------------+----------------------------------------------------------------+
   | 0x4 (4)     | Measure string height                                          |
   +-------------+----------------------------------------------------------------+

.. table:: Drawing Type

   +-------------+--------------------------------------------+
   | Event ID    | Description                                |
   +=============+============================================+
   | 0x0 (0)     | Fill path with a color                     |
   +-------------+--------------------------------------------+
   | 0x1 (1)     | Fill path with a linear gradient           |
   +-------------+--------------------------------------------+
   | 0x2 (2)     | Draw string with a color                   |
   +-------------+--------------------------------------------+
   | 0x3 (3)     | Draw string with a linear gradient         |
   +-------------+--------------------------------------------+
   | 0x4 (4)     | Draw string on a circle with a color       |
   +-------------+--------------------------------------------+
   | 0x5 (5)     | Draw string on a circle with a gradient    |
   +-------------+--------------------------------------------+
   | 0x6 (6)     | Draw image                                 |
   +-------------+--------------------------------------------+

.. table:: Direction Type

   +-------------+--------------------------------------------+
   | Event ID    | Description                                |
   +=============+============================================+
   | 0x0 (0)     | Clockwise                                  |
   +-------------+--------------------------------------------+
   | 0x1 (1)     | Anticlockwise                              |
   +-------------+--------------------------------------------+

.. table:: Drawing Status

   +-------------+--------------------------------------------+
   | Event ID    | Description                                |
   +=============+============================================+
   | 0x0 (0)     | Synchronous drawing done                   |
   +-------------+--------------------------------------------+
   | 0x1 (1)     | Asynchronous drawing delayed               |
   +-------------+--------------------------------------------+


SystemView Integration
----------------------

The traces are :ref:`systemview` compatible.

.. figure:: images/microvg_traces_systemview.png
   :alt: MicroVG Traces displayed in SystemView
   :align: center

   MicroVG Traces displayed in SystemView

The following text can be copied in a file called ``SYSVIEW_MicroVG.txt`` and copied in SystemView installation folder (e.g. ``SEGGER/SystemView_V252a/Description/``).

.. code-block::
   
   #
   # SystemView Description File
   #

   #===========
   # NamedTypes 
   #===========

   # ------------
   # Image Events
   # ------------

   # Deprecated (kept for backward compatibility VG Pack < 1.8.1)
   NamedType VGImage 0=OPEN_RAW_IMAGE
   NamedType VGImage 1=CREATE_IMAGE
   NamedType VGImage 2=CLOSE_IMAGE

   NamedType VGNewImage 0=GET_RAW_IMAGE
   NamedType VGNewImage 1=LOAD_RAW_IMAGE
   NamedType VGNewImage 2=MUTABLE_IMAGE
   NamedType VGNewImage 3=BUILDER_IMAGE
   NamedType VGNewImage 4=FILTERED_IMAGE_FROM_RAW
   NamedType VGNewImage 5=FILTERED_IMAGE_FROM_MUTABLE
   NamedType VGNewImage 6=FILTERED_IMAGE_FROM_BUILDER

   # -----------
   # Font Events
   # -----------

   NamedType VGFont 0=LOAD_FONT
   NamedType VGFont 1=FONT_BASELINE
   NamedType VGFont 2=FONT_HEIGHT
   NamedType VGFont 3=STRING_WIDTH
   NamedType VGFont 4=STRING_HEIGHT

   # --------------
   # Drawing Events
   # --------------

   NamedType VGString *="%u characters"
   NamedType VGRadius *="radius=%u"
   NamedType VGSource *="image=0x%x"

   NamedType VGDirection 0="direction=clockwise"
   NamedType VGDirection 1="direction=anticlockwise"

   # ------------------
   # Old Drawing Events
   # ------------------

   NamedType VGDraw 0=DRAW_PATH
   NamedType VGDraw 1=DRAW_PATH_GRADIENT
   NamedType VGDraw 2=DRAW_STRING
   NamedType VGDraw 3=DRAW_STRING_GRADIENT
   NamedType VGDraw 4=DRAW_STRING_ON_CIRCLE
   NamedType VGDraw 5=DRAW_STRING_ON_CIRCLE_GRADIENT
   NamedType VGDraw 6=DRAW_IMAGE

   # -----------------
   # UI Drawing Events
   # -----------------

   # Copy of MicroUI events (required by the Front Panel)
   NamedType UIDrawAsync 0="Drawing operation done"
   NamedType UIDrawAsync 1="Drawing operation delayed"
   NamedType UIDestination *="dest=0x%x"

   #=======
   # Events
   #=======

   # ---------------
   # MicroVG Library
   # ---------------

   # [0-9]: 10 events

   # Deprecated (kept for backward compatibility VG Pack < 1.8.1)
   0        VG_ImageEvent      type=%VGImage | type=%VGImage done
   2        VG_DrawingEvent    type=%VGDraw  | type=%VGDraw done

   1        VG_FontEvent       type=%VGFont  | type=%VGFont done
   3        VG_NewImage        type=%VGNewImage | id=0x%x
   4        VG_ImageData       type=%VGNewImage id=0x%x size=%u*%u

   # ----------------
   # MicroVG C Module
   # ----------------

   # [10-39]: 30 events

   10       VG_DrawPathColor              %UIDestination anchor=%d,%d | %UIDrawAsync
   11       VG_DrawPathGradient           %UIDestination anchor=%d,%d | %UIDrawAsync
   12       VG_DrawStringColor            %UIDestination %VGString anchor=%d,%d | %UIDrawAsync
   13       VG_DrawStringGradient         %UIDestination %VGString anchor=%d,%d | %UIDrawAsync
   14       VG_DrawStringOnCircleColor    %UIDestination %VGString anchor=%d,%d %VGRadius %VGDirection | %UIDrawAsync
   15       VG_DrawStringOnCircleGradient %UIDestination %VGString anchor=%d,%d %VGRadius %VGDirection | %UIDrawAsync
   16       VG_DrawImage                  %UIDestination %VGSource anchor=%d,%d | %UIDrawAsync

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
