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
     - MicroEJ SDK Direct Wizard
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
--------------

A MicroEJ Add-On Library is a MicroEJ library that is implemented on top of MicroEJ Foundation Libraries (100% full Java code).

**Build type**: ``com.is2t.easyant.buildtypes#build-microej-javalib``

**Configuration**:

This module nature inherits the configuration properties of the following features:

- :ref:`Java Compilation <module_natures.features.compilation>`
- :ref:`Platform Selection <module_natures_platform_selection>`
- :ref:`Javadoc <module_natures.features.javadoc>`
- :ref:`Test Suite <module_natures.features.testsuite>`
- :ref:`Artifact Checker <module_natures.features.artifact_checker>`

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.mock:

Mock
----

A Mock is a jar file containing some Java classes that simulate natives for the Simulator.
Mocks allow applications to be run unchanged in the Simulator while still (apparently) interacting with native code.

**Build type**: ``build-microej-mock``

**Configuration**:

This module nature inherits the configuration properties of the following features:

- :ref:`Java Compilation <module_natures.features.compilation>`
- :ref:`Unit Tests <module_natures.features.unittests>`

Go to the :ref:`Mock <mock_module>` section for more details.

.. _module_natures.module_repository:

Module Repository
-----------------

A module repository is a module that bundles a set of modules in a portable ZIP file.
It is used to contain all the dependencies required to build and package the applications.

**Build type**: ``com.is2t.easyant.buildtypes#build-artifact-repository``

**Configuration**:

This module nature inherits the configuration properties of the following features:

- :ref:`Artifact Checker <module_natures.features.artifact_checker>`

and it also has the following dedicated configuration properties:

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
   * - |question| bar.notification.email.from
     - The email address used as the from address when sending the notification emails.
     - No
     - ``no-reply@microej.com``
   * - |question| bar.notification.email.to
     - The notification email address destination.
     - No
     - ``build-notifications@microej.com``
   * - |question| bar.notification.email.host
     - The hostname of the mail service used to send the notification emails.
     - No
     - ``192.168.2.20``
   * - |question| bar.notification.email.port
     - The port of the mail service used to send the notification emails
     - No
     - ``25``
   * - |question| bar.notification.email.ssl
     - When this property is set to true, SSL/TLS is used to send the notification emails.
     - No
     - ``false``
   * - |question| bar.notification.email.user
     - The username used to authenticate on the mail service.
     - No
     - Empty string
   * - |question| bar.notification.email.password
     - The password used to authenticate on the mail service.
     - No
     - Empty string
   * - skip.email
     - When this property is set (any value), the notification email is not sent.
     - No
     - Not set   
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
     - Path of the folder containing the generated javadoc.
     - No
     - ``${target}/javadoc``
   * - bar.javadoc.stylesheet.file
     - Path of the Stylesheet used for the generated Javadoc.
     - No
     - (To be fixed)

Go to the :ref:`module_repository` section for more details.

.. _module_natures.sandboxed_application:

Sandboxed Application
---------------------

A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a Multi-Sandbox Firmware.
It can be linked either statically or dynamically.
If it is statically linked, it is then called a System Application as it is part of the initial image and cannot be removed.

**Build type**: ``com.is2t.easyant.buildtypes#build-application``

**Configuration**:

This module nature inherits the configuration properties of the following features:

- :ref:`Java Compilation <module_natures.features.compilation>`
- :ref:`Platform Selection <module_natures_platform_selection>`
- :ref:`Javadoc <module_natures.features.javadoc>`
- :ref:`Test Suite <module_natures.features.testsuite>`
- :ref:`Artifact Checker <module_natures.features.artifact_checker>`

Go to the :ref:`sandboxed_application` section for more details.

.. _module_natures.standalone_application:

Standalone Application
----------------------

A MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Firmware.
Such application must define a main entry point, i.e. a class containing a public static void main(String[]) method.

**Build type**: ``com.is2t.easyant.buildtypes#build-firmware-singleapp``

**Configuration**:

This module nature inherits the configuration properties of the following features:

- :ref:`Java Compilation <module_natures.features.compilation>`
- :ref:`Platform Selection <module_natures_platform_selection>`
- :ref:`Test Suite <module_natures.features.testsuite>`
- :ref:`Artifact Checker <module_natures.features.artifact_checker>`

