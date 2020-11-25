.. _testsuite_engine:

Testsuite Engine
================

MicroEJ Testsuite Engine
========================

Introduction
------------

The MicroEJ Testsuite Engine is a generic tool made for validating any
development project using automatic testing.

This section details advanced configuration for users who wish to
integrate custom testsuites in their build flow.

The MicroEJ Testsuite Engine allows the user to test any kind of
projects within the configuration of a generic Ant file.

   .. figure:: images/testsuiteEngine.png
      :alt: MicroEJ Testsuite Engine Overview
      :align: center
      :width: 500px

The MicroEJ Testsuite Engine is already pre-configured for running
testsuites on a MicroEJ Platform (either on Simulator or on Device).

- For Application and Libraries, refer to :ref:`application_testsuite`
  section.
- For Foundation Libraries Testsuites, refer to
  :ref:`platform_testsuite` section.

Using the MicroEJ Testsuite Ant Tasks
--------------------------------------

Multiple Ant tasks are available in the ``testsuite-engine.jar``
provided in the :ref:`Build Kit <mmm_build_kit>`:

-  ``testsuite`` allows the user to run a given testsuite and to
   retrieve an XML report document in a JUnit format.

-  ``javaTestsuite`` is a subtask of the ``testsuite`` task, used to run
   a specialized testsuite for Java (will only run Java classes).

-  ``htmlReport`` is a task which will generate an HTML report from a
   list of JUnit report files.

.. _testsuite-command-ant-runtestsuite:

The ``testsuite`` Task
~~~~~~~~~~~~~~~~~~~~~~

The following attributes are mandatory:

.. list-table:: ``testsuite`` task mandatory attributes
   :widths: 1 5
   :header-rows: 1
   
   * - Attribute Name
     - Description
   * - ``outputDir``
     - The output folder of the testsuite. The final report will be
       generated at ``[outputDir]/[label]/[reportName].xml``, see the
       ``testsuiteReportFileProperty`` and
       ``testsuiteReportDirProperty`` attributes.
   * - ``harnessScript``
     - The harness script must be an Ant script and it is the script
       which will be called for each test by the testsuite engine. It
       is called with a ``basedir`` located at output location of the
       current test.

The testsuite engine provides the following properties to the harness
script giving all the informations to start the test:

.. list-table:: ``harnessScript`` properties
   :widths: 1 5
   :header-rows: 1

   * - Attribute Name
     - Description
   * - ``testsuite.test.name``
     - The output name of the current test in the report. Default
       value is the relative path of the test. It can be manually set
       by the user. More details on the output name are available in
       the section :ref:`testsuite-various-customproperties`.
   * - ``testsuite.test.path``
     - The current test absolute path in the filesystem.
   * - ``testsuite.test.properties``
     - The absolute path to the custom properties of the current test
       (see the property ``customPropertiesExtension``)
   * - ``testsuite.common.properties``
     - The absolute path to the common properties of all the tests
       (see the property ``commonProperties``)
   * - ``testsuite.report.dir``
     - The absolute path to the directory of the final report.

The following attributes are optional:

.. list-table:: ``testsuite`` task optional attributes
   :widths: 1 5 3
   :header-rows: 1

   * - Attribute Name
     - Description
     - Default value
   * - ``timeOut``
     - The time in seconds before any test is considerated as
       unknown. Set it to ``0`` to disable the time-out.
     - ``60``
   * - ``verboseLevel``
     - The required level to output messages from the testsuite. Can
       be one of those values: ``error``, ``warning``, ``info``,
       ``verbose``, ``debug``.
     - ``info``
   * - ``reportName``
     - The final report name (without extension).
     - ``testsuite-report``
   * - ``customPropertiesExtension``
     - The extension of the custom properties for each test. For
       instance, if it is set to ``.options``, a test named
       ``xxx/Test1.class`` will be associated with
       ``xxx/Test1.options``. If a file exists for a test, the
       property ``testsuite.test.properties`` is set with its absolute
       path and given to the ``harnessScript``. If the test path
       references a directory, then the custom properties path is the
       concatenation of the test path and the
       ``customPropertiesExtension`` value.
     - ``.properties``
   * - ``commonProperties``
     - The properties to  apply to every test of  the testsuite. Those
       options might  be overridden by  the custom properties  of each
       test. If this  option is set and the file  exists, the property
       ``testsuite.common.properties`` is set to  the absolute path of
       the ``harnessScript`` file. 
     - no common properties
   * - ``label``
     - The build label.
     - timestamp of when the testsuite was invoked.
   * - ``productName``
     - The name of the current tested product.
     - ``TestSuite``
   * - ``jvm``
     - The location of your Java VM to start the testsuite (the
       ``harnessScript`` is called as is:  ``[jvm] [...] -buildfile
       [harnessScript]``).
     - ``java.home`` location if the property is set, ``java``
       otherwise.
   * - ``jvmargs``
     - The arguments to pass to the Java VM started for each test.
     - None.
   * - ``testsuiteReportFileProperty``
     - The name of the Ant property in which the path of the final
       report is stored. Path is
       ``[outputDir]/[label]/[reportName].xml``
     - ``testsuite.report.file``
   * - ``testsuiteReportDirProperty``
     - The name of the Ant property in which is store the path of the
       directory of the final report. Path is ``[outputDir]/[label]``.
     - ``testsuite.report.dir``

   * - ``testsuiteResultProperty``
     - The name of the Ant property in which you want to have the
       result of the testsuite (``true`` or ``false``), depending if
       every tests successfully passed the testsuite or not.  Ignored
       tests do not affect this result.
     - None

