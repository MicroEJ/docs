.. _section_drawings:

========
Drawings
========

Abstraction Layer
=================

All MicroUI drawings (available in the `Painter`_ class) call a native function.
These native functions are already implemented (in the :ref:`section_drawings_cco` for the Embedded VEE Port and in the :ref:`Front Panel <section_drawings_sim>` for the Simulator).
These implementations use the Graphics Engine's software algorithms to perform the drawings.

Each drawing can be overwritten independently in the VEE Port:

- to use another software algorithm (custom algorithm, no third-party library, etc.),
- to use a GPU to perform the operation,
- to target a destination whose format is different from the display back buffer format,
- etc.
 
The MicroUI native drawing functions are listed in ``LLUI_PAINTER_impl.h`` and ``LLDW_PAINTER_impl.h`` (for the `Drawing`_ library) for the Embedded VEE Port and, respectively, ``LUIPainter.java`` and ``LLDWPainter.java`` for the Simulation VEE Port.

The implementation must handle many constraints: synchronization between drawings, Graphics Engine notification, MicroUI `GraphicsContext`_ clip and colors, dirty flush area, etc.
The principle of implementing a MicroUI drawing function is described in the chapter :ref:`section_drawings_custom`.

.. _section_drawings_destination_format:

Destination Format
==================

Since MicroUI 3.2, the destination buffer of the drawings can be different than the display back buffer format (see :ref:`section_image_display_raw`).
This destination buffer format can be a :ref:`standard format <section_image_standard_raw>` (ARGB8888, A8, etc.) or a :ref:`custom format <section_image_custom_raw>`.

See :ref:`section_buffered_image` for more information about how to create buffered images with another format than the display format and how to draw in them.

.. _section_drawings_soft:

Graphics Engine Software Algorithms
===================================

The Graphics Engine features a software implementation for each MicroUI and Drawing libraries drawing.
These software algorithms respect the MicroUI GraphicsContext clip and use the current MicroUI GraphicsContext foreground color and optional background color.

The Graphics Engine provides a header file ``ui_drawing_soft.h`` (emb), and an implementation instance of ``UIDrawing`` that can be retrieved with ``ej.microui.display.LLUIDisplay.getUIDrawerSoftware()`` (sim) to let the VEE Port use these algorithms.
For instance, a GPU may be able to draw an image whose format is RGB565 but not ARGB1555.
For this image format, BSP implementation can call the ``UI_DRAWING_SOFT_drawImage`` function.

.. warning:: These software algorithms only target buffers whose format is the display back buffer format.

.. _section_drawings_cco:

MicroUI C Module
================ 

Principle
---------

An implementation of ``LLUI_PAINTER_impl.h`` is already available on the :ref:`MicroUI C module<section_ui_releasenotes_cmodule>`.
This implementation respects the synchronization between drawings and the Graphics Engine notification and reduces (when possible) the MicroUI `GraphicsContext`_ clip constraints.

This implementation does not perform the drawings; it only calls the equivalent of drawing available in ``ui_drawing.h``.
This allows simplifying how to use a GPU (or a third-party library) to perform a drawing: the ``ui_drawing.h`` implementation just has to take into consideration the MicroUI `GraphicsContext`_ clip and colors.
Synchronization with the Graphics Engine is already performed.

In addition to the implementation of ``LLUI_PAINTER_impl.h``, an implementation of ``ui_drawing.h`` is already available in :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` (in *weak* mode).
This allows to implement only the functions the GPU can perform.
For a given drawing, the weak function implementation is calling the equivalent of the drawing available in 
``ui_drawing_soft.h`` (this file lists all drawing functions implemented by the Graphics Engine in software).

.. note:: More details are available in ``LLUI_PAINTER_impl.h``, ``ui_drawing.h``, ``LLUI_Display.h``, and ``LLUI_Display_impl.h`` files.

Default Implementation
----------------------

The default implementation is the most used.
It takes into account:

* there is only one destination format (the display back buffer format),
* no drawing is overwritten in the BSP (no GPU, third-party library, etc.),
* :ref:`non-standard images <section_image_custom_raw>` cannot be used as a source.

The :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` is designed to simplify the UI VEE Port:

