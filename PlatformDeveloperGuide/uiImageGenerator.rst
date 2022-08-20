.. _section_image_generator:

===============
Image Generator
===============

Principle
=========

The Image Generator module is an off-board tool that generates image data that is ready to be displayed without needing additional runtime memory. The two main advantages of this module are:

* A pre-generated image is already encoded in the format known by the Image Renderer (MicroEJ format) or by the platform (custom binary format). The time to create an image is very fast and does not require any RAM (Image Loader is not used).
* No extra support is needed (no runtime Image Decoder).

Functional Description
======================

.. figure:: images/static-image-gen2.*
   :alt: Image Generator Principle
   :width: 650px
   :align: center

   Image Generator Principle

Process overview (see too :ref:`section_image_core_process`)

1. The user defines, in a text file, the images to load.
2. The Image Generator outputs a binary file for each image to convert.
3. The raw files are embedded as (hidden) resources within the MicroEJ
   Application. The binary files' data are linked into the FLASH memory.
4. When the application creates a MicroUI Image object which
   targets a pre-generated image, the Image Engine has only to
   create a link from the MicroUI image object to the data in the FLASH
   memory. Therefore, the loading is very fast; only the image data from
   the FLASH memory is used: no copy of the image data is sent to the
   RAM first.
5. When the MicroUI Image is no longer needed, it is garbage-collected
   by the platform, which just deletes the useless link to the FLASH
   memory.

The image generator can run in two modes: 

* Standalone mode: the image to convert (input files) are standard (PNG, JPEG, etc.), the generated binary files are in MicroEJ format and do not depend on platform characteristics or restrictions (see :ref:`section_image_standard_raw`).
* Extended mode: the image to convert (input files) may be custom, the generated binary files can be encoded in customized MicroEJ format (can depend on several platform characteristics and restrictions, see :ref:`section_image_display_raw` and :ref:`section_image_gpu_raw`) or the generated files are encoded in another format than MicroEJ format (binary format, see :ref:`section_image_binary_raw`).

Structure
=========

The Image Generator module is constituted from several parts, the core part and services parts: 

* "Core" part: it takes an images list file as entry point and generates a binary file (no specific format) for each file. To read a file, it redirects the reading to the available service loaders. To generate a binary file, it redirects the encoding to the available service encoders. 
* "Service API" part: it provides some APIs used by the core part to load input files and to encode binary files. It also provides some APIs to customize the MicroEJ format.
* "Standard input format loader" part: this service loads standard image files (PNG, JPEG, etc.).
* "MicroEJ format generator" part: this service encodes an image in MicroEJ format.

Standalone Mode
===============

The standalone Image Generator embeds all parts described above. By consequence, once installed in a platform, the standalone image generator does not need any extended module to generate MicroEJ files from standard images files. 

.. _section_image_generator_extended:

Extended Mode
=============

To increase the capabilities of Image Generator, the extension must be built and added in the platform. As described above this extension will be able to:

* read more input image file formats,
* extend the MicroEJ format with platform characteristics,
* encode images in a third-party binary format.

To do that the Image Generator provides some services to implement. This chapter explain how to create and include this extension in the platform. Next chapters explain the aim of each service.

1. Create a ``std-javalib`` project. The module name must start with the prefix ``imageGenerator`` (for instance ``imageGeneratorMyPlatform``).
2. Add the dependency:

   :: 

      <dependency org="com.microej.pack.ui" name="ui-pack" rev="x.y.z">
         <artifact name="imageGenerator" type="jar"/>
      </dependency>

   Where ``x.y.z`` is the UI pack version used to build the platform (minimum ``13.0.0``). The ``module.ivy`` should look like:

   ::

      <ivy-module version="2.0" xmlns:ea="http://www.easyant.org" xmlns:m="http://www.easyant.org/ivy/maven" xmlns:ej="https://developer.microej.com" ej:version="2.0.0">

         <info organisation="com.microej.microui" module="imageGeneratorMyPlatform" status="integration" revision="1.0.0">      
            <ea:build organisation="com.is2t.easyant.buildtypes" module="build-std-javalib" revision="2.+"/>
         </info>
         
         <configurations defaultconfmapping="default->default;provided->provided">
            <conf name="default" visibility="public" description="Runtime dependencies to other artifacts"/>
            <conf name="provided" visibility="public" description="Compile-time dependencies to APIs provided by the platform"/>
            <conf name="documentation" visibility="public" description="Documentation related to the artifact (javadoc, PDF)"/>
            <conf name="source" visibility="public" description="Source code"/>
            <conf name="dist" visibility="public" description="Contains extra files like README.md, licenses"/>
            <conf name="test" visibility="private" description="Dependencies for test execution. It is not required for normal use of the application, and is only available for the test compilation and execution phases."/>
         </configurations>
         
         <publications/>
         
         <dependencies>
            <dependency org="com.microej.pack.ui" name="ui-pack" rev="[UI Pack version]">
               <artifact name="imageGenerator" type="jar"/>
            </dependency>
         </dependencies>
      </ivy-module>

