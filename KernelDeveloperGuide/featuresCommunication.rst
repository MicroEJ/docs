.. _chapter.communication.features:

Kernel and Features Communication
=================================

Feature and Kernel can communicate between each other in various ways such as sharing interface implementation instances at runtime.

In this section you will learn:
- How can two (or more) feature communicate with each other.
- How can the Kernel communicate with a Feature.


Shared Service
--------------

Interface implementation called Services can be Shared through the usage of the `ej.Service library <https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/ServiceFactory.html>`_.

See the associated JavaDoc to understand more about its usage.

A service can be stored in different Service Registries.

Each feature owns a local registry in which it can register and get service within its own context, services registered in a local context can't be retrieved or used by any other Feature or the Kernel.

The Kernel also has a local registry in which it can register services to be used anywhere else in the Kernel but not available to features.

Finally, A unique shared service registry contains all registered shared service, this registry is then available to all features and the Kernel.

Security policies can also be implemented to restrict the usage of certain service by certain feature.

   .. note::

      Following sections are based on the existing KF implementation of the ej.Service library available in the `KF-Util module <https://forge.microej.com/ui/native/microej-developer-repository-release/com/microej/library/util/kf-util/>`_ , you can also implement your own system depending on your needs.


Communication between Features
------------------------------

The KF specification does not allow Feature to actually use other Features object instances directly, which is why to allow a Feature to use an other feature instance, it must, first, be provided a reference (a proxy of
the other Application instance) to comply with the specificiation.

Features can then communicate together through the use of Shared Interfaces.
This mechanism is described in :ref:`chapter.shared.interfaces` section.
Basically, the Shared Interfaces mechanism is responsible for setting up the capability of
sharing an instance between features whereas the Shared Services allows to actually register and get these instances once correctly set up.


Register a Service
~~~~~~~~~~~~~~~~~~

The following line of code allows you to easily register a Service instance.

``ServiceFactory.register(MyInterface.class,myInterface)``


When registering a service from a Feature there are two possible options:

- The register service is not a Shared Interface: In this case the service instance will be registered in a local service registry and only available in the application itself.

- The register service is a Shared Interface: In this case the service instance will be registered in the Shared Service Registry and therefore available to any other features that has a proxy for this instance.

For Applications to use the Shared Interface mechanism, a Kernel must provide:

* an API for a first Application to register its Shared Interface, and for a second Application to get a proxy on it (ej.Service library)
* a set of registered Kernel types converters (see below)

schema

Get a Service
~~~~~~~~~~~~~

The following line of code allows you to easily get a Service instance.

``MyInterface myInterface = ServiceFactory.getService(MyInterface.class)``

When getting a service instance from a feature, the KF implementation tries to retrieve the service instance in the following order:

- In the Local Registry, check for an instance registered by the Feature.
- In the Shared Registry, check for an instance registered by the Feature itself.
- In the Shared Registry, check for an instance registered (publicly) by the Kernel.
- In the Shared Registry, check for an instance registered as Shared Interface by an other Feature.

If none of the above is found, it will try to create a new instance of the provided Type assuming it has been specified by the Kernel, learn more about types `here <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/classpath.html#types>`_.

   .. note::

      In a Multi-Sandbox context, the only module capable of declaring Types is the Kernel therefore a type belonging to a Feature can't be instantiated this way.
      To ensure that every type is indeed embedded, make sure that the property ``soar.generate.classnames`` is set to ``true``

.. _kernel_service_registry:

Communication between Kernel and Feature
----------------------------------------

A Kernel can also communicate with Feature using Shared Services.

The Kernel can expose instances in the Shared Registry to allow Feature to retrieve and use them.

For that, a Kernel must provide an API for Applications to register and
retrieve instances of shared interface: a KF service registry.
Such registry can be implemented using the `Kernel.bind()`_ KF API to
create a proxy for the requesting consumer Application.

.. _Kernel.bind(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#bind-T-java.lang.Class-ej.kf.Feature-

Note that this can also be used for an Application instance of a Kernel
type. In this case, a :ref:`Converter <kernel_type_converter>` must be
defined and the converted instance is returned instead of creating a
proxy.


Register a Service
~~~~~~~~~~~~~~~~~~

Unlike features, the Kernel has 2 APIs to register a Service because the KF Implementation
does not actually handles automatically in which register the service is stored depending
on if it is a Shared Interface or not as this mechanism is exclusively meant for Features.

First you can use the generic ej.Service API, this will automatically register the service instance in the **local** Kernel service registry.

``ServiceFactory.register(MyInterface.class,myInterface) //accessible within the Kernel context only``

To specify in which Registry the Kernel should register its service you can use the following code, it uses
the ServiceRegistryKF from the KF-Util module such as:

``
ServiceRegistryKF serviceRegistryKF = (ServiceRegistryKF) ServiceFactory.getServiceRegistry();
serviceRegistryKF.register(MyInterface.class,myInterface, false); //accessible by any feature
``

This way, the service instance is exposed in the Shared Registry.


.. note::
    To allow the usage of Kernel APIs by features, you must make sure that the Kernel registers the necessary Kernel APIs.
    Learn more about Kernel API `here <https://docs.microej.com/en/latest/KernelDeveloperGuide/kernelAPI.html>`_.
    The usage of extra APIs from ServiceRegistryKF to specify the registry is reserved for Kernel
    and will thrown an exception if used from a feature context.


Get a Service
~~~~~~~~~~~~~

The following line of code allows you to easily get a Service instance.

``MyInterface myInterface = ServiceFactory.getService(MyInterface.class)``

When getting a service instance from the Kernel, the KF implementation tries to retrieve the service instance in the following order:

- In the Local Registry, check for an instance registered by the Kernel.
- In the Shared Registry, check for an instance registered by the Kernel.
- In the Shared Registry, check for an instance registered as Shared Interface by an other Feature.

If none of the above is found, it will try to create a new instance of the provided Type assuming it has been specified by the Kernel, learn more about types `here <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/classpath.html#types>`_.


.. note::
    In a Multi-Sandbox context, the only module capable of declaring Types is the Kernel therefore a type belonging to a Feature can't be instantiated this way.
    To ensure that every type is indeed embedded, make sure that the property ``soar.generate.classnames`` is set to ``true``


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
