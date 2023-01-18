--------------------------
SDK Distribution Changelog
--------------------------

[22.06] - 2022-06-29
~~~~~~~~~~~~~~~~~~~~

.. note::
   
   This release requires a JDK 11 and therefore an Architecture ``7.17.0`` or higher.
   Please refer to :ref:`system-requirements` for more details.

-  Included :ref:`SDK 5.6.0 <changelog-5.6.0>`.
-  Added support for macOS aarch64 (M1 chip).
-  Updated to Eclipse version ``2022-03``.
-  Changed required Java Runtime to JDK 11 (JRE and other versions are not supported anymore).

[21.11] - 2021-11-15
~~~~~~~~~~~~~~~~~~~~

.. note::

   This release prepares for a future JRE 11 support.
   However, the only officially supported JRE version is still JRE 8. Please refer to :ref:`system-requirements` for more details.

-  Included :ref:`SDK 5.5.0 <changelog-5.5.0>`.
-  Updated installer to accept both JRE 8 and JRE 11.
-  Fixed error ``Error while loading manipulator`` when installing SDK updates on MacOS.
-  Updated End User License Agreement.

[21.03] - 2021-03-25
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`SDK 5.4.0 <changelog-5.4.0>`.
-  Updated End User License Agreement.
  
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

-  See :ref:`SDK 5.4.0 Known Issues <known-issues-5.4.0>` section

[20.12] - 2020-12-11
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`SDK 5.3.1 <changelog-5.3.1>`
-  Disabled Java version check when updating SDK (see
   :ref:`known issues of SDK Distribution 20.10 <known-issues-20.10>`)

[20.10] - 2020-10-30
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`SDK 5.3.0 <changelog-5.3.0>`
-  Updated to Eclipse version ``2020-06``
-  Fixed low quality MacOS SDK icons

.. note::

   Starting with this release, only 64bits JRE are supported
   because 32bits JRE support has been removed since Eclipse version
   ``2018-12``. See `this
   link <https://www.eclipse.org/eclipse/news/4.10/platform.php#java32-removal>`__
   for more details.

.. _known-issues-20.10:

**KNOWN ISSUES**:

-  Projects configured with Null Analysis must be updated to import `EDC API 1.3.3`_
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

.. _EDC API 1.3.3: https://repository.microej.com/modules/ej/api/edc/1.3.3/

[20.07] - 2020-07-28
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`MicroEJ SDK 5.2.0 <changelog-5.2.0>`
-  Updated the default microej repository folder name (replaced
   SDK version by the distribution number)
-  Added ``Dist.`` prefix in installer name (e.g.
   ``MicroEJ SDK Dist. 20.07``) to avoid confusion between SDK
   distribution vs SDK version
-  Updated SDK End User License Agreement
-  Disabled popup window when installing a SDK update site
   (allow to install unsigned content by default)

[19.05] - 2019-05-17
~~~~~~~~~~~~~~~~~~~~

-  Included :ref:`SDK version 5.1.0 <changelog-5.1.0>`
-  Updated MicroEJ icons (``16x16`` and ``32x32``)
-  Updated the publisher of Windows executables (``MicroEJ`` instead of
   ``IS2T SA.``)
