.. _multiapps.enabled.libraries:

Multi-Sandbox Enabled Libraries
===============================

A multi-Sandbox enabled library is a foundation or Add-On Library which can
be embedded into the kernel and exposed as API. MicroEJ Foundation
Libraries provided in MicroEJ SDK are already multi-Sandbox enabled. A
stateless library - i.e. a library that does not contain any method
modifying an internal global state - is multi-Sandbox enabled by default.

This section details the multi-Sandbox semantic that have been added to
MicroEJ Foundation Libraries in order to be multi-Sandbox enabled.

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

-  during a call to ``ej.microui.display.Display.requestShow(ej.microui.display.Displayable)``, ``ej.microui.display.Display.requestHide(ej.microui.display.Displayable)`` or ``ej.microui.display.Display.requestRender()``: after the successful permission check, it is assigned to the context owner.

-  during a call to ``ej.microui.MicroUI.callSerially(java.lang.Runnable)``: after the successful permission check it is assigned to owner of the ``Runnable`` instance.

The physical display switch performs the following actions:

-  If a ``Displayable`` instance is currently shown on the ``Display``,
   the method ``Displayable.onHidden()`` is called,

-  All pending events (input events, display flushes, call serially
   runnable instances) are removed from the display event serializer,

-  System Event Generators handlers are reset to their default
   ``ej.microui.event.EventHandler`` instance,

-  The pending event created by calling ``Display.callOnFlushCompleted(Runnable)`` is removed and will be never added to the display event serializer.

.. warning:: 

   The display switch is performed immediately when the current thread is the MicroUI thread itself (during a MicroUI event such as a ``callSerially``). The caller looses the display and its next requests during same MicroUI event will throw a new display switch. Caller should call future display owner's code (which will ask a display switch) in a dedicated ``callSerially`` event.
   

The call to ``Display.callOnFlushCompleted(java.lang.Runnable)`` has no effect when the display is not assigned to the context owner.

Automatically Reclaimed Resources
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Instances of ``ej.microui.display.ResourceImage``, ``ej.microui.display.Font``
are automatically reclaimed when a Feature is stopped.

ECOM
~~~~

The ``ej.ecom.DeviceManager`` registry allows to share devices across
Features. Instances of ``ej.ecom.Device`` that are registered with a
shared interface type are made accessible through a Proxy to all other
Features that embed the same shared interface (or an upper one of the
hierarchy).

ECOM-COMM
~~~~~~~~~

Instances of ``ej.ecom.io.CommConnection`` are automatically reclaimed
when a Feature is stopped.

FS
~~

Instances of ``java.io.FileInputStream``, ``java.io.FileOutputStream``
are automatically reclaimed when a Feature is stopped.

NET
~~~

Instances of ``java.net.Socket``, ``java.net.ServerSocket``,
``java.net.DatagramSocket`` are automatically reclaimed when a Feature
is stopped.

SSL
~~~

Instances of ``javax.net.ssl.SSLSocket`` are automatically reclaimed
when a Feature is stopped.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
