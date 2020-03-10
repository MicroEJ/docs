==
KF
==


Definitions
===========

.. _kf-feature-definition:

Feature Definition Files
------------------------

A Feature is a group of types, resources and [B-ON] immutables objects
defined using two files that shall be in application classpath:

-  ``[featureName].kf``, a Java properties file. Keys are described in
   :ref:`the "Feature definition file properties" table below <table_kf-feature-keys>`.

-  ``[featureName].cert``, an X509 certificate file that uniquely
   identifies the Feature

.. _table_kf-feature-keys:
.. tabularcolumns:: |p{2.5cm}|p{2cm}|p{10.5cm}|
.. table:: Feature definition file properties

   +---------------+-----------+-----------------------------------------------+
   | Key           | Usage     | Description                                   |
   +===============+===========+===============================================+
   | entryPoint    | Mandatory | The fully qualified name of the class that    |
   |               |           | implements ``ej.kf.FeatureEntryPoint``        |
   +---------------+-----------+-----------------------------------------------+
   | immutables    | Optional  | Semicolon separated list of paths to [B-ON]   |
   |               |           | immutable files owned by the Feature. [B-ON]  |
   |               |           | immutable file is defined by a ``/``          |
   |               |           | separated path relative to application        |
   |               |           | classpath                                     |
   +---------------+-----------+-----------------------------------------------+
   | resources     | Optional  | Semicolon separated list of resource names    |
   |               |           | owned by the Feature. Resource name is        |
   |               |           | defined by                                    |
   |               |           | ``Class.getResourceAsStream(String)``         |
   +---------------+-----------+-----------------------------------------------+
   | requiredTypes | Optional  | Comma separated list of fully qualified names |
   |               |           | of required types. (Types that may be         |
   |               |           | dynamically loaded using                      |
   |               |           | ``Class.forName()``).                         |
   +---------------+-----------+-----------------------------------------------+
   | types         | Optional  | Comma separated list of fully qualified names |
   |               |           | of types owned by the Feature. A wildcard is  |
   |               |           | allowed as terminal character to embed all    |
   |               |           | types starting with the given qualified name  |
   |               |           | (``a.b.C,x.y.*``)                             |
   +---------------+-----------+-----------------------------------------------+
   | version       | Mandatory | String version, that can retrieved using      |
   |               |           | ``ej.kf.Module.getVersion()``                 |
   +---------------+-----------+-----------------------------------------------+

Kernel Definition Files
-----------------------

Kernel definition files are mandatory if one or more Feature definition
file is loaded and are named ``kernel.kf`` and ``kernel.cert``.
``kernel.kf`` must only define the ``version`` key. All types, resources
and immutables are automatically owned by the Kernel if not explicitly
set to be owned by a Feature.

Kernel API Definition
~~~~~~~~~~~~~~~~~~~~~

Kernel types, methods and static fields allowed to be accessed by
Features must be declared in ``kernel.api`` file. Kernel API file is an
XML file (see :ref:`example "Kernel API XML Schema" <fig_kf-api-xsd>` and
:ref:`table "XML elements specification" <table_kf-api-tags>`).

.. _fig_kf-api-xsd:
.. code-block:: xml
   :caption: Kernel API XML Schema

   <xs:schema xmlns:xs='http://www.w3.org/2001/XMLSchema'>
       <xs:element name='require'>
           <xs:complexType>
               <xs:choice minOccurs='0' maxOccurs='unbounded'>
                   <xs:element ref='type'/>
                   <xs:element ref='field'/>
                   <xs:element ref='method'/>
               </xs:choice>
           </xs:complexType>
       </xs:element>

       <xs:element name='type'>
           <xs:complexType>
               <xs:attribute name='name' type='xs:string' use='required'/>
           </xs:complexType>
       </xs:element>

       <xs:element name='field'>
           <xs:complexType>
               <xs:attribute name='name' type='xs:string' use='required'/>
           </xs:complexType>
       </xs:element>

       <xs:element name='method'>
           <xs:complexType>
               <xs:attribute name='name' type='xs:string' use='required'/>
           </xs:complexType>
       </xs:element>
   </xs:schema>

.. _table_kf-api-tags:
.. tabularcolumns:: |p{1cm}|p{1.5cm}|p{12.5cm}|
.. table:: XML elements specification

    +---------+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    | Tag     | Attributes | Description                                                                                                                                                                                                                                                                                                                                                                                                                     |
    +=========+============+=================================================================================================================================================================================================================================================================================================================================================================================================================================+
    | require |            | The root element                                                                                                                                                                                                                                                                                                                                                                                                                |
    +---------+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    |         |            | Static field declaration. Declaring a field as a Kernel API automatically sets the declaring type as a Kernel API                                                                                                                                                                                                                                                                                                               |
    | field   +------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    |         | name       | Fully qualified name on the form ``[type].[fieldName]``                                                                                                                                                                                                                                                                                                                                                                         |
    +---------+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    |         |            | Method or constructor declaration. Declaring a method or a constructor as a Kernel API automatically sets the declaring type as a Kernel API                                                                                                                                                                                                                                                                                    |
    | method  +------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    |         | name       | Fully qualified name on the form ``[type].[methodName]([typeArg1,...,typeArgN) typeReturned``. Types are fully qualified names or one of a base type as described by the Java language (``boolean``, ``byte``, ``char``, ``short``, ``int``, ``long``, ``float``, ``double``) When declaring a constructor, ``methodName`` is the single type name. When declaring a void method or a constructor, ``typeReturned`` is ``void`` |
    +---------+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    |         |            | Type declaration, allowed to be loaded from a Feature using ``Class.forName()``                                                                                                                                                                                                                                                                                                                                                 |
    | type    +------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    |         | name       | Fully qualified name on the form ``[package].[package].[typeName]``                                                                                                                                                                                                                                                                                                                                                             |
    +---------+------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

Access Error Codes
------------------

When an instruction is executed that will break a [KF] insulation
semantic rule, a ``java.lang.IllegalAccessError`` is thrown, with an
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


.. _kf-dyn:

Loading Features Dynamically
============================

Features may be statically embedded with the Kernel or dynamically built
against a Kernel. To build a Feature binary file, select
``Build Dynamic Feature``\ MicroEJ Platform\ ``Execution`` tab. The
generated file can be dynamically loaded by the Kernel runtime using
``ej.kf.Kernel.load(InputStream)``.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
