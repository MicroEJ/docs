.. _ui_port_gpu:

========
GPU Port
========

Principle
=========

MicroUI and MicroUI C modules are designed to be extended using a GPU hardware drawing acceleration.
This acceleration is optional and should be performed after the mandatory operations (see :ref:`ui_port_bsp`).

A GPU can be used to draw shapes and/or images.
Most of the time, the minimal implementation consists of filling the rectangles and drawing the images.
The MicroUI C module is designed to let the BSP implement only the GPU features.
When a drawing is not implemented over a GPU, the software implementation is automatically used instead.
No extra code should be added to the BSP to use the software algorithms.

The main advantages of using a GPU are:

- the drawing is rendered faster than using the software algorithms,
- the drawing is performed asynchronously, allowing the MCU to perform other actions (no need to wait until the end of the drawing).

Existing C Modules
==================

Some C modules are available on the MicroEJ Repository.
These C modules already implement compatible features with a GPU.
Unzip them in the BSP project to use the associated GPU (and add the CCO's include folder to the BSP project's include directories list).
Refer to :ref:`section_ui_releasenotes_cmodule` to have more information.

Port a GPU
==========

Drawing Function
----------------

As described in :ref:`section_display_llapi_painter`, the idea of the implementation of ``LLUI_PAINTER_impl.h`` (and ``LLDW_PAINTER_impl.h``) is first to manage the synchronization with the Graphics Engine and then, to dispatch the drawing itself to a third party implementation through the header file ``ui_drawing.h`` (respectively ``dw_drawing.h``).
The files ``LLUI_PAINTER_impl.c`` and ``LLDW_PAINTER_impl.c`` available in the MicroUI C module already perform this operation for all MicroUI drawings.
Consequently, only the drawing itself should be implemented in the BSP.

For example:

.. code-block:: c

   DRAWING_Status UI_DRAWING_fillRectangle(MICROUI_GraphicsContext* gc, jint x1, jint y1, jint x2, jint y2) {
      // TODO
   }

The drawing function has to respect these elements:

- the color: the structure ``MICROUI_GraphicsContext`` gives the shape color (always fully opaque),
- the clip: the LLUI_DISPLAY.h file provides some functions to retrieve the current ``MICROUI_GraphicsContext``'s clip,
- the buffer destination address by calling the ``LLUI_DISPLAY_getBufferAddress`` function,
- the shape bounds: the drawing function parameters.

The drawing function must return the drawing status.
This status indicates to the Graphics Engine the kind of drawing: 

- synchronous drawing: the drawing is performed by the GPU and entirely performed before returning. In that case, the drawing function has to return ``DRAWING_DONE``.
- asynchronous drawing: the drawing is launched, maybe started by the GPU (or even finished) before returning. In that case, the drawing function has to return ``DRAWING_RUNNING``.

As explained above, the second case should be the rule.
That means the Graphics Engine cannot ask for another drawing (accelerated or not) before the end of the drawing currently performed by the GPU.
To unlock the Graphics Engine, the GPU interrupt routine must call the Graphics Engine function ``LLUI_DISPLAY_notifyAsynchronousDrawingEnd`` to notify the end of the drawing.
The Graphics Engine manages the synchronization alone; no extra support in the BSP is mandatory.

.. note:: The end of the asynchronous drawing may occur before the end of the drawing function execution (before returning). The Graphics Engine also manages this use case, and the BSP implementation does not need to check this use case.

Fallback
--------

A GPU may not be able to manage all drawing function use cases.
For instance, it cannot manage all image formats, or it cannot manage all rotation angles, etc.
In that case, the drawing function can call the software drawing function instead.

.. code-block:: c


   DRAWING_Status UI_DRAWING_fillRectangle(MICROUI_GraphicsContext* gc, jint x1, jint y1, jint x2, jint y2) {
      DRAWING_Status ret;
      if (!compatible_drawing(gc, x1, y1, x2, y2)) {
         UI_DRAWING_SOFT_fillRectangle(gc, x1, y1, x2, y2);
         ret = DRAWING_DONE;
      }
      else {
         gpu_fill_rect(LLUI_DISPLAY_getBufferAddress(&gc->image), x1, y1, x2, y2);
         ret = DRAWING_RUNNING;
      }
      return ret;
   }

Image Constraints
=================

A GPU may require some constraints on the images:

- the pixels buffer start address alignment,
- an image stride different than the image width.

These constraints affect the compile-time images (Image Generator) and the runtime images (decoded images and MicroUI BufferedImage).

Address Alignment
-----------------

In the VEE Port Configuration project, specify the property ``imageBuffer.memoryAlignment`` in the ``display.properties`` file. 
The value is the alignment in bits.
This value will be respected by the compile-time images (Image Generator) and the runtime images.

.. note:: For the runtime image, this alignment value may be customized thanks to the function again ``LLUI_DISPLAY_IMPL_adjustNewImageCharacteristics``.

Stride (Compile-time Images)
----------------------------

The stride is dynamic, often depending on the image format and width.
Consequently, the stride cannot be described thanks to a property in the ``display.properties`` file. 

For the compile-time images (Image Generator), a specific extension of the ImageGenerator is required.

1. See :ref:`section_image_generator_extended` to create the ImageGenerator extension project.
2. Create a class that implements ``BufferedImageLoader``. The value to be returned is expressed in pixels.

.. code-block:: java

   public class MicroUIGeneratorExtension extends BufferedImageLoader{

      private static final int ALIGNMENT_PIXELS = 16;

      @Override
      public int getStride(int defaultStride) {
         return (getWidth() + ALIGNMENT_PIXELS - 1) & ~(ALIGNMENT_PIXELS - 1);
      }
   }

3. Create the file ``/META-INF/services/com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension``
4. Fill it with the class name:

.. code-block:: java

      my.package.MicroUIGeneratorExtension

5. Build the project and copy the result in the VEE Port Configuration project, subfolder ``dropins/tools``.
6. Rebuild the VEE Port.

Stride (Runtime Images)
-----------------------

For the compile-time images, the BSP has to implement the LLAPI ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes`` (the value to be returned is expressed in bytes):

.. code-block:: c

   uint32_t UI_DRAWING_getNewImageStrideInBytes(jbyte image_format, uint32_t image_width, uint32_t image_height, uint32_t default_stride) {
         uint32_t bpp = DISPLAY_UTILS_get_bpp((MICROUI_ImageFormat)image_format);
         return (bpp >= (uint32_t)8) ? ALIGN(image_width, (uint32_t)16) * (bpp / (uint32_t)8) : ALIGN(image_width, (uint32_t)8);
   }

Test Suite
==========

As described :ref:`here <ui_port_bsp_testsuite>`, the Port Qualification Toolkit (PQT) provides a UI test suite to validate the UI Port.
The second block of the UI test suite (extended *Display* test suite) uses a library that tests several MicroUI drawings.
This test suite **must** be executed to validate the UI Port over a GPU and after each modification on this UI Port (for instance, after changes to improve performances).

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
