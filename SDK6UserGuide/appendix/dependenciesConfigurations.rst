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
    - ``microejFullRuntimeClasspath``, used by the :ref:`sdk6_module_natures.tasks.runOnSimulator` and :ref:`sdk6_module_natures.tasks.buildApplicationObjectFile` tasks
    - ``microejVeeFullClasspath``, used by the :ref:`sdk6_module_natures.tasks.loadVee` task
    - ``microejVeeCompileClasspath``, used by the :ref:`sdk6_module_natures.application` plugin
    - ``microejVeeRuntimeClasspath``, used by the :ref:`sdk6_module_natures.application` plugin

.. _gradle_veeport_project_dependencies_configurations:

Dependencies Configurations in a VEE Port Project
--------------------------------------------------

This section describes all the dependency configurations added to your VEE Port project by the MicroEJ Gradle plugins.

The following graph describes the dependency configurations. Use this legend to interpret the colors:

    - Green background: Dependencies can be declared against this configuration
    - Gray background: This configuration is for consumption by tasks only
    - Blue background: The tasks

.. graphviz:: graphVeePortConfigurations.dot

.. _gradle_variants:

Variants
--------

The MicroEJ Gradle plugins define a list of `variants <https://docs.gradle.org/current/userguide/variant_model.html>`__ allowing to fetch the right component of a dependency 
based on the consumer's requirements. Each variant is configured with its own attributes. Refer to :ref:`gradle_variants_attributes` for more information about attributes.

Add-On Library
^^^^^^^^^^^^^^

The :ref:`sdk6_module_natures.addon_lib` plugin defines the following variants: 

runtimeAndMockElements
""""""""""""""""""""""

This variant is used to fetch a Library and its dependencies when it is declared with the ``implementation``  or ``api`` configuration in your VEE Port project.
It is configured with the following attribute:

- the custom ``com.microej.veeport.artifact.usage`` attribute, set to ``default``

Application
^^^^^^^^^^^

The :ref:`sdk6_module_natures.application` plugin defines the following variants: 

microejWPK
""""""""""

This variant is used to fetch the WPK of an Application when a dependency is declared with the ``microejApplication`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``application-wpk``
- the standard ``LibraryElement`` attribute, set to ``microej-wpk``

microejExecutable
"""""""""""""""""

This variant is used to fetch the Executable of an Application when a dependency is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``executable``
- the standard ``LibraryElement`` attribute, set to ``microej-executable``

microejExecutableBuildFiles
"""""""""""""""""""""""""""

This variant is used to publish the files generated when building the Executable of an Application.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``executable-build-files``

microejVirtualDevice
""""""""""""""""""""

This variant is used to fetch the Virtual Device of an Application when a dependency is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``virtual-device``
- the standard ``LibraryElement`` attribute, set to ``microej-vee-port``

microejFeatureBuildFiles
""""""""""""""""""""""""

This variant is used to publish the files generated when building the Feature of an Application.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``feature-build-files``

Mock
^^^^

The :ref:`sdk6_module_natures.mock` plugin defines the following variants: 

microejMockRip
""""""""""""""

This variant is used to fetch the RIP of a Mock when a dependency is declared with the ``microejMock`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.veeport.artifact.usage`` attribute, set to ``default``
- the standard ``LibraryElement`` attribute, set to ``microej-rip``

Runtime Environment
^^^^^^^^^^^^^^^^^^^

The :ref:`sdk6_module_natures.runtime-environment` plugin defines the following variants: 

runtimeEnvironment
""""""""""""""""""

This variant is used to fetch the Runtime Environment Jar when a dependency is declared with the ``microejRuntimeEnvironment`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``runtime-environment-api``
- the standard ``LibraryElement`` attribute, set to ``microej-runtime-environment``

VEE Port
^^^^^^^^

The :ref:`sdk6_module_natures.veeport` plugin defines the following variants: 

microejVeePort
""""""""""""""

This variant is used to fetch the VEE Port when it is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.veeport.artifact.usage`` attribute, set to ``default``
- the standard ``LibraryElement`` attribute, set to ``microej-vee-port``

apiElements
"""""""""""

This variant is used to fetch the Libraries provided by the VEE Port when it is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the standard ``Usage`` attribute, set to ``java-api``

runtimeElements
"""""""""""""""

This variant is used to fetch the Libraries provided by the VEE Port when it is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the standard ``Usage`` attribute, set to ``java-runtime``

.. _gradle_variants_attributes:

Attributes of a Variant
-----------------------

An attribute allows Gradle to select the right variant depending on the consumer's requirements. They are two types of attributes: standard attributes and custom attributes.

Standard Attributes
^^^^^^^^^^^^^^^^^^^

The standard attributes are defined by Gradle. Such an attribute is mandatory so the resolution of a dependency will fail if 
the producer did not define a variant with the attribute set to the same value. 
For example, if a VEE Port is defined using the ``implementation`` configuration, the build fails because the consumer wants a Jar but 
the VEE Port defines the ``LibraryElement`` attribute to ``microej-vee-port``:

.. code:: console

   > Could not resolve all files for configuration ':runtimeClasspath'.
   > Could not resolve com.mycompany:myVeePort:1.0.0.
     Required by:
         root project :
      > No matching variant of com.mycompany:myVeePort:1.0.0 was found. The consumer was configured to find a library for use during runtime, compatible with Java 8, packaged as a jar, preferably optimized for standard JVMs, and its dependencies declared externally but:
          - Variant 'microejVeePort' declares a library for use during runtime, compatible with Java 7, and its dependencies bundled (fat jar):
              - Incompatible because this component declares a component, with the library elements 'microej-vee-port' and the consumer needed a component, packaged as a jar
              - Other compatible attribute:
                  - Doesn't say anything about its target Java environment (preferred optimized for standard JVMs)


If no variant matches the consumer's requirements, Gradle can select a compatible variant. 
To make a variant compatible, the consumer must define a `compatibility rule <https://docs.gradle.org/current/userguide/variant_attributes.html#sec:abm-compatibility-rules>`__.

For example, this is the case for the Mocks built with SDK 6 ``1.1.0`` or below that are published with the ``LibraryElement`` attribute set to ``microej-rip``.
To build a VEE Port from an Application, a compatibility rule is required to ensure that the fetch of the VEE Port and its dependencies other than Mocks does not fail.

Custom Attributes
^^^^^^^^^^^^^^^^^

The custom attributes are defined by the user. These attributes are optional, so when resolving a dependency Gradle selects the default variant of the dependency if the 
producer did not define a variant with the attribute set to the same value. 

For example, this is the case for the Mocks built with SDK 6 ``1.2.0`` or higher that are published with the custom ``com.microej.veeport.artifact.usage`` attribute. This attribute is optional,
so when building a VEE Port from an Application, the VEE Port and all its dependencies other than Mocks are correctly fetched without having to define a compatiblity rule.

.. warning::
   Starting from SDK 6 ``1.3.0``, both a custom attribute and a standard attribute are used when resolving a MicroEJ dependency. 
   The standard attribute is still defined to ensure that modules built with SDK 6 ``1.2.0`` and below can be fetched by projects built with SDK 6 ``1.3.0`` or higher. 
   However, this attribute will be removed in the next major version, so it is highly recommended to update your project to use latest SDK 6 plugins.

For more information about variants and attributes, refer to `the official documentation <https://docs.gradle.org/current/userguide/variant_attributes.html>`__.   

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