* just need to add the C module in the BSP (no extra code is needed),
* flash footprint is reduced (no extra table to manage several destination formats and several sources),
* functions indirections are limited (the software drawing algorithm is called as faster as possible).

The following diagram illustrates the steps to perform a shape drawing (not an image):

.. graphviz:: :align: center

   digraph {

      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"];
      
      { //out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui, UID_soft_c
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h, UID_h, UID_soft_h
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
         
      // --- ELEMENTS -- //
         
      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_h [label="[LLUI_PAINTER_impl.h]\nLLUI_PAINTER_IMPL_drawXXX();"]
      LLUI_c [label="[LLUI_PAINTER_impl.c]\nLLUI_PAINTER_IMPL_drawXXX();"]
      UID_h [label="[ui_drawing.h]\nUI_DRAWING_drawXXX();"]
      UID_weak_c [label="[ui_drawing.c]\nweak UI_DRAWING_drawXXX();"]
      UID_soft_h [label="[ui_drawing_soft.h]\nUI_DRAWING_SOFT_drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]
         
      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_weak_c->UID_soft_h->UID_soft_c

   }

.. force a new line

|

**LLUI_PAINTER_IMPL_drawLine** (available in MicroUI C Module)

.. code-block:: c

   void LLUI_PAINTER_IMPL_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY) {
      // Synchronize the native function of MicroUI Painter.drawLine() with the Graphics Engine
      if (LLUI_DISPLAY_requestDrawing(gc, (SNI_callback)&LLUI_PAINTER_IMPL_drawLine)) {
         // Call ui_drawing.h function
         DRAWING_Status status = UI_DRAWING_drawLine(gc, startX, startY, endX, endY);
         // Update the status of the Graphics Engine
         LLUI_DISPLAY_setDrawingStatus(status);
      }
   }

The Graphics Engine requires synchronization between the drawings.
Doing that requires a call to ``LLUI_DISPLAY_requestDrawing`` at the beginning of native function implementation.
This function takes as a parameter the MicroUI `GraphicsContext`_ and the pointer on the native function itself.
This pointer must be cast in a ``SNI_callback``.

**UI_DRAWING_drawLine** (available in MicroUI C Module)

.. code-block:: c

   #define UI_DRAWING_DEFAULT_drawLine UI_DRAWING_drawLine

The function name is set with preprocessor macros.
This name redirection is useful when the VEE Port features multiple destination formats (not the use-case here).

**UI_DRAWING_DEFAULT_drawLine** (available in MicroUI C Module)

.. code-block:: c

   // Use the compiler's 'weak' attribute
   __weak DRAWING_Status UI_DRAWING_DEFAULT_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY) {
      // Default behavior: call the Graphics Engine's software algorithm
      return UI_DRAWING_SOFT_drawLine(gc, startX, startY, endX, endY);
   }

Implementing the weak function only consists in calling the Graphics Engine's software algorithm.
This software algorithm will respect the `GraphicsContext`_ color and clip.

.. _section_drawings_cco_custom:

Custom Implementation
---------------------

The custom implementation helps connect a GPU or a third-party library.
It takes into account:

* there is only one destination format (the display back buffer format),
* :ref:`non-standard images <section_image_custom_raw>` cannot be used as a source.

The :ref:`MicroUI C module<section_ui_releasenotes_cmodule>` is designed to simplify the adding of third-party drawers:

* just need to add the C module in the BSP,
* overwrite only the expected drawing(s),
* a drawing implementation has just to respect the clip and color (synchronization with the Graphics Engine already done),
* flash footprint is reduced (no extra table to manage several destination formats and several sources),
* functions indirections are limited (the drawing algorithm is called as faster as possible).