3. Create the folder ``META-INF/services`` in source folder ``src/main/resources`` (this folder will be filled in later).
4. When a service is added (see next chapters), build the easyant project.
5. Copy the generated jar: ``target~/artifacts/imageGeneratorMyPlatform.jar`` in the platform configuration project folder: ``MyPlatform-configuration/dropins/tools/``
6. Rebuild the platform.

.. warning:: The dropins folder must be updated (and platform built again) after any changes in the image generator extension project.

.. _section_image_generator_imageio:

Service Image Loader
====================

The standalone Image Generator is not able to load all images formats, for instance SVG format. The service loader can be used to add this feature in order to generate an image file in MicroEJ format. 
There are two ways to populate the service loader: create a custom implementation of ``com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension`` or ``javax.imageio.spi.ImageReaderSpi``.

MicroUIRawImageGeneratorExtension
---------------------------------

This service allows to add a custom image reader. 

1. Open image generator extension project.
2. Create an implementation of interface ``com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension``.
3. Create the file ``META-INF/services/com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension`` and open it.
4. Note down the name of created class, with its package and classname.
5. Rebuild the image generator extension, copy it in platform configuration project (``dropins/tools/``) and rebuild the platform (see above).

.. note:: The class ``com.microej.tool.ui.generator.BufferedImageLoader`` already implements the interface. This implementation is used to load standard images. It can be sub-classed to add some behavior.

ImageReaderSpi
--------------

This extension is part of AWT `ImageIO`_.
By default, the ImageIO class only manages the standard image formats JPG, PNG, BMP and GIF.
It allows to add some image readers by adding some implementations of the service `javax.imageio.spi.ImageReaderSpi`.

Since UI Pack 13.2.0, the Image Generator automatically includes new image decoders (new ImageIO services, see the class ``com.microej.tool.ui.generator.BufferedImageLoader``), compiled in JAR files that follow this convention:

1. The JAR contains the service declaration ``/META-INF/services/javax.imageio.spi.ImageReaderSpi``,
2. The JAR filename's prefix is `imageio-`,
3. The JAR location is the platform configuration project's ``dropins/tools/`` directory.

.. note:: The same JAR is used by the Image Generator and by the :ref:`Front Panel <fp_ui_decoder>`.

.. _ImageIO: https://docs.oracle.com/javase/7/docs/api/javax/imageio/ImageIO.html

.. _section_image_custom_format:

Custom MicroEJ Format
=====================

As mentionned above (:ref:`section_image_display_raw` and :ref:`section_image_gpu_raw`), the MicroEJ format can be extended by notions specific to the platform (and often to the GPU the platform is using). The generated file stays a MicroEJ file format, usable by the Image Renderer. Additionally, the file becomes compatible with the platform constraints. 

1. Open image generator extension project.
2. Create a subclass of ``com.microej.tool.ui.generator.BufferedImageLoader`` (to be able to load standard images) or create an implementation of interface ``com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension`` (to load custom images).
3. Override method ``convertARGBColorToDisplayColor(int)`` if the platform's display pixel encoding is not standard (see :ref:`display_pixel_structure`).
4. Override method ``getStride(int)`` if a padding must be added after each line.
5. Override method ``getOptionalHeader()`` if an additional header must be added between the MicroEJ file header and pixels array. The header size is also used to align image memory address (custom header is aligned on its size).
6. Create the file ``META-INF/services/com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension`` and open it.
7. Note down the name of created class, with its package and classname.
8. Rebuild the image generator extension, copy it in platform configuration project and rebuild the platform (see above).

If the only constraint is the pixels array alignment, the Image Generator extension is not useful:

1. Open platform configuration file ``display/display.properties``.
2. Add the property ``imageBuffer.memoryAlignment``.
3. Build again the platform.

