Color Utilities
===============

The widget library offers some color utilities.

The `ColorHelper`_ is helpful for decomposing colors into components (alpha, red, blue, green) and building back a color from components.

The `GradientHelper`_ can blend two colors and create a gradient from two colors.

The resulting gradient is a list of distinct colors from the start color to the end color.
The colors are truncated to the display color depth.
As a consequence, for the same start and end colors, a gradient created for a 32-bit display will contain more colors than on a 16-bit display.

The `LightHelper`_ proposes several primitives concerning the luminance of the colors.
The luminance of a color is computed from the luminance and the quantity of each of its components.
The green being the brighter, then the red and finally the blue.

.. _ColorHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/color/ColorHelper.html
.. _GradientHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/color/GradientHelper.html
.. _LightHelper: https://repository.microej.com/javadoc/microej_5.x/apis/ej/widget/color/LightHelper.html

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
