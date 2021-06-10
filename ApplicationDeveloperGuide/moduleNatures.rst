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
   * - :ref:`Foundation Library API <module_natures.foundation_lib_api>`
     - microej-javaapi
     - build-microej-javaapi
     - 
   * - :ref:`Foundation Library Implementation <module_natures.foundation_lib_impl>`
     - microej-javaimpl
     - build-microej-javaimpl
     - 
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

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.javadoc`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.addon_processor:

Add-On Processor
----------------

A MicroEJ Add-On Processor is a MicroEJ library that executes operations on sources files.

**Build type**: ``com.is2t.easyant.buildtypes#build-addon-processor``

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.unittests`
- :ref:`module_natures.plugins.artifact_checker`

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.foundation_lib_api:

Foundation Library API
----------------------

A MicroEJ Foundation Library API is a MicroEJ Core library that provides core runtime APIs or hardware-dependent functionality.

**Build type**: ``com.is2t.easyant.buildtypes#build-microej-javaapi``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.javadoc`
- :ref:`module_natures.plugins.artifact_checker`

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.foundation_lib_impl:

Foundation Library Implementation
---------------------------------

A MicroEJ Foundation Library Implementation is a MicroEJ Core library that implements a MicroEJ Foundation Library API.

**Build type**: ``com.is2t.easyant.buildtypes#build-microej-javaimpl``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.testsuite`

and it also has the following dedicated configuration properties:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - |question| microej.lib.implfor
     - Target VM of the Library Implementation.
       Possible values are `emb` (only embedded), `sim` (only simulator) and `common` (both embedded and simulator).
     - ``common``

Go to the :ref:`MicroEJ Libraries <libraries>` section for more details.

.. _module_natures.meta_build:

Meta Build
----------

A Meta Build is a project allowing to build other projects.

**Build type**: ``com.is2t.easyant.buildtypes#microej-meta-build``

**Configuration**:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - metabuild.root
     - Path of the root folder containing the modules to build.
     - ``${basedir}/..``
   * - private.modules.file
     - Name of the file listing the private modules to build.
     - ``private.modules.list``
   * - public.modules.file
     - Name of the file listing the public modules to build.
     - ``public.modules.list``

Go to the :ref:`Meta Build <meta_build>` section for more details.

.. _module_natures.mock:

Mock
----

A Mock is a jar file containing some Java classes that simulate natives for the Simulator.
Mocks allow applications to be run unchanged in the Simulator while still (apparently) interacting with native code.

**Build type**: ``build-microej-mock``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.unittests`

Go to the :ref:`Mock <mock_module>` section for more details.

.. _module_natures.module_repository:

Module Repository
-----------------

A module repository is a module that bundles a set of modules in a portable ZIP file.
It is used to contain all the dependencies required to build and package the applications.

**Build type**: ``com.is2t.easyant.buildtypes#build-artifact-repository``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.artifact_checker`

and it also has the following dedicated configuration properties:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - bar.populate.repository.conf
     - Ivy configuration of included repositories. 
       The modules of the repositories declared as dependency with this configuration are included in the built repository.
     - ``repository``
   * - bar.populate.ivy.settings.file
     - Path of the Ivy settings file used to fetch the modules to populate the repository.
     - ``${project.ivy.settings.file}``
   * - bar.populate.from.resolver
     - Name of the resolver used to fetch the modules to populate the repository.
     - ``fetchRelease``
   * - bar.test.haltonerror
     - When this property is set to true, the artifact checker stops at the first error.
     - ``false``
   * - bar.check.as.v2.module
     - When this property is set to true, the artifact checker uses the MicroEJ Module Manager semantic.
     - ``false``
   * - |question| bar.notification.email.from
     - The email address used as the from address when sending the notification emails.
     - ``no-reply@microej.com``
   * - |question| bar.notification.email.to
     - The notification email address destination.
     - ``build-notifications@microej.com``
   * - |question| bar.notification.email.host
     - The hostname of the mail service used to send the notification emails.
     - ``192.168.2.20``
   * - |question| bar.notification.email.port
     - The port of the mail service used to send the notification emails
     - ``25``
   * - |question| bar.notification.email.ssl
     - When this property is set to true, SSL/TLS is used to send the notification emails.
     - ``false``
   * - |question| bar.notification.email.user
     - The username used to authenticate on the mail service.
     - Empty string
   * - |question| bar.notification.email.password
     - The password used to authenticate on the mail service.
     - Empty string
   * - skip.email
     - When this property is set (any value), the notification email is not sent.
     - Not set   
   * - javadoc.includes
     - Comma-separated list of packages to include in the javadoc.
     - ``**`` (all packages)
   * - javadoc.excludes
     - Comma-separated list of packages to exclude from the javadoc.
     - Empty string
   * - skip.javadoc.deprecated
     - Prevents the generation of any deprecated API at all in the javadoc.
     - ``true``
   * - bar.javadoc.dir
     - Path of the folder containing the generated javadoc.
     - ``${target}/javadoc``
   * - bar.javadoc.stylesheet.file
     - Path of the Stylesheet used for the generated Javadoc.
     - (To be fixed)
   * - skip.artifact.checker
     - When this property is set to true, all artifact checkers are skipped.
     - Not set