and it also has the following dedicated configuration properties:

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
     - Not set
   * - virtual.device.sim.only
     - When this property is set (any value), the firmware is not built.
     - No
     - Not set
   * - skip.build.virtual.device
     - When this property is set (any value), the virtual device is not created.
     - No
     - Not set

Go to the :ref:`standalone_application` section for more details.

.. _module_natures.addon_processor:

Add-On Processor
----------------

A MicroEJ Add-On Processor is a MicroEJ library that executes operations on sources files.

**Build type**: ``com.is2t.easyant.buildtypes#build-addon-processor``

This module nature inherits the configuration properties of the following features:

- :ref:`Java Compilation <module_natures.features.compilation>`
- :ref:`Unit Tests <module_natures.features.unittests>`
- :ref:`Artifact Checker <module_natures.features.artifact_checker>`

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.meta_build:

Meta Build
----------

A Meta Build is a project allowing to build other projects.

**Build type**: ``com.is2t.easyant.buildtypes#microej-meta-build``

**Configuration**:

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
   * - private.modules.file
     - Name of the file listing the private modules to build.
     - No
     - ``private.modules.list``
   * - public.modules.file
     - Name of the file listing the public modules to build.
     - No
     - ``public.modules.list``

Go to the :ref:`Meta Build <meta_build>` section for more details.

Natures features
----------------

.. _module_natures.features.compilation:

Compilation
^^^^^^^^^^^

The compilation feature is used by several modules natures:

- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.addon_lib`

The following options are available to configure the test:

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - src.main.java
     - Path of the folder containing the Java sources.
     - No
     - ``${basedir}/src/main/java``
   * - |question| javac.debug.mode
     - When this property is set to true, the Java compiler is set in debug mode.
     - No
     - ``false``
   * - |question| javac.debug.level
     - Comma-separated list of levels for the Java compiler debug mode.
     - No
     - ``lines,source,vars``
   * - |question| include.java.runtime
     - When this property is set to true, the JRE runtime libraries are included in the classpath.
     - No
     - ``no``
   * - |question| java.configuration
     - Java core library configuration (edc or cldc).
     - No
     - ``edc``
   * - |question| compile.java.source.version
     - Java version of the sources.
     - No
     - ``1.7`` (edc version)
   * - |question| compile.java.target.version
     - Target Java version.
     - No
     - ``1.7`` (edc version)


.. _module_natures_platform_selection:

MicroEJ Platform Selection
^^^^^^^^^^^^^^^^^^^^^^^^^^

Several modules natures require a MicroEJ Platform for building the module or for running tests:

- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.addon_lib`

There are 4 different ways to provide a MicroEJ Platform for a module project:

-  Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.file`` to the path of a MicroEJ Platform file (``.zip``, ``.jpf`` or ``.vde``).
-  Set the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dir`` to the path of the ``source`` folder of an already imported :ref:`Source Platform <source_platform_import>`.
-  Declare a :ref:`module dependency <mmm_module_dependencies>`:

   .. code:: xml

      <dependency org="myorg" name="myname" rev="1.0.0" conf="platform->default" transitive="false"/>

-  Copy a MicroEJ Platform file to the dropins folder. The default dropins folder location is ``[module_project_dir]/dropins``. It can be changed using the :ref:`build option <mmm_build_options>` ``platform-loader.target.platform.dropins``.

The following options are available to configure the platform loading:

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - platform-loader.platform.dir
     - Path of the folder to unzip the loaded platform to.
     - No
     - ``${target}/platform``
   * - |question| platform.loader.skip.load.platform
     - When this property is set to true, the platform is not loaded.
       If the platform is required for the build, it means it must already be unzipped in the folder defined in the property ``platform-loader.platform.dir``.
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

.. _module_natures.features.javadoc:

Javadoc
^^^^^^^

Javadoc can be generated for several modules natures:

- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.addon_lib`

The following options are available to configure the test:

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - src.main.java
     - Path of the folder containing the Java sources.
     - No
     - ``${basedir}/src/main/java``
   * - javadoc.file.encoding
     - Encoding used for the generated Javadoc.
     - No
     - ``UTF-8``
   * - javadoc.failonerror
     - When this property is set to true, the build is stopped if an error is raised during the Javadoc generation.
     - No
     - ``true``
   * - javadoc.failonwarning
     - When this property is set to true, the build is stopped if a warning is raised during the Javadoc generation.
     - No
     - ``false``
   * - target.reports
     - Path of the base folder for reports.
     - No
     - ``${target}/reports``
   * - target.javadoc
     - Path of the base folder where the Javadoc is generated.
     - No
     - ``${target.reports}/javadoc``
   * - target.javadoc.main
     - Path of the folder where the Javadoc is generated.
     - No
     - ``${target.javadoc}/main``
   * - |question| java.configuration
     - Java core library configuration (edc or cldc).
     - No
     - ``edc``
   * - |question| include.java.runtime
     - When this property is set to true, the JRE runtime libraries are included in the classpath.
     - No
     - ``no``
   * - |question| javadoc.source.version
     - Java version of the sources.
     - No
     - ``1.7`` (edc version)
   * - javadoc-microej.overview.html
     - Path of the HTML template file used for the Javadoc overview page.
     - No
     - ``${src.main.java}/overview.html`` if exists, otherwise a default template.
   * - target.artifacts
     - Path of the packaged artifacts.
     - No
     - ``${target}/artifacts``
   * - target.artifacts.main.javadoc.jar.name
     - Name of the packaged JAR containing the generated Javadoc (stored in folder ``target.artifacts``).
     - No
     - ``${module.name}-javadoc.jar``
   * - javadoc.publish.conf
     - Ivy configuration used to publish the Javadoc artifact.
     - No
     - ``documentation``

.. _module_natures.features.unittests:

Unit tests
^^^^^^^^^^
Unit tests can be added for several modules natures:

- :ref:`module_natures.mock`

The following options are available to configure the test suite:

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - test.run.includes.pattern
     - Pattern of classes included in the test suite execution.
     - No
     - ``**/*`` (all tests)
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test suite execution.
     - No
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the build fails if an error is raised.
     - No
     - ``true``
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - No
     - Not set

.. _module_natures.features.testsuite:

Test Suite on MicroEJ Simulator
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A test suite on MicroEJ Simulator can be added for several modules natures:

- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.addon_lib`

The following options are available to configure the test suite:

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - test.run.includes.pattern
     - Pattern of classes included in the test suite execution.
     - No
     - ``**/*`` (all tests)
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test suite execution.
     - No
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the build fails if an error is raised.
     - No
     - ``true``
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - No
     - Not set
   * - microej.testsuite.cc.excludes.classes
     - Pattern of classes excluded from the code coverage abalysis.
     - No
     - Not set
   * - microej.testsuite.properties.s3.cc.activated
     - When this property is set to true, the code coverage analysis is disabled.
     - No
     - Not set

To learn more about the Test Suite, please to go the :ref:`MicroEJ Test Suite <application_testsuite>` page.

.. _module_natures.features.artifact_checker:

Artifact Checker
^^^^^^^^^^^^^^^^

The Artifact Checker is enabled for several modules natures:

- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.addon_lib`
- :ref:`module_natures.module_repository`

The following options are available to configure the test suite:

.. list-table:: 
   :widths: 20 65 5 10
   :header-rows: 1

   * - Name
     - Description
     - Required
     - Default
   * - skip.artifact.checker
     - When this property is set to true, all artifact checkers are skipped.
     - No
     - Not set
   * - skip.addonconf.checker
     - When this property is set to true, the addon configurations checker is not executed.
     - No
     - Not set
   * - skip.foundationconf.checker
     - When this property is set to true, the foundation configurations checker is not executed.
     - No
     - Not set
   * - skip.publicconf.checker
     - When this property is set to true, the public configurations checker is not executed.
     - No
     - Not set
   * - skip.changelog.checker
     - When this property is set to true, the changelog checker is not executed.
     - No
     - Not set
   * - skip.license.checker
     - When this property is set to true, the license checker is not executed.
     - No
     - Not set
   * - skip.readme.checker
     - When this property is set to true, the readme checker is not executed.
     - No
     - Not set
   * - skip.retrieve.checker
     - When this property is set to true, the retrieve checker is not executed.
     - No
     - Not set


.. |question| unicode:: U+1F914 .. thinking

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
