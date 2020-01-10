Principle
=========

SNI provides a simple mechanism for implementing native Java methods in
the C language.

SNI allows you to:

-  Call a C function from a Java method.

-  Access an Immortal array in a C function (see the [B-ON]
   specification to learn about immortal objects).

SNI does not allow you to:

-  Access or create a Java object in a C function.

-  Access Java static variables in a C function.

-  Call Java methods from a C function.

SNI provides some Java APIs to manipulate some data arrays between Java
and the native (C) world.
