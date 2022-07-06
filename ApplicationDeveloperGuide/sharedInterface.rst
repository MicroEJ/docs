.. _chapter.shared.interfaces:

Shared Interfaces
=================

.. _section.shared.interfaces.contract:

Principle
---------

The Shared Interface mechanism provided by MicroEJ Core Engine is an
object communication bus based on plain Java interfaces where method
calls are allowed to cross MicroEJ Sandboxed Applications boundaries.
The Shared Interface mechanism is the cornerstone for designing reliable
Service Oriented Architectures on top of MicroEJ. Communication is based
on the sharing of interfaces defining APIs (Contract Oriented
Programming).

The basic schema:

-  A provider application publishes an implementation for a shared
   interface into a system registry.

-  A user application retrieves the implementation from the system
   registry and directly calls the methods defined by the shared
   interface.

.. figure:: images/SI_1.png
   :alt: Shared Interface Call Mechanism
   :align: center
   :scale: 75%

   Shared Interface Call Mechanism

.. _section.shared.interfaces.element:

Shared Interface Creation
-------------------------

Creation of a Shared Interface follows three steps:

-  Interface definition,

-  Proxy implementation,

-  Interface registration.

Interface Definition
~~~~~~~~~~~~~~~~~~~~

The definition of a Shared Interface starts by defining a standard Java
interface.

.. code:: java

   package mypackage;
   public interface MyInterface{ 
       void foo();
   }

To declare an interface as a Shared Interface, it must be registered in
a Shared Interfaces identification file. A Shared Interface
identification file is an XML file with the ``.si`` suffix with the
following format:

::

   <sharedInterfaces>
       <sharedInterface name="mypackage.MyInterface"/>
   </sharedInterfaces>

Shared Interface identification files must be placed at the root of a
path of the application classpath. For a MicroEJ Sandboxed Application
project, it is typically placed in ``src/main/resources`` folder.

Some restrictions apply to Shared Interfaces compared to standard java
interfaces:

-  Types for parameters and return values must be transferable types;

-  Thrown exceptions must be classes owned by the MicroEJ Firmware.

.. _section.transferable.types:

Transferable Types
~~~~~~~~~~~~~~~~~~

In the process of a cross-application method call, parameters and return
value of methods declared in a Shared Interface must be transferred back
and forth between application boundaries.

.. figure:: images/SI_3.png
   :alt: Shared Interface Parameters Transfer
   :align: center
   :scale: 75%

   Shared Interface Parameters Transfer

:ref:`table.si.transfer.rules` describes the rules applied depending on the
element to be transferred.

.. _table.si.transfer.rules:

.. list-table:: Shared Interface Types Transfer Rules
   :widths: 19 14 10 29
   :header-rows: 1

   - 

      - Type
      - Owner
      - Instance Owner
      - Rule

   - 

      - Base type
      - N/A
      - N/A
      - Passing by value. (``boolean``, ``byte``, ``short``, ``char``,
        ``int``, ``long``, ``double``, ``float``)

   - 

      - Any Class, Array or Interface
      - Kernel
      - Kernel
      - Passing by reference

   - 

      - Any Class, Array or Interface
      - Kernel
      - Application
      - Kernel specific or forbidden

   - 

      - Array of base types
      - Any
      - Application
      - Clone by copy

   - 

      - Arrays of references
      - Any
      - Application
      - Clone and transfer rules applied again on each element

   - 

      - Shared Interface
      - Application
      - Application
      - Passing by indirect reference (Proxy creation)

   - 

      - Any Class, Array or Interface
      - Application
      - Application
      - Forbidden

Objects created by a Sandboxed Application which type is owned by the Kernel 
can be transferred to another Sandboxed Application provided this has been authorized by the Kernel. 
The list of Kernel types that can be transferred is Kernel specific, so you have to consult your Kernel specification.
When an argument transfer is forbidden, the call is abruptly stopped and a `java.lang.IllegalAccessError`_ is thrown by the :ref:`Core Engine <core_engine>`.

.. _java.lang.IllegalAccessError: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalAccessError.html

.. note::

   For these types to be transferable, a dedicated :ref:`Kernel Type Converter <kernel_type_converter>` must have been registered in
   the Kernel.

