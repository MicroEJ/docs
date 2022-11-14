
========
Overview
========

Principle
=========

The Image Engine is designed to make the distinction between three kinds of MicroUI images:

* the images which can be used by the application without a loading step: class `Image`_,
* the images which requires a loading step before being usable by the application: class `ResourceImage`_,
* the buffered images where the application can draw into: class `BufferedImage`_.

The first kind of image requires the Image Engine to be able to use (get, read and draw) an image referenced by its path without any loading step. The *open* step should be very fast: just have to find the image in the application resources list and create an `Image`_ object which targets the resource. No RAM memory to store the image pixels is required: the Image Engine directly uses the resource address (often in FLASH memory). And finally, *closing* step is useless because there is nothing to free (except `Image`_ object itself, via the garbage collector).

The second kind of image requires the Image Engine to be able to use (load, read and draw) an image referenced by its path with or without any loading step. When the image is understandable by the Image Engine without any loading step, the image is considered like the first kind of image (fast *open* step, no RAM memory, useless *closing* step). When a loading step is required (dynamic decoding, external resource loading, image format conversion), the *open* state becomes longer and a buffer in RAM is required to store the image pixels. By consequence a *closing* step is required to free the buffer when image becomes useless.

The third kind of image requires, by definition, a buffer to store the image pixels. Image Engine must be able to use (create, read and draw) this kind of image. The *open* state consists in creating a buffer. By consequence a *closing* step is required to free the buffer when the image becomes useless. Contrary to the other kinds of images, the application will be able to draw into this image.

.. _Image: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#
.. _ResourceImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html#
.. _BufferedImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/BufferedImage.html#

.. _section_image_core_process:

Functional Description
======================

The Image Engine is composed of:

* An "Image Generator" module, for converting images into a MicroEJ format (known by the Image Engine Renderer) or into a platform binary format (cannot be used by the Image Engine Renderer), before runtime (pre-generated images).
* The "Image Loader" module, for loading, converting and closing the images. 
* A set of "Image Decoder" modules, for converting standard image formats into a MicroEJ format (known by the Image Renderer) at runtime. Each Image Decoder is an additional module of the main module "Image Loader".
* The "Image Renderer" module, for reading and drawing the images in MicroEJ format.

.. graphviz::

  digraph {
     
      graph [
         overlap=false
         splines=true
         nodesep=0.7
         ranksep=0.7
         bgcolor="transparent"
         center=1
      ];
      
      node [
         fixedsize=true,
         fontname="Ubuntu"
         fontsize=16
         fontcolor=dimgray
         height=1
         width=2.5
         shape=box
         fillcolor=aliceblue
         style="filled,setlinewidth(3)",
      ];
         
      edge [
         arrowsize=1
         fontsize=16
         fontname="Ubuntu"
         fontcolor=dimgray
      ];
            
      { 
         node [color="lightblue"]
         input generator
      }
      
      { 
         node [color="darkorange2"]
         loader png xxx app algo convert
      }
      
      { 
         node [color="chartreuse2"]
         rom ram ext hard gpu
      }
      
      { 
         node [color="gray"]
         bsp
      }
         
      {
         input [label="Input Files\n(png, xxx)"]
         generator [label="Image Generator"]
         loader [label="Image Loader"]
         rom [label="Flash\n(internal ROM, NOR)"]
         ext [label="External Flash\n(SDCard etc.)"]
         ram [label="RAM"]
         app [label="Image Renderer"]
         bsp [label="BSP"]
         png [label="PNG Decoder"]
         xxx [label="XXX Decoder"]
         convert [label="MEJ Converter"]
         gpu [label="GPU"]
         algo [label="Software\nAlgorithms"]
         hard  [label="Memory Buffer"]
      }         
                  
      input -> {rom ext generator} [ label = "png | xxx"]
      
      generator ->  {rom ext} [label = "png | xxx | mej | bin"]
      
      loader ->  png [label = "png"]
      loader ->  xxx [label = "xxx"]
      loader ->  convert [label = "mej"]
      {png xxx convert} ->  ram [label = "mej"]
      
      app -> bsp  [label = "mej"]
      
      rom ->  bsp [label = "bin"]
      rom ->  loader [label = "png | xxx | mej (to convert)"]
      rom -> app [label = "mej"]
      ram -> app [label = "mej"]
      
      bsp -> gpu  [label = "mej | bin"]
      bsp -> algo  [label = "mej"]
      
      ext ->  loader [label = "png | xxx | mej"]
      ext ->  bsp [label = "bin"]
      ext ->  app [label = "mej (byte @)"]
      
      {algo gpu} -> hard  [label = ""]
   }

* Colors:
   * blue: off-board elements (tools, files).
   * green: hardware elements (memory, processor).
   * orange: on-board Graphics Engine elements.
   * gray: BSP.

* Line labels:
   * ``png``: symbolizes all standard image input formats (PNG, JPG, etc.).
   * ``xxx``: symbolizes a non-standard input format.
   * ``mej``: symbolizes the MicroEJ output format (:ref:`section_image_standard_raw`).
   * ``bin``: symbolizes a platform binary format (:ref:`section_image_binary_raw`).

Process overview:

1. The user specifies the pre-generated images to embed (see
   :ref:`section_image_generator`) and / or the images to embed as
   regular resources (see :ref:`image_runtime_decoder`).

2. The files are embedded as resources with the application. The
   files' data are linked into the FLASH memory.

3. When the application creates a MicroUI Image object, the
   Image Loader loads the image, calling the right sub Image Engine
   module (see :ref:`section_image_generator` and
   :ref:`image_runtime_decoder`) to decode the specified image.

4. When the application draws this MicroUI Image on the display
   (or on buffered image), the decoded image data is used, and no more
   decoding is required, so the decoding is done only once.

5. When the MicroUI Image is no longer needed, it must be closed explicitly by the application. The Image Engine Core asks the right sub Image Engine module (see :ref:`section_image_generator` and :ref:`image_runtime_decoder`) to free the image working area.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.