.. include:: aliases.rst

How to Add Colored Emojis to a Vector Font
==========================================

MicroVG supports the drawing of multicolor fonts that use the COLR/CPAL tables to define multilayered glyphs.
Multicolor fonts are mainly used for providing a set of colorful emojis in messaging applications.
However, emojis fonts usually do not contain many characters other than emojis, which requires applications 
to use multiple fonts to handle all use cases.

One solution to minimize the number of fonts used by the application is to add emojis to another font.
This article shows how to do it using FontLab, a third-party font editor.

.. note::

    FontLab is not free software (it has a 30-days trial period).
    Tests with other tools, including free solutions, were unsuccessful in this very specific task (e.g. `FontTools <https://github.com/fonttools/fonttools>`_, `FontForge <https://fontforge.org/>`_)


#. Download and install `FontLab <https://www.fontlab.com/font-editor/fontlab/>`_.
#. In FontLab, go to :guilabel:`File` > :guilabel:`Export Profiles...`.
#. Create a new Export Profile (the :guilabel:`+` button on the bottom-left).
#. Edit the new profile to match the configuration below in menu :guilabel:`Export color font files`:

    .. figure:: images/emojisProfiles.png
        :alt: New Export Profiles
        :align: center

#. Click on :guilabel:`Ok` to close the :guilabel:`Export Profiles` window.
#. Open the emojis font: go to :guilabel:`File` > :guilabel:`Open Fonts...` and browse to the font file.
#. Open the target font.
#. Select a range of glyphs in the emojis font and select :guilabel:`Edit` \> :guilabel:`Copy Glyphs`.
#. Append the copied glyphs in the target font (:guilabel:`Append Glyphs`).
#. Check that the glyphs have been added to the target font, then go to `File` \> `Export Font As...`.
#. In the :guilabel:`Export Font` dialog, select the new Export Profile (with COLR/CPAL support) and Destination.
#. Click :guilabel:`Export`.


