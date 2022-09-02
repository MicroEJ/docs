==
KF
==


Definitions
===========

.. _kf-feature-definition:

Feature Definition Files
------------------------

A Feature is a group of types, resources and :ref:`[BON] <runtime_bon>` immutables objects
defined using two files that shall be in Application classpath:

-  ``[featureName].kf``, a Java properties file. Keys are described in
   :ref:`the "Feature definition file properties" table below <table_kf-feature-keys>`.

-  ``[featureName].cert``, an X509 certificate file that uniquely
   identifies the Feature

.. _table_kf-feature-keys:
.. tabularcolumns:: |p{2.5cm}|p{2cm}|p{10.5cm}|
.. list-table:: Feature definition file properties
   :widths: 1 1 8
   :header-rows: 1

   * - Key
     - Usage
     - Description
   * - entryPoint
     - Mandatory
     - The fully qualified name of the class that implements `ej.kf.FeatureEntryPoint`_
   * - immutables
     - Optional
     - Semicolon separated list of paths to :ref:`[BON] <runtime_bon>` immutable files owned by the Feature. ``[BON]`` immutable file is defined by a ``/`` separated path relative to application classpath
   * - resources
     - Optional
     - Semicolon separated list of resource names owned by the Feature. Resource name is defined by `Class.getResourceAsStream(String)`_
   * - requiredTypes
     - Optional
     - Comma separated list of fully qualified names of required types. (Types that may be dynamically loaded using `Class.forName()`_).
   * - types
     - Optional
     - Comma separated list of fully qualified names of types owned by the Feature. A wildcard is allowed as terminal character to embed all types starting with the given qualified name (``a.b.C,x.y.*``)
   * - version
     - Mandatory
     - String version, that can retrieved using `ej.kf.Module.getVersion()`_

.. _ej.kf.FeatureEntryPoint: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/FeatureEntryPoint.html
.. _Class.getResourceAsStream(String): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getResourceAsStream-java.lang.String-
.. _Class.forName(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#forName-java.lang.String-
.. _ej.kf.Module.getVersion(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Module.html#getVersion--

Kernel Definition Files
-----------------------

Kernel definition files are mandatory if one or more Feature definition
file is loaded and are named ``kernel.kf`` and ``kernel.cert``.
``kernel.kf`` must only define the ``version`` key. All types, resources
and immutables are automatically owned by the Kernel if not explicitly
set to be owned by a Feature.

Kernel API Files
----------------

Kernel API file definition is explained here :ref:`Kernel API <kernel.api.def>`.

Access Error Codes
------------------

When an instruction is executed that will break a :ref:`[KF] specification <kf_specification>` insulation
semantic rule, a `java.lang.IllegalAccessError`_ is thrown, with an
error code composed of two parts: ``[source][errorKind]``.

-  ``source``: a single character indicating the kind of Java element on
   which the access error occurred
   (:ref:`Table "Error codes: source" <table_kf-errorcodes-source>`)

-  ``errorKind``: an error number indicating the action on which the
   access error occurred (:ref:`Table "Error codes: kind" <table_kf-errorcodes-kind>`)

.. _table_kf-errorcodes-source:
.. table:: Error codes: source

   +---------+------------------------------------------------------------+
   | Ch      | Description                                                |
   | aracter |                                                            |
   +=========+============================================================+
   | A       | Error thrown when accessing an array                       |
   +---------+------------------------------------------------------------+
   | I       | Error thrown when calling a method                         |
   +---------+------------------------------------------------------------+
   | F       | Error thrown when accessing an instance field              |
   +---------+------------------------------------------------------------+
   | M       | Error thrown when entering a synchronized block or method  |
   +---------+------------------------------------------------------------+
   | P       | Error thrown when passing a parameter to a method call     |
   +---------+------------------------------------------------------------+
   | R       | Error thrown when returning from a method call             |
   +---------+------------------------------------------------------------+
   | S       | Error thrown when accessing a static field                 |
   +---------+------------------------------------------------------------+

.. _table_kf-errorcodes-kind:
.. table:: Error codes: kind

   +---------+------------------------------------------------------------+
   | Id      | Description                                                |
   +=========+============================================================+
   | 1       | An object owned by a Feature is being assigned to an       |
   |         | object owned by the Kernel, but the current context is not |
   |         | owned by the Kernel                                        |
   +---------+------------------------------------------------------------+
   | 2       | An object owned by a Feature is being assigned to an       |
   |         | object owned by another Feature                            |
   +---------+------------------------------------------------------------+
   | 3       | An object owned by a Feature is being accessed from a      |
   |         | context owned by another Feature                           |
   +---------+------------------------------------------------------------+
   | 4       | A synchronize on an object owned by the Kernel is executed |
   |         | in a method owned by a Feature                             |
   +---------+------------------------------------------------------------+
   | 5       | A call to a feature code occurs while owning a Kernel      |
   |         | monitor                                                    |
   +---------+------------------------------------------------------------+

.. _java.lang.IllegalAccessError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalAccessError.html

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.