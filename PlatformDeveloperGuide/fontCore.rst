.. _section_font_core:

================
Font Engine Core
================


Principle
=========

The Font Engine Core module is a built-in module of the MicroUI module
(see :ref:`section_microui`) for the application side; and is a
built=in module of the Display module (see :ref:`section_display`)
for the C side.


.. _section_font_core_process:

Functional Description
======================

.. figure:: images/font-process2.*
   :alt: Font Generation
   :width: 80.0%
   :align: center

   Font Generation

Process overview:

1. User uses the Font Designer module to create a new font, and imports
   characters from system fonts (``*.ttf`` files) and / or user images
   (``*.png``, ``*.jpg``, ``*.bmp``, etc.).

2. Font Designer module saves the font as a MicroEJ Font (``*.ejf``
   file).

3. The user defines, in a text file, the fonts to load.

4. The Font Generator outputs a raw file for each font to convert (the
   raw format is display device-dependent).

5. The raw files are embedded as (hidden) resources within the MicroEJ
   Application. The raw files' data are linked into the FLASH memory.

6. When the MicroEJ Application creates a MicroUI DisplayFont object
   which targets a pre-generated image, the Font Engine Core only has to
   link from the MicroUI DisplayFont object to the data in the FLASH
   memory. Therefore, the loading is very fast; only the font data from
   the FLASH memory is used: no copy of the image data is sent to RAM
   memory first.

7. When the MicroUI DisplayFont is no longer needed, it is
   garbage-collected by the platform, which just deletes the useless
   link to the FLASH memory.


Font Engine
===========

Font Format
-----------

The font engine module provides fonts that conform to the `Unicode
Standard <https://unicode.org/standard/standard.html>`_. The ``.ejf`` files hold font properties:

-  Identifiers: Fonts hold at least one identifier that can be one of
   the `predefined Unicode scripts <https://unicode.org/standard/standard.html>`_ or a user-specified identifier.
   The intention is that an identifier indicates that the font contains
   a specific set of character codes, but this is not enforced.

-  Font height and width, in pixels. A font has a fixed height. This
   height includes the white pixels at the top and bottom of each
   character, simulating line spacing in paragraphs. A monospace font is
   a font where all characters have the same width; for example, a '!'
   representation has the same width as a 'w'. In a proportional font,
   'w' will be wider than a '!'. No width is specified for a
   proportional font.

   .. figure:: images/font-height.*
      :alt: Font Height
      :height: 2cm
      :align: center

      Font Height

-  Baseline, in pixels. All characters have the same baseline, which is
   an imaginary line on top of which the characters seem to stand.
   Characters can be partly under the line, for example 'g' or '}'. The
   number of pixels specified is the number of pixels above the
   baseline.

   .. figure:: images/font-baseline.*
      :alt: Font baseline
      :height: 2cm
      :align: center

      Font baseline

-  Space character size, in pixels. For proportional fonts, the Space
   character (``0x20``) is a specific character because it has no filled
   pixels, and so its width must be specified. For monospace, the space
   size is equal to the font width (and hence the same as all other
   characters).

-  Styles: A font holds either a combination of these styles: BOLD,
   ITALIC, UNDERLINED, or is said to be PLAIN.

-  Runtime filters: Some fonts may allow the font engine to apply a
   transformation (in other words, a filter) on characters before they
   are displayed in order to provide some visual effect on characters
   (BOLD, ITALIC, UNDERLINED). Unless specified, a font allows the font
   engine to apply any of its filters.

-  When the selected font does not have a graphical representation of
   the required character, a rectangle is displayed instead. For
   proportional fonts, the width is one third of the height of the font.

   .. figure:: images/font-default-char.*
      :alt: Default Character
      :height: 2cm
      :align: center

      Default Character

Font Selection
--------------

The font engine implements the :ref:`[MUI] selection semantics <esr-specifications>`, and also tries
to select fonts for which styles are built in, instead of applying a
runtime filter. The font is selected based on the following process:

1. Select fonts that define the specified identifier.

2. Select within the step1 fonts, those whose height is the closest to
   the specified height.

3. Select within the step2 fonts, those with built-in styles that match
   the specified styles.

4. If more than one font is selected by the steps above, select those
   fonts that have the most built-in styles. If there is still more than
   one font, one is selected arbitrarily.

Runtime Transformation: Filters
-------------------------------

The user interface extension font engine provides three runtime filters
that may apply if the (currently selected) font allows it. The filters
are:

