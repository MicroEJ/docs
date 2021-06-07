..
.. ReStructuredText
..
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _js.limitations:

Limitations
===========

The MicroEJ engine supports the version 5.1 of the ECMAScript specification, with the limitations described in this page.

Unsupported Directives
**********************

Directives, such as ``'use strict'``, are not supported and are considered as literal statements. Literal statements are just ignored.

Unsupported Statements
**********************

The following syntaxes are not supported by the MicroEJ JavaScript engine:

- ``with (x) { }`` : the ``with`` statement is not supported in MicroEJ since its usage is not recommended. 
  See `the reference documentation <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/with#ambiguity_contra>`_ for more information.

Unsupported Built-in objects
****************************

The unsupported built-in objects are listed in the :ref:`Built-in objects section <js.builtin>`.