Finally, you have to give as nested element the path containing the
tests.

.. list-table:: ``testsuite`` task nested elements
   :widths: 1 5
   :header-rows: 1

   * - Element Name
     - Description
   * - ``testPath``
     - Containing all the file of the tests which will be launched by
       the testsuite.
   * - ``testIgnoredPath`` (optional)
     - Any test in the intersection between ``testIgnoredPath`` and
       ``testPath`` will be executed by the testsuite, but will not
       appear in the JUnit final report. It will still generate a
       JUnit report for each test, which will allow the HTML report to
       let them appears as "ignored" if it is generated.  Mostly used
       for known bugs which are not considered as failure but still
       relevant enough to appears on the HTML report.

.. code-block:: xml
   :caption: Example of testsuite task invocation

   <!-- Launch the testusite engine -->
   <testsuite:testsuite
       timeOut="${microej.kf.testsuite.timeout}"
       outputDir="${target.test.xml}/testkf"
       harnessScript="${com.is2t.easyant.plugins#microej-kf-testsuite.microej-kf-testsuite-harness-jpf-emb.xml.file}"
       commonProperties="${microej.kf.launch.propertyfile}"
       testsuiteResultProperty="testkf.result"
       testsuiteReportDirProperty="testkf.testsuite.report.dir"
       productName="${module.name} testkf"
       jvmArgs="${microej.kf.testsuite.jvmArgs}"
       lockPort="${microej.kf.testsuite.lockPort}"
       verboseLevel="${testkf.verbose.level}"
   >
       <testPath refid="target.testkf.path"/>
   </testsuite:testsuite>

.. _testsuite-command-ant-runjavatestsuite:

The ``javaTestsuite`` Task
~~~~~~~~~~~~~~~~~~~~~~~~~~

This task extends the ``testsuite`` task, specializing the testsuite to
only start real Java class. This task retrieves the classname of the
tests from the classfile and provides new properties to the harness
script:

.. list-table:: ``javaTestsuite`` task properties
   :widths: 1 5
   :header-rows: 1

   * - Property Name
     - Description
   * - ``testsuite.test.class``
     - The classname of the current test. The value of the property
       ``testsuite.test.name`` is also set to the classname of the
       current test.
   * - ``testsuite.test.classpath``
     - The classpath of the current test.

.. code-block:: xml
   :caption: Example of javaTestsuite task invocation

   <!-- Launch test suite -->
   <testsuite:javaTestsuite
       verboseLevel="${microej.testsuite.verboseLevel}"
       timeOut="${microej.testsuite.timeout}"
       outputDir="${target.test.xml}/@{prefix}"
       harnessScript="${harness.file}"
       commonProperties="${microej.launch.propertyfile}"
       testsuiteResultProperty="@{prefix}.result"
       testsuiteReportDirProperty="@{prefix}.testsuite.report.dir"
       productName="${module.name} @{prefix}"
       jvmArgs="${microej.testsuite.jvmArgs}"
       lockPort="${microej.testsuite.lockPort}"
       retryCount="${microej.testsuite.retry.count}"
       retryIf="${microej.testsuite.retry.if}"
       retryUnless="${microej.testsuite.retry.unless}"
   >
       <testPath refid="target.@{prefix}.path"/>
       <testIgnoredPath refid="tests.@{prefix}.ignored.path" />
   </testsuite:javaTestsuite>

