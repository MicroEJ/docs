..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

=======
Testing
=======

Adding Tests
------------

A test is a JavaScript file with the ``.js`` extension. It must be put in  ``src/test/js`` directory of the project.

Each JavaScript test file is considered as a single test.

A test will pass if it can be successfully transpiled to Java and no exception is thrown during the test execution.

Successfully transpiled tests are put in ``src-adpgenerated/microjs/java`` under the ``com.microej.microjstest`` package. Each generated test file is named with following pattern: ``_JsTest_<jsfilename>Code.java`` where ``<jsfilename>`` is the name of the JavaScript test file without its extension.

A test that could not be successfully transpiled generates a test error entry in the class ``_JsTest__brokenCode.java``.

Defining Utility Functions for Tests
------------------------------------

Functions accessible to all tests can defined by puting the JavaScript files to ``src/test/resources``.

For instance, an ``assert()`` function can be defined by creating an ``assert.js`` file in ``src/test/resources`` with the following content:

.. code-block:: javascript

  function assert(result) {
    if (result == 0) {
	  throw 'Test failed!'
	}
  }

Running tests
-------------

Tests are run on simulator.

All tests can be automatically executed when building the module. To do this, add the following lines to your ``module.ivy`` file between the ``<info>`` tags

.. code:: xml

  <ea:property name="test.run.includes.pattern" value="**/_JsTest_*Code.class"/>
  <ea:property name="src.test.java" value="${basedir}/src-adpgenerated/microjs/java"/>

A failing test will result in a build fail.

To run a single test in your workspace, simply launch the corresponding ``_JsTest_*Code.java`` as a MicroEJ application on simulator.