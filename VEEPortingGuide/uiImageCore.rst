.. _section_image_core:

==============
Image Renderer
==============

Principle
=========

The Image Renderer is an on-board engine that reads and draws the images (see :ref:`section_image_raw`).
It calls Abstraction Layer APIs to draw and transform the images (rotation, scaling, deformation, etc.).
It also includes software algorithms to perform the rendering.

Functional Description
======================

All MicroUI image drawings are redirected to a set of Abstraction Layer APIs.
All Abstraction Layer APIs are implemented by weak functions, which call software algorithms.
The BSP can override this default behavior for each Abstraction Layer API independently.
Furthermore, the BSP can override an Abstraction Layer API for a specific MicroEJ format (for instance ``ARGB8888``) and call the software algorithms for all other formats.

Destination Format
==================

Since MicroUI 3.2, the destination buffer of the drawings can be different than the display buffer format (see :ref:`section_image_display_raw`).
This destination buffer format can be a :ref:`standard format <section_image_standard_raw>` (ARGB8888, A8, etc.) or a :ref:`custom format <section_image_custom_raw>`. 

See :ref:`section_buffered_image` for more information about how to create buffered images with another format than the display format and how to draw in them.

Input Formats
=============

Standard
--------

The Image Renderer is by default able to draw all :ref:`standard formats <section_image_standard_raw>`.
No extra support in the VEE Port is required to draw this kind of image.

The image drawing resembles a :ref:`shape drawing <section_drawings>`. 
The drawing is performed by default by the :ref:`section_drawings_soft` and can be overridden to use a third-party library or a GPU.

.. _section_buffered_image_drawer_custom_format:

Custom
------

A :ref:`section_image_custom_raw` image can be:

* an image with a pixel buffer but whose pixel organization is not standard,
* an image with a data buffer: an image encoded with a third-party encoder (proprietary format or not),
* an image with a "command" buffer: instead of performing the drawings on pixels, the image *stores* the drawing actions to replay them later,
* etc.

The VEE Port must extend the Image Renderer to support the drawing of these images.
This extension can consist in:

* decoding the image at runtime to draw it,
* using a compatible GPU to draw it,
* using a command interpreter to perform some :ref:`shape drawings <section_drawings>`,
* etc.

To draw the custom images, the Image Renderer introduces the notion of *custom image drawer*.
This drawer is an engine that has the responsibility to draw the image.
Each custom image format (``0`` to ``7``) has its image drawer.

Each drawing of a custom image is redirected to the associated image drawer.

.. note:: A custom image drawer can call the UI Shapes Drawing API to draw its elements in the destination.

The implementation is not the same between the Embedded side and the Simulation.
However, the concepts are the same and are described in dedicated chapters.

.. _section_renderer_cco:

MicroUI C Module
================

Principle
---------

