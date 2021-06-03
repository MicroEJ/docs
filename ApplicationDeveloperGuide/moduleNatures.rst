.. _module_natures:

Module Natures
==============

This page describes the most common MicroEJ Module Natures.
A description is available for each of them, as well as their :ref:`project skeleton <mmm_module_skeleton>` name, build type name and configuration properties.

Configuration properties can be defined by adding a ``ea:property`` tag inside the ``ea:build`` tag in the file ``module.ivy`` of the module, as described in the section :ref:`mmm_build_options`.

.. _module_nature_skeleton_mapping:

.. list-table:: MicroEJ Module Natures Summary
   :widths: 20 20 20 40
   :header-rows: 1

   * - Module Nature
     - Skeleton Name
     - Build Type Name
     - Direct Wizard
   * - :ref:`Add-On Library <module_natures.addon_lib>`
     - microej-javalib
     - build-microej-javalib
     - :guilabel:`File` > :guilabel:`New` > :guilabel:`Add-On Library Project`
   * - :ref:`Mock <module_natures.mock>`
     - microej-mock
     - build-microej-mock
     - 
   * - :ref:`Module Repository <module_natures.module_repository>`
     - artifact-repository
     - build-artifact-repository
     - 
   * - :ref:`Sandboxed Application <module_natures.sandboxed_application>`
     - application
     - build-application
     - :guilabel:`File` > :guilabel:`New` > :guilabel:`Sandboxed Application Project`
   * - :ref:`Standalone Application <module_natures.standalone_application>`
     - firmware-singleapp
     - build-firmware-singleapp
     - :guilabel:`File` > :guilabel:`New` > :guilabel:`Standalone Application Project`
   * - :ref:`Addon Processor <module_natures.addon_processor>`
     - addon-processor
     - build-addon-processor
     - 

   * - :ref:`Meta Build <module_natures.meta_build>`
     - microej-meta-build
     - microej-meta-build
     - 

.. _module_natures.addon_lib:

Add-On Library
~~~~~~~~~~~~~~

A MicroEJ Add-On Library is a MicroEJ library that is implemented on top of MicroEJ Foundation Libraries (100% full Java code).

**Build type**: ``com.is2t.easyant.buildtypes#build-microej-javalib``

**Inputs**:

- the Java sources of the library in ``src/main/java``
- *(Optional)* the Java sources of the tests in ``src/test/java``

**Outputs**:

- a JAR file containing the compiled Java code

**Configuration properties:**

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - test.run.includes.pattern
     - Pattern of classes included in the test execution.
     - No
     - ``**/*`` (all tests)
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test execution.
     - No
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the tests are not executed.
     - No
     - ``true``
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - No
     - Not set
   * - microej.testsuite.properties.s3.cc.activated
     - When this property is set to true, the code coverage analysis is disabled.
     - No
     - Not set

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.mock:

Mock
~~~~

A Mock is a jar file containing some Java classes that simulate natives for the Simulator.
Mocks allow applications to be run unchanged in the Simulator while still (apparently) interacting with native code.

**Inputs**:

- the Java sources of the mock in ``src/main/java``
- *(Optional)* the Java sources of the tests in ``src/test/java``

**Outputs**:

- a RIP archive file of the mock

**Configuration properties:**

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - test.run.includes.pattern
     - Pattern of classes included in the test execution.
     - No
     - ``**/*`` (all tests)
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test execution.
     - No
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the tests are not executed.
     - No
     - ``true``
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - No
     - Not set
   * - microej.testsuite.properties.s3.cc.activated
     - When this property is set to true, the code coverage analysis is disabled.
     - No
     - Not set


Go to the :ref:`Mock <mock_module>` section for more details.

.. _module_natures.module_repository:

Module Repository
~~~~~~~~~~~~~~~~~

A module repository is a module that bundles a set of modules in a portable ZIP file.
It is used to contain all the dependencies required to build and package the applications.

**Build type**: ``com.is2t.easyant.buildtypes#build-artifact-repository``

**Inputs**:

- a list of dependencies declared in the ``module.ivy`` file

**Outputs**:

- an archive of the Ivy repository containing all the declared dependencies and the related Ivy settings file

**Configuration properties:**

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - bar.populate.repository.conf
     - Ivy configuration of included repositories. 
       The modules of the repositories declared as dependency with this configuration are included in the built repository.
     - No
     - ``repository``
   * - bar.populate.ivy.settings.file
     - Path of the Ivy settings file used to fetch the modules to populate the repository.
     - No
     - ``${project.ivy.settings.file}``
   * - skip.artifact.checker
     - When this property is set (any value), the artifact checker is not executed
     - No
     - Not set
   * - bar.populate.from.resolver
     - Name of the resolver used to fetch the modules to populate the repository.
     - No
     - ``fetchRelease``
   * - bar.test.haltonerror
     - When this property is set to true, the artifact checker stops at the first error.
     - No
     - ``false``
   * - bar.check.as.v2.module
     - When this property is set to true, the artifact checker uses the MicroEJ Module Manager semantic.
     - No
     - ``false``
   * - bar.notification.email.from
     - The email address used as the from address when sending the notification emails.
     - No
     - ``no-reply@microej.com``
   * - bar.notification.email.to
     - The notification email address destination.
     - No
     - ``build-notifications@microej.com``
   * - bar.notification.email.host
     - The hostname of the mail service used to send the notification emails.
     - No
     - ``192.168.2.20``
   * - bar.notification.email.port
     - The port of the mail service used to send the notification emails
     - No
     - ``25``
   * - bar.notification.email.ssl
     - When this property is set to true, SSL/TLS is used to send the notification emails.
     - No
     - ``false``
   * - bar.notification.email.user
     - The username used to authenticate on the mail service.
     - No
     - Empty string
   * - bar.notification.email.password
     - The password used to authenticate on the mail service.
     - No
     - Empty string
   * - javadoc.includes
     - Comma-separated list of packages to include in the javadoc.
     - No
     - ``**`` (all packages)
   * - javadoc.excludes
     - Comma-separated list of packages to exclude from the javadoc.
     - No
     - Empty string
   * - skip.javadoc.deprecated
     - Prevents the generation of any deprecated API at all in the javadoc.
     - No
     - ``true``
   * - bar.javadoc.dir
     - Path of the directory containing the generated javadoc.
     - No
     - ``${target}/javadoc``
   * - bar.javadoc.stylesheet.file
     - Path of the Stylesheet used for the generated Javadoc.
     - No
     - (To be fixed)


