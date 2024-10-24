.. _sdk_6_migrate_mmm_project:

Migrate an MMM Project
======================

This page explains how to migrate a project created with the SDK 5 or lower to the SDK 6.
It covers the following items:

- Project structure
- Build descriptor file
- Build scripts

.. _sdk_6_migrate_project_structure:

Project structure
-----------------

The structure of an SDK 6 Gradle project is similar to an MMM project.
The differences are:

- The ``module.ivy`` file is replaced by a ``build.gradle.kts`` file and a ``settings.gradle.kts`` file (see :ref:`sdk_6_migrate_build_file`).
- The ``module.ant`` and ``override.module.ant`` files are removed (see :ref:`sdk_6_migrate_build_scripts`).
- The ``build`` folder located at the root of the project and containing the Application configuration properties is replaced by the ``configuration`` folder.
  This change is required since Gradle uses the ``build`` folder to store the generated files and artifacts (equivalent of the MMM ``target~`` folder).

Therefore, here are the 2 project structures side by side: 

+--------------------------------+--------------------------------+
| MMM Project                    | Gradle Project                 |
+================================+================================+
| .. code-block::                | .. code-block::                |
|                                |                                |
|    |- src                      |    |- src                      |
|    |   |- main                 |    |   |- main                 |
|    |   |   |- java             |    |   |   |- java             |
|    |   |   |- resources        |    |   |   |- resources        |
|    |   |- test                 |    |   |- test                 |
|    |       |- java             |    |       |- java             |
|    |       |- resources        |    |       |- resources        |
|    |- build                    |    |- configuration            |
|    |   |- common.properties    |    |   |- common.properties    |
|    |- module.ivy               |    |- build.gradle.kts         |
|    |- module.ant               |    |- settings.gradle.kts      |
|                                |                                |
+--------------------------------+--------------------------------+

.. _sdk_6_migrate_build_file:

Build Descriptor File
---------------------

The ``module.ivy`` file of the MMM project must be replaced by a ``build.gradle.kts`` file and a ``settings.gradle.kts`` file.
The ``settings.gradle.kts`` contains the name of the project, 
whereas the ``build.gradle.kts`` file contains all the other information (module type, group, version, ...).

Build Type
~~~~~~~~~~

The MMM build type defined in the ``module.ivy`` file with the ``ea:build`` tag is replaced by a plugin in the ``build.gradle.kts`` file.
For example, here is the block to add at the beginning of the file to migrate a ``build-microej-javalib`` MMM module::

   plugins {
       id("com.microej.gradle.addon-library") version "0.20.0"
   }

The mapping between MMM build types and Gradle plugins is:

.. list-table::
   :widths: 50 50

   * - **MMM Build Type**
     - **Gradle Plugin**
   * - ``build-microej-javalib``
     - ``com.microej.gradle.addon-library``
   * - ``build-application``
     - ``com.microej.gradle.application``
   * - ``build-firmware-singleapp``
     - ``com.microej.gradle.application``
   * - ``build-firmware-multiapp``
     - ``com.microej.gradle.application``
   * - ``build-std-javalib``
     - ``com.microej.gradle.jse-library``
   * - ``build-microej-mock``
     - ``com.microej.gradle.mock``
   * - ``build-runtime-api``
     - ``com.microej.gradle.runtime-environment``

Module Information
~~~~~~~~~~~~~~~~~~

The module information defined by the ``info`` tag in the ``module.ivy`` file are split in the 2 following descriptor files:

- ``settings.gradle.kts``

   - The property ``rootProject.name`` replaces the ``module`` attribute.

- ``build.gradle.kts``

   - The property ``group`` replaces the ``organisation`` attribute.
   - The property ``version`` replaces the ``revision`` attribute.

So for example, the following ``info`` tag::

   <info organisation="com.mycompany" module="myProject" status="integration" revision="0.1.0">

will be converted to:

.. code-block:: java
   :caption: settings.gradle.kts

   rootProject.name = "myProject"

.. code-block:: java
   :caption: build.gradle.kts

   group = "com.mycompany"
   version = "0.1.0"

.. note::

   Refer to :ref:`sdk6_manage_versioning` section for more information on the way to define the module version.

Configuration
~~~~~~~~~~~~~

The configuration of an MMM build is only done with ``ea:property`` tags in the ``module.ivy`` file, 
whereas it can take multiple form in Gradle. 
You can refer to the :ref:`sdk6_module_natures` page for a complete list of configurations.

As a first example, the main class is defined in MMM with the property ``application.main.class``::

   <ea:property name="application.main.class" value="com.mycompany.Main"/>

whereas it is defined by the ``applicationEntryPoint`` property of the ``microej`` block in Gradle::

   microej {
      applicationEntryPoint = "com.mycompany.Main"
   }

As a second example, the pattern of the executed tests is defined in MMM with the property ``test.run.includes.pattern``::

   <ea:property name="test.run.includes.pattern" value="**/_AllTests_MyTest.class"/>

whereas it is defined by the ``filter`` object of the ``test`` task in Gradle::

   testing {
      suites {
        val test by getting(JvmTestSuite::class) {

            ...

            targets {
                all {
                    testTask.configure {
                        filter {
                            includeTestsMatching("MyTest")
                        }
                    }
                }
            }
        }
      }
   }

Dependencies
~~~~~~~~~~~~

