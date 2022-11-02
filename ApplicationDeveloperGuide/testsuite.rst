.. _application_testsuite:

Test Suite with JUnit
=====================

MicroEJ allows to run unit tests using the standard `JUnit`_ API during
the build process of a MicroEJ library or a MicroEJ Application. The
:ref:`testsuite_engine` runs tests on a target Platform and outputs a
JUnit XML report.

.. _JUnit: https://repository.microej.com/modules/ej/library/test/junit/

Principle
---------

`JUnit`_ testing can be enabled when using the ``microej-javalib`` (MicroEJ
Add-On Library) or the ``microej-application`` (MicroEJ Applications)
build type. JUnit test cases processing is automatically enabled when
the following dependency is declared in the ``module.ivy`` file of the
project.

.. code-block:: xml

   <dependency conf="test->*" org="ej.library.test" name="junit" rev="1.6.2"/>

When a new JUnit test case class is created in the ``src/test/java``
folder, a JUnit processor generates MicroEJ compliant classes into a
specific source folder named ``src-adpgenerated/junit/java``. These
files are automatically managed and must not be edited manually.

JUnit Compliance
----------------

MicroEJ is compliant with a subset of JUnit version 4. MicroEJ JUnit
processor supports the following annotations: ``@After``,
``@AfterClass``, ``@Before``, ``@BeforeClass``, ``@Ignore``, ``@Test``.

Each test case entry point must be declared using the ``org.junit.Test``
annotation (``@Test`` before a method declaration). Please refer to
JUnit documentation to get details on usage of other annotations.

Setup a Platform for Tests
--------------------------

Before running tests, a target platform must be configured.

Execution in SDK
~~~~~~~~~~~~~~~~

In order to execute the Test Suite in the SDK, a target platform must be configured in the MicroEJ workspace.
The following steps assume that a platform has been previously imported into the MicroEJ Platform repository (or available in the Workspace):

- Go to :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Platforms` (or :guilabel:`Platforms in workspace`).
- Select the desired platform on which to run the tests.
- Press :kbd:`F2` to expand the details.
- Select the the platform path and copy it to the clipboard.
- Go to :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Ant` > :guilabel:`Runtime` and select the :guilabel:`Properties` tab.
- Click on :guilabel:`Add Property...` button and set a new property named ``target.platform.dir`` with the platform path pasted from the clipboard.

Execution during module build
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to execute the Test Suite during the build of the module, 
a target platform must be configured in the module project as described in the section :ref:`platform_selection`.

Setup a Project with a JUnit Test Case
--------------------------------------

This section describes how to create a new JUnit Test Case starting from
a new MicroEJ library project.

- First create a new :ref:`module project <mmm_module_skeleton>` using the ``microej-javalib`` skeleton.
  A new project named ``mylibrary`` is created in the workspace.
- Right-click on the ``src/test/java`` folder and select :guilabel:`New` > :guilabel:`Other...` menu item.
- Select the :guilabel:`Java` > :guilabel:`JUnit` > :guilabel:`New JUnit Test Case` wizard.
- Enter a test name and press :guilabel:`Finish`. 
  A new JUnit test case class is created with a default failing test case.

Build and Run a JUnit Test Suite
--------------------------------

- Right-click on the ``mylibrary`` project and select :guilabel:`Build Module`.
  After the library is built, the test suite engine launches available test cases and the build process fails in the console view.
- On the ``mylibrary`` project, right-click and select :guilabel:`Refresh`.
  A ``target~`` folder appears with intermediate build files. The JUnit report is available at ``target~\test\xml\TEST-test-report.xml``.
- Double-click on the file to open the JUnit test suite report.
- Modify the test case by replacing

::

   fail("Not yet implemented");

with

::

   Assert.assertTrue(true);

- Right-click again on the ``mylibrary`` project and select :guilabel:`Build Module`.
  The test is now successfully executed on the target platform so the MicroEJ Add-On Library is fully built and published without errors.
- Double-click on the JUnit test suite report to see the test has been successfully executed.

.. _testsuite_report:

Test Suite Reports
------------------

Once a test suite is completed, the following test suite reports are generated:

- JUnit HTML report in the module project location ``target~/test/html/test/junit-noframes.html``.
  This report contains a summary and the execution trace of every executed test.

  .. figure:: images/testsuiteReportHTMLExample.png
     :alt: Example of MicroEJ Test Suite HTML Report
     
     Example of MicroEJ Test Suite HTML Report

