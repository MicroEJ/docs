Setup a KF Test Suite
=====================

A KF test suite can be executed when building a Foundation Library or an Add-On library, 
and usually extends the tests written for the :ref:`default library test suite <application_testsuite>` to verify the behavior
of this library when its APIs are exposed by a Kernel.

A KF test suite is composed of a set of KF tests, each KF test itself is a minimal Multi-Sandbox Executable composed of a Kernel and zero or more Features.


Enable the Test Suite
---------------------

In an existing library project:

.. tabs::

   .. tab:: SDK 6

      - Create the ``src/test/resources/projects`` directory.
      - Follow the instructions to :ref:`setup a testsuite on the Simulator <sdk_6_testsuite_on_sim>`.
      - In the build script file, replace the line::

            microej.useMicroejTestEngine(this)

      by::

            microej.useMicroejTestEngine(this, TestTarget.EMB, TestMode.PROJECT)
      
      - Add the ``import`` statements at the beginning of the file::

            import com.microej.gradle.plugins.TestMode
            import com.microej.gradle.plugins.TestTarget

      - Add the required properties as follows:

         .. code-block::
   
               val test by getting(JvmTestSuite::class) {
                  microej.useMicroejTestEngine(this, TestTarget.EMB, TestMode.PROJECT)
   
                  targets {
                     all {
                        testTask.configure {
                           doFirst {
                                 systemProperties = mapOf(
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

   .. tab:: SDK 5
  
      - Create the ``src/test/projects`` directory,
      - Edit the ``module.ivy`` and insert the following line within the ``<ea:build>`` XML element:

        ::

          <ea:plugin organisation="com.is2t.easyant.plugins" module="microej-kf-testsuite" revision="+" />
      - Configure the option ``artifacts.resolver`` to the name of the resolver used to import KF test dependencies.  
        The name must be one of the resolver names defined in your :ref:`settings file <mmm_settings_file>`. 
        If you are using the default settings file, set the option to ``MicroEJChainResolver``.
        This option is usually set as a global :ref:`MMM option <mmm_options>`.

Add a KF Test
-------------

A KF test is a structured directory placed in the ``src/test/resources/projects`` directory in SDK 6, or in the ``src/test/projects`` directory in SDK 5.
The creation of a KF is done as follows:

.. tabs::

   .. tab:: SDK 6
      
      - In the ``src/test/java`` folder, create a new Interface with the following content:

      .. code-block:: java

         import org.junit.Test;

         public interface MyTest {

            @Test 
            void newTest();
         }   

      - Within the ``src/test/resources/projects`` directory, create a new directory for the KF test with the same name as the method defined in the Interface.
      
      .. note::
         The name of a KF test is free. For each KF test, a method with the same name and annotated with ``@Test`` must be defined in the Java Interface.

      - Within the KF test, create the sub-projects:
  
        - Create a new ``kernel`` directory and :ref:`create a Kernel <multisandbox_firmware_creation>`. The Kernel must depend on your Library project:

         .. code-block::
   
                implementation("org.example:myLibrary")

         .. note::

            The Library project is used as an included build when running one of its KF tests. Therefore, it is not mandatory to specify the dependency version here.

        - Create a new ``app`` directory and :ref:`create an Application <sdk_6_create_project>`.
        - Create a ``settings.gradle.kts`` file and add the following content:

         .. code-block::
   
               include("kernel", "app")

      Each KF test must contain a Kernel project named ``kernel``. If the KF Test also contains one or more Feature projects, their names must be prefixed by ``app``.

      The KF Test Suite structure shall be similar to the following figure:

      .. figure:: png/kf_testsuite_project_structure_sdk6.png
         :alt: KF Test Suite Structure
         :align: center

         KF Test Suite Overall Structure

   .. tab:: SDK 5
  
      - Create a new directory for the KF test
      - Within this directory, create the sub-projects:
  
        - Create a new directory for the Kernel project and initialize it using the ``microej-javalib`` :ref:`skeleton <mmm_module_skeleton>`,
        - Create a new directory for the Feature project and initialize it using the ``application`` :ref:`skeleton <mmm_module_skeleton>`,
        - Create a new directory for the Firmware project and initialize it using the ``firmware-multiapp`` :ref:`skeleton <mmm_module_skeleton>`.

      The names of the project directories are free, however MicroEJ suggests the following naming convention, assuming the KF test directory is ``[TestName]``:

      - ``[TestName]-kernel`` for the Kernel project, 
      - ``[TestName]-app[1..N]`` for Feature projects,
      - ``[TestName]-firmware`` for the Firmware project. 

      The KF Test Suite structure shall be similar to the following figure:

      .. figure:: png/kf_testsuite_project_structure.png
         :alt: KF Test Suite Structure
         :align: center

         KF Test Suite Overall Structure

      All the projects will be built automatically in the right order based on their dependencies.

KF Test Suite Options (SDK 5 only)
----------------------------------
   
It is possible to configure the same options defined by :ref:`Test Suite Options <testsuite_options>` for the KF test suite, 
by using the prefix ``microej.kf.testsuite.properties`` instead of ``microej.testsuite.properties``.

..
   | Copyright 2020-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
