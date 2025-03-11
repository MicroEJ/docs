.. _java_lambdas_chapter:

Java Lambdas
============

To support :ref:`Java lambdas <java_lambdas>` in the code of an Application, the SDK uses a forked version of `RetroLambda <https://github.com/luontola/retrolambda>`__. 

RetroLambda is not compatible with the Java versions :ref:`required by the SDK <sdk_6_system_requirements>`, so a Java 8 toolchain is internally used by the SDK 
to manage Java lambdas.

By default Gradle will use the Java toolchain available locally, but it can be configured to automatically download one by applying the `Foojay Toolchains Plugin <https://github.com/gradle/foojay-toolchains>`__ in the ``settings.gradle.kts`` file of your project::

    plugins {
        id("org.gradle.toolchains.foojay-resolver-convention").version("0.9.0")
    }

This settings plugin downloads the first Java toolchain matching the specified requirements that it finds among the 
`JVM Vendors <https://docs.gradle.org/current/userguide/toolchains.html#sec:precedence>`__ recognized by Gradle and unzips it in the ``$USER_HOME/.gradle/.jdks`` folder, 
so you do not have to install one manually.

.. note::

   A Java 8 toolchain is only required if the Java lambdas are enabled on your Application project. If it is not the case, you do not need to apply the ``Foojay Toolchains Plugin``.

Applied on a MicroEJ project, the plugin downloads the first Java 8 toolchain found, but it is possible to specify a Vendor by configuring the Java toolchain in the ``build.gradle.kts`` file of your project if needed::

    tasks.processMainLambdas.configure {
        javaLauncher.set(javaToolchains.launcherFor {
            languageVersion = JavaLanguageVersion.of(8)
            vendor = JvmVendorSpec.ADOPTIUM
        })
    }

.. note::
  
   For each source set defined in your project, a ``processXXXLambdas`` task exists. To modify the Java toolchain, 
   you must configure the task corresponding to the source set containing Java lambdas. For example, if they are used in the ``src/main/java`` source set, 
   the ``processMainLambdas`` task must be configured. 

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
