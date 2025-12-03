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
    - ``microejVeeRuntimeClasspath``, used by the :ref:`sdk6_module_natures.application` plugin
    - ``microejMockClasspath``, used by the :ref:`sdk6_module_natures.addon_lib` plugin

.. _gradle_veeport_project_dependencies_configurations:

Dependencies Configurations in a VEE Port Project
--------------------------------------------------

This section describes all the dependency configurations added to your VEE Port project by the MicroEJ Gradle plugins.

The following graph describes the dependency configurations. Use this legend to interpret the colors:

    - Green background: Dependencies can be declared against this configuration
    - Gray background: This configuration is for consumption by tasks only
    - Blue background: The tasks

.. graphviz:: graphVeePortConfigurations.dot

.. _gradle_module_repository_project_dependencies_configurations:

Dependencies Configurations in a Module Repository Project
----------------------------------------------------------

This section describes all the dependency configurations added to your Module Repository project by the MicroEJ Gradle plugins.

The following graph describes the dependency configurations. Use this legend to interpret the colors:

    - Green background: Dependencies can be declared against this configuration
    - Gray background: This configuration is for consumption by tasks only
    - Blue background: The tasks

.. graphviz:: graphModuleRepositoryConfigurations.dot


For each dependency defined with ``microejModule``, a configuration ``microejModuleClasspath<group:name:version>``, where ``<group:name:version>`` is the group, name 
and version of the dependency, is created to ensure that each dependency has its own resolution graph.

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

additionalElements
""""""""""""""""""

This variant is used to publish the README, CHANGELOG and License files of the project.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``additional-files``

Application
^^^^^^^^^^^

The :ref:`sdk6_module_natures.application` plugin defines the following variants: 

microejWPK
""""""""""

This variant is used to fetch the WPK of an Application when a dependency is declared with the ``microejApplication`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``application-wpk``

microejExecutable
"""""""""""""""""

This variant is used to fetch the Executable of an Application when a dependency is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``executable``

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

microejFeatureBuildFiles
""""""""""""""""""""""""

This variant is used to publish the files generated when building the Feature of an Application.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``feature-build-files``

additionalElements
""""""""""""""""""

This variant is used to publish the README, CHANGELOG and License files of the project.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``additional-files``

Mock
^^^^

The :ref:`sdk6_module_natures.mock` plugin defines the following variants: 

microejMockRip
""""""""""""""

This variant is used to fetch the RIP of a Mock when a dependency is declared with the ``microejMock`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.veeport.artifact.usage`` attribute, set to ``default``

additionalElements
""""""""""""""""""

This variant is used to publish the README, CHANGELOG and License files of the project.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``additional-files``

Runtime Environment
^^^^^^^^^^^^^^^^^^^

The :ref:`sdk6_module_natures.runtime-environment` plugin defines the following variants: 

runtimeEnvironment
""""""""""""""""""

This variant is used to fetch the Runtime Environment Jar when a dependency is declared with the ``microejRuntimeEnvironment`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.artifact.element`` attribute, set to ``runtime-environment-api``

additionalElements
""""""""""""""""""

This variant is used to publish the README, CHANGELOG and License files of the project.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``additional-files``

VEE Port
^^^^^^^^

The :ref:`sdk6_module_natures.veeport` plugin defines the following variants: 

microejVeePort
""""""""""""""

This variant is used to fetch the VEE Port when it is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the custom ``com.microej.veeport.artifact.usage`` attribute, set to ``default``
- the standard ``Usage`` attribute, set to ``java-runtime``

apiElements
"""""""""""

This variant is used to fetch the Libraries provided by the VEE Port when it is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the standard ``Category`` attribute, set to ``library``
- the standard ``BUNDLING`` attribute, set to ``external``
- the standard ``LIBRARY_ELEMENTS`` attribute, set to ``jar``
- the standard ``Usage`` attribute, set to ``java-api``

runtimeElements
"""""""""""""""

This variant is used to fetch the Libraries provided by the VEE Port when it is declared with the ``microejVee`` configuration in your project.
It is configured with the following attributes:

- the standard ``Category`` attribute, set to ``library``
- the standard ``BUNDLING`` attribute, set to ``external``
- the standard ``LIBRARY_ELEMENTS`` attribute, set to ``jar``
- the standard ``Usage`` attribute, set to ``java-runtime``

