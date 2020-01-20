.. _section_font_core_process:

Functional Description
======================

.. figure:: font/core/images/font-process2.svg
   :alt: Font Generation
   :width: 80.0%

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
   application. The raw files' data are linked into the FLASH memory.

6. When the MicroEJ application creates a MicroUI DisplayFont object
   which targets a pre-generated image, the Font Engine Core only has to
   link from the MicroUI DisplayFont object to the data in the FLASH
   memory. Therefore, the loading is very fast; only the font data from
   the FLASH memory is used: no copy of the image data is sent to RAM
   memory first.

7. When the MicroUI DisplayFont is no longer needed, it is
   garbage-collected by the platform, which just deletes the useless
   link to the FLASH memory.
