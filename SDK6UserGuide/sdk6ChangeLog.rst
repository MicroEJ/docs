.. _sdk_6_changelog:

Changelog
---------

.. _changelog-0.19.0:

[0.19.0] - 2024-09-13
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to define properties of a testsuite project in the `local.properties` file.
- Display clear error message when trying to build a Feature with a Virtual Device built with a Mono-Sandbox VEE Port.

Changed
"""""""

- Application options must now add ``microej.option.*`` prefix to be defined as System properties.
- Load VEE Port MicroUI configuration files from the ``extensions/microui`` folder instead of the ``microui`` folder. 

Fixed
"""""

- Project not configured to build with Java 1.7 when runtimeClasspath configuration has already been resolved.
- Allow to produce feature files during the build in a multi-project with several feature projects.
- Use the provided Runtime API jar if it contains KF to compile the Wrapper class instead of fetching KF to avoid
  dependency resolution error with Offline repositories.
- Fail with readable error message when building a Runtime API with no Kernel API declared.
- VG Pack 1.6.0+ cannot be used for a VEE Port because it provides JAR artifacts on its default configuration (besides
  the Pack RIP).
- Use the Runtime API provided by the Kernel to build an augmented Virtual Device.

.. _changelog-0.18.0:

[0.18.0] - 2024-08-22
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to build a VEE Port.
- Retry tests when they fail to avoid flaky tests (mainly due to license check) to fail the whole build.
- Support build incremental when using a published VEE Port with Full BSP Connection.
- Add the plugin ``com.microej.gradle.runtime-api`` to build a Runtime API.
- Allow to enable/disable the publication of the Ivy descriptor.
- Allow to run dependent applications on simulator (declared with ``microejApplication``).

Fixed
"""""

- Fix publication to add dependencies defined with MicroEJ configurations to the ``.module`` and ``.pom`` files.
- Comment the ``stop`` method of the generated Wrapper class to prevent potential Sonar issue.
- Fix MicroEJ Test Engine compatibility with Gradle 8.6 and higher.
- Allow to run a Virtual Device via its launchers on a JDK version higher than 11.
- Fix build failure on multi-project with several applications depending on a kernel as project dependency.
- Some projects are not configured to be built with Java 1.7 when imported in Eclipse.
- Fix feature not found when launching a Virtual Device with installed applications.

.. _changelog-0.17.0:

[0.17.0] - 2024-05-30
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to add tools to a Virtual Device.
- Allow to fetch Runtime APIs with the ``microejRuntimeApi`` configuration.

Changed
"""""""

- Merge the ``loadXXXConfiguration`` tasks with their matching task.
- Split ``buildExecutable`` in 2 tasks to support incremental build of the ``microejapp.o`` file.
- Make FeatureEntryPoint take priority over main method when generating the Application entryPoint wrapper.

Fixed
"""""

- Re-Generate the Application entrypoint wrapper if the entrypoint class is
  modified, if the ``applicationEntryPoint`` property is changed or if the resources changed.
- Simplify Ant classpath when executing an Ant script to avoid too long classpath and support multiple Windows drives.
- Append Applications provided with the ``microejApplication`` configuration to a Virtual Device.
- Make sure to always generate the Kernel certificate if it does not exist.
- Remove deprecated APIs used to generate Application certificates.
- Log filter in Ant scripts.
- Print last relevant logs as exception message when Ant script execution fails.
- Fix failing Javadoc generation when using EDC 1.3.6 and Null Analysis annotations.
- Make the generated Wrapper Feature class call the main method of the Application with an empty array as
  parameter instead of null.
- Generate Application entrypoint wrapper if the entrypoint class extends a class implementing the
  FeatureEntryPoint interface.
- Do not embed generated KF files in Application JAR to avoid switching in KF mode when executing an Application on a
  VEE Port.
- Fix configurations used to fetch Kernels to avoid NPE during build when a project is provided
  as dependency.
- Set ADP generated folders in the sourcesets to be detected by the IDEs.
- Make sure to copy the Assembly file in the BSP when it is generated.

.. _changelog-0.16.0:

[0.16.0] - 2024-03-18
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Unify Application entryPoints.
- Allow to append an Application to a Virtual Device.
- Make ``execTool`` task available in library projects.
- Add a check on the dependencies versions format to reduce the risk of mistakes.
- Generate the Feature Definition Files and Kernel Definition Files of an Application.

Changed
"""""""

- Rename ``applicationMainClass`` property to ``applicationEntryPoint``.
- Hide MicroEJ internal tasks.
- Set the ``microej-testsuite.properties`` file as output of the ``loadTestApplicationConfiguration`` task 
  instead of its parent folder.

Fixed
"""""

