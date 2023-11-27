.. _chapter.communication.features:

Kernel and Features Communication
=================================

Kernel and Features can communicate with each other by sharing interface implementation instances at runtime.

In this section you will learn:

* How two (or more) Feature(s) can communicate with each other.
* How the Kernel can communicate with a Feature.

Below are defined several terms that will be used throughout this page:

- :ref:`Shared Interface <chapter.shared.interfaces>` is a mechanism specific to MicroEJ Multi-Sandbox that allows exchanging object instances between Features.
- Service represents an object instance (i.e an interface implementation)
- `Shared Services <https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/package-summary.html>`_ is a MicroEJ helper module that eases sharing services within a Multi-Sandbox context; it provides generic APIs that can be re-implemented as needed.
- Registry or Service Registry represents the actual implementation of Shared Services APIs. MicroEJ provides such registries for KF but custom registries can be implemented as needed.

Shared Services
---------------

Services can be shared by means of the `ej.Service library <https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/package-summary.html>`_.

The Shared Services mechanism relies on a registry system that mostly consists in a Java map of class types to object instances (``Map<Class<?>, Object>``).

Each Feature owns a local registry in which it can register and get services within its own context; services registered in a local context cannot be retrieved by the Kernel nor any other Feature.

The Kernel also has a local registry in which it can register services that can be used within its own context but not from the context of Features.

Finally there exists a unique shared service registry contains all the registered shared services; this registry is available to all Features and to the Kernel as well.

Security policies can be implemented to restrict the usage of certain services by certain Features.

.. note::

   The following sections relate to the existing `KF implementation <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/service/ServiceRegistryKF.html>`_ of the `ej.Service library <https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/package-summary.html>`_ available in the `KF-Util module <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/package-summary.html>`_ ; you can however do your own custom implementation depending as needed.

Communication between Features
------------------------------

The KF specification does not allow Features to access object instances from other Features directly: access can only be done by means of a proxy of the target object instance.

This is made possible through the Shared Interfaces mechanism.
More information about proxies can be found in the :ref:`chapter.shared.interfaces` section.

In a nutshell Shared Interfaces and Shared Services are two complementary notions: the Shared Interfaces mechanism is responsible for setting up the capability of sharing an instance between Features whereas Shared Services offer a way to get, store and retrieve these instances once correctly set up.

Register a Service
~~~~~~~~~~~~~~~~~~

The following line of code allows you to easily register a Service instance.

.. code-block:: java

   ServiceFactory.register(MyInterface.class,myInterface)

When registering a service from a Feature there are two possible options:

- The registered service is not a Shared Interface; in this case the service instance will be registered in a local service registry and only available from the Feature itself.

- The registered service is a Shared Interface; in this case the service instance will be registered in the Shared Service Registry and therefore available to any other Features that has a proxy for this instance.

For Features to use the Shared Interfaces mechanism, a Kernel must provide:

* an API for a first Feature to register its Shared Interface, and for a second Feature to get a proxy on it (by means of the `ej.Service library <https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/package-summary.html>`_)
* a set of registered Kernel types converters (see below)

Get a Service
~~~~~~~~~~~~~

The following line of code allows you to easily get a Service instance.

.. code-block:: java

   MyInterface myInterface = ServiceFactory.getService(MyInterface.class)

When getting a service instance from a Feature, the service instance is searched in the following order:

#. In the Local Registry, check for an instance registered by the Feature.
#. In the Shared Registry, check for an instance registered by the Feature itself.
#. In the Shared Registry, check for an instance registered (publicly) by the Kernel.
#. In the Shared Registry, check for an instance registered as a Shared Interface by an other Feature.

If no instance was found, an attempt is made to create a new one of the provided type, assuming the type is embedded in the Kernel.
By default only types referenced directly in the code are embedded in the Kernel. Non-referenced types may be declared as `Required Types <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/classpath.html#types>`_ to be embedded in the Kernel.

.. note::

   In a Multi-Sandbox context, the only module capable of declaring types is the Kernel therefore a type belonging to a Feature cannot be instantiated this way.
   An alternative way to embed type names not referenced by the Kernel is to set property `soar.generate.classnames <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/applicationOptions.html#group-types>`_.
   Note that it can have an impact on the footprint of the Kernel as all types will be embedded.

.. _kernel_service_registry:

Communication between Kernel and Feature
----------------------------------------

The Kernel can also communicate with Features using Shared Services, by exposing object instances to Features in the shared registry.

Register a Service
~~~~~~~~~~~~~~~~~~

From the Kernel side two distinct APIs may be used to register a Service, depending on whether the service must be registered locally or not.

You can use the generic `ej.Service API <https://repository.microej.com/javadoc/microej_5.x/apis/ej/service/package-summary.html>`_ that will automatically register the service instance in the **local** Kernel service registry.

.. code-block:: java

   ServiceFactory.register(MyInterface.class,myInterface) //accessible within the Kernel context only

Or you can specify in which registry the Kernel should register the service by using the `ServiceRegistryKF <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/service/ServiceRegistryKF.html>` API from the `KF-Util module <https://repository.microej.com/javadoc/microej_5.x/apis/com/microej/kf/util/package-summary.html>`_ as depicted below.

