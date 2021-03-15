========
Watchdog
========


Principle
=========

The Watchdog foundation library provides a way to handle platform watchdog timer.
A watchdog is particularly useful if you want to monitor different parts of your
software system during the runtime.

The Watchdog API is in **two parts**, the first part drives the **watchdog timer** itself.
The second part of the API implements a **checkpoint registration system** linked to the watchdog timer.

The checkpoint registration system allows the user to add checkpoints monitored by the platform watchdog timer.
Each checkpoint registered by the Watchdog API must attest their activity before the watchdog
timeout otherwise a **hardware reset** is performed.

The particularity of this library is that it can be either used in Java, in C inside the BSP
or even both of them. The use of this library in the BSP in C is relevant when the user needs
to monitor a part of the software system which is outside of the MicroEJ Virtual Machine.

Dependencies
============

- This library needs to be used with the Watchdog Generic CCO developed for this purpose,
  its module name is ``watchdog-generic``.

- ``LLWATCHDOG_impl.h`` implemetend by the Watchdog Generic CCO (see :ref:`LLWATCHDOG-API-SECTION`).

- ``watchdog_helper.h`` implementation needed by the Watchdog Generic CCO (see :ref:`LLWATCHDOG-API-SECTION`).

Installation
============

Watchdog is an API composed of a ``Pack`` module and a ``CCO`` module.
You need both of them in your platform to install the API.

In the platform configuration project, the one with ``-configuration`` extension, add
the dependency to the two required modules in the file ``module.ivy``:

::

   <dependency org="com.microej.pack.monitoring" name="monitoring-pack" rev="1.0.0" />
   <dependency changing="true" org="com.microej.clibrary.llimpl" name="watchdog-generic" rev="2.0.0" transitive="false"/>

Then, you have to implement functions that match the ``LLWATCHDOG_IMPL_*_action`` pattern
which is required by the Watchdog Generic CCO.

If you use the Realtek ``AmebaD`` board, you can add in the platform configuration the dependency
to the CCO module ``watchdog-helper-realtek-amebad``, in order to retrieve implemented
functions required by the Watchdog Generic CCO. Thus, add this line to ``module.ivy``:

::

   <dependency changing="true" org="com.microej.clibrary.llimpl" name="watchdog-helper-realtek-amebad" rev="1.0.0" transitive="false"/>

Then, build the platform: right-click on ``-configuration`` project > ``Build module``.

Use in a Java application
=========================

The `Watchdog API Module <https://repository.microej.com/artifacts/ej/api/monitoring/>`_
must be added to the :ref:`module.ivy <mmm_module_description>` of the MicroEJ 
Application project in order to allow access to the Watchdog library.

::

   <dependency org="ej.api.monitoring" name="watchdog" rev="1.0.1" transitive="false"/>


Use in C inside the BSP
=======================

Once the platform is configured to use the Watchdog API as explained in ``Installation``
section, you can use functions defined in ``LLWATCHDOG_impl.h``.

Note that compared to the Java API, you have to get error codes returned by functions
to check if the function is executed correctly since you have no access to
exceptions generated for the Java.

There is an additional function in ``LLWATCHDOG_impl.h`` compared to the Java API.
This is ``LLWATCHDOG_IMPL_refresh``, because a low level implementation of this function
is required for the library. However, the user does not need and should not use this function on his own.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