javadocElements
"""""""""""""""

This variant is used to publish the aggregated Javadoc Jar file of all Libraries provided by the VEE Port with the ``api`` and the ``implementation`` configurations in your project.
It is configured with the following attributes:

- the standard ``Category`` attribute, set to ``documentation``
- the standard ``Bundling`` attribute, set to ``external``
- the standard ``DocType`` attribute, set to ``javadoc``
- the standard ``Usage`` attribute, set to ``java-runtime``

additionalElements
""""""""""""""""""

This variant is used to publish the README, CHANGELOG and License files of the project.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``additional-files``

Module Repository
^^^^^^^^^^^^^^^^^

The :ref:`sdk6_module_natures.module-repository` plugin defines the following variants: 

microejModuleRepository
"""""""""""""""""""""""

This variant is used to publish the Module Repository archive file.
It is configured with the following attributes:

- the custom ``com.microej.veeport.artifact.usage`` attribute, set to ``module-repository``
- the standard ``Usage`` attribute, set to ``java-runtime``

additionalElements
""""""""""""""""""

This variant is used to publish the README, CHANGELOG and License files of the project.
It is configured with the following attribute:

- the custom ``com.microej.artifact.element`` attribute, set to ``additional-files``

.. _gradle_variants_attributes:

Attributes of a Variant
-----------------------

An attribute allows Gradle to select the right variant depending on the consumer's requirements. They are two types of attributes: standard attributes and custom attributes. 
For more information about variants and attributes, refer to `the official documentation <https://docs.gradle.org/current/userguide/variant_attributes.html>`__.   


Standard Attributes
^^^^^^^^^^^^^^^^^^^

The standard attributes are defined by Gradle. Such an attribute is mandatory so the resolution of a dependency will fail if 
the producer did not define a variant with the attribute set to the same value. All standard attributes are listed in the `official documentation <https://docs.gradle.org/current/userguide/variant_attributes.html#sec:standard-attributes>`__.

For example, a VEE Port built with SDK 6 ``1.2.0`` or older is published with a single ``microejVeePort`` variant configured with the following attributes:

- the standard ``Category`` attribute, set to ``library``
- the standard ``Bundling`` attribute, set to ``embedded``
- the standard ``jvm.version`` attribute, set to ``7``
- the standard ``Libraryelements`` attribute, set to ``microej-vee-port``
- the standard ``Usage`` attribute, set to ``java-runtime``

When the VEE Port is declared as dependency with the ``implementation`` configuration, the following attributes are expected at runtime:

- the standard ``Category`` attribute, set to ``library``
- the standard ``Bundling`` attribute, set to ``external``
- the standard ``jvm.environment`` attribute, set to ``standard-jvm``
- the standard ``jvm.version`` attribute, set to ``11``
- the standard ``Libraryelements`` attribute, set to ``jar``
- the standard ``Usage`` attribute, set to ``java-runtime``

So the resolution fails because the ``microejVeePort`` variant of the VEE Port is incompatible:

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


If no variant matches the consumer's requirements, it is possible to make a variant compatible by defining a `compatibility rule <https://docs.gradle.org/current/userguide/variant_attributes.html#sec:abm-compatibility-rules>`__.

Custom Attributes
^^^^^^^^^^^^^^^^^

The custom attributes are defined by the user and are optional. When such attributes are used, the dependency resolution may differ depending on if the consumer defines them 
with standard attributes or not:

If the consumer specifies custom attributes only, the variant is selected as follows:

- If a variant is configured with the same custom attributes, Gradle selects it. 
- If no variant is compatible with the custom attributes, Gradle selects a runtime variant among the ones configured with standard attributes. For Java modules, 
  the variant selected by default is ``runtimeElements``.
- If there is no variant with standard attributes, the resolution fails.

If the consumer specifies custom and standard attributes, the variant is selected as follows: 

- If a variant is configured with the same custom and standard attributes, Gradle selects it. 
- If no variant is configured with the custom attributes:

    - If a variant is configured with the same standard attributes, Gradle selects it.
    - If there is no variant with same standard attributes, the resolution fails.  
- If no variant is configured with the same standard attributes, the resolution fails.
- If multiple variants are compatible, the resolution fails.

For example a Mock is published with the following variants:

.. code-block:: kotlin

    "variants": [
    {
      "name": "apiElements",
      "attributes": {
        "org.gradle.category": "library",
        "org.gradle.dependency.bundling": "external",
        "org.gradle.jvm.version": 11,
        "org.gradle.libraryelements": "jar",
        "org.gradle.usage": "java-api"
      },
    },
    {
      "name": "runtimeElements",
      "attributes": {
        "org.gradle.category": "library",
        "org.gradle.dependency.bundling": "external",
        "org.gradle.jvm.version": 11,
        "org.gradle.libraryelements": "jar",
        "org.gradle.usage": "java-runtime"
      },
    },
    {
      "name": "javadocElements",
      "attributes": {
        "org.gradle.category": "documentation",
        "org.gradle.dependency.bundling": "external",
        "org.gradle.docstype": "javadoc",
        "org.gradle.usage": "java-runtime"
      },
    },
    {
      "name": "sourcesElements",
      "attributes": {
        "org.gradle.category": "documentation",
        "org.gradle.dependency.bundling": "external",
        "org.gradle.docstype": "sources",
        "org.gradle.usage": "java-runtime"
      },
    },
    {
      "name": "additionalElements",
      "attributes": {
        "com.microej.artifact.element": "additional-files"
      },
    {
      "name": "microejMockRip",
      "attributes": {
        "com.microej.veeport.artifact.usage": "default"
      }
    }
  ]

So if it is declared as dependency with a custom attribute not defined by the producer:

.. code-block:: kotlin


    val myAttribute = Attribute.of("com.example.my-attribute", String::class.java)
    dependencies {
        microejModule("org.example:my-mock:1.0.0") {
            attributes {
                attribute(myAttribute, "special-value")
            }
        }
    }

the standard ``runtimeElements`` variant is selected and the Jar file of the Mock is fetched. However, if a Mock dependency is configured with a custom attribute and a standard variant:

.. code-block:: kotlin


    val myAttribute = Attribute.of("com.example.my-attribute", String::class.java)
    dependencies {
        microejModule("org.example:my-mock:1.0.0") {
            attributes {
                attribute(myAttribute, "special-value")
                attribute(LibraryElements.LIBRARY_ELEMENTS_ATTRIBUTE, objects.named(LibraryElements::class.java,  LibraryElements.OBJECTS))
            }
        }
    }

the resolution fails because Gradle does not know which variant must be selected:

.. code:: console

   > Could not resolve all dependencies for configuration ':microejMockRuntimeClasspath'.
   > Could not resolve org.example:my-mock:1.0.0.
     Required by:
         root project :
      > The consumer was configured to find a component, with the library elements 'objects', as well as attribute 'com.example.my-attribute' with value 'special-value'. However we cannot choose between the following variants of org.example:my-mock:1.0.0:
          - additionalElements
          - javadocElements
          - microejMockRip
          - sourcesElements
        All of them match the consumer attributes:
          - Variant 'additionalElements' capability 'org.example:my-mock:1.0.0':
              - Unmatched attributes:
                  - Doesn't say anything about com.example.my-attribute (required 'special-value')
                  - Doesn't say anything about its elements (required them with the library elements 'objects')
                  - Provides attribute 'com.microej.artifact.element' with value 'additional-files' but the consumer didn't ask for it
                  - Provides release status but the consumer didn't ask for it
          - Variant 'javadocElements' capability 'org.example:my-mock:1.0.0':
              - Unmatched attributes:
                  - Doesn't say anything about com.example.my-attribute (required 'special-value')
                  - Doesn't say anything about its elements (required them with the library elements 'objects')
                  - Provides documentation but the consumer didn't ask for it
                  - Provides its dependencies declared externally but the consumer didn't ask for it
                  - Provides javadocs but the consumer didn't ask for it
                  - Provides release status but the consumer didn't ask for it
                  - Provides runtime but the consumer didn't ask for it
          - Variant 'microejMockRip' capability 'org.example:my-mock:1.0.0':
              - Unmatched attributes:
                  - Doesn't say anything about com.example.my-attribute (required 'special-value')
                  - Doesn't say anything about its elements (required them with the library elements 'objects')
                  - Provides attribute 'com.microej.veeport.artifact.usage' with value 'default' but the consumer didn't ask for it
                  - Provides release status but the consumer didn't ask for it
          - Variant 'sourcesElements' capability 'org.example:my-mock:1.0.0':
              - Unmatched attributes:
                  - Doesn't say anything about com.example.my-attribute (required 'special-value')
                  - Doesn't say anything about its elements (required them with the library elements 'objects')
                  - Provides documentation but the consumer didn't ask for it
                  - Provides its dependencies declared externally but the consumer didn't ask for it
                  - Provides release status but the consumer didn't ask for it
                  - Provides runtime but the consumer didn't ask for it
                  - Provides sources but the consumer didn't ask for it

If no variant matches the consumer's requirements, it is possible to make a variant compatible by defining a `compatibility rule <https://docs.gradle.org/current/userguide/variant_attributes.html#sec:abm-compatibility-rules>`__.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
