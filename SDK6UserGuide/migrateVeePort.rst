.. _sdk_6_migrate_veeport:

Migrate a VEE Port Project
==========================

This page explains how to migrate an VEE Port project created with the SDK 5 or lower to the SDK 6.

Project structure
-----------------

Even if it is not mandatory, a VEE Port project is most of the time structured as a multi-project.
Indeed, it generally contains other subprojects than the configuration module, for example a Front Panel or an Image Generator subproject.
It can also contains the BSP.

Whereas it was not necessarily structured as a meta-build in SDK 5, it is recommended to structure it as a multi-project in SDK 6.

This brings to the following recommended structure for the VEE Port multi-project::

   |- my-board-vee-port/
   |    |- bsp/
   |    |- demo-application/ (optional)
   |    |    |- src/main/java/
   |    |- vee-port/
   |    |    |- extensions/
   |    |    |    |- my-front-panel/ (optional)
   |    |    |    |- my-image-generator/ (optional)
   |    |    |    |- microui/ (optional)
   |    |    |    |- ...
   |    |    |- validation/
   |    |    |    |- core/ (optional)
   |    |    |    |- fs/ (optional)
   |    |    |    |- ...
   |    |    |- dropins/ (optional)
   |    |    |- configuration.properties
   |    |    |- build.gradle.kts
   |- settings.gradle.kts

This migration guide will go in details in each changes, but as a quick overview, 
here are the main changes compared to SDK 5:

- All root modules have been moved under a ``vee-port`` folder, except for the BSP folder.
- The configuration module (``*-configuration``) is now the ``vee-port`` module, which includes configuration properties, 
  ``dropins`` folder, as well as the other modules required by the VEE Port.
- All configuration properties file have been gathered in the ``vee-port/configuration.properties`` (except for ``microui``).
- The specific components required by the VEE Port are now in the ``vee-port/extensions`` folder, 
  such as Front Panel or Image Generator modules.
- The MicroUI extension has been moved in the ``vee-port/extensions/microui`` folder.

Settings build file
-------------------

A multi-project requires a ``settings.gradle.kts`` file located in the root folder.
Its main purposes are to optionaly define a name for the multi-project and to define its subprojects.
Create this file and add this line with the name of your choice::

   rootProject.name = "my-board-vee-port"

Configuration Subproject
------------------------

The Configuration (``*-configuration``) subproject is still there, but it is recommended to name it ``vee-port``.
Follow these steps to migrate it:

- Rename the folder to ``vee-port``.
- Replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- Use the ``com.microej.gradle.veeport`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.veeport") version "0.19.0"
   }

- Still in the ``build.gradle.kts`` file, define the ``group`` and ``version`` property, 
  which respectively replace the ``organisation`` and ``revision`` of the ``module.ivy`` file. For example::

   group = "com.mycompany"
   version = "0.1.0"

.. note::

   Refer to :ref:`sdk6_manage_versioning` section for more information on the way to define the module version.

- Define the dependencies previously defined in the ``module.ivy`` file. 
  In SDK 6, dependencies are defined in a ``dependencies`` block in the ``build.gradle.kts`` file,
  and each type of VEE Port component must be defined with a dedicated configuration:
  
  - Architecture: ``microejArchitecture``
  - Pack: ``microejPack``
  - Mock: ``microejMock``
  - Front Panel: ``microejFrontPanel``
  - Tool: ``microejTool``

  For example the Architecture defined like this in SDK 5::

   <dependencies>
      <dependency group="com.microej.architecture.CM7.CM7hardfp_GCC48" name ="flopi7G26" rev="8.1.1">
         <artifact name="flopi7G26" m:classifier="eval" ext="xpf" />
      </dependency>
   </dependencies>

  must be changed to this in ``build.gradle.kts`` file::

   dependencies {
      microejArchitecture("com.microej.architecture.CM7.CM7hardfp_GCC48:flopi7G26:8.1.1")
   }

  .. note::

   Note that the Architecture usage (``eval`` or ``prod``) is not defined in the VEE Port configuration anymore.
   It is now set by the project which consumes the VEE Port (for example an Application).

  And the Pack defined like this in SDK 5::

   <dependency group="com.microej.pack" name ="fs" rev="6.0.4" />

  must be changed to this in SDK 6::

   microejPack("com.microej.pack:fs:6.0.4")

- Create a ``configuration.properties`` file at the root of the ``vee-port`` folder.

- Move the property related to the Runtime Capability from the file ``mjvm/mjvm.properties`` to the ``vee-port/configuration.properties`` file,
  then delete the ``mjvm/mjvm.properties`` file.

- Move all configuration properties related to the BSP (``bsp/bsp.properties``) into the ``vee-port/configuration.properties`` file.
  Each property name must be prefixed by ``bsp.<name>.``.
  For example, the ``microejapp.relative.dir`` property must be moved as ``bsp.microejapp.relative.dir`` in the ``vee-port/configuration.properties`` file.

- Move the ``microui`` folder (if it exists) into the ``vee-port/extensions`` folder.

- Move the configuration properties related to all the other Packs (``fs/fs.properties``, ...) into the ``vee-portconfiguration.properties`` file.
  Each property name must be prefixed by ``com.microej.pack.<name>.``, where ``<module>`` is the name of the Pack.
  For example, the ``bpp`` property defined in the ``display/display.properties`` file must be moved as ``com.microej.pack.display.bpp`` in the ``vee-portconfiguration.properties`` file.
  
- Delete old configuration properties files ((``bsp/bsp.properties``, ``display/display.properties``, ``fs/fs.properties``, ...) can be deleted.

- Enable disable Pack modules if required, as described in :ref:`sdk_6_veeport_pack_enable_modules`.

- Delete the ``.platform`` file located at the root of the Configuration subproject, since it is now obsolete.

- The ``dropins`` folder was used as a destination folder for some generated files in SDK 5, so it may contain more than the committed files.
  So make sure to clean it to keep only committed files. This can be done with git with the following command in the ``dropins`` folder::

   git clean -xdf

Front Panel Project
-------------------

The Front Panel is generally a subproject of the VEE Port multi-project.
These steps must be followed to migrate a Front Panel subproject:

- Move the Front Panel folder into the ``vee-port/extensions`` folder.
- Replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- Use the ``com.microej.gradle.mock-frontpanel`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.mock-frontpanel") version "0.19.0"
   }

