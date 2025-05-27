.. _sdk_6_test_project:

Test a Project
==============

The SDK provides the capabilities to implement and run tests for a project.
It relies on the standard `JUnit`_ API.

There are different types of tests:

- Test on the Simulator
- Test on a device
- Test on a Java SE VM

Each type of test is detailed in the next sections.

.. _JUnit: https://repository.microej.com/modules/ej/library/test/junit/


JUnit Compliance
----------------

The SDK relies on `JUnit <https://junit.org/junit4/>`__, the most popular Java testing framework, to define and execute the tests.
It supports a subset of JUnit 4, namely the annotations: ``@After``,
``@AfterClass``, ``@Before``, ``@BeforeClass``, ``@Ignore``, ``@Test``.

Each test case entry point must be declared using the ``org.junit.Test`` annotation (``@Test`` before a method declaration). 
Refer to `JUnit documentation <https://junit.org/junit4/>`__ to get details on the usage of other annotations.


Gradle Integration
------------------

Tests are configured and launched by Gradle. 
Gradle provides 2 ways to configure tests in a project:

- By using the built-in ``Test`` task, 
  as described in `Testing in Java & JVM projects <https://docs.gradle.org/current/userguide/java_testing.html>`__.
- By using the new ``JVM Test Suite`` plugin, 
  as described in `The JVM Test Suite Plugin <https://docs.gradle.org/current/userguide/jvm_test_suite_plugin.html>`__.

The ``JVM Test Suite`` plugin provides an enhanced model to declare multiple groups of automated testsuites, 
and is therefore the recommended way to configure your tests.
The next sections use the ``JVM Test Suite`` plugin to explain how to configure and run tests, but the same results
can be achieved with the ``Test`` task.


.. _sdk_6_testsuite_on_sim:

Test on Simulator
-----------------

Tests can be executed on the Simulator.
They are run on a target VEE Port and generate a JUnit XML report.

Executing tests on the Simulator allows to check the behavior of the code in an environment similar to the target device
but without requiring the board.
This solution is therefore less constraining and more portable than testing on the board.


.. _sdk_6_testsuite_configuration:

Configure the Testsuite
^^^^^^^^^^^^^^^^^^^^^^^

The configuration of the testsuites of a project must be defined inside the following block in the ``build.gradle.kts`` file:

.. code-block::

   testing {
      suites { // (1)
         val test by getting(JvmTestSuite::class) { // (2)
            microej.useMicroejTestEngine(this) // (3)

            dependencies { // (4)
                implementation(project())
                implementation("ej.api:edc:1.3.5")
                implementation("ej.library.test:junit:1.11.0")
            }
         }
      }
   }

This piece of configuration is the minimum configuration required to define a testsuite on the Simulator:

- ``(1)``: configures all the testsuites of the project.
- ``(2)``: configures the built-in ``test`` suite provided by Gradle. Use this testsuite to configure the tests on the Simulator.
- ``(3)``: declares that this testsuite uses the MicroEJ Testsuite Engine. By default, the MicroEJ Testsuite Engine executes the tests on the
  Simulator.
- ``(4)``: adds the dependencies required by the tests. The first line declares a dependency to the code of the project.
  The second line declares a dependency on the ``edc`` Library. The third line declares a dependency to the JUnit API used 
  to annotate Java Test classes. Finally the fourth line declares a dependency to a required JUnit library.

.. warning::

   With SDK 6 prior to ``1.1.0``, ``junit-platform-launcher`` must be added as a test dependency::

      implementation("org.junit.platform:junit-platform-launcher:1.8.2")

.. _sdk_6_testsuite_vee_configuration:

Configure the VEE
^^^^^^^^^^^^^^^^^

The VEE used to execute the tests must be declared in the project dependencies,
with the ``microejVee`` or the ``testMicroejVee`` configuration (refer to :ref:`sdk_6_select_veeport` for more details on the selection capabilities).
A VEE declared with the ``microejVee`` configuration is used to run the Application, as well as to execute the testsuites.
The ``microejVee`` is generally used in Application projects, since the tests should run on the same Application target VEE::

   dependencies {
       ...
       microejVee("com.mycompany:vee-port:1.0.0")
   }

