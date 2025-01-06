.. _sdk6_null_analysis:

Null Analysis
=============

`NullPointerException`_ thrown at runtime is one of the most common causes for failure of Java programs.
All modern IDEs provide a Null Analysis tool which can detect such programming errors (misuse of potential ``null`` Java values) at compile-time.

.. _NullPointerException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/NullPointerException.html

Principle
---------

The Null Analysis tool is based on Java annotations. 
Each Java field, method parameter and method return value must be marked to indicate whether it can be ``null`` or not.

Once the Java code is annotated, the IDE must be configured to enable Null Analysis detection.


Java Code Annotation
---------------------

MicroEJ defines its own annotations:

- `@NonNullByDefault`_: Indicates that all fields, method return values or parameters can never be null in the annotated package or type.
  This rule can be overridden on each element by using the ``@Nullable`` annotation.
  
- `@Nullable`_: Indicates that a field, local variable, method return value or parameter can be null.

- `@NonNull`_: Indicates that a field, local variable, method return value or parameter can never be null.

MicroEJ recommends to annotate the Java code as follows:

- In each Java package, create a ``package-info.java`` file and annotate the Java package with ``@NonNullByDefault``.
  This is a common good practice to deal with non ``null`` elements by default to avoid undesired `NullPointerException`_.
  It enforces the behavior which is already widely outlined in Java coding rules.

  .. code:: java

    @ej.annotation.NonNullByDefault
    package com.mycompany;

- In each Java type, annotate all fields, methods return values and parameters that can be null with ``@Nullable``.
  Usually, this information is already available as textual information in the field or method Javadoc comment. 
  The following example of code shows where annotations must be placed:

  .. code:: java

    @Nullable
    public Object thisFieldCanBeNull;

    @Nullable
    public Object thisMethodCanReturnNull() {
      return null;
    }

    public void thisMethodParameterCanBeNull(@Nullable Object param) {

    }


.. _@NonNullByDefault: https://repository.microej.com/javadoc/microej_5.x/apis/ej/annotation/NonNullByDefault.html
.. _@Nullable: https://repository.microej.com/javadoc/microej_5.x/apis/ej/annotation/Nullable.html
.. _@NonNull: https://repository.microej.com/javadoc/microej_5.x/apis/ej/annotation/NonNull.html

IDE Configuration 
-----------------

Requirements
~~~~~~~~~~~~

The project must depend at least on the version ``1.3.6`` of the ``ej.api:edc`` module::

  dependencies {
    implementation("ej.api:edc:1.3.6")
  }


