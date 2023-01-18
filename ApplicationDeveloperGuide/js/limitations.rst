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
  See `the reference documentation <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/with>`_ for more information.

Unsupported Built-in Objects
****************************

The unsupported built-in objects are listed in the :ref:`API section <js.api>`.

..
   | Copyright 2020-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
