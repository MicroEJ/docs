Definitions
===========

.. _kf-feature-definition:

Feature Definition Files
------------------------

A Feature is a group of types, resources and [B-ON] immutables objects
defined using two files that shall be in application classpath:

-  ``[featureName].kf``, a Java properties file. Keys are described in
   `table_title <#kf-feature-keys>`__.

-  ``[featureName].cert``, an X509 certificate file that uniquely
   identifies the Feature

.. table:: Feature definition file properties

   +-----------+-----------+-----------------------------------------------+
   | Key       | Usage     | Description                                   |
   +===========+===========+===============================================+
   | e         | Mandatory | The fully qualified name of the class that    |
   | ntryPoint |           | implements ``ej.kf.FeatureEntryPoint``        |
   +-----------+-----------+-----------------------------------------------+
   | i         | Optional  | Semicolon separated list of paths to [B-ON]   |
   | mmutables |           | immutable files owned by the Feature. [B-ON]  |
   |           |           | immutable file is defined by a ``/``          |
   |           |           | separated path relative to application        |
   |           |           | classpath                                     |
   +-----------+-----------+-----------------------------------------------+
   | resources | Optional  | Semicolon separated list of resource names    |
   |           |           | owned by the Feature. Resource name is        |
   |           |           | defined by                                    |
   |           |           | ``Class.getResourceAsStream(String)``         |
   +-----------+-----------+-----------------------------------------------+
   | requ      | Optional  | Comma separated list of fully qualified names |
   | iredTypes |           | of required types. (Types that may be         |
   |           |           | dynamically loaded using                      |
   |           |           | ``Class.forName()``).                         |
   +-----------+-----------+-----------------------------------------------+
   | types     | Optional  | Comma separated list of fully qualified names |
   |           |           | of types owned by the Feature. A wildcard is  |
   |           |           | allowed as terminal character to embed all    |
   |           |           | types starting with the given qualified name  |
   |           |           | (``a.b.C,x.y.*``)                             |
   +-----------+-----------+-----------------------------------------------+
   | version   | Mandatory | String version, that can retrieved using      |
   |           |           | ``ej.kf.Module.getVersion()``                 |
   +-----------+-----------+-----------------------------------------------+

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
XML file (see `figure_title <#kf-api-xsd>`__ and
`table_title <#kf-api-tags>`__).

::

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

.. table:: XML elements specification

   +--------+--------+-----------------------------------------------------+
   | Tag    | Attr   | Description                                         |
   |        | ibutes |                                                     |
   +========+========+=====================================================+
   | r      |        | The root element                                    |
   | equire |        |                                                     |
   +--------+--------+-----------------------------------------------------+
   | field  |        | Static field declaration. Declaring a field as a    |
   |        |        | Kernel API automatically sets the declaring type as |
   |        |        | a Kernel API                                        |
   +--------+--------+-----------------------------------------------------+
   | name   | Fully  |                                                     |
   |        | qua    |                                                     |
   |        | lified |                                                     |
   |        | name   |                                                     |
   |        | on the |                                                     |
   |        | form   |                                                     |
   |        | ``[t   |                                                     |
   |        | ype].[ |                                                     |
   |        | fieldN |                                                     |
   |        | ame]`` |                                                     |
   +--------+--------+-----------------------------------------------------+
   | method |        | Method or constructor declaration. Declaring a      |
   |        |        | method or a constructor as a Kernel API             |
   |        |        | automatically sets the declaring type as a Kernel   |
   |        |        | API                                                 |
   +--------+--------+-----------------------------------------------------+
   | name   | Fully  |                                                     |
   |        | qua    |                                                     |
   |        | lified |                                                     |
   |        | name   |                                                     |
   |        | on the |                                                     |
   |        | form   |                                                     |
   |        | ``[typ |                                                     |
   |        | e].[me |                                                     |
   |        | thodNa |                                                     |
   |        | me]([t |                                                     |
   |        | ypeArg |                                                     |
   |        | 1,..., |                                                     |
   |        | typeAr |                                                     |
   |        | gN)typ |                                                     |
   |        | eRetur |                                                     |
   |        | ned``. |                                                     |
   |        | Types  |                                                     |
   |        | are    |                                                     |
   |        | fully  |                                                     |
   |        | qua    |                                                     |
   |        | lified |                                                     |
   |        | names  |                                                     |
   |        | or one |                                                     |
   |        | of a   |                                                     |
   |        | base   |                                                     |
   |        | type   |                                                     |
   |        | as     |                                                     |
   |        | des    |                                                     |
   |        | cribed |                                                     |
   |        | by the |                                                     |
   |        | Java   |                                                     |
   |        | la     |                                                     |
   |        | nguage |                                                     |
   |        | (      |                                                     |
   |        | ``bool |                                                     |
   |        | ean``, |                                                     |
   |        | ``b    |                                                     |
   |        | yte``, |                                                     |
   |        | ``c    |                                                     |
   |        | har``, |                                                     |
   |        | ``sh   |                                                     |
   |        | ort``, |                                                     |
   |        | ``     |                                                     |
   |        | int``, |                                                     |
   |        | ``l    |                                                     |
   |        | ong``, |                                                     |
   |        | ``fl   |                                                     |
   |        | oat``, |                                                     |
   |        | ``dou  |                                                     |
   |        | ble``) |                                                     |
   |        | When   |                                                     |
   |        | dec    |                                                     |
   |        | laring |                                                     |
   |        | a      |                                                     |
   |        | constr |                                                     |
   |        | uctor, |                                                     |
   |        | ``     |                                                     |
   |        | method |                                                     |
   |        | Name`` |                                                     |
   |        | is the |                                                     |
   |        | single |                                                     |
   |        | type   |                                                     |
   |        | name.  |                                                     |
   |        | When   |                                                     |
   |        | dec    |                                                     |
   |        | laring |                                                     |
   |        | a void |                                                     |
   |        | method |                                                     |
   |        | or a   |                                                     |
   |        | constr |                                                     |
   |        | uctor, |                                                     |
   |        | ``ty   |                                                     |
   |        | peRetu |                                                     |
   |        | rned`` |                                                     |
   |        | is     |                                                     |
   |        | ``     |                                                     |
   |        | void`` |                                                     |
   +--------+--------+-----------------------------------------------------+
   | type   |        | Type declaration, allowed to be loaded from a       |
   |        |        | Feature using ``Class.forName()``                   |
   +--------+--------+-----------------------------------------------------+
   | name   | Fully  |                                                     |
   |        | qua    |                                                     |
   |        | lified |                                                     |
   |        | name   |                                                     |
   |        | on the |                                                     |
   |        | form   |                                                     |
   |        | ``[p   |                                                     |
   |        | ackage |                                                     |
   |        | ].[pac |                                                     |
   |        | kage]. |                                                     |
   |        | [typeN |                                                     |
   |        | ame]`` |                                                     |
   +--------+--------+-----------------------------------------------------+

Access Error Codes
------------------

When an instruction is executed that will break a [KF] insulation
semantic rule, a ``java.lang.IllegalAccessError`` is thrown, with an
error code composed of two parts: ``[source][errorKind]``.

-  ``source``: a single character indicating the kind of Java element on
   which the access error occurred
   (`table_title <#kf-errorcodes-source>`__)

-  ``errorKind``: an error number indicating the action on which the
   access error occurred (`table_title <#kf-errorcodes-kind>`__)

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