Go to the :ref:`module_repository` section for more details.

.. _module_natures.sandboxed_application:

Sandboxed Application
---------------------

A MicroEJ Sandboxed Application is a MicroEJ Application that can run over a Multi-Sandbox Firmware.
It can be linked either statically or dynamically.
If it is statically linked, it is then called a System Application as it is part of the initial image and cannot be removed.

**Build type**: ``com.is2t.easyant.buildtypes#build-application``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.javadoc`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

Go to the :ref:`sandboxed_application` section for more details.

.. _module_natures.standalone_application:

Standalone Application
----------------------

A MicroEJ Standalone Application is a MicroEJ Application that is directly linked to the C code to produce a MicroEJ Firmware.
Such application must define a main entry point, i.e. a class containing a public static void main(String[]) method.

**Build type**: ``com.is2t.easyant.buildtypes#build-firmware-singleapp``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

and it also has the following dedicated configuration properties:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - application.main.class
     - Full Qualified Name of the main class of the application. This options is required.
     - Not set
   * - virtual.device.sim.only
     - When this property is set (any value), the firmware is not built.
     - Not set
   * - skip.build.virtual.device
     - When this property is set (any value), the virtual device is not created.
     - Not set

Go to the :ref:`standalone_application` section for more details.

Natures plugins
---------------

.. _module_natures.plugins.compilation:

Java Compilation
^^^^^^^^^^^^^^^^

The compilation feature is used by several modules natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.foundation_lib_impl`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`

The following options are available to configure the test:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - src.main.java
     - Path of the folder containing the Java sources.
     - ``${basedir}/src/main/java``
   * - |question| javac.debug.mode
     - When this property is set to true, the Java compiler is set in debug mode.
     - ``false``
   * - |question| javac.debug.level
     - Comma-separated list of levels for the Java compiler debug mode.
     - ``lines,source,vars``
   * - |question| include.java.runtime
     - When this property is set to true, the JRE runtime libraries are included in the classpath.
     - ``no``
   * - |question| java.configuration
     - Java core library configuration (edc or cldc).
     - ``edc``
   * - |question| compile.java.source.version
     - Java version of the sources.
     - ``1.7`` (edc version)
   * - |question| compile.java.target.version
     - Target Java version.
     - ``1.7`` (edc version)


.. _module_natures.plugins.platform_loader:

Platform Loader
^^^^^^^^^^^^^^^

Several modules natures require a MicroEJ Platform for building the module or for running tests:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`


The following options are available to configure the platform loading:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - platform-loader.target.platform.file
     - Path of the platform file to use in the build. See :ref:`platform_selection` section for Platform Selection rules.
     - Not set
   * - platform-loader.target.platform.dir
     - Path of the root folder of the platform to use in the build. See :ref:`platform_selection` section for Platform Selection rules.
     - Not set
   * - platform-loader.platform.dir
     - Path of the folder to unzip the loaded platform to.
     - ``${target}/platform``
   * - |question| platform.loader.skip.load.platform
     - When this property is set to true, the platform is not loaded.
       If the platform is required for the build, it means it must already be unzipped in the folder defined in the property ``platform-loader.platform.dir``.
     - ``false``
   * - platform-loader.target.platform.conf
     - The Ivy configuration used to retrieved the platform if fetched via dependencies.
     - ``platform``     
   * - platform-loader.target.platform.dropins
     - Absolute or relative (to the project root folder) path of the folder where the platform can be found (see :ref:`module_natures_platform_selection`).
     - ``dropins`` 

To learn more about the Platform Selection, go to the :ref:`platform_selection` page.

.. _module_natures.plugins.javadoc:

Javadoc
^^^^^^^

Javadoc can be generated for several modules natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.sandboxed_application`

