.. _pack_event:

===========
Event Queue
===========


Principle
=========

The Event Queue Foundation Library provides an asynchronous communication interface between the native world and the Managed world based on events.
Its functional architecture and usage are documented in the :ref:`Application Developer Guide <event_queue>`.

Dependencies
============

-  ``LLEVENT_impl.h`` and ``LLEVENT.h`` implementations (see
   :ref:`LLEVENT-API-SECTION`).

.. _pack_event_installation:

Installation
============

The Event Queue :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. group-tab:: SDK 6 (build.gradle.kts)

      For Event Queue 2.3.0 and higher:

      .. code-block:: kotlin

         microejPack("ej.api:event:2.3.0")

      |

      For Event Queue 2.2.0 and lower:

      .. code-block:: kotlin

         microejPack(group="com.microej.pack.event", name="event-pack", version="2.2.0", configuration="mockAPI")

   .. group-tab:: SDK 5 (module.ivy)

      For Event Queue 2.3.0 and higher:

      .. code-block:: xml

         Not Supported

      |

      For Event Queue 2.2.0 and lower:

      .. code-block:: xml

         <dependency org="com.microej.pack.event" name="event-pack" rev="2.2.0" transitive="false"/>

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
