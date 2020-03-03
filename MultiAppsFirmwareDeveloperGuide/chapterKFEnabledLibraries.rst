.. _multiapps.enabled.libraries:

Multi-App Enabled Libraries
===========================

A multi-app enabled library is a foundation or add-on library which can
be embedded into the kernel and exposed as API. MicroEJ foundation
libraries provided in MicroEJ SDK are already multi-app enabled. A
stateless library - i.e. a library that does not contain any method
modifying an internal global state - is multi-app enabled by default.

Foundation Libraries Multi-App Semantic
---------------------------------------

This section details the multi-app semantic that have been added to
MicroEJ foundation libraries in order to be multi-app enabled.

MicroUI
~~~~~~~

Physical Display Ownership
^^^^^^^^^^^^^^^^^^^^^^^^^^

The physical display is owned by only one context at a time (the Kernel
or one Feature). The following cases may trigger a physical display
owner switch:

-  during a call to ``ej.microui.display.Displayable.show()``: after the
   successful permission check, it is assigned to the context owner.

-  during a call to
   ``ej.microui.display.Display.callSerially(java.lang.Runnable)``:
   after the successful permission check it is assigned to owner of the
   ``Runnable`` instance.

The physical display switch performs the following actions:

-  If a ``Displayable`` instance is currently shown on the ``Display``,
   the method ``Displayable.becomeHidden()`` is called.

-  All pending events (input events, display flushes, call serially
   runnable instances) are removed from the display event serializer

-  System Event Generators handlers are reset to their default
   ``ej.microui.util.EventHandler`` instance.

Automatically Reclaimed Resources
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Instances of ``ej.microui.display.Image``, ``ej.microui.display.Font``
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
