--------------------------
SDK Distribution Changelog
--------------------------

[21.11] - 2021-11-15
~~~~~~~~~~~~~~~~~~~~

**NOTE:** This release prepares for a future JRE 11 migration.
However, the officially supported JRE version is still JRE 8. Please refer to :ref:`system-requirements` for more details.

-  Included :ref:`Studio / SDK 5.5.0 <changelog-5.5.0>`
-  Updated installer to accept both JRE 8 and JRE 11.
-  Fixed error ``Error while loading manipulator`` when installing SDK updates on MacOS.

[21.03] - 2021-03-25
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`Studio / SDK 5.4.0 <changelog-5.4.0>`
  
.. _known-issues-21.03:

**KNOWN ISSUES**:

-  The following error occurs when installing an SDK update on MacOS:

  .. code-block:: 

    !MESSAGE Error while loading manipulator.
    !STACK 0
    java.lang.IllegalStateException: Error while loading manipulator.
    	at org.eclipse.equinox.internal.p2.touchpoint.eclipse.LazyManipulator.loadDelegate(LazyManipulator.java:64)
    	at org.eclipse.equinox.internal.p2.touchpoint.eclipse.LazyManipulator.getConfigData(LazyManipulator.java:117)
    	at org.eclipse.equinox.internal.p2.touchpoint.eclipse.actions.UninstallBundleAction.uninstallBundle(UninstallBundleAction.java:57)
    	at org.eclipse.equinox.internal.p2.touchpoint.eclipse.actions.UninstallBundleAction.execute(UninstallBundleAction.java:33)
    	at org.eclipse.equinox.internal.p2.engine.ParameterizedProvisioningAction.execute(ParameterizedProvisioningAction.java:42)
    	at org.eclipse.equinox.internal.p2.engine.Phase.mainPerform(Phase.java:186)
    	at org.eclipse.equinox.internal.p2.engine.Phase.perform(Phase.java:99)
    	at org.eclipse.equinox.internal.p2.engine.PhaseSet.perform(PhaseSet.java:50)
    	at org.eclipse.equinox.internal.p2.engine.Engine.perform(Engine.java:80)
    	at org.eclipse.equinox.internal.p2.engine.Engine.perform(Engine.java:48)
    	at org.eclipse.equinox.p2.operations.ProvisioningSession.performProvisioningPlan(ProvisioningSession.java:181)
    	at org.eclipse.equinox.p2.operations.ProfileModificationJob.runModal(ProfileModificationJob.java:76)
    	at org.eclipse.equinox.p2.operations.ProvisioningJob.run(ProvisioningJob.java:190)
    	at org.eclipse.core.internal.jobs.Worker.run(Worker.java:63)

  The workaround is to replace ``/eclipse/plugins/`` by ``/Eclipse/plugins/`` (capital ``E``) in ``MicroEJ-SDK-21.03.app\Contents\Eclipse\eclipse.ini``.

-  See :ref:`Studio / SDK 5.4.0 Known Issues <known-issues-5.4.0>` section

[20.12] - 2020-12-11
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`Studio / SDK 5.3.1 <changelog-5.3.1>`
-  Disabled Java version check when updating Studio/SDK (see
   :ref:`known issues of Studio/SDK Distribution 20.10 <known-issues-20.10>`)

[20.10] - 2020-10-30
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`Studio / SDK 5.3.0 <changelog-5.3.0>`
-  Updated to Eclipse version ``2020-06``
-  Fixed low quality MacOS SDK icons

**NOTE:** Starting with this release, only 64bits JRE are supported
because 32bits JRE support has been removed since Eclipse version
``2018-12``. See `this
link <https://www.eclipse.org/eclipse/news/4.10/platform.php#java32-removal>`__
for more details.

.. _known-issues-20.10:

**KNOWN ISSUES**:

-  Projects configured with Null Analysis must be updated to import `EDC
   API 1.3.3 <https://repository.microej.com/modules/ej/api/edc/1.3.3/>`__
   or higher in order to avoid an Eclipse JDT builder error (see also
   `this link <https://bugs.eclipse.org/bugs/show_bug.cgi?id=566599>`__
   for more details).
-  The default settings file for connecting MicroEJ Central Repository
   is not automatically installed. To connect to the MicroEJ Central
   Repository, follow the procedure:

   -  For Windows, create the folder: ``C:\Users\%USERNAME%\.microej``.
   -  For Linux, create the folder: ``/home/$USER/.microej``.
   -  For macos, create the folder: ``/Users/$USER/.microej``.
   -  Download and save this file `microej-ivysettings-5.xml <https://repository.microej.com/microej-ivysettings-5.xml>`__ to the previously created ``.microej`` folder.
