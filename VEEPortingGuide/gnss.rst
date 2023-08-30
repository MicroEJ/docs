.. _pack_gnss:

====
GNSS
====


Principle
=========

The GNSS module defines a low-level GNSS framework for embedded
devices. It allows you to manage the underlying GNSS engine and retrieve data such as the longitude, latitude, velocity and time.


Functional Description
======================

The MicroEJ Application manages the GNSS engine using
GnssManager abstraction. The GNSS implementation made for each MicroEJ
Platform is responsible for surfacing the native File System specific
behavior.

Interaction with the GNSS API goes through a GNSS manager. This manager works around a state machine. 
To perform read operations to retrieve GNSS data, the machine must be in a STARTED state. 
Transitions between the states are controlled by the user.
:ref:`The following graph <fig_gnss-state-machine>`: details the different states, their function and transitions.

.. _fig_gnss-state-machine:
.. figure:: images/gnss-state-machine.*
   :alt: GNSS state machine.
   :align: center
   :scale: 75%

   GNSS State Machine

GNSS Mock
=========

GNSS values on simulator can be control through an UI that could be activated and deactivated with the property : ``com.is2t.gnss.embedded.mock.ui``.

Dependencies
============

-  ``LLGNSS_impl.h`` implementations (see
   :ref:`LLGNSS-API-SECTION`).


Installation
============

The GNSS :ref:`Pack <pack_overview>` module must be installed in your VEE Port.

In the Platform configuration project, (``-configuration`` suffix), add
the following dependency to the :ref:`module.ivy <mmm_module_description>` file:

::

	<dependency org="com.microej.pack.gnss" name="gnss-pack" rev="2.0.0" />

The Platform project must be rebuilt (:ref:`platform_build`).

Use
===

The `GNSS API Module`_ must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project to use the GNSS library.

.. code-block:: xml

   <dependency org="ej.api" name="gnss" rev="2.0.0"/>

.. _GNSS API Module: https://repository.microej.com/modules/ej/api/gnss/

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
