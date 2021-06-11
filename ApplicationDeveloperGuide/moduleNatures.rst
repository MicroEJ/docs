.. _module_natures:

Module Natures
==============

This page describes the most common module natures as follows:

- **Skeleton Name**: the :ref:`project skeleton <mmm_module_skeleton>` name.
- **Build Type Name**: the build type name, derived from the module nature name: ``com.is2t.easyant.buildtypes#build-[NATURE_NAME]``.
- **Documentation**: a link to the documentation.
- **SDK Menu**: the menu to the direct wizard in MicroEJ SDK (if available). 
  Any module nature can be created with the default wizard from :guilabel:`File` > :guilabel:`New` > :guilabel:`Module Project`.
- **Configuration**: properties that can be defined to configure the module. Properties are defined inside the ``ea:build`` tag of the :ref:`module.ivy <mmm_module_description>` file,
  using ``ea:property`` tag as described in the section :ref:`mmm_build_options`.
  A module nature also inherits the configuration properties from the listed :ref:`module_natures.plugins`.

.. _module_natures.addon_lib:

Add-On Library
--------------

**Skeleton Name**: ``microej-javalib``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-microej-javalib``

**Documentation**: :ref:`libraries`

**SDK Menu**: :guilabel:`File` > :guilabel:`New` > :guilabel:`Add-On Library Project`

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

This module nature defines the following dedicated configuration properties:

.. list-table:: 
    :widths: 25 65 15
    :header-rows: 1

    * - Name
      - Description
      - Default
    * - microej.lib.name
      - Platform library name on the form: ``[NAME]-[VERSION]-api``.
        - ``[NAME]``: name of the implemented Foundation Library API module.
        - ``[VERSION]``: version of the implemented Foundation Library API module without patch (``Major.minor``).
      - Not set
    * - rip.printableName
      - Printable name for the Platform Editor.
      - Not set

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

This module nature defines the following dedicated configuration properties:

.. list-table:: 
    :widths: 25 65 15
    :header-rows: 1

    * - Name
      - Description
      - Default
    * - microej.lib.implfor
      - Execution target.
        Possible values are `emb` (only on Device), `sim` (only Simulator) and `common` (both).
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
    :widths: 25 65 15
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

This module nature defines the following dedicated configuration properties:

.. list-table:: 
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - bar.check.as.v2.module
     - When this property is set to true, the artifact checker uses the MicroEJ Module Manager semantic.
     - ``false``
   * - bar.javadoc.dir
     - Path of the folder containing the generated javadoc.
     - ``${target}/javadoc``
   * - bar.javadoc.stylesheet.file
     - Path of the Stylesheet used for the generated Javadoc.
     - Not set
   * - bar.notification.email.from
     - The email address used as the from address when sending the notification emails.
     - Not set
   * - bar.notification.email.host
     - The hostname of the mail service used to send the notification emails.
     - Not set
   * - bar.notification.email.password
     - The password used to authenticate on the mail service.
     - Not set
   * - bar.notification.email.port
     - The port of the mail service used to send the notification emails
     - Not set
   * - bar.notification.email.ssl
     - When this property is set to true, SSL/TLS is used to send the notification emails.
     - Not set
   * - bar.notification.email.to
     - The notification email address destination.
     - Not set
   * - bar.notification.email.user
     - The username used to authenticate on the mail service.
     - Not set
   * - bar.populate.from.resolver
     - Name of the resolver used to fetch the modules to populate the repository.
     - ``fetchRelease``
   * - bar.populate.ivy.settings.file
     - Path of the Ivy settings file used to fetch the modules to populate the repository.
     - ``${project.ivy.settings.file}``
   * - bar.populate.repository.conf
     - Ivy configuration of included repositories. 
       The modules of the repositories declared as dependency with this configuration are included in the built repository.
     - ``repository``
   * - bar.test.haltonerror
     - When this property is set to true, the artifact checker stops at the first error.
     - ``false``
   * - javadoc.excludes
     - Comma-separated list of packages to exclude from the javadoc.
     - Empty string
   * - javadoc.includes
     - Comma-separated list of packages to include in the javadoc.
     - ``**`` (all packages)
   * - skip.artifact.checker
     - When this property is set to true, all artifact checkers are skipped.
     - Not set
   * - skip.email
     - When this property is set (any value), the notification email is not sent. 
       Otherwise the ``bar.notification.*`` properties are required.
     - Not set   
   * - skip.javadoc.deprecated
     - Prevents the generation of any deprecated API at all in the javadoc.
     - ``true``

.. _module_natures.sandboxed_application:

Sandboxed Application
---------------------

**Skeleton Name**: ``application``

