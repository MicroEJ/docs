Smart Linker (SOAR)
===================

Java source code is compiled by the Java compiler [1]_ into the binary
format specified in [JVM]. This binary code needs to be linked before
execution. The MicroEJ Platform comes with a linker, named the SOAR. It
is in charge of analyzing ``.class`` files, and some other
application-related files, to produce the final application that the
MicroEJ Platform runtime can execute.

SOAR complies with the deterministic class initialization (``<clinit>``)
order specified in [B-ON]. The application is statically analyzed from
its entry points in order to generate a clinit dependency graph. The
computed clinit sequence is the result of the topological sort of the
dependency graph. An error is thrown if the clinit dependency graph
contains cycles.

An explicit clinit dependency can be declared by creating an XML file
with the ``.clinitdesc`` extension in the application classpath. The
file has the following format:

::

   <?xml version='1.0' encoding='UTF-8'?>
   <clinit>
       <type name="T1" depends="T2"/>
   </clinit>

where ``T1`` and ``T2`` are fully qualified names on the form ``a.b.C``.
This explicitly forces SOAR to create a dependency from ``T1`` to
``T2``, and therefore cuts a potentially detected dependency from ``T2``
to ``T1``.

A clinit map file (ending with extension ``.clinitmap``) is generated
beside the SOAR object file. It describes for each clinit dependency:

-  the types involved

-  the kind of dependency

-  the stack calls between the two types

.. [1]
   The JDT compiler from the Eclipse IDE.
