.. _LLAPI-CHAPTER:

=========================
Appendix A: Low Level API
=========================


This chapter describes succinctly the available Low Level API, module by
module. The exhaustive documentation of each LLAPI function is available
in the LLAPI header files themselves. The required header files to
implement are automatically copied in the folder ``include`` of MicroEJ
Platform at platform build time.


.. _LLMJVM-API-SECTION:

LLMJVM: MicroEJ Core Engine
===========================

Naming Convention
-----------------

The Low Level MicroEJ Core Engine API, the ``LLMJVM`` API, relies on
functions that need to be implemented. The naming convention for such
functions is that their names match the ``LLMJVM_IMPL_*`` pattern.

Header Files
------------

Three C header files are provided:

-  LLMJVM_impl.h

   Defines the set of functions that the BSP must implement to launch
   and schedule the virtual machine

-  LLMJVM.h

   Defines the set of functions provided by virtual machine that can be
   called by the BSP when using the virtual machine

-  LLBSP_impl.h

   Defines the set of extra functions that the BSP must implement.


.. _LLKF-API-SECTION:

LLKERNEL: Multi-Sandbox
=======================

Naming Convention
-----------------

The Low Level Kernel API, the ``LLKERNEL`` API, relies on functions that
need to be implemented. The naming convention for such functions is that
their names match the ``LLKERNEL_IMPL_*`` pattern.

Header Files
------------

One C header file is provided:

-  LLKERNEL_impl.h

   Defines the set of functions that the BSP must implement to manage
   memory allocation of dynamically installed applications.


.. _LLSP-API-SECTION:

LLSP: Shielded Plug
===================

Naming Convention
-----------------

The Low Level Shielded Plug API, the ``LLSP`` API, relies on functions
that need to be implemented. The naming convention for such functions is
that their names match the ``LLSP_IMPL_*`` pattern.  

Header Files
------------

The implementation of the :ref:`[SP] <esr-specifications>` for the MicroEJ Platform assumes some
support from the underlying RTOS. It is mainly related to provide some
synchronization when reading / writing into Shielded Plug blocks.

-  ``LLSP_IMPL_syncWriteBlockEnter`` and
   ``LLSP_IMPL_syncWriteBlockExit`` are used as a semaphore by RTOS
   tasks. When a task wants to write to a block, it "locks" this block
   until it has finished to write in it.

-  ``LLSP_IMPL_syncReadBlockEnter`` and ``LLSP_IMPL_syncReadBlockExit``
   are used as a semaphore by RTOS tasks. When a task wants to read a
   block, it "locks" this block until it is ready to release it.

The :ref:`[SP] specification <esr-specifications>` provides a mechanism to force a task to wait
until new data has been provided to a block. The implementation relies
on functions ``LLSP_IMPL_wait`` and ``LLSP_IMPL_wakeup`` to block the
current task and to reschedule it.


.. _LLEXT_RES-API-SECTION:

LLEXT_RES: External Resources Loader
====================================

Principle
---------

This LLAPI allows to use the External Resource Loader. When installed,
the External Resource Loader is notified when the MicroEJ Core Engine is
not able to find a resource (an image, a file etc.) in the resources
area linked with the MicroEJ Core Engine.

When a resource is not available, the MicroEJ Core Engine invokes the
External Resource Loader in order to load an unknown resource. The
External Resource Loader uses the LLAPI EXT_RES to let the BSP loads or
not the expected resource. The implementation has to be able to load
several files in parallel.

Naming Convention
-----------------

The Low Level API, the ``LLEXT_RES`` API, relies on functions that need
to be implemented. The naming convention for such functions is that
their names match the ``LLEXT_RES_IMPL_*`` pattern.  

Header Files
------------

One header file is provided:

-  LLEXT_RES_impl.h

   Defines the set of functions that the BSP must implement to load some
   external resources.


.. _LLCOMM-API-SECTION:

LLCOMM: Serial Communications
=============================

Naming Convention
-----------------

The Low Level Comm API (LLCOMM), relies on functions that need to be
implemented by engineers in a driver. The names of these functions match
the ``LLCOM_BUFFERED_CONNECTION_IMPL_*`` or the
``LLCOM_CUSTOM_CONNECTION_IMPL_*``\ pattern.

Header Files
------------

Four C header files are provided:

