.. _section_buffered_image:

===============
Buffered Image
===============

Overview
========

MicroUI application is able to create an image where it is possible to draw into: the MicroUI ``BufferedImage``.
The format of this kind of images is Display (default), Standard or Custom (see next chapters).

.. warning:: The output format Standard and Custom depends on the VEE Port capabilities.

.. _section_buffered_image_drawer:

Drawer
======

A buffered image requires a *drawer*.
A drawer is an engine which has the responsibility to:

* allow the application to create Standard and Custom buffered images,
* draw into these images.

The implementation is not the same between the Embedded side and the Simulation.
However the concepts are the same and are described in dedicated chapters.

Formats
=======

Display
-------

This is the format used by default when no format is specified when creating a MicroUI ``BufferedImage``.

The image format is the same as the display buffer format; in other words, its number of bits-per-pixel and its pixel bits organization are the same (see chapter :ref:`section_image_display_raw`).

* Image creation: the Graphics Engine provides the capacity to create this kind of images; no specific support is required in the VEE Port.
* Draw into the image: the rules to draw into this kind of buffered images are the same as to draw in the display buffer, see :ref:`section_drawings`.
* Draw the image: the rules to draw this kind of buffered images are described in the chapter :ref:`image renderer standard <section_buffered_image_drawer_standard>`.

Standard
--------

A MicroUI ``BufferedImage`` can be created specifying a :ref:`section_image_standard_raw` or :ref:`section_image_grayscale_raw` format.

.. note:: 

  When the display format is the same as the standard format used to create the buffered image, the rules to create the image, to draw into and to draw it are the same as the Display format.
  This chapter describes the use case when the format is different than the *display* format.

Unlike the display format, the VEE Port must feature a :ref:`drawer <section_buffered_image_drawer>` for each standard format.

* Image creation: the drawer allows to create this kind of buffered images; if the VEE Port does not feature a drawer for a specific format, the MicroUI ``BufferedImage`` cannot be created and an exception is thrown at runtime.
* Draw into the image: the drawer can implement all MicroUI drawings or just a reduced set; when a drawing is not performed, a :ref:`drawing log <section.veeport.ui.drawings.drawing_logs>` flag is set.
* Draw the image: the image is *standard* so its rendering is *standard* also; the rules to draw this kind of buffered images are described in the chapter  :ref:`image renderer standard <section_buffered_image_drawer_standard>` (no extra support needed in the VEE Port).

Custom
------

A MicroUI ``BufferedImage`` can be created specifying a :ref:`section_image_custom_raw` formats.

Like standard formats, the VEE Port must feature a :ref:`drawer <section_buffered_image_drawer>` for each custom format.
It must also feature an image allocator.

* Image creation: the allocator and drawer allow to create this kind of buffered images; if the VEE Port does not feature an allocator and a drawer for a specific format, the MicroUI ``BufferedImage`` cannot be created and an exception is thrown at runtime.
* Draw into the image: the drawer can implement all MicroUI drawings or just a reduced set; when a drawing is not performed, a :ref:`drawing log <section.veeport.ui.drawings.drawing_logs>` flag is set.
* Draw the image: the image is *custom* so its rendering is *custom* also; the rules to draw this kind of buffered images are described in the chapter  :ref:`image renderer custom <section_buffered_image_drawer_custom>`.

MicroUI C Module
================

Drawer
------

