.. _display_hard_accelerator:

Hardware Accelerator
====================

Overview
--------

The display module allows to use an hardware accelerator to perform some
drawings: fill a rectangle, draw an image, rotate an image etc. Some
optional functions are available in ``LLDISPLAY_EXTRA.h`` file (see
`??? <#LLDISPLAY-EXTRA-API-SECTION>`__). These functions are not
automatically call by the display module. The display module must be
configured during the MicroEJ platform construction specifying which
hardware accelerator to use. It uses the property
``hardwareAccelerator`` in
``MODULE.DISPLAY.NAME/MODULE.DISPLAY.NAME.properties`` file to select a
hardware accelerator (see `??? <#section_display_installation>`__).

The following table lists the available hardware accelerators supported
by MicroEJ, their full names, short names (used in the next tables) and
the ``hardwareAccelerator`` property value (see
`??? <#section_display_installation>`__).

.. table:: Hardware Accelerators

   +------------------------------------------+-------------+-------------+
   |                                          | Short name  | Property    |
   +==========================================+=============+=============+
   | Renesas Graphics Library RGA  [1]_       | RGA         | rga         |
   +------------------------------------------+-------------+-------------+
   | Renesas TES Dave/2d                      | Dave2D      | dave2d      |
   +------------------------------------------+-------------+-------------+
   | STMicroelectronics Chrom-ART Graphics    | DMA2D       | dma2d       |
   | Accelerator                              |             |             |
   +------------------------------------------+-------------+-------------+
   | Custom Hardware Accelerator              | Custom      | custom      |
   |                                          |             |  [2]_       |
   +------------------------------------------+-------------+-------------+

.. note::

   It is possible to target an hardware accelerator which is not
   supported by MicroEJ yet. Set the property ``hardwareAccelerator`` to
   ``custom`` to force display module to call all drawing functions
   which can be accelerated. The LLDISPLAY implementation is able or not
   to implement a function. If not, the software algorithm will be used.

The available list of supported hardware accelerators is MicroEJ
architecture dependent. For instance, the STMicroelectronics Chrom-ART
Graphics Accelerator is only available for the MicroEJ architecture for
Cortex-M4 and Cortex-M7. The Renesas Graphics Library RGA is only
available for the MicroEJ architecture for Cortex-A9. The following
table shows in which MicroEJ architecture an hardware accelerator is
available.

.. table:: Hardware Accelerators according MicroEJ Architectures

   +-----------------------------+---------+---------+---------+---------+
   |                             | RGA     | Dave2D  | DMA2D   | Custom  |
   +=============================+=========+=========+=========+=========+
   | FLOPI0PI28.PRINTABLENAME    | FLOPI0P | FLO     | FL      | FLO     |
   |                             | I28.RGA | PI0PI28 | OPI0PI2 | PI0PI28 |
   |                             |         | .DAVE2D | 8.DMA2D | .CUSTOM |
   +-----------------------------+---------+---------+---------+---------+
   | FLOPI4A20.PRINTABLENAME     | FLOPI4  | FL      | F       | FL      |
   |                             | A20.RGA | OPI4A20 | LOPI4A2 | OPI4A20 |
   |                             |         | .DAVE2D | 0.DMA2D | .CUSTOM |
   +-----------------------------+---------+---------+---------+---------+
   | FLOPI4G25.PRINTABLENAME     | FLOPI4  | FL      | F       | FL      |
   |                             | G25.RGA | OPI4G25 | LOPI4G2 | OPI4G25 |
   |                             |         | .DAVE2D | 5.DMA2D | .CUSTOM |
   +-----------------------------+---------+---------+---------+---------+
   | FLOPI4I30.PRINTABLENAME     | FLOPI4  | FL      | F       | FL      |
   |                             | I30.RGA | OPI4I30 | LOPI4I3 | OPI4I30 |
   |                             |         | .DAVE2D | 0.DMA2D | .CUSTOM |
   +-----------------------------+---------+---------+---------+---------+
   | FLOPI7A21.PRINTABLENAME     | FLOPI7  | FL      | F       | FL      |
   |                             | A21.RGA | OPI7A21 | LOPI7A2 | OPI7A21 |
   |                             |         | .DAVE2D | 1.DMA2D | .CUSTOM |
   +-----------------------------+---------+---------+---------+---------+

.. note::

   Some hardware accelerators may not be available in off-the-self
   architectures . However they are available on some specific
   architectures. Please consult the engineering services page on
   MicroEJ website.