Project configuration
~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

    Follow these steps to enable the Null Analysis tool in Android Studio and IntelliJ IDEA:

    - Go to :guilabel:`File` > :guilabel:`Settings...`.
    - Go to :guilabel:`Editor` > :guilabel:`Inspections`.
    - Open the category :guilabel:`Java` > :guilabel:`Probable Bugs` > :guilabel:`Nullability problems` > :guilabel:`@NotNull/@Nullable problems`.
    - In the :guilabel:`Options` panel, scroll down and click on the :guilabel:`Configure Annotations...` button.

        .. figure:: images/intellij-null-analysis.png
           :alt: Null Analysis Checks Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    - In the :guilabel:`Nullable` tab, click on the :guilabel:`+` button.
    - Type ``ej.annotation.Nullable`` and select the listed class.

          .. figure:: images/intellij-null-analysis-nullabe-annotation.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    - Select ``ej.annotation.Nullable`` in the :guilabel:`Nullable annotations` list.
    - Go to the :guilabel:`NotNull` tab and repeat the same steps with the ``ej.annotation.NonNull`` class.
    - Click on the :guilabel:`OK` button.
    - Change the :guilabel:`Severity` field to :guilabel:`Error`.
    - Check the :guilabel:`Report @NotNull parameters overriding non-annotated` option.

          .. figure:: images/intellij-null-analysis-configuration-01.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    - Check and select the category :guilabel:`Java` > :guilabel:`Probable Bugs` > :guilabel:`Nullability problems` > :guilabel:`Return of 'null'`.
    - Change the :guilabel:`Severity` field to :guilabel:`Error`.

          .. figure:: images/intellij-null-analysis-configuration-02.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%
    
    - Select the category :guilabel:`Java` > :guilabel:`Probable Bugs` > :guilabel:`Nullability problems` > :guilabel:`Return value is outside of declared range`.
    - Change the :guilabel:`Severity` field to :guilabel:`Error`.

          .. figure:: images/intellij-null-analysis-configuration-03.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    
    - Select the category :guilabel:`Java` > :guilabel:`Probable Bugs` > :guilabel:`Nullability and data flow problems`.
    - Change the :guilabel:`Severity` field to :guilabel:`Error`.

          .. figure:: images/intellij-null-analysis-configuration-04.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    - Check and select the category :guilabel:`Java` > :guilabel:`Probable Bugs` > :guilabel:`Nullability problems` > :guilabel:`@NotNull field is not initialized`.
    - Change the :guilabel:`Severity` field to :guilabel:`Error`.
    - Uncheck the :guilabel:`Ignore fields which could be initialized implicitly` option.
    - Uncheck the :guilabel:`Ignore fields initialized in setUp() method` option.

          .. figure:: images/intellij-null-analysis-configuration-05.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    - Check and select the category :guilabel:`Java` > :guilabel:`Javadoc` > :guilabel:`Missing'package-info.java'`.
    - Change the :guilabel:`Severity` field to :guilabel:`Error`.

          .. figure:: images/intellij-null-analysis-configuration-06.png
           :alt: Nullable Annotation Configuration in IntelliJ IDEA and Android
           :align: center
           :scale: 100%

    For more details, refer to the official documentation on `Configure nullability annotations <https://www.jetbrains.com/help/idea/annotating-source-code.html#configure-nullability-annotations>`__.


   .. tab:: Eclipse

      To enable the Null Analysis tool in Eclipse, a project must be configured as follows:

      - In the Package Explorer, right-click on the module project and select :guilabel:`Properties`,
      - Navigate to :guilabel:`Java Compiler` > :guilabel:`Errors/Warnings`,
      - In the :guilabel:`Null analysis` section, configure options as follows:

        .. figure:: images/null_analysis_project_configuration_checks.png
           :alt: Null Analysis Eclipse Checks Configuration
           :align: center
           :scale: 100%

      - Click on the :guilabel:`Configure...` link to configure MicroEJ annotations:
        
        - ``ej.annotation.Nullable``
        - ``ej.annotation.NonNull``
        - ``ej.annotation.NonNullByDefault``

        .. figure:: images/null_analysis_project_configuration_annotations.png
          :alt: Null Analysis Eclipse Annotations Configuration
          :align: center
          :scale: 100%

      - In the :guilabel:`Annotations` section, check :guilabel:`Suppress optional errors with '@SuppressWarnings'` option:
        
        .. figure:: images/null_analysis_project_configuration_suppress_warnings.png
          :alt: Null Analysis Eclipse Suppress Warnings Configuration
          :align: center
          :scale: 100%

        This option allows to fully ignore Null Analysis errors in advanced cases using ``@SuppressWarnings("null")`` annotation.


      If you have multiple projects to configure, you can then copy the content of the ``.settings`` folder to an other module project.

      .. figure:: images/null_analysis_settings_folder.png
        :alt: Null Analysis Settings Folder
        :align: center
        :scale: 100%
          
        Null Analysis Settings Folder

      .. warning::

        You may lose information if your target module project already has custom parameterization or if it was created with another SDK version. 
        In case of any doubt, please configure the options manually or merge with a text file comparator.

Launching Null Analysis
-----------------------

