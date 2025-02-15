.. include:: ../../../VEEPortingGuide/uiReplaces.rst

.. _microui_traces:

Debug Traces
=============

MicroUI logs several actions when traces are enabled (see :ref:`event-tracing`). 
This chapter explains the trace identifiers.

.. note:: Most of the logs are only available on the Embedded VEE Port (not on the Simulator).

Trace format
------------

The trace output format is the following:

``[TRACE: MicroUI] Event AA(BB[CC],DD[EE])``

where:

- AA is the event identifier. See next table.
- BB is the first event data.
- CC is the index of the first event data (0x0).
- DD is the second event data.
- EE is the index of the second event data (0x1).
- etc.

For example, given the following trace output:

``[TRACE: MicroUI] Event 0x2(1[0x0],2[0x1],117571586[0x2])``

- 0x2 -> Execute native input event
- 1 -> Event “Button” (index 0x0)
- 2 -> Generator Id (index 0x1)
- 117571586 -> event data (index 0x2)

Trace identifiers
-----------------

The following tables describe some events data.

.. warning:: These tables are only compatible with the latest pack available (|UIPACKVERSION|).

.. table:: MicroUI Traces

   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | Event ID    | Description                                                                                                       | End of event                                  |
   +=============+===================================================================================================================+===============================================+
   | 0x0 (0)     | Execute EventGenerator event ``%0%`` (see Event Type). Generator id is ``%1%`` and data is ``%2%``.               | End of ``%0%`` (see Event Type).              |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x1 (1)     | Drop event ``%0%``.                                                                                               |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x2 (2)     | Execute native input event ``%0%`` (see Event Type). Generator id is ``%1%`` and data is ``%2%``.                 | End of ``%0%`` (see Event Type).              |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x3 (3)     | Execute display event ``%0%`` (see Event Type). Event is ``%1%``.                                                 | End of ``%0%`` (see Event Type).              |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x4 (4)     | Execute user event ``%0%``.                                                                                       | End of ``%0%``.                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x5 (5)     | Create new image using ``%0%`` algorithm (see Create Image).                                                      | Image created, image identifier is ``%0%``.   |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x6 (6)     | New image characteristics ``%0%`` (see Image Type), identifier is ``%1%`` and memory size is ``%2%``.             |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0xb (11)    | Flush done.                                                                                                       |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0xf (15)    | Asynchronous drawing operation done.                                                                              |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x14 (20)   | Invalid input event ``%0%``.                                                                                      |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x15 (21)   | Event queue is full, cannot add event ``%0%``.                                                                    |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x16 (22)   | Add event ``%0%`` at index ``%1%``; queue length is ``%2%``.                                                      |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x17 (23)   | Replace event ``%0%`` by ``%1%`` at index ``%2%``; queue length is ``%3%``.                                       |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x18 (24)   | Read event ``%0%`` at index ``%1%``.                                                                              |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x40 (64)   | Start drawing operation ``%0%`` (see Drawing Type).                                                               | Drawing status ``%0%`` (see Drawing Status)   |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x50 (80)   | [BRS] New drawing region                                                                                          |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x51 (81)   | [BRS] Flush LCD (id = ``%0%`` buffer = ``%1%``) with a single region (``%2%``, ``%3%``) to (``%4%``, ``%5%``)     |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x52 (82)   | [BRS] Flush LCD (id = ``%0%`` buffer = ``%1%``) with several ``%2%`` regions                                      |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x53 (83)   | [BRS] Add a region (``%0%``, ``%1%``) to (``%2%``, ``%3%``)                                                       |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x54 (84)   | [BRS] Remove a region (``%0%``, ``%1%``) to (``%2%``, ``%3%``)                                                    |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   | 0x55 (85)   | [BRS] Restore a region (``%0%``, ``%1%``) to (``%2%``, ``%3%``)                                                   |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+ 
   | 0x56 (86)   | [BRS] Clear the list of regions                                                                                   |                                               |
   +-------------+-------------------------------------------------------------------------------------------------------------------+-----------------------------------------------+
   
