Font Engine
===========

Font Format
-----------

The font engine module provides fonts that conform to the Unicode
Standard [U61]. ``The .ejf`` files hold font properties:

-  Identifiers: Fonts hold at least one identifier that can be one of
   the predefined Unicode scripts [U61] or a user-specified identifier.
   The intention is that an identifier indicates that the font contains
   a specific set of character codes, but this is not enforced.

-  Font height and width, in pixels. A font has a fixed height. This
   height includes the white pixels at the top and bottom of each
   character, simulating line spacing in paragraphs. A monospace font is
   a font where all characters have the same width; for example, a '!'
   representation has the same width as a 'w'. In a proportional font,
   'w' will be wider than a '!'. No width is specified for a
   proportional font.

   .. figure:: ui/font/core/images/font-height.svg
      :alt: Font Height
      :height: 2cm

      Font Height

-  Baseline, in pixels. All characters have the same baseline, which is
   an imaginary line on top of which the characters seem to stand.
   Characters can be partly under the line, for example 'g' or '}'. The
   number of pixels specified is the number of pixels above the
   baseline.

   .. figure:: ui/font/core/images/font-baseline.svg
      :alt: Font baseline
      :height: 2cm

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

   .. figure:: ui/font/core/images/font-default-char.svg
      :alt: Default Character
      :height: 2cm

      Default Character

Font Selection
--------------

The font engine implements the [MUI] selection semantics, and also tries
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

   +------------+-------------------------------+-------------------------+
   | Name       | Description                   | Rendering sample        |
   +============+===============================+=========================+
   | ITALIC     | Pixels on upper rows are      |                         |
   |            | shifted right. The higher a   |                         |
   |            | pixel is relative to the base |                         |
   |            | line, the more it is          |                         |
   |            | right-shifted.                |                         |
   +------------+-------------------------------+-------------------------+
   | BOLD       | 1 pixel is added to the right |                         |
   |            | of each original pixel.       |                         |
   +------------+-------------------------------+-------------------------+
   | UNDERLINED | A line is displayed two       |                         |
   |            | pixels below the baseline     |                         |
   |            | position.                     |                         |
   +------------+-------------------------------+-------------------------+

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

foreground \* pixelValue / pmax + background \* (pmax - pixelValue) /
pmax + adjustment

where adjustment is an adjustment factor specified in the board support
package of the platform.