.. table:: The Three Font Runtime Style Transformations (filters).

   +------------+-------------------------------+---------------------------------------------+
   | Name       | Description                   | Rendering sample                            |
   +============+===============================+=============================================+
   | ITALIC     | Pixels on upper rows are      | .. image:: images/font-filter-italic.*      |
   |            | shifted right. The higher a   |                                             |
   |            | pixel is relative to the base |                                             |
   |            | line, the more it is          |                                             |
   |            | right-shifted.                |                                             |
   +------------+-------------------------------+---------------------------------------------+
   | BOLD       | 1 pixel is added to the right | .. image:: images/font-filter-bold.*        |
   |            | of each original pixel.       |                                             |
   +------------+-------------------------------+---------------------------------------------+
   | UNDERLINED | A line is displayed two       | .. image:: images/font-filter-underline.*   |
   |            | pixels below the baseline     |                                             |
   |            | position.                     |                                             |
   +------------+-------------------------------+---------------------------------------------+

Multiple filters may apply at the same time, combining their
transformations on the displayed characters.

Pixel Transparency
------------------

The font engine renders the font according the the value stored for each
pixel. If the value is 0, the pixel is not rendered. If the value is the
maximum value (for example the value 3 for 2 bits-per-pixel), the pixel
is rendered using the current foreground color, completely overwriting
the current value of the destination pixel. For other values, the pixel
is rendered by blending the selected foreground color with the current
color of the destination.

If n is the number of bits-per-pixel, then the maximum value of a pixel
(pmax) is 2^n – 1. The value of each color component of the final pixel
is equal to:

``foreground \* pixelValue / pmax + background \* (pmax - pixelValue) /
pmax + adjustment``

where adjustment is an adjustment factor specified in the board support
package of the platform.


Font Identifier
===============

All fonts are loaded at MicroUI startup. Before loading a font, the
Image Engine Core module first tries to attribute a unique identifier to
the future loaded font. This identifier will be used to retrieve the
font after the loading step, in order to draw it and to free it.

An identifier targets a font file (an ejf raw file), which can contain
until eight DisplayFont inside. To prevent some C allocation at runtime,
the number of identifiers is allocated at compile-time. By consequence,
the available number of identifiers is limited. The MicroEJ launcher of
the MicroEJ Application has to specify the number of identifiers (refer
to the chapter :ref:`workbenchLaunchOptions` (``Target`` >
``Memory``) to have more information where specify this number of
identifiers.)

.. note::

   This number has to include the number of system fonts. A system font
   is a font file specified during the MicroUI static initialization
   step (see :ref:`section_static_init`).

When the limit of identifiers is reached, the MicroUI library throws an
error, and the non-loaded fonts are unusable.


Arabic Support
==============

The font engine manages the ARABIC font specificities: the diacritics
and contextual letters. Contrary to the LATIN fonts, some ARABIC
characters can overlap another character. When a character must overlap
the previous character in the text, the font engine repositions the X
coordinate before rendering the new character (instead of placing the
next character just after the previous one).

To render an Arabic text, the font engine requires several points:

-  To determinate if a character has to overlap the previous character,
   the font engine uses a specific range of ARABIC characters: from
   ``0xfe70`` to ``0xfefc``. All others characters (ARABIC or not)
   outside this range are considered *classic* and no overlap is
   performed. Note that several ARABIC characters are available outside
   this range, but the same characters (same representation) are
   available inside this range.

-  The application strings must use the UTF-8 encoding. Furthermore, in
   order to force the use of characters in the range ``0xfe70`` to
   ``0xfefc``, the string must be filled with the following syntax:
   '``\ufee2\ufedc\ufe91\u0020\ufe8e\ufe92\ufea3\ufeae\ufee3``'; where
   ``\uxxxx`` is the UTF-8 character encoding.

-  The application string and its rendering are always performed from
   left to right. However the string contents are managed by the
   application itself, and so can be filled from right to left. To write
   the text: 

   .. image:: images/arabic.png
      :width: 120px

   the string characters must be :
   '``\ufee2\ufedc\ufe91\u0020\ufe8e\ufe92\ufea3\ufeae\ufee3``'. The
   font engine will first render the character '``\ufee2``', then
   '``\ufedc``,' and so on.

-  Each character in the font (in the ``ejf`` file) must have a
   rendering compatible with the character position. The character will
   be rendered by the font engine as-is. No support is performed by the
   font engine to obtain a *linear* text.


External Resources
==================

The Font Engine Core is able to load some fonts located outside the CPU
addresses' space range. It uses the External Resource Loader.

When a font is located in such memory, the Font Engine Core copies a
very short part of the resource (the font file) into a RAM memory (into
CPU addresses space range): the font header. This header stays located
in RAM during the full MicroEJ Application time. Then, on MicroEJ
Application demand, the Font Engine Core loads some extra information
from the font into the RAM memory (the font meta data, the font pixels,
etc.). This extra information is automatically unloaded from RAM when
the Font Engine Core no longer needs them.


Dependencies
============

-  MicroUI module (see :ref:`section_microui`)

-  Display module (see :ref:`section_display`)


Installation
============

The Font Engine Core modules are part of the MicroUI module and Display
module. You must install them in order to be able to use some fonts.


Use
===

The MicroUI font APIs are available in the class
``ej.microui.display.Font``.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