A VEE declared with the ``testMicroejVee`` configuration is used only for the testsuites.
It is recommended in Library projects, since they don't need a VEE to run, the VEE is scoped for the tests only::

   dependencies {
       ...
       testMicroejVee("com.mycompany:vee-port:1.0.0")
   }

As a summary, the rules are:

- Only one VEE must be declared globally.
- If the VEE is declared with ``microejVee``, it is used to run the Application (if it is an Application) and to execute the tests.
- If the VEE is declared with ``testMicroejVee``, it is only used to execute the tests.

.. warning::

   Declaring a VEE in project dependencies only applies to the current project. 
   This configuration is not fetched transitively by consumer projects.
   But it is highly recommended to scope the VEE to its usage since this behavior is aimed to change in a future version.
   Especially when configuring the VEE to test a Library project, it is recommended to use ``testMicroejVee``.

Create a Test Class
^^^^^^^^^^^^^^^^^^^

The SDK provides a JUnit library containing the subset of the supported JUnit API: ``ej.library.test:junit``.
Before creating the Test class, make sure this library is declared in the testsuite dependencies:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            ...
            dependencies {
               implementation("ej.library.test:junit:1.11.0")
            }
            ...
         }
      }
   }

The test class can now be created in the ``src/test/java`` folder.
This can be done manually or with IDE menu:
  
.. tabs::

   .. tab:: IntelliJ IDEA / Android Studio

      - right-click on the ``src/test/java`` folder.
      - select :guilabel:`New` > :guilabel:`Java Class`, then press ``Alt`` + ``Insert`` and select ``Test Method``.

   .. tab:: Eclipse

      - right-click on the ``src/test/java`` folder.
      - select :guilabel:`New` > :guilabel:`Other…` > :guilabel:`Java` > :guilabel:`JUnit` > :guilabel:`New JUnit Test Case`.

   .. tab:: Visual Studio Code

      - right-click on the ``src/test/java`` folder in :guilabel:`JAVA PROJECTS` view.
      - select the :guilabel:`+` icon (:guilabel:`New…`) > :guilabel:`Class`, then enter the test class name you want to create.

.. note::

   Gradle allows to define alternative folders for test sources but it would require additional configuration, 
   so it is recommended to stick with the ``src/test/java`` folder.

Execute the Tests
^^^^^^^^^^^^^^^^^

Once the testsuite is configured, it can be run thanks to the ``test`` Gradle task.
This task is bound to the ``check`` and the ``build`` Gradle lifecycle tasks,
which means that the tests are also executed when launching one of these tasks.

.. tabs::

   .. tab:: IntelliJ IDEA / Android Studio

      In order to execute the testsuite from IntelliJ IDEA or Android Studio, double-click on the task in the Gradle tasks view:

      .. figure:: images/intellij-test-gradle-project.png
         :width: 30%
         :align: center

         Run Gradle ``test`` task from IntelliJ IDEA / Android Studio

   .. tab:: Eclipse

      In order to execute the testsuite from Eclipse, double-click on the task in the Gradle tasks view:

      .. figure:: images/eclipse-test-gradle-project.png
         :width: 30%
         :align: center

         Run Gradle ``test`` task from Eclipse


      .. warning::

         By right-clicking on a test class file, the menu proposes :guilabel:`Gradle Test` and :guilabel:`JUnit Test` in the :guilabel:`Run As` entry.

         .. figure:: images/eclipse_run_as_gradle_test.png
            :width: 40%
            :align: center

            Run test as Gradle test in a class right-click menu

         Always use the :guilabel:`Run` > :guilabel:`Gradle Test` entry.

   .. tab:: Visual Studio Code

      In order to execute the testsuite from VS Code, double-click on the task in the Gradle tasks view:

      .. figure:: images/vscode-test-gradle-project.png
         :width: 25%
         :align: center

         Run Gradle ``test`` task from Visual Studio Code


      .. warning::

         Test start buttons (represented as green triangle) may appear on the left side of class and method definitions.
         
         .. figure:: images/vscode_run_test.png
            :width: 30%
            :align: center

            Green triangles are test start buttons

         Running tests from these buttons may fail because they do not use the Gradle Runner by default. To run a test with Gradle, right-click on the green triangle
         and select :guilabel:`Execute Using Profile...`

         .. figure:: images/vscode_execute_using_profile.png
            :width: 30%
            :align: center

            Right-click menu on test start buttons

         and then select :guilabel:`Delegate Test to Gradle`.

         .. figure:: images/vscode_delegate_test_to_gradle.png
            :width: 30%
            :align: center

            Run test class or test method with Gradle

   .. tab:: Command Line Interface

      In order to execute the testsuite from the Command Line Interface, execute this command::

         $ ./gradlew test