-  By default, a check is done on the JRE version required by the
   plugins on install/update. Since CDT requires JRE 11, it prevents to
   install/update a newer SDK version. The CDT documentation
   explains that this can be bypassed by disabling the option
   :guilabel:`Windows` > :guilabel:`Preferences` > :guilabel:`Install/Update` > :guilabel:`Verify provisioning operation is compatible with currently running JRE`.

[20.07] - 2020-07-28
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`MicroEJ Studio / SDK 5.2.0 <changelog-5.2.0>`
-  Updated the default microej repository folder name (replaced
   Studio/SDK version by the distribution number)
-  Added ``Dist.`` prefix in installer name (e.g.
   ``MicroEJ SDK Dist. 20.07``) to avoid confusion between SDK
   distribution vs SDK version
-  Updated SDK and Studio End User License Agreement
-  Disabled popup window when installing a SDK update site
   (allow to install unsigned content by default)

[19.05] - 2019-05-17
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`Studio / SDK version 5.1.0 <changelog-5.1.0>`
-  Updated MicroEJ icons (``16x16`` and ``32x32``)
-  Updated the publisher of Windows executables (``MicroEJ`` instead of
   ``IS2T SA.``)
-  Updated the JRE link to download in case the default JRE is not
   compatible. (``https://www.java.com`` is deprecated)

[19.02] - 2019-02-22
~~~~~~~~~~~~~~~~~~~~

-  Updated to Eclipse Oxygen version ``4.7.2``
-  Included :ref:`Studio / SDK version 5.0.1 <changelog-5.0.1>`
-  Included Sonarlint version ``4.0.0``

-------------
SDK Changelog
-------------

SDK includes all Studio features.

A line prefixed by ``[Studio]`` is valid for both Studio and SDK. A line prefixed by ``[SDK]`` is only valid for SDK.

.. _changelog-5.5.0:

[5.5.0] - 2021-11-05
~~~~~~~~~~~~~~~~~~~~

**NOTE:** This release prepares for a future JRE 11 migration.
However, the officially supported JRE version is still JRE 8. Please refer to :ref:`system-requirements` for more details.

General
"""""""

-  ``[Studio]`` Added Add-On Processor resolution in workspace.
-  ``[Studio]`` Updated tools for both JRE 8 and JRE 11 compatibility.
-  ``[SDK]`` Updated Architecture version check during Pack import (``greaterOrEqual`` instead of ``compatible``). This allows to import :ref:`pack_architecture_specific` and :ref:`pack_generic_legacy` on future Architecture ``8.x`` versions.

MicroEJ Module Manager
""""""""""""""""""""""

-  ``[Studio]`` Added ``bin`` folder to ``.gitignore`` file of module natures Java project skeleton.
-  ``[Studio]`` Added Null Analysis configuration to ``artifact-checker``. When building a module repository, null analysis configuration is only checked on the highest module version included in the repository.
-  ``[Studio]`` Added Eclipse Public License v2.0 to the list of default licenses allowed for ``artifact-checker``.
-  ``[Studio]`` Clarified input messages of ``mmm init`` command.
-  ``[Studio]`` Updated ``artifact-checker`` plugin binding to target ``verify``. This allow module checks to be executed on builds triggered by a pull request (no publication).
-  ``[Studio]`` Fixed missing ``artifact-checker`` plugin to some module natures (``custom``, ``firmware-multiapp``, ``firmware-singleapp``, ``microej-javaimpl``, ``microej-mock``, ``microej-testsuite``, ``product-java``).
-  ``[Studio]`` Fixed ``mmm run`` execution on a ``firmware-singleapp`` module (do not trigger the Firmware build).
-  ``[Studio]`` Fixed ``kf-testsuite`` plugin test project build.
-  ``[Studio]`` Added support of branch analysis with Sonar.
-  ``[SDK]`` Added ability to package private dependencies to ``mock`` module natures (configuration ``embedded``).
-  ``[SDK]`` Added ``testsuite`` and ``javadoc`` plugin to ``firmware-singleapp`` module nature.
-  ``[SDK]`` Added ``ssh`` deployment to ``microej-kf-testsuite`` plugin.
-  ``[SDK]`` Updated ``firmware-multiapp`` to remove the ``bsp`` directory in Virtual Devices.
-  ``[SDK]`` Updated ``firmware-multiapp`` to allow Virtual Devices for launching a specific main class other than the Kernel main class
   This is useful for running JUnit tests using a Virtual Device instead of a Platform.
-  ``[SDK]`` Updated ``firmware-multiapp`` to allow Virtual Devices for automatically launching a Sandboxed Application project in MicroEJ Studio.
-  ``[SDK]`` Updated ``firmware-multiapp`` to automatically configure the Virtual Device Kernel UID when a Firmware is built.
-  ``[SDK]`` Fixed ``firmware-multiapp`` skeleton default dependencies with only modules available in MicroEJ Central Repository.
-  ``[SDK]`` Fixed ``firmware-multiapp`` unexpected build error when no declared Resident Application.
-  ``[SDK]`` Fixed ``firmware-multiapp`` build which may fail an unexpected ``Unresolved Dependencies`` error the first time,
   for Kernel APIs module dependencies (configuration ``kernelapi``) or Virtual Device specific modules dependencies (configuration ``default-vd``).
-  ``[SDK]`` Fixed ``firmware-multiapp`` unexpected build error when no Application (``.wpk`` file) found in the dropins folder.
-  ``[SDK]`` Fixed ``firmware-multiapp`` unexpected build error when no declared Resident Application.
-  ``[SDK]`` Fixed ``firmware-singleapp`` and ``firmware-multiapp`` skeletons wrong package name generation for the default Main class.
-  ``[SDK]`` Fixed ``artifact-repository`` changelog check for modules with a snapshot version.

.. _changelog-5.4.1:

[5.4.1] - 2021-04-16
~~~~~~~~~~~~~~~~~~~~

**NOTE:** This release is both compatible with Eclipse version ``2020-06``
and Eclipse Oxygen, so it can still be installed on a previous
Studio / SDK Distribution.

MicroEJ Module Manager
""""""""""""""""""""""

-  ``[Studio]`` Fixed missing ``repository`` configuration in
   ``artifact-repository`` skeleton (this configuration is required to
   include modules bundled in an other module repository)
-  ``[Studio]`` Fixed missing some old build types versions that were
   removed by error. (introduced in SDK ``5.4.0``, please refer
   to the :ref:`Known Issues <known-issues-5.4.0>` section for more details)
-  ``[Studio]`` Fixed wrong version of module built in a meta-build
   (module was published with the module version instead of the snapshot
   version)
-  ``[Studio]`` Fixed code coverage analysis on source code (besides on
   bytecode) thanks to the property ``cc.src.folders`` (only for
   architectures in version 7.16.0 and beyond)

.. _changelog-5.4.0:

[5.4.0] - 2021-03-25
~~~~~~~~~~~~~~~~~~~~

**NOTE:** This release is both compatible with Eclipse version ``2020-06``
and Eclipse Oxygen, so it can still be installed on a previous
Studio / SDK Distribution.

.. _known-issues-5.4.0:

Known Issues
""""""""""""

-  Some older build types versions have been removed by error.
   Consequently, using SDK ``5.4.0``, it may be not possible to
   build modules that have been created with an older SDK
   version (For example, `MicroEJ
   GitHub <https://github.com/MicroEJ/>`__ code). The list of missing
   build types:

   -  ``[Studio]`` build-application ``7.0.2``
   -  ``[Studio]`` build-microej-javalib ``4.1.1``
   -  ``[SDK]`` build-firmware-singleapp ``1.2.10``
   -  ``[SDK]`` build-microej-extension ``1.3.2``

General
"""""""

-  ``[Studio]`` Added MicroEJ Module Manager Command Line Interface in
   Build Kit
-  ``[Studio]`` Added ignore optional compilation problems in Addon
   Processor generated source folders
-  ``[Studio]`` Added logs to Standalone Application build indicating
   the mapping of Foundation Libraries to the Platform
-  ``[SDK]`` Updated End User License Agreement
-  ``[SDK]`` Added the latest HIL Engine API to mock-up skeleton (native
   resources management)
-  ``[SDK]`` Updated the Architecture import wizard to automatically
   accept Pack licenses when the Architecture license is accepted

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  ``[Studio]`` Added JSCH library to execute MicroEJ test suites on
   Device through ssh
-  ``[Studio]`` Added pre-compilation phase before executing Addon
   Processor to have compiled classes available
-  ``[Studio]`` Updated the default settings file to import modules from
   `MicroEJ Developer
   repository <https://forge.microej.com/artifactory/microej-developer-repository-release/>`__
   (located at ``${user.dir}\.microej\microej-ivysettings-5.4.xml``)

Build Types
^^^^^^^^^^^

-  ``[Studio]`` Updated all relevant build types to load the Platform
   using the ``platform`` configuration instead of the ``test``
   configuration:

   -  Sandboxed Application (``application``)
   -  Foundation Library Implementation (``javaimpl``)
   -  Addon Library (``javalib``)
   -  MicroEJ Testsuite (``testsuite``)
-  ``[Studio]`` Updated Module Repository to allow to partially include
   an Architecture module (``eval`` and/or ``prod``)
-  ``[Studio]`` Fixed potential Addon Processor error
   ``NoClassDefFoundError: ej/tool/addon/util/Message`` depending on the
   resolution order
-  ``[SDK]`` Removed javadoc generation for ``microej-extension``

Build Plugins
^^^^^^^^^^^^^

-  ``[Studio]`` Updated Addon Processor to fail the build when an error
   is detected. Error messages are dumped to the build logs.
-  ``[Studio]`` Updated Platform Loader to handle Platform module
   (``.zip`` file)
-  ``[Studio]`` Updated Platform Loader to handle Virtual Device module
   (``.vde`` file) declared as a dependency. It worked before only by using the ``dropins``
   folder.
-  ``[Studio]`` Updated Platform Loader to list the Platforms locations
   when too many Platform modules are detected

Skeletons
^^^^^^^^^

-  ``[Studio]`` Fixed wrong ``README.md`` generation for
   ``artifact-repository`` skeleton
-  ``[SDK]`` Removed useless files in ``microej-javaapi``,
   ``microej-javaimpl`` and ``microej-extension`` skeletons (intern
   changelog and ``.dbk`` file)

.. _changelog-5.3.1:

[5.3.1] - 2020-12-11
~~~~~~~~~~~~~~~~~~~~

**NOTE:** This release is both compatible with Eclipse version
``2020-06`` and Eclipse Oxygen, so it can still be installed on a
previous Studio/SDK Distribution.

General
"""""""

-  ``[Studio]`` Fixed missing default settings file for connecting
   MicroEJ Central Repository when starting a fresh install (introduced
   in ``5.3.0``)

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  ``[Studio]`` Fixed potential build error when computing Sonar
   classpath from dependencies (``ivy:cachepath`` task was sometimes
   using a wrong cache location)

Skeletons
^^^^^^^^^

-  ``[Studio]`` Fixed skeleton dependency to
   `EDC-1.3.3 <https://repository.microej.com/modules/ej/api/edc/1.3.3/>`__
   to avoid an Eclipse JDT builder error when Null Analysis is enabled
   (see :ref:`known issues of Studio/SDK Distribution 20.10 <known-issues-20.10>`)

.. _changelog-5.3.0:

[5.3.0] - 2020-10-30
~~~~~~~~~~~~~~~~~~~~

**NOTE:** This release is both compatible with Eclipse version
``2020-06`` and Eclipse Oxygen, so it can still be installed on a
previous Studio / SDK Distribution.

.. _known-issues-5.3.0:

Known Issues
""""""""""""

-  ``[Studio]`` Library module build may lead to unexpected
   ``Unresolved Dependencies`` error in some cases (in ``sonar:init``
   target / ``ivy:cachepath`` task). Workaround is to trigger the
   library build again.

General
"""""""

-  ``[Studio]`` Fixed various plugins for Eclipse version ``2020-06``
   compatibility (icons, project explorer menu entries)
-  ``[Studio]`` Fixed closed module.ivy files after an SDK restart that
   were opened before
-  ``[Studio]`` Removed license check before launching an Application on
   Device
-  ``[Studio]`` Disabled ``Activate on new event`` option of the Error
   Log view to prevent popup of this view when an internal error is
   thrown
-  ``[SDK]`` Removed license check before Platform build
-  ``[SDK]`` Updated filter of the Launch Group configuration (exclude
   the deprecated Eclipse CDT one)
-  ``[SDK]`` Fixed inclusion of mock project dependencies in launcher
   mock classpath
-  ``[SDK]`` Enhance error message in Platform editor (``.platform``
   files) when the required Architecture has not been imported (displays
   Architecture information)

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  ``[Studio]`` Fixed workspace default settings file when clicking on
   the ``Default`` button
-  ``[Studio]`` First wrong resolved dependency when `ChainResolver returnFirst option <https://ant.apache.org/ivy/history/2.5.0/resolver/chain.html>`__
   is enabled and the module to resolve is already in the cache
-  ``[Studio]`` Fixed potential build module crash (``Not comparable``
   issue) when resolving module dependencies across multiple
   configurations

Build Types
^^^^^^^^^^^

-  ``[Studio]`` Exclude packs from artifact checker when building a
   module repository
-  ``[Studio]`` Merged Foundation & Add-On Libraries javadoc when
   building a module repository
-  ``[Studio]`` Added Module dependency line for each type in module
   repository javadoc
-  ``[Studio]`` Added an option to skip deprecated types, fields,
   methods in module repository javadoc
-  ``[Studio]`` Allow to include or exclude Java packages in module
   repository javadoc
-  ``[Studio]`` Added an option ``skip.publish`` to skip artifacts
   publication in ``build-custom`` build type
-  ``[Studio]`` Allow to define Application options from build option
   using the ``platform-launcher.inject.`` prefix
-  ``[Studio]`` Added generation and publication of code coverage report
   after a testsuite execution. The report generation is enabled under
   the following conditions:

   -  at least one test is executed,
   -  tests are executed on Simulator,
   -  build option ``s3.cc.activated`` is set to ``true`` (default),
   -  the Platform is based on an Architecture version ``7.12.0`` or higher
   -  if testing a Foundation Library (using ``microej-testsuite``), build option ``microej.testsuite.cc.jars.name.regex`` must be set to match the simple name of the library being covered (e.g. ``edc-*.jar`` or ``microui-*.jar``)
-  ``[Studio]`` Fixed sonar false negative Null Analysis detection in
   some cases
-  ``[SDK]`` Added a better error message for Studio rebrand build when
   ``izpack.microej.product.location`` option is missing
-  ``[SDK]`` Deprecated ``build-microej-ri`` and disabled documentation
   generation (useless docbook toolchains have been removed to reduce
   the bundle size: ``-150MB``)

Skeletons
^^^^^^^^^

-  ``[Studio]`` Fixed ``microej-mock`` content script initialization
   folder name


.. _changelog-5.2.0:

[5.2.0] - 2020-07-28
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  ``[Studio]`` Added ``Dist.`` prefix in default workspace and
   repository name to avoid confusion between SDK distribution
   vs SDK version
-  ``[Studio]`` Replaced ``Version`` by ``Dist.`` in :guilabel:`Help` >
   :guilabel:`About MicroEJ® SDK | Studio` menu. The SDK or Studio
   version is available in ``Installation Details`` view.
-  ``[Studio]`` Replaced ``IS2T S.A.`` and ``MicroEJ S.A.`` by
   ``MicroEJ Corp.`` in :guilabel:`Help` > :guilabel:`About MicroEJ® SDK | Studio` menu.
-  ``[Studio]`` Updated Front Panel plugin to version 6.1.1
-  ``[Studio]`` Removed MicroEJ Copyright in Java class template and
   skeletons files
-  ``[Studio]`` Fixed Stopping a MicroEJ launch in the progress view
   doesn't stop the launch

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  ``[Studio]`` Added a new configuration page
   (:guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Module Manager`). This page is a merge of
   formerly named ``Easyant4Eclipse`` preferences page and
   ``Ivy Settings`` relevant options for MicroEJ.
-  ``[Studio]`` Added :guilabel:`Export` > :guilabel:`MicroEJ` > :guilabel:`Module Manager Build Kit`
   wizard, to extract the files required for automating MicroEJ modules
   builds out of the IDE.
-  ``[Studio]`` Added :guilabel:`New` > :guilabel:`MicroEJ` > :guilabel:`Module Project` wizard
   (formerly named ``New Easyant Project``), with module fields content
   assist and alphabetical sort of the skeletons list
-  ``[Studio]`` Added :guilabel:`Import` > :guilabel:`MicroEJ` > :guilabel:`Module Repository` wizard to
   automatically configure workspace with a module repository (directory
   or zip file)
-  ``[Studio]`` Added :guilabel:`New MicroEJ Add-On Library Project` wizard to
   simplify Add-On Library skeleton project creation
-  ``[Studio]`` Updated the build repository
   (``microej-build-repository.zip``) to be self contained with its owns
   ``ivysettings.xml``
-  ``[Studio]`` Updated Virtual Device Player (``firmware-singleapp``)
   ``launcher-windows.bat`` (use ``launcher-windows-verbose.bat`` to get
   logs)
-  ``[Studio]`` Renamed the classpath container to
   ``Module Dependencies`` instead of ``Ivy``
-  ``[Studio]`` Fixed Addon Processor ``src-adpgenerated`` folder
   generation when creating or importing a project with the same name
   than a previously deleted one
-  ``[Studio]`` Fixed implementation of settings `ChainResolver returnFirst option <https://ant.apache.org/ivy/history/2.5.0/resolver/chain.html>`__
-  ``[Studio]`` Fixed Ivy module resolution being blocked from time to
   time

Build Types
^^^^^^^^^^^

-  ``[Studio]`` Fixed meta build to publish correct snapshot revisions
   for built dependencies. (Indirectly fixes ADP resolution issue when
   an Add-On Library and its associated Addon Processor were built
   together using a meta build)
-  ``[Studio]`` Fixed potential infinite loop when building a Modules
   Repository with MMM semantic enabled
-  ``[Studio]`` Fixed javadoc not being generated in artifactory
   repository build when ``skip.javadoc`` is set to ``false``
-  ``[Studio]`` Added the capability to build partial modules
   repository, by using the user provided ``ivysettings.xml`` file to
   check the repository consistency
-  ``[Studio]`` Added the possibility to partially extend the build
   repository in a module repository. The build repository can be
   referenced by a file system resolver using the property
   ``${microej-build-repository.repo.dir}``
-  ``[Studio]`` Added the possibility to include a module repository
   into an other module repository (using new configuration
   ``repository->*``)
-  ``[SDK]`` Added the possibility to bundle a set of Virtual Devices
   when building a branded Studio. They are automatically
   imported to the MicroEJ repository when booting on a new workspace.
-  ``[SDK]`` Added the possibility to bundle a Module Repository when
   building a branded Studio. It is automatically imported and
   settings file is configured when booting on a new workspace.

Build Plugins
^^^^^^^^^^^^^

-  ``[Studio]`` Added variables ``@MMM_MODULE_ORGANISATION@``,
   ``@MMM_MODULE_NAME@`` and ``@MMM_MODULE_VERSION@``\ for README.md
   file
-  ``[SDK]`` Fixed ``microej-kf-testsuite`` repository access issue
   (introduced in SDK ``5.0.0``).
-  ``[Studio]`` Fixed ``artifact-checker`` to accept revisions
   surrounded by brackets (as specified by
   https://keepachangelog.com/en/1.0.0/)

Skeletons
^^^^^^^^^

-  ``[Studio]`` Updated ``module.ivy`` indentation characters with tabs
   instead of spaces
-  ``[Studio]`` Updated ``CHANGELOG.md`` formatting
-  ``[Studio]`` Updated and standardized ``README.md`` files
-  ``[Studio]`` Updated dependencies in ``module.ivy`` to use the latest
   versions
-  ``[Studio]`` Added ``.gitignore`` to ignore the ``target~`` and
   ``src-adpgenerated`` folder where the module is built
-  ``[Studio]`` Added Sandboxed Application WPK dropins folder
   (``META-INF/wpk``)
-  ``[Studio]`` Removed conf ``provided`` in ``module.ivy`` for
   foundation libraries dependencies
-  ``[Studio]`` Remove MicroEJ internal site reference in ``module.ant``
   file
-  ``[Studio]`` Fixed corrupted library ``workbenchExtension-api.jar``
   in ``microej-extension`` skeleton
-  ``[Studio]`` Fixed corrupted library ``HILEngine.jar`` in
   ``microej-mock`` skeleton
-  ``[Studio]`` Fixed javadoc content issue in Main class
   ``firmware-singleapp`` skeleton

Misc
""""

-  ``[Studio]`` Updated End User License Agreement
-  ``[SDK]`` Added support for generating Application Options in
   reStructured Text format

.. _changelog-5.1.2:

[5.1.2] - 2020-03-09
~~~~~~~~~~~~~~~~~~~~

MicroEJ Module Manager
""""""""""""""""""""""

-  ``[Studio]`` Fixed potential build error when generating fixed
   dependencies file (``fixdeps`` task was sometimes using a wrong cache
   location)
-  ``[Studio]`` Fixed topogical sort of classpath dependencies when
   building using ``Build Module`` (same as in ``IvyDE`` classpath
   sorted view)
-  ``[Studio]`` Fixed resolution of modules with a version ``0.m.p``
   when transitively fetched (an error was thrown with the range
   ``[1.m.p-RC,1.m.(p+1)-RC[``)
-  ``[Studio]`` Fixed missing classpath dependencies to prevent an error
   when building a standard JAR with JUnit tests


.. _changelog-5.1.1:

[5.1.1] - 2019-09-26
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  ``[SDK]`` Fixed files locked in ``Platform in workspace`` projects
   preventing the Platform from being deleted or rebuilt

.. _changelog-5.1.0:

[5.1.0] - 2019-05-17
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  ``[Studio]`` Updated MicroEJ icons (``16x16`` and ``32x32``)
-  ``[Studio]`` Fixed potential long-blocking operation when launching
   an application on a Virtual Device on Windows 10 (Windows defender
   performs a slow analysis on a zip file when it is open for the first
   time since OS startup)
-  ``[Studio]`` Fixed missing ADP resolution on a fresh MicroEJ
   installation
-  ``[Studio]`` Fixed ADP source folders order generation in
   ``.classpath`` (alphabetical sort of the ADP id)
-  ``[Studio]`` Fixed :guilabel:`Run As...` > :guilabel:`MicroEJ Application` automatic
   launcher creation: when selecting a ``Platform in workspace``, an
   other platform of the repository was used instead
-  ``[Studio]`` Fixed ``Memory Map Analyzer`` load of mapping scripts
   from Virtual Devices
-  ``[Studio]`` Fixed MMM and ADP resolution when importing a zip
   project in a fresh MicroEJ install
-  ``[Studio]`` Fixed ADP crash when a project declares dependencies
   without a source folder
-  ``[Studio]`` Fixed inability to debug an application on a Virtual
   Device if option ``execution.mode`` was specified in firmware build
   properties (now Studio options cannot be overridden)
-  ``[SDK]`` Updated ``Front Panel`` plugin to comply with the new Front
   Panel engine

   -  The Front Panel engine has been refactored and moved from UI Pack to Architecture (UI pack ``12.0.0`` requires Architecture ``7.11.0`` or higher)
   -  :guilabel:`New Front Panel Project` wizard now generates a project skeleton for this new Front Panel engine, based on MMM
   -  Legacy Front Panel projects for UI Pack ``v11.1.0`` or higher are still valid
-  ``[SDK]`` Updated Virtual Device builder to speed-up Virtual Device
   boot time (System Applications are now extracted at build time)
-  ``[SDK]`` Fixed inability to select a ``Platform in workspace`` in a
   MicroEJ Tool launch configuration
-  ``[SDK]`` Fixed broken title in MicroEJ export menu (Platform Export)

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  ``[Studio]`` Added a new option ``application.project.dir`` passed to
   launch scripts with the workspace project directory
-  ``[Studio]`` Updated MMM to throw a non ambiguous error message when
   a ``module.ivy`` configured for MMM declares versions with legacy Ivy
   range notation
-  ``[Studio]`` Updated MicroEJ Central Repository cache directory to
   ``${user.dir}\.microej\caches\repository.microej.com-[version]``
   instead of ``${user.dir}\.ivy2``
-  ``[Studio]`` Updated ``Update Module Dependencies...`` to be disabled
   when ``module.ivy`` cannot be loaded. The menu entry is now grayed
   when the project does not declare an IvyDE classpath container
-  ``[Studio]`` Fixed wrong resolution order when a module is both
   resolved in the repository and the workspace (the workspace module
   must always take precedence to the module resolved in the repository)
-  ``[Studio]`` Fixed useless ``unknown resolver trace`` when cache is
   used by multiple Ivy settings configurations with different resolver
   names.
-  ``[Studio]`` Fixed slow Add-on Processor generation. The classpath
   passed to ADP modules could contain the same entry multiple times,
   which leads each ADP module to process the same classpath multiple
   times.
-  ``[Studio]`` Fixed misspelled recommendation message when a build
   failed
-  ``[Studio]`` Fixed ``Update Module Dependencies...`` tool: wrong
   ``ej:match="perfect"`` added where it was expected to be
   ``compatible``
-  ``[Studio]`` Fixed ``Update Module Dependencies...`` tool: parse
   error when ``module.ivy``\ contains ``<artifact type="rip"/>``
   element
-  ``[Studio]`` Fixed resolution and publication of a module declared
   with an Ivy branch
-  ``[Studio]`` Fixed character ``'-'`` rejected in module organisation
   (according to MMM specification ``2.0-B``)
-  ``[Studio]`` Fixed ADP resolution error when the Add-on Processor
   module was only available in the cache
-  ``[Studio]`` Fixed potential build crash depending on the build kit
   classpath order (error was ``This module requires easyant [0.9,+]``)
-  ``[Studio]`` Fixed ``product-java`` broken skeleton

Build Types
^^^^^^^^^^^

-  ``[Studio]`` Updated Platform Loader error message when the property
   ``platform-loader.target.platform.dir`` is set to an invalid
   directory
-  ``[Studio]`` Fixed meta build property substitution in
   ``*.modules.list`` files
-  ``[Studio]`` Fixed missing publications for ``README.md`` and
   ``CHANGELOG.md`` files
-  ``[Studio]`` Update skeletons to fetch latest libraries (Wadapps
   Framework ``v1.10.0`` and Junit ``v1.5.0``)
-  ``[Studio]`` Updated ``README.md`` publication to generate MMM usage
   and the list of Foundation Libraries dependencies
-  ``[SDK]`` Added a new build nature for building platform options
   pages (``microej-extension``)
-  ``[SDK]`` Updated Virtual Device builder to speed-up Virtual Device
   boot time (System Applications are now extracted at build time)
-  ``[SDK]`` Fixed Virtual Device Player builder (dependencies were not
   exported into the zip file) and updated ``firmware-singleapp``
   skeleton with missing configurations

Skeletons
^^^^^^^^^

-  ``[Studio]`` Updated ``CHANGELOG.md`` based on ``Keep a Changelog``
   specification (https://keepachangelog.com/en/1.0.0/)
-  ``[Studio]`` Updated offline module repository skeleton to fetch in a
   dedicated cache directory under ``${user.dir}/.microej/caches``


.. _changelog-5.0.1:

[5.0.1] - 2019-02-14
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  ``[Studio]`` Removed Wadapps Code generation (see migration notes
   below)
-  ``[Studio]`` Added support for MicroEJ Module Manager semantic (see
   migration notes below)
-  ``[Studio]`` Added a dedicated view for Virtual Devices in MicroEJ
   Preferences
-  ``[Studio]`` Removed Platform related views and menus in MicroEJ
   Studio (Import/Export and Preferences)
-  ``[Studio]`` Added MicroEJ Studio rebranding capability (product
   name, icons, splash screen and installer for Windows)
-  ``[Studio]`` Added a new meta build version, with simplified syntax
   for multi-projects build (see migration notes below)
-  ``[Studio]`` Added a skeleton for building offline module
   repositories
-  ``[Studio]`` Added support for importing extended characters in Fonts
   Designer
-  ``[Studio]`` Allow to import Virtual Devices with ``.vde``\ extension
   (``*.jpf`` import still available for backward compatibility)
-  ``[Studio]`` Removed legacy selection for Types, Resources and
   Immutables in MicroEJ Launch Configuration (replaced by ``*.list``
   files since MicroEJ ``4.0``)
-  ``[Studio]`` Enabled IvyDE workspace dependencies resolution by
   default
-  ``[SDK]`` Enabled MicroEJ workspace Foundation Libraries resolution
   by default
-  ``[SDK]`` Added possibility for Architectures to check for a
   minimum required version of SDK (``sdk.min.version``
   property)
-  ``[SDK]`` Updated ``New Standalone Application Project`` wizard to
   generate a single-app firmware skeleton
-  ``[SDK]`` Updated Virtual Device Builder to manage Sandboxed
   Applications (compatible with Architectures Products ``*_7.10.0`` or
   newer)
-  ``[SDK]`` Updated Virtual Device Builder to include kernel options
   (now options are automatically filled for the application developer
   on Simulator)

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  ``[Studio]`` Added IvyDE resolution from properties defined in
   :guilabel:`Windows` > :guilabel:`Preferences` > :guilabel:`Ant` > :guilabel:`Runtime` > :guilabel:`Properties`
-  ``[Studio]`` Fixed *Illegal character in path* error that may occur
   when running an Add-on Processor
-  ``[Studio]`` Fixed IvyDE crash when defining an Ant property file
   with Eclipse variables

Build Types
^^^^^^^^^^^

-  ``[Studio]`` Kept only latest build types versions (skeletons
   updated)
-  ``[Studio]`` Updated metabuild to execute tests by default for
   private module dependencies
-  ``[Studio]`` Removed remaining build dependencies to JDK (Java code
   compiler and Javadoc processors). All MicroEJ code is now compiled
   using the JDT compiler
-  ``[Studio]`` Introduced a new plugin for executing custom testsuite
   using MicroEJ testsuite engine
-  ``[Studio]`` Fixed *MalformedURLException* error in Easyant trace
-  ``[Studio]`` Fixed Easyant build crash when an Ivy settings file
   contains a cache definitions with a wildcard
-  ``[SDK]`` Updated Platform Builder to keep track in the Platform of
   the architecture on which it has been built
   (``architecture.properties``)
-  ``[SDK]`` Updated Virtual Device Builder to generate with ``.vde``
   extension
-  ``[SDK]`` Updated Multi-app Firmware Builder to embed (Sim/Emb)
   specific modules (Add-on libraries and System Applications)
-  ``[SDK]`` Fixed ``build-microej-ri`` v1.2.1 missing dependencies
   (embedded in SDK 4.1.5)

Skeletons
^^^^^^^^^

-  ``[Studio]`` Updated all skeletons: migrated to latest build types,
   added more comments, copyright cleanup and configuration for MicroEJ
   Module Manager semantic)
-  ``[SDK]`` Added the latest HIL Engine API to mock-up skeleton (Start
   and Stop listeners hooks)

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