- Define the dependencies previously defined in the ``module.ivy`` file. 
  A Front Panel generally depends on libraries, so they can be defined with the ``implementation`` configuration.
  For example to declare a dependency on the Front Panel framework library, use::

   implementation("ej.tool.frontpanel:framework:1.1.0")

  Also note that the Front Panel library from the UI Pack must be declared with the ``name`` and ``extension``::

   implementation("com.microej.pack.ui:ui-pack:14.0.1") {
        artifact {
            name = "frontpanel"
            extension = "jar"
        }
    }

- Include the Front Panel subproject in the multi-project in the ``settings.gradle.kts`` file::
  
   include("vee-port:front-panel")
   project(":vee-port:front-panel").projectDir = file("vee-port/extensions/front-panel")

- Make the VEE Port configuration subproject depend on the Front Panel subproject by adding a project dependency in the ``vee-port/build.gradle.kts`` file::

   microejFrontPanel(project(":vee-port:front-panel"))

Mock
----

If the VEE Port project contains Mock subprojects, they must be migrated by following these steps:

- Move the Mock folder into the ``vee-port/extensions`` folder.
- Replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- Use the ``com.microej.gradle.mock`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.mock") version "0.19.0"
   }

- Define the dependencies previously defined in the ``module.ivy`` file. 
  A Mock generally depends on libraries, so they can be defined with the ``implementation`` configuration.

- Include the Mock subproject in the multi-project in the ``settings.gradle.kts`` file::
  
   include("vee-port:mock")
   project(":vee-port:mock").projectDir = file("vee-port/extensions/mock")

- Make the VEE Port configuration subproject depend on the Mock subproject by adding a project dependency in the ``vee-port/build.gradle.kts`` file::

   microejTool(project(":vee-port:mock"))

Tool subproject
---------------

If the VEE Port project contains Tool subprojects (such as an Image Generator), they must be migrated by following these steps:

- Move the Tool folder into the ``vee-port/extensions`` folder.
- Replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- Use the ``com.microej.gradle.j2se-library`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.j2se-library") version "0.19.0"
   }

- Define the dependencies previously defined in the ``module.ivy`` file. 
  A Tool generally depends on libraries, so they can be defined with the ``implementation`` configuration.
  Note that when the Tool is an Image Generator and depends on the Image Generator library from the UI Pack, the dependency must be declared with the ``name`` and ``extension``::

   implementation("com.microej.pack.ui:ui-pack:14.0.1") {
        artifact {
            name = "imageGenerator"
            extension = "jar"
        }
    }