-  LLCOMM_BUFFERED_CONNECTION_impl.h

   Defines the set of functions that the driver must implement to
   provide a Buffered connection

-  LLCOMM_BUFFERED_CONNECTION.h

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Buffered connection

-  LLCOMM_CUSTOM_CONNECTION_impl.h

   Defines the set of functions that the driver must implement to
   provide a Custom connection

-  LLCOMM_CUSTOM_CONNECTION.h

   Defines the set of functions provided by ECOM Comm that can be called
   by the driver (or other C code) when using a Custom connection


.. _LLINPUT-API-SECTION:

LLUI_INPUT: Inputs
==================

``LLUI_INPUT`` API is composed of the following files:

-  the file ``LLUI_INPUT_impl.h`` that defines the functions to be
   implemented

-  the file ``LLUI_INPUT.h`` that provides the functions for sending events

Implementation
--------------

``LLUI_INPUT_IMPL_initialize`` is the first function called by the input
engine, and it may be used to initialize the underlying devices and bind
them to event generator IDs.

``LLUI_INPUT_IMPL_enterCriticalSection`` and
``LLUI_INPUT_IMPL_exitCriticalSection``  need to provide the input engine with a
critical section mechanism for synchronizing devices when sending events
to the internal event queue. The mechanism used to implement the
synchronization will depend on the platform configuration (with or
without RTOS), and whether or not events are sent from an interrupt
context.

``LLUI_INPUT_IMPL_getInitialStateValue`` allows the input stack to get the
current state for devices connected to the MicroUI States event
generator, such as switch selector, coding wheels, etc.

Sending Events
--------------

The ``LLUI_INPUT`` API provides two generic functions for a C driver to
send data to its associated event generator:

-  ``LLUI_INPUT_sendEvent``:  Sends a 32-bits event to a specific event generator, specified by its ID. If the input buffer is full, the event is not added, and the function returns ``LLUI_INPUT_NOK``; otherwise it returns ``LLUI_INPUT_OK``.

-  ``LLUI_INPUT_sendEvents``: Sends a frame constitued by several 32-bits events to a specific event generator, specified by its ID. If the input buffer cannot receive the whole data, the frame is not added, and the function returns ``LLUI_INPUT_NOK``; otherwise it returns ``LLUI_INPUT_OK``.

Events will be dispatched to the associated event generator that will be
responsible for decoding them (see :ref:`javaEventGenerators`).

The UI extension provides an implementation for each of MicroUI's
built-in event generators. Each one has dedicated functions that allows
a driver to send them structured data without needing to understand the
underlying protocol to encode/decode the data.
:ref:`The following table <table_llinputApiEvtGen>` shows the functions provided to send
structured events to the predefined event generators:

