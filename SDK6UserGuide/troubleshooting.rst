.. _sdk_6_troubleshooting:

Troubleshooting
===============

Java Compiler Version Issue
---------------------------

The SDK requires a JDK 11, so when a JDK 8 is used, the following kind of errors are raised:

- When fetching the MicroEJ Gradle plugin::

	A problem occurred configuring root project 'myProject'.
	> Could not resolve all files for configuration ':classpath'.
	> Could not resolve com.microej.gradle.plugins:plugins:0.3.0.
		Required by:
			project : > com.microej.gradle.addon-library:com.microej.gradle.addon-library.gradle.plugin:0.3.0:20221118.151454-1
		> No matching variant of com.microej.gradle.plugins:plugins:0.3.0:20221118.151454-1 was found. The consumer was configured to find a runtime of a library compatible with Java 8, packaged as a jar, and its dependencies declared externally, as well as attribute 'org.gradle.plugin.api-version' with value '7.4' but:
			- Variant 'apiElements' capability com.microej.gradle.plugins:plugins:0.3.0 declares a library, packaged as a jar, and its dependencies declared externally:
				- Incompatible because this component declares an API of a component compatible with Java 11 and the consumer needed a runtime of a component compatible with Java 8
				- Other compatible attribute:
					- Doesn't say anything about org.gradle.plugin.api-version (required '7.4')
			- Variant 'javadocElements' capability com.microej.gradle.plugins:plugins:0.3.0 declares a runtime of a component, and its dependencies declared externally:
				- Incompatible because this component declares documentation and the consumer needed a library
				- Other compatible attributes:
					- Doesn't say anything about its target Java version (required compatibility with Java 8)
					- Doesn't say anything about its elements (required them packaged as a jar)
					- Doesn't say anything about org.gradle.plugin.api-version (required '7.4')
			- Variant 'runtimeElements' capability com.microej.gradle.plugins:plugins:0.3.0 declares a runtime of a library, packaged as a jar, and its dependencies declared externally:
				- Incompatible because this component declares a component compatible with Java 11 and the consumer needed a component compatible with Java 8
				- Other compatible attribute:
					- Doesn't say anything about org.gradle.plugin.api-version (required '7.4')
			- Variant 'sourcesElements' capability com.microej.gradle.plugins:plugins:0.3.0 declares a runtime of a component, and its dependencies declared externally:
				- Incompatible because this component declares documentation and the consumer needed a library
				- Other compatible attributes:
					- Doesn't say anything about its target Java version (required compatibility with Java 8)
					- Doesn't say anything about its elements (required them packaged as a jar)
					- Doesn't say anything about org.gradle.plugin.api-version (required '7.4')

- When using the MicroEJ Gradle plugin::

	Cause: com/microej/gradle/plugins/MicroejApplicationGradlePlugin has been compiled by a more recent version of the Java Runtime (class file version 55.0), this version of the Java Runtime only recognizes class file versions up to 52.0

The solution is to use a JDK 11 or a higher LTS version (``11``, ``17`` or ``21``) to fix this error:

- For the command line interface, make sure that a supported JDK version is defined in the ``PATH`` environment.
  To check, run ``java -version``. You should see something like this::

    $ java -version
    openjdk version "11.0.14.1" 2022-02-08
    OpenJDK Runtime Environment Temurin-11.0.14.1+1 (build 11.0.14.1+1)
    OpenJDK 64-Bit Server VM Temurin-11.0.14.1+1 (build 11.0.14.1+1, mixed mode)

  Alternatively, you can set the ``JAVA_HOME`` environment variable to point to the installation directory of the JDK.

- For IntelliJ IDEA and Android Studio, go to :guilabel:`File` > :guilabel:`Settings...` > :guilabel:`Build, Execution, Deployment` > :guilabel:`Build Tools` > :guilabel:`Gradle`,
  and make sure the selected :guilabel:`Gradle JVM` is a supported JDK version:

	.. figure:: images/intellij-project-jdk.png
		:alt: Project JDK in IntelliJ IDEA and Android Studio
		:align: center
		:scale: 70%

		Project JDK in IntelliJ IDEA and Android Studio


