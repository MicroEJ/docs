=========================
Appendix A: Low Level API
=========================


This chapter describes succinctly the available Low Level API, module by
module. The exhaustive documentation of each LLAPI function is available
in the LLAPI header files themselves. The required header files to
implement are automatically copied in the folder ``include`` of MicroEJ
Platform at platform build time.


.. _LLMJVM-API-SECTION:

LLMJVM: MicroEJ core engine
===========================

Naming Convention
-----------------

The Low Level MicroEJ core engine API, the ``LLMJVM`` API, relies on
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

The implementation of the SP for the MicroEJ Platform assumes some
support from the underlying RTOS. It is mainly related to provide some
synchronization when reading / writing into Shielded Plug blocks.

-  ``LLSP_IMPL_syncWriteBlockEnter`` and
   ``LLSP_IMPL_syncWriteBlockExit`` are used as a semaphore by RTOS
   tasks. When a task wants to write to a block, it "locks" this block
   until it has finished to write in it.

-  ``LLSP_IMPL_syncReadBlockEnter`` and ``LLSP_IMPL_syncReadBlockExit``
   are used as a semaphore by RTOS tasks. When a task wants to read a
   block, it "locks" this block until it is ready to release it.

The [SP] specification provides a mechanism to force a task to wait
until new data has been provided to a block. The implementation relies
on functions ``LLSP_IMPL_wait`` and ``LLSP_IMPL_wakeup`` to block the
current task and to reschedule it.


.. _LLEXT_RES-API-SECTION:

LLEXT_RES: External Resources Loader
====================================

Principle
---------

This LLAPI allows to use the External Resource Loader. When installed,
the External Resource Loader is notified when the MicroEJ core engine is
not able to find a resource (an image, a file etc.) in the resources
area linked with the MicroEJ core engine.

When a resource is not available, the MicroEJ core engine invokes the
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

LLINPUT: Inputs
===============

``LLINPUT`` API is composed of the following files:

-  the file ``LLINPUT_impl.h`` that defines the functions to be
   implemented

-  the file ``LLINPUT.h`` that provides the functions for sending events

Implementation
--------------

``LLINPUT_IMPL_initialize`` is the first function called by the input
stack, and it may be used to initialize the underlying devices and bind
them to event generator IDs.

``LLINPUT_IMPL_enterCriticalSection`` and
``LLINPUT_IMPL_exitCriticalSection``  need to provide the stack with a
critical section mechanism for synchronizing devices when sending events
to the internal event queue. The mechanism used to implement the
synchronization will depend on the platform configuration (with or
without RTOS), and whether or not events are sent from an interrupt
context.

``LLINPUT_IMPL_getInitialStateValue`` allows the input stack to get the
current state for devices connected to the MicroUI States event
generator, such as switch selector, coding wheels, etc.

Sending Events
--------------

The ``LLINPUT`` API provides two generic functions for a C driver to
send data to its associated event generator:

-  ``LLINPUT_sendEvent``:  Sends a 32-bit encoded event to a specific
   event generator, specified by its ID. If the input buffer is full,
   the event is not added, and the function returns 0; otherwise it
   returns 1.