.. table:: Event Type

   +-------------+----------------------------------------+
   | Event ID    | Description                            |
   +=============+========================================+
   | 0x0 (0)     | Event "Command"                        |
   +-------------+----------------------------------------+
   | 0x1 (1)     | Event "Button"                         |
   +-------------+----------------------------------------+
   | 0x2 (2)     | Event "Pointer"                        |
   +-------------+----------------------------------------+
   | 0x3 (3)     | Event "State"                          |
   +-------------+----------------------------------------+
   | 0x4 (4)     | Event "Unknwon"                        |
   +-------------+----------------------------------------+
   | 0x5 (5)     | Event "Call Serially"                  |
   +-------------+----------------------------------------+
   | 0x6 (6)     | Event "MicroUI Stop"                   |
   +-------------+----------------------------------------+
   | 0x7 (7)     | Event "Input"                          |
   +-------------+----------------------------------------+
   | 0x8 (8)     | Event "Show Displayable"               |
   +-------------+----------------------------------------+
   | 0x9 (9)     | Event "Hide Displayable"               |
   +-------------+----------------------------------------+
   | 0xb (11)    | Event "Pending Flush"                  |
   +-------------+----------------------------------------+
   | 0xc (12)    | Event "Force Flush"                    |
   +-------------+----------------------------------------+
   | 0xd (13)    | Event "Repaint Displayable"            |
   +-------------+----------------------------------------+
   | 0xe (14)    | Event "Repaint Current Displayable"    |
   +-------------+----------------------------------------+
   | 0xf (15)    | Event "KF Stop Feature"                |
   +-------------+----------------------------------------+

   
.. table:: Create Image

   +-------------+----------------------------------------+
   | Event ID    | Description                            |
   +=============+========================================+
   | 0x0 (0)     | Create BufferedImage                   |
   +-------------+----------------------------------------+
   | 0x1 (1)     | Create Image from path                 |
   +-------------+----------------------------------------+
   | 0x2 (2)     | Create Image from InputStream          |
   +-------------+----------------------------------------+

.. table:: Image Type

   +-------------+----------------------------------------------------------------+
   | Event ID    | Description                                                    |
   +=============+================================================================+
   | 0x0 (0)     | New BufferedImage                                              |
   +-------------+----------------------------------------------------------------+
   | 0x1 (1)     | Load MicroEJ Image from RAW file                               |
   +-------------+----------------------------------------------------------------+
   | 0x2 (2)     | New MicroEJ Image from encoded image                           |
   +-------------+----------------------------------------------------------------+
   | 0x3 (3)     | New MicroEJ Image from RAW image in external memory            |
   +-------------+----------------------------------------------------------------+
   | 0x4 (4)     | New MicroEJ Image from encoded image in external memory        |
   +-------------+----------------------------------------------------------------+
   | 0x5 (5)     | New MicroEJ Image from memory InputStream                      |
   +-------------+----------------------------------------------------------------+
   | 0x6 (6)     | New MicroEJ Image from byte array InputStream                  |
   +-------------+----------------------------------------------------------------+
   | 0x7 (7)     | New MicroEJ Image from generic InputStream                     |
   +-------------+----------------------------------------------------------------+
   | 0x8 (8)     | Link Image                                                     |
   +-------------+----------------------------------------------------------------+

