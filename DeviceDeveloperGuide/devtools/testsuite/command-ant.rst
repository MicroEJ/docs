.. _testsuite-command-ant:

Using the MicroEJ Test-Suite Ant tasks
======================================

Multiple Ant tasks are available in the testsuite-engine provided jar:

-  ``testsuite`` allows the user to run a given test suite and to
   retrieve an XML report document in a JUnit format.

-  ``javaTestsuite`` is a subtask of the ``testsuite`` task, used to run
   a specialized test suite for Java (will only run Java classes).

-  ``htmlReport`` is a task which will generate an HTML report from a
   list of JUnit report files.

.. _testsuite-command-ant-runtestsuite:

The test suite task
-------------------

This task have some mandatory attributes to fill:

-  ``outputDir``: the output folder of the test-suite. The final report
   will be generated at ``[outputDir]/[label]/[reportName].xml``, see
   the ``testsuiteReportFileProperty`` and
   ``testsuiteReportDirProperty`` attributes.

-  ``harnessScript``: the harness script must be an Ant script and it is
   the script which will be called for each test by the test-suite
   engine. It is called with a ``basedir`` located at output location of
   the current test. The test-suite engine will provide to it some
   properties giving all the informations to start the test:

   -  ``testsuite.test.name``: The output name of the current test in
      the report. Default value is the relative path of the test. It can
      be manually set by the user. More details on the output name are
      available in the section
      `??? <#testsuite-various-customproperties>`__.

   -  ``testsuite.test.path``: The current test absolute path in the
      filesystem.

   -  ``testsuite.test.properties``: The absolute path to the custom
      properties of the current test (see the property
      ``customPropertiesExtension``)

   -  ``testsuite.common.properties``: The absolute path to the common
      properties of all the tests (see the property
      ``commonProperties``)

   -  ``testsuite.report.dir``: The absolute path to the directory of
      the final report.

Some attributes are optional, and if not set by the user, a default
value will be attributed.

-  ``timeOut``: the time in seconds before any test is considerated as
   unknown. Set it to 0 to disable the time-out. Will be defaulted as
   60.

-  ``verboseLevel``: the required level to output messages from the
   test-suite. Can be one of those values: error, warning, info,
   verbose, debug. Will be defaulted as info.

-  ``reportName``: the final report name (without extension). Default
   value is ``testsuite-report``.

-  ``customPropertiesExtension``: the extension of the custom properties
   for each test. For instance, if it is set to ``.options``, a test
   named ``xxx/Test1.class`` will be associated with
   ``xxx/Test1.options``. If a file exists for a test, the property
   ``testsuite.test.properties`` is set with its absolute path and given
   to the ``harnessScript``. If the test path references a directory,
   then the custom properties path is the concatenation of the test path
   and the ``customPropertiesExtension`` value. By default, custom
   properties extension is ``.properties``.

-  ``commonProperties``: the properties to apply to every test of the
   test-suite. Those options might be overridden by the custom
   properties of each test. If this option is set and the file exists,
   the property ``testsuite.common.properties`` is set to the absolute
   path of the ``harnessScript`` file. By default, there is not any
   common properties.

-  ``label``: the build label. Will be generated as a timestamp by the
   test-suite if not set.

-  ``productName``: the name of the current tested product. Default
   value is ``TestSuite``.

-  ``jvm``: the location of your Java VM to start the test suite (the
   ``harnessScript`` is called as is:
   ``[jvm] [...] -buildfile [harnessScript]``). Will be defaulted as
   your ``java.home`` location if the property is set, or to ``java``.

-  ``jvmargs``: the arguments to pass to the Java VM started for each
   test.

-  ``testsuiteReportFileProperty``: the name of the Ant property in
   which is stored the path of the final report. Default value is
   ``testsuite.report.file`` and path is
   ``[outputDir]/[label]/[reportName].xml``

-  ``testsuiteReportDirProperty``: the name of the Ant property in which
   is store the path of the directory of the final report. Default value
   is ``testsuite.report.dir`` and path is ``[outputDir]/[label]``

-  ``testsuiteResultProperty``: the name of the Ant property in which
   you want to have the result of the test-suite (true or false),
   depending if every tests successfully passed the test-suite or not.
   Ignored tests do not affect this result.

Finally, you have to give as nested element the path containing the
tests.

-  ``testPath``: containing all the file of the tests which will be
   launched by the test-suite.

-  ``testIgnoredPath`` (optional): Any test in the intersection between
   ``testIgnoredPath`` and ``testPath`` will be executed by the
   test-suite, but will not appear in the JUnit final report. It will
   still generate a JUnit report for each test, which will allow the
   HTML report to let them appears as "ignored" if it is generated.
   Mostly used for known bugs which are not considered as failure but
   still relevant enough to appears on the HTML report.

.. _testsuite-command-ant-runjavatestsuite:

The javaTestsuite task
----------------------

This task extends the ``testsuite`` task, specializing the test-suite to
only start real Java class. This task will retrieve the classname of the
tests from the classfile and will provide new properties to the harness
script:

-  ``testsuite.test.class``: The classname of the current test. The
   value of the property ``testsuite.test.name`` is also set to the
   classname of the current test.

-  ``testsuite.test.classpath``: The classpath of the current test.

.. _testsuite-command-ant-generatereport:

The htmlReport task
-------------------

This task allow the user to transform a given path containing a sample
of JUnit reports to an HTML detailled report. Here is the attributes to
fill:

-  A nested fileset containing all the JUnit reports of each test. Take
   care to exclude the final JUnit report generated by the test suite.

-  A nested element ``report``

   -  ``format``: The format of the generated HTML report. Must be
      ``noframes`` or ``frames``. When ``noframes`` format is choosen, a
      standalone HTML file is generated.

   -  ``todir``: The output folder of your HTML report.

   -  The ``report`` tag accepts the nested tag ``param`` with ``name``
      and ``expression`` attributes. These tags can pass XSL parameters
      to the stylesheet. The built-in stylesheets support the following
      parameters:

      -  ``PRODUCT``: the product name that is displayed in the title of
         the HTML report.

      -  ``TITLE``: the comment that is displayed in the title of the
         HTML report.

``Tip:`` It is advised to set the format to ``noframes`` if your test
suite is not a Java test suite. If the format is set to ``frames``, with
a non-Java MicroEJ Test-Suite, the name of the links will not be
relevant because of the non-existency of packages.