Unresolved Dependency When No Repository
----------------------------------------

If this kind of message appears when resolving plugins or modules dependencies:

.. code:: console

	* What went wrong:
	Plugin [id: 'com.microej.gradle.application', version: '1.4.0'] was not found in any of the following sources:

	- Gradle Core Plugins (plugin is not in 'org.gradle' namespace)
	- Included Builds (No included builds contain this plugin)
	- Plugin Repositories (could not resolve plugin artifact 'com.microej.gradle.application:com.microej.gradle.application.gradle.plugin:1.1.0')
	Searched in the following repositories:
		Gradle Central Plugin Repository

or this kind:

.. code:: console

	* What went wrong:
	Execution failed for task ':compileJava'.
	> Could not resolve all files for configuration ':compileClasspath'.
	> Cannot resolve external dependency ej.api:edc:1.3.7 because no repositories are defined.
		Required by:
			root project :

It means that no module or plugin repository has been defined. 
Make sure that the repositories have been configured as described in the :ref:`sdk_6_configure_repositories` section.
In particular, make sure that the Gradle Init script is in the ``.gradle/init.d`` folder in the Gradle User Home folder.
The Gradle User Home folder is defined by default to the OS User Home folder, 
and can be changed by setting the ``GRADLE_USER_HOME`` environment variable 
or in the IDE settings (see `Intellij IDEA documentation <https://www.jetbrains.com/help/idea/gradle-settings.html>`__).

Unresolved Dependency in Repositories
-------------------------------------

If this kind of message appears when resolving plugins or modules dependencies:

