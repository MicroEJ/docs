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
`??? <#display_lut>`__ to have more information about indexed images.

Hardware Accelerator
^^^^^^^^^^^^^^^^^^^^

Some functions allow you to use an hardware accelerator to perform some
drawings: ``LLDISPLAY_EXTRA_IMPL_fillRect``,
``LLDISPLAY_EXTRA_IMPL_drawImage``, ``LLDISPLAY_EXTRA_IMPL_scaleImage``
and ``LLDISPLAY_EXTRA_IMPL_rotateImage``. When called, the LLDISPLAY
*must* perform the drawing (see `??? <#display_hard_accelerator>`__).
Otherwise a call to ``LLDISPLAY_EXTRA_IMPL_error`` will be performed
with an error code as parameter (see `??? <#lldisplayextra_error>`__).
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
additional image decoders (see `??? <#image_external_decoder>`__). This
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
`??? <#image_external_decoder>`__), the C-side has to allocate a RAW
image in the working buffer. The function
``LLDISPLAY_UTILS_allocateRawImage`` takes as parameter a strucutre
which describes the image (size and format) and an output structure
where it stores the image allocation data:

``int32_t LLDISPLAY_UTILS_allocateRawImage(LLDISPLAY_SImage* image, LLDISPLAY_SRawImageData* image_data)``

This function can also be used by C-side to allocate a RAW image in the
working buffer. This image will not be known by MicroUI but this image
can be used in C-side.
