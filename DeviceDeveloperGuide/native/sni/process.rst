Functional Description
======================

SNI defines how to cross the barrier between the Java world and the
native world:

-  Call a C function from Java.

-  Pass parameters to the C function.

-  Return a value from the C world to the Java world.

-  Manipulate (read & write) shared memory both in Java and C : the
   immortal space.

.. figure:: native/sni/images/sni_flow.svg
   :alt: SNI Processing
   :width: 60.0%

   SNI Processing

`figure_title <#sni_flow>`__ illustration shows both Java and C code
accesses to shared objects in the immortal space, while also accessing
their respective memory.
