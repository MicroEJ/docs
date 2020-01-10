.. _mjvm_javalibs:

Foundation Libraries
====================

Embedded Device Configuration (EDC)
-----------------------------------

The Embedded Device Configuration specification defines the minimal
standard runtime environment for embedded devices. It defines all
default API packages:

-  java.io

-  java.lang

-  java.lang.annotation

-  java.lang.ref

-  java.lang.reflect

-  java.util

Beyond Profile (B-ON)
---------------------

B-ON defines a suitable and flexible way to fully control both memory
usage and start-up sequences on devices with limited memory resources.
It does so within the boundaries of Java semantics. More precisely, it
allows:

-  Controlling the initialization sequence in a deterministic way.

-  Defining persistent, immutable, read-only objects (that may be placed
   into non-volatile memory areas), and which do not require copies to
   be made in RAM to be manipulated.

-  Defining immortal, read-write objects that are always alive.