- Load Kernel and Main Application properties when starting the Application on the Simulator.
- Can run more than one simulator on the same Application on IntelliJ/Windows.
- Fix Addon-Processor not reexecuted when dependencies are updated.
- Do not execute tests when building the Executable of an Application.
- MicroEJ Test Engine compatibility with Gradle 8.6.
- Do not force the compilation of J2SE tests classes in Java 7.
- Generate Jar file when building a project containing all MicroEJ artifacts.
- Clean the working files before creating the WPK file to prevent failure if the task is not UP-TO-DATE.

.. _changelog-0.15.0:

[0.15.0] - 2024-01-26
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Unify ``microejVeePort`` and ``microejKernel`` configurations into ``microejVee``.
- Add verification of dependencies checksums during build.
- Add the plugin ``com.microej.gradle.mock`` to build a Mock.
- Mention the system property to accept SDK EULA in error message.

Changed
"""""""

- Task ``:execTool`` looks for a script named after the argument NAME with the following patterns in that order: NAME, NAME.microejTool, NAME.microejLaunch.
- Align the behavior of the ``:buildFeature`` task with the ``localDeploymentSocket.microejLaunch`` script.

  - output files are derived after "application" instead of "feature" (for example "application.fo").
  - the application.main.class is set to the entryPoint defined in the .kf of the application.

Fixed
"""""

- Upgrade to junit-test-engine 0.2.2 to fix failing tests using fonts.
- Handle Security Manager removal from JDK 18+ when executing MicroEJ VEE scripts.
- Support all MicroEJ VEE (VEE Ports & Kernel) for the task ``:execTool``.

Removed
"""""""

- Remove support of dropIns folder for MicroEJ VEE (VEE Port or Kernel) selection.

.. _changelog-0.14.0:

[0.14.0] - 2024-01-03
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add Jenkinsfile files to build and test with a JDK 17 and a JDK 21 (LTS versions).

Changed
"""""""

- Do not build/publish an Executable or a Feature by default and add the ``produceExecutableDuringBuild()``
  and ``produceFeatureDuringBuild()`` methods to build them if needed.
- Set group and version for all projects, including the root project, in order to generate correctly the release tag.
- Use version 2.1.0 of the microej-licenses library to check with the new SDK EULA 3.1-B.

Fixed
"""""

- Fix the override behavior of the Application main class that was not consistent when ``-Dapplication.main.class`` is
  used.
- Fix the Custom Ant Logger to display build errors without having to enable the verbose mode.
- Follow Gradle recommendation on resolvable and consumable configurations.
- Move the Custom Logger to a dedicated module and use its jar instead of fetching the plugin when
  executing VEE Port scripts to fix the tests failure during a release.
- Set Java Compiler encoding to UTF-8.
- Set Java Compliance level to 1.7 in JavaPluginExtension to fix the ``Cannot find the class file for java.lang.invoke.MethodHandles``
  error when opening a Gradle project in Eclipse.
- Fix wrong generated Virtual Device of an Application when the VEE Port changed.
- Bump source level for javadoc task to 1.8 to support JDK 21.
- Fix classpaths when using a Virtual Device to remove warnings about kf files not found.
- Make sure to close all opened streams.
- Fix ``Wrong java/lang/Object`` error when running an Application on the Simulator with a local repository.
- Fix ``No .kf file found for this feature classpath`` error message in logs when running VD with launcher script.

.. _changelog-0.13.0:

[0.13.0] - 2023-11-10
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add a check on EULA acceptation when using the MicroEJ Gradle plugin.
- Automatically publish the ASSEMBLY_EXCEPTION.txt file if it exists at the root of the project.
- Allow to publish the Feature file of an Application.
- Add ``:execTool`` task to execute Stack Trace Reader and Code Coverage Analyzer Tools provided by the selected VEE Port or Kernel.

Fixed
"""""

- Fix warning during compilation because of non-existing file or folder (``incorrect classpath: C:\\Users\\user\\...\myProject\\build\\resources\\main``).
- Fix warning in SOAR when building an Executable with Architecture 8.0.0 (``[M59] - Classpath file [C:\Users\user\...\myProject\build\resources\main] does not exist``).
- Enable Ant verbose mode for VEE Port scripts when Gradle debug log level is enabled.
- Fix the build of a Feature when the provided Virtual Device does not contain the ``dynamicFeatureLink.microejLaunch`` build script (Virtual Device built with SDK 5).

.. _changelog-0.12.1:

[0.12.1] - 2023-10-16
~~~~~~~~~~~~~~~~~~~~~

Fixed
"""""

