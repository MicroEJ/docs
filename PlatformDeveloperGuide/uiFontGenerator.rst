.. _section_fontgen:

==============
Font Generator
==============


Principle
=========

The Font Generator module is an off-board tool that generates fonts
ready to be displayed without the need for additional runtime memory. It
outputs a raw file for each converted font.


Functional Description
======================

.. figure:: images/static-font-gen2.*
   :alt: Font Generator Principle
   :width: 450px
   :align: center

   Font Generator Principle

Process overview:

1. The user defines, in a text file, the fonts to load.

2. The Font Generator outputs a raw file for each font to convert.

3. The raw files are embedded as (hidden) resources within the MicroEJ
   Application. The raw file's data is linked into the FLASH memory.

4. When the application draws text on the display (or on an
   image), the font data comes directly from the FLASH memory (the font
   data is not copied to the RAM memory first).


Pixel Transparency
==================

As mentioned above, each pixel of each character in an ``.ejf`` file has
one of 256 different gray-scale values. However RAW files can have 1, 2,
4 or 8 bits-per-pixel (respectively 2, 4, 16 or 256 gray-scale values).
The required pixel depth is defined in the configuration file (see next
chapter). The Font Generator compresses the input pixels to the required
depth.

The following tables illustrates the conversion "grayscale to
transparency level". The grayscale value '0x00' is black whereas value
'0xff' is white. The transparency level '0x0' is fully transparent
whereas level '0x1' (bpp == 1), '0x3' (bpp == 2) or '0xf' (bpp == 4) is
fully opaque.

.. table:: Font 1-BPP RAW Conversion

   +-----------------------------------+-----------------------------------+
   | Grayscale Ranges                  | Transparency Levels               |
   +===================================+===================================+
   | 0x00 to 0x7f                      | 0x1                               |
   +-----------------------------------+-----------------------------------+
   | 0x80 to 0xff                      | 0x0                               |
   +-----------------------------------+-----------------------------------+

.. table:: Font 2-BPP RAW Conversion

   +-----------------------------------+-----------------------------------+
   | Grayscale Ranges                  | Transparency Levels               |
   +===================================+===================================+
   | 0x00 to 0x1f                      | 0x3                               |
   +-----------------------------------+-----------------------------------+
   | 0x20 to 0x7f                      | 0x2                               |
   +-----------------------------------+-----------------------------------+
   | 0x80 to 0xdf                      | 0x1                               |
   +-----------------------------------+-----------------------------------+
   | 0xe0 to 0xff                      | 0x0                               |
   +-----------------------------------+-----------------------------------+

.. table:: Font 4-BPP RAW Conversion

   +-----------------------------------+-----------------------------------+
   | Grayscale Ranges                  | Transparency Levels               |
   +===================================+===================================+
   | 0x00 to 0x07                      | 0xf                               |
   +-----------------------------------+-----------------------------------+
   | 0x08 to 0x18                      | 0xe                               |
   +-----------------------------------+-----------------------------------+
   | 0x19 to 0x29                      | 0xd                               |
   +-----------------------------------+-----------------------------------+
   | 0x2a to 0x3a                      | 0xc                               |
   +-----------------------------------+-----------------------------------+
   | 0x3b to 0x4b                      | 0xb                               |
   +-----------------------------------+-----------------------------------+
   | 0x4c to 0x5c                      | 0xa                               |
   +-----------------------------------+-----------------------------------+
   | 0x5d to 0x6d                      | 0x9                               |
   +-----------------------------------+-----------------------------------+
   | 0x6e to 0x7e                      | 0x8                               |
   +-----------------------------------+-----------------------------------+
   | 0x7f to 0x8f                      | 0x7                               |
   +-----------------------------------+-----------------------------------+
   | 0x90 to 0xa0                      | 0x6                               |
   +-----------------------------------+-----------------------------------+
   | 0xa1 to 0xb1                      | 0x5                               |
   +-----------------------------------+-----------------------------------+
   | 0xb2 to 0xc2                      | 0x4                               |
   +-----------------------------------+-----------------------------------+
   | 0xc3 to 0xd3                      | 0x3                               |
   +-----------------------------------+-----------------------------------+
   | 0xd4 to 0xe4                      | 0x2                               |
   +-----------------------------------+-----------------------------------+
   | 0xe5 to 0xf5                      | 0x1                               |
   +-----------------------------------+-----------------------------------+
   | 0xf6 to 0xff                      | 0x0                               |
   +-----------------------------------+-----------------------------------+

For 8-BPP RAW font, a transparency level is equal to
``255 - grayscale value``.

.. _section_fontgen_conffile:

Configuration File
==================

The Font Generator uses a configuration file (called the "list file")
for describing fonts that must be processed. The list file is a basic
text file where each line describes a font to convert. The font file is
described as a resource path, and should be available from the
application classpath.

.. note::

   The list file must be specified in the application launcher
   (see :ref:`application_options`). However, all files in
   application classpath with suffix ``.fonts.list`` are automatically
   parsed by the Font Generator tool.

Each line can have optional parameters (separated by a ':') which define
some ranges of characters to embed in the final raw file, and the
required pixel depth. By default, all characters available in the input
font file are embedded, and the pixel depth is 1 (i.e 1 bit-per-pixel).

.. note::

   See :ref:`fonts_list_grammar` to understand the list file grammar.

Selecting only a specific set of characters to embed reduces the memory
footprint. There are two ways to specify a character range: the custom
range and the known range. Several ranges can be specified, separated by
";".

Below is an example of a list file for the Font Generator:

.. code-block::
   :caption: Fonts Configuration File Example

   myfont
   myfont1:latin
   myfont2:latin:8
   myfont3::4


External Resources
==================

The Font Generator manages two configuration files when the External
Resources Loader is enabled. The first configuration file lists the
fonts which will be stored as internal resources with the MicroEJ
Application. The second file lists the fonts the Font Generator must
convert and store in the External Resource Loader output directory. It
is the BSP's responsibility to load the converted fonts into an external
memory.


Dependencies
============

-  Font Renderer module (see :ref:`section_font_core`)


Installation
============

The Font Generator module is an additional tool for MicroUI library.
When the MicroUI module is installed, install this module in order to be
able to embed some additional fonts with the application.

If the module is not installed, the platform user will not be able to
embed a new font with his/her application. He/she will be only
able to use the system fonts specified during the MicroUI initialization
step (see :ref:`section_static_init`).

In the platform configuration file, check :guilabel:`UI` > :guilabel:`Font Generator` to
install the Font Generator module.


Use
===

In order to be able to embed ready-to-be-displayed fonts, you must
activate the fonts conversion feature and specify the fonts
configuration file.

Refer to the chapter :ref:`application_options` (:guilabel:`Libraries` >
:guilabel:`MicroUI` > :guilabel:`Font`) for more information about specifying the fonts
configuration file.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
