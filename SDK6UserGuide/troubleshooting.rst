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

- For IntelliJ IDEA, go to ``File`` > ``Settings...`` > ``Build, Execution, Deployment`` > ``Build Tools`` > ``Gradle``,
  and make sure the selected ``Gradle JVM`` is a supported JDK version:

	.. figure:: images/intellij-project-jdk.png
		:alt: Project JDK in IntelliJ IDEA
		:align: center
		:scale: 70%

		Project JDK in IntelliJ IDEA

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

it means the ``version`` property is missing and should be defined in the module build file.
See :ref:`sdk_6_publish_project` for more information.

Fail to load a VEE Port as dependency
-------------------------------------

When a VEE Port is defined as a dependency, the build of the project can fail with the following message::

	> No 'release.properties' and 'architecture.properties' files found.
  The given file <path/to/file> is not a VEE Port archive.

If the dependency is a valid VEE Port, this error probably means that several artifacts of the VEE Port have been published
with the ``default`` Ivy configuration.
To fix this issue, you can select the right artifact by adding information on the one to fetch in the ``artifact`` block, for example::

	microejVeePort("com.mycompany:myveeport:1.0.0") {
		artifact {
			name = "artifact-name"
			type = "zip"
		}
	}

This will select the artifact with the name ``artifact-name`` and with the type ``zip``.

Forked Java process still running after the interruption of a build
-------------------------------------------------------------------

If a build is interrupted before the end of its execution, the next build can fail with error such as::

	Failed to delete some children. This might happen because a process has files open or has its working directory set in the 
	target directory.

This error is probably due to a forked Java process that has been started during the execution of the build and that is still running.
By default Gradle uses `the Gradle Daemon <https://docs.gradle.org/current/userguide/gradle_daemon.html>`__ 
to reduce the time to run a build. When a build is interrupted before the end of its execution, 
the Gradle Daemon does not stop the forked Java processes that have been started during the build.
To fix this issue, you have to stop the forked Java process manually.

The following tasks use a forked Java process:

- ``runOnSimulator``
- ``buildExecutable``

It is possible to avoid this issue by disabling the Gradle Daemon with the ``--no-daemon`` flag, for example::

	gradle runOnSimulator --no-daemon


Slow Build because of File System Watching
------------------------------------------

In some cases, Gradle may take a lot of time to execute its build.
One of the possible reasons is the file system watching feature which allows Gradle to track any change on the file system.
Depending on your environment, this feature can impact the build execution time significantly.
For example, when network drives are mapped and the network connection experiences instability.

This feature can be disabled for a build by passing the ``--no-watch-fs`` option in the command line, for example::

	./gradlew build --no-watch-fs

or for all builds by setting the following property in the ``$USER_HOME/.gradle/gradle.properties`` file::
	
	org.gradle.vfs.watch=false

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.