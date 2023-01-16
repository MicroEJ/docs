.. _js.tests:

Tests
=====

JavaScript applications can be tested with tests written in JavaScript.
The JavaScript test files must be located in the project folder ``src/test/js``.
All JavaScript files (``*.js``) found in this folder, at any level, are considered as test files.

In order to setup JavaScript tests for your application, follow these steps:

- create an :ref:`Add-On Library <libraries>` project or a :ref:`Standalone Application <standalone_application>` project
- define the following properties in the module.ivy file of the project inside the ``ea:build`` tag (if the properties already exist, replace them):

.. code-block:: xml

    <ea:property name="test.run.includes.pattern" value="**/_JsTest_*Code.class"/>
    <ea:property name="target.main.classes" value="${basedir}/target~/test/classes"/>

- add the MicroEJ JavaScript dependency in the module.ivy file of the project:

.. code-block:: xml

    <dependency org="com.microej.library.runtime" name="js" rev="0.13.0"/>

- define the platform to use to run the tests with one of the options described in :ref:`platform_selection` section
- create a file ``assert.js`` in the folder ``src/test/resources`` with the following content:

.. code-block:: javascript

	var assertionCount = 0;

	function assert(value) {
		assertionCount++;
		if (value == 0) {
			print("assert " + assertionCount + " - FAILED");
		} else {
			print("assert " + assertionCount + " - PASSED");
		}
	}

This method ``assert`` will be available in all tests to do assertions.

- create a file ``test.js`` in the folder ``src/test/js`` and write your first test:

.. code-block:: javascript

	var a = 5;
	var b = 3;
	var sum = a + b;
	assert(sum === 8);

- build the application in the SDK or in command line with the :ref:`MMM CLI <mmm_build_kit>`

The execution of the tests produces a report available in the folder ``target~/test/html`` for the project.

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
