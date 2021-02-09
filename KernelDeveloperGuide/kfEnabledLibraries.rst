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

Physical Display Ownership
^^^^^^^^^^^^^^^^^^^^^^^^^^

The physical display is owned by only one context at a time (the Kernel
or one Feature). A call to ``ej.microui.display.Display.requestShow(ej.microui.display.Displayable)`` may trigger a physical display owner switch: after the successful permission check, it is assigned to the context owner.

The physical display switch performs the following actions:

-  If a ``Displayable`` instance is currently shown on the ``Display``,
   the method ``Displayable.onHidden()`` is called.

-  All pending events (input events, display flushes, call serially
   runnable instances) are removed from the display event serializer

-  System Event Generators handlers are reset to their default
   ``ej.microui.event.EventHandler`` instance.

-  The pending event created by calling ``Display.callOnFlushCompleted(Runnable)`` is removed and will be never added to the display event serializer.

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
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
