SOAR
====

.. _soar_clinit:

Class Initialization Code
-------------------------

SOAR complies with the deterministic class initialization (``<clinit>``)
order specified in :ref:`[BON] <esr-specifications>`. The application is statically analyzed from
its entry points in order to generate a clinit dependency graph. The
computed clinit sequence is the result of the topological sort of the
dependency graph. An error is thrown if the clinit dependency graph
contains cycles.

A clinit map file (ending with extension ``.clinitmap``) is generated
beside the SOAR object file. It describes for each clinit dependency:

-  the types involved

-  the kind of dependency

-  the stack calls between the two types

.. _soar_clinit_explicit_dependencies:

In case of complex clinit code with too many runtime dependencies, the statically computed clinit order may be wrong.

It is then possible to help SOAR by manually declaring explicit clinit dependencies.
Such dependencies are declared in XML files with the ``.clinitdesc`` extension in the application classpath. 

The file has the following format:

::

   <?xml version='1.0' encoding='UTF-8'?>
   <clinit>
       <type name="T1" depends="T2"/>
   </clinit>

where ``T1`` and ``T2`` are fully qualified names on the form ``a.b.C``.
This explicitly forces SOAR to create a dependency from ``T1`` to
``T2``, and therefore cuts a potentially detected dependency from ``T2``
to ``T1``.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
