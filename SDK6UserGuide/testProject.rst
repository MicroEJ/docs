.. _sdk_6_test_project:

Test a Project
==============

The SDK provides the capabilities to implement and run tests for a project.
It relies on the standard `JUnit`_ API.
The tests are executed on a target VEE Port and generate a JUnit XML report.

There are different types of tests:

- test on the Simulator
- test on a J2SE VM
- test on a device
- project test on a device

The SDK 6 currently supports only the tests on the Simulator.

.. _JUnit: https://repository.microej.com/modules/ej/library/test/junit/

JUnit Compliance
----------------

MicroEJ is compliant with a subset of JUnit version 4. 
MicroEJ JUnit processor supports the following annotations: ``@After``,
``@AfterClass``, ``@Before``, ``@BeforeClass``, ``@Ignore``, ``@Test``.

Each test case entry point must be declared using the ``org.junit.Test`` annotation (``@Test`` before a method declaration). 
Refer to JUnit documentation to get details on usage of other annotations.

Test on Simulator
-----------------

Create a Test
~~~~~~~~~~~~~

JUnit testing can be enabled for Add-On Library projects (plugin ``com.microej.gradle.library``) 
or Application projects (plugin ``com.microej.gradle.application``).

- add the following dependency in the ``build.gradle.kts`` file of the project:

.. code-block:: xml

   dependencies {
      testImplementation("ej.library.test:junit:1.7.1")
   }

- create a JUnit class in the ``src/test/java`` folder.
  This can be done manually or with IDE menu:
  
.. tabs::

   .. tab:: Eclipse

      - right-click on the ``src/test/java`` folder.
      - select :guilabel:`New`` > :guilabel:`Other…` > :guilabel:`Java` > :guilabel:`JUnit` > :guilabel:`New JUnit Test Case`.

   .. tab:: IntelliJ IDEA

      - right-click on the ``src/test/java`` folder.
      - select :guilabel:`New` > :guilabel:`Java Class``, then press ``Alt`` + ``Insert`` and select ``Test Method``.

Setup a VEE Port
~~~~~~~~~~~~~~~~

Before running tests, a target VEE Port must be configured using one of the methods described in the :ref:`sdk_6_select_veeport` page.

Filter the Tests
~~~~~~~~~~~~~~~~

For a single test, several classes are generated (see :ref:`sdk_6_testsuite_generated_classes` for more details).
Only one of them must be executed, dependending on your need.
The :ref:`testsuite_engine` allows to select the classes that will be
executed, by adding the following configuration in the project build file:

.. code-block:: java

   tasks.test {
      filter {
         includeTestsMatching([Test Case Include Pattern])
      }
   }

The following configuration considers all JUnit test methods of the same class as
a single MicroEJ test case (default behavior). If at least one JUnit
test method fails, the whole test case fails in the JUnit report.

.. code-block:: java

   tasks.test {
      filter {
         includeTestsMatching("*_AllTests_*")
      }
   }

The following configuration considers each JUnit test method as a dedicated
MicroEJ test case. Each test method is viewed independently in the JUnit
report, but this may slow down the test suite execution because a new
deployment is done for each test method.

.. code-block:: java

   tasks.test {
      filter {
         includeTestsMatching("*._SingleTest_*")
      }
   }

Execute the Tests
~~~~~~~~~~~~~~~~~

The SDK provides the Gradle task ``testOnSimulator`` to execute tests on the Simulator.
This task is plugged to the ``test``, which is part of the default Gradle lifecycle.
It means that the tests can be executed by launching the task ``testOnSimulator``, ``test`` 
or even ``build`` since the ``build`` task depends on the ``test`` task.

It can be executed with the command line interface::

   gradle test

or from Eclipse and IntelliJ IDEA, by double-clicking on the task in the Gradle tasks view:

.. tabs::

   .. tab:: Eclipse

      .. image:: images/eclipse-test-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      .. image:: images/intellij-test-gradle-project.png
         :width: 30%
         :align: center

Run a Single Test Manually
~~~~~~~~~~~~~~~~~~~~~~~~~~

Each test can be run independently by using the ``--tests`` option of the ``test`` task::

   gradle test --tests com.mycompany._AllTests_MyTest

The test must be referenced by the Full Qualified Name of the generated class.

The test is executed on the VEE Port defined in the project build file 
and the output result is dumped into the console.

Test Suite Reports
------------------

Once a test suite is completed, the following test suite reports are generated:

- JUnit HTML report in the module project location ``build/testsuite/report/junit-noframes.html``.
  This report contains a summary and the execution trace of every executed test.

  .. figure:: ../SDKUserGuide/images/testsuiteReportHTMLExample.png
     :alt: Example of MicroEJ Test Suite HTML Report
     
     Example of MicroEJ Test Suite HTML Report

- JUnit XML report in the module project location ``build/testsuite/results/TESTS-TestSuites.xml``.

  .. figure:: ../SDKUserGuide/images/testsuiteReportXMLExample.png
     :alt: Example of MicroEJ Test Suite XML Report
     
     Example of MicroEJ Test Suite XML Report
  
  XML report file can also be opened In Eclipse in the JUnit View. 
  Right-click on the file > :guilabel:`Open With` >  :guilabel:`JUnit View`:

  .. figure:: ../SDKUserGuide/images/testsuiteReportXMLExampleJunitView.png
     :alt: Example of MicroEJ Test Suite XML Report in JUnit View
     
     Example of MicroEJ Test Suite XML Report in JUnit View


Advanced Configurations
-----------------------

.. _sdk_6_testsuite_generated_classes:

Autogenerated Test Classes
~~~~~~~~~~~~~~~~~~~~~~~~~~

The JUnit processor generates test classes into the ``build/adp/src-adpgenerated/junit/java`` folder. 
This folder contains:

``_AllTestClasses.java`` file
    A single class with a main entry point that sequentially calls all declared
    test methods of all JUnit test case classes.

``_AllTests_[TestCase].java`` files
    For each JUnit test case class, a class with a main entry point that
    sequentially calls all declared test methods.

``_SingleTest_[TestCase]_[TestMethod].java`` files
    For each test method of each JUnit test case class, a class with a main
    entry point that calls the test method.

.. _sdk_6_testsuite_options:

Test Specific Options
~~~~~~~~~~~~~~~~~~~~~

The :ref:`testsuite_engine` allows to define :ref:`application_options` specific to each test case. 
This can be done by defining a file with the same name as the generated test case file, 
but with the ``.properties`` extension instead of the ``.java`` extension. 
The file must be put in the ``src/test/resources`` folder and within the same package than the test case file.

.. _sdk_6_test_with_multiple_vee_ports:

Test a Project with multiple VEE Ports
--------------------------------------

If multiple VEE Ports are defined, the tests are executed on each VEE Port sequentially.
If you want to execute the tests on only one VEE Port, you must select it by setting the ``veePort`` property 
to the :ref:`unique name <sdk_6_vee_port_unique_name>` of the VEE Port in the command line::

   gradle test -PveePort="veePortName"

If you want to add the property from IntelliJ IDEA : 

- Go to ``Run`` > ``Edit Configurations...``
- Click on the ``+`` button and select ``Gradle``
- Choose a name for the new Configuration
- Add the command line with the ``veePort`` property in the Run dialog : ``test -PveePort="veePortName"``:

  .. figure:: images/intellij-test-run-configuration.png
     :alt: IntelliJ test Run Configuration Window
     :align: center
     :scale: 100%

     IntelliJ test Run Configuration Window

- Click on ``OK``
- Run the task by double clicking on the newly created Run Configuration in the Gradle task view:

  .. figure:: images/intellij-test-run-configuration-gradle-view.png
     :alt: IntelliJ test Run Configuration in Gradle tasks view
     :align: center
     :scale: 100%

     IntelliJ test Run Configuration in Gradle tasks view

If you want to add the property from Eclipse : 

- Go to ``Run`` > ``Run Configurations...``
- Create a new Gradle Configuration
- In the ``Gradle Tasks``, add the ``test`` task :

  .. figure:: images/eclipse-test-gradle-tasks.png
     :alt: Eclipse test task Gradle Tasks tab
     :align: center
     :scale: 100%
     
     Eclipse test task Gradle Tasks tab

- Go to the ``Project Settings`` tab
- Check ``Override project settings``
- Select ``Gradle Wrapper``
- Add the property as a Program Argument :

  .. figure:: images/eclipse-test-project-settings.png
     :alt: Eclipse test task Project Settings tab
     :align: center
     :scale: 100%
     
     Eclipse test task Project Settings tab

- Click on ``Run``
  
The name of each VEE Port can be found by executing the tests with the verbose mode enabled::

   gradle test --info

The list of the VEE Ports is displayed before running the testsuite::

   The testsuite will be run on each of the following VEE Ports:
   - "veePort1"
   - "veePort2"

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