As described above, an :ref:`image drawer <section_buffered_image_drawer_custom_format>` allows drawing the images whose format is *custom*.
The :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` is designed to manage the notion of drawers: it does not *support* the custom formats but allows adding some additional drawers.

This support uses several weak functions and tables to redirect the image drawings.
When this support is not used (when the VEE Port does not need to support *custom* images), this support can be removed to reduce the footprint (by removing the indirection tables) and improve the performances (by reducing the number of runtime function calls).

.. _section_buffered_image_drawer_standard:

Standard Formats Only (Default)
-------------------------------

The default implementation can only draw images with a :ref:`standard format <section_image_standard_raw>`. 
In other words, the application cannot draw a custom image. 
This is the most frequent use case, the only one available with MicroUI before version 3.2.

.. hint:: To select this implementation (to disable the custom format support), the define ``LLUI_IMAGE_CUSTOM_FORMATS`` must be unset.

The following graph illustrates the drawing of an image:

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c UID_gpu_hard stub
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h UID_h UID_soft_h UID_stub_h UII_h
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_stub_c UII_c UID_gpu_c UID_gpu_driver
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond UID_gpu_cond UII_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_h [label="[LLUI_PAINTER_impl.h]\nLLUI_PAINTER_IMPL_drawXXX();"]
      LLUI_c [label="[LLUI_PAINTER_impl.c]\nLLUI_PAINTER_IMPL_drawXXX();"]
      UID_h [label="[ui_drawing.h]\nUI_DRAWING_drawXXX();"]
      UID_weak_c [label="[ui_drawing.c]\nweak UI_DRAWING_drawXXX();"]
      UID_soft_h [label="[ui_drawing_soft.h]\nUI_DRAWING_SOFT_drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="algo implemented?"]
      UID_gpu_c [label="[ui_drawing_gpu.c]\nUI_DRAWING_drawXXX();"]
      UID_gpu_cond [label="GPU compatible?"]
      UID_gpu_driver [label="[GPU driver]"]
      UID_gpu_hard [label="[GPU]"]

      UID_stub_h [label="[ui_drawing_stub.h]\nUI_DRAWING_STUB_drawXXX();"]
      UID_stub_c [label="[ui_drawing_stub.c]\nUI_DRAWING_STUB_drawXXX();"]
      stub [label="-"]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[ui_image_drawing.h]\nUI_IMAGE_DRAWING_drawXXX();"]
      UII_c [label="[ui_image_drawing.c]\nUI_IMAGE_DRAWING_drawXXX();"]
      UII_cond [label="standard image?"]

      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_cond
      UID_cond->UID_weak_c [label="no" fontname="courier new" fontsize="10"]
      UID_weak_c->UII_h->UII_c->UII_cond
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UID_gpu_cond->UID_gpu_driver [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_driver->UID_gpu_hard
      UII_cond->UID_soft_h [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UID_stub_h [label="no" fontname="courier new" fontsize="10"]
      UID_soft_h->UID_soft_c
      UID_stub_h->UID_stub_c->stub
   }

.. force a new line

|

**LLUI_PAINTER_IMPL_drawImage** (available in MicroUI C Module)

Similar to ``LLUI_PAINTER_IMPL_drawLine``, see :ref:`section_drawings_cco`.

**UI_DRAWING_drawImage**

.. code-block:: c

   // available in MicroUI C Module
   #define UI_DRAWING_DEFAULT_drawImage UI_DRAWING_drawImage

   // to write in the BSP (optional)
   #define UI_DRAWING_GPU_drawImage UI_DRAWING_drawImage

The function names are set thanks to some ``define``.
These name redirections are helpful when the VEE Port features more than one destination format (not the use-case here).

**UI_DRAWING_GPU_drawImage** (to write in the BSP)

Similar to ``UI_DRAWING_GPU_drawLine`` (see :ref:`section_drawings_cco`), but lets the image drawer manage the image instead of calling the software drawer directly.

.. code-block:: c

   // unlike the MicroUI C Module, this function is not "weak"
   DRAWING_Status UI_DRAWING_GPU_drawImage(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha) {
      
      DRAWING_Status status;

      if (is_gpu_compatible(xxx)) {
         
         // see chapter "Drawings"
         // [...]
      }
      else {
         // let the image drawer manages the image  (available in the C module)
         status = UI_IMAGE_DRAWING_draw(gc, img, regionX, regionY, width, height, x, y, alpha);
      }
      return status;
   }

**UI_DRAWING_DEFAULT_drawImage** (available in MicroUI C Module)

.. code-block:: c

   // use the preprocessor 'weak'
   __weak DRAWING_Status UI_DRAWING_DEFAULT_drawImage(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha) {
   #if !defined(LLUI_IMAGE_CUSTOM_FORMATS)
      return UI_DRAWING_SOFT_drawImage(gc, img, regionX, regionY, width, height, x, y, alpha);
   #else
      return UI_IMAGE_DRAWING_draw(gc, img, regionX, regionY, width, height, x, y, alpha);
   #endif
   }

The define ``LLUI_IMAGE_CUSTOM_FORMATS`` is not set, so the implementation of the weak function only consists in calling the Graphics Engine' software algorithm.

.. _section_buffered_image_drawer_custom:

Custom Format Support 
---------------------

In addition to the :ref:`standard formats <section_image_standard_raw>`, this implementation allows drawing images with a :ref:`custom format <section_image_custom_raw>`. 
This advanced use case is available only with MicroUI 3.2 or higher.

.. hint:: To select this implementation, the define ``LLUI_IMAGE_CUSTOM_FORMATS`` must be set (no specific value).

The MicroUI C module uses some tables to redirect the image management to the expected extension.
There is one table per Image Abstraction Layer API (draw, copy, region, rotate, scale, flip) to embed only necessary algorithms (a table and its functions are only embedded in the final binary file if and only if the MicroUI drawing method is called).

Each table contains ten elements:

.. code:: c

   static const UI_IMAGE_DRAWING_draw_t UI_IMAGE_DRAWING_draw_custom[] = {
         &UI_DRAWING_STUB_drawImage,
         &UI_DRAWING_SOFT_drawImage,
         &UI_IMAGE_DRAWING_draw_custom0,
         &UI_IMAGE_DRAWING_draw_custom1,
         &UI_IMAGE_DRAWING_draw_custom2,
         &UI_IMAGE_DRAWING_draw_custom3,
         &UI_IMAGE_DRAWING_draw_custom4,
         &UI_IMAGE_DRAWING_draw_custom5,
         &UI_IMAGE_DRAWING_draw_custom6,
         &UI_IMAGE_DRAWING_draw_custom7,
   };

* ``UI_DRAWING_STUB_drawImage`` is the drawing function called when the drawing function is not implemented,
* ``UI_DRAWING_SOFT_drawImage`` is the drawing function that redirects the drawing to the :ref:`section_drawings_soft`,
* ``UI_IMAGE_DRAWING_draw_customX`` (``0`` to ``7``) are the drawing functions for each custom format.

The MicroUI C Module retrieves the table index according to the image format.

The following graph illustrates the drawing of an image:


.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c UID_gpu_hard stub UIIx_impl_d
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h UID_h UID_soft_h UID_stub_h UII_h UID_h2
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_gpu_c UID_stub_c UII_c UIIx_c UIIx_impl_c UID_gpu_driver
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c UIIx_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond UID_gpu_cond UII_cond UIIx_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_h [label="[LLUI_PAINTER_impl.h]\nLLUI_PAINTER_IMPL_drawXXX();"]
      LLUI_c [label="[LLUI_PAINTER_impl.c]\nLLUI_PAINTER_IMPL_drawXXX();"]
      UID_h [label="[ui_drawing.h]\nUI_DRAWING_drawXXX();"]
      UID_weak_c [label="[ui_drawing.c]\nweak UI_DRAWING_drawXXX();"]
      UID_soft_h [label="[ui_drawing_soft.h]\nUI_DRAWING_SOFT_drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="algo implemented?"]
      UID_gpu_c [label="[ui_drawing_gpu.c]\nUI_DRAWING_drawXXX();"]
      UID_gpu_cond [label="GPU compatible?"]
      UID_gpu_driver [label="[GPU driver]"]
      UID_gpu_hard [label="[GPU]"]

      UID_stub_h [label="[ui_drawing_stub.h]\nUI_DRAWING_STUB_drawXXX();"]
      UID_stub_c [label="[ui_drawing_stub.c]\nUI_DRAWING_STUB_drawXXX();"]
      stub [label="-"]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[ui_image_drawing.h]\nUI_IMAGE_DRAWING_drawXXX();"]
      UII_c [label="[ui_image_drawing.c]\nUI_IMAGE_DRAWING_drawXXX();"]
      UII_cond [label="standard image?"]
      UIIx_c [label="[ui_image_drawing.c]\ntable[x] = UI_IMAGE_DRAWING_draw_customX()"]
      UIIx_weak_c [label="[ui_image_drawing.c]\nweak UI_IMAGE_DRAWING_draw_customX();"]
      UIIx_cond [label="implemented?"]
      UIIx_impl_c [label="[ui_image_x.c]\nUI_IMAGE_DRAWING_draw_customX()"]
      UIIx_impl_d [label="[custom drawing]"]

      UID_h2 [label="[ui_drawing.h]\n@see Simple Flow (chapter Drawings)"]

      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_cond
      UID_cond->UID_weak_c [label="no" fontname="courier new" fontsize="10"]
      UID_weak_c->UII_h->UII_c->UII_cond
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UID_gpu_cond->UID_gpu_driver [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_driver->UID_gpu_hard
      UII_cond->UID_soft_h [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UIIx_c [label="no" fontname="courier new" fontsize="10"]
      UID_soft_h->UID_soft_c
      UIIx_c->UIIx_cond
      UIIx_cond->UIIx_weak_c [label="no" fontname="courier new" fontsize="10"]
      UIIx_weak_c->UID_stub_h->UID_stub_c->stub
      UIIx_cond->UIIx_impl_c [label="yes" fontname="courier new" fontsize="10"]
      UIIx_impl_c->UIIx_impl_d
      UIIx_impl_d->UID_h2 [style=dotted label="optional
      (drawShapes)" fontname="courier new" fontsize="10"]
   }

.. force a new line

|

Take the same example as the *Standard Formats Only* implementation (draw an image):

**UI_DRAWING_DEFAULT_drawImage** (available in MicroUI C Module)

.. code-block:: c

   // use the preprocessor 'weak'
   __weak DRAWING_Status UI_DRAWING_DEFAULT_drawImage(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha) {
   #if !defined(LLUI_IMAGE_CUSTOM_FORMATS)
      return UI_DRAWING_SOFT_drawImage(gc, img, regionX, regionY, width, height, x, y, alpha);
   #else
      return UI_IMAGE_DRAWING_draw(gc, img, regionX, regionY, width, height, x, y, alpha);
   #endif
   }

The define ``LLUI_IMAGE_CUSTOM_FORMATS`` is set so the implementation of the weak function redirects the image drawing to the image drawers manager (``ui_image_drawing.h``).

**UI_IMAGE_DRAWING_draw** (available in MicroUI C Module)

.. code-block:: c

   static const UI_IMAGE_DRAWING_draw_t UI_IMAGE_DRAWING_draw_custom[] = {
      &UI_DRAWING_STUB_drawImage,
      &UI_DRAWING_SOFT_drawImage,
      &UI_IMAGE_DRAWING_draw_custom0,
      &UI_IMAGE_DRAWING_draw_custom1,
      &UI_IMAGE_DRAWING_draw_custom2,
      &UI_IMAGE_DRAWING_draw_custom3,
      &UI_IMAGE_DRAWING_draw_custom4,
      &UI_IMAGE_DRAWING_draw_custom5,
      &UI_IMAGE_DRAWING_draw_custom6,
      &UI_IMAGE_DRAWING_draw_custom7,
   };

   DRAWING_Status UI_IMAGE_DRAWING_draw(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha){
      return (*UI_IMAGE_DRAWING_draw_custom[_get_table_index(gc, img)])(gc, img, regionX, regionY, width, height, x, y, alpha);
   }

The implementation in the MicroUI C module redirects the drawing to the expected drawer.
The drawer is retrieved thanks to its format (function ``_get_table_index()``):

* the format is standard but the destination is not the *display* format: index ``0`` is returned,
* the format is standard and the destination is the *display* format: index ``1`` is returned,
* the format is custom: index ``2`` to ``9`` is returned,

**UI_IMAGE_DRAWING_draw_custom0** (available in MicroUI C Module)

.. code-block:: c

   // use the preprocessor 'weak'
   __weak DRAWING_Status UI_IMAGE_DRAWING_draw_custom0(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha){
      return UI_DRAWING_STUB_drawImage(gc, img, regionX, regionY, width, height, x, y, alpha);
   }

The default implementation of ``UI_IMAGE_DRAWING_draw_custom0`` (same behavior for ``0`` to ``7``) consists in calling the stub implementation.

**UI_DRAWING_STUB_drawImage** (available in MicroUI C Module)

.. code-block:: c

  DRAWING_Status UI_DRAWING_STUB_drawImage(MICROUI_GraphicsContext* gc, MICROUI_Image* img, jint regionX, jint regionY, jint width, jint height, jint x, jint y, jint alpha){
    // set the drawing log flag "not implemented"
    LLUI_DISPLAY_reportError(gc, DRAWING_LOG_NOT_IMPLEMENTED);
    return DRAWING_DONE;
  }

The implementation only consists in setting the :ref:`Drawing log <section.veeport.ui.drawings.drawing_logs>`  ``DRAWING_LOG_NOT_IMPLEMENTED`` to notify the application that the drawing has not been performed.

.. _section_image_renderer_sim:

Simulation
==========

Principle
---------

The simulation behavior is similar to the :ref:`section_renderer_cco` for the Embedded side.

The :ref:`Front Panel<section_ui_releasenotes_frontpanel>` defines support of the drawers based on Java service loader.

Standard Formats Only (Default Implementation)
----------------------------------------------

The default implementation can draw images with a standard format.

The following graph illustrates the drawing of an image:

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c UID_gpu_hard stub
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] UID_h UID_soft_h UII_h
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_gpu_c UID_stub_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond UID_gpu_cond UII_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_c [label="[FrontPanel]\nLLUIPainter.drawXXX();"]
      UID_h [label="[FrontPanel]\ngetUIDrawer().drawXXX();"]
      UID_weak_c [label="[FrontPanel]\nDisplayDrawer.drawXXX();"]
      UID_soft_h [label="[FrontPanel]\ngetUIDrawerSoftware()\n.drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden?"]
      UID_gpu_c [label="[VEE Port FP]\nDisplayDrawerExtension\n.drawXXX();"]
      UID_gpu_cond [label="can draw algo?"]
      UID_gpu_hard [label="[Third-party lib]"]

      UID_stub_c [label="[FrontPanel]\nno op"]
      stub [label="-"]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[FrontPanel]\ngetUIImageDrawer()\n.drawXXX();"]
      UII_cond [label="standard image?"]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UII_h->UII_cond
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UID_gpu_cond->UID_gpu_hard [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UID_soft_h [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UID_stub_c [label="no" fontname="courier new" fontsize="10"]
      UID_soft_h->UID_soft_c
      UID_stub_c->stub
   }

.. force a new line

|

It is possible to override the image drawers for the standard format in the same way as the custom formats.

.. _section_buffered_image_drawer_custom_fp:

Custom Format Support 
---------------------

It is possible to draw images with a custom format by implementing the ``UIImageDrawing`` interface.
This advanced use case is available only with MicroUI 3.2 or higher.

The ``UIImageDrawing`` interface contains one method for each image drawing primitive (draw, copy, region, rotate, scale, flip).
Only the necessary methods can be implemented.
Each non-implemented method will result in calling the stub implementation.

The method ``handledFormat()``must be implemented and returns the managed format.

Once created, the ``UIImageDrawing`` implementation must be registered as a service.

The following graph illustrates the drawing of an image:

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c UID_gpu_hard stub UIIx_impl_d
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] UID_h UID_soft_h UII_h UID_h2
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_gpu_c UID_stub_c UIIx_impl_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond UID_gpu_cond UII_cond UIIx_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_c [label="[FrontPanel]\nLLUIPainter.drawXXX();"]
      UID_h [label="[FrontPanel]\ngetUIDrawer().drawXXX();"]
      UID_weak_c [label="[FrontPanel]\nDisplayDrawer.drawXXX();"]
      UID_soft_h [label="[FrontPanel]\ngetUIDrawerSoftware()\n.drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden?"]
      UID_gpu_c [label="[VEE Port FP]\nDisplayDrawerExtension\n.drawXXX();"]
      UID_gpu_cond [label="can draw algo?"]
      UID_gpu_hard [label="[Third-party lib]"]

      UID_stub_c [label="[FrontPanel]\nno op"]
      stub [label="-"]

      // --- MULTIPLE IMAGES FLOW ELEMENTS -- //

      UII_h [label="[FrontPanel]\ngetUIImageDrawer()\n.drawXXX();"]
      UII_cond [label="standard image?"]
      UIIx_cond [label="available image drawer\nand method implemented?"]
      UIIx_impl_c [label="[VEE Port Fp]\nCustomImageDrawing.draw()"]
      UIIx_impl_d [label="[custom drawing]"]

      UID_h2 [label="[FrontPanel]\ngetUIDrawer().drawXXX();\n@see Simple Flow (chapter Drawings)"]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UII_h->UII_cond
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UID_gpu_cond->UID_gpu_hard [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UID_soft_h [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UIIx_cond [label="no" fontname="courier new" fontsize="10"]
      UID_soft_h->UID_soft_c
      UIIx_cond->UID_stub_c [label="no" fontname="courier new" fontsize="10"]
      UID_stub_c->stub
      UIIx_cond->UIIx_impl_c [label="yes" fontname="courier new" fontsize="10"]
      UIIx_impl_c->UIIx_impl_d
      UIIx_impl_d->UID_h2 [style=dotted label="optional\n(drawShapes)" fontname="courier new" fontsize="10"]
   }

.. force a new line

|

Let's implement the image drawer for the `CUSTOM_0` format.

.. code:: java

   public class MyCustomImageDrawer implements UIImageDrawing {

      @Override
      public MicroUIImageFormat handledFormat() {
         return MicroUIImageFormat.MICROUI_IMAGE_FORMAT_CUSTOM_0;
      }

      @Override
      public void draw(MicroUIGraphicsContext gc, MicroUIImage img, int regionX, int regionY, int width, int height,
            int x, int y, int alpha) {
         MyCustomImage customImage = (MyCustomImage) img.getImage().getRAWImage();
         customImage.drawOn(gc, regionX, regionY, width, height, x, y, alpha);
      }

   }

Now, this drawer needs to be registered as a service.
This can be achieved by creating a file in the resources of the Front Panel project named ``META-INF/services/ej.microui.display.UIImageDrawing``.
And its content containing the fully qualified name of the previously created image drawer.

.. code-block::

   com.mycompany.MyCustomImageDrawer

It is also possible to declare it programmatically (see where a drawer is registered in the :ref:`drawing custom <section_drawings_sim_custom>` section):

.. code-block:: java

   LLUIDisplay.Instance.registerUIImageDrawer(new MyCustomImageDrawer());

Dependencies
============

-  MicroUI module (see :ref:`section_microui`),
-  Display module (see :ref:`section_display`).

Installation
============

The image Renderer module is part of the MicroUI module and Display module. Install them to be able to use some images.

Use
===

The MicroUI image APIs are available in the class `ej.microui.display.Image`_.

.. _ej.microui.display.Image: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