All hardware accelerators are not available for each number of
bits-per-pixel configuration. The following table illustrates in which
display stack according ``bpp``, an hardware accelerator can be used.

.. table:: Hardware Accelerators according BPP

   +-----------------------------+---------+---------+---------+---------+
   |                             | RGA     | Dave2D  | DMA2D   | Custom  |
   +=============================+=========+=========+=========+=========+
   | 1 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | C1                          |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 2 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | C2                          |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 4 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | C4                          |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 8 BPP                       |         |         |         |         |
   +-----------------------------+---------+---------+---------+---------+
   | 16 BPP                      |         |         |         | •       |
   +-----------------------------+---------+---------+---------+---------+
   | RGB565                      | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | ARGB1555                    | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | ARGB4444                    | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | 24 BPP                      |         |         |         | •       |
   +-----------------------------+---------+---------+---------+---------+
   | RGB888                      |         |         | •       | •       |
   +-----------------------------+---------+---------+---------+---------+
   | 32 BPP                      |         |         |         | •       |
   +-----------------------------+---------+---------+---------+---------+
   | ARGB8888                    | •       | •       | •       | •       |
   +-----------------------------+---------+---------+---------+---------+

Features and Limits
-------------------

Each hardware accelerator has a list of features (list of drawings the
hardware accelerator can perform) and some constraints. When the display
module is configured to use an hardware accelerator, it takes in
consideration these features and limits. If a drawing is detected by the
display module as a drawing to be hardware accelerated, the LLDISPLAY
implementation *must* configure and use the hardware accelerator to
perform the full drawing (not just a part of drawing).

.. note::

   The *custom* hardware generator does not have any limit by default.
   This is the LLDISPLAY implementation which fixes the limits.

The following table lists the algorithms accelerated by each hardware
accelerator.

.. table:: Hardware Accelerators Algorithms

   +-----------------------------------+-----------+-----------+-----------+
   |                                   | RGA       | Dave2D    | DMA2D     |
   +===================================+===========+===========+===========+
   | Fill a rectangle                  | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | Draw an image                     | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | Scale an image                    | •         |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | Rotate an image                   | •         |           |           |
   +-----------------------------------+-----------+-----------+-----------+

Images
------

The available list of supported image formats is not the same for all
hardware accelerators. Furthermore some hardware accelerators require a
custom header before the RAW pixel data, require a padding between each
line etc.. MicroEJ manages these contraints for supported hardware
accelerators. For *custom* hardware accelerator, no image header can be
added and no padding can be set.

The following table illustratres the RAW image formats supported by each
hardware accelerator.

.. table:: Hardware Accelerators RAW Image Formats

   +-----------------------------------+-----------+-----------+-----------+
   |                                   | RGA       | Dave2D    | DMA2D     |
   +===================================+===========+===========+===========+
   | A1                                | •  [3]_   |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | A2                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | A4                                | •  [4]_   |           | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | A8                                | •  [5]_   |           | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | C1                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | C2                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | C4                                |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | AC11                              |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | AC22                              |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | AC44                              |           |           |           |
   +-----------------------------------+-----------+-----------+-----------+
   | RGB565                            | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | ARGB1555                          | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | ARGB4444                          | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | RGB888                            |           |           | •         |
   +-----------------------------------+-----------+-----------+-----------+
   | ARGB8888                          | •         | •         | •         |
   +-----------------------------------+-----------+-----------+-----------+

The RAW image given as parameter (in input and/or in output) respects
the hardware accelerator specification. For instance a RAW image with
4BPP must be often aligned on 8 bits, even if its size is odd. The RAW
image size given as parameter is the *software* size. That means it is
the size of the original image.

Example for a A4 image with required alignment on 8 bits:

-  Original image width in pixels (== width in MicroEJ application): 47

-  Hardware image width in pixels (== line width in pixels in RAW image
   data): 48

-  Width in pixels available in ``LLDISPLAY``
   (``((LLDISPLAY_SImage*)src)->width``): 48

-  Hardware width in bytes (== line width in bytes in RAW image data):
   48 / 2 = 24

The hardware size may be higher than the software size (like in the
example). However the number of pixels to draw
(``((LLDISPLAY_SDrawImage*)drawing)->src_width``) is *always* smaller or
equal to the software area size. That means the display module never
asks to draw the pixels which are outside the software area. The
hardware size is only useful to be compatible with the hardware
accelerator restrictions about memory alignment.

.. [1]
   hardware or software implementation

.. [2]
   see next note

.. [3]
   maximum size <= display width

.. [4]
   maximum size <= display width

.. [5]
   maximum size <= display width
