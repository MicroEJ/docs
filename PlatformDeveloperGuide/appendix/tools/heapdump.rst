Heap Dumping
============

XML Schema
----------

Below is the XML schema for heap dumps.

.. table:: XML Schema for Heap Dumps
   :class: longtable

   +---------------------------------------------------------------------------------------------+
   | ::                                                                                          |
   |                                                                                             |
   |    <?xml version='1.0' encoding='UTF-8'?>                                                   |
   |    <!--                                                                                     |
   |        Schema                                                                               |
   |                                                                                             |
   |        Copyright 2012 IS2T. All rights reserved.                                            |
   |                                                                                             |
   |       IS2T PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.                       |
   |    -->                                                                                      |
   |                                                                                             |
   |    <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">                                  |
   |        <!-- root element : heap -->                                                         |
   |        <xs:element name="heap">                                                             |
   |            <xs:complexType>                                                                 |
   |                <xs:choice minOccurs="0" maxOccurs="unbounded">                              |
   |                    <xs:element ref="class"/>                                                |
   |                    <xs:element ref="object"/>                                               |
   |                    <xs:element ref="array"/>                                                |
   |                    <xs:element ref="stringLiteral"/>                                        |
   |                </xs:choice>                                                                 |
   |            </xs:complexType>                                                                |
   |        </xs:element>                                                                        |
   +---------------------------------------------------------------------------------------------+
   | ::                                                                                          |
   |                                                                                             |
   |        <!-- class element -->                                                               |
   |        <xs:element name="class">                                                            |
   |            <xs:complexType>                                                                 |
   |                <xs:choice minOccurs="0" maxOccurs="unbounded">                              |
   |                    <xs:element ref="field"/>                                                |
   |                </xs:choice>                                                                 |
   |                <xs:attribute name="name" type="xs:string" use = "required"/>                |
   |                <xs:attribute name="id" type="xs:string" use = "required"/>                  |
   |                <xs:attribute name="superclass" type="xs:string"/>                           |
   |            </xs:complexType>                                                                |
   |        </xs:element>                                                                        |
   +---------------------------------------------------------------------------------------------+
   | ::                                                                                          |
   |                                                                                             |
   |        <!-- object element-->                                                               |
   |        <xs:element name="object">                                                           |
   |            <xs:complexType>                                                                 |
   |                <xs:choice minOccurs="0" maxOccurs="unbounded">                              |
   |                    <xs:element ref="field"/>                                                |
   |                </xs:choice>                                                                 |
   |                <xs:attribute name="id" type="xs:string" use = "required"/>                  |
   |                <xs:attribute name="class" type="xs:string" use = "required"/>               |
   |                <xs:attribute name="createdAt" type="xs:string" use = "optional"/>           |
   |                <xs:attribute name="createdInThread" type="xs:string" use = "optional"/>     |
   |                <xs:attribute name="createdInMethod" type="xs:string"/>                      |
   |                <xs:attribute name="tag" type="xs:string" use = "required"/>                 |
   |            </xs:complexType>                                                                |
   |        </xs:element>                                                                        |
   +---------------------------------------------------------------------------------------------+
   | ::                                                                                          |
   |                                                                                             |
   |        <!-- array element-->                                                                |
   |        <xs:element name="array" type = "arrayTypeWithAttribute"/>                           |
   |        <!-- stringLiteral element-->                                                        |
   |        <xs:element name="stringLiteral">                                                    |
   |            <xs:complexType>                                                                 |
   |                <xs:sequence>                                                                |
   |                    <xs:element minOccurs ="4" maxOccurs="4" ref="field "/>                  |
   |                </xs:sequence>                                                               |
   |                <xs:attribute name="id" type="xs:string" use = "required"/>                  |
   |                <xs:attribute name="class" type="xs:string" use = "required"/>               |
   |            </xs:complexType>                                                                |
   |        </xs:element>                                                                        |
   +---------------------------------------------------------------------------------------------+
   | ::                                                                                          |
   |                                                                                             |
   |                                                                                             |
   |     <!-- field element :  child of class, object and stringLiteral-->                       |
   |        <xs:element name="field">                                                            |
   |            <xs:complexType>                                                                 |
   |                <xs:attribute name="name" type="xs:string" use = "required"/>                |
   |                <xs:attribute name="id" type="xs:string" use = "optional"/>                  |
   |                <xs:attribute name="value" type="xs:string" use = "optional"/>               |
   |                <xs:attribute name="type" type="xs:string" use = "optional"/>                |
   |            </xs:complexType>                                                                |
   |        </xs:element>                                                                        |
   |                                                                                             |
   |        <xs:simpleType name = "arrayType">                                                   |
   |            <xs:list itemType="xs:integer"/>                                                 |
   |        </xs:simpleType>                                                                     |
   |                                                                                             |
   |                                                                                             |
   |                                                                                             |
   |  <!-- complex type "arrayTypeWithAttribute". type of array element-->                       |
   |        <xs:complexType name = "arrayTypeWithAttribute">                                     |
   |            <xs:simpleContent>                                                               |
   |                <xs:extension base="arrayType">                                              |
   |                    <xs:attribute name="id" type="xs:string" use = "required"/>              |
   |                    <xs:attribute name="class" type="xs:string" use = "required"/>           |
   |                    <xs:attribute name="createdAt" type="xs:string" use = "optional"/>       |
   |                    <xs:attribute name="createdInThread" type="xs:string" use = "optional"/> |
   |                    <xs:attribute name="createdInMethod" type="xs:string" use = "optional"/> |
   |                    <xs:attribute name="length" type="xs:string" use = "required"/>          |
   |                    <xs:attribute name="elementsType" type="xs:string" use = "optional"/>    |
   |                    <xs:attribute name="type" type="xs:string" use = "optional"/>            |
   |                </xs:extension>                                                              |
   |            </xs:simpleContent>                                                              |
   |        </xs:complexType>                                                                    |
   |                                                                                             |
   |    </xs:schema>                                                                             |
   +---------------------------------------------------------------------------------------------+