The following diagram illustrates the steps to perform a shape drawing (not an image):


.. graphviz:: :align: center

   digraph {
      ratio="auto";
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"];
      
      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui, UID_soft_c, UID_gpu_hard
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] LLUI_h, UID_h, UID_soft_h
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c, UID_gpu_c, UID_gpu_driver
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond, UID_gpu_cond
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

      UID_cond [label="Function implemented?"]
      UID_gpu_c [label="[ui_drawing_gpu.c]\nUI_DRAWING_drawXXX();"]
      UID_gpu_cond [label="GPU compatible?"]
      UID_gpu_driver [label="[GPU driver]"]
      UID_gpu_hard [label="[GPU]"]

      // --- FLOW -- //

      mui->LLUI_h->LLUI_c->UID_h->UID_cond
      UID_cond->UID_weak_c [label="no" fontname="courier new" fontsize="10"]
      UID_weak_c->UID_soft_h->UID_soft_c
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UID_gpu_driver [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_driver->UID_gpu_hard
      UID_gpu_cond->UID_soft_h [label="no" fontname="courier new" fontsize="10"]
   }

.. force a new line

|

Take the same example as the default implementation (draw a line): the BSP just has to overwrite the weak function ``UI_DRAWING_drawLine`` :

**UI_DRAWING_drawLine** (to write in the BSP)

.. code-block:: c

   #define UI_DRAWING_GPU_drawLine UI_DRAWING_drawLine

The function name should be set with preprocessor macros.
This name redirection is useful when the VEE Port features multiple destination formats (not the use-case here).

**UI_DRAWING_GPU_drawLine** (to write in the BSP)

.. code-block:: c

   // Contrary to the MicroUI C Module, this function is not "weak"
   DRAWING_Status UI_DRAWING_GPU_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY) {
      
      DRAWING_Status status;

      if (is_gpu_compatible(xxx)) {
         // Can use the GPU to draw the line

         // Retrieve the destination buffer address
         uint8_t* destination_address = LLUI_DISPLAY_getBufferAddress(&gc->image);

         // Configure the GPU clip
         gpu_set_clip(startX, startY, endX, endY);

         // Draw the line
         gpu_draw_line(destination_address, startX, startY, endX, endY, gc->foreground_color);

         // GPU is running: set the right status for the Graphics Engine
         status = DRAWING_RUNNING;
      }
      else {
         // Default behavior: call the Graphics Engine's software algorithm (like "weak" function)
         status = UI_DRAWING_SOFT_drawLine(gc, startX, startY, endX, endY);
      }
      return status;
   }

First, the drawing function must ensure the GPU can render the expected drawing.
If not, the drawing function must perform the same thing as the default weak function: calls the Graphics Engine software algorithm.

The GPU drawing function usually requires the destination buffer address: the drawing function calls ``LLUI_DISPLAY_getBufferAddress(&gc->image);``.

The drawing function has to respect the `GraphicsContext`_ clip
The ``MICROUI_GraphicsContext`` structure holds the clip, and the drawer cannot perform a drawing outside this clip (otherwise, the behavior is unknown).
Note the bottom-right coordinates might be smaller than the top-left (in x and/or y) when the clip width and/or height is null.
The clip may be disabled (when the current drawing fits the clip); this allows to reduce runtime.
See ``LLUI_DISPLAY_isClipEnabled()``.

.. hint:: Several clip functions are available in ``LLUI_DISPLAY.h`` to check if a drawing fits the clip.

Finally, after the drawing, the drawing function has to return the drawing status.
Most of the time, the GPU performs *asynchronous* drawings: the drawing is started but not completed.
To notify the Graphics Engine, the status to return is ``DRAWING_RUNNING``.
In case of the drawing is done after the call to ``gpu_draw_line()``, the status to return is ``DRAWING_DONE``.

.. warning:: 
   
   If the drawing status is not set to the Graphics Engine, the global VEE execution is locked: the Graphics Engine waits indefinitely for the status and cannot perform the next drawing.

