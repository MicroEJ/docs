..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _js.limitations:

Limitations
===========

Unsupported Directives
**********************

Directives, such as ``'use strict'``, are not supported and are considered as literal statements. Literal statements are just ignored.

Unsupported Statements
**********************

The following syntaxes are not supported by the MicroEJ JavaScript engine:

- ``with (x) { }``
- unreachable code after a ``return``, ``break``, ``continue`` or ``throw``
- ``delete x``
- ``typeof x``
- ``arguments``
- ``get`` and ``set`` in object initialiser

Unsupported Methods
*******************

The following methods are not supported by the MicroEJ JavaScript engine:

- ``eval ( x )``
- ``Function ( p1, p2, … , pn, body )`` constructor