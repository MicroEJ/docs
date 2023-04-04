.. _sdk_6_troubleshooting:

Troubleshooting
===============

Java Compiler Version Issue
---------------------------

The SDK requires a JDK 11, so when a JDK 8 is used, the following kind of errors are raised:

- when fetching the MicroEJ Gradle plugin::

	A problem occurred configuring root project 'myProject'.
	> Could not resolve all files for configuration ':classpath'.
	> Could not resolve com.microej.gradle.plugins:plugins:0.3.0.
		Required by:
			project : > com.microej.gradle.library:com.microej.gradle.library.gradle.plugin:0.3.0:20221118.151454-1
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

- when using the MicroEJ Gradle plugin::

	Cause: com/microej/gradle/plugins/MicroejApplicationGradlePlugin has been compiled by a more recent version of the Java Runtime (class file version 55.0), this version of the Java Runtime only recognizes class file versions up to 52.0

The solution is to use a JDK 11 to fix this error:

- for the command line interface, make sure that a JDK 11 is defined in the ``PATH`` environment.
  To check, run ``java -version``. You should see something like this::

    $ java -version
    openjdk version "11.0.14.1" 2022-02-08
    OpenJDK Runtime Environment Temurin-11.0.14.1+1 (build 11.0.14.1+1)
    OpenJDK 64-Bit Server VM Temurin-11.0.14.1+1 (build 11.0.14.1+1, mixed mode)

  Alternatively, you can set the ``JAVA_HOME`` environment variable to point to the installation directory of the JDK 11.

- for IntelliJ IDEA, go to ``File`` > ``Settings...`` > ``Build, Execution, Deployment`` > ``Build Tools`` > ``Gradle``,
  and make sure the selected ``Gradle JVM`` is a JDK 11:

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

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.