The following options are available to configure the test:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - src.main.java
     - Path of the folder containing the Java sources.
     - ``${basedir}/src/main/java``
   * - javadoc.file.encoding
     - Encoding used for the generated Javadoc.
     - ``UTF-8``
   * - javadoc.failonerror
     - When this property is set to true, the build is stopped if an error is raised during the Javadoc generation.
     - ``true``
   * - javadoc.failonwarning
     - When this property is set to true, the build is stopped if a warning is raised during the Javadoc generation.
     - ``false``
   * - target.reports
     - Path of the base folder for reports.
     - ``${target}/reports``
   * - target.javadoc
     - Path of the base folder where the Javadoc is generated.
     - ``${target.reports}/javadoc``
   * - target.javadoc.main
     - Path of the folder where the Javadoc is generated.
     - ``${target.javadoc}/main``
   * - |question| java.configuration
     - Java core library configuration (edc or cldc).
     - ``edc``
   * - |question| include.java.runtime
     - When this property is set to true, the JRE runtime libraries are included in the classpath.
     - ``no``
   * - |question| javadoc.source.version
     - Java version of the sources.
     - ``1.7`` (edc version)
   * - javadoc-microej.overview.html
     - Path of the HTML template file used for the Javadoc overview page.
     - ``${src.main.java}/overview.html`` if exists, otherwise a default template.
   * - target.artifacts
     - Path of the packaged artifacts.
     - ``${target}/artifacts``
   * - target.artifacts.main.javadoc.jar.name
     - Name of the packaged JAR containing the generated Javadoc (stored in folder ``target.artifacts``).
     - ``${module.name}-javadoc.jar``
   * - javadoc.publish.conf
     - Ivy configuration used to publish the Javadoc artifact.
     - ``documentation``

.. _module_natures.plugins.testsuite:

Test Suite
^^^^^^^^^^

A test suite on MicroEJ VM can be added for several modules natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.foundation_lib_impl`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`

The following options are available to configure the test suite:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - test.run.includes.pattern
     - Pattern of classes included in the test suite execution.
     - ``**/*`` (all tests)
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test suite execution.
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the build fails if an error is raised.
     - ``true``
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - Not set
   * - microej.testsuite.cc.excludes.classes
     - Pattern of classes excluded from the code coverage abalysis.
     - Not set
   * - microej.testsuite.properties.s3.cc.activated
     - When this property is set to true, the code coverage analysis is disabled.
     - Not set

To learn more about the Test Suite, go to the :ref:`Test Suite <application_testsuite>` page.

.. _module_natures.plugins.artifact_checker:

.. _module_natures.plugins.unittests:

J2SE Unit Tests
^^^^^^^^^^^^^^^

J2SE Unit tests can be added for several modules natures:

- :ref:`module_natures.addon_processor`
- :ref:`module_natures.mock`

These tests are generally reserved for tools.
Tests classes must be created in the folder ``srtc/test/java`` of the project.

The following options are available to configure the J2SE unit tests:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - test.run.includes.pattern
     - Pattern of classes included in the test suite execution.
     - ``**/*`` (all tests)
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test suite execution.
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the build fails if an error is raised.
     - ``true``
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - Not set

Artifact Checker
^^^^^^^^^^^^^^^^

The Artifact Checker is enabled for several modules natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.module_repository`

The following options are available to configure the test suite:

.. list-table:: 
   :widths: 20 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - run.artifact.checker
     - When this property is set (any value), the artifact checker is executed.
     - Not set
   * - skip.addonconf.checker
     - When this property is set to true, the addon configurations checker is not executed.
     - Not set
   * - skip.foundationconf.checker
     - When this property is set to true, the foundation configurations checker is not executed.
     - Not set
   * - skip.publicconf.checker
     - When this property is set to true, the public configurations checker is not executed.
     - Not set
   * - skip.changelog.checker
     - When this property is set to true, the changelog checker is not executed.
     - Not set
   * - skip.license.checker
     - When this property is set to true, the license checker is not executed.
     - Not set
   * - skip.readme.checker
     - When this property is set to true, the readme checker is not executed.
     - Not set
   * - skip.retrieve.checker
     - When this property is set to true, the retrieve checker is not executed.
     - Not set


.. |question| unicode:: U+1F914 .. thinking

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
