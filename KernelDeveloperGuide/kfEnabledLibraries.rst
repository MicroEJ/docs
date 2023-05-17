.. _multiapps.enabled.libraries:

Multi-Sandbox Enabled Libraries
===============================

A Multi-Sandbox enabled library is a Foundation Library or an Add-On Library that can be embedded
by a Kernel with its APIs exposed to Features.

A library requires specific code for enabling Multi-Sandbox in the following cases:

- it implements an internal global state: lazy initialization of a singleton, registry of callbacks, internal cache, ...,
- it provides access to native resources that must be controlled using a Security Manager.

Otherwise the library is called a stateless library.
A stateless library is Multi-Sandbox enabled by default: it can be embedded by the Kernel and its APIs directly exposed to Features without code modification.

.. note::
   
   This chapter applies more generally to any Kernel code, not only to Libraries.

Manage Internal Global State
----------------------------

A Library may define code that performs modifications of its internal state, for example:

- lazy initialization of a singleton,
- registering/un-registering a callback,
- maintaining an internal global cache, ...

By default, calling one of these APIs from a Feature context will throw one of the following error:

.. code-block:: 
   
   java.lang.IllegalAccessError: KF:E=S1
      at <Kernel Method>
      ...
      at <Feature Method>

   java.lang.IllegalAccessError: KF:E=F1
      at <Kernel Method>
      ...
      at <Feature Method>

The reason is that the Core Engine rejects the assignment of a Feature object in a static field or an instance field owned by the Kernel.
See the :ref:`KF library access error codes <kf-access-error-codes>` for more details.
This prevents to create unwanted object links from the Feature to the Kernel, which would lead to stale references when stopping the Feature.

The library code must be adapted to implement the desired behavior when the code is called from a Feature context. 
Next sections describe the most common strategies applied on a concrete example:

- declaring a static field local to the Feature,
- allowing a field assignment in Kernel mode,
- using existing Multi-Sandbox enabled data structures.

Declare a Static Field Local to the Feature
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :ref:`kf_specification` defines Context Local Storage for static fields.
This indicates the Core Engine to allocate a dedicated memory slot to store the static field for each execution context (the Kernel and each Feature).

Context Local Storage for static fields is typically used when the Library defines a lazy initialized singleton. 
A lazy initialized singleton is a singleton that is only allocated the first time it is required.
This is how is implemented the well known `Math.random()`_ method:

.. code-block:: java

   public class Math{
      private static Random RandomGenerator;

      public static double random() {
         if(RandomGenerator == null) {
            RandomGenerator = new Random();
         }
         return RandomGenerator.nextDouble();
      }
   }

To enable this code for Multi-Sandbox, you can simply declare the static field local to the context.
For that, create a ``kernel.intern`` file at the root of the application classpath (e.g. in ``src/main/resources`` directory) with the following content:

.. code-block:: xml

   <kernel>
      <contextLocalStorage name="java.lang.Math.RandomGenerator"/>
   </kernel>

When the method is called in a new context, the static field is read to ``null``, then a new object will be allocated and assigned to the local static field.
Thus, each context will create its own instance of the ``Random`` singleton on demand.

.. note:: 

   By default, reading a static field for the first time in a new context returns ``null``.
   It is possible to write dedicated code for initializing the static field before it first read access.
   See section `§4.3.3 Context Local Static Field References` of the :ref:`kf_specification` for more details.

   