-  ``LLINPUT_sendEvents``: Sends event data to a specific event
   generator, specified by its ID. If the input buffer cannot receive
   the whole data, the event is not added, and the function returns 0;
   otherwise it returns 1.

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
.. table:: LLINPUT API for predefined event generators

   +--------------------------------------+-----------+---------------------------------------+
   | Function name                        | Default   | Comments                              |
   |                                      | event     |                                       |
   |                                      | generator |                                       |
   |                                      | kind [1]_ |                                       |
   |                                      |           |                                       |
   |                                      |           |                                       |
   +======================================+===========+=======================================+
   | ``LLINPUT_sendCommandEvent``         | Command   | Constants are provided that           |
   |                                      |           | define all standard MicroUI           |
   |                                      |           | commands [MUI].                       |
   +--------------------------------------+-----------+---------------------------------------+
   | ``LLINPUT_sendButtonPressedEvent``   | Buttons   | In the case of                        |
   |                                      |           | chronological sequences               |
   |                                      |           | (for example, a RELEASE               |
   | ``LLINPUT_sendButtonReleasedEvent``  |           | that may occur only after a           |
   |                                      |           | PRESSED), it is the                   |
   |                                      |           | responsibility of the                 |
   | ``LLINPUT_sendButtonRepeatedEvent``  |           | driver to ensure the                  |
   |                                      |           | integrity of such                     |
   |                                      |           | sequences.                            |
   +--------------------------------------+-----------+---------------------------------------+
   | ``LLINPUT_sendPointerPressedEvent``  | Pointer   | In the case of                        |
   |                                      |           | chronological sequences               |
   |                                      |           | (for example, a RELEASE               |
   | ``LLINPUT_sendPointerReleasedEvent`` |           | that may occur only after a           |
   |                                      |           | PRESSED), it is the                   |
   |                                      |           | responsibility of the                 |
   | ``LLINPUT_sendPointerMovedEvent``    |           | driver to ensure the                  |
   |                                      |           | integrity of such                     |
   |                                      |           | sequences. Depending on               |
   |                                      |           | whether a button of the               |
   |                                      |           | pointer is pressed while              |
   |                                      |           | moving, a DRAG and/or a               |
   |                                      |           | MOVE MicroUI event is                 |
   |                                      |           | generated.                            |
   +--------------------------------------+-----------+---------------------------------------+
   | ``LLINPUT_sendStateEvent``           | States    | The initial value of each             |
   |                                      |           | state machine (of a States)           |
   |                                      |           | is retrieved by a call to             |
   |                                      |           | ``LLINPUT_IMPL_getInitialStateValue`` |
   |                                      |           | that must be implemented by           |
   |                                      |           | the device. Alternatively,            |
   |                                      |           | the initial value can be              |
   |                                      |           | specified in the XML static           |
   |                                      |           | configuration.                        |
   +--------------------------------------+-----------+---------------------------------------+
   | ``LLINPUT_sendTouchPressedEvent``    | Pointer   | In the case of                        |
   |                                      |           | chronological sequences               |
   |                                      |           | (for example, a RELEASE               |
   | ``LLINPUT_sendTouchReleasedEvent``   |           | that may only occur after a           |
   |                                      |           | PRESSED), it is the                   |
   |                                      |           | responsibility of the                 |
   | ``LLINPUT_sendTouchMovedEvent``      |           | driver to ensure the                  |
   |                                      |           | integrity of such                     |
   |                                      |           | sequences. These APIs will            |
   |                                      |           | generate a DRAG MicroUI               |
   |                                      |           | event instead of a MOVE               |
   |                                      |           | while they represent a                |
   |                                      |           | touch pad over a display.             |
   +--------------------------------------+-----------+---------------------------------------+

Event Buffer
------------

The maximum usage of the internal event buffer may be retrieved at
runtime using the ``LLINPUT_getMaxEventsBufferUsage`` function. This is
useful for tuning the size of the buffer.

.. [1]
   The implementation class is a subclass of the MicroUI class of the
   column.


LLDISPLAY
=========

.. _LLDISPLAY-API-SECTION:

LLDISPLAY: Display
------------------

Principle & Naming Convention
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each display stack provides a low level API in order to connect a
display driver. The file ``LLDISPLAY_impl.h`` defines the API headers to
be implemented. For the APIs themselves, the naming convention is that
their names match the ``*_IMPL_*`` pattern when the functions need to be
implemented.

Initialization
~~~~~~~~~~~~~~

Each display stack gets initialized the same way:

-  First, the function ``LLDISPLAY_IMPL_initialize`` is called: It asks
   its display driver to initialize itself.

-  Second, the functions ``LLDISPLAY_IMPL_getWidth`` and
   ``LLDISPLAY_IMPL_getHeight`` are called to retrieve the size of the
   physical screen.

Working buffer
~~~~~~~~~~~~~~