File Specification
------------------

Types referenced in heap dumps are represented in the internal classfile
format (:ref:`intClassfileFormat`). Fully qualified names
are names separated by the / separator (For example, ``a/b/C``).

.. _intClassFileFormat:
.. code-block::
   :caption: Internal classfile Format for Types

   Type = <BaseType> | <ClassType> | <ArrayType>
   BaseType: B(byte), C(char), D(double), F(float), I(int), J(long), S(short), Z(boolean), 
   ClassType: L<ClassName>;
   ArrayType: [<Type>

Tags used in the heap dumps are described in the table below.

.. table:: Tag Descriptions

   +-------------------+------------------+------------------------------------------------------------+
   | Tags              | Attributes       | Description                                                |
   +-------------------+------------------+------------------------------------------------------------+
   | ``heap``          |                  | The root element.                                          |
   +-------------------+------------------+------------------------------------------------------------+
   |                   |                  | Element that references a Java class.                      |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``name``         | Class type (``<ClassType>``)                               |
   | ``class``         +------------------+------------------------------------------------------------+
   |                   | ``id``           | Unique identifier of the class.                            |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``superclass``   | Identifier of the superclass of this class.                |
   +-------------------+------------------+------------------------------------------------------------+
   |                   |                  | Element that references a Java object.                     |
   |                   +------------------+------------------------------------------------------------+
   | ``object``        | ``id``           | Unique identifier of this object.                          |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``class``        | Fully qualified name of the class of this object.          |
   +-------------------+------------------+------------------------------------------------------------+
   |                   |                  | Element that references a Java array.                      |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``id``           | Unique identifier of this array.                           |
   |                   +------------------+------------------------------------------------------------+
   | ``array``         | ``class``        | Fully qualified name of the class of this array.           |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``elementsType`` | Type of the elements of this array.                        |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``length``       | Array length.                                              |
   +-------------------+------------------+------------------------------------------------------------+
   |                   |                  | Element that references a ``java.lang.String`` literal.    |
   |                   +------------------+------------------------------------------------------------+
   | ``stringLiteral`` | ``id``           | Unique identifier of this object.                          |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``class``        | Id of ``java.lang.String`` class.                          |
   +-------------------+------------------+------------------------------------------------------------+
   |                   |                  | Element that references the field of an object or a class. |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``name``         | Name of this field.                                        |
   |                   +------------------+------------------------------------------------------------+
   | ``field``         | ``id``           | Object or Array identifier, if it holds a reference.       |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``type``         | Type of this field, if it holds a base type.               |
   |                   +------------------+------------------------------------------------------------+
   |                   | ``value``        | Value of this field, if it holds a base type.              |
   +-------------------+------------------+------------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
