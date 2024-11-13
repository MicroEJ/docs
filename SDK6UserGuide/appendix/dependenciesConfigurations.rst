.. _gradle_dependencies_configurations_chapter:

Dependencies Configurations
===========================

This chapter describes all the dependency configurations added to your project by the MicroEJ Gradle plugins.

.. note::

   The MicroEJ Gradle plugins extend the Gradle Java and Java Library plugins.
   For more information about the configurations inherited from those plugins, 
   refer to the official documentation :
   
      - `Java plugin <https://docs.gradle.org/current/userguide/java_plugin.html#sec:java_plugin_and_dependency_management>`__
      - `Java Library plugin <https://docs.gradle.org/current/userguide/java_library_plugin.html#sec:java_library_separation>`__

The following graph describes the dependency configurations. Use this legend to interpret the colors:

    - Green background : Dependencies can be declared against this configuration
    - Gray background : This configuration is for consumption by tasks only
    - Blue background : A task

.. graphviz:: graphConfigurations.dot

The MicroEJ Gradle plugins also define dependency configurations for internal use:

    - ``antScriptLauncherClasspath``, used by the :ref:`sdk6_module_natures.tasks.buildVirtualDevice` task
    - ``addonProcessorClasspath`` , used by the :ref:`sdk6_module_natures.tasks.adp` task
    - ``jdtCompilerClasspath``, used by the :ref:`sdk6_module_natures.addon_lib` and :ref:`sdk6_module_natures.application` plugins
    - ``wrapperClasspath``, used by the ``compileJava`` task
    - ``microejRuntimeEnvironmentFullRuntimeClasspath``, used by the :ref:`sdk6_module_natures.tasks.buildVirtualDevice`, :ref:`sdk6_module_natures.tasks.buildApplicationObjectFile` and :ref:`sdk6_module_natures.tasks.buildExecutable` tasks

Publication Variants
--------------------

The :ref:`sdk6_module_natures.application` plugin defines a list of variants 
that are used during the publication of an Application.

microejWPK
~~~~~~~~~~

This variant is used to publish the WPK of an Application, 
that can be fetched by declaring a dependency with the ``microejApplication`` configuration.
The ``LibraryElement`` attribute of the variant is set to ``microej-wpk``.

microejExecutable
~~~~~~~~~~~~~~~~~

This variant is used to publish the Executable of an Application, 
that can be fetched by declaring a dependency with the ``microejVee`` configuration.
The ``LibraryElement`` attribute of the variant is set to ``microej-executable``.

microejExecutableBuildFiles
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This variant is used to publish the files generated when building the Executable of an Application.
The ``LibraryElement`` attribute of the variant is set to ``microej-build-files``.

microejVirtualDevice
~~~~~~~~~~~~~~~~~~~~

This variant is used to publish the Virtual Device of an Application, 
that can be fetched by declaring a dependency with the ``microejVee`` configuration.
The ``LibraryElement`` attribute of the variant is set to ``microej-vee-port``.

microejMockRip
~~~~~~~~~~~~~~

This variant is used to publish a Mock.
The ``LibraryElement`` attribute of the variant is set to ``microej-rip``.

runtimeEnvironment
~~~~~~~~~~~~~~~~~~

This variant is used to publish a Runtime Environment, 
that can be fetched by declaring a dependency with the ``microejRuntimeEnvironment`` configuration.
The ``LibraryElement`` attribute of the variant is set to ``microej-runtime-environment``.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