.. _table_llinputApiEvtGen:
.. tabularcolumns:: |p{5.5cm}|p{2cm}|p{6.5cm}|
.. table:: LLUI_INPUT API for predefined event generators

   +----------------------------------------+-----------+-----------------------------------------+
   | Function name                          | Default   | Comments                                |
   |                                        | event     |                                         |
   |                                        | generator |                                         |
   |                                        | kind [1]_ |                                         |
   |                                        |           |                                         |
   |                                        |           |                                         |
   +========================================+===========+=========================================+
   | ``LLUI_INPUT_sendCommandEvent``        | Command   | Constants are provided that             |
   |                                        |           | define all standard MicroUI             |
   |                                        |           | commands [MUI].                         |
   +----------------------------------------+-----------+-----------------------------------------+
   | ``LLUI_INPUT_sendButtonPressedEvent``  | Buttons   | In the case of                          |
   |                                        |           | chronological sequences                 |
   |                                        |           | (for example, a RELEASE                 |
   | ``LLUI_INPUT_sendButtonReleasedEvent`` |           | that may occur only after a             |
   |                                        |           | PRESSED), it is the                     |
   |                                        |           | responsibility of the                   |
   | ``LLUI_INPUT_sendButtonRepeatedEvent`` |           | driver to ensure the                    |
   |                                        |           | integrity of such                       |
   |                                        |           | sequences.                              |
   | ``LLUI_INPUT_sendButtonLongEvent``     |           |                                         |
   |                                        |           |                                         |
   +----------------------------------------+-----------+-----------------------------------------+
   | ``LLUI_INPUT_sendPointerPressedEvent`` | Pointer   | In the case of                          |
   |                                        |           | chronological sequences                 |
   |                                        |           | (for example, a RELEASE                 |
   | ``LLUI_INPUT_sendPointerReleasedEvent``|           | that may occur only after a             |
   |                                        |           | PRESSED), it is the                     |
   |                                        |           | responsibility of the                   |
   | ``LLUI_INPUT_sendPointerMovedEvent``   |           | driver to ensure the                    |
   |                                        |           | integrity of such                       |
   |                                        |           | sequences. Depending on                 |
   |                                        |           | whether a button of the                 |
   |                                        |           | pointer is pressed while                |
   |                                        |           | moving, a DRAG and/or a                 |
   |                                        |           | MOVE MicroUI event is                   |
   |                                        |           | generated.                              |
   +----------------------------------------+-----------+-----------------------------------------+
   | ``LLUI_INPUT_sendStateEvent``          | States    | The initial value of each               |
   |                                        |           | state machine (of a States)             |
   |                                        |           | is retrieved by a call to               |
   |                                        |           | ``LLUI_INPUT_IMPL_getInitialStateValue``|
   |                                        |           | that must be implemented by             |
   |                                        |           | the device. Alternatively,              |
   |                                        |           | the initial value can be                |
   |                                        |           | specified in the XML static             |
   |                                        |           | configuration.                          |
   +----------------------------------------+-----------+-----------------------------------------+
   | ``LLUI_INPUT_sendTouchPressedEvent``   | Pointer   | In the case of                          |
   |                                        |           | chronological sequences                 |
   |                                        |           | (for example, a RELEASE                 |
   | ``LLUI_INPUT_sendTouchReleasedEvent``  |           | that may only occur after a             |
   |                                        |           | PRESSED), it is the                     |
   |                                        |           | responsibility of the                   |
   | ``LLUI_INPUT_sendTouchMovedEvent``     |           | driver to ensure the                    |
   |                                        |           | integrity of such                       |
   |                                        |           | sequences. These APIs will              |
   |                                        |           | generate a DRAG MicroUI                 |
   |                                        |           | event instead of a MOVE                 |
   |                                        |           | while they represent a                  |
   |                                        |           | touch pad over a display.               |
   +----------------------------------------+-----------+-----------------------------------------+

Event Buffer
------------

The maximum usage of the internal event buffer may be retrieved at
runtime using the ``LLUI_INPUT_getMaxEventsBufferUsage`` function. This is
useful for tuning the size of the buffer.

.. [1]
   The implementation class is a subclass of the MicroUI class of the
   column.


.. _LLDISPLAY-API-SECTION:

LLUI_DISPLAY: Display
=====================

Principle & Naming Convention
-----------------------------

Each display engine provides a low level API in order to connect a display driver. The file ``LLUI_DISPLAY_impl.h`` defines the API headers to be implemented. For the APIs themselves, the naming convention is that their names match the ``*_IMPL_*`` pattern when the functions need to be implemented:

* ``LLUI_DISPLAY_IMPL_initialize``
* ``LLUI_DISPLAY_IMPL_binarySemaphoreTake``
* ``LLUI_DISPLAY_IMPL_binarySemaphoreGive``
* ``LLUI_DISPLAY_IMPL_flush``

Some additional low level API allow you to connect display extra features. These LLAPIs are not required. When they are not implemented, a default implementation is used (weak function). It concerns backlight, contrast etc.

This describes succinctly some ``LLUI_DISPLAY_IMPL`` functions. Please refer to documentation inside header files to have more information. 

Initialization
--------------

Each display engine gets initialized by calling the function ``LLUI_DISPLAY_IMPL_initialize``: It asks its display driver to initialize itself. The implementation function has to fill the given structure ``LLUI_DISPLAY_SInitData``. This structure allows to retrieve the size of the virtual and physical screen, the back buffer address (where MicroUI is drawing). The implementation has too `give` two binary semaphores.

Image Heap
----------

The display driver must reserve a runtime memory buffer for creating dynamic images when using MicroUI ``ResouceImage`` and ``BufferedImage`` classes methods. The display driver may choose to reserve an empty buffer. Thus, calling MicroUI methods will result in a ``MicroUIException`` exception.

The section name is ``.bss.microui.display.imagesHeap``.

External Font Heap
------------------

