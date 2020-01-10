Principle
=========

The LEDs module contains the C part of the MicroUI implementation which
manages LED devices. This module is composed of two elements:

-  the C part of the MicroUI LEDs API (a built-in C archive),

-  an implementation of a low level API for the LEDs (LLLEDS) which must
   be provided by the BSP (see `??? <#LLLEDS-API-SECTION>`__).
