.. _sdk_6_test_project:

Test a Project
==============

The SDK provides the capabilities to implement and run tests for a project.
It relies on the standard `JUnit`_ API.

There are different types of tests:

- test on the Simulator
- test on a device
- test on a J2SE VM

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

- by using the built-in ``Test`` task, 
  as described in `Testing in Java & JVM projects <https://docs.gradle.org/current/userguide/java_testing.html>`__.
- by using the new ``JVM Test Suite`` plugin, 
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


Configure the Testsuite
~~~~~~~~~~~~~~~~~~~~~~~

The configuration of the testsuites of a project must be defined inside the following block in the ``build.gradle.kts`` file:

.. code-block::

   testing {
      suites { // (1)
         val test by getting(JvmTestSuite::class) { // (2)
            microej.useMicroejTestEngine(this) // (3)

            dependencies { // (4)
                implementation(project())
                implementation("ej.api:edc:1.3.5")
                implementation("ej.library.test:junit:1.7.1")
                implementation("org.junit.platform:junit-platform-launcher:1.8.2")
            }
         }
      }
   }

This piece of configuration is the minimum configuration required to define a testsuite on the Simulator:

- ``(1)``: configures all the testsuites of the project.
- ``(2)``: configures the built-in ``test`` suite provided by Gradle. Use this testsuite to configure the tests on the Simulator.
- ``(3)``: declares that this testsuite uses the MicroEJ Test Engine. By default, the MicroEJ Test Engine executes the tests on the
  Simulator.
- ``(4)``: adds the dependencies required by the tests. The first line declares a dependency to the code of the project.
  The second line declares a dependency on the ``edc`` Library. The third line declares a dependency to the JUnit API used 
  to annotate Java Test classes. Finally the fourth line declares a dependency to a required JUnit library.


Create a Test Class
~~~~~~~~~~~~~~~~~~~

The SDK provides a JUnit library containing the subset of the supported JUnit API: ``ej.library.test:junit``.
Before creating the Test class, make sure this library is declared in the testsuite dependencies:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            ...
            dependencies {
               implementation("ej.library.test:junit:1.7.1")
            }
            ...
         }
      }
   }

The test class can now be created in the ``src/test/java`` folder.
This can be done manually or with IDE menu:
  
.. tabs::

   .. tab:: Eclipse

      - right-click on the ``src/test/java`` folder.
      - select :guilabel:`New` > :guilabel:`Other…` > :guilabel:`Java` > :guilabel:`JUnit` > :guilabel:`New JUnit Test Case`.

   .. tab:: IntelliJ IDEA

      - right-click on the ``src/test/java`` folder.
      - select :guilabel:`New` > :guilabel:`Java Class`, then press ``Alt`` + ``Insert`` and select ``Test Method``.

.. note::

   Gradle allows to define alternative folders for test sources but it would require additional configuration, 
   so it is recommended to stick with the ``src/test/java`` folder.


Setup a VEE Port
~~~~~~~~~~~~~~~~

Before running tests, at least one target VEE Port must be configured using one of the methods described in the :ref:`sdk_6_select_veeport` page.
If several VEE Ports are defined, the testsuite is executed on each of them.


Execute the Tests
~~~~~~~~~~~~~~~~~

Once the testsuite is configured, it can be run thanks to the ``test`` Gradle task::

   gradle test

This task is bound to the ``check`` and the ``build`` Gradle lifecycle tasks,
which means that the tests are also executed when launching one of these tasks.
   
In order to execute the testsuite from Eclipse and IntelliJ IDEA, double-click on the task in the Gradle tasks view:

.. tabs::

   .. tab:: Eclipse

      .. image:: images/eclipse-test-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: IntelliJ IDEA

      .. image:: images/intellij-test-gradle-project.png
         :width: 30%
         :align: center


Filter the Tests
~~~~~~~~~~~~~~~~

Gradle automatically executes all the tests located in the test source folder.
If you want to execute only a subset of these tests, Gradle provides 2 solutions:

