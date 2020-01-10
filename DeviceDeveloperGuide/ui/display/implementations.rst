.. _section_display_implementation:

Implementations
===============

The implementation of the MicroUI ``Display`` API targets a generic
display (see `??? <#section_display_modes>`__): Switch, Copy and Direct.
It provides some low level API. The BSP has to implement these LLAPI,
making the link between the MicroUI C library ``display`` and the BSP
display driver. The LLAPI to implement are listed in the header file
``LLDISPLAY_impl.h``.

When there is no display on the board, a *stub* implementation of C
library is available. This C library must be linked by the third-party C
IDE when MicroUI module is installed in the MicroEJ platform.