The display driver must reserve a runtime memory buffer for loading external fonts (fonts located outside CPU addresses ranges). The display driver may choose to reserve an empty buffer. Thus, calling MicroUI ``Font`` methods will result in empty drawings of some characters.

The section name is ``.bss.microui.display.externalFontsHeap``.

Flush and Synchronization
-------------------------

The back buffer (graphics buffer) address set in Initialization function is the address for the very first drawing. The content of this buffer is flushed to the external display memory by the function ``LLUI_DISPLAY_flush``. The parameters define the rectangular area of the content which has changed during the last drawing action, and which must be flushed to the display buffer (dirty area). This function should be atomic: the implementation has to start another task or a hardware device (often a DMA) to perform the copy.

As soon as the application performs a new drawing, the display engine locks the thread. It will automatically unlocked when the BSP will call ``LLUI_DISPLAY_flushDone`` at the end of the copy, 

Display Characteristics
-----------------------

Function ``LLUI_DISPLAY_IMPL_isColor`` directly implements the method from the MicroUI ``Display`` class of the same name. The default implementation always returns ``true`` when the number of bits per pixel is higher than 4.

Function ``LLUI_DISPLAY_IMPL_getNumberOfColors`` directly implements the method from the MicroUI ``Display`` class of the same name. The default implementation returns a value according to the number of bits by pixel, without taking into consideration the alpha bit(s).

Function ``LLUI_DISPLAY_IMPL_isDoubleBuffered`` directly implements the method from the MicroUI ``Display`` class of the same name. The default implementation returns ``true``. When LLAPI implementation targets a LCD in ``direct`` mode, this function must be implemented and return ``false``.

Contrast
--------

``LLUI_DISPLAY_IMPL_setContrast`` and ``LLUI_DISPLAY_IMPL_getContrast`` are called to set/get the current display contrast intensity. The default implementations don't manage the contrast.

BackLight
---------

``LLUI_DISPLAY_IMPL_hasBacklight`` indicates whether the display has backlight capabilities.

``LLUI_DISPLAY_IMPL_setBacklight`` and ``LLUI_DISPLAY_IMPL_getBacklight`` are called to set/get the current display backlight intensity.

.. _colorConversions:

Color Conversions
-----------------

The following functions are only useful (and called) when the display is not a standard display, see :ref:`display_pixel_structure`.

``LLUI_DISPLAY_IMPL_convertARGBColorToDisplayColor`` is called to convert a 32-bit ARGB MicroUI color in ``0xAARRGGBB`` format into the "driver" display color.

``LLUI_DISPLAY_IMPL_convertDisplayColorToARGBColor`` is called to convert a display color to a 32-bit ARGB MicroUI color.

LUT
---

The function ``LLUI_DISPLAY_IMPL_prepareBlendingOfIndexedColors`` is called when drawing an image with indexed color. See :ref:`display_lut` to have more information about indexed images.

Image Decoders
--------------

The API ``LLUI_DISPLAY_IMPL_decodeImage`` allows to add some additional :ref:`image decoders<image_external_decoder>`. 

.. _LLLEDS-API-SECTION:

LLUI_LED: LEDs
==============

Principle
---------

The LEDs engine provides a Low Level API for connecting LED drivers. The file ``LLUI_LED_impl.h``, which comes with the LEDs engine, defines the API headers to be implemented.

Naming Convention
-----------------

The Low Level API relies on functions that must be implemented. The naming convention for such functions is that their names match the ``*_IMPL_*`` pattern.

Initialization
--------------

The first function called is ``LLUI_LED_IMPL_initialize``, which allows the driver to initialize all LED devices. This method must return the available number of LEDs. Each LED has a unique identifier. The first LED has the ID 0, and the last has the ID NbLEDs – 1.

This UI extension provides support to efficiently implement the set of methods that interact with the LEDs provided by a device. Below are the relevant C functions:

-  ``LLUI_LED_IMPL_getIntensity``: Get the intensity of a specific LED using its ID.

-  ``LLUI_LED_IMPL_setIntensity``: Set the intensity of an LED using its ID.


.. _LLNET-API-SECTION:

LLNET: Network
==============

Naming Convention
-----------------

The Low Level API, the ``LLNET`` API, relies on functions that need to
be implemented. The naming convention for such functions is that their
names match the ``LLNET_IMPL_*`` pattern.

Header Files
------------

