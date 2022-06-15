.. include:: aliases.rst

Android Vector Drawable Loader
==============================

The AVD Loader is an Add-on Library that can load Vector Images from Android Vector Drawable XML files, at runtime.

There are cases where it is required to load a vector image directly from its original XML description at runtime rather than loading it as an immutable resource at build-time.
For example, the image can be an external resource retrieved dynamically from a server or a filesystem. 
For those cases, the AVD Loader can parse a Vector Drawable XML file and build the corresponding vector image.

To use the AVD Loader library, add the following dependency to a :ref:`module description file <mmm_module_description>`:

.. code-block:: XML

	<dependency org="ej.library.ui" name="vectorimage-loader" rev="1.0.0"/>


.. note::

   The AVD Loader library requires MicroVG library 1.1.0 and above.



Loading a Vector Drawable
-------------------------

Here is a simple example of a Vector Drawable ``myImage.xml`` that defines a 100 x 100 image with two paths: the first one with a solid color fill, the second one with a linear gradient.

.. code-block:: XML

   <vector xmlns:aapt="http://schemas.android.com/aapt" xmlns:android="http://schemas.android.com/apk/res/android" android:height="100.0dp" android:viewportHeight="100.0" android:viewportWidth="100.0" android:width="100.0dp">
      <path android:fillColor="#FFFFFFAA" android:fillType="nonZero" android:pathData="M0,0L50,0L50,50L0,50Z " />
      <path android:fillType="nonZero" android:pathData="M50,50L100,50L100,100L50,100Z ">
         <aapt:attr name="android:fillColor">
            <gradient android:endX="100.0" android:endY="100.0" android:startX="50.0" android:startY="50.0" android:type="android:linear">
               <item android:color="#FF0000FF" android:offset="0.0" />
               <item android:color="#FFFF00FF" android:offset="1.0" />
            </gradient>
         </aapt:attr>
      </path>
   </vector>

The following code loads the Vector Drawable with the ``AvdImageLoader.loadImage()`` method, given the path to the resource. The resulting vector image can then be drawn on the display:


|startTable|

.. code-block:: java

   public static void main(String[] args) {
      MicroUI.start();
      
      Display display = Display.getDisplay();
      GraphicsContext g = display.getGraphicsContext();
      
      VectorImage image = AvdImageLoader.loadImage("/images/myImage.xml");
      VectorGraphicsPainter.drawImage(g, image, 100, 100);
      
      display.requestFlush();
   }

|midTable|
  
.. figure:: images/drawRuntimeImage.png
   :alt: Draw Vector Drawable
   :width: 400px
   :align: center

|endTable|


.. note::

   Vector Drawables that must be loaded as :ref:`Raw Resource <section.classpath.elements.resources>` are declared in ``*.resources.list`` files.

.. _section.avdloader.requirements:

Requirements
------------

Unlike the :ref:`immutable vector images <vectorimage_overview>`, which are converted at build-time using the image generator tool, the conversion from the Vector Drawable format to the platform format is done at runtime.
To limit the CPU time and memory needed for parsing and interpreting Vector Drawables in resource-constrained embedded devices, the input XML file must have been pre-processed before loading.

The pre-processing step converts the original XML into a Vector Drawable which is optimized for runtime loading.
The objective of the conversion is threefold:

* Limit the size of the XML file (e.g., minification)
* Normalize the output (e.g., use only absolute path commands in ``android:pathData``)
* Pre-process the resource-consuming operations (e.g., transformations, stroking)

To convert a Vector Drawable, run the Vector Image Converter with the following command line:

.. code-block::

   java -jar vectorimage-converter.jar --input originalImage.xml --avd myImage.xml




Limitations
-----------

The AVD Loader can only load static images (i.e., no animations). The other limitations are :ref:`the same as for immutable vector images <vectorimage_limitations>`. 



Advanced / Best Practices
-------------------------

Heap Usage
~~~~~~~~~~

The loading of a vector Drawable at runtime uses some Java heap:

* for the working buffers and intermediate objects used during the loading phase. The XML parser is optimized to stream the data and uses as few heap as possible
* for the image data



Simplify the Path Data
~~~~~~~~~~~~~~~~~~~~~~

The loading time and heap usage grow linearly with the number of path commands in the Vector Drawable. The drawing time may also be affected.
To achieve optimal performances, it is recommended to reduce the number of path commands, by "simplifying" the paths. The simplification algorithm will determine the optimal amount of anchor points to use in the artwork.
Most of the modern Graphic Design Software have an option to simplify a path (check `this article <https://helpx.adobe.com/illustrator/using/simplify_paths.html>`_ for Adobe Illustrator for example).


Monitor the Number of Path Commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To print the number of paths and path commands declared in a Vector Drawable, set the :ref:`constant <section.classpath.elements.constants>` ``ej.vectorimage.loader.debug.enabled`` to ``true``. 
This will output the numbers in the console when loading a file.

Output example:

.. code-block::

   avdimageloader INFO: Parsed a path data with a number of 5 commands
   avdimageloader INFO: Parsed a path data with a number of 5 commands
   avdimageloader INFO: Parsed a path data with a number of 28 commands
   avdimageloader INFO: Number of paths in loaded image: 3


Troubleshooting
---------------

The Image Cannot Be Parsed
~~~~~~~~~~~~~~~~~~~~~~~~~~

A error can be raised when the parsing fails:

.. code-block::

   Exception in thread "main" ej.microvg.VectorGraphicsException: MicroVG: The image cannot be parsed. The image must be a valid AVD image, converted with the platform's image generator.

This error indicates that the file is not a valid Vector Drawable converted by the Vector Image Converter. See :ref:`this section <section.avdloader.requirements>` to convert a Vector Drawable.


..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.