.. _Math.random(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Math.html#random--

Allow a Field Assignment in Kernel Mode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is possible to assign a Feature object in a static field or an instance field owned by the Kernel, provided the current context is owned by the Kernel.
Such assignment must be removed before stopping the Feature. 
The common way is to register a `FeatureStateListener`_ at Kernel boot. This gives a hook to remove Kernel links to Feature objects when a Feature is moving to the ``STOPPED`` state.

.. code-block:: java

   Kernel.addFeatureStateListener(new FeatureStateListener() {

      @Override
      public synchronized void stateChanged(Feature feature, State previousState) {
         if (feature.getState() == State.STOPPED) {
            // Here, remove Kernel->Feature references
         }
      }
   };

Without this, the Feature will remain in the ``STOPPED`` state. It will not be possible to uninstall it or to start it again until the link is removed.
Remaining Feature objects references by the Kernel are called Kernel stale references.

.. note:: 

   To help debugging your Kernel, Kernel stale references are displayed by the :ref:`Core Engine dump <vm_dump>`.

.. _FeatureStateListener: https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/FeatureStateListener.html

Use Existing Multi-Sandbox Enabled Data Structures
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MicroEJ Corp. provides ready-to-use classes on the shelf that are Multi-Sandbox enabled. 
Among we can cite:

- ``KernelObservable``: Implementation of Observable which can handle observers from any Module.
- ``KFList``: Implementation of a Collection with multi-context support.
- ``SharedPropertyRegistry``: Map of key/value properties.
- ``SharedServiceRegistry``: Map of api/implementation services.

Please contact :ref:`our support team <get_support>` for more details on usage.

Implementing a Security Manager Check
-------------------------------------

A Multi-Sandbox enabled Foundation Library should protect Feature accesses to native resources.
This is done by requesting a check to the current `SecurityManager`_ defined by the Kernel.

The following code is the typical code that must be written at the beginning of API methods.

.. code-block:: java

   void myAPIThatOpensAccessToANativeResource(){

      if (Constants.getBoolean("com.microej.library.edc.securitymanager.enabled")) {
         // Here, the Security Manager support is enabled. 

         SecurityManager securityManager = System.getSecurityManager();
         if (securityManager != null) {
            // Here, the Kernel has registered a Security Manager

            // Create a Permission with relevant parameters for the Security Manager to render the permission
            MyResourcePermission = new MyResourcePermission();

            // Request the permission check. 
            // If the Kernel rejects the permission it will throw a SecurityException
            securityManager.checkPermission(p);
         }
      }

      // Implementation code
      // ...

   }

.. note::

   The code is wrapped by a static check of the :ref:`option_enable_security_manager`.
   By default, this option is disabled, so the code is automatically removed by the SOAR.
   This allows to use your library in a Mono-Sandbox environment where ROM footprint matters.
   This option shall be enabled by your Kernel to enable the Security Manager check.

.. _SecurityManager: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/SecurityManager.html


Known Foundation Libraries Behavior
-----------------------------------

This section details the Multi-Sandbox semantic that have been added to
Foundation Libraries in order to be Multi-Sandbox enabled.
Usually, most of the Foundation Libraries provided by MicroEJ Corp. are Multi-Sandbox enabled,
unless the library documentation (e.g. ``README.md``) mentions specific limitations.


MicroUI
~~~~~~~

.. note::

   This chapter describes the current MicroUI version ``3``, provided by UI Pack version ``13.0.0`` or higher.
   If you are using the former MicroUI version ``2`` (provided by MicroEJ UI Pack version up to ``12.1.x``),
   please refer to this `MicroEJ Documentation Archive <https://docs.microej.com/_/downloads/en/20201009/pdf/>`_. 


Physical Display Ownership
^^^^^^^^^^^^^^^^^^^^^^^^^^

The physical display is owned by only one context at a time (the Kernel
or one Feature). The following cases may trigger a physical display
owner switch:

-  during a call to  `Display.requestShow(Displayable)`_, `Display.requestHide(Displayable)`_, `Display.requestRender()`_ or `Display.requestFlush()`_: after the successful permission check, it is assigned to the context owner.

-  during a call to `MicroUI.callSerially(Runnable)`_: after the successful permission check it is assigned to owner of the ``Runnable`` instance.

The physical display switch performs the following actions:

-  If a `Displayable`_ instance is currently shown on the ``Display``,
   the method `Displayable.onHidden()`_ is called,

-  All pending events (input events, display flushes, call serially
   runnable instances) are removed from the display event serializer,

-  System Event Generators handlers are reset to their default `EventHandler`_ instance,

-  The pending event created by calling `Display.callOnFlushCompleted(Runnable)`_ is removed and will be never added to the display event serializer.

.. warning:: 

   The display switch is performed immediately when the current thread is the MicroUI thread itself (during a MicroUI event such as a `MicroUI.callSerially(Runnable)`_). The caller looses the display and its next requests during same MicroUI event will throw a new display switch. Caller should call future display owner's code (which will ask a display switch) in a dedicated `MicroUI.callSerially(Runnable)`_ event.
   

The call to `Display.callOnFlushCompleted(Runnable)`_ has no effect when the display is not assigned to the context owner.

.. _Display.requestShow(Displayable): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestShow-ej.microui.display.Displayable-
.. _Display.requestHide(Displayable): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestHide-ej.microui.display.Displayable-
.. _Display.requestRender(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestRender--
.. _Display.requestFlush(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#requestFlush--
.. _MicroUI.callSerially(Runnable): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/MicroUI.html#callSerially-java.lang.Runnable-
.. _Displayable: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Displayable.html
.. _Displayable.onHidden(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Displayable.html#onHidden--
.. _EventHandler: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/event/EventHandler.html
.. _Display.callOnFlushCompleted(Runnable): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Display.html#callOnFlushCompleted-java.lang.Runnable-

Automatically Reclaimed Resources
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Instances of `ResourceImage`_ and `Font`_ are automatically reclaimed when a Feature is stopped.

.. _ResourceImage: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/ResourceImage.html
.. _Font: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Font.html

BON
~~~

Kernel Timer 
^^^^^^^^^^^^

A Kernel `Timer`_ instance can handle `TimerTask`_ instances owned by the Kernel or any Features.

It should not be created in :ref:`clinit code <soar_clinit>`, otherwise you may have to manually declare :ref:`explicit clinit dependencies <soar_clinit_explicit_dependencies>`.

.. _Timer: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/Timer.html
.. _TimerTask: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/TimerTask.html

Automatically Reclaimed Resources
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`TimerTask`_ instances are automatically canceled when a Feature is stopped.


ECOM
~~~~

The `ej.ecom.DeviceManager`_ registry allows to share devices across
Features. Instances of `ej.ecom.Device`_ that are registered with a
Shared Interface type are made accessible through a Proxy to all other
Features that embed the same Shared Interface (or an upper one of the
hierarchy).

.. _ej.ecom.DeviceManager: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/DeviceManager.html
.. _ej.ecom.Device: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/Device.html

ECOM-COMM
~~~~~~~~~

Instances of `ej.ecom.io.CommConnection`_ are automatically reclaimed
when a Feature is stopped.

.. _ej.ecom.io.CommConnection: https://repository.microej.com/javadoc/microej_5.x/apis/ej/ecom/io/CommConnection.html

FS
~~

Instances of `java.io.FileInputStream`_, `java.io.FileOutputStream`_
are automatically reclaimed when a Feature is stopped.

.. _java.io.FileInputStream: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/FileInputStream.html
.. _java.io.FileOutputStream: https://repository.microej.com/javadoc/microej_5.x/apis/java/io/FileOutputStream.html

NET
~~~

Instances of `java.net.Socket`_, `java.net.ServerSocket`_,
`java.net.DatagramSocket`_ are automatically reclaimed when a Feature
is stopped.

.. _java.net.Socket: https://repository.microej.com/javadoc/microej_5.x/apis/java/net/Socket.html
.. _java.net.ServerSocket: https://repository.microej.com/javadoc/microej_5.x/apis/java/net/ServerSocket.html
.. _java.net.DatagramSocket: https://repository.microej.com/javadoc/microej_5.x/apis/java/net/DatagramSocket.html

SSL
~~~

Instances of `javax.net.ssl.SSLSocket`_ are automatically reclaimed
when a Feature is stopped.

.. _javax.net.ssl.SSLSocket: https://repository.microej.com/javadoc/microej_5.x/apis/javax/net/ssl/SSLSocket.html

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
