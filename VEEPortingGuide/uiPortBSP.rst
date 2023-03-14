.. _ui_port_bsp:

========
BSP Port
========

Principle
=========

The BSP Port (or Embedded Port) involves implementing some Low-level API.
There are several kinds of LLAPI:

- The mandatory LLAPI to manipulate the LEDs,
- The mandatory LLAPI to send the input events,
- The mandatory LLAPI to initialize, use and flush the drawings to the display,
- The optional LLAPI to customize the Graphics Engine to be compatible with the display constraints,
- The optional LLAPI to manipulate the optional display features (backlight, contrast, etc.),
- The optional LLAPI to add some features as new image decoders,
- The optional LLAPI to use a GPU.

The following chapters describe the first points. 
For the GPU acceleration, see :ref:`ui_port_gpu`.

MicroUI C Module
================

The UI Pack **requires** the MicroUI C module. 
This C module 

- implements some MicroUI native functions,
- manages the drawings synchronization with the Graphics Engine,
- features an image heap allocator,
- features an input events decoder.

Before all, install the MicroUI C Module:

1. Find the correct version of the C module according to the UI Pack version; see :ref:`section_ui_releasenotes_cmodule`.
2. Add the C module dependency in the VEE Port ivy file (or unzip it in the BSP project):

.. code-block:: xml

   <dependency org="com.microej.clibrary.llimpl" name="microui" rev="2.0.1"/>

3. Add the mandatory files in the BSP project: ``LLDW_PAINTER_impl.c`` and ``LLUI_PAINTER_impl.c``.
4. Add the optional files in the BSP project: 
 
   - ``LLUI_DISPLAY_HEAP_impl.c``: to use another image heap allocator,
   - ``LLUI_INPUT_LOG_impl.c`` and ``microui_event_decoder.c``: to decode the MicroUI event (input events and MicroUI internal events).
  

LEDs
====

As soon as the VEE Port Configuration project LEDs module is checked, the VEE Port features the header file LLAPI ``LLUI_LED_impl.h``.
This header must be implemented.
The mandatory functions to implement are:

- ``LLUI_LED_IMPL_initialize``: initialize the LED driver (if required) and return the available number of LEDs.
- ``LLUI_LED_IMPL_getIntensity``: return, if possible, the LED intensity.
- ``LLUI_LED_IMPL_setIntensity``: set the LED intensity.

Refer to :ref:`section_leds_llapi` to have more information.
Refer too to the C-doc in the header file itself.

Inputs
======

The VEE Port always features the header file LLAPI  ``LLUI_INPUT_impl.h``.
This header must be implemented even if there is no input device: the critical section management is required by the MicroUI library itself.
The mandatory functions to implement are:

- ``LLUI_INPUT_IMPL_initialize``: can be empty if nothing is to initialize.
- ``LLUI_INPUT_IMPL_getInitialStateValue``: empty if there is no State Event Generator.
- ``LLUI_INPUT_IMPL_enterCriticalSection``: disable all input events (disable input devices interrupts and/or disable the OS scheduling).
- ``LLUI_INPUT_IMPL_leaveCriticalSection``: re-enable all inputs events.

Refer to :ref:`section_input_llapi` to have more information.
Refer too to the C-doc in the header file itself.

Display
=======

As soon as the VEE Port Configuration project Display module is checked, the VEE Port features the header file LLAPI ``LLUI_DISPLAY_impl.h``.
This header must be implemented.
The mandatory functions to implement are:

- ``LLUI_DISPLAY_IMPL_initialize``: fill the given structure ``LLUI_DISPLAY_SInitData`` (display size, buffer address, etc.).
- ``LLUI_DISPLAY_IMPL_binarySemaphoreTake``: *takes* the given semaphore.
- ``LLUI_DISPLAY_IMPL_binarySemaphoreGive``: *gives* the given semaphore.
- ``LLUI_DISPLAY_IMPL_flush``: copy/send the buffer content to the LCD.

Refer to :ref:`section_display_llapi` to have more information.
Refer too to the C-doc in the header file itself.

Once implemented, run the UI test suite of the Port Qualification Toolkit to validate the implementation.
Refer to :ref:`platform_testsuite` to have more information.

Display: LCD Constraints
========================

According to the LCD constraints (see :ref:`ui_port_conf`), some additional LLAPI must be implemented:

- ``LLUI_DISPLAY_IMPL_convertARGBColorToDisplayColor`` and ``LLUI_DISPLAY_IMPL_convertDisplayColorToARGBColor``: required when the pixel format is custom (not standard, see :ref:`section_display_implementation`).
- ``LLUI_DISPLAY_IMPL_prepareBlendingOfIndexedColors``: required when the display buffer is a LUT buffer, not a pixel buffer.
- ``LLUI_DISPLAY_IMPL_isDoubleBuffered``: the default implementation returns always ``true``; only useful as information for the application.
- ``LLUI_DISPLAY_IMPL_isColor``: the default implementation always returns ``true`` when the BPP is higher than 8; only useful as information for the application.
- ``LLUI_DISPLAY_IMPL_getNumberOfColors``: the default implementation returns always ``1 << BPP``; only useful as information for the application.

Display: Optional Features
==========================

Several kinds of features can be implemented.

**Hardware features:**

- ``LLUI_DISPLAY_IMPL_setContrast`` and ``LLUI_DISPLAY_IMPL_getContrast``: to configure the display contrast.
- ``LLUI_DISPLAY_IMPL_hasBacklight``, ``LLUI_DISPLAY_IMPL_setBacklight`` and ``LLUI_DISPLAY_IMPL_getBacklight``: to turn on or off the display backlight.

**Runtime Image Decoders**

The BSP can add some runtime image decoders with the runtime decoders selected in the VEE Port configuration project (modules PNG and BMP Monochrom decoders).

- ``LLUI_DISPLAY_IMPL_decodeImage``: called by MicroUI to decode an image whose format is unknown by the internal runtime image decoders.

**Image Heap Management**

By default, a best-fit allocator manages the image heap.
To add another allocator, implement these functions:

- ``LLUI_DISPLAY_IMPL_image_heap_initialize``: initialize the allocator.
- ``LLUI_DISPLAY_IMPL_image_heap_allocate``: allocates the expected buffer.
- ``LLUI_DISPLAY_IMPL_image_heap_free``: frees the given buffer.

**MicroUI Image Management**

The three functions are only helpful for compatibility with a GPU; see :ref:`ui_port_gpu`.

- ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes``
- ``LLUI_DISPLAY_IMPL_adjustNewImageCharacteristics``
- ``LLUI_DISPLAY_IMPL_initializeNewImage``




..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
