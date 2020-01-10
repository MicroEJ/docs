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
the MicroEJ application has to specify the number of identifiers (refer
to the chapter `??? <#workbenchLaunchOptions>`__ (``Target`` >
``Memory``) to have more information where specify this number of
identifiers.)

.. note::

   This number has to include the number of system fonts. A system font
   is a font file specified during the MicroUI static initialization
   step (see `??? <#section_static_init>`__).

When the limit of identifiers is reached, the MicroUI library throws an
error, and the non-loaded fonts are unusable.
