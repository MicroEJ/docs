

====================
Font Characteristics
====================

Font Format
===========

The Font Engine provides fonts that conform to the Unicode
Standard. The ``.ejf`` files hold font properties:

-  Identifiers: Fonts hold at least one identifier that can be one of
   the predefined Unicode scripts (see official Unicode website) or a user-specified identifier.
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
   ITALIC, or is said to be PLAIN.

-  When the selected font does not have a graphical representation of
   the required character, the first character in font is drawn instead. 

Multiple filters may apply at the same time, combining their
transformations on the displayed characters.

Pixel Transparency
==================

The Font Renderer renders the font according the the value stored for each
pixel. If the value is 0, the pixel is not rendered. If the value is the
maximum value (for example the value 3 for 2 bits-per-pixel), the pixel
is rendered using the current foreground color, completely overwriting
the current value of the destination pixel. For other values, the pixel
is rendered by blending the selected foreground color with the current
color of the destination.

If n is the number of bits-per-pixel, then the maximum value of a pixel
(pmax) is ``2^n – 1``. The value of each color component of the final pixel
is equal to:

.. math::

   foreground * pixelValue / pmax + background * (pmax - pixelValue) / pmax

Language
========

Supported Languages
-------------------

The Font Renderer manages the Unicode basic multilingual languages, whose characters are encoded on 16-bit, i.e. Unicodes from 0x0000 to 0xFFFF. It allows to render left-to-right or right-to-left writing systems: Latin (English, etc.), Arabic, Chinese, etc. are some supported languages. Note that the rendering is always performed left-to-right, even if the string are written right-to-left. There is no support for top-to-bottom writing systems. Some languages require diacritics and contextual letters; the Font Renderer manages simple rules in order to combine several characters.

Arabic Support
--------------

The Font Renderer manages the ARABIC font specificities: the diacritics and contextual letters. 

To render an Arabic text, the Font Renderer requires several points:

-  To determinate if a character has to overlap the previous character,
   the Font Renderer uses a specific range of ARABIC characters: from
   ``0xfe70`` to ``0xfefc``. All other characters (ARABIC or not)
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
   Font Renderer will first render the character '``\ufee2``', then
   '``\ufedc``,' and so on.

-  Each character in the font (in the ``ejf`` file) must have a
   rendering compatible with the character position. The character will
   be rendered by the Font Renderer as-is. No support is performed by the
   Font Renderer to obtain a *linear* text.