.. _sdk_6_test_generate_code_coverage:

Generate Code Coverage
^^^^^^^^^^^^^^^^^^^^^^

To generate the Code Coverage files (``.cc``) for each test, configure the test suite as follows:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {

            ...

            targets {
               all {
                  testTask.configure {
                     doFirst {
                        systemProperties["microej.testsuite.properties.s3.cc.activated"] = "true"
                        systemProperties["microej.testsuite.properties.s3.cc.thread.period"] = "15"
                     }
                  }
               }
            }
         }
      }
   }

Then, to generate an HTML report, see :ref:`sdk6.section.code_coverage_analyzer`.

Filter the Tests
^^^^^^^^^^^^^^^^

Gradle automatically executes all the tests located in the test source folder.
If you want to execute only a subset of these tests, Gradle provides 2 solutions:

- Filtering configuration in the build script file.
- Filtering option in the command line.

The tests filtering configuration must be done in the ``filter`` block of the test task:

.. code-block::

   testing {
      suites {
        val test by getting(JvmTestSuite::class) {

            ...

            targets {
                all {
                    testTask.configure {
                        filter {
                            includeTestsMatching("com.mycompany.*")
                        }
                    }
                }
            }
        }
      }
   }

This example tells Gradle to run the tests located in the ``com.mycompany`` package only.
Other methods are available for test filtering, such as ``excludeTestsMatching`` to exclude tests.
Refer to the `TestFilter <https://docs.gradle.org/current/javadoc/org/gradle/api/tasks/testing/TestFilter.html>`__
documentation for the complete list of available filtering methods.

Gradle also allows to filter the tests from the command line directly, thanks to the ``--tests`` option.
For example, to execute only the tests from the class ``MyTestClass``, run this command::

   ./gradlew test --tests MyTestClass

This can be convenient to quickly execute one test, without requiring a change in the build script file.

.. note::
   The test class referenced by the ``--tests`` option is executed only if it is not excluded in the test 
   configuration in the ``build.gradle.kts`` file. Therefore, make sure to adpat your test configuration 
   when using this option.

Refer to the Gradle `Test filtering <https://docs.gradle.org/current/userguide/java_testing.html#test_filtering>`__
documentation for more details on how to filter the tests and on the available patterns.

.. warning::

   At the moment, only class-level filtering is supported. 
   This means that, for instance, it is not possible to run a single test method within a test class.


.. _sdk_6_testsuite_on_device:

Test on Device
--------------

The SDK allows to execute a testsuite on a device.
This requires to:

- Have a VEE Port which implements the :ref:`BSP Connection <bsp_connection>`.
- Have a device connected to your workstation both for programming the Executable and getting the output traces. 
  Consult your VEE Port specific documentation for setup.
- Start the :ref:`sdk6_tool_serial_to_socket` tool if the VEE Port does not redirect execution traces.

The configuration is similar to the one used to execute a testsuite on the Simulator.

1. Follow the instructions to :ref:`setup a testsuite on the Simulator <sdk_6_testsuite_on_sim>`.

2. In the build script file, replace the line::

      microej.useMicroejTestEngine(this)

   by::

      microej.useMicroejTestEngine(this, TestTarget.EMB)