The ``dependencies`` tag in the ``module.ivy`` file is replaced by the ``dependencies`` block in the ``build.gradle.kts`` file.
Each dependency is tight to a Gradle configuration.
For example, migrating a dependency used at compile time and runtime should use the ``implementation`` configuration, 
so the following dependency::

   <dependency org="ej.api" name="edc" rev="1.3.5" />

will be converted to::

   implementation("ej.api:edc:1.3.5")

wheras a dependency used for the tests only should use the ``testIplementation`` configuration, 
so the following dependency::

   <dependency conf="test->*" org="ej.library.test" name="junit" rev="1.7.1"/>

will be converted to::

   testImplementation("ej.library.test:junit:1.7.1")

Also note that this will not resolve snapshot builds since versions are explicit in SDK 6, see :ref:`this chapter <sdk_6_add_dependency_version>` for more details.
To resolve both snapshot and release versions, use ``[1.0.0-RC,1.0.0]`` instead of ``1.0.0``.

.. note::
   If the dependency relates to another module of the same project, you may use a multi-project structure instead (see
   `Multi-Project Build Basics <https://docs.gradle.org/current/userguide/intro_multi_project_builds.html>`__).

Refer to the :ref:`sdk_6_add_dependency` page to go further on the Gradle dependencies and configurations.

Example
~~~~~~~

This section gives an example of migration from a ``module.ivy`` file to a ``build.gradle.kts`` file and a ``settings.gradle.kts`` file.

**SDK 5 and lower**

.. code-block:: xml
   :caption: module.ivy

   <ivy-module version="2.0" xmlns:ea="http://www.easyant.org" xmlns:m="http://ant.apache.org/ivy/extra" xmlns:ej="https://developer.microej.com" ej:version="2.0.0">
      <info organisation="com.mycompany" module="myProject" status="integration" revision="0.1.0">
         <ea:build organisation="com.is2t.easyant.buildtypes" module="build-application" revision="9.2.+">
            <ea:property name="test.run.includes.pattern" value="**/_AllTests_*.class"/>
         </ea:build>
      </info>
      
      <configurations defaultconfmapping="default->default;provided->provided">
         <conf name="default" visibility="public" description="Runtime dependencies to other artifacts"/>
         <conf name="provided" visibility="public" description="Compile-time dependencies to APIs provided by the platform"/>
         <conf name="platform" visibility="private" description="Build-time dependency, specify the platform to use"/>
         <conf name="documentation" visibility="public" description="Documentation related to the artifact (javadoc, PDF)"/>
         <conf name="source" visibility="public" description="Source code"/>
         <conf name="dist" visibility="public" description="Contains extra files like README.md, licenses"/>
         <conf name="test" visibility="private" description="Dependencies for test execution. It is not required for normal use of the application, and is only available for the test compilation and execution phases."/>
         <conf name="microej.launch.standalone" visibility="private" description="Dependencies for standalone application. It is not required for normal use of the application, and is only available when launching the main entry point on a standalone MicroEJ launch."/>
      </configurations>
      
      <publications>
         <!-- keep this empty if no specific artifact to publish -->
         <!-- must be here in order to avoid all configurations for the default artifact -->
      </publications>
      
      <dependencies>
         <!--
            Put your custom Runtime Environment dependency here. For example:
            
            <dependency org="com.company" name="my-runtime-api" rev="1.0.0" conf="provided->runtimeapi" />
         -->
         <!--
            Or put direct dependencies to MicroEJ libraries if your Application is not intended to run on a specific custom Runtime Environment.
         -->
         <dependency org="ej.api" name="edc" rev="1.3.5" />
         <dependency org="ej.api" name="kf" rev="1.6.1" />
         
         <dependency conf="test->*" org="ej.library.test" name="junit" rev="1.7.1"/>

         <dependency org="com.microej.platform.esp32.esp-wrover-kit-v41" name="HDAHT" rev="1.8.0" conf="platform->default" transitive="false"/>
      </dependencies>
   </ivy-module>

**SDK 6**

.. code-block:: java
   :caption: settings.gradle.kts

   rootProject.name = "myProject"

.. code-block:: java
   :caption: build.gradle.kts

   plugins {
       id("com.microej.gradle.application") version "0.20.0"
   }

   group = "com.mycompany"
   version = "0.1.0"

   dependencies {
      implementation("ej.api:edc:1.3.3")
      implementation("ej.api:kf:1.6.1")

      testImplementation("ej.library.test:junit:1.7.1")

      microejVee("com.microej.platform.esp32.esp-wrover-kit-v41:HDAHT:1.8.2")
   }

.. _sdk_6_migrate_build_scripts:

Build Scripts
-------------

MMM supports the use of the ``module.ant`` and ``override.module.ant`` to customize the build process.
These files are not supported anymore with Gradle.
Instead, since Gradle build files are code, customizations can be applied directly in the build files.

As an example, defining a property conditionnaly is done as follows in a ``module.ant`` file:

.. code-block:: xml

   <target name="my-project:define-properties" extensionOf="compile">
      <condition property="myProperty" value="myValue">
         <not><equals arg1="${anotherProperty}" arg2="anotherValue"/></not>
      </condition>	
   </target>

and as follows in a ``build.gradle.kts`` file:

.. code-block:: java

   var myProperty = ""
   tasks.register("defineProperties") {
      if(project.properties["anotherProperty"] == "anotherValue") {
         myProperty = "myValue"
      }
   }

   tasks.compileJava {
      dependsOn("defineProperties")
   }

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