**Build Type Name**: ``com.is2t.easyant.buildtypes#build-application``

**Documentation**: :ref:`sandboxed_application`

**SDK Menu**: :guilabel:`File` > :guilabel:`New` > :guilabel:`Sandboxed Application Project`

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

**SDK Menu**: :guilabel:`File` > :guilabel:`New` > :guilabel:`Standalone Application Project`

**Configuration**:

This module nature inherits the configuration properties of the following plugins:

- :ref:`module_natures.plugins.compilation`
- :ref:`module_natures.plugins.platform_loader`
- :ref:`module_natures.plugins.testsuite`
- :ref:`module_natures.plugins.artifact_checker`

This module nature defines the following dedicated configuration properties:

.. list-table:: 
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - application.main.class
     - Full Qualified Name of the main class of the application. This option is required.
     - Not set
   * - skip.build.virtual.device
     - When this property is set (any value), the virtual device is not built.
     - Not set
   * - virtual.device.sim.only
     - When this property is set (any value), the firmware is not built.
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
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - javac.debug.level
     - Comma-separated list of levels for the Java compiler debug mode.
     - ``lines,source,vars``
   * - javac.debug.mode
     - When this property is set to true, the Java compiler is set in debug mode.
     - ``false``
   * - src.main.java
     - Path of the folder containing the Java sources.
     - ``${basedir}/src/main/java``


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
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - platform-loader.platform.dir
     - Path of the folder to unzip the loaded platform to.
     - ``${target}/platform``
   * - platform.loader.skip.load.platform
     - When this property is set to true, the platform is not loaded. It must be already available in the directory defined by the property ``platform-loader.platform.dir``.
       Use with caution: the platform content may be modified during the build (e.g. in case of Testsuite or Virtual Device build).
     - ``false``
   * - platform-loader.target.platform.conf
     - The Ivy configuration used to retrieved the platform if fetched via dependencies.
     - ``platform``     
   * - platform-loader.target.platform.dir
     - Path of the root folder of the platform to use in the build. See :ref:`platform_selection` section for Platform Selection rules.
     - Not set
   * - platform-loader.target.platform.dropins
     - Absolute or relative (to the project root folder) path of the folder where the platform can be found (see :ref:`module_natures_platform_selection`).
     - ``dropins`` 
   * - platform-loader.target.platform.file
     - Path of the platform file to use in the build. See :ref:`platform_selection` section for Platform Selection rules.
     - Not set

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
   :widths: 25 65 15
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
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - microej.testsuite.cc.excludes.classes
     - Pattern of classes excluded from the code coverage analysis.
     - Not set
   * - microej.testsuite.properties.s3.cc.activated
     - When this property is set to true, the code coverage analysis is disabled.
     - Not set
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test suite execution.
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the build fails if an error is raised.
     - ``true``
   * - test.run.includes.pattern
     - Pattern of classes included in the test suite execution.
     - ``**/*`` (all tests)
   * - skip.test
     - When this property is set (any value), the tests are not executed.
     - Not set

.. _module_natures.plugins.unittests:

J2SE Unit Tests
^^^^^^^^^^^^^^^

.. warning::
   
   This plugin is reserved for tools written in Java Standard Edition.
   Tests classes must be created in the folder ``src/test/java`` of the project.
   See :ref:`module_natures.plugins.testsuite` section for MicroEJ tests.

**Module Natures**:

This plugin is used by the following module natures:

- :ref:`module_natures.addon_processor`
- :ref:`module_natures.mock`

**Configuration**:

This plugin defines the following configuration properties:

.. list-table:: 
   :widths: 25 65 15
   :header-rows: 1

   * - Name
     - Description
     - Default
   * - test.run.excludes.pattern
     - Pattern of classes excluded from the test suite execution.
     - Empty string (no test)
   * - test.run.failonerror
     - When this property is set to true, the build fails if an error is raised.
     - ``true``
   * - test.run.includes.pattern
     - Pattern of classes included in the test suite execution.
     - ``**/*`` (all tests)
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
   :widths: 25 65 15
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
   * - skip.changelog.checker
     - When this property is set to true, the changelog checker is not executed.
     - Not set
   * - skip.foundationconf.checker
     - When this property is set to true, the foundation configurations checker is not executed.
     - Not set
   * - skip.license.checker
     - When this property is set to true, the license checker is not executed.
     - Not set
   * - skip.publicconf.checker
     - When this property is set to true, the public configurations checker is not executed.
     - Not set
   * - skip.readme.checker
     - When this property is set to true, the readme checker is not executed.
     - Not set
   * - skip.retrieve.checker
     - When this property is set to true, the retrieve checker is not executed.
     - Not set


..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
