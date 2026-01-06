.. _sdk_6_howto_use_proguard:

How To Use Proguard
===================

`ProGuard <https://www.guardsquare.com/en/products/proguard>`_ is a tool that shrinks, optimizes, and obfuscates Java code. 
It can be executed as a task using the official `Proguard Gradle plugin <https://www.guardsquare.com/manual/setup/gradle>`_.

The code below registers a Proguard task that is executed whenever the ``jar`` task runs.
To use it, add the following snippet in your ``build.gradle.kts`` file:

.. code-block:: java

    buildscript {
        repositories {
            mavenCentral()
        }
        dependencies {
            classpath("com.guardsquare:proguard-gradle:7.8.2")
        }
    }

    // Registers the Proguard task
    tasks.register<proguard.gradle.ProGuardTask>("proguard") {
        dependsOn("jar")
        mustRunAfter("test")
        val jarTask = tasks.named("jar")
        val libsDir = layout.buildDirectory.dir("libs")
        val nonObfuscatedName = "${project.name}-${version}-non-obfuscated.jar"
        val nonObfuscatedJar = layout.buildDirectory.file("libs/$nonObfuscatedName")

        doFirst {
            copy {
                from(jarTask)
                into(libsDir)
                rename { nonObfuscatedName }
            }
        }

        configuration("module.pro")
        injars(nonObfuscatedJar)
        libraryjars(files(configurations.compileClasspath))
        outjars(jarTask)
    }

    // Makes Proguard automatically run whenever jar runs
    tasks.named("jar") {
        finalizedBy("proguard")
    }

To run Proguard on the project, you can either call ``./gradlew proguard`` directly or build the module with ``./gradlew build``.

In this example, the Proguard configuration is defined in a file named ``module.pro`` at the root of the project.
See the `ProGuard manual <https://www.guardsquare.com/manual/configuration/usage>`_ for all available options.

Javadoc and Sources Management
------------------------------

ProGuard does not automatically update Javadoc or sources JARs, it only obfuscates the compiled ``.class`` files contained in the main artifact.
As a result, the published Javadoc and sources may not correspond to the obfuscated bytecode and can inadvertently expose implementation details or sensitive code that should not be publicly available.

If this default behavior is not acceptable, you have two possible approaches:

- Do not publish Javadoc or sources for obfuscated artifacts.
- Restrict the published Javadoc and sources to classes matching ProGuard ``-keep`` rules.


Approach 1: Do not Publish Javadoc/Sources for Obfuscated Code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If publishing Javadoc and source artifacts is not required, you can simply disable the ``javadocJar`` and ``sourcesJar`` tasks.
In this case, the published module will not include the ``<module-name>-javadoc.jar`` and ``<module-name>-sources.jar`` artifacts.

Add the following to your ``build.gradle.kts`` file:

.. code-block:: java

    tasks.named("javadocJar") {
        enabled = false
    }

    tasks.named("sourcesJar") {
        enabled = false
    }

Approach 2: Include Only Classes Matching ProGuard ``-keep`` Rules
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A more selective approach consists of including only the classes that match the ProGuard ``-keep`` rules.

In the example below, the ``javadoc`` and ``sourcesJar`` tasks are configured to include only the classes explicitly listed with ``-keep`` directives in the ``module.pro`` file:

.. code-block:: java

    // Lists the classes matching "-keep" in the "module.pro".
    fun getKeptClasses(): List<File> =
        file("module.pro").readLines()
            .map { it.trim() }
            .mapNotNull { line ->
                val regex = Regex("""^-keep\s+.*\bclass\s+([\w.$-]+)""")
                regex.find(line)?.groupValues?.get(1)
            }
            .map { fqn -> file("src/main/java/${fqn.replace('.', '/')}.java") }
            .filter { it.exists() }

    // Generates Javadoc only for the classes matching "-keep".
    tasks.named<Javadoc>("javadoc") {
        dependsOn("proguard")
        setSource(files(getKeptClasses()))
    }

    // Packages the sources only with the classes matching "-keep".
    tasks.named<Jar>("sourcesJar") {
        dependsOn("proguard")
        getKeptClasses().forEach {
                c -> include(c.relativeTo(file("src/main/java")).path)
        }
    }

As a result, the published Javadoc and source artifacts will contain only the classes declared as part of the public API.

.. note::

    Depending on your Proguard configuration and the organization of your code, this approach may still include obfuscated methods within public classes.
    This occurs because the inclusion logic operates at the file (class) level rather than at the method level.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