GPU Synchronization
-------------------

When a :ref:`GPU is used to perform a drawing<section_drawings_cco_custom>`, the caller (MicroUI painter native method) returns immediately.
This allows the application to perform other operations during the GPU rendering.
However, as soon as the application is trying to perform another drawing, the previous drawing made by the GPU must be done.
The Graphics Engine is designed to be synchronized with the GPU asynchronous drawings by defining some points in the rendering timeline.
It is not optional: MicroUI assumes that a drawing is fully done when it starts a new one.
The end of a GPU drawing must notify the Graphics Engine calling ``LLUI_DISPLAY_notifyAsynchronousDrawingEnd()``.

Extended C Modules
------------------

Several :ref:`section_ui_cco` are available on the MicroEJ Repositories.
These modules are compatible with the MicroUI C module (they follow the rules described above) and use one GPU (a C Module per GPU).
These C Modules should be fetched in the VEE Port in addition to the MicroUI C Module; it avoids re-writing the GPU port.

.. _section_drawings_sim:

Simulation
==========

Principle
---------

This is the same principle as :ref:`section_drawings_cco` for the Embedded side: 

* The drawing primitive natives called the matching method in ``LLUIPainter``.
* The ``LLUIPainter`` synchronizes the drawings with the Graphics Engine and dispatches the drawing itself to an implementation of the interface ``UIDrawing``.
* The Front Panel provides a software implementation of ``UIDrawing`` available by calling ``ej.microui.display.LLUIDisplay.getUIDrawerSoftware()``.
* The ``DisplayDrawer`` implements ``UIDrawing`` and is used to draw in the display back buffer and the images with the same format.

These classes are available in the :ref:`UI Pack extension <section_ui_simulation>` of the Front Panel Mock.

.. note:: More details are available in ``LLUIPainter``, ``UIDrawing``, ``LLUIDisplay``, and ``LLUIDisplayImpl`` files.

Default Implementation
----------------------

The default implementation is the most used.
It considers that:

* there is only one destination format (the display back buffer format),
* no drawing is overwritten in the BSP (no third-party library),
* :ref:`non-standard images <section_image_custom_raw>` cannot be used as a source.

The :ref:`UI Pack extension <section_ui_simulation>` is designed to simplify the UI VEE Port:

* Simply add the dependency to the UI Pack extension in the VEE Port Front Panel project.
* Function indirections are limited (the software drawing algorithm is called as fast as possible).

The following diagram illustrates the steps to perform a shape drawing (not an image):

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"];
      
      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui, UID_soft_c
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] UID_h, UID_soft_h
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
         
      // --- ELEMENTS -- //
      
      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_c [label="[FrontPanel]\nLLUIPainter.drawXXX();"]
      UID_h [label="[FrontPanel]\ngetUIDrawer().drawXXX();"]
      UID_weak_c [label="[FrontPanel]\nDisplayDrawer.drawXXX();"]
      UID_soft_h [label="[FrontPanel]\ngetUIDrawerSoftware()\n.drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_soft_h->UID_soft_c
   }

.. force a new line

|

**LLUIPainter.drawLine** (available in UI Pack extension)

.. code-block:: java

   public static void drawLine(byte[] target, int x1, int y1, int x2, int y2) {

      // Retrieve the Graphics Engine instance
      LLUIDisplay graphicalEngine = LLUIDisplay.Instance;

      // Synchronize the native function of MicroUI Painter.drawLine() with the Graphics Engine
      synchronized (graphicalEngine) {

         // Retrieve the Front Panel instance of the MicroUI GraphicsContext (the destination)
         MicroUIGraphicsContext gc = graphicalEngine.mapMicroUIGraphicsContext(target);

         // Ask to the Graphics Engine if a drawing can be performed on the target
         if (gc.requestDrawing()) {

            // Retrieve the drawer for the GraphicsContext (by default: DisplayDrawer)
            UIDrawing drawer = getUIDrawer(gc);

            // Call UIDrawing function
            drawer.drawLine(gc, x1, y1, x2, y2);
         }
      }
   }