The display driver must allocate a runtime memory buffer for creating
dynamic images when using MicroUI ``Image.createImage()`` methods that
explicitly create mutable images.

The display driver may choose to return an empty buffer. Thus, calling
MicroUI ``Image.createImage()`` methods will result in a
``java.lang.OutOfMemoryError`` exception.

``LLDISPLAY_getWorkingBufferStartAddress`` returns the buffer start
address. ``LLDISPLAY_getWorkingBufferEndAddress`` returns the next
address after the buffer (end-start is the buffer length).

Flush and Synchronization
~~~~~~~~~~~~~~~~~~~~~~~~~

Function ``LLDISPLAY_getGraphicsBufferAddress`` returns the address of
the graphics buffer (back buffer) for the very first drawing. The
content of this buffer is flushed to the external display memory by the
function ``LLDISPLAY_flush``. The parameters define the rectangular area
of the content which has changed during the last drawing action, and
which must be flushed to the display buffer (dirty area).

``LLDISPLAY_synchronize`` is called before the next drawing after a call
to the flush function, in order to avoid flickering on the display
device.

.. _LLDISPLAY-EXTRA-API-SECTION:

LLDISPLAY_EXTRA: Display Extra Features
---------------------------------------

Principle
~~~~~~~~~

An additional low level API allows you to connect display extra
features. The files ``LLDISPLAY_EXTRA_impl.h`` define the API headers to
be implemented.  For the APIs themselves, the naming convention is that
their names match the ``*_IMPL_*`` pattern when the functions must be
implemented. These LLAPIs are not required. When they are not
implemented, a default implementation is used (weak function).

Display characteristics
~~~~~~~~~~~~~~~~~~~~~~~

Function ``LLDISPLAY_EXTRA_IMPL_isColor`` directly implements the method
from the MicroUI ``Display`` class of the same name. The default
implementation always returns ``LLDISPLAY_EXTRA_OK``.

Function ``LLDISPLAY_EXTRA_IMPL_getNumberOfColors`` directly implements
the method from the MicroUI ``Display`` class of the same name. The
default implementation returns a value according to the number of bits
by pixels, without taking into consideration the alpha bit(s).

Function ``LLDISPLAY_EXTRA_IMPL_isDoubleBuffered`` directly implements
the method from the MicroUI ``Display`` class of the same name. The
default implementation returns ``LLDISPLAY_EXTRA_OK``. When LLAPI
implementation targets a LCD in ``direct`` mode, this function must be
implemented and return ``LLDISPLAY_EXTRA_NOT_SUPPORTED``.

Contrast
~~~~~~~~

``LLDISPLAY_EXTRA_IMPL_setContrast`` and
``DISPLAY_EXTRA_IMPL_getContrast`` are called to set/get the current
display contrast intensity. The default implementations don't manage the
contrast.

BackLight
~~~~~~~~~

``LLDISPLAY_EXTRA_IMPL_hasBackLight`` indicates whether the display has
backlight capabilities.

``LLDISPLAY_EXTRA_IMPL_setBackLight`` and
``DISPLAY_EXTRA_IIMPL_getBackLight`` are called to set/get the current
display backlight intensity.

``LLDISPLAY_EXTRA_IMPL_backlightOn`` and
``LLDISPLAY_EXTRA_IMPL_backlightOff`` enable/disable the backlight. The
default implementations don't manage the backlight.

.. _colorConversions:

Color conversions
~~~~~~~~~~~~~~~~~

``LLDISPLAY_EXTRA_IMPL_convertARGBColorToDisplayColor`` is called to
convert a 32-bit ARGB MicroUI color in ``0xAARRGGBB`` format into the
"driver" display color.

``LLDISPLAY_EXTRA_IMPL_convertDisplayColorToARGBColor`` is called to
convert a display color to a 32-bit ARGB MicroUI color.

Drawings
~~~~~~~~

Synchronization
^^^^^^^^^^^^^^^

