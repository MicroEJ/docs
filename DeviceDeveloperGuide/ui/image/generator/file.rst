Configuration File
==================

The Image Generator uses a configuration file (also called the "list
file") for describing images that need to be processed. The list file is
a text file in which each line describes an image to convert. The image
is described as a resource path, and should be available from the
application classpath.

.. note::

   The list file must be specified in the MicroEJ application launcher
   (see `??? <#workbenchLaunchOptions>`__). However, all files in
   application classpath with suffix ``.images.list`` are automatically
   parsed by the Image Generator tool.

Each line can add optional parameters (separated by a ':') which define
and/or describe the output file format (raw format). When no option is
specified, the image is converted into the default format.

.. note::

   See `??? <#image_gen_tool>`__ to understand the list file grammar.

Below is an example of a list file for the Image Generator:

::

   image1
   image2:RGB565

The next chapters describe the available output formats.
