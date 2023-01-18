.. _multiapps.enabled.libraries:

Multi-Sandbox Enabled Libraries
===============================

A Multi-Sandbox enabled library is a Foundation or Add-On Library which can
be embedded into the Kernel and exposed as API. MicroEJ Foundation
Libraries provided in MicroEJ SDK are already Multi-Sandbox enabled. A
stateless library - i.e. a library that does not contain any method
modifying an internal global state - is Multi-Sandbox enabled by default.

This section details the Multi-Sandbox semantic that have been added to
MicroEJ Foundation Libraries in order to be Multi-Sandbox enabled.

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
