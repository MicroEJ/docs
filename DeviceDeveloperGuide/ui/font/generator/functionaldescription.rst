Functional Description
======================

.. figure:: font/generator/images/static-font-gen2.svg
   :alt: Font Generator Principle
   :width: 50.0%

   Font Generator Principle

Process overview:

1. The user defines, in a text file, the fonts to load.

2. The Font Generator outputs a raw file for each font to convert.

3. The raw files are embedded as (hidden) resources within the MicroEJ
   application. The raw file's data is linked into the FLASH memory.

4. When the MicroEJ application draws text on the display (or on an
   image), the font data comes directly from the FLASH memory (the font
   data is not copied to the RAM memory first).
