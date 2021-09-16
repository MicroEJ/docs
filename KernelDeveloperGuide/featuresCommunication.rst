Communication between Features
==============================

Features can communicate together through the use of shared interfaces.
This mechanism is described in :ref:`chapter.shared.interfaces` section.

The shared interface mechanism allows to transfer an object instance of
a Kernel type from one Feature to an other. To do that, the Kernel must
register a new Kernel type converter.

See the `Converter <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Converter.html>`_ class and `Kernel.addConverter() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#addConverter-ej.kf.Converter->`_ method for more details.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