-  Updated the JRE link to download in case the default JRE is not
   compatible. (``https://www.java.com`` is deprecated)

[19.02] - 2019-02-22
~~~~~~~~~~~~~~~~~~~~

-  Updated to Eclipse Oxygen version ``4.7.2``
-  Included :ref:`SDK version 5.0.1 <changelog-5.0.1>`
-  Included Sonarlint version ``4.0.0``

-------------
SDK Changelog
-------------

.. _changelog-5.6.2:

[5.6.2] - 2022-08-31
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Fixed error when opening some heap dump files.
-  Fixed error when saving a EJF file with the Font Designer.

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  Fixed invalid module name when using spaces in the project name.

Skeletons
^^^^^^^^^

-  Fixed wrong package name in the class generated when creating a firmware-multiapp project.

.. _changelog-5.6.1:

[5.6.1] - 2022-07-08
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Removed check on JRE version when opening a workspace.

.. _changelog-5.6.0:

[5.6.0] - 2022-06-29
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Added support for JDK 11.
-  Changed Easyant targets executed by ``mmm build`` from ``clean,verify`` to ``clean,package``.
-  Upgraded Front Panel plugin to version 6.1.3 to remove warning on fp framework.
-  Updated Workspace settings to ignore errors in Ant build files by default.
-  Fixed error when opening a Heap Dump file not part of the workspace.
-  Fixed error when opening a Map file not part of the workspace.
-  Removed Resources Center view.

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  Added the capability to override module organisation/name/revision with :ref:`mmm_build_system_options`.
-  Added error message when using non-supported Eclipse Link Folders.
-  Updated End User License Agreement.
-  Fixed MMM failure when resolving a dependency with a version containing a number with 4 digits.
-  Fixed error when building a meta-build project with public sub-modules and using target ``verify``.

Build Types
^^^^^^^^^^^

-  Added support for Kernel Runtime Environments (``build-firmware-multiapp``, ``build-runtime-api`` and ``build-application``).
-  Added option ``javadoc.modules.excludes`` to exclude modules from Javadoc generation when building a module repository.

Build Plugins
^^^^^^^^^^^^^

-  Updated ``elf-utils`` plugin to load the ELF related tools from the architecture/platform.

Skeletons
^^^^^^^^^

-  Added JUnit dependency to all Java module skeletons (including default JUnit tests pattern).
-  Updated ``firmware-singleapp`` and ``firmware-multiapp`` skeletons for building the executable by default.
-  Updated Sandboxed Application skeleton (``application``) to be compatible with any Kernel (based on KF ``FeatureEntryPoint``).

.. _changelog-5.5.3:

[5.5.3] - 2022-05-03
~~~~~~~~~~~~~~~~~~~~

MicroEJ Module Manager
""""""""""""""""""""""

-  Fixed error ``Can't parse module descriptor`` when building a Module on Windows with a JDK 8.0.331+.

.. _changelog-5.5.2:

[5.5.2] - 2021-12-22
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Fixed Addon Processors of a project in a workspace being applied to others projects.

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  Updated Log4j in Artifact Checker and Cobertura plugins to version 2.17.0.

.. _changelog-5.5.1:

[5.5.1] - 2021-12-02
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Fixed wrong category name in ``New Project`` wizard.

.. _changelog-5.5.0:

[5.5.0] - 2021-11-15
~~~~~~~~~~~~~~~~~~~~

.. note::
   
   This release prepares for a future JRE 11 support.
   However, the only officially supported JRE version is still JRE 8. Please refer to :ref:`system-requirements` for more details.

General
"""""""

-  Added Add-On Processor resolution in workspace.
-  Updated tools for both JRE 8 and JRE 11 compatibility.
-  Fixed corrupted font file created by the Font designer when importing large number of glyphs.
-  Updated Architecture version check during Pack import (``greaterOrEqual`` instead of ``compatible``). This allows to import :ref:`pack_architecture_specific` and :ref:`pack_generic_legacy` on future Architecture versions ``8.x``.
-  Updated End User License Agreement.

MicroEJ Module Manager
""""""""""""""""""""""

-  Added ``bin`` folder to ``.gitignore`` file of module natures Java project skeleton.
-  Added Null Analysis configuration to ``artifact-checker``. When building a module repository, null analysis configuration is only checked on the highest module version included in the repository.
-  Added Eclipse Public License v2.0 to the list of default licenses allowed for ``artifact-checker``.
-  Clarified input messages of ``mmm init`` command.
-  Updated ``artifact-checker`` plugin binding to target ``verify``. This allow module checks to be executed on builds triggered by a pull request (no publication).
-  Fixed missing ``artifact-checker`` plugin to some module natures (``custom``, ``firmware-multiapp``, ``firmware-singleapp``, ``microej-javaimpl``, ``microej-mock``, ``microej-testsuite``, ``product-java``).
-  Fixed ``mmm run`` execution on a ``firmware-singleapp`` module (do not trigger the Firmware build).
-  Fixed ``kf-testsuite`` plugin test project build.
-  Added support of branch analysis with Sonar.
-  Added ability to package private dependencies to ``mock`` module natures (configuration ``embedded``).
-  Added ``testsuite`` and ``javadoc`` plugin to ``firmware-singleapp`` module nature.
-  Added ``ssh`` deployment to ``microej-kf-testsuite`` plugin.
-  Updated ``firmware-multiapp`` to remove the ``bsp`` directory in Virtual Devices.
-  Updated ``firmware-multiapp`` to allow Virtual Devices for launching a specific main class other than the Kernel main class.
   This is useful for running JUnit tests using a Virtual Device instead of a Platform.
-  Updated ``firmware-multiapp`` to allow Virtual Devices for automatically launching a Sandboxed Application project in the SDK.
-  Updated ``firmware-multiapp`` to automatically configure the Virtual Device Kernel UID when a Firmware is built.
-  Fixed ``firmware-multiapp`` skeleton default dependencies with only modules available in MicroEJ Central Repository.
-  Fixed ``firmware-multiapp`` unexpected build error when no declared System Application.
-  Fixed ``firmware-multiapp`` build which may fail an unexpected ``Unresolved Dependencies`` error the first time,
   for Kernel APIs module dependencies (configuration ``kernelapi``) or Virtual Device specific modules dependencies (configuration ``default-vd``).
-  Fixed ``firmware-multiapp`` unexpected build error when no Application (``.wpk`` file) found in the dropins folder.
-  Fixed ``firmware-multiapp`` unexpected build error when no declared System Application.
-  Fixed ``firmware-singleapp`` and ``firmware-multiapp`` skeletons wrong package name generation for the default Main class.
-  Fixed ``artifact-repository`` changelog check for modules with a snapshot version.

.. _changelog-5.4.1:

[5.4.1] - 2021-04-16
~~~~~~~~~~~~~~~~~~~~

.. note::
   
   This release is both compatible with Eclipse version ``2020-06``
   and Eclipse Oxygen, so it can still be installed on a previous
   SDK Distribution.

MicroEJ Module Manager
""""""""""""""""""""""

-  Fixed missing ``repository`` configuration in
   ``artifact-repository`` skeleton (this configuration is required to
   include modules bundled in an other module repository)
-  Fixed missing some old build types versions that were
   removed by error. (introduced in SDK ``5.4.0``, please refer
   to the :ref:`Known Issues <known-issues-5.4.0>` section for more details)
-  Fixed wrong version of module built in a meta-build
   (module was published with the module version instead of the snapshot
   version)
-  Fixed code coverage analysis on source code (besides on
   bytecode) thanks to the property ``cc.src.folders`` (only for
   architectures in version 7.16.0 and beyond)

.. _changelog-5.4.0:

[5.4.0] - 2021-03-25
~~~~~~~~~~~~~~~~~~~~

.. note::
   
   This release is both compatible with Eclipse version ``2020-06``
   and Eclipse Oxygen, so it can still be installed on a previous
   SDK Distribution.

.. _known-issues-5.4.0:

Known Issues
""""""""""""

-  Some older build types versions have been removed by error.
   Consequently, using SDK ``5.4.0``, it may be not possible to
   build modules that have been created with an older SDK
   version (For example, `MicroEJ
   GitHub <https://github.com/MicroEJ/>`__ code). The list of missing
   build types:

   -  build-application ``7.0.2``
   -  build-microej-javalib ``4.1.1``
   -  build-firmware-singleapp ``1.2.10``
   -  build-microej-extension ``1.3.2``

General
"""""""

-  Added MicroEJ Module Manager Command Line Interface in
   Build Kit
-  Added ignore optional compilation problems in Addon
   Processor generated source folders
-  Added logs to Standalone Application build indicating
   the mapping of Foundation Libraries to the Platform
-  Updated End User License Agreement
-  Added the latest HIL Engine API to mock-up skeleton (native
   resources management)
-  Updated the Architecture import wizard to automatically
   accept Pack licenses when the Architecture license is accepted

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  Added JSCH library to execute MicroEJ test suites on
   Device through ssh
-  Added pre-compilation phase before executing Addon
   Processor to have compiled classes available
-  Updated the default settings file to import modules from
   `MicroEJ Developer
   repository <https://forge.microej.com/artifactory/microej-developer-repository-release/>`__
   (located at ``${user.dir}\.microej\microej-ivysettings-5.4.xml``)

Build Types
^^^^^^^^^^^

-  Updated all relevant build types to load the Platform
   using the ``platform`` configuration instead of the ``test``
   configuration:

   -  Sandboxed Application (``application``)
   -  Foundation Library Implementation (``javaimpl``)
   -  Addon Library (``javalib``)
   -  MicroEJ Testsuite (``testsuite``)
-  Updated Module Repository to allow to partially include
   an Architecture module (``eval`` and/or ``prod``)
-  Fixed potential Addon Processor error
   ``NoClassDefFoundError: ej/tool/addon/util/Message`` depending on the
   resolution order
-  Removed javadoc generation for ``microej-extension``

Build Plugins
^^^^^^^^^^^^^

-  Updated Addon Processor to fail the build when an error
   is detected. Error messages are dumped to the build logs.
-  Updated Platform Loader to handle Platform module
   (``.zip`` file)
-  Updated Platform Loader to handle Virtual Device module
   (``.vde`` file) declared as a dependency. It worked before only by using the ``dropins``
   folder.
-  Updated Platform Loader to list the Platforms locations
   when too many Platform modules are detected

Skeletons
^^^^^^^^^

-  Fixed wrong ``README.md`` generation for
   ``artifact-repository`` skeleton
-  Removed useless files in ``microej-javaapi``,
   ``microej-javaimpl`` and ``microej-extension`` skeletons (intern
   changelog and ``.dbk`` file)

.. _changelog-5.3.1:

[5.3.1] - 2020-12-11
~~~~~~~~~~~~~~~~~~~~

.. note::
   
   This release is both compatible with Eclipse version
   ``2020-06`` and Eclipse Oxygen, so it can still be installed on a
   previous SDK Distribution.

General
"""""""

-  Fixed missing default settings file for connecting
   MicroEJ Central Repository when starting a fresh install (introduced
   in ``5.3.0``)

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  Fixed potential build error when computing Sonar
   classpath from dependencies (``ivy:cachepath`` task was sometimes
   using a wrong cache location)

Skeletons
^^^^^^^^^

-  Fixed skeleton dependency to `EDC API 1.3.3`_
   to avoid an Eclipse JDT builder error when Null Analysis is enabled
   (see :ref:`known issues of SDK Distribution 20.10 <known-issues-20.10>`)

.. _changelog-5.3.0:

[5.3.0] - 2020-10-30
~~~~~~~~~~~~~~~~~~~~

.. note::
   
   This release is both compatible with Eclipse version
   ``2020-06`` and Eclipse Oxygen, so it can still be installed on a
   previous SDK Distribution.

.. _known-issues-5.3.0:

Known Issues
""""""""""""

-  Library module build may lead to unexpected
   ``Unresolved Dependencies`` error in some cases (in ``sonar:init``
   target / ``ivy:cachepath`` task). Workaround is to trigger the
   library build again.

General
"""""""

-  Fixed various plugins for Eclipse version ``2020-06``
   compatibility (icons, project explorer menu entries)
-  Fixed closed module.ivy files after an SDK restart that
   were opened before
-  Removed license check before launching an Application on
   Device
-  Disabled ``Activate on new event`` option of the Error
   Log view to prevent popup of this view when an internal error is
   thrown
-  Removed license check before Platform build
-  Updated filter of the Launch Group configuration (exclude
   the deprecated Eclipse CDT one)
-  Fixed inclusion of mock project dependencies in launcher
   mock classpath
-  Enhance error message in Platform editor (``.platform``
   files) when the required Architecture has not been imported (displays
   Architecture information)

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  Fixed workspace default settings file when clicking on
   the ``Default`` button
-  First wrong resolved dependency when `ChainResolver returnFirst option <https://ant.apache.org/ivy/history/2.5.0/resolver/chain.html>`__
   is enabled and the module to resolve is already in the cache
-  Fixed potential build module crash (``Not comparable``
   issue) when resolving module dependencies across multiple
   configurations

Build Types
^^^^^^^^^^^

-  Exclude packs from artifact checker when building a
   module repository
-  Merged Foundation & Add-On Libraries javadoc when
   building a module repository
-  Added Module dependency line for each type in module
   repository javadoc
-  Added an option to skip deprecated types, fields,
   methods in module repository javadoc
-  Allow to include or exclude Java packages in module
   repository javadoc
-  Added an option ``skip.publish`` to skip artifacts
   publication in ``build-custom`` build type
-  Allow to define Application options from build option
   using the ``platform-launcher.inject.`` prefix
-  Added generation and publication of code coverage report
   after a testsuite execution. The report generation is enabled under
   the following conditions:

   -  at least one test is executed,
   -  tests are executed on Simulator,
   -  build option ``s3.cc.activated`` is set to ``true`` (default),
   -  the Platform is based on an Architecture version ``7.12.0`` or higher
   -  if testing a Foundation Library (using ``microej-testsuite``), build option ``microej.testsuite.cc.jars.name.regex`` must be set to match the simple name of the library being covered (e.g. ``edc-*.jar`` or ``microui-*.jar``)
-  Fixed sonar false negative Null Analysis detection in
   some cases
-  Added a better error message for Studio rebrand build when
   ``izpack.microej.product.location`` option is missing
-  Deprecated ``build-microej-ri`` and disabled documentation
   generation (useless docbook toolchains have been removed to reduce
   the bundle size: ``-150MB``)

Skeletons
^^^^^^^^^

-  Fixed ``microej-mock`` content script initialization
   folder name


.. _changelog-5.2.0:

[5.2.0] - 2020-07-28
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Added ``Dist.`` prefix in default workspace and
   repository name to avoid confusion between SDK distribution
   vs SDK version
-  Replaced ``Version`` by ``Dist.`` in :guilabel:`Help` >
   :guilabel:`About MicroEJ® SDK` menu. The SDK
   version is available in ``Installation Details`` view.
-  Replaced ``IS2T S.A.`` and ``MicroEJ S.A.`` by
   ``MicroEJ Corp.`` in :guilabel:`Help` > :guilabel:`About MicroEJ® SDK` menu.
-  Updated Front Panel plugin to version 6.1.1
-  Removed MicroEJ Copyright in Java class template and
   skeletons files
-  Fixed Stopping a MicroEJ launch in the progress view
   doesn't stop the launch

MicroEJ Module Manager
""""""""""""""""""""""

General
^^^^^^^

-  Added a new configuration page
   (:guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Module Manager`). This page is a merge of
   formerly named ``Easyant4Eclipse`` preferences page and
   ``Ivy Settings`` relevant options for MicroEJ.
-  Added :guilabel:`Export` > :guilabel:`MicroEJ` > :guilabel:`Module Manager Build Kit`
   wizard, to extract the files required for automating MicroEJ modules
   builds out of the IDE.
-  Added :guilabel:`New` > :guilabel:`MicroEJ` > :guilabel:`Module Project` wizard
   (formerly named ``New Easyant Project``), with module fields content
   assist and alphabetical sort of the skeletons list
-  Added :guilabel:`Import` > :guilabel:`MicroEJ` > :guilabel:`Module Repository` wizard to
   automatically configure workspace with a module repository (directory
   or zip file)
-  Added :guilabel:`New MicroEJ Add-On Library Project` wizard to
   simplify Add-On Library skeleton project creation
-  Updated the build repository
   (``microej-build-repository.zip``) to be self contained with its owns
   ``ivysettings.xml``
-  Updated Virtual Device Player (``firmware-singleapp``)
   ``launcher-windows.bat`` (use ``launcher-windows-verbose.bat`` to get
   logs)
-  Renamed the classpath container to
   ``Module Dependencies`` instead of ``Ivy``
-  Fixed Addon Processor ``src-adpgenerated`` folder
   generation when creating or importing a project with the same name
   than a previously deleted one
-  Fixed implementation of settings `ChainResolver returnFirst option <https://ant.apache.org/ivy/history/2.5.0/resolver/chain.html>`__
-  Fixed Ivy module resolution being blocked from time to
   time

Build Types
^^^^^^^^^^^

-  Fixed meta build to publish correct snapshot revisions
   for built dependencies. (Indirectly fixes ADP resolution issue when
   an Add-On Library and its associated Addon Processor were built
   together using a meta build)
-  Fixed potential infinite loop when building a Modules
   Repository with MMM semantic enabled
-  Fixed javadoc not being generated in artifactory
   repository build when ``skip.javadoc`` is set to ``false``
-  Added the capability to build partial modules
   repository, by using the user provided ``ivysettings.xml`` file to
   check the repository consistency
-  Added the possibility to partially extend the build
   repository in a module repository. The build repository can be
   referenced by a file system resolver using the property
   ``${microej-build-repository.repo.dir}``
-  Added the possibility to include a module repository
   into an other module repository (using new configuration
   ``repository->*``)
-  Added the possibility to bundle a set of Virtual Devices
   when building a branded Studio. They are automatically
   imported to the MicroEJ repository when booting on a new workspace.
-  Added the possibility to bundle a Module Repository when
   building a branded Studio. It is automatically imported and
   settings file is configured when booting on a new workspace.

Build Plugins
^^^^^^^^^^^^^

-  Added variables ``@MMM_MODULE_ORGANISATION@``,
   ``@MMM_MODULE_NAME@`` and ``@MMM_MODULE_VERSION@``\ for README.md
   file
-  Fixed ``microej-kf-testsuite`` repository access issue
   (introduced in SDK ``5.0.0``).
-  Fixed ``artifact-checker`` to accept revisions
   surrounded by brackets (as specified by
   https://keepachangelog.com/en/1.0.0/)

Skeletons
^^^^^^^^^

-  Updated ``module.ivy`` indentation characters with tabs
   instead of spaces
-  Updated ``CHANGELOG.md`` formatting
-  Updated and standardized ``README.md`` files
-  Updated dependencies in ``module.ivy`` to use the latest
   versions
-  Added ``.gitignore`` to ignore the ``target~`` and
   ``src-adpgenerated`` folder where the module is built
-  Added Sandboxed Application WPK dropins folder
   (``META-INF/wpk``)
-  Removed conf ``provided`` in ``module.ivy`` for
   foundation libraries dependencies
-  Remove MicroEJ internal site reference in ``module.ant``
   file
-  Fixed corrupted library ``workbenchExtension-api.jar``
   in ``microej-extension`` skeleton
-  Fixed corrupted library ``HILEngine.jar`` in
   ``microej-mock`` skeleton
-  Fixed javadoc content issue in Main class
   ``firmware-singleapp`` skeleton

Misc
""""

-  Updated End User License Agreement
-  Added support for generating Application Options in
   reStructured Text format

.. _changelog-5.1.2:

[5.1.2] - 2020-03-09
~~~~~~~~~~~~~~~~~~~~

MicroEJ Module Manager
""""""""""""""""""""""

-  Fixed potential build error when generating fixed
   dependencies file (``fixdeps`` task was sometimes using a wrong cache
   location)
-  Fixed topogical sort of classpath dependencies when
   building using ``Build Module`` (same as in ``IvyDE`` classpath
   sorted view)
-  Fixed resolution of modules with a version ``0.m.p``
   when transitively fetched (an error was thrown with the range
   ``[1.m.p-RC,1.m.(p+1)-RC[``)
-  Fixed missing classpath dependencies to prevent an error
   when building a standard JAR with JUnit tests


.. _changelog-5.1.1:

[5.1.1] - 2019-09-26
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Fixed files locked in ``Platform in workspace`` projects
   preventing the Platform from being deleted or rebuilt

.. _changelog-5.1.0:

[5.1.0] - 2019-05-17
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Updated MicroEJ icons (``16x16`` and ``32x32``)
-  Fixed potential long-blocking operation when launching
   an application on a Virtual Device on Windows 10 (Windows defender
   performs a slow analysis on a zip file when it is open for the first
   time since OS startup)
-  Fixed missing ADP resolution on a fresh MicroEJ
   installation
-  Fixed ADP source folders order generation in
   ``.classpath`` (alphabetical sort of the ADP id)
-  Fixed :guilabel:`Run As...` > :guilabel:`MicroEJ Application` automatic
   launcher creation: when selecting a ``Platform in workspace``, an
   other platform of the repository was used instead
-  Fixed ``Memory Map Analyzer`` load of mapping scripts
   from Virtual Devices
-  Fixed MMM and ADP resolution when importing a zip
   project in a fresh MicroEJ install
-  Fixed ADP crash when a project declares dependencies
   without a source folder
-  Fixed inability to debug an application on a Virtual
   Device if option ``execution.mode`` was specified in firmware build
   properties (now SDK options cannot be overridden)
-  Updated ``Front Panel`` plugin to comply with the new Front
   Panel engine

   -  The Front Panel engine has been refactored and moved from UI Pack to Architecture (UI pack ``12.0.0`` requires Architecture version ``7.11.0`` or higher)
   -  :guilabel:`New Front Panel Project` wizard now generates a project skeleton for this new Front Panel engine, based on MMM
   -  Legacy Front Panel projects for UI Pack ``v11.1.0`` or higher are still valid
-  Updated Virtual Device builder to speed-up Virtual Device
   boot time (System Applications are now extracted at build time)
-  Fixed inability to select a ``Platform in workspace`` in a
   MicroEJ Tool launch configuration
-  Fixed broken title in MicroEJ export menu (Platform Export)

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  Added a new option ``application.project.dir`` passed to
   launch scripts with the workspace project directory
-  Updated MMM to throw a non ambiguous error message when
   a ``module.ivy`` configured for MMM declares versions with legacy Ivy
   range notation
-  Updated MicroEJ Central Repository cache directory to
   ``${user.dir}\.microej\caches\repository.microej.com-[version]``
   instead of ``${user.dir}\.ivy2``
-  Updated ``Update Module Dependencies...`` to be disabled
   when ``module.ivy`` cannot be loaded. The menu entry is now grayed
   when the project does not declare an IvyDE classpath container
-  Fixed wrong resolution order when a module is both
   resolved in the repository and the workspace (the workspace module
   must always take precedence to the module resolved in the repository)
-  Fixed useless ``unknown resolver trace`` when cache is
   used by multiple Ivy settings configurations with different resolver
   names.
-  Fixed slow Add-On Processor generation. The classpath
   passed to ADP modules could contain the same entry multiple times,
   which leads each ADP module to process the same classpath multiple
   times.
-  Fixed misspelled recommendation message when a build
   failed
-  Fixed ``Update Module Dependencies...`` tool: wrong
   ``ej:match="perfect"`` added where it was expected to be
   ``compatible``
-  Fixed ``Update Module Dependencies...`` tool: parse
   error when ``module.ivy``\ contains ``<artifact type="rip"/>``
   element
-  Fixed resolution and publication of a module declared
   with an Ivy branch
-  Fixed character ``'-'`` rejected in module organisation
   (according to MMM specification ``2.0-B``)
-  Fixed ADP resolution error when the Add-On Processor
   module was only available in the cache
-  Fixed potential build crash depending on the build kit
   classpath order (error was ``This module requires easyant [0.9,+]``)
-  Fixed ``product-java`` broken skeleton

Build Types
^^^^^^^^^^^

-  Updated Platform Loader error message when the property
   ``platform-loader.target.platform.dir`` is set to an invalid
   directory
-  Fixed meta build property substitution in
   ``*.modules.list`` files
-  Fixed missing publications for ``README.md`` and
   ``CHANGELOG.md`` files
-  Update skeletons to fetch latest libraries (Wadapps
   Framework ``v1.10.0`` and Junit ``v1.5.0``)
-  Updated ``README.md`` publication to generate MMM usage
   and the list of Foundation Libraries dependencies
-  Added a new build nature for building platform options
   pages (``microej-extension``)
-  Updated Virtual Device builder to speed-up Virtual Device
   boot time (System Applications are now extracted at build time)
-  Fixed Virtual Device Player builder (dependencies were not
   exported into the zip file) and updated ``firmware-singleapp``
   skeleton with missing configurations

Skeletons
^^^^^^^^^

-  Updated ``CHANGELOG.md`` based on ``Keep a Changelog``
   specification (https://keepachangelog.com/en/1.0.0/)
-  Updated offline module repository skeleton to fetch in a
   dedicated cache directory under ``${user.dir}/.microej/caches``


.. _changelog-5.0.1:

[5.0.1] - 2019-02-14
~~~~~~~~~~~~~~~~~~~~

General
"""""""

-  Removed Wadapps Code generation (see migration notes
   below)
-  Added support for MicroEJ Module Manager semantic (see
   migration notes below)
-  Added a dedicated view for Virtual Devices in MicroEJ
   Preferences
-  Removed Platform related views and menus in the SDK (Import/Export and Preferences)
-  Added Studio rebranding capability (product
   name, icons, splash screen and installer for Windows)
-  Added a new meta build version, with simplified syntax
   for multi-projects build (see migration notes below)
-  Added a skeleton for building offline module
   repositories
-  Added support for importing extended characters in Fonts
   Designer
-  Allow to import Virtual Devices with ``.vde``\ extension
   (``*.jpf`` import still available for backward compatibility)
-  Removed legacy selection for Types, Resources and
   Immutables in MicroEJ Launch Configuration (replaced by ``*.list``
   files since MicroEJ ``4.0``)
-  Enabled IvyDE workspace dependencies resolution by
   default
-  Enabled MicroEJ workspace Foundation Libraries resolution
   by default
-  Added possibility for Architectures to check for a
   minimum required version of SDK (``sdk.min.version``
   property)
-  Updated ``New Standalone Application Project`` wizard to
   generate a single-app firmware skeleton
-  Updated Virtual Device Builder to manage Sandboxed
   Applications (compatible with Architectures Products ``*_7.10.0`` or
   newer)
-  Updated Virtual Device Builder to include kernel options
   (now options are automatically filled for the application developer
   on Simulator)

MicroEJ Module Manager
""""""""""""""""""""""

Build Plugins
^^^^^^^^^^^^^

-  Added IvyDE resolution from properties defined in
   :guilabel:`Windows` > :guilabel:`Preferences` > :guilabel:`Ant` > :guilabel:`Runtime` > :guilabel:`Properties`
-  Fixed *Illegal character in path* error that may occur
   when running an Add-On Processor
-  Fixed IvyDE crash when defining an Ant property file
   with Eclipse variables

Build Types
^^^^^^^^^^^

-  Kept only latest build types versions (skeletons
   updated)
-  Updated metabuild to execute tests by default for
   private module dependencies
-  Removed remaining build dependencies to JDK (Java code
   compiler and Javadoc processors). All MicroEJ code is now compiled
   using the JDT compiler
-  Introduced a new plugin for executing custom testsuite
   using MicroEJ testsuite engine
-  Fixed *MalformedURLException* error in Easyant trace
-  Fixed Easyant build crash when an Ivy settings file
   contains a cache definitions with a wildcard
-  Updated Platform Builder to keep track in the Platform of
   the architecture on which it has been built
   (``architecture.properties``)
-  Updated Virtual Device Builder to generate with ``.vde``
   extension
-  Updated Multi-app Firmware Builder to embed (Sim/Emb)
   specific modules (Add-On libraries and System Applications)
-  Fixed ``build-microej-ri`` v1.2.1 missing dependencies
   (embedded in SDK 4.1.5)

Skeletons
^^^^^^^^^

-  Updated all skeletons: migrated to latest build types,
   added more comments, copyright cleanup and configuration for MicroEJ
   Module Manager semantic)
-  Added the latest HIL Engine API to mock-up skeleton (Start
   and Stop listeners hooks)

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
