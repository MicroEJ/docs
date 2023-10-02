.. _pack_event:

===========
Event Queue
===========


Principle
=========

The Event Queue Foundation Library provides an asynchronous communication interface between the native world and the Java world based on events.
Its functional architecture and usage are documented in the :ref:`Application Developer Guide <event_queue>`.

Dependencies
============

-  ``LLEVENT_impl.h`` and ``LLEVENT.h`` implementations (see
   :ref:`LLEVENT-API-SECTION`).

.. _pack_event_installation:

Installation
============

The Event Queue :ref:`Pack <pack_overview>` module must be installed in your VEE Port.

In the VEE Port configuration project, add the following dependency to the :ref:`module.ivy <mmm_module_description>` file:

::

   <dependency org="com.microej.pack.event" name="event-pack" rev="1.0.0" transitive="false"/>

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