.. ::
    ServiceRegistryKF serviceRegistryKF = (ServiceRegistryKF) ServiceFactory.getServiceRegistry();
    serviceRegistryKF.register(MyInterface.class,myInterface, false); //accessible by any feature


By doing so the service instance is exposed in the Shared Registry.

.. note::

   To allow the usage of Kernel APIs by Features, you must make sure that the Kernel registers the necessary Kernel APIs.
   Learn more about `Kernel API <https://docs.microej.com/en/latest/KernelDeveloperGuide/kernelAPI.html>`_.
   Use of extra APIs from ServiceRegistryKF to specify the registry is reserved for the Kernel
   and will throw an exception if used from a Feature context.

Get a Service
~~~~~~~~~~~~~

The following line of code allows you to easily get a Service instance.

.. code-block:: java

   MyInterface myInterface = ServiceFactory.getService(MyInterface.class)

When getting a service instance from the Kernel, the service instance is searched in the following order:

#. In the Local Registry, check for an instance registered by the Kernel.
#. In the Shared Registry, check for an instance registered by the Kernel.
#. In the Shared Registry, check for an instance registered as Shared Interface by an other Feature.

If no instance was found, an attempt is made to create a new one of the provided type, assuming the type is embedded in the Kernel.
By default only types referenced directly in the code are embedded in the Kernel. Non-referenced types may be declared as `Required Types <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/classpath.html#types>`_ to be embedded in the Kernel.

.. note::

   In a Multi-Sandbox context, the only module capable of declaring types is the Kernel therefore a type belonging to a Feature cannot be instantiated this way.
   An alternative way to embed type names not referenced by the Kernel is to set property `soar.generate.classnames <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/applicationOptions.html#group-types>`_.
   Note that it can have an impact on the footprint of the Kernel as all types will be embedded.

Implement a Registry
--------------------

In case the existing KF implementation of Shared Services does not fit your needs, you can implement your own registry system classes using the `Kernel.bind()`_ KF API.

This API allows a consumer Feature for remote use of an instance which type is owned by another Feature or the Kernel. In case the type is owned by another Feature, the returned instance is a `Proxy <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Proxy.html>`_ of the shared instance. In case the type is owned by the Kernel, the returned instance is the conversion result of the shared instance to the Kernel type; for this to happen a suitable :ref:`Converter <kernel_type_converter>` must be registered.

As an example the steps below describe how to implement a generic Shared Interface service that relies on the `Kernel.bind()`_ API.

#. Declare the following class in your Kernel

.. code-block:: java

   package com.microej.example;

   import ej.kf.Feature;
   import ej.kf.Feature.State;
   import ej.kf.FeatureStateListener;
   import ej.kf.Kernel;
   import ej.kf.Module;

   /**
   * Example of Kernel APIs for registering a generic Shared Interface service.
   */
   public class GlobalService {

      private static Object GLOBAL_SERVICE;
      static {
         // automatically unregister the global service when the Feature is stopped.
         Kernel.addFeatureStateListener(new FeatureStateListener() {

            @Override
            public void stateChanged(Feature feature, State previousState) {
               synchronized (GlobalService.class) {
                  if (GLOBAL_SERVICE != null && Kernel.getOwner(GLOBAL_SERVICE) == feature
                        && previousState == State.STARTED) {
                     GLOBAL_SERVICE = null;
                  }
               }
            }
         });
      }

      /**
      * Basic API to register a Feature service. <br>
      * The service is automatically unregistered when the Feature is stopped.
      *
      * @param service
      *            the service being registered. It must implement a shared interface.
      */
      public synchronized static void registerService(Object service) {
         Kernel.enter();
         GLOBAL_SERVICE = service;
      }

      /**
      * Basic API to retrieve a Feature service. <br>
      *
      * @param <T>
      *            the interface type
      *
      * @param serviceClass
      *            the interface of the service being retrieved. It must implement a shared interface.
      * @return the binded service or <code>null</code> if no registered service
      */
      @SuppressWarnings("unchecked")
      public synchronized static <T> T getService(Class<T> serviceClass) {
         Module contextOwner = Kernel.getContextOwner();
         Kernel.enter();
         if (GLOBAL_SERVICE == null) {
            return null;
         }
         return Kernel.bind((T) GLOBAL_SERVICE, serviceClass, (Feature) contextOwner);
      }
   }

#. Declare the following exposed APIs in your ``kernel.api`` file (refer to `Kernel API Definition <https://docs.microej.com/en/latest/KernelDeveloperGuide/kernelAPI.html#kernel-api-definition>`_ for details)

.. code-block:: xml

   <method name="com.microej.example.GlobalService.registerService(java.lang.Object)void" />
   <method name="com.microej.example.GlobalService.getService(java.lang.Class)java.lang.Object" />

#. Your App1 is ready to register a Shared Interface as a service

.. code-block:: java

   MySharedInterface service = new MySharedInterface();
   GlobalService.registerService(service);

#. Your App2 is ready to retrieve a Shared Interface as a service

.. code-block:: java

   MySharedInterface service = GlobalService.getService(MySharedInterface.class))
   service.use();

.. _Kernel.bind(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#bind-T-java.lang.Class-ej.kf.Feature-

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