.. code:: console

	* What went wrong:
	Plugin [id: 'com.microej.gradle.application', version: '1.4.0'] was not found in any of the following sources:

	- Gradle Core Plugins (plugin is not in 'org.gradle' namespace)
	- Included Builds (No included builds contain this plugin)
	- Plugin Repositories (could not resolve plugin artifact 'com.microej.gradle.application:com.microej.gradle.application.gradle.plugin:1.4.0')
	Searched in the following repositories:
		microEJCentral(https://repository.microej.com/modules)
		microEJForgeCentral(https://forge.microej.com/artifactory/microej-central-repository-release)
		microEJForgeDeveloper(https://forge.microej.com/artifactory/microej-developer-repository-release)

or this kind:

.. code:: console

   * What went wrong:
   Execution failed for task ':compileJava'.
   > Could not resolve all files for configuration ':compileClasspath'.
     > Could not find com.mycompany:mymodule:M.m.p.
        Searched in the following locations:
          - https://my-company-first-repository/com/mycompany/mymodule/M.m.p/kf-M.m.p.pom
          - https://my-company-first-repository/com/mycompany/mymodule/M.m.p/ivy-M.m.p.xml
          - https://my-company-second-repository/com/mycompany/mymodule/M.m.p/kf-M.m.p.pom
          - https://my-company-second-repository/com/mycompany/mymodule/M.m.p/ivy-M.m.p.xml
        Required by:
            project :


First, check that either the requested plugin or module exists in the listed repositories.

- If the plugin or module does not exist, 
  
  - if it is declared as a :ref:`direct dependency <sdk_6_add_dependency>`, the module repository is not compatible with your source code. 
    You can either check if another module version is available in the repository or add the missing module to the repository.
  - otherwise, this is likely a missing transitive module dependency. The module repository is not consistent.
    Check the module repository and make sure all the transitive dependencies exist.

- If the module exists, this may be due to a missing repository in the configuration.
  Check that your repository appears in the list of URLs below the error line:

  .. code:: console

     Searched in the following locations:
  
  If the URL of your repository is not listed, add it to :ref:`the list of the repositories <sdk_6_configure_repositories>`.

- If the repository is correctly configured, this may be a network connection error. 
  We can check in the debug logs, by adding the ``--debug`` arguments in the Gradle command line.

Otherwise, if your module repository is an URL, check for an :ref:`sdk_6_troubleshooting_invalid_certificate` issue.


.. _sdk_6_troubleshooting_invalid_certificate:

Invalid SSL Certificate
-----------------------
         
If a dependency cannot be retrieved from a remote repository, this may be due to a missing or incorrect SSL certificate.
It can be checked in the debug logs, by adding the ``--debug`` and ``-Djavax.net.debug=all`` arguments in the Gradle command line, for example::

  ./gradlew build --debug -Djavax.net.debug=all

If the SSL certificate is missing or incorrect, the following line should appear:

  .. code:: console

	PKIX path building failed: sun.security.provider.certpath.SunCertPathBuilderException: unable to find valid certification path to requested target

This can be raised in several cases, such as:

- an artifact repository configured in the MicroEJ Module Manager settings using a self-signed SSL certificate or a SSL certificate not trusted by the JDK.
- the requests to an artifact repository configured in the MicroEJ Module Manager settings are redirected to a proxy server using a SSL certificate not trusted by the JDK.

In all cases, the SSL certificate (used by the artifact repository server or the proxy) must be added to the JDK trust store that is running Gradle.

Before updating the SSL certificate, it is recommended to exit all your IDE projects and `stop Gradle daemons <https://docs.gradle.org/current/userguide/gradle_daemon.html#sec:stopping_an_existing_daemon>`_ (all versions).
One simple way is to list all Java processes and kill the ones named ``GradleDaemon``:

.. code-block:: console
   :emphasize-lines: 3,6

	./jps
	12768
	17792 GradleDaemon
	16920
	4712 Jps
	1820 GradleDaemon

Also, if you don't know which JDK is running Gradle, you can first fix the JDK used by Gradle by following :ref:`sdk_6_howto_gradle_java_home`.

Ask your System Administrator, or retrieve the SSL certificate and add it to the JDK trust store:

- on Windows

  #. Install `Keystore Explorer <http://keystore-explorer.org/downloads.html>`_.
  #. Start Keystore Explorer, and open file ``[JRE_HOME]/lib/security/cacerts`` or ``[JDK_HOME]/jre/lib/security/cacerts`` with the password ``changeit``.
     You may not have the right to modify this file. Edit rights if needed before opening it or open Keystore Explorer with admin rights.
  #. Click on :guilabel:`Tools`, then :guilabel:`Import Trusted Certificate`.
  #. Select your certificate.
  #. Save the ``cacerts`` file.

- on Linux/macOS

  #. Open a terminal.
  #. Make sure the JDK's ``bin`` folder is in the ``PATH`` environment variable.
  #. Execute the following command::

      keytool -importcert -v -noprompt -trustcacerts -alias myAlias -file /path/to/the/certificate.pem -keystore /path/to/the/truststore -storepass changeit


If the problem still occurs, there should be a trace which indicates the beggining of the handshake phase of the SSL negotiation::

	 2023-12-15T17:32:47.442+0100 [DEBUG] [org.apache.http.conn.ssl.SSLConnectionSocketFactory] Starting handshake

The error very probably occurs during this phase.
There should be the following trace before the error::

   Consuming server Certificate handshake message

The traces below this one indicates the SSL certificate (or the SSL certificates chain) presented by the server.
This certificate or one of the root or intermediate certificates must be added in the JDK truststore as explained previously.

Failing Resolution in ``adp`` Task
----------------------------------

During the build of a project, the error ``Cannot locate module version for non-maven layout`` may be raised::

	Execution failed for task ':adp'.
	> Could not resolve all files for configuration ':addonProcessorClasspath'.
		> Could not download binary-nls-processor-2.4.2.adp (com.microej.tool.addon.runtime:binary-nls-processor:2.4.2)
			> Cannot locate module version for non-maven layout.
		> Could not download js-processor-0.13.0.adp (com.microej.tool.addon.runtime:js-processor:0.13.0)
			> Cannot locate module version for non-maven layout.
		> Could not download junit-processor-1.7.1.adp (ej.tool.addon.test:junit-processor:1.7.1)
			> Cannot locate module version for non-maven layout.

This is due to a wrong pattern in the declaration of the Ivy repositories.
Check your Ivy repositories and make sure the value of the ``artifact`` of the ``patternLayout`` block is set to ``[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])``.
For example::

	ivy {
		url = uri("https://repository.microej.com/5/artifacts/")
		patternLayout {
			artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
			ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
			setM2compatible(true)
		}
	}

Missing Version for Publication
-------------------------------

If the following message is displayed when publishing a module::

	The project version must be defined.

It means the ``version`` property is missing and should be defined in the module build file.
See :ref:`sdk_6_publish_project` for more information.

Fail to load a VEE Port as dependency
-------------------------------------

When a VEE Port is defined as a dependency, the build of the project can fail with the following message::

	> No 'release.properties' and 'architecture.properties' files found.
  The given file <path/to/file> is not a VEE Port archive.

If the dependency is a valid VEE Port, this error probably means that several artifacts of the VEE Port have been published
with the ``default`` Ivy configuration.
To fix this issue, you can select the right artifact by adding information on the one to fetch in the ``artifact`` block, for example::

	microejVee("com.mycompany:myveeport:1.0.0") {
		artifact {
			name = "artifact-name"
			type = "zip"
		}
	}

This will select the artifact with the name ``artifact-name`` and with the type ``zip``.

Slow Build because of File System Watching
------------------------------------------

In some cases, Gradle may take a lot of time to execute its build.
One of the possible reasons is the file system watching feature which allows Gradle to track any change on the file system.
Depending on your environment, this feature can impact the build execution time significantly.
For example, when network drives are mapped and the network connection experiences instability.

This feature can be disabled for a build by passing the ``--no-watch-fs`` option in the command line, for example::

	./gradlew build --no-watch-fs

or for all builds by setting the following property in the ``<USER_HOME>/.gradle/gradle.properties`` file::
	
	org.gradle.vfs.watch=false

Missing Tasks in the Gradle view of Android Studio
--------------------------------------------------

In some cases, Android Studio may not build all the Gradle tasks, the :guilabel:`Task list not built...` message is displayed:

	.. figure:: images/android-studio-gradle-tasks.png
		:alt: Incomplete Gradle tasks list in Android Studio
		:align: center
		:scale: 70%

To build all the Gradle tasks in Android Studio:

- Go to :guilabel:`File` > :guilabel:`Settings` > :guilabel:`Experimental`,
- Enable the option: :guilabel:`Configure all Gradle tasks during Gradle Sync (...)`.

Back in the Gradle task view:

- Right-click on the project name,
- Select :guilabel:`Reload Gradle Project`.

	.. figure:: images/android-studio-reload-gradle-project.png
		:alt: Reload the Gradle Project in Android Studio
		:align: center
		:scale: 70%


.. note::

  By default, all supported IDEs require the user to explicitly trigger the reload of a Gradle project when its configuration has changed.
  However you can configure your IDE to automatically reload your project. 
  Refer to the :ref:`sdk_6_howto_gradle_autoreloading` section for more information.

Code Detected as Unreachable in IntelliJ
----------------------------------------

When opening MicroEJ project with IntelliJ ``2024.1``, code is displayed in grey (dead code style) after a call to a MicroEJ Foundation API.

.. figure:: images/dead_code.png
		:alt: Unreachable code is displayed in grey in IntelliJ
		:align: center
		:scale: 100%

This happens because Foundation API dependencies do not include implementation code but only throw ``RuntimeException``. IntelliJ thus infers
that the code that comes after is unreachable.

The detection of unreachable code can be disabled by going in :guilabel:`Settings...` > :guilabel:`Editor` > :guilabel:`Inspections`
and unchecking the option :guilabel:`Unreachable code` in :guilabel:`Java` > :guilabel:`Probable bugs`.

.. figure:: images/unreachable_code_setings.png
		:alt: Disable unreachable code detection in settings
		:align: center
		:scale: 70%

You can also disable unreachable code detection locally by using ``@SuppressWarnings("UnreachableCode")`` on the method or on the class.

Resolution Conflict with Testsuite Dependencies 
-----------------------------------------------

When a project and its testsuite depend on different versions of the same dependency, 
the build of the project can fail with the following message::

	Execution failed for task ':adp'.
	> Conflict(s) with a direct dependency for the following module(s):
	- ej.api:kf : the resolved version is 1.7.0 whereas the direct dependency version is 1.4.4

To fix this issue, you must update the dependency of your testsuite to use the same version as the project dependency::

	dependencies {
		implementation("ej.api:edc:1.3.7")
		implementation("ej.api:kf:1.7.0")
	}

	testing {
		suites {
			val test by getting(JvmTestSuite::class) {
				microej.useMicroejTestEngine(this)

				dependencies {
					implementation(project())
					implementation("ej.api:edc:1.3.7")
					implementation("ej.api:kf:1.7.0")
					implementation("ej.library.test:junit:1.12.0")
					implementation("org.junit.platform:junit-platform-launcher:1.8.2")
				}
			}
		}
	}

.. _sdk_6_disable_k2:

Gradle Build Files (`*.kts`) Errors in IntelliJ IDEA
----------------------------------------------------

Since version ``2025.1``, the new Kotlin K2 compiler is enabled by default to compile Gradle build scripts. For now, it requires a JDK in project's classpath in order to
interpret the build file successfully. MicroEJ projects do not have JDK in classpath, the Gradle build scripts are thus fully marked in red with the following errors::

	Cannot access 'Comparable' which is a supertype of 'KotlinBuildScript'. Check your module classpath for missing or conflicting dependencies.
	Cannot access 'Object' which is a supertype of 'KotlinBuildScript'. Check your module classpath for missing or conflicting dependencies.

To fix this, you need to

  - uncheck :guilabel:`Enable K2` in :guilabel:`Settings...` > :guilabel:`Languages & Frameworks` > :guilabel:`Kotlin`

	.. figure:: images/intellij_disable_K2.png
		:alt: Disable K2 in IntelliJ IDEA
		:align: center
		:scale: 70%

		Disable K2 in IntelliJ IDEA

	- Invalidate caches from :guilabel:`Files` > :guilabel:`Invalidate Caches...` and check all the checkboxes as shown below, and click on :guilabel:`Invalidate and Restart`

	.. figure:: images/intellij_invalidate_caches.png
		:alt: Invalidate all the caches
		:align: center
		:scale: 70%

		Invalidate all the caches

.. _sdk_6_fetch_architecture_prod:

Fail to fetch the ``prod`` version of an Architecture
-----------------------------------------------------

Fetching the ``prod`` version of an Architecture may raise the following error::

   > Could not find flopi4G25-8.3.0-prod.xpf (com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.4.0).
     Searched in the following locations:
         https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_GCC48/flopi4G25/8.4.0/flopi4G25-8.4.0-prod.xpf

This happens when a module repository containing only the ``eval`` version of the Architecture is declared before the module repository containing the ``prod`` version.
This is typically the case with the `MicroEJ Central Repository <https://developer.microej.com/central-repository/>`__ which contains only the ``eval`` versions of the public Architecture. 
If the ``prod`` version is deployed in another repository declared after the MicroEJ Central Repository, the above error is raised.

To fix this, declare the repository containing the ``prod`` version before the one containing the ``eval`` version.
Refer to :ref:`sdk_6_howto_gradle_add_repository` for more details on how to declare module repositories.

.. _sdk_6_missing_compilation_capability:

Missing Compilation Capability
------------------------------

During the build of a project (precisely the Java compilation phase), the following error may be raised::

	* What went wrong:
	Execution failed for task ':compileJava'.
	> Error while evaluating property 'javaCompiler' of task ':compileJava'.
		> Failed to calculate the value of task ':compileJava' property 'javaCompiler'.
			> Toolchain installation 'C:\Program Files (x86)\Eclipse Adoptium\jre-11.0.28.6-hotspot' does not provide the required capabilities: [JAVA_COMPILER]

This means that the Java installation used by Gradle is not a JDK but a JRE, whereas Gradle and the SDK require a JDK.
Therefore, the solution is to install and configure a JDK.
Refer to :ref:`sdk_6_check_jdk` for more information.

.. _sdk_6_vee_launch_jvm_configuration_errors:

Build Errors from JVM Memory Misconfiguration
---------------------------------------------

Below are two examples of error messages that can be raised when the JVM used to launch the VEE scripts is not configured properly.
The ouput may vary depending on the Gradle task being executed but the errors share the same root cause.

When :ref:`building an executable <sdk_6_build_executable>`::

	=============== [ Launching SOAR ] ===============
  	1 : ERROR :
  	[M2] - OutOfMemory error. Try to increase heap space using JVM option '-Xmx' (e.g. '-Xmx4096M')
  	Terminated with errors

When :ref:`running on simulator <sdk_6_run_on_simulator>`::

	=============== [ Launching on Simulator ] ===============
	"Internal limits reached. Please contact support@microej.com"

These errors are typically seen when running ``gradlew buildExecutable`` or ``gradlew runOnSimulator`` if the forked JVM is started with insufficient heap.

To resolve this, adjust the JVM memory configuration by setting the JVM options accordingly with the property ``microej.launch.jvmargs``, for example::

	./gradlew buildExecutable -Dmicroej.launch.jvmargs="-Xmx1024m -Xms512m"

.. _sdk_6_no_architecture_defined_error:

No Architecture Defined Error
-----------------------------

The following error may be raised when building a project::

	Execution failed for task ':loadVee'.
  	> No Architecture defined. An Architecture can be provided by declaring adependency with the `microejArchitecture` configuration (e.g. `microejArchitecture("com.mycompany:myArchitecture:M.m.p")').

This can happen when a VEE Port built with SDK 6 ``1.3.0`` or higher is provided to a project using an older version of the SDK 6.
To resolve this, update your project to use SDK 6 version ``1.2.0`` minimum.

Build Errors from JDK / Gradle Incompatibilities in VS Code
-----------------------------------------------------------

Gradle must be run with a compatible JDK version.
If the Gradle/JDK compatibility matrix is not respected, project sync or builds may fail, and in VS Code the Java/Gradle integration often reports non-explicit errors, making the root cause difficult to identify.

If you experience the following errors, first verify Gradle/JDK compatibility and either update the Gradle Wrapper or use a supported JDK before further troubleshooting.
Please refer to the `Gradle Compatibility Matrix <https://docs.gradle.org/current/userguide/compatibility.html#java_runtime>`__ for more details.

*JDK 25 with Gradle < 9.1.0*

.. code-block:: text

	* What went wrong:
	25.0.1

*JDK 24 and Gradle < 8.14.0*

.. code-block:: text

	* What went wrong:
	Could not create task ':outgoingVariants'.
	> Could not create task of type 'OutgoingVariantsReportTask'.
		> Could not create an instance of type org.gradle.api.tasks.diagnostics.internal.configurations.ConfigurationReportsImpl.
			> Could not create an instance of type org.gradle.api.reporting.internal.DefaultReportContainer.
				> Type T not present

*JDK 23 and Gradle < 8.10*

.. code-block:: text

	* What went wrong:
	Could not open cp_init generic class cache for initialization script
	BUG! exception in phase 'semantic analysis' in source unit '_BuildScript_' Unsupported class file major version 67
	> Unsupported class file major version 67

*JDK 22 and Gradle < 8.7*

.. code-block:: text

	* What went wrong:
	BUG! exception in phase 'semantic analysis' in source unit '_BuildScript_' Unsupported class file major version 66
	> Unsupported class file major version 66

*JDK 11  and Gradle 9+*

.. code-block:: text

	* What went wrong:
	[error] [gradle-server] Could not run build action using connection to Gradle distribution 'https://services.gradle.org/distributions/gradle-9.x.x-bin.zip'.


..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.