While Eclipse automatically launches Null Analysis on the whole project and reports all the problems found, 
IntelliJ IDEA and Android Studio launch the Null Analysis only on the currently open file.
In order to launch an Analysis of the full project:

- Go to :guilabel:`Code` > :guilabel:`Inspect Code`.
- Check the :guilabel:`Whole project` option.
- Uncheck the :guilabel:`Include test sources` option.
- Click on :guilabel:`Analyze`.

Disabling Analysis for Test Folder
----------------------------------

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

    The Analysis of the test folder can be disabled by unchecking the option ``Include test sources`` when launching a Code Inspection:

        .. figure:: images/intellij-null-analysis-code-inspection.png
          :alt: Disabling Analysis in Test Folder
          :align: center
          :scale: 100%


   .. tab:: Eclipse

    The Null Analysis can be automatically disabled in test folder by using the ``eclipse-wtp`` Gradle plugin:

    - In the ``build.gradle.kts`` plugin of the project, add the ``eclipse-wtp`` plugin:

      .. code-block::

        plugins {
          ...
          `eclipse-wtp`
        }
    
    - Then add the following snippet of code:

      .. code-block:: java

        import org.gradle.plugins.ide.eclipse.model.AbstractClasspathEntry
        import org.gradle.plugins.ide.eclipse.model.Classpath

        eclipse.classpath.file {
            whenMerged(Action<Classpath> {
                entries.filter { entry ->
                    (entry.kind == "src" && entry is AbstractClasspathEntry && entry.path == "src/test/java")
                }.forEach { entry ->
                    (entry as AbstractClasspathEntry).entryAttributes["ignore_optional_problems"] = "true"
                }
            })
        }

      Adapth the path of your test folder accordingly.


Sharing Null Analysis IDE Configuration
---------------------------------------

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

    The configuration related to Null Analysis is located in the ``.idea/misc.xml`` and ``.idea/inspectionProfiles/*`` files.
    In order to share them, they must be committed in your project source reposiory.
    For Git projects, if you decided to not commit the IDE configuration files, 
    these files can be excluded with the following lines in the ``.gitignore`` file::

      /.idea/*
      !/.idea/misc.xml
      !/.idea/inspectionProfiles/*

      .. warning::

        Android Studio and IntelliJ IDEA create a ``.gitignore`` file in the ``.idea`` folder.
        You can remove it or adapt it to fit your needs.

   .. tab:: Eclipse

    The configuration related to Null Analysis is located in the ``.settings/org.eclipse.jdt.core.prefs`` file.
    In order to share it, it must be committed in your project source reposiory.
    For Git projects, if you decided to not commit the IDE configuration files, 
    these files can be excluded with the following lines in the ``.gitignore`` file::

      /.settings/*
      !/.settings/org.eclipse.jdt.core.prefs


MicroEJ Libraries
-----------------

Many libraries available on :ref:`central_repository` are annotated with Null Analysis. 
If you are using a library which is not yet annotated, please contact :ref:`our support team <get_support>`.

For the benefit of Null Analysis, some APIs have been slightly constrained compared to the Javadoc description.
Here are some examples to illustrate the philosophy:

- `System.getProperty(String key, String def)`_ does not accept a ``null`` default value, 
  which allows to ensure the returned value is always non ``null``.
- Collections of the Java Collections Framework that can hold ``null`` elements (e.g. `HashMap`_) do not accept ``null`` elements. 
  This allows APIs to return ``null`` (e.g. `HashMap.get(Object)`_) only when an element is not contained in the collection.

Implementations are left unchanged and still comply with the Javadoc description whether the Null Analysis is enabled or not. 
So if these additional constraints are not acceptable for your project, please disable Null Analysis.

.. _System.getProperty(String key, String def): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#getProperty-java.lang.String-java.lang.String-
.. _HashMap: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/HashMap.html
.. _HashMap.get(Object): https://repository.microej.com/javadoc/microej_5.x/apis/java/util/HashMap.html#get-java.lang.Object-


..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