- Fix the issue with the ``microejKernel`` configuration that prevented IDEs from loading a project.

.. _changelog-0.12.0:

[0.12.0] - 2023-10-13
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to publish the Virtual Device of an Application.
- Allow to fetch a Virtual Device and an Executable with the ``microejKernel`` configuration.

Changed
"""""""

- Add README, CHANGELOG and License files as publication artifacts in the generated ivy.xml file.
- Publish test report in Jenkins job.
- Set ``deploy.bsp.microejscript`` property to ``true`` by default to build the executable.
- Publish the Executable file as a variant.
- Rename the ``kernelFile`` property to ``kernelExecutableFile``.
- Use File dependency instead of the ``veePortPath`` property to load a local VEE Port.
- Use File dependency instead of the ``kernelExecutableFile`` property to load a local Kernel Executable.

Fixed
"""""

- Fix unexpected fetch of the transitive dependencies of a VEE Port dependency (``microejVeePort`` configuration).
- Fix System properties defined in ``gradle.properties`` are ignored.
- Fix VEE Port launcher: temporary configuration file could prevent to launch a second time.
- Remove usage of deprecated API Project.getBuildDir().
- Fix the message when no executable are found by the ``runOnDevice`` task.
- Fix Executable not updated after a project change and a call to the ``buildExecutable`` task.
- Fix wrong order of tests classes and resources folder in the test classpath.
- Call VEE Port Ant script from a separate temporary directory to satisfy MicroEJ Architecture. This fixes spurious HIL timeouts when calling the ``runOnSimulator`` task.
- Fix Java process still running when Simulator is interrupted.
- Fix missing Nashorn dependencies when running a testsuite and when launching the launcher scripts to make it work with JDK 17 and higher.

.. _changelog-0.11.1:

[0.11.1] - 2023-09-22
~~~~~~~~~~~~~~~~~~~~~

Fixed
"""""

- Fix usage of a SNAPSHOT version of the junit-test-engine dependency.

.. _changelog-0.11.0:

[0.11.0] - 2023-09-22
~~~~~~~~~~~~~~~~~~~~~

Changed
"""""""

- Use Gradle standard mechanism to support Multi-VEEPort instead of relying on an in-house feature.

.. _changelog-0.10.0:

[0.10.0] - 2023-09-13
~~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add a task ``runOnDevice`` to run the Executable on a Device.
- Support all JDK LTS versions higher or equals to version 11.

Fixed
"""""

- Allow to build a Feature file of an Application with a Virtual Device.
- Fix javadoc failure when the project contains a JDK class.

.. _changelog-0.9.0:

[0.9.0] - 2023-09-01
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to depend on local Application project (dependency with ``microejApplication`` configuration).
- Implement properties loading chain.
- Add launcher scripts to the Virtual Device.

Changed
"""""""

- Move the ``vd-init.xml`` script in the template file instead of hardcoding it in the class.
- Remove the Application properties from ``options/application.properties`` file and rename file to ``target.properties`` in Virtual Device.
- Merge ``veePortFiles`` and ``veePortDirs`` properties into the ``veePortPaths`` property.
- Add missing Javadoc and clean the project.

Fixed
"""""

- Fix resources generated by Addon Processors of type FolderKind.MainResources not processed.
- Fix root path used for relative VEE port path: use the project root directory.
- Fix the content of a WPK to remove the Foundation Libraries.
- Make sure `.a` and `.o` files of an Application are correct by always executing the `buildExecutable` task.

.. _changelog-0.8.0:

[0.8.0] - 2023-07-13
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to build the Virtual Device of an Application.
- Add checks to ensure that a Virtual Device can be used or not depending on the called task.
- Allow to build the Feature binary file of an Application.

