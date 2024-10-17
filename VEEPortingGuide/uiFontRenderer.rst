.. _section_font_renderer:

=============
Font Renderer
=============

Principle
=========

The Font Renderer is a module of the MicroUI runtime that reads and draws the strings with a font.
It calls Abstraction Layer APIs to draw and transform the strings, the MicroUI `RenderableString`_ and single characters (with an optional transformation like a rotation or a scaling).
In addition, the Graphics Engine provides some software algorithms to perform the rendering of the strings with the :ref:`internal font format <section_font_internal_format>`.

Functional Description
======================

All MicroUI string drawings are redirected to a set of Abstraction Layer APIs.
All Abstraction Layer APIs are implemented by weak functions, which call software algorithms.
The BSP can override this default behavior:

* to use an advanced complex layout manager,
* to use a custom drawer,
* to handle :ref:`Custom Fonts <section_font_custom>`.

Font Formats
============

Internal Font Format
--------------------

The  Graphics Engine's software algorithms are by default able to draw an :ref:`internal font <section_font_internal_format>`.
No extra support in the VEE Port is required to draw strings with this kind of font.

The string drawing resembles a :ref:`shape drawing <section_drawings>`.
The drawing is performed by default by the :ref:`section_drawings_soft` and can be overridden.
This allows to enrich the :ref:`language support <section_font_languages>`  by using a third-party library that provides an advanced complex layout manager.

.. _section_font_drawer_custom_format:

Custom Font Format
------------------

The VEE Port must extend the Font Renderer to support the drawing of strings with a :ref:`section_font_custom`.
This extension can consist in:

* decoding the font at runtime to draw it,
* using an advanced complex layout manager,
* using a command interpreter to perform some :ref:`shape drawings <section_drawings>`,
* etc.

To draw strings with custom fonts, the Font Renderer introduces the notion of *custom font drawer*.
This drawer is an engine that has the responsibility to draw the string with the font.
Each custom font format (``0`` to ``7``) has its own font drawer.

Each drawing of a string with a custom font is redirected to the associated font drawer.

.. hint:: A custom font drawer can call the UI Shapes Drawing API to draw its elements in the destination.

The implementation is not the same between the Embedded side and the Simulation.
However, the concepts are the same and are described in dedicated chapters.


.. _section_font_renderer_cco:

MicroUI C Module
================

Principle
---------

