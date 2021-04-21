Communication between Features
==============================

Features can communicate together through the use of shared interfaces.
The mechanism is described in *Chapter Shared Interfaces* of the
Application Developer's Guide.

Kernel Type Converters
----------------------

The shared interface mechanism allows to transfer an object instance of
a Kernel type from one Feature to an other. To do that, the Kernel must
register a new converter (See ``Kernel.addConverter()`` method).

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
