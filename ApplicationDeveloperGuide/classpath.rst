.. _chapter.microej.classpath:

MicroEJ Classpath
#################

MicroEJ Applications run on a target device and their footprint is
optimized to fulfill embedded constraints. The final execution context
is an embedded device that may not even have a file system. Files
required by the application at runtime are not directly copied to the
target device, they are compiled to produce the application binary code
which will be executed by MicroEJ Core Engine.

As a part of the compile-time trimming process, all types not required
by the embedded application are eliminated from the final binary.

MicroEJ Classpath is a developer defined list of all places containing
files to be embedded in the final application binary. MicroEJ Classpath
is made up of an ordered list of paths. A path is either a folder or a
zip file, called a JAR file (JAR stands for Java ARchive).

-  :ref:`application.classpath.mapping` explains how the MicroEJ Classpath is built from a
   MicroEJ Application project.

-  :ref:`section.microej.link.and.load.model` explains how the application contents is loaded from
   MicroEJ Classpath.

-  :ref:`section.classpath.elements` specifies the different elements that can be declared
   in MicroEJ Classpath to describe the application contents.

.. _application.classpath.mapping:

Application Classpath
=====================

The following schema shows the classpath mapping from a MicroEJ
Application project to the MicroEJ Classpath ordered list of folders and
JAR files. The classpath resolution order (left to right) follows the
project appearance order (top to bottom).

.. figure:: images/ClassPath_4.png
   :alt: MicroEJ Application Classpath Mapping
   :align: center
   :scale: 70%

   MicroEJ Application Classpath Mapping

.. _section.microej.link.and.load.model:

Classpath Load Model
====================

A MicroEJ Application classpath is created via the loading of :

-  an entry point type,

-  all ``*.[extension].list`` files declared in a MicroEJ Classpath.

The different elements that constitute an application are described in
:ref:`section.classpath.elements`. They are searched within MicroEJ Classpath from left to
right (the first file found is loaded). Types referenced by previously loaded
MicroEJ Classpath elements are loaded transitively.

.. figure:: images/ClassPath_1.png
   :alt: Classpath Load Principle
   :align: center
   :scale: 65%

   Classpath Load Principle

.. _section.classpath.elements:

Classpath Elements
==================

The MicroEJ Classpath contains the following elements:

-  An entrypoint described in section :ref:`section.classpath.elements.entrypoints`;

-  Types in ``.class`` files, described in section :ref:`section.classpath.elements.types`;

-  Raw resources, described in section :ref:`section.classpath.elements.resources`;

-  Immutables Object data files, described in Section :ref:`section.classpath.elements.immutables`;

-  Images, Fonts and Native Language Support (NLS) resources, described in :ref:`chapter.microej.applicationResources`;

-  ``*.[extension].list`` files, declaring contents to load. Supported
   list file extensions and format is specific to declared application
   contents and is described in the appropriate section.

At source level, Java types are stored in ``src/main/java`` folder of the :ref:`module project <mmm_module_skeleton>`, 
any other kind of resources and list files are stored in the ``src/main/resources`` folder.

.. _section.classpath.elements.entrypoints:

Application Entry Points
------------------------

MicroEJ Application entry point declaration differs depending on the
application kind:

-  In case of a MicroEJ Standalone Application, it is a class that
   contains a ``public static void main(String[])`` method, declared
   using the option ``application.main.class``.

-  In case of a MicroEJ Sandboxed Application, it is a class that
   implements ``ej.kf.FeatureEntryPoint``, declared in the
   ``Application-EntryPoint`` entry in ``META-INF/MANIFEST.MF`` file.

.. _section.classpath.elements.types:

Types
-----

MicroEJ types (classes, interfaces) are compiled from source code
(``.java``) to classfiles (``.class``). When a type is loaded, all types
dependencies found in the classfile are loaded (transitively).

A type can be declared as a *Required type* in order to enable the
following usages:

-  to be dynamically loaded from its name (with a call to
   ``Class.forName(String)``);

-  to retrieve its fully qualified name (with a call to
   ``Class.getName()``).

A type that is not declared as a *Required type* may not have its fully
qualified name (FQN) embedded. Its FQN can be retrieved using the stack
trace reader tool (see :ref:`section.stacktrace.reader.tool`).

Required Types are declared in MicroEJ Classpath using ``*.types.list``
files. The file format is a standard Java properties file, each line
listing the fully qualified name of a type. Example:

::

   # The following types are marked as MicroEJ Required Types
   com.mycompany.MyImplementation
   java.util.Vector

.. _section.classpath.elements.resources:

Raw Resources
-------------