- filtering configuration in the build script file
- filtering option in the command line

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

As mentionned earlier, Gradle allows to filter the tests from the command line directly, thanks to the ``--tests`` option::

   gradle check --tests MyTestClass

This can be convenient to quickly execute one test for example, without requiring a change in the build script file.

Refer to the Gradle `Test filtering <https://docs.gradle.org/current/userguide/java_testing.html#test_filtering>`__
documentation for more details on how to filter the tests and on the available patterns.


.. _sdk_6_testsuite_on_device:

Test on Device
--------------

The SDK allows to execute a testsuite on a device.
This requires to:

- have a VEE Port which implements the :ref:`BSP Connection <bsp_connection>`.
- have a device connected to your workstation both for programming the Executable and getting the output traces. 
  Consult your VEE Port specific documentation for setup.
- start the :ref:`tool_serial_to_socket` tool if the VEE Port does not redirect execution traces.

The configuration is similar to the one used to execute a testsuite on the Simulator.
Therefore, the first step is to follow the instructions to :ref:`setup a testsuite on the Simulator <sdk_6_testsuite_on_sim>`.

Then, in the build script file, replace the line::

   microej.useMicroejTestEngine(this)

by::

   microej.useMicroejTestEngine(this, TestTarget.EMB)

And add the ``import`` statement at the beginning of the file::

   import com.microej.gradle.plugins.TestTarget

Finally, add the required properties as follows:

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
                           // Tell the testsuite engine that the VEE Port Run script redirects execution traces
                           "microej.testsuite.properties.launch.test.trace.file" to "true",
                           // Configure the TCP/IP address and port if the VEE Port Run script does not redirect execution traces
                           "microej.testsuite.properties.testsuite.trace.ip" to "localhost",
                           "microej.testsuite.properties.testsuite.trace.port" to "5555"
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
  the :ref:`tool_serial_to_socket` tool must be used to redirect the traces to a socket.
- ``microej.testsuite.properties.testsuite.trace.ip``: TCP/IP address used by the :ref:`tool_serial_to_socket` tool to redirect traces from the board.
  This property is only required if the VEE Port does not redirect execution traces.
- ``microej.testsuite.properties.testsuite.trace.port``: TCP/IP port used by the :ref:`tool_serial_to_socket` tool to redirect traces from the board.
  This property is only required if the VEE Port does not redirect execution traces.

Any other property can be passed to the Test Engine by prefixing it by ``microej.testsuite.properties.``.
For example, to set the the Immortal heap size:

.. code-block::

   systemProperties = mapOf(
      "microej.testsuite.properties.core.memory.immortal.size" to "8192",
      ...
   )


.. _sdk_6_testsuite_on_j2se:

Test on J2SE VM
---------------

The SDK allows to run tests on a J2SE VM.
This can be useful when the usage of mock libraries like `Mockito <https://site.mockito.org/>`__ is needed.

There is nothing specific related to MicroEJ to run tests on a J2SE VM.
Follow the `Gradle documentation <https://docs.gradle.org/current/userguide/jvm_test_suite_plugin.html>`__ to setup such tests.
As an example, here is a typical configuration to execute the tests located in the ``src/test/java`` folder:

.. code-block::

   testing {
      suites { 
         val test by getting(JvmTestSuite::class) { 
            useJUnitJupiter()
         }
      }
   }


Test Suite Reports
------------------

Once a testsuite is completed, the JUnit XML report is generated in the module project location ``build/testsuite/output/<date>/testsuite-report.xml``.

  .. figure:: ../SDKUserGuide/images/testsuiteReportXMLExample.png
     :alt: Example of MicroEJ Test Suite XML Report
     
     Example of MicroEJ Test Suite XML Report
  
  XML report file can also be opened In Eclipse in the JUnit View. 
  Right-click on the file > :guilabel:`Open With` >  :guilabel:`JUnit View`:

  .. figure:: ../SDKUserGuide/images/testsuiteReportXMLExampleJunitView.png
     :alt: Example of MicroEJ Test Suite XML Report in JUnit View
     
     Example of MicroEJ Test Suite XML Report in JUnit View