Go to the :ref:`module_repository` section for more details.

.. _module_natures.sandboxed_application:

Sandboxed Application
~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a Multi-Sandbox Firmware.
It can be linked either statically or dynamically.
If it is statically linked, it is then called a System Application as it is part of the initial image and cannot be removed.

Go to the :ref:`sandboxed_application` section for more details.

.. _module_natures.standalone_application:

Standalone Application
~~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Firmware.
Such application must define a main entry point, i.e. a class containing a public static void main(String[]) method.

**Build type**: ``com.is2t.easyant.buildtypes#build-firmware-singleapp``

**Inputs**:

- the Java sources of the application in ``src/main/java``, containing at least a ``main`` class
- the :ref:`application resources <chapter.microej.applicationResources>` in ``src/main/resources`` (images, fonts, ...)
- a platform, provided by one of the ways described in the chapter :ref:`module_natures_platform_selection`
- one or more properties files in the ``build`` folder for the application configuration
- *(Optional)* the Java sources of the tests in ``src/test/java``

**Outputs:**

- the application firmware
- a virtual device, allowing to run the application in Simulation mode
- the SOAR Map file
- the SOAR information file

**Configuration properties:**

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - application.main.class
     - Full Qualified Name of the main class of the application.
     - Yes
     -
   * - virtual.device.sim.only
     - When this property is set (any value), the firmware is not built.
     - No
     - Not set
   * - skip.build.virtual.device
     - When this property is set (any value), the virtual device is not created.
     - No
     - Not set
   * - platform-loader.platform.dir
     - Path of the directory to unzip the loaded platform to.
     - No
     - ``${target}/platform``
   * - platform.loader.skip.load.platform
     - When this property is set to true, the platform is not loaded. 
       If the platform is required for the build, it means it must already be unzipped in the directory defined in the property ``platform-loader.platform.dir``.
     - No
     - ``false``
   * - platform-loader.target.platform.conf
     - The Ivy configuration used to retrieved the platform if fetched via dependencies.
     - No
     - ``platform``     
   * - platform-loader.target.platform.dropins
     - Absolute or relative (to the project root folder) path of the folder where the platform can be found (see :ref:`module_natures_platform_selection`).
     - No
     - ``dropins`` 


Go to the :ref:`standalone_application` section for more details.

.. _module_natures.addon_processor:

Add-On Processor
~~~~~~~~~~~~~~~~

A MicroEJ Add-On Processor is a MicroEJ library that executes operations on sources files.

**Build type**: ``com.is2t.easyant.buildtypes#build-addon-processor``

**Inputs**:

- the Java sources of the application in ``src/main/java``, containing at least a class implementing the interface ``ej.tool.addon.AddonProcessor``
- a file named ``ej.tool.addon.AddonProcessor`` in the folder ``src/main/resources/META-INF/services`` containing the FQN of the class implementing the interface ``ej.tool.addon.AddonProcessor``

**Outputs**:

- an archive with the ``adp`` extension containing the compiled Java code as a jar, as well as all the dependencies

**Configuration properties:**

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - dependencies.retrieve.conf
     - Comma-separated list of Ivy configurations used to fetch the Addon Processor dependencies.
     - No
     - ``default,embedded``


Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.meta_build:

Meta Build
~~~~~~~~~~

A Meta Build is a project allowing to build other projects.

**Build type**: ``com.is2t.easyant.buildtypes#microej-meta-build``

**Inputs**:

- a file ``private.modules.list`` listing the names of the modules to build but not pusblish
- a file ``public.modules.list`` listing the names of the modules to build and pusblish

**Outputs**:

*Declared modules built, no dedicated output.*

**Configuration properties:**

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - metabuild.root
     - Path of the root folder containing the modules to build.
     - No
     - ``${basedir}/..``
   * - metabuild.module.filename
     - Name of the Ivy file of the meta-build module.
     - No
     - ``module.ivy``
   * - private.modules.file
     - Name of the file listing the private modules to build.
     - No
     - ``private.modules.list``
   * - public.modules.file
     - Name of the file listing the public modules to build.
     - No
     - ``public.modules.list``


.. _module_natures_platform_selection:

MicroEJ Platform Selection
~~~~~~~~~~~~~~~~~~~~~~~~~~

Many modules natures require a MicroEJ Platform for building the module or for running tests.

There are 4 different ways to provide a MicroEJ Platform for a module project:

-  Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.file`` to the path of a MicroEJ Platform file (``.zip``, ``.jpf`` or ``.vde``).
-  Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dir`` to the path of the ``source`` folder of an already imported :ref:`Source Platform <source_platform_import>`.
-  Declare a :ref:`module dependency <mmm_module_dependencies>`:

   .. code:: xml

      <dependency org="myorg" name="myname" rev="1.0.0" conf="platform->default" transitive="false"/>

-  Copy a MicroEJ Platform file to the dropins folder. The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dropins``.


..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
