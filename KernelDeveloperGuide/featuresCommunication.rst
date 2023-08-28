.. _chapter.communication.features:

Communication between Features
==============================

Features can communicate together through the use of Shared Interfaces.
This mechanism is described in :ref:`chapter.shared.interfaces` section.

For Applications to use the Shared Interface mechanism, a Kernel must provide:

* an API for a first Application to register its Share Interface, and for a second Application to get a proxy on it
* a set of registered Kernel types converters
.. _kernel_service_registry:

Kernel Service Registry
-----------------------

Although an Application can use another Application instance of a
Shared Interface, it must, first, be provided a reference (a proxy of
the other Application instance).

For that, a Kernel must provide an API for Applications to register and
retrieve instances of shared interface: a KF service registry.
Such registry can be implemented using the `Kernel.bind()`_ KF API to
create a proxy for the requesting consumer Application.

.. _Kernel.bind(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#bind-T-java.lang.Class-ej.kf.Feature-

Note that this can also be used for an Application instance of a Kernel
type. In this case, a :ref:`Converter <kernel_type_converter>` must be
defined and the converted instance is returned instead of creating a
proxy.

An implementation of such KF service registry is provided by the
`Wadapps multisandbox implementation <https://forge.microej.com/artifactory/microej-developer-repository-release/ej/library/wadapps/wadapps-multisandbox/>`_.

.. _kernel_type_converter:

Kernel Types Converter
----------------------

The Shared Interface mechanism allows to transfer an object instance of
a Kernel type from one Feature to an other (see :ref:`section.transferable.types` section). 

To do that, the Kernel must register a new Kernel type converter.
See the `Converter`_ class and `Kernel.addConverter()`_ method for more details.

The table below shows some converters defined in the `com.microej.library.util#kf-util`_ library.

.. list-table:: Example of Available Kernel Types Converters
   :header-rows: 1

   -  - Type
      - Converter Class
      - Conversion Rule
   -  - `java.lang.Boolean <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Boolean.html>`_
      - `BooleanConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/BooleanConverter.html>`_
      - Clone by copy
   -  - `java.lang.Byte <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Byte.html>`_
      - `ByteConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/ByteConverter.html>`_
      - Clone by copy
   -  - `java.lang.Character <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Character.html>`_
      - `CharacterConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/CharacterConverter.html>`_
      - Clone by copy
   -  - `java.lang.Short <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Short.html>`_
      - `ShortConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/ShortConverter.html>`_
      - Clone by copy
   -  - `java.lang.Integer <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Integer.html>`_
      - `IntegerConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/IntegerConverter.html>`_
      - Clone by copy
   -  - `java.lang.Float <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Float.html>`_
      - `FloatConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/FloatConverter.html>`_
      - Clone by copy
   -  - `java.lang.Long <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Long.html>`_
      - `LongConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/LongConverter.html>`_
      - Clone by copy
   -  - `java.lang.Double <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Double.html>`_
      - `DoubleConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/DoubleConverter.html>`_
      - Clone by copy
   -  - `java.lang.String <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/String.html>`_
      - `StringConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/StringConverter.html>`_
      - Clone by copy
   -  - `java.io.InputStream <https://repository.microej.com/javadoc/microej_5.x/apis/java/io/InputStream.html>`_
      - `InputStreamConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/InputStreamConverter.html>`_
      - Create a Proxy reference
   -  - `java.util.Date <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Date.html>`_
      - `DateConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/DateConverter.html>`_
      - Clone by copy
   -  - `java.util.List<T> <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/List.html>`_
      - `ListConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/ListConverter.html>`_
      - Clone by copy with recursive element conversion
   -  - `java.util.Map<K,V> <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Map.html>`_
      - `MapConverter <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/MapConverter.html>`_
      - Clone by copy with recursive keys and values conversion

.. _Converter: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Converter.html
.. _Kernel.addConverter(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#addConverter-ej.kf.Converter-
.. _com.microej.library.util#kf-util: https://repository.microej.com/modules/com/microej/library/util/kf-util/

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
