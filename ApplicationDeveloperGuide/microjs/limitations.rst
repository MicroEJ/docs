..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _microjs.limitations:

Limitations
===========

Syntaxes
********

The following syntaxes are not supported by the MicroEJ JavaScript engine:

- ``with (x) { }``
- ``break`` or ``continue`` in an unreachable section of code i.e. after a ``return`` or another ``break`` or ``continue``
- ``delete x``
- ``typeof x``
- ``arguments``

Methods
*******

The following methods are not supported by the MicroEJ JavaScript engine:

- ``eval ( x )``
- ``Function ( p1, p2, … , pn, body )`` constructor