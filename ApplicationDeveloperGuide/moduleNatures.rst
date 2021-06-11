.. _module_natures:

Module Natures
==============

This page describes the most common module natures as follows:

- **Skeleton Name**: the :ref:`project skeleton <mmm_module_skeleton>` name.
- **Build Type Name**: the build type name, derived from the module nature name: ``com.is2t.easyant.buildtypes#build-[NATURE_NAME]``.
- **Documentation**: a link to the documentation.
- **Wizard**: the direct wizard shortcut in MicroEJ SDK (if available).
- **Configuration**: properties that can be defined to configure the module. Properties are defined inside the ``ea:build`` tag of the :ref:`module.ivy <mmm_module_description>` file,
  using ``ea:property`` tag as described in the section :ref:`mmm_build_options`.
  A module nature also inherits the configuration properties from the listed :ref:`module_natures.plugins`.

.. _module_natures.addon_lib:

Add-On Library
--------------

**Skeleton Name**: ``microej-javalib``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-microej-javalib``

**Documentation**: :ref:`libraries`

**Wizard**: :guilabel:`File` > :guilabel:`New` > :guilabel:`Add-On Library Project`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.javadoc`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

.. _module_natures.addon_processor:

Add-On Processor
----------------

**Skeleton Name**: ``addon-processor``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-addon-processor``

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.unittests`
- :ref:`module_natures.plugins.artifact_checker`

.. _module_natures.foundation_lib_api:

Foundation Library API
----------------------

**Skeleton Name**: ``microej-javaapi``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-microej-javaapi``

**Documentation**: :ref:`libraries`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.javadoc`
- :ref:`module_natures.plugins.artifact_checker`

.. _module_natures.foundation_lib_impl:

Foundation Library Implementation
---------------------------------

**Skeleton Name**: ``microej-javaimpl``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-microej-javaimpl``

**Documentation**: :ref:`libraries`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.testsuite`

It defines the following dedicated configuration properties:

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

.. _module_natures.meta_build:

Meta Build
----------

**Skeleton Name**: ``microej-meta-build``

**Build Type Name**: ``com.is2t.easyant.buildtypes#microej-meta-build``

**Documentation**: :ref:`meta_build`

**Configuration**:

This module nature defines the following dedicated configuration properties:

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

.. _module_natures.mock:

Mock
----

**Skeleton Name**: ``microej-mock``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-microej-mock``

**Documentation**: :ref:`mock`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.unittests`

.. _module_natures.module_repository:

Module Repository
-----------------

**Skeleton Name**: ``artifact-repository``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-artifact-repository``

**Documentation**: :ref:`module_repository`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.artifact_checker`

It defines the following dedicated configuration properties:

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

.. _module_natures.sandboxed_application:

Sandboxed Application
---------------------

**Skeleton Name**: ``application``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-application``

**Documentation**: :ref:`sandboxed_application`

**Wizard**: :guilabel:`File` > :guilabel:`New` > :guilabel:`Sandboxed Application Project`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.javadoc`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

.. _module_natures.standalone_application:

Standalone Application
----------------------

**Skeleton Name**: ``firmware-singleapp``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-firmware-singleapp``

**Documentation**: :ref:`standalone_application`

**Wizard**: :guilabel:`File` > :guilabel:`New` > :guilabel:`Standalone Application Project`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

It defines the following dedicated configuration properties:

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

.. _module_natures.plugins:

Natures Plugins
---------------

This page describes the most common module nature plugins as follows:

- **Documentation**: link to documentation.
- **Module Natures**: list of :ref:`module_natures` using this plugin.
- **Configuration**: properties that can be defined to configure the module. Properties are defined inside the ``ea:build`` tag of the :ref:`module.ivy <mmm_module_description>` file,
  using ``ea:property`` tag as described in the section :ref:`mmm_build_options`.


.. _module_natures.plugins.compilation:

Java Compilation
^^^^^^^^^^^^^^^^

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.foundation_lib_impl`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`

**Configuration**:

This plugin defines the following configuration properties:

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

**Documentation**: :ref:`platform_selection`

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`

**Configuration**:

This plugin defines the following configuration properties:

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

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.sandboxed_application`

**Configuration**:

This plugin defines the following configuration properties:

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

**Documentation**: :ref:`application_testsuite`

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.foundation_lib_impl`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`

**Configuration**:

This plugin defines the following configuration properties:

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

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_processor`
- :ref:`module_natures.mock`

**Configuration**:

This plugin defines the following configuration properties:

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

.. _module_natures.plugins.artifact_checker:

Artifact Checker
^^^^^^^^^^^^^^^^

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_lib`
- :ref:`module_natures.foundation_lib_api`
- :ref:`module_natures.standalone_application`
- :ref:`module_natures.sandboxed_application`
- :ref:`module_natures.module_repository`

**Configuration**:

This plugin defines the following configuration properties:

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