Fixed
"""""

- Add the Application properties defined in the ``configuration folder`` to the WPK file.

.. _changelog-0.7.0:

[0.7.0] - 2023-06-26
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add Standard Java Library plugin (``com.microej.gradle.j2se-library``).
- Rename ``com.microej.gradle.library`` plugin to ``com.microej.gradle.addon-library``.


Changed
"""""""

- Unbind the checkModule task from the build task.
- Use version ``0.1.1`` of the MicroEJ JUnit Test Engine to fix error when test classes are not in a package.
- Use version ``2.0.0`` of the microej-licenses library to check with the new authorized licenses.

.. _changelog-0.6.0:

[0.6.0] - 2023-05-30
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Allow to publish WPK file artifact.
- Allow to publish files generated by the ``buildExecutable`` task.
- Allow to define multiple testsuites in different environments (sim or J2SE).
- Allow to define a testsuite for tests on device.


Changed
"""""""

- Use Ivy descriptor content to know if a dependency is a Foundation Library or an Addon Processor Library.
- Optimize the ``loadVeePort`` task to reduce the time to load a VEE Port.
- Use a smaller VEE Port as dependency in tests to reduce the time to build.
- Remove ``JPF`` support.
- Check that the given file/directory is a VEE Port.
- Move Application properties to ``configuration`` folder instead of ``src/main/resources``.
- Clean the Jenkins workspace after a successful build.
- Improve the checker on changelog files to support "-SNAPSHOT" suffix and "Unreleased" label.
- Remove the ``debugOnSimulator`` task and use a property to run an Application in debug mode.

Fixed
"""""

- Fix multiple VEE Ports error message in ``loadConfiguration`` task.
- Fix connection to a debugger and debug.port property.
- Fix StackOverflow error when building a project with cyclic dependencies.

.. _changelog-0.5.0:

[0.5.0] - 2023-03-24
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add Xlint checking.
- Add verification of using java 11 by user's project.
- Allow to build the Executable file of an Application.
- Allow to build the WPK file of an Application.
- Allow to define multiple VEE Ports.
- Check that the project uses at least Gradle 8.0.
- Add more tests on topological order in the Application classpath.

Changed
"""""""

- Make the plugin compatible with Gradle ``8.0``.

.. _changelog-0.4.0:

[0.4.0] - 2023-01-27
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Apply the Java Library Plugin to user's project.
- Allow to load a VEE Port by dropping it in the ``dropIns`` folder.

Changed
"""""""

- Optimise memory used by project.
- Remove the ``runArtifactChecker`` property, the Artifact Checker task must be executed explicitly.
- Hide compilation warnings in the adp and compileJava tasks.

Fixed
"""""

- Disable the warning on non-compatible version for Maven client.
- Fix loading new dependency when the ``build.gradle.kts`` file is updated.
- Fix too long classpath error when running the simulator on Windows.

.. _changelog-0.3.0:

[0.3.0] - 2022-12-09
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add feature to avoid loading the VEE Port when there is no test.
- Add the auto assembling project for ``runOnSimulator`` and ``debugOnSimulator`` tasks.
- Add the opportunity disable custom conflict resolution rules.
- Add the plugin ``com.microej.gradle.library`` to build an Addon Library.
- Generate and publish the Java sources jar.
- Generate and publish the Javadoc jar.
- Publish ``README.md``, ``CHANGELOG.md`` and ``LICENSE.txt`` files if they exist in the project.
- Suffix version with timestamp when it ends with "-RC".
- Make the build fail if a direct dependency is resolved with a higher minor version than the one declared.
- Add the ``checkModule`` task to check compliance of the module with MicroEJ rules.
- Add the execution of tests on the simulator.
- Add support for Mac M1.
- Build the plugin in Java 11.
- Add test to ensure that the dependencies are topologically sorted.

Changed
"""""""

- Remove automatic version conversion.
- Rename the Application plugin to ``com.microej.gradle.application``.
- Change the publication plugin to publish Maven modules instead of Ivy modules.
- Use Ant Java API to launch the simulator to avoid requiring an Ant installation.
- Rename the ``runOnSim`` and ``debugOnSim`` tasks to ``runOnSimulator`` and ``debugOnSimulator``.
- Use JDT compiler instead of javac.
- Isolate functional tests to keep a quick build.

Fixed
"""""

- VEE Port not reloaded when referenced by ``veePortDirPath`` and the VEE Port source folder is updated.
- Set Java source and target version to be recognized by IDEs.
- Make ``processResources`` task implicitly depend on ADP task to fix failures during ``runOnSimulator``.

.. _changelog-0.2.0:

[0.2.0] - 2022-05-17
~~~~~~~~~~~~~~~~~~~~

Changed
"""""""

- Make the build fails when an ADP raises errors.
- Convert build scripts from ``Groovy`` to ``Kotlin``.

.. _changelog-0.1.0:

[0.1.0] - 2022-05-03
~~~~~~~~~~~~~~~~~~~~

Added
"""""

- Add the capability to load the platform from dependencies.
- Add the task ``debugOnSim`` to execute the application in debug mode in the simulator.
- Publish the sources jar of the plugin.

Fixed
"""""

- Extract ADP classpath JAR files into OS temp dir to avoid error on cleaning because of locks.



..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
