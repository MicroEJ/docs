..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _microjs.limitations:

Limitations
===========

Unsupported Statements
**********************

The following syntaxes are not supported by the MicroEJ JavaScript engine:

- ``with (x) { }``
- unreachable code after a ``return``, ``break``, ``continue`` or ``throw``
- ``delete x``
- ``typeof x``
- ``arguments``

Unsupported Methods
*******************

The following methods are not supported by the MicroEJ JavaScript engine:

- ``eval ( x )``
- ``Function ( p1, p2, … , pn, body )`` constructor