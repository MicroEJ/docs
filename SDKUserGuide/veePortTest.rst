.. _veeport_test:

===============
Test a VEE Port
===============

VEE Port Qualification
======================

The SDK provides the capability to test a VEE Port.
While you can create your own tests (see :ref:`create_junit_vee_port_testsuite`), 
MicroEJ provides a set of tools and pre-defined projects aimed at simplifying the steps for validating VEE Ports 
in the form of the :ref:`VEE Port Qualification Tools (PQT) <veeport_qualification>`.

Please refer to the `VEE Port Qualification Tools README <https://github.com/MicroEJ/VEEPortQualificationTools>`__ 
to learn how to setup and run this Qualification process.


.. _create_junit_vee_port_testsuite:

Create a VEE Port Test Suite
============================

A VEE Port Test Suite is composed of two projects:

- the Test Suite module: the project that contains test cases. Test cases are written in :ref:`Junit <application_testsuite>`.
  When this project is built, it produces a versionned library. See :ref:`test_suite_versioning` for available Test Suite modules for the most common Packs provided by MicroEJ Corp.
- the Test Suite runner: the project that contains the configuration for its execution on a VEE Port. 
  When this project is built, it runs the Test Suite on a Device and generates the Test Suite report.

.. note:: 
  
   Creating a VEE Port Test Suite requires SDK ``5.6.0`` or higher.


Create the Test Suite Module
----------------------------

The Test Suite module contains the tests of the Foundation Library to be qualified.

Create the Test Suite Module Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A new Test Suite module is created using the ``microej-javaimpl`` Skeleton (see :ref:`module_natures.foundation_lib_impl`).