.. table:: Drawing Type

   +-------------+--------------------------------------------+
   | Event ID    | Description                                |
   +=============+============================================+
   | 0x1 (1)     | Write pixel                                |
   +-------------+--------------------------------------------+
   | 0x2 (2)     | Draw line                                  |
   +-------------+--------------------------------------------+
   | 0x3 (3)     | Draw horizontal line                       |
   +-------------+--------------------------------------------+
   | 0x4 (4)     | Draw vertical line                         |
   +-------------+--------------------------------------------+
   | 0x5 (5)     | Draw rectangle                             |
   +-------------+--------------------------------------------+
   | 0x6 (6)     | Fill rectangle                             |
   +-------------+--------------------------------------------+
   | 0x7 (7)     | Unknown                                    |
   +-------------+--------------------------------------------+
   | 0x8 (8)     | Draw rounded rectangle                     |
   +-------------+--------------------------------------------+
   | 0x9 (9)     | Fill rounded rectangle                     |
   +-------------+--------------------------------------------+
   | 0xa (10)    | Draw circle arc                            |
   +-------------+--------------------------------------------+
   | 0xb (11)    | Fill circle arc                            |
   +-------------+--------------------------------------------+
   | 0xc (12)    | Draw ellipse arc                           |
   +-------------+--------------------------------------------+
   | 0xd (13)    | Fill ellipse arc                           |
   +-------------+--------------------------------------------+
   | 0xe (14)    | Draw ellipse                               |
   +-------------+--------------------------------------------+
   | 0xf (15)    | Fill ellipse                               |
   +-------------+--------------------------------------------+
   | 0x10 (16)   | Draw circle                                |
   +-------------+--------------------------------------------+
   | 0x11 (17)   | Fill circle                                |
   +-------------+--------------------------------------------+
   | 0x12 (18)   | Draw ARGB array                            |
   +-------------+--------------------------------------------+
   | 0x13 (19)   | Draw image                                 |
   +-------------+--------------------------------------------+
   | 0x14 (20)   | Draw string                                |
   +-------------+--------------------------------------------+
   | 0x15 (21)   | Get string width                           |
   +-------------+--------------------------------------------+
   | 0x32 (50)   | Draw polygon                               |
   +-------------+--------------------------------------------+
   | 0x33 (51)   | Fill polygon                               |
   +-------------+--------------------------------------------+
   | 0x34 (52)   | Get ARGB image data                        |
   +-------------+--------------------------------------------+
   | 0x3b (59)   | Get pixel                                  |
   +-------------+--------------------------------------------+
   | 0x64 (100)  | Draw thick faded point                     |
   +-------------+--------------------------------------------+
   | 0x65 (101)  | Draw thick faded line                      |
   +-------------+--------------------------------------------+
   | 0x66 (102)  | Draw thick faded circle                    |
   +-------------+--------------------------------------------+
   | 0x67 (103)  | Draw thick faded circle arc                |
   +-------------+--------------------------------------------+
   | 0x68 (104)  | Draw thick faded ellipse                   |
   +-------------+--------------------------------------------+
   | 0x69 (105)  | Draw thick line                            |
   +-------------+--------------------------------------------+
   | 0x6a (106)  | Draw thick circle                          |
   +-------------+--------------------------------------------+
   | 0x6b (107)  | Draw thick ellipse                         |
   +-------------+--------------------------------------------+
   | 0x6c (108)  | Draw thick circle arc                      |
   +-------------+--------------------------------------------+
   | 0xc8 (200)  | Draw image with fli                        |
   +-------------+--------------------------------------------+
   | 0xc9 (201)  | Draw image with rotation (simple)          |
   +-------------+--------------------------------------------+
   | 0xca (202)  | Draw image with rotation (bilinear)        |
   +-------------+--------------------------------------------+
   | 0xcb (203)  | Draw image with scalling (simple)          |
   +-------------+--------------------------------------------+
   | 0xcc (204)  | Draw image with scalling (bilinear)        |
   +-------------+--------------------------------------------+
   | 0xcd (205)  | Draw string with scaling (bilinear)        |
   +-------------+--------------------------------------------+
   | 0xce (206)  | Draw character with rotation (bilinear)    |
   +-------------+--------------------------------------------+
   | 0xcf (207)  | Draw character with rotation (simple)      |
   +-------------+--------------------------------------------+

.. table:: Drawing Status

   +-------------+--------------------------------------------+
   | Event ID    | Description                                |
   +=============+============================================+
   | 0x0 (0)     | Synchronous drawing done                   |
   +-------------+--------------------------------------------+
   | 0x1 (1)     | Asynchronous drawing runs                  |
   +-------------+--------------------------------------------+

SystemView Integration
----------------------

The traces are :ref:`systemview` compatible.

.. figure:: images/microui_traces_systemview.png
   :alt: MicroUI Traces displayed in SystemView
   :align: center

   MicroUI Traces displayed in SystemView

