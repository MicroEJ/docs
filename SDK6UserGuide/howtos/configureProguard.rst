.. _sdk_6_howto_use_proguard:

How To Use Proguard
===================

`ProGuard <https://www.guardsquare.com/en/products/proguard>`_ is a tool that shrinks, optimizes, and obfuscates Java code.

To use Proguard in your project, add the following code in the ``build.gradle.kts``:

.. code-block:: java

    buildscript {
        repositories {
            mavenCentral()
        }
        dependencies {
            classpath("com.guardsquare:proguard-gradle:7.7.0")
        }
    }

    // Reads the classes listed with "-keep" in the "module.pro".
    fun getKeptClasses(): List<File> =
        file("module.pro").readLines()
            .map { it.trim() }
            .mapNotNull { line ->
                val regex = Regex("""^-keep\s+.*\bclass\s+([\w.$-]+)""")
                regex.find(line)?.groupValues?.get(1)
            }
            .map { fqn -> file("src/main/java/${fqn.replace('.', '/')}.java") }
            .filter { it.exists() }

    // Generates Javadoc only for the classes listed with "-keep".
    tasks.named<Javadoc>("javadoc") {
        setSource(files(getKeptClasses()))
    }

    // Packages the sources only with the classes listed with "-keep".
    tasks.named<Jar>("sourcesJar") {
        getKeptClasses().forEach {
                c -> include(c.relativeTo(file("src/main/java")).path)
        }
    }

    // Registers the Proguard task
    tasks.register<proguard.gradle.ProGuardTask>("proguard") {
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

    // Executes the Proguard task before publication
    tasks.named("generateMetadataFileForMicroejPublication") { dependsOn("proguard") }

This code registers a Proguard task that executes when the module is published.

The Proguard configuration is defined in a file named ``module.pro`` at the root of the project.
See the `ProGuard manual <https://www.guardsquare.com/manual/configuration/usage>`_ for all available options.

.. note::

    In this example, the ``javadoc`` and ``sourcesJar`` tasks are set to only include the classes listed with ``-keep`` in the ``module.pro`` file.
    This avoids publishing Javadoc and sources for the obfuscated classes.


..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
