SOAR
====

This chapter describes SOAR capabilities and optimizations from the Application developer's point of view.
To get more details on its internal structure, please refer to :ref:`soar_build_phases` section.

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


.. _soar_method_devirtualization:

Method Devirtualization
------------------------

Method devirtualization consists of transforming a virtual method call to a direct method call when possible.
A virtual method call is a call to a non-private instance method declared either in an interface or in a class. 
The Core Engine determines the proper method to call at runtime depending on the actual class of the object. 
A call to a constructor or a private method is already optimized as a direct method call by the Java compiler.

SOAR automatically optimizes a virtual method call to a direct method call if there is one and only one embedded implementation method.

.. note::
  
   SOAR generates the list of the embedded methods in the :ref:`SOAR Information File <soar_info_file>`.

.. _soar_method_inlining:

Method Inlining
---------------

Method inlining consists of replacing a direct method call with the content of the method. This avoids the creation of a new stack frame context, which can be slower than executing the code itself.
Method inlining is transitively applied from leaf to root methods.

The following method code patterns are inlined:

- empty code after processing :ref:`assertions <enable_assertions_emb>` and :ref:`if code removal <if_constant_removal>`.
- call to a constructor with no parameters.
- call to a private method with no parameters.
- call to a static method with no parameters, if and only if the caller is also a static method.

.. note::

   Method inlining is performed after :ref:`method devirtualization <soar_method_devirtualization>`, so a virtual method call will be inlined 
   if there is a unique embedded implementation method that matches one of the inlined method code patterns.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