- Include the Tool subproject in the multi-project in the ``settings.gradle.kts`` file::
  
   include("vee-port:image-generator")
   project(":vee-port:image-generator").projectDir = file("vee-port/extensions/image-generator")

- Make the VEE Port subproject depend on the Tool subproject by adding a project dependency in the ``vee-port/build.gradle.kts`` file::

   microejTool(project(":vee-port:image-generator"))

Testsuites Project
------------------

These steps must be followed to migrate the Testsuites:

- Move the Testsuite folder into the ``vee-port/validation`` folder.

Then for each Testsuite:

- Replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- Use the ``com.microej.gradle.testsuite`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.testsuite") version "0.19.0"
   }

- The tested VEE Port was defined in SDK 5 in the ``config.properties`` file, with the ``target.platform.dir`` property.
  In SDK6, it is done by declaring the VEE Port Configuration project as a project dependency::

   dependencies {
      microejVee(project(":vee-port"))
   }

  and including the testsuite project in the ``settings.gradle.kts`` file of the multi-project::

   include("java-testsuite-runner-security")
   project(":java-testsuite-runner-security").projectDir = file("validation/security/java-testsuite-runner-security")

  The second line is required when the testsuite subproject is not directly in a subfolder of the multi-project.
  The path set as the value is relative to the root folder of the multi-project.

  Once done, you can delete the ``target.platform.dir`` property in the ``config.properties`` file.

- define the testsuite in the ``build.gradle.kts`` file::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this, TestTarget.EMB, TestMode.MAIN)

            dependencies {
               implementation(project()) // (1)
               implementation("ej.library.test:junit:1.7.1") // (2)
               implementation("org.junit.platform:junit-platform-launcher:1.8.2") // (3)

               implementation("ej.api:security:1.4.0") // (4)
               implementation("com.microej.pack.security:security-1_4-testsuite:1.3.0") // (4)
            }
         }
      }
   }

  The testsuite dependencies must contain:

  - the project *(1)*
  - the JUnit libraries *(2)*
  - the Foundation Library to test *(3)*
  - the Testsuite related to the Foundation Library *(4)*

- The patterns of the included and excluded test classes was defined with the ``test.run.includes.pattern`` 
  and ``test.run.excludes.pattern`` properties in the ``config.properties`` file.
  There must be now defined directly in the testsuite configuration in the ``build.gradle.kts`` file, 
  by using the standard Gradle filter feature::

   testing {
      suites {
         val test by getting(JvmTestSuite::class) {
            microej.useMicroejTestEngine(this, TestTarget.EMB, TestMode.MAIN)

            dependencies {
               ...
            }

            targets {
                all {
                    testTask.configure {
                        filter {
                            excludeTestsMatching("*AllTestClasses")
                            excludeTestsMatching("*SingleTest*")
                            excludeTestsMatching("*AllTests_MessageDigestTest")
                            excludeTestsMatching("*AllTests_KeyPairGeneratorTest")
                        }
                    }
                }
            }
         }
      }
   }

  Refer to the `Gradle documentation on 
  test filtering <https://docs.gradle.org/current/userguide/java_testing.html#test_filtering>`_ for more details.

  Once done, you can delete the ``test.run.includes.pattern`` and ``test.run.excludes.pattern`` properties 
  in the ``config.properties`` file.

BSP
---

It is recommended to keep the BSP folder at the root of the multi-project.
The paths to the BSP can be updated in the VEE Port configuration (``vee-port/configuration.properties``) if necessary.
Refer to the :ref:`bsp_connection` documentation for more details.

Wrap up
-------

At the end of the migration, you should have a structure similar to the one presented at the beginning of this page.
The ``settings.gradle.kts`` should look like::

   // Define the VEE Port mulit-project name
   rootProject.name = "my-board-vee-port"

   // Include the subprojects
   include("vee-port", "vee-port:front-panel", "vee-port:mock", "vee-port:image-generator", "demo-application")
   include("vee-port:validation:java-testsuite-runner-core")
   include("vee-port:validation:java-testsuite-runner-fs")

   // Define the paths of the subprojects
   project(":vee-port:front-panel").projectDir = file("vee-port/extensions/front-panel")
   project(":vee-port:image-generator").projectDir = file("vee-port/extensions/image-generator")
   project(":vee-port:validation:java-testsuite-runner-core").projectDir = file("vee-port/validation/core/java-testsuite-runner-core")
   project(":vee-port:validation:java-testsuite-runner-fs").projectDir = file("vee-port/validation/fs/java-testsuite-runner-fs")

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
