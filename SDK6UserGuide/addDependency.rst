.. _sdk_6_add_dependency:

Add a Dependency
================

A project generally relies on other components such as libraries.
These components have to be declared as dependencies of the build to be used by the project.
This declaration is done in the ``dependencies`` block of the ``build.gradle.kts`` file.
For example, to add the EDC library as a dependency::

   dependencies {
      implementation("ej.api:edc:1.3.5")
   }

Every dependency declared for a Gradle project applies to a specific scope.
For example some dependencies should be used for compiling source code whereas others only need to be available at runtime. 
Gradle represents the scope of a dependency with the help of a configuration. 
In the above example, the ``implementation`` configuration is used.

Since the MicroEJ Gradle plugins extend the Gradle Java and Java Library plugins, they inherits from their configurations,
but they also adds their own configurations.
Let's have a look at the mostly used configurations:

- **implementation** (from Gradle Java plugin) - Dependencies used by the project at compile time and runtime.
- **api**  (from Gradle Java Library plugin) - Same as the **implementation** configuration, except that the dependency is also exposed to the consumers of your project.
- **testImplementation** (from Gradle Java plugin) - Dependencies used by the test classes of the project.
  This configures extends the **implementation** configuration, so it inherits from all the dependencies declared with the **implementation** configuration.
- **microejPlatform** - Platform used by the project for build and test.

Here is an example of dependencies declaration for a project::

   dependencies {
      implementation("ej.library.runtime:basictool:1.7.0")

      testImplementation("ej.library.test:junit:1.7.1")

      microejPlatform("com.microej.platform.esp32.esp-wrover-kit-v41:HDAHT:1.8.0")
   }

For an exhaustive list of the available configurations and more details on how to manage dependencies, 
please refer to the following official documentations:

- `Declaring dependencies <https://docs.gradle.org/current/userguide/declaring_dependencies.html>`__
- `Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html#sec:java_plugin_and_dependency_management>`__
- `Java Library plugin <https://docs.gradle.org/current/userguide/java_library_plugin.html#sec:java_library_separation>`__

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
