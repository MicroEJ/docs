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

Kernel API file definition is explained here: :ref:`Kernel API <kernel.api.def>`.

.. _kf-access-error-codes:

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

   +-----------+------------------------------------------------------------+
   | Character | Description                                                |
   +===========+============================================================+
   | A         | Error thrown when accessing an array                       |
   +-----------+------------------------------------------------------------+
   | I         | Error thrown when calling a method                         |
   +-----------+------------------------------------------------------------+
   | F         | Error thrown when accessing an instance field              |
   +-----------+------------------------------------------------------------+
   | M         | Error thrown when entering a synchronized block or method  |
   +-----------+------------------------------------------------------------+
   | P         | Error thrown when passing a parameter to a method call     |
   +-----------+------------------------------------------------------------+
   | R         | Error thrown when returning from a method call             |
   +-----------+------------------------------------------------------------+
   | S         | Error thrown when accessing a static field                 |
   +-----------+------------------------------------------------------------+

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


.. _kf-loader-error-codes:

Feature Installation and Loading Error Codes
--------------------------------------------

When an error occurs during the installation of a Feature via the `Kernel.install(InputStream)`_ method,
or during the loading of installed Features at bootstrap, 
the system may throw an `ej.kf.InvalidFormatException`_. 

This exception carries a specific error code, which can be retrieved by calling the `getMessage()`_ method 
on the `InvalidFormatException`_ instance.
The returned message will follow the format: ``code=<id>``, where ``id`` corresponds the specific error encountered.

Error codes ranging from ``150`` to ``180``, thrown during Feature installation, typically indicate an invalid or corrupted Feature file. 
This corruption may occur during the file transfer process.

Other possible causes for this exception include errors returned by the LLKERNEL abstraction layer, 
or issues with a stored Feature, such as corruption or incompatibility.

.. _table_kf-install-errorcodes-llkernel:
.. table:: Feature Installation Error Codes Related to LLKERNEL Implementation

   +---------+----------------------------------------------------------------+
   | Id      | Description                                                    |
   +=========+================================================================+
   | 51      | The ``LLKERNEL_impl_copyToROM()`` function returned an error.  |
   +---------+----------------------------------------------------------------+
   | 52      | The maximum number of installed Features is reached.           |
   +---------+----------------------------------------------------------------+
   | 54      | The address returned by the last call to                       |
   |         | ``LLKERNEL_impl_getFeatureAddressRAM()`` or                    |
   |         | ``LLKERNEL_impl_getFeatureAddressROM()`` does not match the    |
   |         | alignment constraint.                                          |
   +---------+----------------------------------------------------------------+
   | 55      | The address returned by the last call to                       |
   |         | ``LLKERNEL_impl_getFeatureAddressROM()`` overlaps with a       |
   |         | previously returned address.                                   |
   +---------+----------------------------------------------------------------+
   | 56      | The address returned by the last call to                       |
   |         | ``LLKERNEL_impl_getFeatureAddressRAM()`` overlaps with a       |
   |         | previously returned address.                                   |
   +---------+----------------------------------------------------------------+
   | 58      | The ``.fo`` file cannot be installed on this Kernel because it | 
   |         | contains a code chunk section with a size greater than this    |
   |         | Kernel code chunk size.                                        |
   +---------+----------------------------------------------------------------+
   | 59      | The ``LLKERNEL_IMPL_allocateFeature()`` function returned      |
   |         | ``0``. The Feature cannot be allocated in memory.              | 
   +---------+----------------------------------------------------------------+

.. _table_kf-load-errorcodes-llkernel:
.. table:: Installed Feature Loading Error Codes

   +---------+----------------------------------------------------------------+
   | Id      | Description                                                    |
   +=========+================================================================+
   | 53      | The installed Feature content has been corrupted               |
   |         | (CRC check error).                                             |
   +---------+----------------------------------------------------------------+
   | 57      | The address returned by the last call to                       |
   |         | ``LLKERNEL_impl_getFeatureAddressRAM()`` is not the same than  |
   |         | the one returned when the Feature has been installed.          |
   +---------+----------------------------------------------------------------+
   | 60      | The ``LLKERNEL_IMPL_getFeatureHandle()`` function returned     |
   |         | ``0``. The Feature cannot be allocated in memory.              |
   +---------+----------------------------------------------------------------+
   
.. _java.lang.IllegalAccessError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalAccessError.html
.. _Kernel.install(InputStream): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream-
.. _ej.kf.InvalidFormatException: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/InvalidFormatException.html
.. _InvalidFormatException: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/InvalidFormatException.html
.. _getMessage(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html#getMessage--

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.