To create the Test Suite module, click on: :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...` then select :guilabel:`MicroEJ` > :guilabel:`Module Project`

Fill up the following fields of the form:

- Project name (e.g: ``myFoundationLib-testsuite``).
- Organization (e.g: ``com.mycompany``).
- Module (e.g: ``myFoundationLib-testsuite``).
- Revision (version of your Test Suite module).
- Select the Skeleton: ``microej-javaimpl``.

Then, create two test source folders: 

- Right-click on your project.
- Click on: :guilabel:`New` > :guilabel:`Source Folder`.
- Fill up the ``Folder name`` field of the form with: ``src/test/java`` and for the second folder: ``src/test/resources``.

You should get a Foundation Library Test Suite project that looks like:

   .. figure:: images/foundation-library-testsuite-skeleton.png
      :alt: Foundation Library Test Suite Project Skeleton
      :align: center

      Foundation Library Test Suite Project Skeleton
      
Your Test Suite module project is created and ready to be setup.

Configure the Test Suite Module Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Open the ``module.ivy`` file and follow steps below:

- Edit the module ``ivy-module > info > ea:build`` node to update ``rip.printableName``:
  
  .. code-block:: XML
  
		<ea:build organisation="com.is2t.easyant.buildtypes" module="build-microej-javaimpl" microej.lib.name="myFoundationLib-testsuite-1.0" rip.printableName="myFoundationLib Test Suite Impl" revision="5.2.+">
  
- Add the following properties in the ``ivy-module > info`` node:
  
  .. code-block:: XML

		<ea:property name="skip.test" value="set"/>
		<ea:property name="target.main.classes" value="${basedir}/target~/test/classes"/>
		<ea:property name="addon-processor.src.test.java.path.ref.name" value="src.java.path"/>
  
- Update the JUnit dependency to: 

  .. code-block:: XML

		<dependency org="ej.library.test" name="junit" rev="1.7.1" conf="default;test->*"/>

- Add a ``module.ant`` file at the root of the Test Suite project with the following content:

  .. code-block:: XML

		<project>
			<target name="BuildTestTarget" extensionOf="abstract-compile:compile-ready" depends="resources-std:copy-test-resources">
				<augment id="src.java.path">
					<path location="${basedir}/src/test/java" />
					<path location="${target}/adpgenerated/src-adpgenerated/junit/java"/>
				</augment>
			</target>
		</project>

.. note:: An error on ``module.ant`` file can occurred with message ``Target resources-std:copy-test-resources does not exist in this project``. Please ignore it. 

Create a New Test Case
~~~~~~~~~~~~~~~~~~~~~~

Right click on ``src/test/java``, then click on :guilabel:`New` > :guilabel:`Class`. Fill ``Name:`` with the ``MyTest`` 
and then click on ``Finish``. Copy/paste the following example in ``MyTest.java`` file:

.. code-block:: java

        import org.junit.Assert;
        import org.junit.Test;

        public class MyTest {

        	@Test
                public static void Test() {
        		Assert.assertTrue(true);
                }
        }

The console output on the Simulator for this test should be:

:: 

        =============== [ Initialization Stage ] ===============
        =============== [ Launching on Simulator ] ===============
        OK: Test
        PASSED: 1
        =============== [ Completed Successfully ] ===============

        SUCCESS

Build the Test Suite Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once the test cases are implemented, you can :ref:`build the module <mmm_module_build>`.
The next step is to create a Test Suite Runner.
The Test Suite Runner will fetch the Test Suite Module dependency.

Create the Test Suite Runner
----------------------------

The Test Suite runner project contains configuration files for running a Test Suite module on a Device using a VEE Port.

Create the Test Suite Runner Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- To create the Test Suite runner project, click on: :guilabel:`File` > :guilabel:`New` > :guilabel:`Other...` > :guilabel:`MicroEJ` > :guilabel:`Module Project`.

- Fill up the following fields of the form:

  - Project name
  - Organization
  - Module
  - Revision (version of your Test Suite module)
  - Select the Skeleton: ``microej-testsuite``

- Inside the ``module.ivy`` file, add the dependency to the Test Suite module as following:
  
  .. code-block:: XML
        
        <dependency org="com.mycompany" name="myFoundationLib-testsuite" rev="0.1.0" conf="test->default;provided->provided"/>

- Inside the ``module.ant``, add the following ANT target to configure trace redirection options :
  
  .. code-block:: XML

        <target name="tracefile:init" extensionOf="abstract-test:test-ready">
        	<!-- Set the launch.test.trace.file when the testsuite.trace.ip properties is not set -->
        	<condition property="microej.testsuite.properties.launch.test.trace.file">
        		<not>
        			<isset property="microej.testsuite.properties.testsuite.trace.ip" />
        		</not>
        	</condition>
        </target>

- Create the file ``override.module.ant`` at the root of the project. Add the following content to configure the load of testsuite options:
  
  .. code-block:: XML
  
        <project name="myFoundationlib.testsuite.override" xmlns:ac="antlib:net.sf.antcontrib">
                <!-- Load options from 'local.properties' beside this file -->
                <ac:if>
                        <available file="local.properties" type="file"/>
                        <ac:then>
                                <property file="local.properties"/>
                        </ac:then>
                </ac:if>
                <!-- Load options from 'config.properties' beside this file -->
                <property file="config.properties"/>
        </project>


- Create the following ``.properties`` files:

  - ``{PROJECT_LOC}/validation/microej-testsuite-common.properties``: see `microej-testsuite-common.properties template <https://github.com/MicroEJ/VEEPortQualificationTools/blob/2.9.0/tests/core/java-testsuite-runner-core/validation/microej-testsuite-common.properties>`_.
  - ``{PROJECT_LOC}/config.properties``: see `config.properties template <https://github.com/MicroEJ/VEEPortQualificationTools/blob/2.9.0/tests/core/java-testsuite-runner-core/config.properties.tpl>`_.

.. note:: ``{PROJECT_LOC}`` refers here to the location of your Test Suite runner project.

.. _run_test_suite_on_device:

Configure and Run the Test Suite
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Follow the :ref:`run_fs_test_suite_on_esp32_wrover` tutorial to configure your VEE Port and run the Test Suite on your Device.

.. toctree::
   :hidden:

   runFsTestSuiteOnESP32WROVER

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
