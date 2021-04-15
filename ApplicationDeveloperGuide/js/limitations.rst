..
.. ReStructuredText
..
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
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
- ``arguments``
- ``get`` and ``set`` in object initialiser

Unsupported Built-in objects
****************************

The unsupported built-in objects are listed in the :ref:`Built-in objects section <js.builtin>`.