As described above, a :ref:`drawer <section_buffered_image_drawer>` allows to create and draw into buffered images whose format is different than the display format.
The :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` is designed to manage the notion of drawers: it does not *support* the other formats than display format, but it allows to add some additional drawers.

This support uses several weak functions and tables to redirect the image creation and drawings.
When this support is not used (when the VEE Port does not need to support *extra* images), this support can be removed to reduce the footprint (by removing the indirection tables) and increase the performances (by reducing the number of runtime functions calls).

In addition with the Display, Standard and Custom formats, the MicroUI C module implementation introduces the notion of *Single* and *Multiple* formats, more specifically *Single Format Implementation* and *Multiple Formats Implementation*.

Single Format Implementation (Default Implementation)
"""""""""""""""""""""""""""""""""""""""""""""""""""""

This MicroUI BufferedImage implementation can only target images with the display format. 
In other words, the application is not able to create a MicroUI BufferedImage with a format different than the display format. 
This is the most frequent use-case, which was the only one available with MicroUI before version 3.2. 

.. hint:: To select this implementation (to disable the multi formats support), the define ``LLUI_GC_SUPPORTED_FORMATS`` must be unset or lower than ``2``.

This is the default implementation. 

.. _section_buffered_image_c_multi:

Multiple Formats Implementation
"""""""""""""""""""""""""""""""

This MicroUI BufferedImage implementation allows to create a MicroUI BufferedImage whose format is different than the display format.
This is an advanced use-case, only available with MicroUI 3.2 or higher. 

.. hint:: To select this implementation, the define ``LLUI_GC_SUPPORTED_FORMATS`` must be set to ``2`` or more. Its value defines the available number of *extra* formats the VEE Port features.

The MicroUI C module uses some tables to redirect the image management to the expected :ref:`drawer <section_buffered_image_drawer>`.
There is one table per Abstraction Layer API in order not to embed all algorithms (a table and its functions are only embedded in the final binary file if and only if the MicroUI drawing method is called).
The tables size is dimensioned according to the define value. 

To manipulate the tables, the C module uses 0-based index whose value is different than the image format value.
For instance, according to the VEE Port capabilities, the support image format ARGB8888 can have the index ``1`` for a given VEE Port and ``2`` for another one.
This differentiation allows to reduce the tables size: when a format is not supported by the VEE Port, no extra size in the tables is used (no empty cell).

.. note:: The index ``0`` is reserved to the *display* format. 

A table holds a list of functions for a given algorithm.
For instance, the following table allows to redirect the drawing ``writePixel`` to the drawers ``0`` to ``2``:

.. code:: c

  static const UI_DRAWING_writePixel_t UI_DRAWER_writePixel[] = {
    &UI_DRAWING_writePixel_0,
    &UI_DRAWING_writePixel_1,
  #if (LLUI_GC_SUPPORTED_FORMATS > 2)
    &UI_DRAWING_writePixel_2,
  #endif
  };

* ``UI_DRAWING_writePixel_0`` is the drawing function called when the image format is the display format,
* ``UI_DRAWING_writePixel_1`` and ``UI_DRAWING_writePixel_2`` are the drawing functions called for the images whose format are respectively identified by the index ``1`` and ``2`` (see *Image Creation* below).

By default, the C module only manages up to 3 different formats: the *display* format (index ``0``) and two others formats. 
To add another format, the C module must be customized: look for everywhere the define ``LLUI_GC_SUPPORTED_FORMATS`` is used and add a new cell in the tables.

Custom Format
"""""""""""""

A MicroUI BufferedImage can have a *custom* format as soon as the Multiple Formats Implementation is selected.
However a third-party support is required to render this kind of images. 

.. hint:: In addition to the ``#define LLUI_GC_SUPPORTED_FORMATS``, the ``#define LLUI_IMAGE_CUSTOM_FORMATS`` must be set. This is the same ``define`` used to render custom RAW images: see :ref:`section_buffered_image_drawer_custom`.

.. _section_buffered_image_c_creation:

Image Creation
--------------

Overview
""""""""

Creates an image consists in several steps.
These steps are managed by the Graphics Engine that calls four Abstraction Layer APIs.
These four LLAPI are already implemented by the MicroUI C Module.

According to the support of multiple drawers, the C module redirects or not these LLAPI to some ``ui_drawing.h`` functions.
The image creation steps are succinctly described below, refer to the next chapters for more details.

1. The application asks the creation of a buffered image.
2. The Graphics Engine calls the LLAPI ``LLUI_DISPLAY_IMPL_getDrawerIdentifier()``: this function allows to get a drawer index related to the image format. The index ``0`` indicates to use the default drawer: the *display* drawer.
   A positive value indicates a drawer index for all other formats than the display format. 
   A negative index indicates that the VEE Port does not support the image format (in that case, the image creation is refused and an exception is thrown in the application). 
3. Depending on the image format, the Graphics Engine calculates the minimal stride of the image.
   This stride can be customized to fit the GPU constraint (see :ref:`section_image_gpu_raw`) by implementing the LLAPI ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes()``. 
4. The Graphics Engine determinates the image buffer size according to the image format, its size (width and height) and its stride (see previous step).
   This size and the buffer alignment can be adjusted thanks to the LLAPI ``LLUI_DISPLAY_IMPL_adjustNewImageCharacteristics()``.
   The buffer size should be higher or equal than the buffer size calculated by the Graphics Engine.
   If smaller, the Graphics Engine will use the initial value. For a *custom* image, the initial value is 0: the VEE Port must set a positive value otherwise the image creation is refused and an exception is thrown in the application. 
5. The Graphics Engine allocates the image buffer according to the values adjusted before (size and alignment). 
6. Finally, the Graphics Engine calls the LLAPI ``LLUI_DISPLAY_IMPL_initializeNewImage()`` that allows the VEE Port to initialize the image buffer (often only useful for custom images).

Single Format Implementation
""""""""""""""""""""""""""""

The MicroUI C module implements the four LLAPI to create only MicroUI BufferedImages with the *display* format.

* ``LLUI_DISPLAY_IMPL_getDrawerIdentifier()``: the C module checks if the image format is the *display* format.
  If yes, it returns the index ``0`` that indicates to the Graphics Engine to use the default drawer.
  If not, it returns a negative index: the image creation is refused.
* It redirects the three last LLAPI to some ``ui_drawing.h`` functions.
  These ``ui_drawing.h`` functions are already implemented as ``weak`` functions; that allows the VEE Port to implement only the required functions:

  * Implementation of ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes()`` calls ``UI_DRAWING_getNewImageStrideInBytes()``, the weak function returns the stride given as parameter.
  * Implementation of ``LLUI_DISPLAY_IMPL_adjustNewImageCharacteristics()`` calls ``UI_DRAWING_adjustNewImageCharacteristics()``, the weak function does nothing.
  * Implementation of ``LLUI_DISPLAY_IMPL_initializeNewImage()`` calls ``UI_DRAWING_initializeNewImage()``, the weak function does nothing.

Multiple Formats Implementation
"""""""""""""""""""""""""""""""

The MicroUI C module implements the four LLAPI to create a MicroUI BufferedImage with any kind of format.

* ``LLUI_DISPLAY_IMPL_getDrawerIdentifier()``: the C module checks if the image format is the *display* format.
  If yes, it returns the index ``0`` that indicates to the Graphics Engine to use the default drawer.
  If not, it calls the function ``UI_DRAWING_is_drawer_1()`` and then ``UI_DRAWING_is_drawer_2()``.
  The VEE Port has the responsibility to implement at least one function.
  The index ``1`` or ``2`` will be assigned to the image format according to the VEE Port capabilities.
  If no drawer is found for the given format, the image creation is refused.
* It redirects the three last LLAPI to the associated tables: 

  * Implementation of ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes()`` calls the functions of the table ``UI_DRAWER_getNewImageStrideInBytes[]``, the weak functions return the stride given as parameter.
  * Implementation of ``LLUI_DISPLAY_IMPL_adjustNewImageCharacteristics()`` calls the functions of the table ``UI_DRAWER_adjustNewImageCharacteristics[]``, the weak functions do nothing.
  * Implementation of ``LLUI_DISPLAY_IMPL_initializeNewImage()`` calls the functions of the table ``UI_DRAWER_initializeNewImage[]``, the weak functions do nothing.

Display and Standard Image
""""""""""""""""""""""""""

For this kind of images, the implementation of the functions ``getNewImageStrideInBytes``, ``adjustNewImageCharacteristics`` and ``initializeNewImage`` is optional: it mainly depend on the :ref:`GPU support <section_image_gpu_raw>`.

Custom Image
"""""""""""""

For the :ref:`custom <section_image_custom_raw>` images, the implementation of the function ``getNewImageStrideInBytes`` is optional but the implementation of the functions ``adjustNewImageCharacteristics`` and ``initializeNewImage`` is mandatory:

* ``adjustNewImageCharacteristics`` has to set the image buffer size (the default value is ``0`` which is an invalid size), this value will be used by the Graphics Engine to allocate the image buffer. 
* ``initializeNewImage`` must initialize the custom image buffer.


.. _section_buffered_image_c_drawintodisplay:

Draw into the Image: Display Format
-----------------------------------

Overview
""""""""

To draw into a buffered image with the display format, the same concepts to draw in the display buffer are used: the MicroUI Abstraction Layer drawings are redirected to the ``ui_drawing.h`` functions (see :ref:`section_drawings` for more details).

The MicroUI C module already implements all ``ui_drawing.h`` functions and the drawing are redirected to the :ref:`section_drawings_soft`.
However the function names are ``UI_DRAWING_DEFAULT_drawX()`` and not ``UI_DRAWING_drawX()``.
Thanks to the define ``LLUI_GC_SUPPORTED_FORMATS``, the function names are redefined with C macros.
This compile-time redirection allows to use the same implementation (``UI_DRAWING_DEFAULT_drawX()``) when the multiple formats support is disabled or enabled (when the target is an image with the same format as the display).

The weak implementation of the function ``UI_DRAWING_DEFAULT_drawX()`` calls :ref:`section_drawings_soft` .
This implementation allows to use a GPU or a third-party drawer to perform the rendering (see :ref:`section_drawings` for more details).

Single Format Implementation
""""""""""""""""""""""""""""

The define ``LLUI_GC_SUPPORTED_FORMATS`` is unset or lower than ``2``; the compile-time redirection is:

.. code:: c

  #define UI_DRAWING_DEFAULT_writePixel UI_DRAWING_writePixel

Multiple Formats Implementation
"""""""""""""""""""""""""""""""
				
For the images whose format is the display format (index ``0``, see :ref:`section_buffered_image_c_multi`), the compile-time redirection is:

.. code:: c

  #define UI_DRAWING_DEFAULT_writePixel UI_DRAWING_writePixel_0

.. _section_buffered_image_c_drawinto:

Draw into the Image: Non-Display Format
---------------------------------------

To draw into a buffered image with a format different than the display format, the :ref:`section_buffered_image_c_multi` must be selected.

For the images whose format is not the display format (index ``1`` and ``2``), the C module provides the weak implementations that that does nothing (see :ref:`Drawing log <section.veeport.ui.drawings.drawing_logs>`  ``DRAWING_LOG_NOT_IMPLEMENTED``).

The following graph illustrates the drawing of a shape (not an image, see :ref:`section_buffered_image_c_drawit`):

.. graphviz::
    
  digraph {
    ratio="auto"
    splines="true";
    node [style=filled fillcolor=white shape=rectangle fontname=monospace fontcolor=black width=3];

    // --- SIMPLE FLOW ELEMENTS -- //

    mui [label="[MicroUI]
    Painter.drawXXX();" shape=ellipse] 
    LLUI_h [label="[LLUI_PAINTER_impl.h]
    LLUI_PAINTER_IMPL_drawXXX();" fillcolor=gray]
    LLUI_c [label="[LLUI_PAINTER_impl.c]
    LLUI_PAINTER_IMPL_drawXXX();"]
    UID_h [label="[ui_drawing.h]
    UI_DRAWING_drawXXX();" fillcolor=gray]
    // UID_weak_c [label="[ui_drawing.c]
    // weak UI_DRAWING_drawXXX();" style=dotted]
    UID_soft_h [label="[ui_drawing_soft.h]
    UI_DRAWING_SOFT_drawXXX();" fillcolor=gray]
    UID_soft_c [label="[Graphics Engine]" shape=ellipse]

    // --- GPU FLOW ELEMENTS -- //

    UID_cond [label="function implemented ?" shape=diamond]
    // UID_gpu_c [label="[ui_drawing_gpu.c]
    // UI_DRAWING_drawXXX();"]
    UID_gpu_cond [label="GPU compatible ?" shape=diamond]
    UID_gpu_driver [label="[GPU driver]"]
    UID_gpu_hard [label="[GPU]" shape=ellipse]

    // --- MULTIPLE GC FLOW ELEMENTS -- //

    UID_c [label="[ui_drawing.c]
    UI_DRAWING_drawXXX();"]
    UID_table [label="GC format ?" shape=diamond]
    UID_c0 [label="[ui_drawing.c]
    table[0] = UI_DRAWING_drawXXX_0()"]
    UID_c1 [label="[ui_drawing.c]
    table[1] = UI_DRAWING_drawXXX_1()"]
    UID_weak_0_c [label="[ui_drawing.c]
    weak UI_DRAWING_drawXXX_0();" style=dotted]
    UID_gpu_0_c [label="[ui_drawing_gpu.c]
    UI_DRAWING_drawXXX_0();"]
    UID_cond_1 [label="function implemented ?" shape=diamond]
    UID_weak_1_c [label="[ui_drawing.c]
    weak UI_DRAWING_drawXXX_1();" style=dotted]
    UID_1_c [label="[ui_drawing_yyy.c]
    UI_DRAWING_drawXXX_1();"]
    UID_1_d [label="[custom drawing]" shape=ellipse]

    UID_stub_h [label="[ui_drawing_stub.h]
    UI_DRAWING_STUB_drawXXX();" fillcolor=gray]
    UID_stub_c [label="[ui_drawing_stub.c]
    UI_DRAWING_STUB_drawXXX();"]
    stub [label="-" shape=ellipse]

    // --- FLOW -- //

    mui->LLUI_h->LLUI_c->UID_h->UID_c->UID_table
    UID_table->UID_c0 [label="display format"]
    UID_c0->UID_cond
    UID_table->UID_c1 [label="other format"]
    UID_c1->UID_cond_1
    UID_cond->UID_weak_0_c [label="no"]
    UID_weak_0_c->UID_soft_h->UID_soft_c
    UID_cond->UID_gpu_0_c [label="yes"]
    UID_gpu_0_c->UID_gpu_cond
    UID_cond_1->UID_weak_1_c [label="no"]
    UID_weak_1_c->UID_stub_h->UID_stub_c->stub
    UID_cond_1->UID_1_c [label="yes"]
    UID_1_c->UID_1_d
    UID_gpu_cond->UID_soft_h [label="no"]
    UID_gpu_cond->UID_gpu_driver [label="yes"]
    UID_gpu_driver->UID_gpu_hard
  }

.. force a new line

|


**LLUI_PAINTER_IMPL_drawLine** (available in MicroUI C Module)

See :ref:`section_drawings_cco`.

**UI_DRAWING_drawLine** (available in MicroUI C Module)

.. code-block:: c

  static const UI_DRAWING_drawLine_t UI_DRAWER_drawLine[] = {
    &UI_DRAWING_drawLine_0,
    &UI_DRAWING_drawLine_1,
  #if (LLUI_GC_SUPPORTED_FORMATS > 2)
    &UI_DRAWING_drawLine_2,
  #endif
  };

  DRAWING_Status UI_DRAWING_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY){
    // table redirection according to the drawer index
    return (*UI_DRAWER_drawLine[gc->drawer])(gc, startX, startY, endX, endY);
  }

The implementation in the MicroUI C module redirects the drawing to the expected drawer.
The drawer is identified by the index stored in the ``MICROUI_GraphicsContext`` (index fixed during the image creation).

**UI_DRAWING_drawLine_0** (available in MicroUI C Module)

.. code-block:: c

   #define UI_DRAWING_DEFAULT_drawLine UI_DRAWING_drawLine_0

The index ``0`` is reserved to draw into the image whose format is the display format (see above).
The function name is set thanks to a ``define`` to reuse the same code between Single and Multiple Formats Implementations.

The behavior after this function is similar to :ref:`section_drawings_cco_custom`.

**UI_DRAWING_drawLine_1** (available in MicroUI C Module)

.. code-block:: c
  
   // use the preprocessor 'weak'
  __weak DRAWING_Status UI_DRAWING_drawLine_1(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY){
      // default behavior: call the stub implementation
    return UI_DRAWING_STUB_drawLine(gc, startX, startY, endX, endY);
  }

The implementation of the weak function only consists in calling the stub implementation.

**UI_DRAWING_STUB_drawLine** (available in MicroUI C Module)

.. code-block:: c

  DRAWING_Status UI_DRAWING_STUB_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY){
    // set  the drawing log flag "not implemented"
    LLUI_DISPLAY_reportError(gc, DRAWING_LOG_NOT_IMPLEMENTED);
    return DRAWING_DONE;
  }

The implementation only consists in setting the :ref:`Drawing log <section.veeport.ui.drawings.drawing_logs>` ``DRAWING_LOG_NOT_IMPLEMENTED`` to notify the application that the drawing has not been performed.

**UI_DRAWING_drawLine_1**  (to write in the BSP)

.. code-block:: c

  // this drawer has the index 1
  #define UI_DRAWING_IDENTIFIER_A8_FORMAT 1
  #define UI_DRAWING_A8_is_drawer CONCAT(UI_DRAWING_is_drawer_, UI_DRAWING_IDENTIFIER_A8_FORMAT)
  #define UI_DRAWING_A8_drawLine CONCAT(UI_DRAWING_drawLine_, UI_DRAWING_IDENTIFIER_A8_FORMAT)

This example illustrates how to implement the ``drawLine`` function for an image with the format ``A8``.
The drawer should be written in its own file. 
However, the MicroUI C module advises not to use directly the name ``UI_DRAWING_drawLine_1`` but to use this mechanism to redirect at compile-time the call to ``UI_DRAWING_A8_drawLine``.

* The define ``UI_DRAWING_IDENTIFIER_A8_FORMAT`` assignes the index to the A8 drawer, here ``1``.
* The define ``UI_DRAWING_A8_is_drawer`` sets at compile-time the name of the ``is_drawer`` function, here: ``UI_DRAWING_is_drawer_1``.
* The define ``UI_DRAWING_A8_drawLine``  sets at compile-time the name of the ``drawLine`` function, here: ``UI_DRAWING_drawLine_1``.

**UI_DRAWING_A8_is_drawer**  (to write in the BSP)

.. code-block:: c

  bool UI_DRAWING_A8_is_drawer(jbyte image_format) {
    return MICROUI_IMAGE_FORMAT_A8 == (MICROUI_ImageFormat)image_format;
  }

This function (actually ``UI_DRAWING_is_drawer_1`` thanks to the define, see above) answers ``true`` when the application tries to open a MicroUI BufferedImage with the format ``A8``.

**UI_DRAWING_A8_drawLine**  (to write in the BSP)

.. code-block:: c

  DRAWING_Status UI_DRAWING_A8_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY){

    // retrieve the destination buffer address
    uint8_t* destination_address = LLUI_DISPLAY_getBufferAddress(&gc->image);
    
    // update the next "flush"'s dirty area
    LLUI_DISPLAY_setDrawingLimits(startX, startY, endX, endY);

    // configure the GPU clip
    THIRD_PARTY_DRAWER_set_clip(startX, startY, endX, endY);

    // draw the line
    THIRD_PARTY_DRAWER_draw_line(destination_address, startX, startY, endX, endY, (gc->foreground_color & 0xff) /* use the blue component as opacity level */),

    // here, consider the drawing as done (not asynchronous drawing)
    return DRAWING_DONE;
  }

This function (actually ``UI_DRAWING_drawLine_1`` thanks to the define, see above) performs the drawing.
It is very similar to :ref:`section_drawings_cco_custom`.

Draw the Image: Single Format Implementation 
--------------------------------------------

By definition, the image is a standard image (only display format is allowed) so its drawing is redirected to ``ui_image_drawing.h``, see :ref:`section_buffered_image_drawer_standard`.

.. _section_buffered_image_c_drawit:

Draw the Image: Multiple Formats Implementation 
-----------------------------------------------

Unlike the Single Format Implementation, the destination may be another format than the display format.
By consequence, the drawer has to check the image format **and** the destination format.

The following graph illustrates the drawing of an image (draw, rotate or scale) in other image or in display buffer (to draw a shape, see :ref:`section_buffered_image_c_drawinto`).
This graph gathers the both graphs :ref:`draw in a custom image <section_buffered_image_c_drawinto>` and :ref:`render a custom image <section_buffered_image_drawer_custom>`.

.. graphviz::

  digraph {
    ratio="auto"
    splines="true";
    node [style=filled fillcolor=white shape=rectangle fontname=monospace fontcolor=black width=3];
        
    // --- SIMPLE FLOW ELEMENTS -- //

    mui [label="[MicroUI]
    Painter.drawXXX();" shape=ellipse] 
    LLUI_h [label="[LLUI_PAINTER_impl.h]
    LLUI_PAINTER_IMPL_drawXXX();" fillcolor=gray]
    LLUI_c [label="[LLUI_PAINTER_impl.c]
    LLUI_PAINTER_IMPL_drawXXX();"]
    UID_h [label="[ui_drawing.h]
    UI_DRAWING_drawXXX();" fillcolor=gray]
    // UID_weak_c [label="[ui_drawing.c]
    // weak UI_DRAWING_drawXXX();" style=dotted]
    UID_soft_h [label="[ui_drawing_soft.h]
    UI_DRAWING_SOFT_drawXXX();" fillcolor=gray]
    UID_soft_c [label="[Graphics Engine]" shape=ellipse]

    // --- GPU FLOW ELEMENTS -- //

    UID_cond [label="algo implemented ?" shape=diamond]
    // UID_gpu_c [label="[ui_drawing_gpu.c]
    // UI_DRAWING_drawXXX();"]
    UID_gpu_cond [label="GPU compatible ?" shape=diamond]
    UID_gpu_driver [label="[GPU driver]"]
    UID_gpu_hard [label="[GPU]" shape=ellipse]

    // --- MULTIPLE GC FLOW ELEMENTS -- //

    UID_c [label="[ui_drawing.c]
    UI_DRAWING_drawXXX();"]
    UID_table [label="GC format ?" shape=diamond]
    UID_c0 [label="[ui_drawing.c]
    table[0] = UI_DRAWING_drawXXX_0()"]
    UID_c1 [label="[ui_drawing.c]
    table[1] = UI_DRAWING_drawXXX_1()"]
    UID_weak_0_c [label="[ui_drawing.c]
    weak UI_DRAWING_drawXXX_0();" style=dotted]
    UID_gpu_0_c [label="[ui_drawing_gpu.c]
    UI_DRAWING_drawXXX_0();"]
    UID_cond_1 [label="implemented ?" shape=diamond]
    UID_weak_1_c [label="[ui_drawing.c]
    weak UI_DRAWING_drawXXX_1();" style=dotted]
    UID_1_c [label="[ui_drawing_yyy.c]
    UI_DRAWING_drawXXX_1();"]
    UID_1_d [label="[custom drawing]" shape=ellipse]
    UID_1_i [label="image compatible ?" shape=diamond]

    UID_stub_h [label="[ui_drawing_stub.h]
    UI_DRAWING_STUB_drawXXX();" fillcolor=gray]
    UID_stub_c [label="[ui_drawing_stub.c]
    UI_DRAWING_STUB_drawXXX();"]
    stub [label="-" shape=ellipse]

    // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

    UII_h [label="[ui_image.h]
    UI_IMAGE_drawXXX();" fillcolor=gray]
    UII_c [label="[ui_image.c]
    UI_IMAGE_drawXXX();"]
    UII_cond [label="standard image ?" shape=diamond]
    UII_gc [label="GC format ?" shape=diamond]
    UIIx_c [label="[ui_image.c]
    table[x] = UI_IMAGE_drawCustom_x()"]
    UIIx_weak_c [label="[ui_image.c]
    weak UI_IMAGE_drawCustom_x();" style=dotted]
    UIIx_cond [label="implemented ?" shape=diamond]
    UIIx_impl_c [label="[ui_image_x.c]
    UI_IMAGE_drawCustom_x()"]
    UIIx_impl_d [label="[custom drawing]" shape=ellipse]
    UIIx_gc [label="gc compatible ?" shape=diamond]
    UIIx_shape [label="can draw shapes ?" shape=diamond]

    UID_h2 [label="[ui_drawing.h]
    @see Multiple Output Formats;" fillcolor=gray ]

    // --- FLOW -- //

    mui->LLUI_h->LLUI_c->UID_h->UID_c->UID_table
    UID_table->UID_c0 [label="display format"]
    UID_c0->UID_cond
    UID_table->UID_c1 [label="other format"]
    UID_c1->UID_cond_1

    // dest: display format
    UID_cond->UID_weak_0_c [label="no"]
    UID_weak_0_c->UII_h->UII_c->UII_cond
    UID_cond->UID_gpu_0_c [label="yes"]
    UID_gpu_0_c->UID_gpu_cond

    UID_stub_h->UID_stub_c->stub

    // dest: custom format
    UID_cond_1->UID_weak_1_c [label="no"]
    UID_weak_1_c->UII_h
    UID_cond_1->UID_1_c [label="yes"]
    UID_1_c->UID_1_i
    UID_1_i->UID_1_d [label="yes"]
    UID_1_i->UII_h [label="no"]

    // gpu
    UID_gpu_cond->UII_h [label="no"]
    UID_gpu_cond->UID_gpu_driver [label="yes"]
    UID_gpu_driver->UID_gpu_hard

    UII_cond->UII_gc [label="yes"]
    UII_cond->UIIx_c [label="no"]
    UII_gc->UID_soft_h  [label="display"]
    UII_gc->UID_stub_h  [label="other"]
    UID_soft_h->UID_soft_c
    UIIx_c->UIIx_cond
    UIIx_cond->UIIx_weak_c [label="no"]
    UIIx_weak_c->UID_stub_h
    UIIx_cond->UIIx_impl_c [label="yes"]
    UIIx_impl_c->UIIx_gc
    UIIx_gc->UIIx_impl_d [label="yes"]
    UIIx_gc->UIIx_shape [label="no"]
    UIIx_shape->UID_h2 [label="yes"]
    UIIx_shape->UID_stub_h [label="no"]
    UIIx_impl_d->UID_h2 [style=dotted label="optional
    (drawShapes)"]

  }

.. force a new line

|

The following description considers that previous both graphs (:ref:`draw in a custom image <section_buffered_image_c_drawinto>` and :ref:`render a custom image <section_buffered_image_drawer_custom>`) have been read and understood.
It only describes the *final* use-case: draw a custom image in an unknown destination (unknown destination format):

**UI_IMAGE_DRAWING_draw_custom4** (to write in the BSP)

.. code-block:: c

  // this image drawer manages the custom format 4
  #define UI_IMAGE_IDENTIFIER_CMD_FORMAT 4
  #define UI_IMAGE_DRAWING_CMD_draw CONCAT(UI_IMAGE_DRAWING_draw_custom_, UI_IMAGE_IDENTIFIER_CMD_FORMAT)

  // macro to map a custom struct "cmd_image_t*" on the MicroUI Image buffer
  #define MAP_CMD_ON_IMAGE(image) ((cmd_image_t*) LLUI_DISPLAY_getBufferAddress(image))
  
  DRAWING_Status UI_IMAGE_DRAWING_CMD_draw(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha){
    
    // retrieve the commands list
    cmd_image_t* cmd = MAP_CMD_ON_IMAGE(img);

    for(int i = 0; i < cmd->size; i++) {
      switch (cmd->list[i].kind) {

        case COMMAND_LINE: {

          // change the graphics context color
          gc->foreground_color = cmd->list[i].color;

          // draw a line as usual
          UI_DRAWING_drawLine(gc, x + cmd->list[i].args[0], y + cmd->list[i].args[1], x + cmd->list[i].args[2], y + cmd->list[i].args[3]);

          break;
        }

        // all others commands
        // [...] 
      }
    }
    
    // restore the original color
    gc->foreground_color = original_color;

    return DRAWING_DONE;
  }

This drawer manages a custom image that holds a commands buffer (a list of drawings). 
The image drawing consists in decoding the commands list and call the standard shapes drawings.
This drawer does not need to *recognize* the destination: the drawing of the shapes will do it.

Thanks to the define ``UI_IMAGE_IDENTIFIER_CMD_FORMAT``, this drawer uses the custom format ``4``.


**UI_IMAGE_DRAWING_draw_custom6** (to write in the BSP)

.. code-block:: c

  // this image drawer manages the custom format 6
  #define UI_IMAGE_IDENTIFIER_PROPRIETARY_FORMAT 6
  #define UI_IMAGE_DRAWING_PROPRIETARY_draw CONCAT(UI_IMAGE_DRAWING_draw_custom_, UI_IMAGE_IDENTIFIER_PROPRIETARY_FORMAT)

  DRAWING_Status UI_IMAGE_DRAWING_PROPRIETARY_draw(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha){
    
    DRAWING_Status ret;

    // can only draw in an image with same format than display 
    if (LLUI_DISPLAY_isDisplayFormat(gc->image.format)) {
      // call a third-party library
      THIRD_PARTY_LIB_draw_image([...]);
      ret = DRAWING_DONE; // or DRAWING_RUNNING
    }
    else {
      // cannot draw the image: call stub implementation
      ret = UI_DRAWING_STUB_drawImage(gc, img, regionX, regionY, width, height, x, y, alpha);
    }

    return ret;
  }

This drawer manages an image whose format is *proprietary* . 
This example considers that the third-party library is only able to draw the image in a bufer with the display format.
Otherwise, the drawing is cancelled and the stub implementation is used.

Thanks to the define ``UI_IMAGE_IDENTIFIER_PROPRIETARY_FORMAT``, this drawer uses the custom format ``6``.

Extended C Modules
------------------

MicroVG enables custom format for the Buffered Vector Image. 
It uses the mechanisms described above and can be used as example.
See :ref:`section_vg_cco`.

The drawings in the custom format *BVI* are implemented into the file ``ui_drawing_bvi.c``.

Simulation
==========

services



Dependencies
============

-  MicroUI module (see :ref:`section_microui`),
-  Display module (see :ref:`section_display`).

Installation
============

BufferedImage module is part of the MicroUI module and Display module. Install them in order to be able to use some buffered images.

Use
===

The MicroUI image APIs are available in the class `ej.microui.display.BufferedImage`_.

.. _ej.microui.display.BufferedImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html





..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners. 