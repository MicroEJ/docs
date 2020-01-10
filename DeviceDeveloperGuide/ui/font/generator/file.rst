Configuration File
==================

The Font Generator uses a configuration file (called the "list file")
for describing fonts that must be processed. The list file is a basic
text file where each line describes a font to convert. The font file is
described as a resource path, and should be available from the
application classpath.

.. note::

   The list file must be specified in the MicroEJ application launcher
   (see `??? <#workbenchLaunchOptions>`__). However, all files in
   application classpath with suffix ``.fonts.list`` are automatically
   parsed by the Font Generator tool.

Each line can have optional parameters (separated by a ':') which define
some ranges of characters to embed in the final raw file, and the
required pixel depth. By default, all characters available in the input
font file are embedded, and the pixel depth is 1 (i.e 1 bit-per-pixel).

.. note::

   See `??? <#font_gen_tool>`__ to understand the list file grammar.

Selecting only a specific set of characters to embed reduces the memory
footprint. There are two ways to specify a character range: the custom
range and the known range. Several ranges can be specified, separated by
";" .

Below is an example of a list file for the Font Generator:

::

   myfont
   myfont1:latin
   myfont2:latin:8
   myfont3::4