- JUnit XML report in the module project location ``target~/test/xml/TEST-test-report.xml``.

  .. figure:: images/testsuiteReportXMLExample.png
     :alt: Example of MicroEJ Test Suite XML Report
     
     Example of MicroEJ Test Suite XML Report
  
  XML report file can also be open in the JUnit View. Right-click on the file > :guilabel:`Open With` >  :guilabel:`JUnit View`:

  .. figure:: images/testsuiteReportXMLExampleJunitView.png
     :alt: Example of MicroEJ Test Suite XML Report in JUnit View
     
     Example of MicroEJ Test Suite XML Report in JUnit View

If executed on device, the Firmware binary produced for each test
is available in module project location ``target~/test/xml/<TIMESTAMP>/bin/<FULLY-QUALIFIED-CLASSNAME>/application.out``.


Advanced Configurations
-----------------------

Autogenerated Test Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~

The JUnit processor generates test classes into the
``src-adpgenerated/junit/java`` folder. This folder contains:

``_AllTestClasses.java`` file
    A single class with a main entry point that sequentially calls all declared
    test methods of all JUnit test case classes.

``_AllTests_[TestCase].java`` files
    For each JUnit test case class, a class with a main entry point that
    sequentially calls all declared test methods.

``_SingleTest_[TestCase]_[TestMethod].java`` files
    For each test method of each JUnit test case class, a class with a main
    entry point that calls the test method.

JUnit Test Case to MicroEJ Test Case
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :ref:`testsuite_engine` allows to select the classes that will be
executed, by setting the following property in the project
``module.ivy`` file.

.. code-block:: xml

   <ea:property name="test.run.includes.pattern" value="[MicroEJ Test Case Include Pattern]"/>

The following line consider all JUnit test methods of the same class as
a single MicroEJ test case (default behavior). If at least one JUnit
test method fails, the whole test case fails in the JUnit report.

.. code-block:: xml

   <ea:property name="test.run.includes.pattern" value="**/_AllTests_*.class"/>

The following line consider each JUnit test method as a dedicated
MicroEJ test case. Each test method is viewed independently in the JUnit
report, but this may slow down the test suite execution because a new
deployment is done for each test method.

.. code-block:: xml

   <ea:property name="test.run.includes.pattern" value="**/_SingleTest_*.class"/>

Run a Single Test Manually
~~~~~~~~~~~~~~~~~~~~~~~~~~

Each test can be run independently as each class contains a main entry
point.

In the ``src-adpgenerated/junit/java`` folder, right-click on the desired
autogenerated class (``_SingleTest_[TestCase]_[TestMethod].java``) and select
:guilabel:`Run As` > :guilabel:`MicroEJ Application`.

The test is executed on the selected Platform and the output result is
dumped into the console.

.. _testsuite_options:

Test Suite Options
~~~~~~~~~~~~~~~~~~

The :ref:`testsuite_engine` can be configured with specific options 
which can be added to the ``module.ivy`` file of the project running the test suite, 
within the ``<ea:build>`` XML element.

- Application Option Injection
  
  It is possible to inject an :ref:`Application Option <application_options>` for all the tests, 
  by adding to the original option the ``microej.testsuite.properties.`` prefix:

  .. code-block:: xml 
  
     <ea:property name="microej.testsuite.properties.[application_option_name]" value="[application_option_value]"/> 
      
- Retry Mechanism
  
  A test execution may not be able to produce the success trace for an external reason,
  for example an unreliable harness script that may lose some trace characters or crop the end of the trace.
  For all these unlikely reasons, it is possible to configure the number of retries before a test is considered to have failed:

  .. code-block:: xml

     <ea:property name="microej.testsuite.retry.count" value="[nb_of_retries]"/> 
      
  By default, when a test has failed, it is not executed again (option value is set to ``0``).

Test Specific Options
~~~~~~~~~~~~~~~~~~~~~

The :ref:`testsuite_engine` allows to define :ref:`application_options`
specific to each test case. This can be done by defining a file with the
same name as the generated test case file with the ``.properties``
extension instead of the ``.java`` extension. The file must be put in
the ``src/test/resources`` folder and within the same package than the
test case file.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
