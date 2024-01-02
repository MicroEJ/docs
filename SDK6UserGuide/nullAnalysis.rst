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

- In each Java package, create a ``package-info.java`` file and annotate the Java package with ``@NonNullByDefault`` in you use Eclipse 
  or with your custom annotation if you use Android Studio or IntelliJ IDEA (see next section on IDEs configuration).
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
.. _EDC-1.3.3: https://repository.microej.com/modules/ej/api/edc/1.3.3/
.. _EDC 1.3.3 Changelog: https://repository.microej.com/modules/ej/api/edc/1.3.3/CHANGELOG-1.3.3.md

IDE Configuration 
-----------------

Requirements
~~~~~~~~~~~~

The project must depend at least on the version ``1.3.3`` of the ``ej.api:edc`` module::

  dependencies {
    implementation("ej.api:edc:1.3.3")
  }


Project configuration
~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

    To enable the Null Analysis tool in Android Studio and IntelliJ IDEA, refer to the official documentation on `Configure nullability annotations <https://www.jetbrains.com/help/idea/annotating-source-code.html#configure-nullability-annotations>`__.

    Both IDEs support custom annotations for ``Nullable`` and ``NotNull`` annotations, but not for ``NonNullByDefault``.
    Here are the solutions to be able to define all fields, methods return values and parameters of a whole class or package as non null by default:

    - create a custom annotation in your project using the ``@TypeQualifierDefault`` annotation, for example ``NonNullByDefault``:

      .. code:: java

        import javax.annotation.Nonnull;
        import javax.annotation.meta.TypeQualifierDefault;
        import java.lang.annotation.Documented;
        import java.lang.annotation.ElementType;
        import java.lang.annotation.Retention;
        import java.lang.annotation.RetentionPolicy;

        /**
        * This annotation can be applied to a package, class or method to indicate that the class fields,
        * method return types and parameters in that element are not null by default.
        */
        @Documented
        @Nonnull
        @TypeQualifierDefault(
                {
                        ElementType.ANNOTATION_TYPE,
                        ElementType.CONSTRUCTOR,
                        ElementType.FIELD,
                        ElementType.LOCAL_VARIABLE,
                        ElementType.METHOD,
                        ElementType.PACKAGE,
                        ElementType.PARAMETER,
                        ElementType.TYPE
                })
        @Retention(RetentionPolicy.RUNTIME)
        public @interface NonNullByDefault {
        }

      This requires to add the following dependency in your project::
        
        compileOnly("com.google.code.findbugs:jsr305:3.0.2")

    - add the ``@NonNull`` annotation explicitly on each field, method return value or parameter.
    - use the ``@javax.annotation.ParametersAreNonnullByDefault`` annotation. It is supported by Android Studio and IntelliJ IDEA.
      This requires to add the following dependency in your project::
        
        compileOnly("com.google.code.findbugs:jsr305:3.0.2")
    

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

        You may lose information if your target module project already has custom parameterization or if it was created with another MicroEJ SDK version. 
        In case of any doubt, please configure the options manually or merge with a text file comparator.


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