The Graphics Engine requires synchronization between the drawings.
To do that, the drawing is synchronized on the instance of the Graphics Engine itself.

The target (the Front Panel object that maps the MicroUI `GraphicsContext`_) is retrieved in the native drawing method by asking the Graphics Engine to map the byte array (returned by ``GraphicsContext.getSNIContext()``).
Like the embedded side, this object holds a clip, and the drawer cannot perform a drawing outside of this clip (otherwise, the behavior is unknown).

**DisplayDrawer.drawLine** (available in UI Pack extension)

.. code-block:: java

	@Override
	public void drawLine(MicroUIGraphicsContext gc, int x1, int y1, int x2, int y2) {
		LLUIDisplay.Instance.getUIDrawerSoftware().drawLine(gc, x1, y1, x2, y2);
	}

The implementation of ``DisplayDrawer`` simply calls the Graphics Engine's software algorithm.
This software algorithm will use the `GraphicsContext`_ color and clip.

.. _section_drawings_sim_custom:

Custom Implementation
---------------------

The custom implementation helps connect a third-party library or to simulate the same constraints as the embedded side (the same GPU constraints).
It considers that:

* there is only one destination format (the display back buffer format),
* :ref:`non-standard images <section_image_custom_raw>` cannot be used as a source.

The :ref:`UI Pack extension <section_ui_simulation>` is designed to simplify the adding of third-party drawers:

* Add the dependency to the UI Pack extension in the VEE Port Front Panel project.
* Create a subclass of ``DisplayDrawer`` (implementation of the interface ``UIDrawing``).
* Overwrite only the desired drawing(s).
   * Each drawing implementation must comply with the clip and color (synchronization with the Graphics Engine already done).
   * Function indirections are limited (the drawing algorithm is called as fast as possible).
* Register this drawer in place of the default display drawer.

The following diagram illustrates the steps to perform a shape drawing (not an image):

