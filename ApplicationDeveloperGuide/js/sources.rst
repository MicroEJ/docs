.. _js.sources:

Sources Management
==================

JavaScript Sources Location
---------------------------

The JavaScript sources of an application must be located in the project folder ``src/main/js``.
All JavaScript files (``*.js``) found in this folder, at any level, are processed.


JavaScript Sources Load Order
-----------------------------

When several JavaScript files are found in the sources folder, they are loaded in alphabetical order of their relative path.
For example, the following source files:

.. code-block::

   src
   └── main
       └── js
           ├── components
           │   ├── component1.js
           │   └── component2.js
           ├── ui
           │   └── widgets.js
           ├── app.js
           ├── feature1.js
           └── feature2.js

are loaded in this order:

#. app.js
#. components/component1.js
#. components/component2.js
#. feature1.js
#. feature2.js
#. ui/widgets.js


JavaScript Sources Load Scope
-----------------------------

All the code of the JavaScript source files are loaded in the same scope.
It means a variable or function defined in a source file can be used in another one if it has been loaded first.
In this example:

.. code-block:: javascript
   :caption: src/main/js/lib.js

   function sum(a, b) {
       return a + b;
   }

.. code-block:: javascript
   :caption: src/main/js/main.js

   print("5 + 3 = " + sum(5, 3));

the file ``src/main/js/lib.js`` is loaded before ``src/main/js/main.js`` so the function ``sum`` can be used in ``src/main/js/main.js``.

JavaScript Sources Processing
-----------------------------

JavaScript sources need to be processed before being executed. This processing is done in the following cases:

- when building the project with :ref:`MMM <mmm>`.
- when developing the project in MicroEJ SDK.
  The MicroEJ SDK detects any change in JavaScript sources folder (addition/update/deletion) to trigger the processing.

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