The table below lists typical Kernel types allowed to be transferred through a Shared Interface
call on Evaluation Firmware distributed by MicroEJ Corp.

.. list-table:: MicroEJ Evaluation Firmware Example of Transfer Types
   :header-rows: 1

   -  - Type
      - Rule
   -  - `java.lang.Boolean <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Boolean.html>`_
      - Clone by copy
   -  - `java.lang.Byte <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Byte.html>`_
      - Clone by copy
   -  - `java.lang.Character <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Character.html>`_
      - Clone by copy
   -  - `java.lang.Short <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Short.html>`_
      - Clone by copy
   -  - `java.lang.Integer <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Integer.html>`_
      - Clone by copy
   -  - `java.lang.Float <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Float.html>`_
      - Clone by copy
   -  - `java.lang.Long <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Long.html>`_
      - Clone by copy
   -  - `java.lang.Double <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Double.html>`_
      - Clone by copy
   -  - `java.lang.String <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html>`_
      - Clone by copy
   -  - `java.io.InputStream <https://repository.microej.com/javadoc/microej_5.x/apis/java/io/InputStream.html>`_
      - Create a Proxy reference
   -  - `java.util.Date <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Date.html>`_
      - Clone by copy
   -  - `java.util.List<T> <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/List.html>`_
      - Clone by copy with recursive element conversion
   -  - `java.util.Map<K,V> <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Map.html>`_
      - Clone by copy with recursive keys and values conversion

.. _section.proxy.implementation:

Proxy Class Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~

The Shared Interface mechanism is based on automatic proxy objects
created by the underlying MicroEJ Core Engine, so that each application
can still be dynamically stopped and uninstalled. This offers a reliable
way for users and providers to handle the relationship in case of a
broken link.

Once a Java interface has been declared as Shared Interface, a dedicated
implementation is required (called the Proxy class implementation). Its
main goal is to perform the remote invocation and provide a reliable
implementation regarding the interface contract even if the remote
application fails to fulfill its contract (unexpected exceptions,
application killed...). The MicroEJ Core Engine will allocate instances
of this class when an implementation owned by another application is
being transferred to this application.

.. figure:: images/SI_4.png
   :alt: Shared Interfaces Proxy Overview
   :align: center
   :scale: 75%

   Shared Interfaces Proxy Overview

A proxy class is implemented and executed on the client side, each
method of the implemented interface must be defined according to the
following pattern:

.. code:: java

   package mypackage;

   public class MyInterfaceProxy extends Proxy<MyInterface> implements MyInterface {

       @Override
       public void foo(){
           try {
               invoke(); // perform remote invocation
           } catch (Throwable e) {
               e.printStackTrace();
           }
       }
   }

Each implemented method of the proxy class is responsible for performing
the remote call and catching all errors from the server side and to
provide an appropriate answer to the client application call according
to the interface method specification (contract). Remote invocation
methods are defined in the super class `ej.kf.Proxy`_ and are named
``invokeXXX()`` where ``XXX`` is the kind of return type. As this class
is part of the application, the application developer has the full
control on the Proxy implementation and is free to insert additional
code such as logging calls and errors for example.

.. _ej.kf.Proxy: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html

.. list-table:: Proxy Remote Invocation Built-in Methods
   :widths: 31 41
   :header-rows: 1

   - 

      - Invocation Method
      - Usage

   - 

      - void `invoke()`_
      - Remote invocation for a proxy method that returns void

   - 

      - Object `invokeRef()`_
      - Remote invocation for a proxy method that returns a reference

   - 

      - boolean `invokeBoolean()`_, byte `invokeByte()`_, char `invokeChar()`_,
        short `invokeShort()`_, int `invokeInt()`_, long `invokeLong()`_, double
        `invokeDouble()`_, float `invokeFloat()`_
      - Remote invocation for a proxy method that returns a base type

.. _invoke(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invoke--
.. _invokeRef(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeRef--
.. _invokeBoolean(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeBoolean--
.. _invokeByte(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeByte--
.. _invokeChar(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeChar--
.. _invokeShort(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeShort--
.. _invokeInt(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeInt--
.. _invokeLong(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeLong--
.. _invokeDouble(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeDouble--
.. _invokeFloat(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html#invokeFloat--

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