3. Add the ``import`` statement at the beginning of the file::

      import com.microej.gradle.plugins.TestTarget

4. Add the required properties as follows:

   .. code-block::
   
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this, TestTarget.EMB)
   
            targets {
               all {
                  testTask.configure {
                     doFirst {
                           systemProperties = mapOf(
                              // Enable the build of the Executable
                              "microej.testsuite.properties.deploy.bsp.microejscript" to "true",
                              "microej.testsuite.properties.microejtool.deploy.name" to "deployToolBSPRun",
                              
                              // Configure the TCP/IP address and port if the VEE Port Run script does not redirect execution traces
                              "microej.testsuite.properties.testsuite.trace.ip" to "localhost",
                              "microej.testsuite.properties.testsuite.trace.port" to "5555",
                              // Tell the testsuite engine that the VEE Port Run script redirects execution traces.
                              // Uncomment this line and comment the 2 lines above if the VEE Port supports it.
                              //"microej.testsuite.properties.launch.test.trace.file" to "true"
                           )
                     }
                  }
               }
            }
         }

The properties are:

- ``microej.testsuite.properties.deploy.bsp.microejscript``: enables the build of the Executable. It is required.
- ``microej.testsuite.properties.microejtool.deploy.name``: name of the tool used to deploy the Executable to the board. It is required.
  It is generally set to ``deployToolBSPRun``.
- ``microej.testsuite.properties.launch.test.trace.file``: enables the redirection of the traces in file. If the VEE Port does not have this capability, 
  the :ref:`sdk6_tool_serial_to_socket` tool must be used to redirect the traces to a socket.
- ``microej.testsuite.properties.testsuite.trace.ip``: TCP/IP address used by the :ref:`sdk6_tool_serial_to_socket` tool to redirect traces from the board.
  This property is only required if the VEE Port does not redirect execution traces.
- ``microej.testsuite.properties.testsuite.trace.port``: TCP/IP port used by the :ref:`sdk6_tool_serial_to_socket` tool to redirect traces from the board.
  This property is only required if the VEE Port does not redirect execution traces.

Any other property can be passed to the Test Engine by prefixing it by ``microej.testsuite.properties.``.
For example, to set the the Immortal heap size:

.. code-block::

   systemProperties = mapOf(
      "microej.testsuite.properties.core.memory.immortal.size" to "8192",
      ...
   )


.. _sdk_6_testsuite_on_jse:

Test on Java SE VM
------------------

The SDK allows to run tests on a Java SE VM.
This can be useful, for example, when the usage of mock libraries like ``Mockito`` is 
needed (this kind of library is not supported by the MicroEJ VM).

There is nothing specific related to MicroEJ to run tests on a Java SE VM.
Follow the `Gradle documentation <https://docs.gradle.org/current/userguide/jvm_test_suite_plugin.html>`__ to setup such tests.
As an example, here is a typical configuration to execute the tests located in the ``src/test/java`` folder:

.. code-block::

   testing {
      suites { 
         val test by getting(JvmTestSuite::class) { 
            useJUnitJupiter()

            dependencies {
               runtimeOnly("org.junit.platform:junit-platform-launcher:1.8.2")
            }
         }
      }
   }

If you want to use `Mockito <https://site.mockito.org/>`__, add it in the testsuite dependencies:

.. code-block::

   testing {
      suites { 
         val test by getting(JvmTestSuite::class) { 
            useJUnitJupiter()

            dependencies {
               implementation("org.mockito:mockito-core:4.11.0")
               runtimeOnly("org.junit.platform:junit-platform-launcher:1.8.2")
            }
         }
      }
   }

Then you can use it in your test classes:

.. code-block:: java

   import org.junit.jupiter.api.Test;
   import org.mockito.Mockito;

   import static org.junit.jupiter.api.Assertions.assertNotNull;

   public class MyTest {
      @Test
      public void test() {
         MyClass mock = Mockito.mock(MyClass.class);

         assertNotNull(mock);
      }
   }

.. _sdk_6_testsuite_reports:

Test Suite Reports
------------------

.. tabs::

    .. group-tab:: SDK 6 1.1.0 and higher

        Once a testsuite is completed, the JUnit HTML report is generated in the module project location ``build/reports/tests/<testsuite>/index.html``.

        .. figure:: ../SDK6UserGuide/images/junitHtmlReport.png
           :alt: Example of JUnit HTML Report

           Example of JUnit HTML Report

    .. group-tab:: SDK 6 1.0.0 and below

        Once a testsuite is completed, the JUnit XML report is generated in the module project location ``build/testsuite/output/<date>/testsuite-report.xml``.

        .. figure:: ../SDKUserGuide/images/testsuiteReportXMLExample.png
           :alt: Example of MicroEJ Test Suite XML Report

           Example of MicroEJ Test Suite XML Report

        XML report file can also be opened In Eclipse in the JUnit View.
        Right-click on the file > :guilabel:`Open With` >  :guilabel:`JUnit View`:

        .. figure:: ../SDKUserGuide/images/testsuiteReportXMLExampleJunitView.png
           :alt: Example of MicroEJ Test Suite XML Report in JUnit View

           Example of MicroEJ Test Suite XML Report in JUnit View

.. _sdk_6_publish_testsuite_reports:

Publish Test Suite Reports
^^^^^^^^^^^^^^^^^^^^^^^^^^

Starting from SDK 6 ``1.2.0``, it is possible to publish an archive file containing all testsuite reports of a project.
By default, the tests are not executed when publishing a project, so you must explicitly run your testsuite to publish the reports::

   ./gradlew test publish

The published archive file contains the HTML and XML reports of all testsuites that have been executed.
If your project contains :ref:`multiple testsuites <sdk_6_mixing_testsuites>`, you must execute each testsuite whose report must be published::

   ./gradlew testOnSim testOnJavaSE publish

You can also bind the ``check`` task to all your testsuites in the ``build.gradle.kts`` file of your project::

   tasks.named("check") {
       dependsOn("testOnSim", "testOnJavaSE")
   }

and execute the ``check`` task when publishing the project::

   ./gradlew check publish

.. _sdk_6_mixing_testsuites:

Mixing tests
------------

The SDK allows to define multiple testsuites on different targets.
For example, you can configure a testsuite to run tests on the Simulator and a testsuite to run tests on a device.

Configuring multiple testsuites is almost only a matter of aggregating the testsuite declarations documented in the previous sections,
as described in the `Gradle documentation <https://docs.gradle.org/current/userguide/jvm_test_suite_plugin.html#sec:declare_an_additional_test_suite>`__.

Mixing tests on the Simulator and on a device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you need to define a testsuite to run on the Simulator and a testsuite to run on a device, 
the only point to take care is related to the tests source location, because:

- Gradle automatically uses the testsuite name to know the tests source folder to use.
  For example, for a testsuite named ``test`` (the built-in testsuite), the folder ``src/test/java`` is used,
  and for a testsuite named ``testOnDevice``, the folder ``src/testOnDevice/java`` is used.
- Tests classes executed by the MicroEJ Test Engine on the Simulator and on device are not directly the tests source classes.
  The SDK generates new tests classes, based on the original ones, but compliant with the MicroEJ Test Suite mechanism.
  This process assumes by default that the tests classes are located in the ``src/test/java`` folder.

Therefore:

- It is recommended to use the built-in ``test`` testsuite for either the tests on the Simulator or the tests on device.
  This avoids extra configuration to change the location of the tests source folder.
