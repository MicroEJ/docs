.. _sdk_6_migrate_veeport:

Migrate a VEE Port Project
==========================

This page explains how to migrate an VEE Port project created with the SDK 5 or lower to the SDK 6.
It focuses on the elements specific to a VEE Port project, 
so make sure to first follow :ref:`the documentation explaining the migration of the elements common to any project <sdk_6_migrate_sdk5_project>`.

Project structure
-----------------

Even if it is not mandatory, a VEE Port project is most of the time structured as a multi-project.
Indeed, it generally contains other subprojects than the configuration module, for example a Front Panel or an Image Generator subproject.
Whereas it was not necessarily structured as a meta-build in SDK 5, it is recommended to structure it as a multi-project in SDK 6.

A multi-project requires a ``settings.gradle.kts`` file located in the root folder.
This brings to the following structure for the first level elements of the VEE Port multi-project::

   |- my-vee-port/
   |    |- my-vee-port-configuration/
   |    |- my-front-panel/ (optional)
   |    |- my-image-generator/ (optional)
   |    |- settings.gradle.kts

The ``settings.gradle.kts`` file can define a name for the VEE Port project (defaults to the root folder name) and must include all the subprojects::

   rootProject.name = "my-vee-port"

   include("my-vee-port-configuration")
   include("my-front-panel")
   include("my-image-generator")


Configuration Subproject
------------------------

These steps must be followed to migrate a Configuration subproject:

- replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- use the ``com.microej.gradle.veeport`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.veeport") version "0.17.0"
   }

- define the dependencies previously defined in the ``module.ivy`` file. 
  In SDK 6, each type of VEE Port component must be defined with a dedicated configuration:
  
  - Architecture: ``microejArchitecture``
  - Pack: ``microejPack``
  - Mock: ``microejMock``
  - Front Panel: ``microejFrontPanel``
  - Tool: ``microejTool``

  For example the Architecture defined like this in SDK 5::

   <dependency group="com.microej.architecture.CM7.CM7hardfp_GCC48" name ="flopi7G26" rev="8.1.1">
      <artifact name="flopi7G26" m:classifier="eval" ext="xpf" />
   </dependency>

  must be changed to this in SDK 6::

   microejArchitecture("com.microej.architecture.CM7.CM7hardfp_GCC48:flopi7G26:8.1.1")

  .. note::

   Note that the Architecture usage (``eval`` or ``prod``) is not defined in the VEE Port configuration anymore.
   It is now set by the project which consumes the VEE Port (for example an Application).

  And the Pack defined like this in SDK 5::

   <dependency group="com.microej.pack" name ="fs" rev="6.0.4" />

  must be changed to this in SDK 6::

   microejArchitecture("com.microej.pack:fs:6.0.4")

- move the property related to the Runtime Capability from the file ``mjvm/mjvm.properties`` to the ``configuration/common.properties`` file,
  then delete the ``mjvm/mjvm.properties`` file.

- move all configuration properties related to the Packs (``bsp/bsp.properties``, ``fs/fs.properties``, ...) into a single ``configuration/common.properties``.
  Each property name must be prefixed by ``com.microej.pack.<name>.``, where ``<module>`` is the name of the Pack.
  For example, the ``bpp`` property defined in the ``display/display.properties`` file must be moved as ``com.microej.pack.display.bpp`` in the ``configuration/common.properties``.
  
  This is also true for BSP properties.
  For example, the ``microejapp.relative.dir`` property defined in the ``bsp/bsp.properties`` file must be moved as ``com.microej.bsp.microejapp.relative.dir`` in the ``configuration/common.properties``.

  Then old configuration properties files ((``bsp/bsp.properties``, ``display/display.properties``, ``fs/fs.properties``, ...) can be deleted.

- enable disable Pack modules if required, as described in :ref:`sdk_6_veeport_pack_enable_modules`.

- delete the ``.platform`` file located at the root of the Configuration subproject, since it is now obsolete.

Front Panel Project
-------------------

The Front Panel is generally a subproject of the VEE Port multi-project.
These steps must be followed to migrate a Front Panel subproject:

- replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- use the ``com.microej.gradle.mock-frontpanel`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.mock-frontpanel") version "0.17.0"
   }

- define the dependencies previously defined in the ``module.ivy`` file. 
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

- include the Front Panel subproject in the multi-project in the ``settings.gradle.kts`` file::
  
   include("my-front-panel")

- make the VEE Port configuration subproject depend on the Front Panel subproject by adding a project dependency in its ``build.gradle.kts`` file::

   microejFrontPanel(project("my-front-panel"))

Mock
----

If the VEE Port project contains Mock subprojects, they must be migrated by following these steps:

- replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- use the ``com.microej.gradle.mock`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.mock") version "0.17.0"
   }

- define the dependencies previously defined in the ``module.ivy`` file. 
  A Mock generally depends on libraries, so they can be defined with the ``implementation`` configuration.

- include the Mock subproject in the multi-project in the ``settings.gradle.kts`` file::
  
   include("my-mock")

- make the VEE Port configuration subproject depend on the Mock subproject by adding a project dependency in its ``build.gradle.kts`` file::

   microejTool(project("my-mock"))

Tool subproject
---------------

If the VEE Port project contains Tool subprojects, they must be migrated by following these steps:

- replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- use the ``com.microej.gradle.j2se-library`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.j2se-library") version "0.17.0"
   }

- define the dependencies previously defined in the ``module.ivy`` file. 
  A Tool generally depends on libraries, so they can be defined with the ``implementation`` configuration.
  Note that when the Tool is an Image Generator and depends on the Image Generator library from the UI Pack, the dependency must be declared with the ``name`` and ``extension``::

   implementation("com.microej.pack.ui:ui-pack:14.0.1") {
        artifact {
            name = "imageGenerator"
            extension = "jar"
        }
    }

- include the Tool subproject in the multi-project in the ``settings.gradle.kts`` file::
  
   include("my-tool")

- make the VEE Port configuration subproject depend on the Tool subproject by adding a project dependency in its ``build.gradle.kts`` file::

   microejTool(project("my-tool"))

Testsuites Project
------------------

These steps must be followed for each Testsuite to migrate:

- replace the ``module.ivy`` file by a ``build.gradle.kts`` file.
- use the ``com.microej.gradle.testsuite`` plugin in this file::
  
   plugins {
      id("com.microej.gradle.testsuite") version "0.17.0"
   }

- the tested VEE Port was defined in SDK 5 in the ``config.properties`` file, with the ``target.platform.dir`` property.
  In SDK6, it is done by declaring the VEE Port Configuration project as a project dependency::

   dependencies {
      microejVee(project(":my-vee-port"))
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

- the patterns of the included and excluded test classes was defined with the ``test.run.includes.pattern`` 
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

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
