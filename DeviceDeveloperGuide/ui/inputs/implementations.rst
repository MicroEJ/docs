.. _section_inputs_implementation:

Implementation
==============

The implementation of the MicroUI ``Event Generator`` APIs provides some
low level APIs. The BSP has to implement these LLAPI, making the link
between the MicroUI C library ``inputs`` and the BSP input devices
drivers.

The LLAPI to implement are listed in the header file ``LLINPUT_impl.h``.
It allows events to be sent to the MicroUI implementation. The input
drivers are allowed to add events directly using the event generator's
unique ID (see `??? <#section_static_init>`__). The drivers are fully
dependent on the MicroEJ framework (a driver cannot be developed without
MicroEJ because it uses the header file generated during the MicroUI
initialization step).

When there is no input device on the board, a *stub* implementation of C
library is available. This C library must be linked by the third-party C
IDE when the MicroUI module is installed in the MicroEJ platform.
