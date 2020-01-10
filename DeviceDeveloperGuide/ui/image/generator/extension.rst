Extensions Purpose
==================

The output representation of the images in the same format as the LCD
(same pixel representation, see `??? <#imagen_lcd_format>`__) is
dependent on the drivers that run the underlying screen. Indeed, the
output raw format is specific to each display device. The Image
Generator tool provided is expandable by extensions, each extension
implementing a dedicated display device layout.

Standard Extension
------------------

When the LCD pixels representation is standard (``ARGB8888`` or
``RGB565`` etc., see `??? <#display_pixel_structure>`__) the image
generator does not need an extension. The formulas of conversions
``ARGB8888`` to RAW formats are the same as described in the chapter
`??? <#display_pixel_structure>`__.

Generic Extension
-----------------

When the LCD pixel representation is generic
(``1 | 2 | 4 | 8 | 16 | 24 | 32``, see
`??? <#display_pixel_structure>`__) the image generator requires an
extension in order to understand how to convert ARGB pixels into LCD
pixel representations.

The Display module provides generic display implementation according the
number of bits-per-pixels (1, 2, 4, 8, 16, 24 and 32). The Image
Generator tool provides a simple extension to implement in order to
target these kinds of displays: ``GenericDisplayExtension``.  [1]_

A method must be implemented in relation to the way the driver has built
the layout of the display buffers in memory: The
``convertARGBColorToDisplayColor`` method is used to convert a 32-bits
ARGB color into the display pixel memory representation.

.. note::

   The Image Generator automatically uses the right number of bits to
   represent a pixel (BPP) and respect the memory buffer layout using
   the result of the installation of the Display module.

.. _section_image_extension:

Create an Extension
-------------------

Follow the steps below to create an Image Generator extension:

1. First, create a new J2SE project, called (for example)
   ``imageGeneratorExtension``.

2. In the project's Java build path (project's property window, select
   ``Java Build Path > Libraries tab``), add the variable
   ``IMAGE-GENERATOR-x.y``.

3. Create the package ``com.is2t.microui.generators.extension``.

4. Create a class in the package whose name must be:
   ``MicroUIGeneratorExtension``.

5. The Java class must implement the extension interface available in
   the library ``IMAGE-GENERATOR-x.y`` (see previous chapters). Fill the
   required methods.

The Java project should now look like this:

.. figure:: ui/image/generator/images/imagen.png
   :alt: Image Generator Extension Project

   Image Generator Extension Project

With a Java class like this:

::

   package com.is2t.microui.generators.extension;

   import com.is2t.microej.microui.image.GenericDisplayExtension;

   public class MicroUIGeneratorExtensionMyLCD implements GenericDisplayExtension{

       public int convertARGBColorToDisplayColor(int color) {
           return (char) 
               ((color & 0xf80000) >>> 8) | 
               ((color & 0x00fc00) >>> 5) | 
               ((color & 0x0000f8) >>> 3);       
       }

   }

.. [1]
   Package com.is2t.microej.microui.image