.. _sdk_6_mixing_testsuites:

Mixing tests
------------

The SDK allows to define multiple testsuites on different targets.
For example, you can configure a testsuite to run tests on the Simulator and a testsuite to run tests on a device.

Configuring multiple testsuites is almost only a matter of aggregating the testsuite declarations documented in the previous sections,
as described in the `Gradle documentation <https://docs.gradle.org/current/userguide/jvm_test_suite_plugin.html#sec:declare_an_additional_test_suite>`__.

Mixing tests on the Simulator and on a device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you need to define a testsuite to run on the Simulator and a testsuite to run on a device, 
the only point to take care is related to the tests source location, because:

- Gradle automatically uses the testsuite name to know the tests source folder to use.
  For example, for a testsuite named ``test`` (the built-in testsuite), the folder ``src/test/java`` is used,
  and for a testsuite named ``testOnDevice``, the folder ``src/testOnDevice/java`` is used.
- Tests classes executed by the MicroEJ Test Engine on the Simulator and on device are not directly the tests source classes.
  The SDK generates new tests classes, based on the original ones, but compliant with the MicroEJ Test Suite mechanism.
  This process assumes by default that the tests classes are located in the ``src/test/java`` folder.

Therefore:

- it is recommended to use the built-in ``test`` testsuite for either the tests on the Simulator or the tests on device.
  This avoids extra configuration to change the location of the tests source folder.
- the tests source folder of the other testsuite must be changed to use the ``src/test/java`` folder as well:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this)

            dependencies {
               implementation(project())
               implementation("ej.library.test:junit:1.7.1")
               implementation("org.junit.platform:junit-platform-launcher:1.8.2")
            }
         }

         val testOnDevice by registering(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this, TestTarget.EMB)

            sources {
               java {
                  setSrcDirs(listOf("src/test/java"))
               }
               resources {
                  setSrcDirs(listOf("src/test/resources"))
               }
            }

            dependencies {
               implementation(project())
               implementation("ej.library.test:junit:1.7.1")
               implementation("org.junit.platform:junit-platform-launcher:1.8.2")
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

Mixing tests on the Simulator and on a J2SE VM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Defining tests on the Simulator and on a J2SE VM is only a matter of aggregating the configuration of each testsuite:

.. code-block::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this)
            ...
         }

         val testOnJ2SE by registering(JvmTestSuite::class) {
            useJUnitJupiter()
            ...
         }
      }
   }

As explained in the previous section, it is recommended to use the built-in ``test`` testsuite for the tests on the Simulator
since it avoids adding confguration to change the tests sources folder. 
With this configuration, tests on the Simulator are located in the ``src/test/java`` folder, 
and tests on a J2SE VM are located in the ``src/testOnJ2SE/java`` folder.

.. _sdk_6_testsuite_options:

Inject Application Options
--------------------------

:ref:`application_options` can be defined to configure the Application or Library being tested.
They can be defined globally, to be applied on all tests, or specifically to a test.

Inject Application Options Globally
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to define an Application Option globally, 
it must be prefixed by ``microej.testsuite.properties.`` and passed as a System Property,
either in the command line or in the build script file.
For example to inject the property ``core.memory.immortal.size``:

- in the command line with ``-D``::

   gradle test -Dmicroej.testsuite.properties.core.memory.immortal.size=8192

- in the build script file:

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to define an Application Option for a specific test, 
it must set in a file with the same name as the generated test case file, 
but with the ``.properties`` extension instead of the ``.java`` extension. 
The file must be put in the ``src/test/resources`` folder and within the same package than the test file.
For example, to inject a Application Option for the test class ``com.mycompany.MyTest``, 
it must be set in a file named ``src/test/resources/com.mycompany/MyTest.properties``.


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
