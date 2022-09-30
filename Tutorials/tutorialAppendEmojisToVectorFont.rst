.. _tutorial_append_emojis:

How to Add Emojis to a Vector Font
==================================

:ref:`MicroVG <section_app_microvg>` supports the drawing of multicolor fonts that use the COLR/CPAL tables to define multi-layered glyphs.
Multicolor fonts are mainly used for providing a set of colorful emojis in messaging applications.
However, emojis fonts usually do not contain many characters other than emojis, which requires applications 
to use multiple fonts to handle all use cases.

One solution to minimize the number of fonts used by an application is to add emojis to another font (i.e., combine fonts into one).
This article shows how to achieve this using FontLab, a third-party font editor.

.. note::

    FontLab is not a free software (it has a 30-days trial period).
    Tests with other tools, including free solutions, were unsuccessful in this very specific task 
    (e.g. `FontTools <https://github.com/fonttools/fonttools>`_, `FontForge <https://fontforge.org/>`_ which are great tools for font editing).


Intended Audience
-----------------

The audience for this document is Application engineers who want to
use :ref:`section_vector_fonts` in their applications.

In addition, this tutorial should be of interest to all developers
wishing to familiarize themselves with the vector features of :ref:`MicroVG <section_app_microvg>`.


Prerequisites
-------------

* Windows 10 (and higher) or MacOS 10.14 (and higher),
* An COLR/CPAL emoji font (e.g., Segoe UI Emoji),
* A target font (i.e., a TTF/OTF font to append emojis to).


Append the Emoji Glyphs
-----------------------

#. Download and install `FontLab <https://www.fontlab.com/font-editor/fontlab/>`_.
#. In FontLab, go to :guilabel:`File` > :guilabel:`Export Profiles...`.
#. Create a new Export Profile (the :guilabel:`+` button on the bottom-left).
#. Edit the new profile to match the configuration below in menu :guilabel:`Export color font files`:

    .. figure:: images/emojisProfiles.png
        :alt: New Export Profiles
        :align: center

#. Click on :guilabel:`OK` to close the :guilabel:`Export Profiles` window.
#. Open the emoji font: go to :guilabel:`File` > :guilabel:`Open Fonts...` and browse to the font file.
#. Open the target font.
#. Select a range of glyphs in the emoji font and select :guilabel:`Edit` \> :guilabel:`Copy Glyphs`:

    .. figure:: images/emojisCopy.png
        :alt: Copy Emojis
        :align: center

#. Select the target font and append the copied glyphs: go to :guilabel:`Edit` > :guilabel:`Append Glyphs`.
#. Check that the glyphs have been added to the target font:

    .. figure:: images/emojisAppend.png
        :alt: Append Emojis
        :align: center

#. To save the changes, go to :guilabel:`File` \> :guilabel:`Export Font As...`.
#. In the :guilabel:`Export Font` dialog, select the new Export Profile (with COLR/CPAL support) and :guilabel:`Destination`.

    .. figure:: images/emojisExport.png
        :alt: Export Font
        :align: center

#. Click :guilabel:`Export`.


The exported font can then be used in an application, as described in the :ref:`Application Developer Guide <section_vector_fonts>`.

.. warning::

    There are multiple ways of implementing emojis in fonts. The four main formats are 
    COLR/CPAL (Microsoft), CBDT/CBLC (Google), SVG (Adobe/Firefox) and sbix (Apple).
    Each format uses custom tables in fonts to describe the emoji glyphs. 
    MicroVG supports COLR/CPAL tables and this article only applies to this case. 
    See :ref:`this section <colored_emojis>` for more details about color emojis support with MicroVG.