.. graphviz:: :align: center

   digraph {
      ratio="auto"
      splines="true";
      bgcolor="transparent"
      node [style="filled,rounded" fontname="courier new" fontsize="10"];
      
      { //in/out
         node [shape="ellipse" color="#e5e9eb" fontcolor="black"] mui, UID_soft_c, UID_gpu_hard
      }
      { // h
         node [shape="box" color="#00aec7" fontcolor="white"] UID_h, UID_soft_h
      }
      { // c
         node [shape="box" color="#ee502e" fontcolor="white"] LLUI_c, UID_gpu_c
      }
      { // weak
         node [shape="box" style="dashed,rounded" color="#ee502e"] UID_weak_c
      }
      { // choice
         node [shape="diamond" color="#e5e9eb"] UID_cond, UID_gpu_cond
      }
         
      // --- SIMPLE FLOW ELEMENTS -- //

      mui [label="[MicroUI]\nPainter.drawXXX();"] 
      LLUI_c [label="[FrontPanel]\nLLUIPAINTER.drawXXX();"]
      UID_h [label="[FrontPanel]\ngetUIDrawer().drawXXX();"]
      UID_weak_c [label="[FrontPanel]\nDisplayDrawer.drawXXX();"]
      UID_soft_h [label="[FrontPanel]\ngetUIDrawerSoftware()\n.drawXXX();"]
      UID_soft_c [label="[Graphics Engine]"]

      // --- GPU FLOW ELEMENTS -- //

      UID_cond [label="method overridden?"]
      UID_gpu_c [label="[VEE Port FP]\nDisplayDrawerExtension\n.drawXXX();"]
      UID_gpu_cond [label="can draw algo?"]
      UID_gpu_hard [label="[Third-party lib]"]

      // --- FLOW -- //

      mui->LLUI_c->UID_h->UID_weak_c->UID_cond
      UID_cond->UID_soft_h [label="no" fontname="courier new" fontsize="10"]
      UID_soft_h->UID_soft_c
      UID_cond->UID_gpu_c [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_c->UID_gpu_cond
      UID_gpu_cond->UID_gpu_hard [label="yes" fontname="courier new" fontsize="10"]
      UID_gpu_cond->UID_soft_h [label="no" fontname="courier new" fontsize="10"]
   }

.. force a new line

|

Let's use the same example as the previous section (draw line function): the Front Panel project has to create its drawer based on the default drawer:

**MyDrawer** (to write in the Front Panel project)

.. code-block:: java

   public class MyDrawer extends DisplayDrawer {

      @Override
      public void drawLine(MicroUIGraphicsContext gc, int x1, int y1, int x2, int y2) {

         if (isCompatible(xxx)) {
            // Can use the GPU to draw the line on the embedded side: can use another algorithm than the software algorithm

            // Retrieve the AWT Graphics2D
            Graphics2D src = (Graphics2D)((BufferedImage)gc.getImage().getRAWImage()).getGraphics();

            // Draw the line using AWT (have to respect clip & color)
            src.setColor(new Color(gc.getRenderingColor()));
            src.drawLine(x1, y1, x2, x2);
         }
         else {
            // Default behavior: call the Graphics Engine's software algorithm
            super.drawLine(gc, x1, y1, x2, y2);
         }
      }
   }

The Front Panel framework is running over AWT.
The method ``gc.getImage()`` returns a ``ej.fp.Image``.
It is the representation of a MicroUI Image in the Front Panel framework.
The method ``gc.getImage().getRAWImage()`` returns the implementation of the Front Panel image on the Java SE framework: an `AWT BufferedImage`_. 
The AWT graphics 2D can be retrieved from this buffered image.

The MicroUI color (``gc.getRenderingColor()``) is converted to an AWT color.

The method behavior is exactly the same as the embedded side; see :ref:`section_drawings_cco_custom`.

This newly created drawer must now replace the default display drawer.
There are two possible ways to register it:

- Declare it as a UIDrawing service.
- Declare it programmatically.

**UIDrawing Service**

- Create a new file in the resources of the Front Panel project named ``META-INF/services/ej.microui.display.UIDrawing`` and write the fully qualified name of the previously created drawer:

.. code-block::

   com.mycompany.MyDrawer

**Programmatically**

- Create an empty widget to invoke the new implementation:

.. code-block:: java

   @WidgetDescription(attributes = { })
   public class Init extends Widget{
      @Override
      public void start() {
         super.start();
         LLUIDisplay.Instance.registerUIDrawer(new MyDrawer());
      }
   }
   
- Invoke this widget in the .fp file:

.. code-block:: java

   <frontpanel xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns="https://developer.microej.com" xsi:schemaLocation="https://developer.microej.com .widget.xsd">
      <device name="STM32429IEVAL" skin="Board-480-272.png">
         <com.is2t.microej.fp.Init/>
         [...]
      </device>
   </frontpanel>

.. _section_drawings_custom:

Custom Drawing
==============

Principle
---------

MicroUI allows adding some custom drawings (drawings not listed in the MicroUI Painter classes).
A custom drawing has to respect the same rules as the MicroUI drawings to avoid corrupting the MicroUI execution (flickering, memory corruption, unknown behavior, etc.).

As explained above, MicroUI implementation provides an Abstraction Layer that lists all MicroUI Painter drawing native functions and their implementations (:ref:`section_drawings_cco` and :ref:`section_drawings_sim`).
The implementation of MicroUI Painter drawings should be used as a model to implement the custom drawings.

Application Method
------------------

.. code-block:: java

   // Application drawing method
   protected void render(GraphicsContext gc) {

      // [...]

      // Set the GraphicsContext color
      gc.setColor(Colors.RED);
      // Draw a red line
      Painter.drawLine(gc, 0, 0, 10, 10);
      // Draw a red custom drawing
      drawCustom(gc.getSNIContext(), 5, 5);

      // [...]
   }

   // Custom drawing native method
   private static native void drawCustom(byte[] graphicsContext, int x, int y);

All native functions must have a MicroUI `GraphicsContext`_ as a parameter (often the first parameter) that identifies the destination target.
The application retrieves this target by calling the method ``GraphicsContext.getSNIContext()``.
This method returns a byte array to give as-is to the drawing native method.

BSP Implementation
------------------

The native drawing function implementation pattern is:

.. code:: c

   void Java_com_mycompany_MyPainterClass_drawCustom(MICROUI_GraphicsContext* gc, jint x, jint y) {

      // Tell the Graphics Engine if the drawing can be performed
      if (LLUI_DISPLAY_requestDrawing(gc, (SNI_callback)&Java_com_mycompany_MyPainterClass_drawCustom)) {
         DRAWING_Status status;

         // Perform the drawing (respecting clip if not disabled)
         status = custom_drawing(LLUI_DISPLAY_getBufferAddress(&gc->image), x, y);

         // Set drawing status
         LLUI_DISPLAY_setDrawingStatus(status);
      }
      // Else: refused drawing
   }

The target (the MicroUI `GraphicsContext`_) is retrieved in the native drawing function by mapping the ``MICROUI_GraphicsContext`` structure in MicroUI native drawing function declaration.

This implementation has to follow the same rules as the custom MicroUI drawings implementation: see :ref:`section_drawings_cco_custom`.

Simulation
----------

.. note:: This chapter considers the VEE Port Front Panel project already features a custom drawer that replaces the default drawer ``DisplayDrawer``. See :ref:`section_drawings_sim_custom`.

The native drawing function implementation pattern is as follows (see below for the explanations):

.. code-block:: java

   public static void drawCustom(byte[] target, int x, int y) {
   
      // Retrieve the Graphics Engine instance
      LLUIDisplay graphicalEngine = LLUIDisplay.Instance;

      // Synchronize the native function with the Graphics Engine
      synchronized (graphicalEngine) {

         // Retrieve the Front Panel instance of the MicroUI GraphicsContext (the destination)
         MicroUIGraphicsContext gc = graphicalEngine.mapMicroUIGraphicsContext(target);

         // Ask to the Graphics Engine if a drawing can be performed on the target
         if (gc.requestDrawing()) {

            // Retrieve the drawer for the GraphicsContext (by default: DisplayDrawer)
            UIDrawing drawer = getUIDrawer(gc);

            // Call UIDrawing function
            MyDrawer.Instance.drawSomething(gc, x, y);
         }
      }
   }

This implementation has to follow the same rules as the custom MicroUI drawings implementation: see :ref:`section_drawings_sim_custom`.

.. _section.veeport.ui.drawings.drawing_logs:

Drawing Logs
============

When performing drawing operations, the program may fail or encounter an incident of some kind.
MicroUI offers a mechanism allowing the VEE Port to report such incidents to the application through the use of flags.

Usage Overview
--------------

When an incident occurs, the VEE Port can report it to the application by setting the *drawing log flags* stored in the graphics context.
The flags will then be made available to the application.
See :ref:`section.ui.drawing_logs` for more information on reading the flags in the application.

Without an intervention from the application, the drawing log flags retain their values through every call to drawing functions and are cleared when a flush is performed.

.. note::

   The clearing of drawing log flags can be disabled at build time by the application developer.

Incidents are split into two categories:

* *Non-critical* incidents, or *warnings*, are incidents that the application developer may ignore.
  The flags are made available for the application to check, but without an explicit statement in the application, these incidents will be ignored silently.
* *Critical* incidents, or *errors*, are failures significant enough that the application developer should not ignore them.
  As for warnings, the application may check the drawing log flags explicitly.
  However, when flushing the display, the application checks the flags and throws an exception if an error has been reported.

.. warning::

   As this behavior can be disabled at build time, the drawing log flags are meant to be used as a **debugging hint** when the application does not display what the developer expects.
   The VEE Port must **not** rely on applications throwing an exception if an error was reported or on the drawing log flags being reset after the display is flushed.

.. note::

   Any incident may be either a *warning* or an *error*.
   They are differentiated with the special flag ``DRAWING_LOG_ERROR``.

Available Constants
-------------------

MicroUI offers a set of flag constants to report incidents to the application.
They are defined and documented in ``LLUI_PAINTER_impl.h`` (for embedded targets) and ``LLUIPainter`` (for front panels).

Refer to the :ref:`application documentation<section.ui.drawing_logs_constants>` for the exhaustive list of drawing logs.

.. hint::

   Sometimes, incidents may match more than one flag constant.
   In such cases, the VEE Port may report the incident with multiple flags by combining them with the bitwise OR operator (``|``), just like any other flags.
   For example, an out-of-memory incident occurring in an underlying drawing library may be reported with the value ``DRAWING_LIBRARY_INCIDENT | DRAWING_OUT_OF_MEMORY``.

Embedded Targets
----------------

MicroUI exposes two functions to be used in the VEE Port.
Both functions are declared in ``LLUI_DISPLAY.h``, and their documentation is available in that file.

* ``LLUI_DISPLAY_reportWarning`` reports a warning to the application.
  It will set the flags passed as an argument in the graphics context.
  It will *not* reset the previous flag values, thus retaining all reported incidents until the application clears the flags.
* ``LLUI_DISPLAY_reportError`` reports an error to the application.
  It behaves similarly to ``LLUI_DISPLAY_reportWarning``, except it will additionally set the flag ``DRAWING_LOG_ERROR``.
  This special flag will cause an exception to be thrown in the application the next time the application checks the flags.

For example, if the VEE Port contains a custom implementation to draw a line that may cause an out-of-memory error, it could report this error this way:

.. code:: c

   void LLUI_PAINTER_IMPL_drawLine(MICROUI_GraphicsContext* gc, jint startX, jint startY, jint endX, jint endY) {
      // This could cause an out-of-memory error.
      unsigned int result = custom_line_drawing();

      // Check if an error occurred.
      if (result == OUT_OF_MEMORY) {
         // If an error occurred, set the corresponding flag.
         LLUI_DISPLAY_reportError(gc, DRAWING_LOG_OUT_OF_MEMORY);
      }
   }

Simulator
---------

Similarly, MicroUI exposes two functions to set drawing log flags in the front panel implementation.
Both functions are declared as methods of the interface ``MicroUIGraphicsContext`` and are documented there.
The Graphics Engine provides an implementation for these methods.

* ``MicroUIGraphicsContext.reportWarning`` behaves like ``LLUI_DISPLAY_reportWarning`` and reports a warning to the application.
* ``MicroUIGraphicsContext.reportError`` behaves like ``LLUI_DISPLAY_reportError`` and reports an error to the application.

The front panel version of the previous example that reported an out-of-memory error would look like this:

.. code:: java

   public static void drawLine(byte[] target, int startX, int startY, int endX, int endY) {
      LLUIDisplay engine = LLUIDisplay.Instance;

      synchronized (engine) {
         MicroUIGraphicsContext gc = engine.mapMicroUIGraphicsContext(target);

         // This could cause an out-of-memory error.
         int result = CustomDrawings.drawLine();

         // Check if an error occurred.
         if (result == Constants.OUT_OF_MEMORY) {
            // If an error occurred, set the corresponding flag.
            gc.reportError(gc, DRAWING_LOG_OUT_OF_MEMORY);
         }
      }
   }


.. _AWT BufferedImage: https://docs.oracle.com/javase/7/docs/api/java/awt/image/BufferedImage.html
.. _Display.flush(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#flush--
.. _Painter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Painter.html
.. _GraphicsContext: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html
.. _Drawing: https://repository.microej.com/modules/ej/api/drawing


..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