.. _testsuite-command-ant-generatereport:

The ``htmlReport`` Task
~~~~~~~~~~~~~~~~~~~~~~~

This task allow the user to transform a given path containing a sample
of JUnit reports to an HTML detailed report. Here is the attributes to
fill:

- A nested ``fileset`` element containing all the JUnit reports of
  each test.  Take care to exclude the final JUnit report generated by
  the testsuite.

-  A nested element ``report``:

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

.. note::

   It is advised to set the format to ``noframes`` if your test suite
   is not a Java testsuite. If the format is set to ``frames``, with a
   non-Java MicroEJ Testsuite, the name of the links will not be
   relevant because of the non-existency of packages.


.. code-block:: xml
   :caption: Example of htmlReport task invocation

   <!-- Generate HTML report -->
   <testsuite:htmlReport>
       <fileset dir="${@{prefix}.testsuite.report.dir}">
           <include name="**/*.xml"/> <!-- include unary reports -->
           <exclude name="**/bin/**/*.xml"/> <!-- exclude test bin files -->
           <exclude name="*.xml"/> <!-- exclude global report -->
       </fileset>
       <report format="noframes" todir="${target.test.html}/@{prefix}"/>
   </testsuite:htmlReport>


.. _testsuite-trace-analyzer:

Using the Trace Analyzer
------------------------

This section will shortly explains how to use the ``Trace Analyzer``.
The MicroEJ Testsuite comes with an archive containing the
``Trace Analyzer`` which can be used to analyze the output trace of an
application. It can be used from different forms;

-  The ``FileTraceAnalyzer`` will analyze a file and research for the
   given tags, failing if the success tag is not found.

-  The ``SerialTraceAnalyzer`` will analyze the data from a serial
   connection.

.. _testsuite-trace-analyzer-options:

The TraceAnalyzer Tasks Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is the common options to all TraceAnalyzer tasks:

-  ``successTag``: the regular expression which is synonym of success
   when found (by default ``.*PASSED.*``).

-  ``failureTag``: the regular expression which is synonym of failure
   when found (by default ``.*FAILED.*``).

-  ``verboseLevel``: int value between 0 and 9 to define the verbose
   level.

-  ``waitingTimeAfterSuccess``: waiting time (in s) after success before
   closing the stream (by default 5).

-  ``noActivityTimeout``: timeout (in s) with no activity on the stream
   before closing the stream. Set it to 0 to disable timeout (default
   value is 0).

-  ``stopEOFReached``: boolean value. Set to ``true`` to stop analyzing
   when input stream EOF is reached. If ``false``, continue until
   timeout is reached (by default ``false``).

-  ``onlyPrintableCharacters``: boolean value. Set to ``true`` to only
   dump ASCII printable characters (by default ``false``).

.. _testsuite-trace-analyzer-file:

The FileTraceAnalyzer Task Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is the specific options of the FileTraceAnalyzer task:

-  ``traceFile``: path to the file to analyze.

.. _testsuite-trace-analyzer-serial:

The SerialTraceAnalyzer Task Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is the specific options of the SerialTraceAnalyzer task:

-  ``port``: the comm port to open.

-  ``baudrate``: serial baudrate (by default 9600).

-  ``databits``: databits (5|6|7|8) (by default 8).

-  ``stopBits``: stopbits (0|1|3 for (1_5)) (by default 1).

-  ``parity``: ``none`` \| ``odd`` \| ``event`` (by default ``none``).


.. _testsuite-various:

Appendix
--------

The goal of this section is to explain some tips and tricks that might
be useful in your usage of the testsuite engine.

.. _testsuite-various-customproperties:

Specific Custom Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~

Some custom properties are specifics and retrieved from the testsuite
engine in the custom properties file of a test.

-  The ``testsuite.test.name`` property is the output name of the
   current test. Here are the steps to compute the output name of a
   test:

   -  If the custom properties are enabled and a property named
      ``testsuite.test.name`` is find on the corresponding file, then
      the output name of the current test will be set to it.

   -  Otherwise, if the running MicroEJ Testsuite is a Java testsuite,
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
   global timeout defined for the MicroEJ Testsuite is used.


Dependencies
------------

No dependency.


Installation
------------

This tool is provided in the :ref:`Build Kit <mmm_build_kit>`.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