This alignment will be used by the Image Generator and also by the Image Loader.

Platform Binary Format
======================

As mentionned above (:ref:`section_image_binary_raw`), the Image Generator is able to generate a binary file compatible with platform (and not compatible with Image Renderer). This is very useful when a platform library offers the possibility to use other kinds of images than MicroUI library. The binary file can be encoded according to the options the user gives in the images list file.

1. Open image generator extension project.
2. Create an implementation of the interface ``com.microej.tool.ui.generator.ImageConverter``.
3. Create the file ``META-INF/services/com.microej.tool.ui.generator.ImageConverter`` and open it.
4. Note down the name of created class, with its package and classname.
5. Rebuild the image generator extension, copy it in platform configuration project and rebuild the platform (see above).

.. _section_image_generator_conffile:

Configuration File
==================

The Image Generator uses a configuration file (also called the "list file") for describing images that need to be processed. The list file is a text file in which each line describes an image to convert. The image is described as a resource path, and should be available from the
application classpath.

.. note::

   The list file must be specified in the application launcher (see :ref:`application_options`). However, all the files in the application classpath with suffix ``.images.list`` are automatically parsed by the Image Generator tool.

Each line can add optional parameters (separated by a ':') which define and/or describe the output file format (raw format). When no option is specified, the image is not converted and embedded as well.

.. note::

   See :ref:`image_gen_tool` to understand the list file grammar.

* MicroEJ standard output format: to encode the image in a standard MicroEJ format, specify the MicroEJ format:

   .. code-block::
      :caption: Standard Output Format Examples

      image1:ARGB8888
      image2:RGB565
      image3:A4

* MicroEJ "Display" output format: to encode the image in the same format as the display (generic display or custom display, see :ref:`display_pixel_structure`), specify ``display`` as output format:

   .. code-block::
      :caption: Display Output Format Example

      image1:display

* MicroEJ "GPU" output format: this format declaration is identical to standard format. It is a format that is also supported by the GPU.

   .. code-block::
      :caption: GPU Output Format Examples

      image1:ARGB8888
      image2:RGB565
      image3:A4

* MicroEJ RLE1 output format: to encode the image in RLE1 format, specify ``RLE1`` as output format:

   .. code-block::
      :caption: RLE1 Output Format Example

      image1:RLE1

* Without Compression: to keep original file, do not specify any format:

   .. code-block::
      :caption: Unchanged Image Example

      image1

* Binary format: to encode the image in a format only known by the platform, refer to the platform documentation to know which format are available.

   .. code-block::
      :caption: Binary Output Format Example

      image1:XXX

Linker File
===========

In addition to images binary files, the Image Generator module generates a linker file (``*.lscf``). This linker file declares an image section called ``.rodata.images``. This section follows the next rules:

* The files are always listed in same order between two application builds.
* The section is aligned on the value specified by the Display module property ``imageBuffer.memoryAlignment`` (32 bits by default).
* Each file is aligned on section alignment value.

External Resources
==================

The Image Generator manages two configuration files when the External
Resources Loader is enabled. The first configuration file lists the
images which will be stored as internal resources with the MicroEJ
Application. The second file lists the images the Image Generator must
convert and store in the External Resource Loader output directory. It
is the BSP's responsibility to load the converted images into an
external memory.


Dependencies
============

-  Image Renderer module (see :ref:`section_image_core`).

-  Display module (see :ref:`section_display`): This module gives
   the characteristics of the graphical display that are useful to configure the Image Generator.


.. _section_imagen_installation:

Installation
============

The Image Generator is an additional module for the MicroUI library.
When the MicroUI module is installed, also install this module in order
to be able to target pre-generated images.

In the platform configuration file, check :guilabel:`UI` > :guilabel:`Image Generator`
to install the Image Generator module. When checked, the properties file
``imageGenerator/imageGenerator.properties`` is required to specify the Image Generator extension project. When no extension is required (standalone mode only), this property is useless.

Use
===

The MicroUI Image APIs are available in the class
`ej.microui.display.Image`_ ant its subclasses. There are no specific APIs that use a
pre-generated image. When an image has been pre-processed, the MicroUI
Image APIs ``getImage`` and ``loadImage`` will get/load the images.

Refer to the chapter :ref:`application_options` (:guilabel:`Libraries` >
:guilabel:`MicroUI` > :guilabel:`Image`) for more information about specifying the image
configuration file.

.. _ej.microui.display.Image: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