Raw resources are binary files that need to be embedded by the
application so that they may be dynamically retrieved with a call to
``Class.getResourceAsStream(java.io.InputStream)``. Raw Resources are
declared in MicroEJ Classpath using ``*.resources.list`` files. The file
format is a standard Java properties file, each line is a relative ``/``
separated name of a file in MicroEJ Classpath to be embedded as a
resource. Example:

::

   # The following resource is embedded as a raw resource
   com/mycompany/MyResource.txt

Others resources types are supported in MicroEJ Classpath, 
see :ref:`chapter.microej.applicationResources` for more details.

.. _section.classpath.elements.immutables:

Immutable Objects
-----------------

Immutables objects are regular read-only objects that can be retrieved
with a call to ``ej.bon.Immutables.get(String)``. Immutables objects are
declared in files called *immutable objects data files*, which format is
described in the :ref:`[BON] specification <esr-specifications>`.
Immutables objects data files are declared in MicroEJ Classpath using
``*.immutables.list`` files. The file format is a standard Java
properties file, each line is a ``/`` separated name of a relative file
in MicroEJ Classpath to be loaded as an Immutable objects data file.
Example:

::

   # The following file is loaded as an Immutable objects data files
   com/mycompany/MyImmutables.data


.. _system_properties:

System Properties
-----------------

System Properties are key/value string pairs that can be accessed with a
call to `System.getProperty(String) <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#getProperty-java.lang.String->`_. 

System Properties are defined when building a :ref:`standalone_application`,
by declaring ``*.properties.list`` files in MicroEJ Classpath. 

The file format is a standard Java properties file. Example:

.. code-block:: xml
   :caption: Example of Contents of a MicroEJ Properties File

   # The following property is embedded as a System property
   com.mycompany.key=com.mycompany.value
   microedition.encoding=ISO-8859-1

System Properties are resolved at runtime, and all declared keys and values are embedded as intern Strings.

System Properties can also be defined using :ref:`application_options`. This
can be done by setting the option with a specific
prefix in their name:

-  Properties for both the MicroEJ Core Engine and the MicroEJ Simulator :
   name starts with ``microej.java.property.*``

-  Properties for the MicroEJ Simulator: name starts with
   ``sim.java.property.*``

-  Properties for the MicroEJ Core Engine: name starts with
   ``emb.java.property.*``

For example, to define the property ``myProp`` with the value
``theValue``, set the following option :

.. code-block:: xml
   :caption: Example of MicroEJ System Property Definition as Application Option

   microej.java.property.myProp=theValue

Option can also be set in the ``VM arguments`` field of the ``JRE`` tab of the launch using the -D option (e.g. ``-Dmicroej.java.property.myProp=theValue``).

.. note::

   When building a :ref:`sandboxed_application`, ``*.properties.list`` files found in MicroEJ Classpath are silently skipped.

.. _section.classpath.elements.constants:

Constants
---------

.. note::
   This feature require :ref:`[BON] <esr-specifications>` version ``1.4`` 
   which is available in MicroEJ Runtime starting from MicroEJ Architecture version ``7.11.0``.

Constants are key/value string pairs that can be accessed with a
call to ``ej.bon.Constants.get[Type](String)``, where ``Type`` if one of:

- Boolean,
- Byte,
- Char,
- Class,
- Double,
- Float,
- Int,
- Long,
- Short,
- String.

Constants are declared in MicroEJ Classpath ``*.constants.list`` files. The file format is a
standard Java properties file. Example:

.. code-block:: xml
   :caption: Example of Contents of a BON constants File

   # The following property is embedded as a constant
   com.mycompany.myconstantkey=com.mycompany.myconstantvalue


Constants are resolved at binary level without having to recompile the sources. 

At link time, constants are directly inlined at the place of 
``Constants.get[Type]`` method calls with no cost. 

The String key parameter must be resolved as an inlined String:

- either a String literal ``"com.mycompany.myconstantkey"``
- or a ``static final String`` field resolved as a String constant

The String value is converted to the desired type using conversion rules described by the :ref:`[BON] <esr-specifications>` API.

.. _if_constant_removal:

A boolean constant declared in an ``if`` statement condition can be used to fully remove portions of code.
This feature is similar to C pre-processors ``#ifdef`` directive with the difference that this optimization is performed at binary level
without having to recompile the sources.

.. code-block:: java
   :caption: Example of ``if`` code removal using a BON boolean constant

   if (Constants.getBoolean("com.mycompany.myconstantkey")) {
          System.out.println("this code and the constant string will be fully removed when the constant is resolved to 'false'")
   }


.. note::
   In :ref:`Multi-Sandbox <multisandbox>` environment, constants are processed locally within each context.
   In particular, constants defined in the Kernel are not propagated to :ref:`Sandboxed Applications <sandboxed_application>`.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