The following text can be copied in a file called ``SYSVIEW_MicroUI.txt`` and copied in SystemView installation folder (e.g. ``SEGGER/SystemView_V252a/Description/``).

.. warning:: These traces are only compatible with the latest pack available (|UIPACKVERSION|).

.. code-block::

   NamedType UIEvent 0=COMMAND
   NamedType UIEvent 1=BUTTON
   NamedType UIEvent 2=POINTER
   NamedType UIEvent 3=STATE
   NamedType UIEvent 4=UNKNOWN
   NamedType UIEvent 5=CALLSERIALLY
   NamedType UIEvent 6=STOP
   NamedType UIEvent 7=INPUT
   NamedType UIEvent 8=SHOW_DISPLAYABLE
   NamedType UIEvent 9=HIDE_DISPLAYABLE
   NamedType UIEvent 11=PENDING_FLUSH
   NamedType UIEvent 12=FORCE_FLUSH
   NamedType UIEvent 13=REPAINT_DISPLAYABLE
   NamedType UIEvent 14=REPAINT_CURRENT_DISPLAYABLE
   NamedType UIEvent 15=KF_STOP_FEATURE

   NamedType UINewImage 0=MUTABLE_IMAGE
   NamedType UINewImage 1=IMAGE_FROM_PATH
   NamedType UINewImage 2=IMAGE_FROM_INPUTSTREAM

   NamedType UIImageData 0=NEW_IMAGE
   NamedType UIImageData 1=LOAD_MICROEJ
   NamedType UIImageData 2=NEW_ENCODED
   NamedType UIImageData 3=NEW_MICROEJ_EXTERNAL
   NamedType UIImageData 4=NEW_ENCODED_EXTERNAL
   NamedType UIImageData 5=MEMORY_INPUTSTREAM
   NamedType UIImageData 6=BYTEARRAY_INPUTSTREAM
   NamedType UIImageData 7=GENERIC_INPUTSTREAM
   NamedType UIImageData 8=LINK_IMAGE

   NamedType GEDraw 1=WRITE_PIXEL
   NamedType GEDraw 2=DRAW_LINE
   NamedType GEDraw 3=DRAW_HORIZONTALLINE
   NamedType GEDraw 4=DRAW_VERTICALLINE
   NamedType GEDraw 5=DRAW_RECTANGLE
   NamedType GEDraw 6=FILL_RECTANGLE
   NamedType GEDraw 7=UNKNOWN
   NamedType GEDraw 8=DRAW_ROUNDEDRECTANGLE
   NamedType GEDraw 9=FILL_ROUNDEDRECTANGLE
   NamedType GEDraw 10=DRAW_CIRCLEARC
   NamedType GEDraw 11=FILL_CIRCLEARC
   NamedType GEDraw 12=DRAW_ELLIPSEARC
   NamedType GEDraw 13=FILL_ELLIPSEARC
   NamedType GEDraw 14=DRAW_ELLIPSE
   NamedType GEDraw 15=FILL_ELLIPSE
   NamedType GEDraw 16=DRAW_CIRCLE
   NamedType GEDraw 17=FILL_CIRCLE
   NamedType GEDraw 18=DRAW_ARGB
   NamedType GEDraw 19=DRAW_IMAGE
   NamedType GEDraw 20=DRAW_STRING
   NamedType GEDraw 21=STRING_WIDTH

   NamedType GEDraw 50=DRAW_POLYGON
   NamedType GEDraw 51=FILL_POLYGON
   NamedType GEDraw 52=GET_IMAGEARGB
   NamedType GEDraw 59=GET_PIXEL

   NamedType GEDraw 100=DRAW_THICKFADEDPOINT
   NamedType GEDraw 101=DRAW_THICKFADEDLINE
   NamedType GEDraw 102=DRAW_THICKFADEDCIRCLE
   NamedType GEDraw 103=DRAW_THICKFADEDCIRCLEARC
   NamedType GEDraw 104=DRAW_THICKFADEDELLIPSE
   NamedType GEDraw 105=DRAW_THICKLINE
   NamedType GEDraw 106=DRAW_THICKCIRCLE
   NamedType GEDraw 107=DRAW_THICKELLIPSE
   NamedType GEDraw 108=DRAW_THICKCIRCLEARC

   NamedType GEDraw 200=DRAW_FLIPPEDIMAGE
   NamedType GEDraw 201=DRAW_ROTATEDIMAGENEARESTNEIGHBOR
   NamedType GEDraw 202=DRAW_ROTATEDIMAGEBILINEAR
   NamedType GEDraw 203=DRAW_SCALEDIMAGENEARESTNEIGHBOR
   NamedType GEDraw 204=DRAW_SCALEDIMAGEBILINEAR
   NamedType GEDraw 205=DRAW_SCALEDCHARSBILINEAR
   NamedType GEDraw 206=DRAW_CHARWITHROTATIONBILINEAR
   NamedType GEDraw 207=DRAW_CHARWITHROTATIONNEARESTNEIGHBOR

   NamedType GEDrawAsync 0=done
   NamedType GEDrawAsync 1=started

   #
   # MicroUI
   #
   0        UI_EGEvent         (MicroUI) Execute EventGenerator event %UIEvent (generatorID = %u, data = %p)   | (MicroUI) EventGenerator event %UIEvent done
   1        UI_DROPEvent       (MicroUI) Drop event %p
   2        UI_InputEvent      (MicroUI) Execute native input event %UIEvent (generatorID = %u, event = %p)    | (MicroUI) Native input event %UIEvent done
   3        UI_DisplayEvent    (MicroUI) Execute display event %UIEvent (event = %p)                           | (MicroUI) Display event %UIEvent done
   4        UI_UserEvent       (MicroUI) Execute user event %p                                                 | (MicroUI) User event %p done
   5        UI_OpenImage       (MicroUI) Create %UINewImage                                                    | (MicroUI) Image created, id = %p
   6        UI_ImageData       (MicroUI) %UINewImage %UIImageData, id = %p, size = %d*%d

   #
   # MicroUI Graphics Engine
   #
   11       GE_FlushDone       (MicroUI GraphicsEngine) Flush done
   15       GE_GPUDrawDone     (MicroUI GraphicsEngine) Asynchronous drawing operation done

   #
   # MicroUI Event Engine
   #
   20       EE_InvalidEvent    (MicroUI Event Engine) Invalid event: %p
   21       EE_QueueFull       (MicroUI Event Engine) Queue full, cannot add event %p
   22       EE_AddEvent        (MicroUI Event Engine) Add event %p (index = %u / queue length = %u)
   23       EE_ReplaceEvent    (MicroUI Event Engine) Replace event %p by %p (index = %u / queue length = %u)
   24       EE_ReadEvent       (MicroUI Event Engine) Read event %p (index %u)

   #
   # MicroUI CCO
   #
   40       UI_Draw            (MicroUI) Drawing operation %GEDraw                   | (MicroUI) Drawing operation %GEDrawAsync

   50       BRS_NewDrawing     (BRS) New drawing region (%u,%u) to (%u,%u)
   51       BRS_FlushSingle    (BRS) Flush LCD (id=%u buffer=%p) single region (%u,%u) to (%u,%u)
   52       BRS_FlushMulti     (BRS) Flush LCD (id=%u buffer=%p) %u regions
   53       BRS_AddRegion      (BRS) Add region (%u,%u) to (%u,%u)
   54       BRS_RemoveRegion   (BRS) Remove region (%u,%u) to (%u,%u)
   55       BRS_RestoreRegion  (BRS) Restore region (%u,%u) to (%u,%u)
   56       BRS_ClearList      (BRS) Clear the list of regions


.. hint:: Retrieve a compatible file with the VEE Port's UI Pack in the UI Pack (open it with as a zip): in the VEE Port configuration project, open ``[veeport-configuration]\target~\dependencies\[architecture]-ui-pack.xpfp\build\fragments\microui\content\lib\SYSVIEW_MicroUI.txt``.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
