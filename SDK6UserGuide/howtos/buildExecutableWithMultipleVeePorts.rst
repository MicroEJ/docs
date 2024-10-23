.. _sdk_6_howto_build_executable_with_multiple_vee_ports:

How To Build an Executable With Multiple VEE Ports
==================================================

When creating an Application, only one VEE Port must be defined to build an Executable.
However, it is possible to build an Executable for a list of VEE Ports 
by using a Gradle `multi-project <https://docs.gradle.org/current/userguide/multi_project_builds.html>`__.

For example, if you want to build an Executable for two VEE Ports, you can create a multi-project composed of two subprojects:

.. code-block::

   |- rootProject
   |   |- myApplicationVeePort1
   |   |   |- src/main/java
   |   |   |- src/main/resources
   |   |   |- build.gradle.kts
   |   |- myApplicationVeePort2
   |   |   |- build.gradle.kts
   |   |- settings.gradle.kts
   |   |- build.gradle.kts

- The ``myApplicationVeePort1`` subproject is the Application project in which the first VEE Port is defined and the ``applicationEntryPoint``
  property is set to the Fully Qualified Name of your main class.
- The ``myApplicationVeePort2`` subproject is an Application project that only contains a ``build.gradle.kts`` file in which the second VEE Port is defined and
  the ``applicationEntryPoint`` property is set to the Fully Qualified Name of your main class. To avoid having to duplicate the Source code of the Application,
  a `SourceSet <https://docs.gradle.org/current/dsl/org.gradle.api.tasks.SourceSet.html>`__ must be defined to use the Source code of 
  the ``myApplicationVeePort1`` subproject::

	sourceSets {
		main {
			java {
				srcDirs(project(":myApplicationVeePort1").layout.projectDirectory.dir("src/main/java"),
				    project(":myApplicationVeePort1").layout.projectDirectory.dir("src/main/resources"))
			}
		}
	}

- In the ``build.gradle.kts`` file of the multi-project, you can define the Gradle configuration that is common to all subprojects to avoid duplicates,
  for example::
    
    plugins {
        id("com.microej.gradle.application") version "0.20.0" apply false
    }
    
    subprojects {
        apply(plugin = "com.microej.gradle.application")
        
        val implementation by configurations
        
        dependencies {
            implementation("ej.api:edc:1.3.5")
        }
    }

- For each VEE Port, the Application configuration properties can be defined in the ``configuration`` folder of the corresponding Application project.

The Executable of the Application can now be built for a VEE Port by executing the ``buildExecutable`` task on the corresponding subproject::

    ./gradlew myApplicationVeePort1:buildExecutable

To build the Executable for all VEE Ports, a new task can be created in the ``build.gradle.kts`` file 
of the multi-project::

    tasks.create("buildAllExecutables")
    subprojects {
        rootProject.tasks.getByName("buildAllExecutables").dependsOn("$path:buildExecutable")
    }

All Executables can now be built by executing the ``buildAllExecutables`` task::
    
    ./gradlew buildAllExecutables

For each VEE Port, the Executable is generated in the ``build/output/application`` folder of the corresponding subproject.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