- The tests source folder of the other testsuite must be changed to use the ``src/test/java`` folder as well:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this)

            dependencies {
               implementation(project())
               implementation("ej.library.test:junit:1.11.0")
            }
         }

         val testOnDevice by registering(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this, TestTarget.EMB)

            sources {
               java {
                  setSrcDirs(listOf(sourceSets.getByName(SourceSet.TEST_SOURCE_SET_NAME).java))
               }
               resources {
                  setSrcDirs(listOf(sourceSets.getByName(SourceSet.TEST_SOURCE_SET_NAME).resources))
               }
            }

            dependencies {
               implementation(project())
               implementation("ej.library.test:junit:1.11.0")
            }

            targets {
                all {
                  testTask.configure {
                     doFirst {
                        systemProperties = mapOf(
                           "microej.testsuite.properties.deploy.bsp.microejscript" to "true",
                           "microej.testsuite.properties.microejtool.deploy.name" to "deployToolBSPRun",
                           "microej.testsuite.properties.testsuite.trace.ip" to "localhost",
                           "microej.testsuite.properties.testsuite.trace.port" to "5555"
                        )
                     }
                  }
               }
            }
         }
      }
   }

The important part is the ``sources`` block of the ``testOnDevice`` testsuite.
This allows to use the ``src/test/java`` and ``src/test/resources`` folders as the tests source folders.

With this configuration, all tests are executed on both the Simulator and the device.
If you want to have different tests for each testsuite, it is recommended to separate the tests in different packages.
For example the tests on the Simulator could be in ``src/test/java/com/mycompany/sim`` 
and the tests on the device could be in ``src/test/java/com/mycompany/emb``.
Then you use the test filtering capabilities to configure which package to run in which testsuite:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            ...

            targets {
                all {
                  testTask.configure {
                     ...

                     filter {
                        includeTestsMatching("com.mycompany.sim.*")
                     }
                  }
               }
            }
         }

         val testOnDevice by registering(JvmTestSuite::class) {
            ...

            targets {
                all {
                  testTask.configure {
                     ...

                     filter {
                        includeTestsMatching("com.mycompany.emb.*")
                     }
                  }
               }
            }
         }
      }
   }

Mixing tests on the Simulator and on a Java SE VM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defining tests on the Simulator and on a Java SE VM is only a matter of aggregating the configuration of each testsuite:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this)
            ...
         }

         val testOnJavaSE by registering(JvmTestSuite::class) {
            useJUnitJupiter()

            dependencies {
               runtimeOnly("org.junit.platform:junit-platform-launcher:1.8.2")
            }

            ...
         }
      }
   }

As explained in the previous section, it is recommended to use the built-in ``test`` testsuite for the tests on the Simulator
since it avoids adding confguration to change the tests sources folder. 
With this configuration, tests on the Simulator are located in the ``src/test/java`` folder, 
and tests on a Java SE VM are located in the ``src/testOnJavaSe/java`` folder.

.. _sdk_6_testsuite_engine_options:

Configure the Testsuite Engine
------------------------------

The engine used to execute the testsuite provides a set of configuration parameters that can be defined with System Properties.
For example, to set the timeout of the tests:

- In the command line with ``-D``::

   ./gradlew test -Dmicroej.testsuite.timeout=120

- In the build script file:

   .. code-block::

      testing {
         suites {
            val test by getting(JvmTestSuite::class) {
               ...

               targets {
                  all {
                     testTask.configure {
                        ...

                        doFirst {
                           systemProperties = mapOf(
                              "microej.testsuite.timeout" to "120"
                           )
                        }
                     }
                  }
               }
            }
         }
      }

The following configuration parameters are available:

.. list-table:: 
   :widths: 25 55 25
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - ``microej.testsuite.timeout``
     - The time in seconds before a test is considered as failed. Set it to ``0`` to disable the timeout.
     - ``60``
   * - ``microej.testsuite.jvmArgs``
     - The arguments to pass to the Java VM started for each test.
     - Not set
   * - ``microej.testsuite.lockPort``
     - The localhost port used by the framework to synchronize its execution with other frameworks on same computer.
       Synchronization is not performed when this port is ``0`` or negative.
     - ``0``
   * - ``microej.testsuite.retry.count``
     - A test execution may not be able to produce the success trace for an external reason,
       for example an unreliable harness script that may lose some trace characters or crop the end of the trace.
       For all these unlikely reasons, it is possible to configure the number of retries before a test is considered to have failed.
     - ``0``
   * - ``microej.testsuite.retry.if``
     - Regular expression checked against the test output to retry the test. 
       If the regular expression is found in the test output, the test is retried (up to the value of ``microej.testsuite.retry.count``).
     - Not set
   * - ``microej.testsuite.retry.unless``
     - Regular expression checked against the test output to retry the test. 
       If the regular expression is not found in the test output, the test is retried (up to the value of ``microej.testsuite.retry.count``).
     - Not set
   * - ``microej.testsuite.verbose.level``
     - Verbose level of the testsuite output. Available values are ``error``, ``warning``, ``info``, ``verbose`` and ``debug``.

       .. deprecated:: 1.2.0

          The testsuite verbose level follows Gradle log level.

     - ``info``
   * - ``microej.testsuite.status.pattern``
     - **since `1.3.0`** Pattern to change test ``PASSED`` and ``FAILED`` tags in testsuite logs.
       This tags are catched by the testsuite engine to determine if a test has passed or failed.
       The ``{}`` placeholder in the pattern will be replaced by respectively ``PASSED`` or ``FAILED`` in order to discriminates theses tags from other test logs.
     - ``.:[{}]:.``

.. _sdk_6_testsuite_application_options:

Inject Application Options
--------------------------

:ref:`application_options` can be defined to configure the Application or Library being tested.
They can be defined globally, to be applied on all tests, or specifically to a test.

Inject Application Options Globally
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In order to define an Application Option globally, 
it must be prefixed by ``microej.testsuite.properties.`` and passed as a System Property,
either in the command line or in the build script file.
For example, to inject the property ``core.memory.immortal.size``:

- In the command line with ``-D``::

   ./gradlew test -Dmicroej.testsuite.properties.core.memory.immortal.size=8192

- In the build script file:

   .. code-block::

      testing {
         suites {
            val test by getting(JvmTestSuite::class) {
               ...

               targets {
                  all {
                     testTask.configure {
                        ...

                        doFirst {
                           systemProperties = mapOf(
                              "microej.testsuite.properties.core.memory.immortal.size" to "8192"
                           )
                        }
                     }
                  }
               }
            }
         }
      }

Inject Application Options For a Specific Test
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In order to define an Application Option for a specific test, 
it must be set in a file with the same name as the test case file,
but with the ``.properties`` extension instead of the ``.java`` extension.
The file must be put in the ``src/test/resources`` folder and within the same package than the test file.

For example, to inject an Application Option for the test class ``MyTest`` located in the ``com.mycompany`` package, 
a ``MyTest.properties`` file must be created. Its path must be: ``src/test/resources/com/mycompany/MyTest.properties``.

Application Options defined in this file do not require the ``microej.testsuite.properties.`` prefix.

.. note::
   If the testsuite is configured to execute main classes (thanks to the parameter ``TestMode.MAIN``)::

      microej.useMicroejTestEngine(this, TestTarget.SIM, TestMode.MAIN)
   
   the properties file must be named after the main class. 
   If the main class has been generated from a JUnit test class, its class name is prefixed by ``_AllTests_``.


Test Suite Advanced Configuration
---------------------------------

.. _sdk_6_vee_configuration_by_testsuite:

Configure a VEE by Test Suite
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The VEE declared in the project dependencies with the ``microejVee`` or the ``testMicroejVee`` configuration 
(refer to :ref:`sdk_6_testsuite_vee_configuration` for more details) is used to execute all test suites. 
If your project contains a test suite other than the built-in ``test`` test suite, 
it is also possible to run the test suite on a dedicated VEE. To define a VEE for your custom testsuite, you must:

- Create a new ``<testsuite_name>MicroejVee`` configuration depending on your test suite name in the ``build.gradle.kts`` file of your project. For example::

   configurations.create("testOnDeviceMicroejVee") {
       isCanBeConsumed = false
       isCanBeResolved = false
       isTransitive = false
   }

- Declare the VEE in the project dependencies with your new configuration::

   dependencies {
       ...
       "testOnDeviceMicroejVee"("com.mycompany:vee-port:1.0.0")
   }

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
