.. _testsuite-various:

Appendix
========

The goal of this section is to explain some tips and tricks that might
be useful in your usage of the test-suite engine.

.. _testsuite-various-customproperties:

Specific custom properties
--------------------------

Some custom properties are specifics and retrieved from the test-suite
engine in the custom properties file of a test.

-  The ``testsuite.test.name`` property is the output name of the
   current test. Here are the steps to compute the output name of a
   test:

   -  If the custom properties are enabled and a property named
      ``testsuite.test.name`` is find on the corresponding file, then
      the output name of the current test will be set to it.

   -  Otherwise, if the running MicroEJ Test-Suite is a Java testsuite,
      the output name is set to the class name of the test.

   -  Otherwise, from the path containing all the tests, a common prefix
      will be retrieved. The output name will be set to the relative
      path of the current test from this common prefix. If the common
      prefix equals the name of the test, then the output name will be
      set to the name of the test.

   -  Finally, if multiples tests have the same output name, then the
      current name will be followed by ``_XXX``, an underscore and an
      integer.

-  The ``testsuite.test.timeout`` property allow the user to redefine
   the time out for each test. If it is negative or not an integer, then
   global timeout defined for the MicroEJ Test-Suite is used.