As described above, a :ref:`font drawer <section_font_drawer_custom_format>` allows drawing strings with a font which format is *custom*.
The :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` is designed to manage the notion of drawers: it does not *support* the custom formats but allows adding some additional drawers.

This support uses several weak functions and tables to redirect the string drawings.
When custom drawers are not used (when the VEE Port does not need to support *custom* fonts), this redirection can be removed to reduce the memory footprint (by removing the indirection tables) and improve the performances (by reducing the number of runtime function calls).

.. _section_font_drawer_internal:

Internal Font Format Only (Default)
-----------------------------------

The default implementation can only draw string with :ref:`internal fonts <section_font_internal_format>`.
In other words, the application cannot draw with a custom font.
This is the most frequent use case, the only one available with MicroUI before version 3.6.

.. attention:: To select this implementation (to disable the custom font support), the define ``LLUI_FONT_CUSTOM_FORMATS`` must be unset.

The font drawing is similar to ``UI_DRAWING_GPU_drawLine`` (see :ref:`section_drawings_cco`), except that the drawing consists in decoding the string first (to optionally applying a complex layout manager), and then calling the Graphics Engine's software algorithms to draw the string.

Theoretically, the weak drawer should let the font drawer handle the font instead of calling the software drawer directly.
However the MicroUI C Module take advantage of the define ``LLUI_FONT_CUSTOM_FORMATS``: as it is not set, the C Module bypasses the indirection to the font drawer, and as a consequence the implementation of the weak function only consists in calling the Graphics Engine's software algorithm (basic string layouter, see :ref:`section_font_languages` and software drawings). 
This tip reduces the footprint and the CPU usage.

An implementation of a third-party complex layouter can optionally take advantage of the define ``LLUI_FONT_CUSTOM_FORMATS``.
The following diagrams illustrate the drawing of a string with or without taking advantage of the define ``LLUI_FONT_CUSTOM_FORMATS`` (respectively *default* and *optimized* implementation).

.. tabs::

   .. tab:: Default Implementation

      .. graphviz:: :align: center

         digraph {
            ratio="auto"
            splines="true";
            bgcolor="transparent"
            node [style="filled,rounded" fontname="courier new" fontsize="10"]

            { //in/out
               node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c stub
            }
            { // h
               node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h UID_h UID_soft_h UID_stub_h UII_h
            }
            { // c
               node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_stub_c UII_c UID_gpu_c
            }
            { // weak
               node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
            }
            { // choice
               node [shape="diamond" color="#e5e9eb"] UID_cond UII_cond
            }

            // --- SIMPLE FLOW ELEMENTS -- //

            mui [label="[MicroUI]\nPainter.drawString();"] 
            LLUI_h [label="[LLUI_PAINTER_impl.h]\nLLUI_PAINTER_IMPL_drawString();"]
            LLUI_c [label="[LLUI_PAINTER_impl.c]\nLLUI_PAINTER_IMPL_drawString();"]
            UID_h [label="[ui_drawing.h]\nUI_DRAWING_drawString();"]
            UID_weak_c [label="[ui_drawing.c]\nweak UI_DRAWING_drawString();"]
            UID_soft_h [label="[ui_drawing_soft.h]\nUI_DRAWING_SOFT_drawString();"]
            UID_soft_c [label="[Graphics Engine]"]

            // --- GPU FLOW ELEMENTS -- //

            UID_cond [label="algo implemented?"]
            UID_gpu_c [label="[complex_layout.c]\nUI_DRAWING_drawString();"]

            UID_stub_h [label="[ui_drawing_stub.h]\nUI_DRAWING_STUB_drawString();"]
            UID_stub_c [label="[ui_drawing_stub.c]\nUI_DRAWING_STUB_drawString();"]
            stub [label="-"]

            // --- MULTIPLE FONTS FLOW ELEMENTS -- //

            UII_h [label="[ui_font_drawing.h]\nUI_FONT_DRAWING_drawString();"]
            UII_c [label="[ui_font_drawing.c]\nUI_FONT_DRAWING_drawString();"]
            UII_cond [label="internal font?"]
            
            // --- FLOW -- //

            mui->LLUI_h->LLUI_c->UID_h->UID_cond
            UID_cond->UID_weak_c [label="no" fontname="courier new" fontsize="10"]
            UID_weak_c->UID_soft_h [label="built-in optim" fontname="courier new" fontsize="10"]
            UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
            UID_gpu_c->UII_h->UII_c->UII_cond
            UII_cond->UID_soft_h [label="yes" fontname="courier new" fontsize="10"]
            UII_cond->UID_stub_h [label="no" fontname="courier new" fontsize="10"]
            UID_soft_h->UID_soft_c
            UID_stub_h->UID_stub_c->stub
         }

   .. tab:: Optimized Implementation

      .. graphviz:: :align: center

         digraph {
            ratio="auto"
            splines="true";
            bgcolor="transparent"
            node [style="filled,rounded" fontname="courier new" fontsize="10"]

            { //in/out
               node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c
            }
            { // h
               node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h UID_h UID_soft_h
            }
            { // c
               node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_gpu_c
            }
            { // weak
               node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
            }
            { // choice
               node [shape="diamond" color="#e5e9eb"] UID_cond
            }

            // --- SIMPLE FLOW ELEMENTS -- //

            mui [label="[MicroUI]\nPainter.drawString();"] 
            LLUI_h [label="[LLUI_PAINTER_impl.h]\nLLUI_PAINTER_IMPL_drawString();"]
            LLUI_c [label="[LLUI_PAINTER_impl.c]\nLLUI_PAINTER_IMPL_drawString();"]
            UID_h [label="[ui_drawing.h]\nUI_DRAWING_drawString();"]
            UID_weak_c [label="[ui_drawing.c]\nweak UI_DRAWING_drawString();"]
            UID_soft_h [label="[ui_drawing_soft.h]\nUI_DRAWING_SOFT_drawString();"]
            UID_soft_c [label="[Graphics Engine]"]

            // --- GPU FLOW ELEMENTS -- //

            UID_cond [label="algo implemented?"]
            UID_gpu_c [label="[complex_layout.c]\nUI_DRAWING_drawString();"]
            
            // --- FLOW -- //

            mui->LLUI_h->LLUI_c->UID_h->UID_cond
            UID_cond->UID_weak_c [label="no" fontname="courier new" fontsize="10"]
            UID_weak_c->UID_soft_h [label="built-in optim" fontname="courier new" fontsize="10"]
            UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
            UID_gpu_c->UID_soft_h
            UID_soft_h->UID_soft_c
         }
   

**LLUI_PAINTER_IMPL_drawString** (available in MicroUI C Module)

Similar to ``LLUI_PAINTER_IMPL_drawLine``, see :ref:`section_drawings_cco`.


**UI_DRAWING_drawString**

.. code-block:: c

   // Available in MicroUI C Module
   #define UI_DRAWING_DEFAULT_drawString UI_DRAWING_drawString

   // To write in the BSP (optional)
   #define UI_DRAWING_LAYOUT_drawString UI_DRAWING_drawString

The function names are set with preprocessor macros.
These name redirections are helpful when the VEE Port features more than one destination format (which is not the case here).


**UI_DRAWING_LAYOUT_drawString** (to write in the BSP)

Similar to ``UI_DRAWING_GPU_drawLine`` (see :ref:`section_drawings_cco`), but lets the font drawer manage the font instead of calling the software drawer directly (*Default Implementation*) or takes advantage of the define ``LLUI_FONT_CUSTOM_FORMATS`` (*Optimized Implementation*):

.. tabs::

   .. tab:: Default Implementation

      .. code-block:: c

         // Unlike the MicroUI C Module, this function is not "weak".
         DRAWING_Status UI_DRAWING_LAYOUT_drawString(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y) {
            
            DRAWING_Status status;
            jchar *transformed_chars = [...] ;

            // Let the font drawer manages the string (available in the C module)
            status = UI_FONT_DRAWING_drawString(gc, transformed_chars, length, font, x, y);

            return status;
         }

   .. tab:: Optimized Implementation

      .. code-block:: c

         // Unlike the MicroUI C Module, this function is not "weak".
         DRAWING_Status UI_DRAWING_LAYOUT_drawString(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y) {
            
            DRAWING_Status status;
            jchar *transformed_chars = [...] ;

         #if !defined(UI_FEATURE_FONT_CUSTOM_FORMATS)
            status = UI_DRAWING_SOFT_drawString(gc, transformed_chars, length, font, x, y);
         #else
            // Let the font drawer manages the string (available in the C module)
            status = UI_FONT_DRAWING_drawString(gc, transformed_chars, length, font, x, y);
         #endif
            return status;
         }


**UI_DRAWING_DEFAULT_drawString** (available in MicroUI C Module)

.. code-block:: c

   // Use the compiler's 'weak' attribute
   __weak DRAWING_Status UI_DRAWING_DEFAULT_drawString(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y) {
   #if !defined(LLUI_FONT_CUSTOM_FORMATS)
      return UI_DRAWING_SOFT_drawString(gc, chars, length, font, x, y);
   #else
      return UI_FONT_DRAWING_drawString(gc, chars, length, font, x, y);
   #endif
   }

The define ``LLUI_FONT_CUSTOM_FORMATS`` is not set, so the implementation of the weak function only consists in calling the Graphics Engine's software algorithm.


.. _section_font_drawer_custom:

Custom Font Format
------------------

In addition to the :ref:`internal font format <section_font_internal_format>`, this implementation allows drawing strings with a :ref:`custom font format <section_font_custom>`.
This advanced use case is available only with MicroUI 3.6 or higher.

.. attention:: To select this implementation, the define ``LLUI_FONT_CUSTOM_FORMATS`` must be set (no specific value).

The MicroUI C module uses some tables to redirect the font management to the expected extension.
There is one table per Font Abstraction Layer API (draw, rotate, scale) to embed only the necessary algorithms (a table and its functions are only embedded in the final binary file if and only if the MicroUI drawing method is called).

Each table contains ten elements:

.. code:: c

   static const UI_FONT_DRAWING_drawString_t UI_FONT_DRAWING_drawString_custom[] = {
      &UI_DRAWING_STUB_drawString,
      &UI_DRAWING_SOFT_drawString,
      &UI_FONT_DRAWING_drawString_custom0,
      &UI_FONT_DRAWING_drawString_custom1,
      &UI_FONT_DRAWING_drawString_custom2,
      &UI_FONT_DRAWING_drawString_custom3,
      &UI_FONT_DRAWING_drawString_custom4,
      &UI_FONT_DRAWING_drawString_custom5,
      &UI_FONT_DRAWING_drawString_custom6,
      &UI_FONT_DRAWING_drawString_custom7,
   };

* ``UI_DRAWING_STUB_drawString`` is the drawing function called when the drawing function is not implemented,
* ``UI_DRAWING_SOFT_drawString`` is the drawing function that redirects the drawing to the :ref:`section_drawings_soft`,
* ``UI_FONT_DRAWING_drawString_customX`` (``0`` to ``7``) are the drawing functions for each custom format.

The MicroUI C Module retrieves the table index according to the font format.

The implementation of ``UI_DRAWING_drawString`` can have two behaviors:

  1. It only manages the characters layouting; the drawing is performed by another C file. 
  2. It manages the layouting **and** the drawing; in that case, the implementation has to check if it supports the font.

The following diagram illustrates the drawing of an string:


.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c stub UIIx_impl_d
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h UID_h UID_soft_h UID_stub_h UII_h UID_h2
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_gpu_c UID_gpu2_c UID_stub_c UII_c UIIx_c UIIx_impl_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c UIIx_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond UII_cond UIIx_cond UIL_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawString();"] 
      LLUI_h [label="[LLUI_PAINTER_impl.h]\nLLUI_PAINTER_IMPL_drawString();"]
      LLUI_c [label="[LLUI_PAINTER_impl.c]\nLLUI_PAINTER_IMPL_drawString();"]
      UID_h [label="[ui_drawing.h]\nUI_DRAWING_drawString();"]
      UID_weak_c [label="[ui_drawing.c]\nweak UI_DRAWING_drawString();"]
      UID_soft_h [label="[ui_drawing_soft.h]\nUI_DRAWING_SOFT_drawString();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="algo implemented?"]
      UIL_cond [label="supported font?"]
      UID_gpu_c [label="[complex_layout.c]\nUI_DRAWING_drawString();"]
      UID_gpu2_c [label="[layout_and_draw.c]\nUI_DRAWING_drawString();"]
      
      UID_stub_h [label="[ui_drawing_stub.h]\nUI_DRAWING_STUB_drawString();"]
      UID_stub_c [label="[ui_drawing_stub.c]\nUI_DRAWING_STUB_drawString();"]
      stub [label="-"]

      // --- MULTIPLE FONTS FLOW ELEMENTS -- //

      UII_h [label="[ui_font_drawing.h]\nUI_FONT_DRAWING_drawString();"]
      UII_c [label="[ui_font_drawing.c]\nUI_FONT_DRAWING_drawString();"]
      UII_cond [label="internal font?"]
      UIIx_c [label="[ui_font_drawing.c]\ntable[x] = UI_FONT_DRAWING_drawString_customX()"]
      UIIx_weak_c [label="[ui_font_drawing.c]\nweak UI_FONT_DRAWING_drawString_customX();"]
      UIIx_cond [label="implemented?"]
      UIIx_impl_c [label="[ui_font_x.c]\nUI_FONT_DRAWING_drawString_customX()"]
      UIIx_impl_d [label="[custom drawing]"]

      UID_h2 [label="[ui_drawing.h]\n@see Simple Flow (chapter Drawings)"]

      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_cond
      UID_cond->UID_weak_c [label="no" fontname="courier new" fontsize="10"]
      UID_weak_c->UII_h->UII_c->UII_cond
      UID_cond->UID_gpu_c [label="layout only" fontname="courier new" fontsize="10"]
      UID_cond->UID_gpu2_c [label="layout + draw" fontname="courier new" fontsize="10"]
      UID_gpu_c->UII_h
      UID_gpu2_c->UIL_cond
      UIL_cond->UIIx_impl_d [label="yes" fontname="courier new" fontsize="10"]
      UIL_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
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

Take the same example as the *Internal Font Formats Only* implementation (draw a string):

**UI_DRAWING_DEFAULT_drawString** (available in MicroUI C Module)

.. code-block:: c

   // Use the compiler's 'weak' attribute
   __weak DRAWING_Status UI_DRAWING_DEFAULT_drawString(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y) {
   #if !defined(LLUI_FONT_CUSTOM_FORMATS)
      return UI_DRAWING_SOFT_drawString(gc, chars, length, font, x, y);
   #else
      return UI_FONT_DRAWING_drawString(gc, chars, length, font, x, y);
   #endif
   }

The define ``LLUI_FONT_CUSTOM_FORMATS`` is set so the implementation of the weak function redirects the string drawing to the font drawer manager (``ui_font_drawing.h``).

**UI_FONT_DRAWING_draw** (available in MicroUI C Module)

.. code-block:: c

   static const UI_FONT_DRAWING_drawString_t UI_FONT_DRAWING_drawString_custom[] = {
      &UI_DRAWING_STUB_drawString,
      &UI_DRAWING_SOFT_drawString,
      &UI_FONT_DRAWING_drawString_custom0,
      &UI_FONT_DRAWING_drawString_custom1,
      &UI_FONT_DRAWING_drawString_custom2,
      &UI_FONT_DRAWING_drawString_custom3,
      &UI_FONT_DRAWING_drawString_custom4,
      &UI_FONT_DRAWING_drawString_custom5,
      &UI_FONT_DRAWING_drawString_custom6,
      &UI_FONT_DRAWING_drawString_custom7,
   };

   DRAWING_Status UI_FONT_DRAWING_drawString(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y){
      return (*UI_FONT_DRAWING_drawString_custom[_get_table_index(gc, font)])(gc, chars, length, font, x, y);
   }

The implementation in the MicroUI C module redirects the drawing to the expected drawer.
The drawer is retrieved using the font format (function ``_get_table_index()``):

* the format is internal but the destination is not the *display* format: index ``0`` is returned,
* the format is internal and the destination is the *display* format: index ``1`` is returned,
* the format is custom: an index from ``2`` to ``9`` is returned.

**UI_FONT_DRAWING_drawString_custom0** (available in MicroUI C Module)

.. code-block:: c

   // Use the compiler's 'weak' attribute
   __weak DRAWING_Status UI_FONT_DRAWING_drawString_custom0(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y){
      return UI_DRAWING_STUB_drawString(gc, chars, length, font, x, y);
   }

The default implementation of ``UI_FONT_DRAWING_drawString_custom0`` (same behavior for ``0`` to ``7``) consists in calling the stub implementation.

**UI_DRAWING_STUB_drawString** (available in MicroUI C Module)

.. code-block:: c

  DRAWING_Status UI_DRAWING_STUB_drawString(MICROUI_GraphicsContext *gc, jchar *chars, jint length, MICROUI_Font *font, jint x, jint y){
    // Set the drawing log flag "not implemented"
    LLUI_DISPLAY_reportError(gc, DRAWING_LOG_NOT_IMPLEMENTED);
    return DRAWING_DONE;
  }

The implementation only consists in setting the :ref:`Drawing log flag <section.veeport.ui.drawings.drawing_logs>` ``DRAWING_LOG_NOT_IMPLEMENTED`` to notify the application that the drawing has not been performed.


.. _section_font_renderer_sim:

Simulation
==========

Principle
---------

The simulation behavior is similar to the :ref:`section_renderer_cco` for the Embedded side.

The :ref:`Front Panel<section_ui_releasenotes_frontpanel>` defines support for the drawers based on the Java service loader.

Internal Font Format Only (Default)
-----------------------------------

The default implementation can only draw strings with internal fonts.

.. note:: Contrary to the :ref:`section_renderer_cco`, the simulation does not (and doesn't need to) provide an option to disable the use of custom font. 

The following diagram illustrates the drawing of a string:

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c stub
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
         node [shape="diamond" color="#e5e9eb"] UID_cond UII_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawString();"] 
      LLUI_c [label="[FrontPanel]\nLLUIPainter.drawString();"]
      UID_h [label="[FrontPanel]\ngetUIDrawer().drawString();"]
      UID_weak_c [label="[FrontPanel]\nDisplayDrawer.drawString();"]
      UID_soft_h [label="[FrontPanel]\ngetUIDrawerSoftware()\n.drawString();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden?"]
      UID_gpu_c [label="[VEE Port FP]\nComplexLayout\n.drawString();"]

      UID_stub_c [label="[FrontPanel]\nno op"]
      stub [label="-"]

      // --- MULTIPLE FONTS FLOW ELEMENTS -- //

      UII_h [label="[FrontPanel]\ngetUIFontDrawer()\n.drawString();"]
      UII_cond [label="internal font?"]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UII_h->UII_cond
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UII_h
      UII_cond->UID_soft_h [label="yes" fontname="courier new" fontsize="10"]
      UII_cond->UID_stub_c [label="no" fontname="courier new" fontsize="10"]
      UID_soft_h->UID_soft_c
      UID_stub_c->stub
   }

.. force a new line

|

It is possible to override the font drawers for the internal format in the same way as the custom formats.

.. _section_font_drawer_custom_fp:

Custom Font Format
------------------

It is possible to draw fonts with a custom format by implementing the ``UIFontDrawing`` interface.
This advanced use case is available only with MicroUI 3.6 or higher.

The ``UIFontDrawing`` interface contains one method for each font drawing primitive (draw, getWidth, RenderableString, rotate, scale).
Only the necessary methods have to be implemented.
Each non-implemented method will result in calling the stub implementation.

The method ``handledFormat()`` must be implemented and returns the font format handled by the drawer.

Once created, the ``UIFontDrawing`` implementation must be registered as a service.

The following diagram illustrates the drawing of a string: 

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"]

      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui UID_soft_c stub UIIx_impl_d
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] UID_h UID_soft_h UII_h UID_h2
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c UID_gpu_c UID_gpu2_c UID_stub_c UIIx_impl_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond UII_cond UIIx_cond UIL_cond
      }

      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawString();"] 
      LLUI_c [label="[FrontPanel]\nLLUIPainter.drawString();"]
      UID_h [label="[FrontPanel]\ngetUIDrawer().drawString();"]
      UID_weak_c [label="[FrontPanel]\nDisplayDrawer.drawString();"]
      UID_soft_h [label="[FrontPanel]\ngetUIDrawerSoftware()\n.drawString();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden?"]
      UIL_cond [label="supported font?"]
      UID_gpu_c [label="[VEE Port FP]\ComplexLayout\n.drawString();"]
      UID_gpu2_c [label="[VEE Port FP]\nLayoutAndDraw\n.drawString();"]

      UID_stub_c [label="[FrontPanel]\nno op"]
      stub [label="-"]

      // --- MULTIPLE FONTS FLOW ELEMENTS -- //

      UII_h [label="[FrontPanel]\ngetUIFontDrawer()\n.drawString();"]
      UII_cond [label="internal font?"]
      UIIx_cond [label="available font drawer\nand method implemented?"]
      UIIx_impl_c [label="[VEE Port Fp]\nCustomFontDrawing.draw()"]
      UIIx_impl_d [label="[custom drawing]"]

      UID_h2 [label="[FrontPanel]\ngetUIDrawer().drawString();\n@see Simple Flow (chapter Drawings)"]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
      UII_h->UII_cond
      UID_cond->UID_gpu_c [label="layout only" fontname="courier new" fontsize="10"]
      UID_cond->UID_gpu2_c [label="layout + draw" fontname="courier new" fontsize="10"]
      UID_gpu_c->UII_h
      UID_gpu2_c->UIL_cond
      UIL_cond->UIIx_impl_d [label="yes" fontname="courier new" fontsize="10"]
      UIL_cond->UII_h [label="no" fontname="courier new" fontsize="10"]
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

Let's implement the font drawer for the `CUSTOM_0` format.

.. code:: java

   public class MyCustomFontDrawer implements UIFontDrawing {

      @Override
      public MicroUIFontFormat handledFormat() {
         return MicroUIFontFormat.MICROUI_FONT_FORMAT_CUSTOM_0;
      }

      @Override
      public void draw(MicroUIGraphicsContext gc, char[] chars, int offset, int length, MicroUIFont font, int x, int y) {
         byte[] fontData = font.getFontData();
         MyCustomFont customFont = MyCustomFont.get(fontData);
         customFont.drawOn(gc, chars, offset, length, customFont, x, y);
      }

   }

Now, this drawer needs to be registered as a service.
This can be achieved by creating a file in the resources of the Front Panel project named ``META-INF/services/ej.microui.display.UIFontDrawing`` and containing the fully qualified name of the previously created font drawer.

.. code-block::

   com.mycompany.MyCustomFontDrawer

It is also possible to declare it programmatically (see where a drawer is registered in the :ref:`drawing custom <section_drawings_sim_custom>` section):

.. code-block:: java

   LLUIDisplay.Instance.registerUIFontDrawer(new MyCustomFontDrawer());

Installation
============

The Font Renderer is part of the MicroUI module and Display module.
You must install them in order to be able to use some fonts.


Use
===

The MicroUI font APIs are available in the class
`ej.microui.display.Font`_.

.. _ej.microui.display.Font: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html#
.. _RenderableString: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/RenderableString.html#

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