Several header files are provided:

-  LLNET_CHANNEL_impl.h

   Defines a set of functions that the BSP must implement to initialize
   the Net native component. It also defines some configuration
   operations to setup a network connection.

-  LLNET_SOCKETCHANNEL_impl.h

   Defines a set of functions that the BSP must implement to create,
   connect and retrieve information on a network connection.

-  LLNET_STREAMSOCKETCHANNEL_impl.h

   Defines a set of functions that the BSP must implement to do some I/O
   operations on connection oriented socket (TCP). It also defines
   function to put a server connection in accepting mode (waiting for a
   new client connection).

-  LLNET_DATAGRAMSOCKETCHANNEL_impl.h

   Defines a set of functions that the BSP must implement to do some I/O
   operations on connectionless oriented socket (UDP).

-  LLNET_DNS_impl.h

   Defines a set of functions that the BSP must implement to request
   host IP address associated to a host name or to request Domain Name
   Service (DNS) host IP addresses setup in the underlying system.

-  LLNET_NETWORKADDRESS_impl.h

   Defines a set of functions that the BSP must implement to convert
   string IP address or retrieve specific IP addresses (lookup,
   localhost or loopback IP address).

-  LLNET_NETWORKINTERFACE_impl.h

   Defines a set of functions that the BSP must implement to retrieve
   information on a network interface (MAC address, interface link
   status, etc.).


.. _LLNET_SSL-API-SECTION:

LLNET_SSL: SSL
==============

Naming Convention
-----------------

The Low Level API, the ``LLNET_SSL`` API, relies on functions that need
to be implemented. The naming convention for such functions is that
their names match the ``LLNET_SSL_*`` pattern.

Header Files
------------

Three header files are provided:

-  LLNET_SSL_CONTEXT_impl.h

   Defines a set of functions that the BSP must implement to create a
   SSL Context and to load CA (Certificate Authority) certificates as
   trusted certificates.

-  LLNET_SSL_SOCKET_impl.h

   Defines a set of functions that the BSP must implement to initialize
   the SSL native components, to create an underlying SSL Socket and to
   initiate a SSL session handshake. It also defines some I/O operations
   such as ``LLNET_SSL_SOCKET_IMPL_write`` or
   ``LLNET_SSL_SOCKET_IMPL_read`` used for encrypted data exchange
   between the client and the server.

-  LLNET_SSL_X509_CERT_impl.h

   Defines a function named ``LLNET_SSL_X509_CERT_IMPL_parse`` for
   certificate parsing. This function checks if a given certificate is
   an X.509 digital certificate and returns its encoded format type :
   Distinguished Encoding Rules (DER) or Privacy-Enchanced Mail (PEM).


.. _LLFS-API-SECTION:

LLFS: File System
=================

Naming Convention
-----------------

The Low Level File System API (LLFS), relies on functions that need to
be implemented by engineers in a driver. The names of these functions
match the ``LLFS_IMPL_*`` and the ``LLFS_File_IMPL_*`` pattern.

Header Files
------------

Two C header files are provided:

-  LLFS_impl.h

   Defines a set of functions that the BSP must implement to initialize
   the FS native component. It also defines some functions to manage
   files, directories and retrieve information about the underlying File
   System (free space, total space, etc.).

-  LLFS_File_impl.h

   Defines a set of functions that the BSP must implement to do some I/O
   operations on files (open, read, write, close, etc.).


.. _LLHAL-API-SECTION:

LLHAL: Hardware Abstraction Layer
=================================

Naming Convention
-----------------

The Low Level API, the ``LLHAL`` API, relies on functions that need to
be implemented. The naming convention for such functions is that their
names match the ``LLHAL_IMPL_*`` pattern.

Header Files
------------

One header file is provided:

-  LLHAL_impl.h

   Defines the set of functions that the BSP must implement to configure
   and drive some MCU GPIO.


.. _LLDEVICE-API-SECTION:

LLDEVICE: Device Information
============================

Naming Convention
-----------------

The Low Level Device API (LLDEVICE), relies on functions that need to be
implemented by engineers in a driver. The names of these functions match
the ``LLDEVICE_IMPL_*`` pattern.

Header Files
------------

One C header file is provided:

-  LLDEVICE_impl.h

   Defines a set of functions that the BSP must implement to get the
   platform architecture name and unique device identifier.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