The display stack calls the functions
``LLDISPLAY_EXTRA_IMPL_enterDrawingMode`` and
``LLDISPLAY_EXTRA_IMPL_exitDrawingMode`` to enter / leave a critical
section. This is useful when some drawings are performed in C-side using
the ``LLDISPLAY_UTILS`` API. This function implementation can stay empty
when there is no call from C-side, or when the calls from C-side are
performed in the same OS task, rather than in the MicroEJ core engine
task. By default these functions do nothing.

LUT
^^^

The function ``LLDISPLAY_EXTRA_IMPL_prepareBlendingOfIndexedColors`` is
called when drawing an image with indexed color. See
:ref:`display_lut` to have more information about indexed images.

Hardware Accelerator
^^^^^^^^^^^^^^^^^^^^

Some functions allow you to use an hardware accelerator to perform some
drawings: ``LLDISPLAY_EXTRA_IMPL_fillRect``,
``LLDISPLAY_EXTRA_IMPL_drawImage``, ``LLDISPLAY_EXTRA_IMPL_scaleImage``
and ``LLDISPLAY_EXTRA_IMPL_rotateImage``. When called, the LLDISPLAY
*must* perform the drawing (see :ref:`display_hard_accelerator`).
Otherwise a call to ``LLDISPLAY_EXTRA_IMPL_error`` will be performed
with an error code as parameter (see :ref:`lldisplayextra_error`).
Furthermore, the drawing will be not performed by software.

A drawing may be executed directly during the call of the relative
function (synchronous execution), may be executed by a hardware
peripheral like a DMA (asynchronous execution), or may be executed by a
dedicated OS task (asynchronous execution). When the drawing is
synchronous, the function must return
``LLDISPLAY_EXTRA_DRAWING_COMPLETE``, which indicates the drawing is
complete. When the drawing is asynchronous, the function must return
``LLDISPLAY_EXTRA_DRAWING_RUNNING``, which indicates that the drawing is
running. In this case, the very next drawing (with or without hardware
acceleration) will be preceded by a specific call in order to
synchronize the display stack work with the end of hardware drawing. The
function used to wait for the end of drawing is
``LLDISPLAY_EXTRA_IMPL_waitPreviousDrawing``.

The default implementations call the error function.

Structures
~~~~~~~~~~

The drawing functions are using some ``struct`` to specify the drawing
to perform. These structures are listed in
``LLDISPLAY_EXTRA_drawing.h``. Refer to this h file have the exhaustive
list of structures and structures elements.

-  ``int32_t LLDISPLAY_EXTRA_IMPL_fillRect(LLDISPLAY_SImage* dest, int32_t destAddr, LLDISPLAY_SRectangle* rect, int32_t color)``

-  ``int32_t LLDISPLAY_EXTRA_IMPL_drawImage(LLDISPLAY_SImage* src, int32_t srcAddr, LLDISPLAY_SImage* dest, int32_t destAddr, LLDISPLAY_SDrawImage* drawing)``

-  ``int32_t LLDISPLAY_EXTRA_IMPL_scaleImage(LLDISPLAY_SImage* src, int32_t srcAddr, LLDISPLAY_SImage* dest, int32_t destAddr, LLDISPLAY_SScaleImage* drawing)``

-  ``int32_t LLDISPLAY_EXTRA_IMPL_rotateImage(LLDISPLAY_SImage* src, int32_t srcAddr, LLDISPLAY_SImage* dest, int32_t destAddr, LLDISPLAY_SRotateImage* drawing)``

Image Decoders
~~~~~~~~~~~~~~

The API ``LLDISPLAY_EXTRA_IMPL_decodeImage`` allows to add some
additional image decoders (see :ref:`image_external_decoder`). This
LLAPI uses some structures as parameter:

``int32_t LLDISPLAY_EXTRA_IMPL_decodeImage(int32_t address, int32_t length, int32_t expected_format, LLDISPLAY_SImage* image, LLDISPLAY_SRawImageData* image_data)``

LLDISPLAY_UTILS: Display Utils
------------------------------

