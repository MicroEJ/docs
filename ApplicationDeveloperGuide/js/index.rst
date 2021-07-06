..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

============
 JavaScript
============

MicroEJ allows to develop parts of an application in JavaScript. Basically, a MicroEJ Application boots in Java, then it initializes the JavaScript runtime to run a mix of Java and JavaScript code.


.. figure:: images/js_runtime.png
   :alt: MicroEJ JavaScript Runtime Overview
   :scale: 55%
   :align: center

   MicroEJ JavaScript Runtime Overview
|

It supports the `ECMAScript 5.1 specification <https://262.ecma-international.org/5.1>`_, with :ref:`some limitations <js.limitations>`.
You can start playing with it by following the :ref:`Getting Started <js.getting_started>` page.

.. toctree::
   :maxdepth: 1
   :hidden:

   getting_started
   sources
   examples
   java
   tests
   limitations
   builtin
   troubleshooting
   internals