Principle
~~~~~~~~~

This header file lets some APIs in C-side perform some drawings in the
same buffers used by the display stack. This is very useful for reusing
legacy code, performing a specific drawing, etc.

Synchronization
~~~~~~~~~~~~~~~

Every drawing performed in C-side must be synchronized with the display
stack drawings. The idea is to force the display stack to wait the end
of previous asynchronous drawings before drawing anything else. Use the
functions ``enterDrawingMode`` and ``exitDrawingMode`` to enter / leave
a critical section.

Buffer Characteristics
~~~~~~~~~~~~~~~~~~~~~~

A set of functions allow retrieval of several characterics of an image
(or the display buffer itself). These functions use a parameter to
identify the image: the image Java object hash code
(``myImage.hashCode()`` or ``myGraphicsContext.hashCode()``).

The function ``getBufferAddress`` returns the address of the image data
buffer. This buffer can be located in runtime memory (RAM, SRAM, SDRAM,
etc.) or in read-only memory (internal flash, NOR, etc.).

The functions ``getWidth`` and ``getHeight`` return the size of the
image / graphics context.

The function ``getFormat`` returns the format of the image / graphics
context. The formats list is available in MicroUI ``GraphicsContext``
class.

The functions ``getClipX1``, ``getClipX2``, ``getClipY1`` and
``getClipY2`` return the current clip of the image / graphics context.
The C-side drawing can use the clip limits (this is optional).

Drawings
~~~~~~~~

A set of functions allows you to use internal display stack functions to
draw something on an image (or in the display buffer itself). These
functions use a parameter to identify the image: the image Java object
hash code (``myImage.hashCode()`` or ``myGraphicsContext.hashCode()``).

The basic functions ``drawPixel`` and ``readPixel`` are useful for
drawing or reading a pixel. The function ``blend`` allows you to blend
two colors and a global alpha.

The C-side can change the current clip of an image / graphics context
only in the display stack. The clip is not updated in MicroUI. Use the
function ``setClip`` to do this.

A C-side drawing has to update the drawing limits (before or after the
drawing itself), using the function ``setDrawingLimits`` when the
drawing is made in the display back buffer. This allows you to update
the size of the dirty area the display stack has to flush. If it is not
updated, the C-side drawing (available in back buffer) may never be
flushed to the display graphical memory.

Allocation
~~~~~~~~~~

When decoding an image with an external image decoder (see
:ref:`image_external_decoder`), the C-side has to allocate a RAW
image in the working buffer. The function
``LLDISPLAY_UTILS_allocateRawImage`` takes as parameter a strucutre
which describes the image (size and format) and an output structure
where it stores the image allocation data:

``int32_t LLDISPLAY_UTILS_allocateRawImage(LLDISPLAY_SImage* image, LLDISPLAY_SRawImageData* image_data)``

This function can also be used by C-side to allocate a RAW image in the
working buffer. This image will not be known by MicroUI but this image
can be used in C-side.


.. _LLLEDS-API-SECTION:

LLLEDS: LEDs
============

Principle
---------

The LEDs stack provides a Low Level API for connecting LED drivers. The
file ``LLLEDS_impl.h``, which comes with the LEDs stack, defines the API
headers to be implemented.

Naming convention
-----------------

The Low Level API relies on functions that must be implemented. The
naming convention for such functions is that their names match the
``*_IMPL_*`` pattern.

Initialization
--------------

The first function called is ``LLLEDS_IMPL_initialize``, which allows
the driver to initialize all LED devices. This method must return the
number of LEDs available.

Each LED has a unique identifier. The first LED has the ID 0, and the
last has the ID NbLEDs – 1.

This UI extension provides support to efficiently implement the set of
methods that interact with the LEDs provided by a device. Below are the
relevant C functions:

-  ``LLLEDS_IMPL_getIntensity``: Get the intensity of a specific LED
   using its ID.

-  ``LLLEDS_IMPL_setIntensity``: Set the intensity of an LED using its
   ID.


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
